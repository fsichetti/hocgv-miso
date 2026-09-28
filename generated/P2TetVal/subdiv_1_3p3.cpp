#include "../P2TetVal.hpp"
namespace miso {
	std::array<RealVector<20>, 20> P2TetVal::subdiv_1_3p3(const RealVector<20> &_b) {
		#pragma region Temporaries
		const Real _t0 = (0.25)*_b[1];
		const Real _t1 = (0.5)*_b[0];
		const Real _t2 = (0.25)*_b[10];
		const Real _t3 = _t1 + _t2;
		const Real _t4 = _t0 + _t3;
		const Real _t5 = (0.0625)*_b[16];
		const Real _t6 = _t2 + _t5;
		const Real _t7 = (0.25)*_b[0];
		const Real _t8 = (0.0625)*_b[2];
		const Real _t9 = _t7 + _t8;
		const Real _t10 = (0.125)*_b[11];
		const Real _t11 = _t0 + _t10;
		const Real _t12 = _t11 + _t6 + _t9;
		const Real _t13 = (0.1875)*_b[11];
		const Real _t14 = (0.015625)*_b[3];
		const Real _t15 = _t13 + _t14;
		const Real _t16 = (0.1875)*_b[1] + (0.09375)*_b[2];
		const Real _t17 = (0.125)*_b[0];
		const Real _t18 = (0.015625)*_b[19];
		const Real _t19 = (0.1875)*_b[10] + (0.09375)*_b[16] + _t18;
		const Real _t20 = _t17 + _t19;
		const Real _t21 = (0.046875)*_b[12] + (0.046875)*_b[17];
		const Real _t22 = _t15 + _t16 + _t20 + _t21;
		const Real _t23 = (0.25)*_b[4];
		const Real _t24 = _t23 + _t3;
		const Real _t25 = (0.125)*_b[4];
		const Real _t26 = (0.125)*_b[1];
		const Real _t27 = _t26 + _t7;
		const Real _t28 = (0.0625)*_b[5];
		const Real _t29 = (0.0625)*_b[11];
		const Real _t30 = (0.0625)*_b[13];
		const Real _t31 = _t29 + _t30;
		const Real _t32 = _t28 + _t31;
		const Real _t33 = _t27 + _t32;
		const Real _t34 = _t25 + _t33 + _t6;
		const Real _t35 = _t19 + _t28;
		const Real _t36 = (0.03125)*_b[17];
		const Real _t37 = (0.015625)*_b[18];
		const Real _t38 = _t36 + _t37;
		const Real _t39 = (0.03125)*_b[2];
		const Real _t40 = (0.015625)*_b[12];
		const Real _t41 = _t39 + _t40;
		const Real _t42 = (0.03125)*_b[14];
		const Real _t43 = (0.0625)*_b[4];
		const Real _t44 = _t17 + _t43;
		const Real _t45 = _t42 + _t44;
		const Real _t46 = (0.015625)*_b[6];
		const Real _t47 = _t30 + _t46;
		const Real _t48 = _t45 + _t47;
		const Real _t49 = _t10 + _t26 + _t35 + _t38 + _t41 + _t48;
		const Real _t50 = (0.125)*_b[13];
		const Real _t51 = _t50 + _t7;
		const Real _t52 = (0.0625)*_b[7];
		const Real _t53 = _t23 + _t52;
		const Real _t54 = _t51 + _t53 + _t6;
		const Real _t55 = (0.0625)*_b[1];
		const Real _t56 = _t17 + _t55;
		const Real _t57 = (0.03125)*_b[7];
		const Real _t58 = _t25 + _t57;
		const Real _t59 = (0.015625)*_b[15];
		const Real _t60 = _t42 + _t59;
		const Real _t61 = (0.03125)*_b[18];
		const Real _t62 = (0.015625)*_b[17];
		const Real _t63 = _t61 + _t62;
		const Real _t64 = (0.015625)*_b[8];
		const Real _t65 = _t29 + _t64;
		const Real _t66 = _t50 + _t65;
		const Real _t67 = _t35 + _t56 + _t58 + _t60 + _t63 + _t66;
		const Real _t68 = (0.1875)*_b[13];
		const Real _t69 = (0.015625)*_b[9];
		const Real _t70 = _t68 + _t69;
		const Real _t71 = (0.1875)*_b[4] + (0.09375)*_b[7];
		const Real _t72 = (0.046875)*_b[15] + (0.046875)*_b[18];
		const Real _t73 = _t20 + _t70 + _t71 + _t72;
		const Real _t74 = (0.5)*_b[10];
		const Real _t75 = (0.375)*_b[10];
		const Real _t76 = (0.125)*_b[16];
		const Real _t77 = _t10 + _t76;
		const Real _t78 = (0.0625)*_b[17];
		const Real _t79 = _t17 + _t2;
		const Real _t80 = _t26 + _t79;
		const Real _t81 = (0.03125)*_b[19];
		const Real _t82 = (0.15625)*_b[16] + _t81;
		const Real _t83 = (0.03125)*_b[12];
		const Real _t84 = _t39 + _t83;
		const Real _t85 = _t13 + _t84;
		const Real _t86 = _t25 + _t76;
		const Real _t87 = _t79 + _t82;
		const Real _t88 = (0.09375)*_b[13];
		const Real _t89 = _t42 + _t88;
		const Real _t90 = (0.03125)*_b[5];
		const Real _t91 = (0.09375)*_b[11];
		const Real _t92 = _t90 + _t91;
		const Real _t93 = _t61 + _t92;
		const Real _t94 = (0.0625)*_b[18];
		const Real _t95 = (0.03125)*_b[15];
		const Real _t96 = _t94 + _t95;
		const Real _t97 = (0.25)*_b[16];
		const Real _t98 = _t10 + _t97;
		const Real _t99 = _t55 + _t78;
		const Real _t100 = (0.0625)*_b[19];
		const Real _t101 = (0.3125)*_b[10] + _t100 + _t17;
		const Real _t102 = _t50 + _t97;
		const Real _t103 = _t43 + _t94;
		const Real _t104 = (0.375)*_b[16];
		const Real _t105 = (0.125)*_b[19];
		const Real _t106 = _t104 + _t105 + _t17 + _t75;
		const Real _t107 = _t0 + _t23;
		const Real _t108 = _t1 + _t107;
		const Real _t109 = (0.125)*_b[5];
		const Real _t110 = _t109 + _t52;
		const Real _t111 = _t107 + _t110 + _t9;
		const Real _t112 = (0.1875)*_b[5];
		const Real _t113 = _t112 + _t17;
		const Real _t114 = _t69 + _t71;
		const Real _t115 = _t14 + _t16;
		const Real _t116 = (0.046875)*_b[6] + (0.046875)*_b[8];
		const Real _t117 = _t113 + _t114 + _t115 + _t116;
		const Real _t118 = (0.5)*_b[4];
		const Real _t119 = (0.375)*_b[4];
		const Real _t120 = (0.125)*_b[7];
		const Real _t121 = _t119 + _t120;
		const Real _t122 = (0.0625)*_b[8];
		const Real _t123 = (0.03125)*_b[6];
		const Real _t124 = _t123 + _t39;
		const Real _t125 = (0.03125)*_b[9];
		const Real _t126 = (0.15625)*_b[7] + _t125 + _t23;
		const Real _t127 = (0.25)*_b[7];
		const Real _t128 = (0.3125)*_b[4];
		const Real _t129 = _t109 + _t127;
		const Real _t130 = (0.0625)*_b[9];
		const Real _t131 = _t122 + _t130;
		const Real _t132 = (0.375)*_b[7];
		const Real _t133 = (0.125)*_b[9];
		const Real _t134 = _t119 + _t132 + _t133 + _t17;
		const Real _t135 = (0.125)*_b[10];
		const Real _t136 = _t135 + _t33 + _t53;
		const Real _t137 = _t109 + _t26;
		const Real _t138 = (0.0625)*_b[10];
		const Real _t139 = _t138 + _t31 + _t60;
		const Real _t140 = (0.03125)*_b[8];
		const Real _t141 = _t140 + _t46;
		const Real _t142 = _t17 + _t41;
		const Real _t143 = _t114 + _t137 + _t139 + _t141 + _t142;
		const Real _t144 = (0.09375)*_b[5];
		const Real _t145 = _t138 + _t144;
		const Real _t146 = (0.03125)*_b[11];
		const Real _t147 = _t140 + _t146;
		const Real _t148 = _t127 + _t50;
		const Real _t149 = (0.0625)*_b[15];
		const Real _t150 = _t138 + _t149;
		const Real _t151 = (0.03125)*_b[16];
		const Real _t152 = _t135 + _t17;
		const Real _t153 = _t151 + _t152;
		const Real _t154 = _t28 + _t62;
		const Real _t155 = _t154 + _t37;
		const Real _t156 = _t114 + _t153 + _t155 + _t42 + _t55 + _t66 + _t95;
		const Real _t157 = _t149 + _t61;
		const Real _t158 = (0.5)*_b[1];
		const Real _t159 = (0.25)*_b[2];
		const Real _t160 = (0.375)*_b[1];
		const Real _t161 = (0.375)*_b[2];
		const Real _t162 = (0.125)*_b[3];
		const Real _t163 = _t160 + _t161 + _t162 + _t17;
		const Real _t164 = _t109 + _t25;
		const Real _t165 = (0.125)*_b[2];
		const Real _t166 = _t160 + _t165 + _t7;
		const Real _t167 = (0.3125)*_b[1];
		const Real _t168 = _t109 + _t159;
		const Real _t169 = (0.0625)*_b[6];
		const Real _t170 = (0.0625)*_b[3];
		const Real _t171 = _t169 + _t170;
		const Real _t172 = _t0 + _t169;
		const Real _t173 = (0.03125)*_b[3];
		const Real _t174 = (0.15625)*_b[2] + _t173;
		const Real _t175 = _t10 + _t135;
		const Real _t176 = (0.0625)*_b[12];
		const Real _t177 = _t138 + _t176;
		const Real _t178 = _t10 + _t159;
		const Real _t179 = _t135 + _t25;
		const Real _t180 = _t0 + _t179 + _t32 + _t9;
		const Real _t181 = _t0 + _t174;
		const Real _t182 = _t123 + _t83;
		const Real _t183 = (0.03125)*_b[13];
		const Real _t184 = _t183 + _t91;
		const Real _t185 = _t164 + _t17;
		const Real _t186 = _t123 + _t64;
		const Real _t187 = _t115 + _t139 + _t185 + _t186 + _t40 + _t57;
		const Real _t188 = _t176 + _t36;
		const Real _t189 = _t115 + _t151 + _t155 + _t175 + _t48 + _t83;
		const Real _t190 = _t135 + _t26;
		const Real _t191 = _t151 + _t62;
		const Real _t192 = _t46 + _t64;
		const Real _t193 = (0.25)*_b[17];
		const Real _t194 = (0.5)*_b[19];
		const Real _t195 = _t194 + _t97;
		const Real _t196 = _t193 + _t195;
		const Real _t197 = (0.25)*_b[19];
		const Real _t198 = _t177 + _t193 + _t197 + _t98;
		const Real _t199 = (0.09375)*_b[12] + (0.1875)*_b[17];
		const Real _t200 = _t105 + _t199;
		const Real _t201 = (0.015625)*_b[0];
		const Real _t202 = (0.046875)*_b[1] + (0.046875)*_b[2] + _t201;
		const Real _t203 = (0.09375)*_b[10] + (0.1875)*_b[16];
		const Real _t204 = _t15 + _t200 + _t202 + _t203;
		const Real _t205 = (0.25)*_b[18];
		const Real _t206 = _t195 + _t205;
		const Real _t207 = _t138 + _t197;
		const Real _t208 = (0.125)*_b[17];
		const Real _t209 = _t208 + _t97;
		const Real _t210 = (0.125)*_b[18];
		const Real _t211 = (0.0625)*_b[14];
		const Real _t212 = _t211 + _t31;
		const Real _t213 = _t210 + _t212;
		const Real _t214 = _t207 + _t209 + _t213;
		const Real _t215 = _t10 + _t105;
		const Real _t216 = _t201 + _t203;
		const Real _t217 = (0.015625)*_b[2];
		const Real _t218 = _t217 + _t83;
		const Real _t219 = (0.03125)*_b[1];
		const Real _t220 = (0.015625)*_b[4];
		const Real _t221 = _t219 + _t220;
		const Real _t222 = _t211 + _t90;
		const Real _t223 = _t222 + _t47 + _t94;
		const Real _t224 = _t208 + _t215 + _t216 + _t218 + _t221 + _t223;
		const Real _t225 = _t149 + _t205;
		const Real _t226 = _t102 + _t207 + _t225;
		const Real _t227 = _t210 + _t50;
		const Real _t228 = _t105 + _t216;
		const Real _t229 = (0.03125)*_b[4];
		const Real _t230 = _t229 + _t78;
		const Real _t231 = (0.015625)*_b[1];
		const Real _t232 = _t222 + _t231 + _t65;
		const Real _t233 = (0.015625)*_b[7];
		const Real _t234 = _t233 + _t95;
		const Real _t235 = _t227 + _t228 + _t230 + _t232 + _t234;
		const Real _t236 = (0.09375)*_b[15] + (0.1875)*_b[18];
		const Real _t237 = (0.046875)*_b[4] + (0.046875)*_b[7];
		const Real _t238 = _t228 + _t236 + _t237 + _t70;
		const Real _t239 = (0.5)*_b[16];
		const Real _t240 = _t104 + _t197;
		const Real _t241 = (0.03125)*_b[0];
		const Real _t242 = (0.15625)*_b[10] + _t241;
		const Real _t243 = _t135 + _t227;
		const Real _t244 = _t105 + _t97;
		const Real _t245 = _t242 + _t244;
		const Real _t246 = _t92 + _t94;
		const Real _t247 = _t219 + _t89;
		const Real _t248 = _t210 + _t95;
		const Real _t249 = _t43 + _t57;
		const Real _t250 = (0.0625)*_b[0];
		const Real _t251 = (0.3125)*_b[16] + _t2 + _t250;
		const Real _t252 = _t105 + _t50;
		const Real _t253 = _t193 + _t205;
		const Real _t254 = _t194 + _t253;
		const Real _t255 = (0.125)*_b[14];
		const Real _t256 = _t197 + _t255;
		const Real _t257 = _t149 + _t176;
		const Real _t258 = _t253 + _t256 + _t257;
		const Real _t259 = (0.1875)*_b[14];
		const Real _t260 = _t14 + _t259;
		const Real _t261 = _t236 + _t69;
		const Real _t262 = _t116 + _t200 + _t260 + _t261;
		const Real _t263 = (0.5)*_b[18];
		const Real _t264 = (0.375)*_b[18];
		const Real _t265 = (0.125)*_b[15];
		const Real _t266 = _t208 + _t265;
		const Real _t267 = _t125 + _t259;
		const Real _t268 = _t105 + _t205;
		const Real _t269 = (0.15625)*_b[15] + _t268;
		const Real _t270 = (0.25)*_b[15];
		const Real _t271 = _t255 + _t78;
		const Real _t272 = (0.3125)*_b[18] + _t270;
		const Real _t273 = (0.375)*_b[15];
		const Real _t274 = _t105 + _t133 + _t264 + _t273;
		const Real _t275 = _t197 + _t76;
		const Real _t276 = _t208 + _t212 + _t225 + _t275;
		const Real _t277 = _t105 + _t255;
		const Real _t278 = _t208 + _t277;
		const Real _t279 = _t233 + _t31 + _t5 + _t90;
		const Real _t280 = _t141 + _t218 + _t261 + _t278 + _t279;
		const Real _t281 = _t265 + _t50;
		const Real _t282 = _t125 + _t269;
		const Real _t283 = (0.09375)*_b[14];
		const Real _t284 = _t283 + _t5;
		const Real _t285 = _t88 + _t90;
		const Real _t286 = _t57 + _t78;
		const Real _t287 = _t5 + _t52;
		const Real _t288 = (0.03125)*_b[10];
		const Real _t289 = _t288 + _t76;
		const Real _t290 = _t220 + _t289;
		const Real _t291 = _t232 + _t252 + _t261 + _t286 + _t290;
		const Real _t292 = _t229 + _t68;
		const Real _t293 = (0.5)*_b[17];
		const Real _t294 = (0.25)*_b[12];
		const Real _t295 = (0.375)*_b[12];
		const Real _t296 = (0.375)*_b[17];
		const Real _t297 = _t105 + _t162 + _t295 + _t296;
		const Real _t298 = (0.125)*_b[12];
		const Real _t299 = _t296 + _t298;
		const Real _t300 = _t255 + _t94;
		const Real _t301 = (0.3125)*_b[17] + _t294;
		const Real _t302 = _t169 + _t193;
		const Real _t303 = _t173 + _t259;
		const Real _t304 = (0.15625)*_b[12] + _t105;
		const Real _t305 = _t170 + _t8;
		const Real _t306 = _t176 + _t193 + _t213 + _t275;
		const Real _t307 = _t173 + _t183;
		const Real _t308 = _t14 + _t186 + _t199 + _t217 + _t248 + _t277 + _t279;
		const Real _t309 = _t193 + _t8;
		const Real _t310 = _t173 + _t219;
		const Real _t311 = _t231 + _t288;
		const Real _t312 = _t14 + _t200 + _t220 + _t223 + _t311 + _t39 + _t77;
		const Real _t313 = _t208 + _t210;
		const Real _t314 = _t283 + _t88;
		const Real _t315 = (0.25)*_b[8];
		const Real _t316 = (0.5)*_b[9];
		const Real _t317 = _t127 + _t316;
		const Real _t318 = _t315 + _t317;
		const Real _t319 = (0.25)*_b[9];
		const Real _t320 = _t169 + _t319;
		const Real _t321 = _t129 + _t315 + _t320 + _t43;
		const Real _t322 = (0.09375)*_b[4] + (0.1875)*_b[7];
		const Real _t323 = _t133 + _t322;
		const Real _t324 = (0.09375)*_b[6] + (0.1875)*_b[8];
		const Real _t325 = _t14 + _t324;
		const Real _t326 = _t112 + _t202 + _t323 + _t325;
		const Real _t327 = _t270 + _t317;
		const Real _t328 = _t265 + _t319;
		const Real _t329 = _t211 + _t28;
		const Real _t330 = (0.125)*_b[8];
		const Real _t331 = _t30 + _t330;
		const Real _t332 = _t329 + _t331;
		const Real _t333 = _t127 + _t328 + _t332 + _t43;
		const Real _t334 = _t109 + _t133;
		const Real _t335 = _t201 + _t322;
		const Real _t336 = _t123 + _t217 + _t40;
		const Real _t337 = (0.015625)*_b[10];
		const Real _t338 = _t146 + _t337;
		const Real _t339 = _t149 + _t211 + _t338;
		const Real _t340 = _t219 + _t331 + _t334 + _t335 + _t336 + _t339;
		const Real _t341 = _t103 + _t148 + _t270 + _t319;
		const Real _t342 = _t122 + _t133;
		const Real _t343 = (0.015625)*_b[16];
		const Real _t344 = _t146 + _t343;
		const Real _t345 = _t281 + _t311 + _t329 + _t335 + _t342 + _t344 + _t63;
		const Real _t346 = (0.1875)*_b[15] + (0.09375)*_b[18] + _t18;
		const Real _t347 = (0.046875)*_b[10] + (0.046875)*_b[16] + _t201;
		const Real _t348 = _t323 + _t346 + _t347 + _t68;
		const Real _t349 = (0.5)*_b[7];
		const Real _t350 = _t132 + _t319;
		const Real _t351 = _t112 + _t241;
		const Real _t352 = _t127 + _t133;
		const Real _t353 = (0.15625)*_b[4] + _t352;
		const Real _t354 = _t241 + _t353;
		const Real _t355 = _t122 + _t146;
		const Real _t356 = _t144 + _t288;
		const Real _t357 = _t265 + _t61;
		const Real _t358 = _t138 + _t151;
		const Real _t359 = _t109 + _t250;
		const Real _t360 = (0.3125)*_b[7] + _t23;
		const Real _t361 = _t133 + _t50;
		const Real _t362 = _t270 + _t315;
		const Real _t363 = _t316 + _t362;
		const Real _t364 = _t300 + _t320 + _t362;
		const Real _t365 = _t133 + _t346;
		const Real _t366 = _t21 + _t260 + _t324 + _t365;
		const Real _t367 = (0.5)*_b[15];
		const Real _t368 = _t273 + _t319;
		const Real _t369 = _t255 + _t330;
		const Real _t370 = _t259 + _t81;
		const Real _t371 = _t133 + _t270;
		const Real _t372 = (0.15625)*_b[18] + _t371;
		const Real _t373 = (0.3125)*_b[15] + _t100 + _t205;
		const Real _t374 = _t120 + _t319;
		const Real _t375 = _t270 + _t332 + _t374 + _t94;
		const Real _t376 = _t30 + _t344 + _t52;
		const Real _t377 = _t28 + _t336 + _t36 + _t365 + _t369 + _t376;
		const Real _t378 = _t372 + _t81;
		const Real _t379 = _t283 + _t52;
		const Real _t380 = _t120 + _t329;
		const Real _t381 = _t229 + _t231;
		const Real _t382 = _t191 + _t338 + _t342 + _t346 + _t380 + _t381 + _t50;
		const Real _t383 = _t288 + _t5;
		const Real _t384 = (0.5)*_b[8];
		const Real _t385 = (0.25)*_b[6];
		const Real _t386 = (0.375)*_b[6];
		const Real _t387 = (0.375)*_b[8];
		const Real _t388 = _t133 + _t162 + _t386 + _t387;
		const Real _t389 = (0.125)*_b[6];
		const Real _t390 = _t255 + _t389;
		const Real _t391 = _t255 + _t257;
		const Real _t392 = (0.3125)*_b[8] + _t133 + _t385;
		const Real _t393 = _t133 + _t315;
		const Real _t394 = (0.15625)*_b[6] + _t393;
		const Real _t395 = _t109 + _t389;
		const Real _t396 = _t169 + _t30 + _t315 + _t328 + _t380;
		const Real _t397 = _t144 + _t146;
		const Real _t398 = _t133 + _t154 + _t218 + _t255 + _t325 + _t357 + _t376;
		const Real _t399 = _t112 + _t229;
		const Real _t400 = _t120 + _t334;
		const Real _t401 = _t30 + _t325 + _t339 + _t381 + _t400 + _t41;
		const Real _t402 = _t120 + _t265;
		const Real _t403 = (0.5)*_b[3];
		const Real _t404 = _t159 + _t403;
		const Real _t405 = _t385 + _t404;
		const Real _t406 = (0.25)*_b[3];
		const Real _t407 = _t122 + _t406;
		const Real _t408 = _t385 + _t407;
		const Real _t409 = _t168 + _t408 + _t55;
		const Real _t410 = (0.1875)*_b[6] + (0.09375)*_b[8] + _t69;
		const Real _t411 = (0.1875)*_b[2];
		const Real _t412 = (0.09375)*_b[1];
		const Real _t413 = _t162 + _t411 + _t412;
		const Real _t414 = _t201 + _t413;
		const Real _t415 = _t112 + _t237 + _t410 + _t414;
		const Real _t416 = _t294 + _t404;
		const Real _t417 = _t29 + _t329;
		const Real _t418 = _t298 + _t417;
		const Real _t419 = _t159 + _t389 + _t406 + _t418 + _t55;
		const Real _t420 = _t176 + _t229;
		const Real _t421 = _t140 + _t337 + _t59;
		const Real _t422 = _t233 + _t29;
		const Real _t423 = _t183 + _t422;
		const Real _t424 = _t211 + _t395 + _t414 + _t420 + _t421 + _t423;
		const Real _t425 = _t294 + _t406;
		const Real _t426 = _t178 + _t425 + _t99;
		const Real _t427 = _t10 + _t298;
		const Real _t428 = _t162 + _t427;
		const Real _t429 = _t169 + _t183;
		const Real _t430 = _t201 + _t220 + _t288 + _t329 + _t343 + _t38 + _t411 + _t412 + _t428 + _t429;
		const Real _t431 = (0.1875)*_b[12] + (0.09375)*_b[17] + _t18;
		const Real _t432 = _t13 + _t347 + _t413 + _t431;
		const Real _t433 = (0.5)*_b[2];
		const Real _t434 = _t161 + _t26 + _t406;
		const Real _t435 = _t159 + _t162;
		const Real _t436 = (0.15625)*_b[1] + _t435;
		const Real _t437 = _t140 + _t389;
		const Real _t438 = _t241 + _t436;
		const Real _t439 = _t298 + _t36;
		const Real _t440 = (0.3125)*_b[2] + _t162;
		const Real _t441 = _t294 + _t385;
		const Real _t442 = _t403 + _t441;
		const Real _t443 = _t271 + _t407 + _t441;
		const Real _t444 = _t162 + _t431;
		const Real _t445 = _t259 + _t410 + _t444 + _t72;
		const Real _t446 = (0.5)*_b[12];
		const Real _t447 = _t208 + _t295 + _t406;
		const Real _t448 = _t162 + _t294;
		const Real _t449 = (0.15625)*_b[17] + _t448;
		const Real _t450 = (0.3125)*_b[12] + _t100 + _t162;
		const Real _t451 = _t165 + _t389;
		const Real _t452 = _t417 + _t425 + _t451 + _t78;
		const Real _t453 = _t28 + _t343 + _t8;
		const Real _t454 = _t140 + _t390 + _t423 + _t444 + _t453 + _t59 + _t61;
		const Real _t455 = _t10 + _t165;
		const Real _t456 = _t449 + _t81;
		const Real _t457 = _t283 + _t8;
		const Real _t458 = _t151 + _t429;
		const Real _t459 = _t221 + _t37;
		const Real _t460 = _t329 + _t337 + _t444 + _t455 + _t458 + _t459;
		const Real _t461 = _t165 + _t219;
		const Real _t462 = (0.5)*_b[6];
		const Real _t463 = _t386 + _t406;
		const Real _t464 = (0.3125)*_b[6] + _t130 + _t162 + _t315;
		const Real _t465 = _t162 + _t385;
		const Real _t466 = (0.15625)*_b[8] + _t465;
		const Real _t467 = _t165 + _t330;
		const Real _t468 = _t165 + _t408 + _t418;
		const Real _t469 = _t125 + _t466;
		const Real _t470 = _t183 + _t95;
		const Real _t471 = _t176 + _t57;
		const Real _t472 = _t162 + _t410;
		const Real _t473 = _t255 + _t37 + _t422 + _t439 + _t453 + _t470 + _t472;
		const Real _t474 = _t109 + _t183 + _t211 + _t220 + _t29 + _t337 + _t461 + _t471 + _t472 + _t59;
		const Real _t475 = (0.25)*_b[11];
		const Real _t476 = _t105 + _t475;
		const Real _t477 = _t190 + _t209 + _t476;
		const Real _t478 = _t165 + _t76;
		const Real _t479 = _t193 + _t298;
		const Real _t480 = _t476 + _t478 + _t479;
		const Real _t481 = _t208 + _t475;
		const Real _t482 = _t478 + _t481;
		const Real _t483 = _t448 + _t482;
		const Real _t484 = _t298 + _t475;
		const Real _t485 = _t0 + _t165;
		const Real _t486 = _t190 + _t435 + _t484;
		const Real _t487 = (0.25)*_b[13];
		const Real _t488 = _t210 + _t487;
		const Real _t489 = _t488 + _t86;
		const Real _t490 = _t489 + _t79;
		const Real _t491 = _t255 + _t26;
		const Real _t492 = _t109 + _t77;
		const Real _t493 = _t243 + _t491 + _t492;
		const Real _t494 = (0.25)*_b[14];
		const Real _t495 = _t389 + _t494;
		const Real _t496 = _t210 + _t495;
		const Real _t497 = _t475 + _t478 + _t496;
		const Real _t498 = _t175 + _t50;
		const Real _t499 = _t165 + _t390;
		const Real _t500 = _t137 + _t498 + _t499;
		const Real _t501 = (0.25)*_b[5];
		const Real _t502 = _t17 + _t501;
		const Real _t503 = _t25 + _t389;
		const Real _t504 = _t485 + _t502 + _t503;
		const Real _t505 = _t265 + _t487;
		const Real _t506 = _t120 + _t23;
		const Real _t507 = _t152 + _t505 + _t506;
		const Real _t508 = _t330 + _t501;
		const Real _t509 = _t190 + _t505 + _t508;
		const Real _t510 = _t26 + _t330 + _t502 + _t506;
		const Real _t511 = _t227 + _t492;
		const Real _t512 = _t105 + _t479 + _t496;
		const Real _t513 = _t120 + _t76;
		const Real _t514 = _t330 + _t494;
		const Real _t515 = _t266 + _t268 + _t514;
		const Real _t516 = _t265 + _t369 + _t511;
		const Real _t517 = _t371 + _t488 + _t513;
		const Real _t518 = _t179 + _t352 + _t505;
		const Real _t519 = _t25 + _t26 + _t352 + _t508;
		const Real _t520 = _t120 + _t501;
		const Real _t521 = _t393 + _t451 + _t520;
		const Real _t522 = _t281 + _t369;
		const Real _t523 = _t395 + _t455 + _t522;
		const Real _t524 = _t265 + _t298;
		const Real _t525 = _t465 + _t514 + _t524;
		const Real _t526 = _t208 + _t448 + _t496;
		const Real _t527 = _t467 + _t520;
		const Real _t528 = _t26 + _t503;
		#pragma endregion
		#pragma region Expressions
		return {{
			{
				_b[0],
				_t4,
				_t12,
				_t22,
				_t24,
				_t34,
				_t49,
				_t54,
				_t67,
				_t73,
				_t1 + _t74,
				_t27 + _t75 + _t77,
				_t78 + _t80 + _t82 + _t85,
				_t51 + _t75 + _t86,
				_t36 + _t43 + _t55 + _t87 + _t89 + _t93,
				_t58 + _t68 + _t87 + _t96,
				_t7 + _t74 + _t97,
				_t101 + _t98 + _t99,
				_t101 + _t102 + _t103,
				_t106,
			},
			{
				_b[0],
				_t108,
				_t111,
				_t117,
				_t1 + _t118,
				_t109 + _t121 + _t27,
				_t113 + _t122 + _t124 + _t126 + _t26,
				_t118 + _t127 + _t7,
				_t128 + _t129 + _t131 + _t56,
				_t134,
				_t24,
				_t136,
				_t143,
				_t121 + _t135 + _t51,
				_t126 + _t145 + _t147 + _t56 + _t89 + _t95,
				_t128 + _t130 + _t148 + _t150 + _t17,
				_t54,
				_t156,
				_t126 + _t153 + _t157 + _t68,
				_t73,
			},
			{
				_b[0],
				_t1 + _t158,
				_t158 + _t159 + _t7,
				_t163,
				_t108,
				_t164 + _t166,
				_t167 + _t168 + _t171 + _t44,
				_t111,
				_t113 + _t140 + _t172 + _t174 + _t58,
				_t117,
				_t4,
				_t166 + _t175,
				_t167 + _t17 + _t170 + _t177 + _t178,
				_t180,
				_t145 + _t181 + _t182 + _t184 + _t45,
				_t187,
				_t12,
				_t13 + _t153 + _t181 + _t188,
				_t189,
				_t22,
			},
			{
				_b[0],
				_t24,
				_t54,
				_t73,
				_t4,
				_t34,
				_t67,
				_t12,
				_t49,
				_t22,
				_t108,
				_t136,
				_t156,
				_t180,
				_t142 + _t144 + _t190 + _t191 + _t192 + _t37 + _t58 + _t59 + _t89 + _t91,
				_t189,
				_t111,
				_t143,
				_t187,
				_t117,
			},
			{
				_b[19],
				_t196,
				_t198,
				_t204,
				_t206,
				_t214,
				_t224,
				_t226,
				_t235,
				_t238,
				_t194 + _t239,
				_t175 + _t208 + _t240,
				_t105 + _t209 + _t242 + _t55 + _t85,
				_t240 + _t243,
				_t230 + _t245 + _t246 + _t247,
				_t245 + _t248 + _t249 + _t68,
				_t197 + _t2 + _t239,
				_t215 + _t251 + _t99,
				_t103 + _t251 + _t252,
				_t106,
			},
			{
				_b[19],
				_t254,
				_t258,
				_t262,
				_t194 + _t263,
				_t256 + _t264 + _t266,
				_t122 + _t182 + _t208 + _t267 + _t269,
				_t197 + _t263 + _t270,
				_t105 + _t131 + _t271 + _t272,
				_t274,
				_t206,
				_t276,
				_t280,
				_t264 + _t275 + _t281,
				_t147 + _t282 + _t284 + _t285 + _t286,
				_t130 + _t252 + _t272 + _t287,
				_t226,
				_t291,
				_t282 + _t289 + _t292 + _t52,
				_t238,
			},
			{
				_b[19],
				_t194 + _t293,
				_t197 + _t293 + _t294,
				_t297,
				_t254,
				_t210 + _t256 + _t299,
				_t105 + _t171 + _t300 + _t301,
				_t258,
				_t140 + _t248 + _t302 + _t303 + _t304,
				_t262,
				_t196,
				_t197 + _t299 + _t77,
				_t215 + _t301 + _t305 + _t5,
				_t306,
				_t124 + _t193 + _t246 + _t284 + _t304 + _t307,
				_t308,
				_t198,
				_t13 + _t289 + _t304 + _t309 + _t310,
				_t312,
				_t204,
			},
			{
				_b[19],
				_t206,
				_t226,
				_t238,
				_t196,
				_t214,
				_t235,
				_t198,
				_t224,
				_t204,
				_t254,
				_t276,
				_t291,
				_t306,
				_t105 + _t192 + _t218 + _t231 + _t234 + _t290 + _t313 + _t314 + _t92,
				_t312,
				_t258,
				_t280,
				_t308,
				_t262,
			},
			{
				_b[9],
				_t318,
				_t321,
				_t326,
				_t327,
				_t333,
				_t340,
				_t341,
				_t345,
				_t348,
				_t316 + _t349,
				_t164 + _t330 + _t350,
				_t124 + _t330 + _t351 + _t353 + _t55,
				_t25 + _t281 + _t350,
				_t149 + _t247 + _t354 + _t355 + _t356,
				_t354 + _t357 + _t358 + _t68,
				_t23 + _t319 + _t349,
				_t342 + _t359 + _t360 + _t55,
				_t150 + _t250 + _t360 + _t361,
				_t134,
			},
			{
				_b[9],
				_t363,
				_t364,
				_t366,
				_t316 + _t367,
				_t210 + _t368 + _t369,
				_t182 + _t330 + _t370 + _t372 + _t78,
				_t205 + _t319 + _t367,
				_t271 + _t342 + _t373,
				_t274,
				_t327,
				_t375,
				_t377,
				_t120 + _t227 + _t368,
				_t151 + _t285 + _t355 + _t36 + _t378 + _t379,
				_t287 + _t361 + _t373,
				_t341,
				_t382,
				_t120 + _t292 + _t378 + _t383,
				_t348,
			},
			{
				_b[9],
				_t316 + _t384,
				_t319 + _t384 + _t385,
				_t388,
				_t363,
				_t328 + _t387 + _t390,
				_t170 + _t391 + _t392,
				_t364,
				_t188 + _t303 + _t357 + _t394,
				_t366,
				_t318,
				_t374 + _t387 + _t395,
				_t110 + _t305 + _t392,
				_t396,
				_t149 + _t307 + _t379 + _t394 + _t397 + _t84,
				_t398,
				_t321,
				_t120 + _t310 + _t394 + _t399 + _t8,
				_t401,
				_t326,
			},
			{
				_b[9],
				_t327,
				_t341,
				_t348,
				_t318,
				_t333,
				_t345,
				_t321,
				_t340,
				_t326,
				_t363,
				_t375,
				_t382,
				_t396,
				_t133 + _t314 + _t330 + _t336 + _t337 + _t343 + _t381 + _t397 + _t402 + _t63,
				_t401,
				_t364,
				_t377,
				_t398,
				_t366,
			},
			{
				_b[3],
				_t405,
				_t409,
				_t415,
				_t416,
				_t419,
				_t424,
				_t426,
				_t430,
				_t432,
				_t403 + _t433,
				_t395 + _t434,
				_t249 + _t351 + _t436 + _t437,
				_t427 + _t434,
				_t169 + _t184 + _t356 + _t42 + _t420 + _t438,
				_t13 + _t358 + _t438 + _t439,
				_t0 + _t406 + _t433,
				_t172 + _t359 + _t43 + _t440,
				_t11 + _t177 + _t250 + _t440,
				_t163,
			},
			{
				_b[3],
				_t442,
				_t443,
				_t445,
				_t403 + _t446,
				_t390 + _t447,
				_t370 + _t437 + _t449 + _t96,
				_t193 + _t406 + _t446,
				_t300 + _t302 + _t450,
				_t297,
				_t416,
				_t452,
				_t454,
				_t447 + _t455,
				_t456 + _t457 + _t458 + _t93,
				_t10 + _t309 + _t450 + _t5,
				_t426,
				_t460,
				_t13 + _t383 + _t456 + _t461,
				_t432,
			},
			{
				_b[3],
				_t403 + _t462,
				_t315 + _t406 + _t462,
				_t388,
				_t442,
				_t298 + _t369 + _t463,
				_t391 + _t464,
				_t443,
				_t157 + _t267 + _t439 + _t466,
				_t445,
				_t405,
				_t109 + _t463 + _t467,
				_t110 + _t464 + _t8,
				_t468,
				_t397 + _t457 + _t469 + _t470 + _t471,
				_t473,
				_t409,
				_t399 + _t461 + _t469 + _t52,
				_t474,
				_t415,
			},
			{
				_b[3],
				_t416,
				_t426,
				_t432,
				_t405,
				_t419,
				_t430,
				_t409,
				_t424,
				_t415,
				_t442,
				_t452,
				_t460,
				_t468,
				_t144 + _t162 + _t184 + _t233 + _t283 + _t343 + _t421 + _t439 + _t451 + _t459,
				_t474,
				_t443,
				_t454,
				_t473,
				_t445,
			},
			{
				_t106,
				_t477,
				_t480,
				_t297,
				_t481 + _t76 + _t80,
				_t190 + _t298 + _t482,
				_t483,
				_t152 + _t484 + _t485,
				_t486,
				_t163,
				_t490,
				_t493,
				_t497,
				_t185 + _t491 + _t498,
				_t500,
				_t504,
				_t507,
				_t509,
				_t510,
				_t134,
			},
			{
				_t106,
				_t477,
				_t480,
				_t297,
				_t179 + _t244 + _t488,
				_t278 + _t511,
				_t512,
				_t268 + _t505 + _t513,
				_t515,
				_t274,
				_t490,
				_t493,
				_t497,
				_t135 + _t402 + _t489,
				_t516,
				_t517,
				_t507,
				_t509,
				_t518,
				_t134,
			},
			{
				_t134,
				_t519,
				_t521,
				_t388,
				_t509,
				_t523,
				_t525,
				_t497,
				_t526,
				_t297,
				_t510,
				_t527 + _t528,
				_t465 + _t527,
				_t500,
				_t109 + _t428 + _t499 + _t50,
				_t483,
				_t504,
				_t435 + _t501 + _t528,
				_t486,
				_t163,
			},
			{
				_t134,
				_t519,
				_t521,
				_t388,
				_t509,
				_t523,
				_t525,
				_t497,
				_t526,
				_t297,
				_t518,
				_t10 + _t400 + _t522,
				_t393 + _t495 + _t524,
				_t516,
				_t266 + _t298 + _t330 + _t496,
				_t512,
				_t517,
				_t313 + _t371 + _t514,
				_t515,
				_t274,
			},
		}};
		#pragma endregion
	}
}
