# Degenerate-element positivity checks

This note documents the `degenerate-check` branch, which spans three repos:

- **pymiso** — the Python code generator (`degenerate-check` branch)
- **misolib** — the header-only C++ runtime library (`degenerate-check` branch)
- **hocgv-miso** (this repo) — generated code + polyfem-facing glue and examples

It adds an opt-in way to certify a Bernstein polynomial (here: a Jacobian
determinant `det J`) strictly positive over a simplicial domain even when the
polynomial is *known* to vanish, by construction, on one boundary element
(a vertex, edge, or face) of that domain.

## The problem

`solve()`/`minimize()` certify positivity by subdividing the domain and, on
each subdomain, taking min/max over that subdomain's Bernstein coefficients
(`RealVector::inclusion()`). This is a valid enclosure, but it is only useful
if the true minimum is bounded away from zero.

Polyfem's Jacobian checks sometimes generate elements where `det J` is
*supposed* to vanish on a face by construction — e.g. a corner where two edge
control points have been collapsed onto the corner's own control point, so
one column (or more) of the Jacobian is identically zero there. A plain
`inclusion()` sees the resulting zero coefficient (and the ring of
neighboring coefficients it forces toward zero too, for higher-order
vanishing) and reports `lower <= 0` on every subdomain touching that face,
forever — subdivision never shrinks the reported minimum above zero because
the zero is real, not a numerical artifact. `solve()` never terminates with
a clean answer; `minimize()` never returns a useful bound.

## The idea

If a function vanishes to order `m` on a face of the domain, its Bernstein
coefficients at lattice points *on* the face are exactly zero, and so are the
coefficients within `m` "layers" of it (see below). Excluding those known-zero
coefficients from the min/max still gives a sound bound on the function's
values **away from the face**: Bernstein basis functions indexed by an excluded
lattice point vanish on the face themselves, so they contribute nothing to the
function's value there, and a strictly positive reduced minimum implies strict
positivity everywhere except on the face itself. This is a **positivity
certificate**, not an enclosure — it cannot bound values *on* the face (it
already assumes those are zero) and it cannot be composed through interval
arithmetic. It only ever applies to bare constraint leaves (`MiSoPoly`
inclusions), never the objective.

Which coefficients count as "on the face" depends on where the face sits in
the *current* subdomain, and that changes under subdivision — hence a small
per-class state machine that rides along with each subdomain object and
tracks "which face, and to what order" as subdivision proceeds.

## Why "order" has to be an a priori claim, not something derived

It's worth being precise about *why* this needs a state machine and a
caller-supplied order at all, rather than something simpler. With exact
arithmetic, none of this would be necessary: "exclude coefficient `i` from
the min iff `c_i` is exactly 0" is sound and complete all by itself. You'd
never exclude too little (any genuinely nonzero coefficient would just show
up as nonzero) and never too much (you can't discard a value by checking
whether it equals zero and being wrong about it). Order — and the whole
face/order state machine — exists *only* because the runtime representation
is a rounded interval, not an exact value, and a rounded interval containing
zero is consistent with two very different realities: a coefficient that is
truly, exactly zero by construction (safe to drop), or a coefficient that is
genuinely small and negative — a real self-intersection — that just hasn't
been resolved by enough subdivision yet (not safe to drop). Interval
arithmetic alone cannot tell these apart, so the code needs to be *told*
which one it is, a priori, by whoever performed the exact construction (the
number of control points actually collapsed) — that's what `order` is.

This also fixes the scope of the concern. It only applies to the *declared*
face's own coefficients, which are being claimed to vanish identically over
an entire sub-manifold (an algebraic fact about the construction, not
something observed). It does not extend to an incidental zero coefficient
turning up somewhere else:
- Away from any domain vertex, a Bernstein coefficient is just a control
  point, not an interpolation of the function — only the pure lattice point
  at a vertex equals the function's actual value there. A stray zero
  elsewhere is a coarse-grid artifact; it carries no information, and a
  subdivision or two will generically move it off zero on its own (the
  ordinary, non-degenerate algorithm already relies on this to make
  progress). Nothing needs to treat it specially.
- At a *different*, non-declared vertex, a zero coefficient is exact and
  permanent (same interpolation property), so it would never wash out under
  subdivision — but that's not a gap in this mechanism either: the ordinary
  algorithm just never certifies that region, which is the correct, safe
  (if incomplete) outcome for a genuinely different degeneracy the caller
  didn't declare.

`inclusionDegenerate`'s `assert(lower(data[i]) <= 0 && upper(data[i]) >= 0)`
is the closest available substitute for the equality check exact arithmetic
would give for free — but it's strictly weaker: it only catches a claim
that's grossly wrong (e.g. the wrong vertex or an order too high for the
actual construction), not the subtle case of a real small negative value
whose rounded interval still happens to straddle zero. So the certificate's
soundness ultimately rests on the caller's a priori claim about what they
built, not on anything the runtime verifies — which is the real reason the
order (and which face) must be supplied by the generator/caller rather than
inferred from the coefficients at runtime.

## Subdivision near the degenerate element

Excluding the right coefficients is not enough on its own for orders ≥ 2:
with uniform (red) subdivision the search can still fail to terminate.

**Why it stalls.** A uniform corner child is its parent scaled by 1/2 about
the corner `v`. Near `v`, `det J(v + h·y) = h^m·Q_m(y) + O(h^{m+1})`, where
`Q_m` is the degree-`m` leading form. So the corner child's layer-`m`
coefficients tend (up to the factor `h^m`) to the degree-`m` Bernstein
coefficients of `Q_m` on the facet opposite `v`, and scaling about `v` never
changes those. For `m = 1` they're just `Q_1`'s values at the facet's
vertices, so positive in means positive out. For `m = 2` a quadratic can be
positive on the facet while one of its mixed coefficients is negative; the
corner child then keeps a negative coefficient at every depth and never
certifies, although the element is valid. The test case in
`tests/test_jacobian.cpp` is such an element: with uniform subdivision it hits
the 20 000-iteration cap at depth 540.

**The fix: `corner_refined_subdivision(D)`** (pymiso, `miso/subdivision.py`).
This is uniform subdivision, except that each corner child is split further
into the cones from its domain vertex over the uniform subdivision of its
opposite facet. For a tet that's 4 × 4 + 4 = 20 children; for a triangle,
3 × 2 + 1 = 7. Each level halves the corner child both radially and in the
directions around `v`, so `Q_m`'s coefficients are subdivided on the facet
and converge to its values, which are positive. The split is symmetric in the
vertices, so it doesn't depend on which vertex is degenerate or on vertex
labeling.

It is used only for subdomains in a degenerate state (`degenerateState != 0`,
i.e. those that still contain the degenerate element). Every other subdomain
keeps the scheme the algorithm asks for. For CGV it is taken in product with
time bisection, so `minimize()` can still locate the first invalid `t` near
the corner.

**The state machine works with any scheme.** Transitions are computed from
whatever affine child maps the generator is given, and a child of an affine
scheme always meets a face of its parent in one of its own faces. That's
because the hyperplane cutting out the face also supports the child. So
adding or changing schemes only needs regeneration, and `degenerate.py`'s
consistency errors can't fire for a valid subdivision.

**Limitation.** The override is hardwired in the generated `split()`: a
subdomain in any nonzero state always uses the one degenerate scheme. Letting
schemes depend on the state more generally, or on other criteria, would need
a per-state table or a hook in misolib's algorithms.

## pymiso: `miso/degenerate.py` (new file)

This is the core of the feature: `build_degen_state_machine(domain,
all_subdivisions, member_subdomains, member_E, member_degs, max_order)`.

Terminology:
- A **face** of the reference domain is represented as one barycentric
  *support set* per simplex factor (a domain built as a product of simplices,
  e.g. `X * T` for space-time, has one factor per simplex). For a simplex with
  barycentric coordinates `lambda = (u_0, ..., u_{d-1}, 1 - sum(u))`, a
  point's support is the subset of indices where `lambda != 0`. A point lies
  on a face iff its support is contained in the face's support, factor by
  factor. The **empty face** (all supports empty) means "not degenerate" —
  this is state 0.
- **`layer_count(point, face, degs)`** — how many Bernstein "layers" a lattice
  point sits from the face: the total multi-index weight carried by the
  barycentric coordinates that vanish on the face. A function vanishing to
  order `m` has zero coefficients exactly where `layer_count < m`;
  `layer_count == 0` means the point is on the face itself.
- **`span(points)`** — the smallest face containing a set of points (used
  both to compute a face's image under subdivision, and to project a face
  onto a member's subdomain by re-spanning its projected vertices — exact
  because the projection of a polytope is the hull of its projected vertices).

Algorithm:
1. Enumerate every non-empty face of the domain (`all_faces`, as products of
   per-factor barycentric supports) crossed with every order `1..max_order`.
2. For each `(face, order)` pair, compute, per constraint member, which
   lattice indices have `layer_count < order` (`excluded_for`). If this would
   exclude *every* coefficient of some member, the state is dropped (a
   positivity certificate needs at least one surviving coefficient) and
   logged.
3. Surviving `(face, order)` pairs become states, indexed 0 (empty face) . `S-1`.
   Each state records: the bitmask of domain vertices on its face
   (`vertex_masks`), its order, the sorted vertex indices on the face
   (`sample_masks`, used to mask samples), and the excluded lattice index
   list per member (`excluded`).
4. **Transitions**: for every subdivision scheme and every child transform in
   it, map each state's face forward by applying the transform to the
   domain's vertices and re-spanning the hull of whichever vertices land on
   the parent face. This must exactly reproduce a known face of the domain,
   or the state machine is inconsistent (vertices don't span a domain face) —
   both are raised as hard errors, since a broken transition would silently
   let zero-coefficients leak into a state that doesn't account for them.
   Order is a local property, so it's carried through unchanged.
5. Domain vertex count is capped at 32 (bitmask width).

Returns `(vertex_masks, orders, sample_masks, transitions, excluded)`,
consumed directly by codegen.

## pymiso: `generate()` (`miso/generate.py`)

New keyword: `allow_degenerate=False` (bool or int). `True` means order 1;
an int `N` allows orders up to `N`. When set:

1. **Validates** every constraint (not the objective) is a bare `MiSoPoly`
   leaf (`inclusion_func`) — degenerate inclusion can't be propagated through
   arithmetic, so composite expressions are rejected with a clear error
   telling the caller to wrap with `make_poly()`.
2. Collects the distinct polynomial members appearing in constraints
   (`degen_members`), and calls `build_degen_state_machine` with each
   member's subdomain, evaluation lattice (`E`), and per-simplex degrees.
3. For each state, builds a parallel copy of the `inclusions` tuple where
   each degenerate member's plain `inclusion_func(m)` is replaced by
   `inclusion_degen_func(m, *excluded_indices)` — a new placeholder function
   (`miso/codewriter.py`) that lowers to `<member>.inclusionDegenerate<i0,i1,...>()`
   instead of `<member>.inclusion()`. Only constraints are touched; the
   objective always keeps the plain `inclusion()` call.
4. Packs everything into a `degenerate` dict (`vertex_masks`, `orders`,
   `excluded` (member name -> indices, one dict per state), `sample_masks`,
   `transitions`, `inclusions` (per-state expression tuples)) and passes it
   to `CodeGenerator.write_class`.

New keyword: `degenerate_subdivision=None` (a `Subdivision`, requires
`allow_degenerate`). It is appended to the subdivision schemes, so the
conversion matrices and state-machine transitions include it, and its index
is passed to codegen as `degenerate['scheme']`.

`parallel` also gained the ability to take an int (worker cap) rather than
just a bool, since the larger degenerate-enabled B2B conversions (bigger
signatures, more subdivision children) can exhaust memory with an unbounded
`ProcessPoolExecutor`.

## pymiso: codegen output (`miso/codegen.py`)

When `degenerate` is passed to `write_class`, the generated class
(`<Name>.hpp` / `<Name>.cpp`) gains:

- **`unsigned degenerateState = 0;`** member — which state (face x order) the
  instance currently represents. Defaults to 0 (not degenerate), so existing
  callers that never touch degeneracy are unaffected.
- **Static per-class tables** (kept in the `.cpp`, in an anonymous namespace,
  not the header — they can get long, the header is included by every
  translation unit, and nothing performance-sensitive reads them):
  - `kDegenerateStateVertices[S]` — vertex bitmask per state
  - `kDegenerateStateOrders[S]` — order per state
  - `kDegenerateTransitions[S][children]` — successor state per state per
    global child index (child indices are global across subdivision schemes,
    consistent with how `SubdivHistory` already addresses children)
- **Static lookup methods**, declared in the header:
  - `degenerateStateFromVertices(vertexMask, order=1)` — linear scan over the
    tables; returns `0` immediately for `vertexMask == 0`; throws
    `std::invalid_argument` if no matching state exists (e.g. asking for an
    order the generator wasn't told to support). This is the entry point
    callers use to seed `degenerateState` on a freshly built root element.
  - `degenerateStateVertexMask(s)`, `degenerateStateOrder(s)`,
    `degenerateTransition(s, q)` — thin accessors over the tables, exposed in
    case a caller needs to introspect a state.
- **`inherit(parent, q)`** (called when a subdomain is split into child `q`)
  now also sets `degenerateState = kDegenerateTransitions[parent.degenerateState][q]`,
  so the state rides along through subdivision automatically.
- **`split(scheme, f)`**: if a `degenerate_subdivision` was given, starts with
  `if (degenerateState != 0) scheme = <its index>;`, so subdomains on the
  degenerate element always use it regardless of what the algorithm asked for.
- **`inclusion(i)`**: for `i` < `num_constraints`, the generated switch now
  nests a second switch on `degenerateState`: non-zero states return the
  precomputed degenerate-inclusion expression for that state (which lowers to
  `.inclusionDegenerate<...>()` calls per the exclusion list), state 0 (and
  any state code didn't special-case) falls through to the original plain
  expression. The objective (`i >= num_constraints`) is untouched — degenerate
  certification never applies there.
- **`sample(i)`**: same shape, but each degenerate case wraps the sample
  expression in `maskDegenerate<v0,v1,...>(...)` (misolib, see below) with the
  state's `sample_masks` — the domain vertices lying on the degenerate face
  get poisoned to `+infinity` so they can never be reported as a feasible
  solution point (they are known zeros of the constraint, not genuine roots).
- **Zeroing known-zero coefficients before subdivision**
  (`degenerateZeroed_<member>()`): for every member that appears in some
  state's `excluded` list, codegen emits a method that copies the member's
  coefficient vector and, per state, sets the excluded indices to exact
  `Real(0)` before returning it. `split_impl<SI>()` calls this method (instead
  of using the raw member) when building each child's constructor arguments.
  This exists so a coefficient that is only *approximately* zero (due to
  floating point / interval rounding from the original conversion) doesn't
  have its tiny rounding-error width propagate and compound across many
  levels of subdivision — it's provably exactly zero given the degenerate
  state, so it's forced to exactly zero on the copy handed to children. Sound
  because the degenerate state is itself the assertion that these
  coefficients are zero; `inclusion()` on the *current* object still sees the
  original (unzeroed) coefficients, only the copy handed down to children is
  affected.

## pymiso: `miso/codewriter.py`

Adds `inclusion_degen_func = Function('MiSoInclusionDegenerate', real=True)`
alongside the existing `inclusion_func`/`sample_func` placeholders, and a
printer rule: `MiSoInclusionDegenerate(member, i0, i1, ...)` lowers to
`<member>.inclusionDegenerate<i0,i1,...>()`.

## misolib: `include/core/RealVector.hpp`

Two additions, both templated on the excluded/masked lattice indices so the
skip test compiles down to a constant per index rather than a runtime loop:

- **`inclusionDegenerate<M...>()`** — same min/max reduction as
  `inclusion()`, but skips indices in `M...`. Builds a `constexpr
  std::array<bool, N>` skip table at compile time (`O(N)` loop, not
  `O(N * sizeof...(M))`). For skipped coefficients it asserts
  `lower(data[i]) <= 0 && upper(data[i]) >= 0` (i.e. the coefficient really
  does bound zero — a debug-mode sanity check that the caller's claimed
  degenerate state matches reality) and otherwise ignores them entirely.
- **`maskDegenerate<M...>(RealVector<N> v)`** (free function) — sets lanes
  `M...` of a sampled vertex vector to `Real(infinity)` before returning it,
  so those vertices can never satisfy a `<= epsilon` feasibility test.

## misolib: `include/algorithms/{solve,minimize,batch-minimize}.hpp`

Each has one assertion loosened:
```cpp
assert(s.inclusion(i).contains(Cv[v]));
// becomes:
assert(upper(Cv[v]) == infinity || s.inclusion(i).contains(Cv[v]));
```
This assertion checks that every sampled vertex value falls inside the
constraint's own inclusion. It's no longer universally true: vertices on a
degenerate face are deliberately poisoned to `+infinity` by
`maskDegenerate`, and `+infinity` is obviously not contained in a finite
`inclusion()`. The assertion now only fires for vertices that weren't
poisoned.

## hocgv-miso: `generate.py`

Drives pymiso for each polyfem element type/degree. Changes:

- Pins the generator to the matching pymiso branch: clones/checks out
  `degenerate-check` explicitly instead of tracking whatever pymiso's default
  branch is, and re-fetches/checks it out on reruns against an existing
  clone.
- Switches the polynomial map basis from `Basis.LAGRANGE` to
  `Basis.BERNSTEIN` for both the static (`Val`) and blended (`CGV`) map
  construction. (Needed for the degenerate machinery to reason directly about
  Bernstein coefficients of the *map* nodes, not just of `det J`.)
- `degenerate = 2 if (D == 3 and P > 1) else False` — degenerate handling is
  generated only for 3D tets of degree > 1 (P1 tets have constant `det J`,
  nothing to make degenerate; only tets are handled currently, not
  triangles).
- Passes `allow_degenerate=degenerate` to both the `Val` and `CGV`
  `generate()` calls. For the CGV call, `parallel=(2 if degenerate and P > 2
  else True)` — caps worker count to 2 for the larger P3 degenerate case to
  avoid the memory blowup `parallel.py`'s int-cap change was added for.
- The generated `<X>CGV` classes correspond to a face `{corner} x [0,1]` in
  space-time (a spatial corner held degenerate for the whole time blend) —
  documented in a comment, not a code change, since order is still measured
  purely in the spatial directions (only spatial derivatives revive `det J`,
  a pure time-translation doesn't).
- Passes `degenerate_subdivision`: `corner_refined_subdivision(3)` for Val,
  and its product with time bisection for CGV. The degenerate tet classes now
  have schemes `{8, 20}` (Val) and `{16, 2, 40}` (CGV); the degenerate scheme
  is appended last so that `minimize()`'s hardcoded `scheme = 1` still means
  the time split in CGV.
- The CGV calls use `separate_subdivision=True`. With a single combined
  function, the 40-child split of `P3TetCGV` is ~5 MB of expressions in one
  body, and compiling it at `-O3` hadn't finished after more than an hour.
  With one file per child, the pieces are small and compile in parallel.

This means, for the checked-in generated code: `P2TetVal`, `P3TetVal`,
`P2TetCGV`, `P3TetCGV` were (re)generated with `allow_degenerate=2`; the
triangle classes (`P2TriVal/CGV`, `P3TriVal/CGV`, `P4TriVal/CGV`) were
regenerated too (Bernstein vs. Lagrange map basis affects their conversion
tables) but without degenerate support.

## hocgv-miso: generated output diffs

- `generated/P{2,3}TetVal.hpp` / `P{2,3}TetCGV.hpp` gain: `unsigned
  degenerateState = 0;`, `numDegenerateStates` (29 for both `Val` classes —
  one state per qualifying face/order pair on a tet, plus state 0),
  the four static degenerate methods, and a private
  `degenerateZeroed_m0()` declaration (only member `m0` needs zeroing here —
  the map's single polynomial member).
- The corresponding `.cpp` files gain the state tables and the switch-based
  `inclusion()`/`sample()` bodies described above. (These files are large —
  the diffstat shows thousands of changed lines per file — mostly because
  regenerating from `Basis.BERNSTEIN` instead of `Basis.LAGRANGE` changes
  every downstream conversion constant, not just the degenerate-specific
  additions.)
- `generated/CMakeLists.txt`: the `FetchContent` `GIT_TAG` for misolib is
  pinned to `degenerate-check` instead of a specific commit hash, so the
  generated build picks up the matching misolib branch.

## hocgv-miso: `EigenAdapters.hpp`

Adds `assertRoundingModeUp()` — asserts `fegetround() == FE_UPWARD`, i.e.
that `RealInterval::init()` was called before `solve()`/`minimize()`. Interval
arithmetic here depends on the FPU rounding mode being pinned upward; this is
a cheap guard against forgetting the `init()`/`deinit()` pairing, used in the
test and example mains after every `solve`/`minimize` call.

## hocgv-miso: `DegenerateHelpers.hpp` (new file)

Bridges polyfem's element/vertex conventions to miso's internal domain vertex
ordering and Bernstein lattice, so a caller never has to reason about miso's
internals. Provides four factory functions:

- `make_p2tet_val_degenerate(cp, offset, vertex, collapseTowards)`
- `make_p3tet_val_degenerate(cp, offset, vertex, collapseTowards)`
- `make_p2tet_cgv_degenerate(cp1, cp2, offset, vertex, collapseTowards)`
- `make_p3tet_cgv_degenerate(cp1, cp2, offset, vertex, collapseTowards)`

Each takes:
- `cp` (`cp1`/`cp2` for CGV) — a polyfem-ordered control point matrix (same
  input the plain `make_pXtet_*()` factories already take)
- `vertex` — the **polyfem-local** vertex index (0..3) where `det J` is
  allowed to vanish
- `collapseTowards` — 1 or 2 of the *other* polyfem vertex indices, i.e.
  which incident edges' near control points were collapsed onto `vertex`'s
  own control point; its size is also the certified vanishing order (1 or 2)

Internals (`namespace miso::detail`):
- `tetPolyfemVertexToDomain[4] = {0, 3, 2, 1}` — polyfem's `p_nodes_3d`
  vertex order vs. miso's `Domain.vertices` order are both the same 4
  reference-tet corners, just enumerated differently; this remaps one to the
  other.
- `tet2NearEdgeCP[4][4]` / `tet3NearEdgeCP[4][4]` — for quadratic/cubic tets,
  the polyfem row index of the control point nearest vertex `v` on the edge
  to vertex `w` (quadratic tets have one shared control point per edge;
  cubic tets have two, one near each end — only the "near `v`" one is
  relevant here).

Each `Val` factory builds the element normally (`make_pXtet_val`), then sets
`dom.degenerateState = PXTetVal::degenerateStateFromVertices(1u <<
tetPolyfemVertexToDomain[vertex], collapseTowards.size())`. The `CGV`
factories mask in *both* time-endpoints of the corresponding spatial vertex
(`domain.vertices` for a space-time product enumerates `(spatial vertex, t)`
with `t` fastest, so spatial vertex `m` is product vertices `2*m` and
`2*m+1`) since the collapse is applied identically at both ends of the linear
blend and therefore holds for the whole `[0,1]` time extent.

Note this file does **not** itself collapse any control points into `cp` —
the caller is expected to have already built `cp` with the relevant edge rows
equal to the corner's row; these helpers only compute and set the resulting
`degenerateState`. (Earlier versions did the collapse; commit `1deaf07`
removed it. The `tet{2,3}NearEdgeCP` tables are now unused, and the P3 tests
and the example below pass the uncollapsed reference tet, so they no longer
exercise a real zero: the "excluded" coefficients there are positive. That's
still sound, but the `inclusionDegenerate` assert fires in debug builds.)

## hocgv-miso: `tests/test_jacobian.cpp`

- Switches its include from `EigenAdapters.hpp` to `DegenerateHelpers.hpp`
  (which itself includes `EigenAdapters.hpp`, so this is purely additive).
- Wraps `main()` in `RealInterval::init()`/`deinit()` (previously implicit/
  absent) and asserts `assertRoundingModeUp()` after every `solve`/`minimize`
  call via the `check()` helper.
- New `"Degenerate elements (cubic tet)"` section with 3 cases on `P3TetVal`/
  `P3TetCGV`:
  1. One collapsed edge control point toward vertex 1 -> order-1 degeneracy
     at vertex 0 -> `solve()` still certifies valid (empty solution set).
  2. Two collapsed edge control points (vertices 1 and 2) -> order-2
     degeneracy at vertex 0 (this is exactly the case order-1 alone cannot
     certify, since the coefficient ring around the vertex is also forced to
     zero and stays self-similar under subdivision forever) -> `solve()`
     certifies valid only with order 2.
  3. Same order-2 geometry, blended via CGV with a uniformly translated copy
     -> `minimize()` should return `t_lo >= 1` (a pure translation can't turn
     a valid map invalid).
- A P2 case that actually collapses edges 0-1 and 0-2 onto vertex 0, with a
  leading quadratic that is positive on the opposite face but has a negative
  mixed Bernstein coefficient (found by a random search). It requires
  `solve()` to finish with `Info::Status::completed` and no solutions,
  within `maxIter = 20000`. With uniform subdivision it hit the cap at
  depth 540; with `corner_refined_subdivision` it certifies after 2
  iterations. As a soundness check (not in the test file), three elements
  whose leading quadratic goes negative on the opposite face — invalid only
  near the corner — were each rejected, at depths 2–5, by a negative sample
  in a subdomain still containing the corner.

## hocgv-miso: `examples/degenerate_tet.cpp` (new file) + `examples/CMakeLists.txt`

A standalone `degenerate_tet` executable (wired into the top-level
`CMakeLists.txt` via `add_subdirectory(examples)`) that exhaustively walks all
12 "two edges collapsed at one corner" configurations of a cubic tet (4
vertices x C(3,2)=3 edge-pairs each), first as `Val` (expects `solve()` to
report an empty solution set for every configuration) then again as `CGV`
blended against a uniformly translated copy (expects `minimize()` to report
`t_lo >= 1` for every configuration). Prints a `PASS`/`FAIL` line per case and
returns a nonzero exit code if any case fails — a broader regression sweep
than the 3 fixed cases in `test_jacobian.cpp`.

## Misc

- `.gitignore`: `build/` -> `build*/`, to also ignore `build_debug/`.
- `generated/JacEval_*` evaluator files changed only because the map basis
  switched from Lagrange to Bernstein upstream — no degenerate-specific
  content there.

## Putting it together: how a caller uses this

1. Generate with `allow_degenerate=N` for the polynomial(s) that may vanish
   on a face to order up to `N` (hocgv-miso's `generate.py` does this for 3D
   tet `Val`/`CGV` classes at `N=2`).
2. Build the element as usual, then set `degenerateState` once via the
   generated `degenerateStateFromVertices(vertexMask, order)` (or, for
   polyfem elements specifically, via one of `DegenerateHelpers.hpp`'s
   `make_pXtet_{val,cgv}_degenerate()` wrappers, which compute the vertex
   mask for you from polyfem-local vertex/edge indices).
3. Call `solve()`/`minimize()` as normal. `degenerateState` propagates
   automatically through `inherit()` on every subdivision; `inclusion()`
   automatically excludes the known-zero coefficients for the current state;
   `sample()` automatically poisons the degenerate face's vertices so they
   never surface as reported solution points; and known-zero coefficients are
   zeroed exactly before being handed to children, so their rounding error
   can't accumulate across subdivision depth.
4. State 0 (the default) means "not degenerate" and reproduces the original,
   unmodified behavior exactly — so this is fully opt-in per element
   instance, not just per generated class.
