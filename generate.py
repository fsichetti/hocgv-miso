"""
Generate miso C++ solver classes for polyfem Jacobian validity checks.

Produces two classes per (D, P) pair:
  P{P}{Simplex}Val  -- SOLVE: static injectivity check (det J > 0 everywhere)
  P{P}{Simplex}CGV  -- MINIMIZE: continuous geometric validity (max safe time step)
  JacEval_P{P}{Simplex}  -- evaluator for det J at a point (used for P=1 static check
                             and robust_evaluate_jacobian)

Run:
    python generate.py
"""
import os
import sys
import shutil
import subprocess

from sympy import Matrix, symbols

# Clone pymiso from GitLab into ignore/pymiso if not already present, and keep
# it on the branch this project needs.
_HERE = os.path.dirname(os.path.abspath(__file__))
_PYMISO_DIR = os.path.join(_HERE, 'ignore', 'pymiso')
_PYMISO_URL = 'https://gitlab.com/minimize-solve/pymiso.git'
_PYMISO_BRANCH = 'degenerate-check'

if not os.path.isdir(_PYMISO_DIR):
    os.makedirs(os.path.join(_HERE, 'ignore'), exist_ok=True)
    subprocess.run(['git', 'clone', '--branch', _PYMISO_BRANCH,
                    _PYMISO_URL, _PYMISO_DIR], check=True)
else:
    subprocess.run(['git', '-C', _PYMISO_DIR, 'fetch', 'origin', _PYMISO_BRANCH], check=True)
    subprocess.run(['git', '-C', _PYMISO_DIR, 'checkout', _PYMISO_BRANCH], check=True)

sys.path.insert(0, _PYMISO_DIR)
from miso import Domain, Basis, make_poly, generate, generate_evaluator

SRC_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'generated')

SIMPLEX = {1: 'Lin', 2: 'Tri', 3: 'Tet'}


def SimplexChecks(D, P):
    """
    Generate both static (Val) and continuous (CGV) validity solvers for a
    degree-P map on a D-simplex. Two generate() calls share the symbolic setup.
    """
    simplex = SIMPLEX[D]
    X = Domain(' '.join(f'x{i}' for i in range(D)))
    T = Domain('t')
    domain = X * T
    t = domain.variables[-1]  # T[0] may differ by identity from domain.variables

    # Compute the static Jacobian determinant (shared symbolic work)
    x = X.poly_map(P, Basis.BERNSTEIN, codomain_dim=D, name='p', output_miso_poly=False)
    Jx = x.jacobian(X.variables).applyfunc(make_poly)
    jd_val = make_poly(Jx.det())

    # Evaluator: standalone function computing det J at a point (all free symbols
    # become parameters). Used for P=1 static validity check (constant det) and
    # for robust_evaluate_jacobian (pointwise evaluation for P>1).
    generate_evaluator(SRC_DIR, f'JacEval_P{P}{simplex}', jd_val)
    print(f'JacEval_P{P}{simplex} done')

    # Tets may have edge control points collapsed onto a corner, which makes
    # det J vanish there to order equal to the number collapsed; order 2 covers
    # the two-collapsed case. The caller selects the element and order at
    # runtime via degenerateState, so a non-degenerate element is unaffected.
    # Not applied to P=1: a linear map has no edge control points to collapse,
    # and its det J is constant in the domain variables.
    degenerate = 2 if (D == 3 and P > 1) else False

    # Call 1: static validity (SOLVE, no objective)
    # P=1: Jacobian of a linear map is constant in domain variables (degree 0);
    # miso's Bernstein converter requires degree >= 1.  Handled directly in C++.
    if P > 1:
        generate(SRC_DIR, f'P{P}{simplex}Val', X, [jd_val], parallel=True,
                 allow_degenerate=degenerate)
        print(f'P{P}{simplex}Val done')

    # CGV: blended map (1-t)*p0 + t*p1, space-time Jacobian determinant
    p0 = X.poly_map(P, Basis.BERNSTEIN, codomain_dim=D, name='p0')
    p1 = X.poly_map(P, Basis.BERNSTEIN, codomain_dim=D, name='p1')
    p = [make_poly(a * (1 - t) + b * t) for a, b in zip(p0, p1)]
    p_ext = p + [t]  # plain symbol: avoids sympy Function canonicalization swapping t identity
    jd_cgv = make_poly(Matrix(p_ext).jacobian(domain.variables).applyfunc(make_poly).det())
    sd_all = domain.default_subdivision
    sd_t = domain.make_subdivision(T)

    # Call 2: continuous geometric validity (MINIMIZE, objective=t)
    # The degenerate element becomes {corner} x [0,1] here: the collapse holds
    # at both ends of a linear blend, so it holds at every time. Only spatial
    # derivatives revive det J there, so the order is still measured in the
    # three spatial directions.
    generate(SRC_DIR, f'P{P}{simplex}CGV', domain, [jd_cgv],
             objective=t, subdivisions=[sd_all, sd_t],
             parallel=(2 if degenerate and P > 2 else True),
             allow_degenerate=degenerate)
    print(f'P{P}{simplex}CGV done')


if __name__ == '__main__':
    os.makedirs(SRC_DIR, exist_ok=True)
    # Clear existing class subdirectories; keep top-level CMakeLists.txt / include.hpp
    for entry in os.scandir(SRC_DIR):
        if entry.is_dir():
            shutil.rmtree(entry.path)

    for D, P in [(2, 1), (2, 2), (2, 3), (2, 4), (3, 1), (3, 2), (3, 3)]:
        SimplexChecks(D, P)

    print('All done.')
