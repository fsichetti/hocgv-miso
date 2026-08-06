#include "../P3TriCGV.hpp"
namespace miso {
	RealVector<45> P3TriCGV::CL_m0(const RealVector<10> &p0x, const RealVector<10> &p0y, const RealVector<10> &p1x, const RealVector<10> &p1y) {
		#pragma region Temporaries
		const Real _t0 = 3*p0x[0];
		const Real _t1 = 3*p0y[0];
		const Real _t2 = (1.5)*p0x[1];
		const Real _t3 = (1.5)*p1x[1];
		const Real _t4 = (1.5)*p0x[0] + (1.5)*p1x[0];
		const Real _t5 = (1.5)*p0y[4];
		const Real _t6 = (1.5)*p1y[4];
		const Real _t7 = (1.5)*p0y[0] + (1.5)*p1y[0];
		const Real _t8 = (1.5)*p0x[4];
		const Real _t9 = (1.5)*p1x[4];
		const Real _t10 = (1.5)*p0y[1];
		const Real _t11 = (1.5)*p1y[1];
		const Real _t12 = 3*p1x[0];
		const Real _t13 = 3*p1y[0];
		const Real _t14 = (1.6875)*p0x[0];
		const Real _t15 = -_t14;
		const Real _t16 = (0.5625)*p0x[1];
		const Real _t17 = (0.1875)*p0x[3];
		const Real _t18 = (1.6875)*p0y[0];
		const Real _t19 = (1.125)*p0y[5];
		const Real _t20 = -_t19;
		const Real _t21 = _t20 + (1.125)*p0y[1];
		const Real _t22 = (0.1875)*p0y[2];
		const Real _t23 = _t22 - 0.1875*p0y[6];
		const Real _t24 = -_t18;
		const Real _t25 = (0.5625)*p0y[1];
		const Real _t26 = (0.1875)*p0y[3];
		const Real _t27 = (1.125)*p0x[5];
		const Real _t28 = -_t27;
		const Real _t29 = _t28 + (1.125)*p0x[1];
		const Real _t30 = (0.1875)*p0x[2];
		const Real _t31 = _t30 - 0.1875*p0x[6];
		const Real _t32 = (0.84375)*p0x[0];
		const Real _t33 = (0.84375)*p1x[0];
		const Real _t34 = -_t32 - _t33;
		const Real _t35 = (0.09375)*p0x[3] + (0.09375)*p1x[3];
		const Real _t36 = (0.28125)*p0x[1] + (0.28125)*p1x[1];
		const Real _t37 = (0.5625)*p1y[1];
		const Real _t38 = (0.5625)*p0y[5];
		const Real _t39 = (0.5625)*p1y[5];
		const Real _t40 = -_t38 - _t39;
		const Real _t41 = _t25 + _t37 + _t40;
		const Real _t42 = (0.84375)*p0y[0];
		const Real _t43 = (0.84375)*p1y[0];
		const Real _t44 = _t42 + _t43;
		const Real _t45 = (0.09375)*p0y[2];
		const Real _t46 = (0.09375)*p1y[2];
		const Real _t47 = _t45 + _t46;
		const Real _t48 = _t47 - 0.09375*p0y[6] - 0.09375*p1y[6];
		const Real _t49 = -_t42 - _t43;
		const Real _t50 = (0.09375)*p0y[3] + (0.09375)*p1y[3];
		const Real _t51 = (0.28125)*p0y[1] + (0.28125)*p1y[1];
		const Real _t52 = (0.5625)*p1x[1];
		const Real _t53 = (0.5625)*p0x[5];
		const Real _t54 = (0.5625)*p1x[5];
		const Real _t55 = -_t53 - _t54;
		const Real _t56 = _t16 + _t52 + _t55;
		const Real _t57 = _t32 + _t33;
		const Real _t58 = (0.09375)*p0x[2];
		const Real _t59 = (0.09375)*p1x[2];
		const Real _t60 = _t58 + _t59;
		const Real _t61 = _t60 - 0.09375*p0x[6] - 0.09375*p1x[6];
		const Real _t62 = (1.6875)*p1x[0];
		const Real _t63 = -_t62;
		const Real _t64 = (0.1875)*p1x[3];
		const Real _t65 = (1.6875)*p1y[0];
		const Real _t66 = (1.125)*p1y[5];
		const Real _t67 = -_t66;
		const Real _t68 = _t67 + (1.125)*p1y[1];
		const Real _t69 = (0.1875)*p1y[2];
		const Real _t70 = _t69 - 0.1875*p1y[6];
		const Real _t71 = -_t65;
		const Real _t72 = (0.1875)*p1y[3];
		const Real _t73 = (1.125)*p1x[5];
		const Real _t74 = -_t73;
		const Real _t75 = _t74 + (1.125)*p1x[1];
		const Real _t76 = (0.1875)*p1x[2];
		const Real _t77 = _t76 - 0.1875*p1x[6];
		const Real _t78 = (0.75)*p0x[0];
		const Real _t79 = (0.75)*p0x[1];
		const Real _t80 = (0.75)*p0x[2];
		const Real _t81 = -0.75*p0x[3];
		const Real _t82 = (0.75)*p0y[4];
		const Real _t83 = -_t82;
		const Real _t84 = (0.75)*p0y[0];
		const Real _t85 = (1.5)*p0y[5];
		const Real _t86 = _t84 - _t85;
		const Real _t87 = -0.75*p0y[6];
		const Real _t88 = (0.75)*p0y[2];
		const Real _t89 = _t87 + _t88;
		const Real _t90 = (0.75)*p0y[1];
		const Real _t91 = -0.75*p0y[3];
		const Real _t92 = (0.75)*p0x[4];
		const Real _t93 = -_t92;
		const Real _t94 = (1.5)*p0x[5];
		const Real _t95 = _t78 - _t94;
		const Real _t96 = -0.75*p0x[6];
		const Real _t97 = _t80 + _t96;
		const Real _t98 = (0.375)*p0x[2];
		const Real _t99 = (0.375)*p1x[2];
		const Real _t100 = (0.375)*p0x[0];
		const Real _t101 = (0.375)*p1x[0];
		const Real _t102 = _t100 + _t101;
		const Real _t103 = -0.375*p0x[3] - 0.375*p1x[3];
		const Real _t104 = (0.375)*p0x[1];
		const Real _t105 = (0.375)*p1x[1];
		const Real _t106 = _t104 + _t105;
		const Real _t107 = (0.75)*p1y[1];
		const Real _t108 = (0.375)*p0y[4];
		const Real _t109 = (0.375)*p1y[4];
		const Real _t110 = -_t108 - _t109;
		const Real _t111 = (0.75)*p0y[5];
		const Real _t112 = (0.75)*p1y[5];
		const Real _t113 = (0.375)*p0y[0];
		const Real _t114 = (0.375)*p1y[0];
		const Real _t115 = _t113 + _t114;
		const Real _t116 = -_t111 - _t112 + _t115;
		const Real _t117 = (0.375)*p0y[2];
		const Real _t118 = (0.375)*p1y[2];
		const Real _t119 = _t117 + _t118;
		const Real _t120 = -0.375*p0y[6] - 0.375*p1y[6];
		const Real _t121 = _t119 + _t120;
		const Real _t122 = -0.375*p0y[3] - 0.375*p1y[3];
		const Real _t123 = (0.375)*p0y[1];
		const Real _t124 = (0.375)*p1y[1];
		const Real _t125 = _t123 + _t124;
		const Real _t126 = (0.75)*p1x[1];
		const Real _t127 = (0.375)*p0x[4];
		const Real _t128 = (0.375)*p1x[4];
		const Real _t129 = -_t127 - _t128;
		const Real _t130 = (0.75)*p0x[5];
		const Real _t131 = (0.75)*p1x[5];
		const Real _t132 = _t102 - _t130 - _t131;
		const Real _t133 = _t98 + _t99;
		const Real _t134 = -0.375*p0x[6] - 0.375*p1x[6];
		const Real _t135 = _t133 + _t134;
		const Real _t136 = (0.75)*p1x[0];
		const Real _t137 = (0.75)*p1x[2];
		const Real _t138 = -0.75*p1x[3];
		const Real _t139 = (0.75)*p1y[4];
		const Real _t140 = -_t139;
		const Real _t141 = (0.75)*p1y[0];
		const Real _t142 = (1.5)*p1y[5];
		const Real _t143 = _t141 - _t142;
		const Real _t144 = -0.75*p1y[6];
		const Real _t145 = (0.75)*p1y[2];
		const Real _t146 = _t144 + _t145;
		const Real _t147 = -0.75*p1y[3];
		const Real _t148 = (0.75)*p1x[4];
		const Real _t149 = -_t148;
		const Real _t150 = (1.5)*p1x[5];
		const Real _t151 = _t136 - _t150;
		const Real _t152 = -0.75*p1x[6];
		const Real _t153 = _t137 + _t152;
		const Real _t154 = (0.1875)*p0x[0];
		const Real _t155 = (0.5625)*p0x[2];
		const Real _t156 = -1.6875*p0x[3];
		const Real _t157 = (0.1875)*p0y[0];
		const Real _t158 = (0.1875)*p0y[4];
		const Real _t159 = (1.6875)*p0y[2];
		const Real _t160 = _t159 - 1.6875*p0y[6];
		const Real _t161 = (0.5625)*p0y[2];
		const Real _t162 = -1.6875*p0y[3];
		const Real _t163 = (0.1875)*p0x[4];
		const Real _t164 = (1.6875)*p0x[2];
		const Real _t165 = _t164 - 1.6875*p0x[6];
		const Real _t166 = (0.09375)*p0x[0] + (0.09375)*p1x[0];
		const Real _t167 = -0.84375*p0x[3] - 0.84375*p1x[3];
		const Real _t168 = (0.28125)*p0x[2] + (0.28125)*p1x[2];
		const Real _t169 = (0.09375)*p0y[4];
		const Real _t170 = (0.09375)*p1y[4];
		const Real _t171 = (0.09375)*p0y[0] + (0.09375)*p1y[0];
		const Real _t172 = (0.84375)*p0y[2] + (0.84375)*p1y[2];
		const Real _t173 = _t172 - 0.84375*p0y[6] - 0.84375*p1y[6];
		const Real _t174 = -0.84375*p0y[3] - 0.84375*p1y[3];
		const Real _t175 = (0.28125)*p0y[2] + (0.28125)*p1y[2];
		const Real _t176 = (0.09375)*p0x[4];
		const Real _t177 = (0.09375)*p1x[4];
		const Real _t178 = (0.84375)*p0x[2] + (0.84375)*p1x[2];
		const Real _t179 = _t178 - 0.84375*p0x[6] - 0.84375*p1x[6];
		const Real _t180 = (0.1875)*p1x[0];
		const Real _t181 = (0.5625)*p1x[2];
		const Real _t182 = -1.6875*p1x[3];
		const Real _t183 = (0.1875)*p1y[0];
		const Real _t184 = (0.1875)*p1y[4];
		const Real _t185 = (1.6875)*p1y[2];
		const Real _t186 = _t185 - 1.6875*p1y[6];
		const Real _t187 = (0.5625)*p1y[2];
		const Real _t188 = -1.6875*p1y[3];
		const Real _t189 = (0.1875)*p1x[4];
		const Real _t190 = (1.6875)*p1x[2];
		const Real _t191 = _t190 - 1.6875*p1x[6];
		const Real _t192 = 3*p0x[2];
		const Real _t193 = 3*p0y[2];
		const Real _t194 = (1.5)*p0x[2] + (1.5)*p1x[2];
		const Real _t195 = -1.5*p0y[6];
		const Real _t196 = -1.5*p1y[6];
		const Real _t197 = (1.5)*p0y[2] + (1.5)*p1y[2];
		const Real _t198 = -1.5*p0x[6];
		const Real _t199 = -1.5*p1x[6];
		const Real _t200 = 3*p1x[2];
		const Real _t201 = 3*p1y[2];
		const Real _t202 = (0.5625)*p0x[4];
		const Real _t203 = (0.1875)*p0x[9];
		const Real _t204 = (0.1875)*p0y[7];
		const Real _t205 = _t204 - 0.1875*p0y[8];
		const Real _t206 = _t20 + (1.125)*p0y[4];
		const Real _t207 = (0.5625)*p0y[4];
		const Real _t208 = (0.1875)*p0y[9];
		const Real _t209 = (0.1875)*p0x[7];
		const Real _t210 = _t209 - 0.1875*p0x[8];
		const Real _t211 = _t28 + (1.125)*p0x[4];
		const Real _t212 = (0.09375)*p0x[9] + (0.09375)*p1x[9];
		const Real _t213 = (0.28125)*p0x[4] + (0.28125)*p1x[4];
		const Real _t214 = (0.5625)*p1y[4];
		const Real _t215 = _t207 + _t214 + _t40;
		const Real _t216 = (0.09375)*p0y[7];
		const Real _t217 = (0.09375)*p1y[7];
		const Real _t218 = _t216 + _t217;
		const Real _t219 = _t218 - 0.09375*p0y[8] - 0.09375*p1y[8];
		const Real _t220 = (0.09375)*p0y[9] + (0.09375)*p1y[9];
		const Real _t221 = (0.28125)*p0y[4] + (0.28125)*p1y[4];
		const Real _t222 = (0.5625)*p1x[4];
		const Real _t223 = _t202 + _t222 + _t55;
		const Real _t224 = (0.09375)*p0x[7];
		const Real _t225 = (0.09375)*p1x[7];
		const Real _t226 = _t224 + _t225;
		const Real _t227 = _t226 - 0.09375*p0x[8] - 0.09375*p1x[8];
		const Real _t228 = (0.1875)*p1x[9];
		const Real _t229 = (0.1875)*p1y[7];
		const Real _t230 = _t229 - 0.1875*p1y[8];
		const Real _t231 = _t67 + (1.125)*p1y[4];
		const Real _t232 = (0.1875)*p1y[9];
		const Real _t233 = (0.1875)*p1x[7];
		const Real _t234 = _t233 - 0.1875*p1x[8];
		const Real _t235 = _t74 + (1.125)*p1x[4];
		const Real _t236 = (0.5625)*p0x[7];
		const Real _t237 = -_t79;
		const Real _t238 = -_t30;
		const Real _t239 = (0.1875)*p0x[6];
		const Real _t240 = (0.375)*p0x[5];
		const Real _t241 = _t240 - _t78;
		const Real _t242 = -_t204;
		const Real _t243 = (0.1875)*p0y[8];
		const Real _t244 = (0.375)*p0y[5];
		const Real _t245 = _t244 - _t84;
		const Real _t246 = -_t209;
		const Real _t247 = (0.1875)*p0x[8];
		const Real _t248 = (0.5625)*p0y[7];
		const Real _t249 = -_t90;
		const Real _t250 = -_t22;
		const Real _t251 = (0.1875)*p0y[6];
		const Real _t252 = (0.1875)*p1x[8];
		const Real _t253 = (0.28125)*p0x[7] + (0.28125)*p1x[7];
		const Real _t254 = -_t104 - _t105;
		const Real _t255 = -_t58 - _t59;
		const Real _t256 = (0.1875)*p0x[5] + (0.1875)*p1x[5];
		const Real _t257 = -_t100 - _t101 + _t256;
		const Real _t258 = (0.1875)*p1y[6];
		const Real _t259 = -_t216 - _t217;
		const Real _t260 = (0.1875)*p0y[5] + (0.1875)*p1y[5];
		const Real _t261 = -_t113 - _t114 + _t260;
		const Real _t262 = (0.1875)*p1x[6];
		const Real _t263 = -_t224 - _t225;
		const Real _t264 = (0.1875)*p1y[8];
		const Real _t265 = (0.28125)*p0y[7] + (0.28125)*p1y[7];
		const Real _t266 = -_t123 - _t124;
		const Real _t267 = -_t45 - _t46;
		const Real _t268 = (0.5625)*p1x[7];
		const Real _t269 = -_t126;
		const Real _t270 = -_t76;
		const Real _t271 = (0.375)*p1x[5];
		const Real _t272 = -_t136 + _t271;
		const Real _t273 = -_t229;
		const Real _t274 = (0.375)*p1y[5];
		const Real _t275 = -_t141 + _t274;
		const Real _t276 = -_t233;
		const Real _t277 = (0.5625)*p1y[7];
		const Real _t278 = -_t107;
		const Real _t279 = -_t69;
		const Real _t280 = -0.1875*p0x[9];
		const Real _t281 = -0.75*p0x[8];
		const Real _t282 = _t154 + _t281;
		const Real _t283 = _t157 + _t87;
		const Real _t284 = _t154 + _t96;
		const Real _t285 = -0.1875*p0y[9];
		const Real _t286 = -0.75*p0y[8];
		const Real _t287 = _t157 + _t286;
		const Real _t288 = -0.09375*p0x[9] - 0.09375*p1x[9];
		const Real _t289 = -0.375*p0x[8] - 0.375*p1x[8];
		const Real _t290 = _t166 + _t289;
		const Real _t291 = _t120 + _t171;
		const Real _t292 = _t134 + _t166;
		const Real _t293 = -0.09375*p0y[9] - 0.09375*p1y[9];
		const Real _t294 = -0.375*p0y[8] - 0.375*p1y[8];
		const Real _t295 = _t171 + _t294;
		const Real _t296 = -0.1875*p1x[9];
		const Real _t297 = -0.75*p1x[8];
		const Real _t298 = _t180 + _t297;
		const Real _t299 = _t144 + _t183;
		const Real _t300 = _t152 + _t180;
		const Real _t301 = -0.1875*p1y[9];
		const Real _t302 = -0.75*p1y[8];
		const Real _t303 = _t183 + _t302;
		const Real _t304 = _t27 - 1.125*p0x[6];
		const Real _t305 = _t19 - 1.125*p0y[8];
		const Real _t306 = _t27 - 1.125*p0x[8];
		const Real _t307 = _t19 - 1.125*p0y[6];
		const Real _t308 = _t53 + _t54;
		const Real _t309 = _t308 - 0.5625*p0x[6] - 0.5625*p1x[6];
		const Real _t310 = _t38 + _t39;
		const Real _t311 = _t310 - 0.5625*p0y[8] - 0.5625*p1y[8];
		const Real _t312 = _t308 - 0.5625*p0x[8] - 0.5625*p1x[8];
		const Real _t313 = _t310 - 0.5625*p0y[6] - 0.5625*p1y[6];
		const Real _t314 = _t73 - 1.125*p1x[6];
		const Real _t315 = _t66 - 1.125*p1y[8];
		const Real _t316 = _t73 - 1.125*p1x[8];
		const Real _t317 = _t66 - 1.125*p1y[6];
		const Real _t318 = (0.75)*p0x[7];
		const Real _t319 = -0.75*p0x[9];
		const Real _t320 = (0.75)*p0y[7];
		const Real _t321 = _t286 + _t320;
		const Real _t322 = -0.75*p0y[9];
		const Real _t323 = _t281 + _t318;
		const Real _t324 = (0.375)*p0x[7];
		const Real _t325 = (0.375)*p1x[7];
		const Real _t326 = -0.375*p0x[9] - 0.375*p1x[9];
		const Real _t327 = _t127 + _t128;
		const Real _t328 = (0.375)*p0y[7];
		const Real _t329 = (0.375)*p1y[7];
		const Real _t330 = _t328 + _t329;
		const Real _t331 = _t294 + _t330;
		const Real _t332 = -0.375*p0y[9] - 0.375*p1y[9];
		const Real _t333 = _t108 + _t109;
		const Real _t334 = _t324 + _t325;
		const Real _t335 = _t289 + _t334;
		const Real _t336 = (0.75)*p1x[7];
		const Real _t337 = -0.75*p1x[9];
		const Real _t338 = (0.75)*p1y[7];
		const Real _t339 = _t302 + _t338;
		const Real _t340 = -0.75*p1y[9];
		const Real _t341 = _t297 + _t336;
		const Real _t342 = -0.1875*p0y[3];
		const Real _t343 = (0.1875)*p0y[1];
		const Real _t344 = -0.1875*p0x[3];
		const Real _t345 = (0.1875)*p0x[1];
		const Real _t346 = (0.1875)*p1x[1];
		const Real _t347 = (0.09375)*p0y[1];
		const Real _t348 = (0.09375)*p1y[1];
		const Real _t349 = -0.09375*p0y[3] - 0.09375*p1y[3];
		const Real _t350 = (0.09375)*p0x[1];
		const Real _t351 = (0.09375)*p1x[1];
		const Real _t352 = -0.09375*p0x[3] - 0.09375*p1x[3];
		const Real _t353 = (0.1875)*p1y[1];
		const Real _t354 = -0.1875*p1y[3];
		const Real _t355 = -0.1875*p1x[3];
		const Real _t356 = -1.5*p0y[8];
		const Real _t357 = -1.5*p0x[8];
		const Real _t358 = _t130 + _t131;
		const Real _t359 = _t111 + _t112;
		const Real _t360 = -1.5*p1y[8];
		const Real _t361 = -1.5*p1x[8];
		const Real _t362 = -1.6875*p0x[9];
		const Real _t363 = (1.6875)*p0y[7];
		const Real _t364 = _t363 - 1.6875*p0y[8];
		const Real _t365 = -1.6875*p0y[9];
		const Real _t366 = (1.6875)*p0x[7];
		const Real _t367 = _t366 - 1.6875*p0x[8];
		const Real _t368 = -0.84375*p0x[9] - 0.84375*p1x[9];
		const Real _t369 = (0.84375)*p0y[7] + (0.84375)*p1y[7];
		const Real _t370 = _t369 - 0.84375*p0y[8] - 0.84375*p1y[8];
		const Real _t371 = -0.84375*p0y[9] - 0.84375*p1y[9];
		const Real _t372 = (0.84375)*p0x[7] + (0.84375)*p1x[7];
		const Real _t373 = _t372 - 0.84375*p0x[8] - 0.84375*p1x[8];
		const Real _t374 = -1.6875*p1x[9];
		const Real _t375 = (1.6875)*p1y[7];
		const Real _t376 = _t375 - 1.6875*p1y[8];
		const Real _t377 = -1.6875*p1y[9];
		const Real _t378 = (1.6875)*p1x[7];
		const Real _t379 = _t378 - 1.6875*p1x[8];
		const Real _t380 = 3*p0x[7];
		const Real _t381 = 3*p0y[7];
		const Real _t382 = (1.5)*p0x[7] + (1.5)*p1x[7];
		const Real _t383 = (1.5)*p0y[7] + (1.5)*p1y[7];
		const Real _t384 = 3*p1x[7];
		const Real _t385 = 3*p1y[7];
		#pragma endregion
		#pragma region Expressions
		return {
			-(-_t0 + 3*p0x[1])*(-_t1 + 3*p0y[4]) + (-_t0 + 3*p0x[4])*(-_t1 + 3*p0y[1]),
			(-_t4 + _t8 + _t9)*(_t10 + _t11 - _t7) - (_t2 + _t3 - _t4)*(_t5 + _t6 - _t7),
			-(-_t12 + 3*p1x[1])*(-_t13 + 3*p1y[4]) + (-_t12 + 3*p1x[4])*(-_t13 + 3*p1y[1]),
			(-_t14 - _t29 - _t31 + (1.6875)*p0x[4])*(_t24 + _t25 + _t26 + (0.9375)*p0y[2]) - (-_t18 - _t21 - _t23 + (1.6875)*p0y[4])*(_t15 + _t16 + _t17 + (0.9375)*p0x[2]),
			-(-_t41 - _t44 - _t48 + (0.84375)*p0y[4] + (0.84375)*p1y[4])*(_t34 + _t35 + _t36 + (0.46875)*p0x[2] + (0.46875)*p1x[2]) + (-_t56 - _t57 - _t61 + (0.84375)*p0x[4] + (0.84375)*p1x[4])*(_t49 + _t50 + _t51 + (0.46875)*p0y[2] + (0.46875)*p1y[2]),
			(-_t62 - _t75 - _t77 + (1.6875)*p1x[4])*(_t37 + _t71 + _t72 + (0.9375)*p1y[2]) - (-_t65 - _t68 - _t70 + (1.6875)*p1y[4])*(_t52 + _t63 + _t64 + (0.9375)*p1x[2]),
			-(-_t10 - _t83 - _t86 - _t89)*(-_t78 - _t79 + _t80 - _t81) + (-_t2 - _t93 - _t95 - _t97)*(-_t84 + _t88 - _t90 - _t91),
			-(-_t102 - _t103 - _t106 + _t98 + _t99)*(-_t107 - _t110 - _t116 - _t121 - _t90) + (-_t115 + _t117 + _t118 - _t122 - _t125)*(-_t126 - _t129 - _t132 - _t135 - _t79),
			(-_t107 - _t141 + _t145 - _t147)*(-_t149 - _t151 - _t153 - _t3) - (-_t11 - _t140 - _t143 - _t146)*(-_t126 - _t136 + _t137 - _t138),
			-(-_t154 - _t155 - _t156 - 0.9375*p0x[1])*(-_t157 + _t158 - _t160 - _t21) + (-_t154 + _t163 - _t165 - _t29)*(-_t157 - _t161 - _t162 - 0.9375*p0y[1]),
			-(-_t166 - _t167 - _t168 - 0.46875*p0x[1] - 0.46875*p1x[1])*(_t169 + _t170 - _t171 - _t173 - _t41) + (-_t166 + _t176 + _t177 - _t179 - _t56)*(-_t171 - _t174 - _t175 - 0.46875*p0y[1] - 0.46875*p1y[1]),
			-(-_t180 - _t181 - _t182 - 0.9375*p1x[1])*(-_t183 + _t184 - _t186 - _t68) + (-_t180 + _t189 - _t191 - _t75)*(-_t183 - _t187 - _t188 - 0.9375*p1y[1]),
			-(-_t192 + 3*p0x[3])*(-_t193 + 3*p0y[6]) + (-_t192 + 3*p0x[6])*(-_t193 + 3*p0y[3]),
			(-_t194 - _t198 - _t199)*(-_t197 + (1.5)*p0y[3] + (1.5)*p1y[3]) - (-_t194 + (1.5)*p0x[3] + (1.5)*p1x[3])*(-_t195 - _t196 - _t197),
			-(-_t200 + 3*p1x[3])*(-_t201 + 3*p1y[6]) + (-_t200 + 3*p1x[6])*(-_t201 + 3*p1y[3]),
			-(-_t14 - _t210 - _t211 + (1.6875)*p0x[1])*(_t207 + _t208 + _t24 + (0.9375)*p0y[7]) + (-_t18 - _t205 - _t206 + (1.6875)*p0y[1])*(_t15 + _t202 + _t203 + (0.9375)*p0x[7]),
			(-_t215 - _t219 - _t44 + (0.84375)*p0y[1] + (0.84375)*p1y[1])*(_t212 + _t213 + _t34 + (0.46875)*p0x[7] + (0.46875)*p1x[7]) - (-_t223 - _t227 - _t57 + (0.84375)*p0x[1] + (0.84375)*p1x[1])*(_t220 + _t221 + _t49 + (0.46875)*p0y[7] + (0.46875)*p1y[7]),
			(-_t230 - _t231 - _t65 + (1.6875)*p1y[1])*(_t222 + _t228 + _t63 + (0.9375)*p1x[7]) - (-_t234 - _t235 - _t62 + (1.6875)*p1x[1])*(_t214 + _t232 + _t71 + (0.9375)*p1y[7]),
			-(_t155 + _t17 + _t241 + _t246 + _t247 + _t93 + (0.375)*p0x[6])*(_t208 + _t245 + _t248 + _t249 + _t250 + _t251 + (0.375)*p0y[8]) + (_t161 + _t242 + _t243 + _t245 + _t26 + _t83 + (0.375)*p0y[6])*(_t203 + _t236 + _t237 + _t238 + _t239 + _t241 + (0.375)*p0x[8]),
			(_t110 + _t175 + _t251 + _t258 + _t259 + _t261 + _t50 + (0.09375)*p0y[8] + (0.09375)*p1y[8])*(_t212 + _t247 + _t252 + _t253 + _t254 + _t255 + _t257 + (0.09375)*p0x[6] + (0.09375)*p1x[6]) - (_t129 + _t168 + _t239 + _t257 + _t262 + _t263 + _t35 + (0.09375)*p0x[8] + (0.09375)*p1x[8])*(_t220 + _t243 + _t261 + _t264 + _t265 + _t266 + _t267 + (0.09375)*p0y[6] + (0.09375)*p1y[6]),
			(_t140 + _t187 + _t264 + _t273 + _t275 + _t72 + (0.375)*p1y[6])*(_t228 + _t262 + _t268 + _t269 + _t270 + _t272 + (0.375)*p1x[8]) - (_t149 + _t181 + _t252 + _t272 + _t276 + _t64 + (0.375)*p1x[6])*(_t232 + _t258 + _t275 + _t277 + _t278 + _t279 + (0.375)*p1y[8]),
			(-_t108 - _t205 - _t244 - _t25 - _t283 - _t91)*(-_t163 - _t246 - _t280 - _t282 - _t79 - _t97) - (-_t127 - _t16 - _t210 - _t240 - _t284 - _t81)*(-_t158 - _t242 - _t285 - _t287 - _t89 - _t90),
			-(-_t103 - _t163 - _t189 - _t227 - _t256 - _t292 - _t36)*(-_t121 - _t125 - _t169 - _t170 - _t259 - _t293 - _t295) + (-_t106 - _t135 - _t176 - _t177 - _t263 - _t288 - _t290)*(-_t122 - _t158 - _t184 - _t219 - _t260 - _t291 - _t51),
			-(-_t107 - _t146 - _t184 - _t273 - _t301 - _t303)*(-_t128 - _t138 - _t234 - _t271 - _t300 - _t52) + (-_t109 - _t147 - _t230 - _t274 - _t299 - _t37)*(-_t126 - _t153 - _t189 - _t276 - _t296 - _t298),
			-(-_t156 - _t164 - _t210 - _t304)*(-_t160 - _t204 - _t285 - _t305) + (-_t159 - _t162 - _t205 - _t307)*(-_t165 - _t209 - _t280 - _t306),
			-(-_t167 - _t178 - _t227 - _t309)*(-_t173 - _t218 - _t293 - _t311) + (-_t172 - _t174 - _t219 - _t313)*(-_t179 - _t226 - _t288 - _t312),
			-(-_t182 - _t190 - _t234 - _t314)*(-_t186 - _t229 - _t301 - _t315) + (-_t185 - _t188 - _t230 - _t317)*(-_t191 - _t233 - _t296 - _t316),
			-(-_t237 - _t323 - _t8 - _t95)*(_t320 - _t322 - _t82 - _t84) + (-_t249 - _t321 - _t5 - _t86)*(_t318 - _t319 - _t78 - _t92),
			(-_t102 + _t324 + _t325 - _t326 - _t327)*(-_t116 - _t139 - _t266 - _t331 - _t82) - (-_t115 + _t328 + _t329 - _t332 - _t333)*(-_t132 - _t148 - _t254 - _t335 - _t92),
			(-_t136 - _t148 + _t336 - _t337)*(-_t143 - _t278 - _t339 - _t6) - (-_t139 - _t141 + _t338 - _t340)*(-_t151 - _t269 - _t341 - _t9),
			(-_t104 - _t202 - _t240 - _t282 - _t31 - _t319)*(-_t250 - _t283 - _t321 - _t342 - _t343 - _t82) - (-_t123 - _t207 - _t23 - _t244 - _t287 - _t322)*(-_t238 - _t284 - _t323 - _t344 - _t345 - _t92),
			(-_t213 - _t256 - _t290 - _t326 - _t345 - _t346 - _t61)*(-_t267 - _t291 - _t331 - _t333 - _t347 - _t348 - _t349) - (-_t221 - _t260 - _t295 - _t332 - _t343 - _t353 - _t48)*(-_t255 - _t292 - _t327 - _t335 - _t350 - _t351 - _t352),
			(-_t105 - _t222 - _t271 - _t298 - _t337 - _t77)*(-_t139 - _t279 - _t299 - _t339 - _t353 - _t354) - (-_t124 - _t214 - _t274 - _t303 - _t340 - _t70)*(-_t148 - _t270 - _t300 - _t341 - _t346 - _t355),
			(-_t195 - _t321 - _t85 - _t88 - _t91)*(-_t318 - _t319 - _t357 - _t94 - _t97) - (-_t198 - _t323 - _t80 - _t81 - _t94)*(-_t320 - _t322 - _t356 - _t85 - _t89),
			-(-_t103 - _t133 - _t152 - _t335 - _t358 - _t96)*(-_t121 - _t286 - _t302 - _t330 - _t332 - _t359) + (-_t119 - _t122 - _t144 - _t331 - _t359 - _t87)*(-_t135 - _t281 - _t297 - _t326 - _t334 - _t358),
			-(-_t137 - _t138 - _t150 - _t199 - _t341)*(-_t142 - _t146 - _t338 - _t340 - _t360) + (-_t142 - _t145 - _t147 - _t196 - _t339)*(-_t150 - _t153 - _t336 - _t337 - _t361),
			-(-_t154 - _t211 + _t345 - _t367)*(-_t157 - _t248 - _t365 - 0.9375*p0y[4]) + (-_t154 - _t236 - _t362 - 0.9375*p0x[4])*(-_t157 - _t206 + _t343 - _t364),
			-(-_t166 - _t223 + _t350 + _t351 - _t373)*(-_t171 - _t265 - _t371 - 0.46875*p0y[4] - 0.46875*p1y[4]) + (-_t166 - _t253 - _t368 - 0.46875*p0x[4] - 0.46875*p1x[4])*(-_t171 - _t215 + _t347 + _t348 - _t370),
			-(-_t180 - _t235 + _t346 - _t379)*(-_t183 - _t277 - _t377 - 0.9375*p1y[4]) + (-_t180 - _t268 - _t374 - 0.9375*p1x[4])*(-_t183 - _t231 + _t353 - _t376),
			(-_t22 - _t307 - _t342 - _t364)*(-_t306 - _t31 - _t362 - _t366) - (-_t23 - _t305 - _t363 - _t365)*(-_t30 - _t304 - _t344 - _t367),
			-(-_t309 - _t352 - _t373 - _t60)*(-_t311 - _t369 - _t371 - _t48) + (-_t312 - _t368 - _t372 - _t61)*(-_t313 - _t349 - _t370 - _t47),
			-(-_t314 - _t355 - _t379 - _t76)*(-_t315 - _t375 - _t377 - _t70) + (-_t316 - _t374 - _t378 - _t77)*(-_t317 - _t354 - _t376 - _t69),
			-(-_t380 + 3*p0x[8])*(-_t381 + 3*p0y[9]) + (-_t380 + 3*p0x[9])*(-_t381 + 3*p0y[8]),
			(-_t356 - _t360 - _t383)*(-_t382 + (1.5)*p0x[9] + (1.5)*p1x[9]) - (-_t357 - _t361 - _t382)*(-_t383 + (1.5)*p0y[9] + (1.5)*p1y[9]),
			-(-_t384 + 3*p1x[8])*(-_t385 + 3*p1y[9]) + (-_t384 + 3*p1x[9])*(-_t385 + 3*p1y[8]),
		};
		#pragma endregion
	}
}
