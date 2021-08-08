// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

#include "sink_vqm.h"
#include "nvqm.h"

#define FUNCS(P0, P1, P2, P3, P4, P5, P6, P7)                                                  \
	P2("vec2.add"           , vec2  , vec2_add           , vec2, vec2                        ) \
	P2("vec2.applymat2"     , vec2  , vec2_applymat2     , vec2, mat2                        ) \
	P2("vec2.applymat3"     , vec2  , vec2_applymat3     , vec2, mat3                        ) \
	P2("vec2.applymat4"     , vec2  , vec2_applymat4     , vec2, mat4                        ) \
	P3("vec2.clamp"         , vec2  , vec2_clamp         , vec2, vec2, vec2                  ) \
	P2("vec2.cross"         , num   , vec2_cross         , vec2, vec2                        ) \
	P2("vec2.dist"          , num   , vec2_dist          , vec2, vec2                        ) \
	P2("vec2.dist2"         , num   , vec2_dist2         , vec2, vec2                        ) \
	P2("vec2.div"           , vec2  , vec2_div           , vec2, vec2                        ) \
	P2("vec2.dot"           , num   , vec2_dot           , vec2, vec2                        ) \
	P1("vec2.inverse"       , vec2  , vec2_inverse       , vec2                              ) \
	P1("vec2.len"           , num   , vec2_len           , vec2                              ) \
	P1("vec2.len2"          , num   , vec2_len2          , vec2                              ) \
	P3("vec2.lerp"          , vec2  , vec2_lerp          , vec2, vec2, num                   ) \
	P2("vec2.max"           , vec2  , vec2_max           , vec2, vec2                        ) \
	P2("vec2.min"           , vec2  , vec2_min           , vec2, vec2                        ) \
	P2("vec2.mul"           , vec2  , vec2_mul           , vec2, vec2                        ) \
	P1("vec2.neg"           , vec2  , vec2_neg           , vec2                              ) \
	P1("vec2.normal"        , vec2  , vec2_normal        , vec2                              ) \
	P2("vec2.scale"         , vec2  , vec2_scale         , vec2, num                         ) \
	P2("vec2.sub"           , vec2  , vec2_sub           , vec2, vec2                        ) \
	P2("vec3.add"           , vec3  , vec3_add           , vec3, vec3                        ) \
	P2("vec3.angle"         , num   , vec3_angle         , vec3, vec3                        ) \
	P2("vec3.applymat3"     , vec3  , vec3_applymat3     , vec3, mat3                        ) \
	P2("vec3.applymat4"     , vec3  , vec3_applymat4     , vec3, mat4                        ) \
	P2("vec3.applyquat"     , vec3  , vec3_applyquat     , vec3, quat                        ) \
	P3("vec3.clamp"         , vec3  , vec3_clamp         , vec3, vec3, vec3                  ) \
	P2("vec3.cross"         , vec3  , vec3_cross         , vec3, vec3                        ) \
	P2("vec3.dist"          , num   , vec3_dist          , vec3, vec3                        ) \
	P2("vec3.dist2"         , num   , vec3_dist2         , vec3, vec3                        ) \
	P2("vec3.div"           , vec3  , vec3_div           , vec3, vec3                        ) \
	P2("vec3.dot"           , num   , vec3_dot           , vec3, vec3                        ) \
	P1("vec3.inverse"       , vec3  , vec3_inverse       , vec3                              ) \
	P1("vec3.len"           , num   , vec3_len           , vec3                              ) \
	P1("vec3.len2"          , num   , vec3_len2          , vec3                              ) \
	P3("vec3.lerp"          , vec3  , vec3_lerp          , vec3, vec3, num                   ) \
	P2("vec3.max"           , vec3  , vec3_max           , vec3, vec3                        ) \
	P2("vec3.min"           , vec3  , vec3_min           , vec3, vec3                        ) \
	P2("vec3.mul"           , vec3  , vec3_mul           , vec3, vec3                        ) \
	P2("vec3.nangle"        , num   , vec3_nangle        , vec3, vec3                        ) \
	P1("vec3.neg"           , vec3  , vec3_neg           , vec3                              ) \
	P1("vec3.normal"        , vec3  , vec3_normal        , vec3                              ) \
	P2("vec3.orthogonal"    , vec3  , vec3_orthogonal    , vec3, vec3                        ) \
	P2("vec3.scale"         , vec3  , vec3_scale         , vec3, num                         ) \
	P2("vec3.sub"           , vec3  , vec3_sub           , vec3, vec3                        ) \
	P2("vec4.add"           , vec4  , vec4_add           , vec4, vec4                        ) \
	P2("vec4.applymat4"     , vec4  , vec4_applymat4     , vec4, mat4                        ) \
	P2("vec4.applyquat"     , vec4  , vec4_applyquat     , vec4, quat                        ) \
	P3("vec4.clamp"         , vec4  , vec4_clamp         , vec4, vec4, vec4                  ) \
	P2("vec4.div"           , vec4  , vec4_div           , vec4, vec4                        ) \
	P2("vec4.dist"          , num   , vec4_dist          , vec4, vec4                        ) \
	P2("vec4.dist2"         , num   , vec4_dist2         , vec4, vec4                        ) \
	P2("vec4.dot"           , num   , vec4_dot           , vec4, vec4                        ) \
	P1("vec4.inverse"       , vec4  , vec4_inverse       , vec4                              ) \
	P1("vec4.len"           , num   , vec4_len           , vec4                              ) \
	P1("vec4.len2"          , num   , vec4_len2          , vec4                              ) \
	P3("vec4.lerp"          , vec4  , vec4_lerp          , vec4, vec4, num                   ) \
	P2("vec4.max"           , vec4  , vec4_max           , vec4, vec4                        ) \
	P2("vec4.min"           , vec4  , vec4_min           , vec4, vec4                        ) \
	P2("vec4.mul"           , vec4  , vec4_mul           , vec4, vec4                        ) \
	P1("vec4.neg"           , vec4  , vec4_neg           , vec4                              ) \
	P1("vec4.normal"        , vec4  , vec4_normal        , vec4                              ) \
	P2("vec4.scale"         , vec4  , vec4_scale         , vec4, num                         ) \
	P2("vec4.sub"           , vec4  , vec4_sub           , vec4, vec4                        ) \
	P2("quat.axisang"       , quat  , quat_axisang       , vec3, num                         ) \
	P2("quat.between"       , quat  , quat_between       , vec3, vec3                        ) \
	P2("quat.dot"           , num   , quat_dot           , quat, quat                        ) \
	P1("quat.euler_xyz"     , quat  , quat_euler_xyz     , vec3                              ) \
	P1("quat.euler_xzy"     , quat  , quat_euler_xzy     , vec3                              ) \
	P1("quat.euler_yxz"     , quat  , quat_euler_yxz     , vec3                              ) \
	P1("quat.euler_yzx"     , quat  , quat_euler_yzx     , vec3                              ) \
	P1("quat.euler_zxy"     , quat  , quat_euler_zxy     , vec3                              ) \
	P1("quat.euler_zyx"     , quat  , quat_euler_zyx     , vec3                              ) \
	P0("quat.identity"      , quat  , quat_identity                                          ) \
	P1("quat.invert"        , quat  , quat_invert        , quat                              ) \
	P3("quat.lerp"          , quat  , quat_lerp          , quat, quat, num                   ) \
	P2("quat.mul"           , quat  , quat_mul           , quat, quat                        ) \
	P2("quat.naxisang"      , quat  , quat_naxisang      , vec3, num                         ) \
	P2("quat.nbetween"      , quat  , quat_nbetween      , vec3, vec3                        ) \
	P1("quat.neg"           , quat  , quat_neg           , quat                              ) \
	P3("quat.nlerp"         , quat  , quat_nlerp         , quat, quat, num                   ) \
	P1("quat.normal"        , quat  , quat_normal        , quat                              ) \
	P3("quat.slerp"         , quat  , quat_slerp         , quat, quat, num                   ) \
	P2("mat2.add"           , mat2  , mat2_add           , mat2, mat2                        ) \
	P1("mat2.adjoint"       , mat2  , mat2_adjoint       , mat2                              ) \
	P2("mat2.compmul"       , mat2  , mat2_compmul       , mat2, mat2                        ) \
	P1("mat2.det"           , num   , mat2_det           , mat2                              ) \
	P0("mat2.identity"      , mat2  , mat2_identity                                          ) \
	P1("mat2.invert"        , mat2  , mat2_invert        , mat2                              ) \
	P2("mat2.mul"           , mat2  , mat2_mul           , mat2, mat2                        ) \
	P2("mat2.rotate"        , mat2  , mat2_rotate        , mat2, num                         ) \
	P1("mat2.rotation"      , mat2  , mat2_rotation      , num                               ) \
	P2("mat2.scale"         , mat2  , mat2_scale         , mat2, vec2                        ) \
	P1("mat2.scaling"       , mat2  , mat2_scaling       , vec2                              ) \
	P2("mat2.sub"           , mat2  , mat2_sub           , mat2, mat2                        ) \
	P1("mat2.transpose"     , mat2  , mat2_transpose     , mat2                              ) \
	P2("mat3x2.add"         , mat3x2, mat3x2_add         , mat3x2, mat3x2                    ) \
	P2("mat3x2.compmul"     , mat3x2, mat3x2_compmul     , mat3x2, mat3x2                    ) \
	P1("mat3x2.det"         , num   , mat3x2_det         , mat3x2                            ) \
	P0("mat3x2.identity"    , mat3x2, mat3x2_identity                                        ) \
	P1("mat3x2.invert"      , mat3x2, mat3x2_invert      , mat3x2                            ) \
	P2("mat3x2.mul"         , mat3x2, mat3x2_mul         , mat3x2, mat3x2                    ) \
	P2("mat3x2.rotate"      , mat3x2, mat3x2_rotate      , mat3x2, num                       ) \
	P1("mat3x2.rotation"    , mat3x2, mat3x2_rotation    , num                               ) \
	P2("mat3x2.scale"       , mat3x2, mat3x2_scale       , mat3x2, vec2                      ) \
	P1("mat3x2.scaling"     , mat3x2, mat3x2_scaling     , vec2                              ) \
	P2("mat3x2.sub"         , mat3x2, mat3x2_sub         , mat3x2, mat3x2                    ) \
	P2("mat3x2.translate"   , mat3x2, mat3x2_translate   , mat3x2, vec2                      ) \
	P1("mat3x2.translation" , mat3x2, mat3x2_translation , vec2                              ) \
	P3("mat3.add"           , mat3  , mat3_add           , mat3, mat3, mat3                  ) \
	P2("mat3.adjoint"       , mat3  , mat3_adjoint       , mat3, mat3                        ) \
	P3("mat3.compmul"       , mat3  , mat3_compmul       , mat3, mat3, mat3                  ) \
	P2("mat3.copy"          , mat3  , mat3_copy          , mat3, mat3                        ) \
	P1("mat3.det"           , num   , mat3_det           , mat3                              ) \
	P1("mat3.identity"      , mat3  , mat3_identity      , mat3                              ) \
	P2("mat3.invert"        , mat3  , mat3_invert        , mat3, mat3                        ) \
	P3("mat3.mul"           , mat3  , mat3_mul           , mat3, mat3, mat3                  ) \
	P2("mat3.quat"          , mat3  , mat3_quat          , mat3, quat                        ) \
	P3("mat3.rotate"        , mat3  , mat3_rotate        , mat3, mat3, num                   ) \
	P2("mat3.rotation"      , mat3  , mat3_rotation      , mat3, num                         ) \
	P3("mat3.scale"         , mat3  , mat3_scale         , mat3, mat3, vec2                  ) \
	P2("mat3.scaling"       , mat3  , mat3_scaling       , mat3, vec2                        ) \
	P3("mat3.sub"           , mat3  , mat3_sub           , mat3, mat3, mat3                  ) \
	P3("mat3.translate"     , mat3  , mat3_translate     , mat3, mat3, vec2                  ) \
	P2("mat3.translation"   , mat3  , mat3_translation   , mat3, vec2                        ) \
	P2("mat3.transpose"     , mat3  , mat3_transpose     , mat3, mat3                        ) \
	P3("mat4.add"           , mat4  , mat4_add           , mat4, mat4, mat4                  ) \
	P2("mat4.adjoint"       , mat4  , mat4_adjoint       , mat4, mat4                        ) \
	P3("mat4.compmul"       , mat4  , mat4_compmul       , mat4, mat4, mat4                  ) \
	P2("mat4.copy"          , mat4  , mat4_copy          , mat4, mat4                        ) \
	P1("mat4.det"           , num   , mat4_det           , mat4                              ) \
	P7("mat4.frustum"       , mat4  , mat4_frustum       , mat4, num, num, num, num, num, num) \
	P1("mat4.identity"      , mat4  , mat4_identity      , mat4                              ) \
	P2("mat4.invert"        , mat4  , mat4_invert        , mat4, mat4                        ) \
	P4("mat4.lookat"        , mat4  , mat4_lookat        , mat4, vec3, vec3, vec3            ) \
	P3("mat4.mul"           , mat4  , mat4_mul           , mat4, mat4, mat4                  ) \
	P5("mat4.orthogonal"    , mat4  , mat4_orthogonal    , mat4, num, num, num, num          ) \
	P6("mat4.perspective"   , mat4  , mat4_perspective   , mat4, num, num, num, num, num     ) \
	P2("mat4.quat"          , mat4  , mat4_quat          , mat4, quat                        ) \
	P4("mat4.rotate"        , mat4  , mat4_rotate        , mat4, mat4, vec3, num             ) \
	P3("mat4.rotation"      , mat4  , mat4_rotation      , mat4, vec3, num                   ) \
	P3("mat4.rottrans"      , mat4  , mat4_rottrans      , mat4, quat, vec3                  ) \
	P4("mat4.rottransorigin", mat4  , mat4_rottransorigin, mat4, quat, vec3, vec3            ) \
	P3("mat4.scale"         , mat4  , mat4_scale         , mat4, mat4, vec3                  ) \
	P2("mat4.scaling"       , mat4  , mat4_scaling       , mat4, vec3                        ) \
	P3("mat4.sub"           , mat4  , mat4_sub           , mat4, mat4, mat4                  ) \
	P3("mat4.translate"     , mat4  , mat4_translate     , mat4, mat4, vec3                  ) \
	P2("mat4.translation"   , mat4  , mat4_translation   , mat4, vec3                        ) \
	P2("mat4.transpose"     , mat4  , mat4_transpose     , mat4, mat4                        )

#define FUNC(F, R) \
	static sink_val L_ ## F(sink_ctx ctx, int size, sink_val *args, void *nuser){ \
		return R;                                                                 \
	}

static inline sink_val return_num(sink_ctx tx, float a, sink_val d){
	return sink_num(a);
}

static inline sink_val return_vec2(sink_ctx ctx, vec2 a, sink_val d){
	sink_val v[2] = { sink_num(a.v[0]), sink_num(a.v[1]) };
	return sink_list_newblob(ctx, 2, v);
}

static inline sink_val return_vec3(sink_ctx ctx, vec3 a, sink_val d){
	sink_val v[3] = { sink_num(a.v[0]), sink_num(a.v[1]), sink_num(a.v[2]) };
	return sink_list_newblob(ctx, 3, v);
}

static inline sink_val return_vec4(sink_ctx ctx, vec4 a, sink_val d){
	sink_val v[4] = { sink_num(a.v[0]), sink_num(a.v[1]), sink_num(a.v[2]), sink_num(a.v[3]) };
	return sink_list_newblob(ctx, 4, v);
}

static inline sink_val return_quat(sink_ctx ctx, quat a, sink_val d){
	sink_val v[4] = { sink_num(a.v[0]), sink_num(a.v[1]), sink_num(a.v[2]), sink_num(a.v[3]) };
	return sink_list_newblob(ctx, 4, v);
}

static inline sink_val return_mat2(sink_ctx ctx, mat2 a, sink_val d){
	sink_val v[4] = { sink_num(a.v[0]), sink_num(a.v[1]), sink_num(a.v[2]), sink_num(a.v[3]) };
	return sink_list_newblob(ctx, 4, v);
}

static inline sink_val return_mat3x2(sink_ctx ctx, mat3x2 a, sink_val d){
	sink_val v[6] = {
		sink_num(a.v[0]), sink_num(a.v[1]),
		sink_num(a.v[2]), sink_num(a.v[3]),
		sink_num(a.v[4]), sink_num(a.v[5])
	};
	return sink_list_newblob(ctx, 6, v);
}

static inline sink_val return_mat3(sink_ctx ctx, mat3 *a, sink_val d){
	sink_list ls = sink_castlist(ctx, d);
	ls->vals[0] = sink_num(a->v[0]);
	ls->vals[1] = sink_num(a->v[1]);
	ls->vals[2] = sink_num(a->v[2]);
	ls->vals[3] = sink_num(a->v[3]);
	ls->vals[4] = sink_num(a->v[4]);
	ls->vals[5] = sink_num(a->v[5]);
	ls->vals[6] = sink_num(a->v[6]);
	ls->vals[7] = sink_num(a->v[7]);
	ls->vals[8] = sink_num(a->v[8]);
	return d;
}

static inline sink_val return_mat4(sink_ctx ctx, mat4 *a, sink_val d){
	sink_list ls = sink_castlist(ctx, d);
	ls->vals[0] = sink_num(a->v[0]);
	ls->vals[1] = sink_num(a->v[1]);
	ls->vals[2] = sink_num(a->v[2]);
	ls->vals[3] = sink_num(a->v[3]);
	ls->vals[4] = sink_num(a->v[4]);
	ls->vals[5] = sink_num(a->v[5]);
	ls->vals[6] = sink_num(a->v[6]);
	ls->vals[7] = sink_num(a->v[7]);
	ls->vals[8] = sink_num(a->v[8]);
	ls->vals[9] = sink_num(a->v[9]);
	ls->vals[10] = sink_num(a->v[10]);
	ls->vals[11] = sink_num(a->v[11]);
	ls->vals[12] = sink_num(a->v[12]);
	ls->vals[13] = sink_num(a->v[13]);
	ls->vals[14] = sink_num(a->v[14]);
	ls->vals[15] = sink_num(a->v[15]);
	return d;
}

static inline float fix_num(sink_ctx ctx, sink_val a){
	if (!sink_isnum(a)){
		sink_abortcstr(ctx, "Expecting num");
		return 0;
	}
	return sink_castnum(a);
}

static inline vec2 fix_vec2(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting vec2");
		return (vec2){ 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 2){
		sink_abortcstr(ctx, "Expecting vec2");
		return (vec2){ 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1])){
		sink_abortcstr(ctx, "Expecting vec2");
		return (vec2){ 0, 0 };
	}
	return (vec2){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]) };
}

static inline vec3 fix_vec3(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting vec3");
		return (vec3){ 0, 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 3){
		sink_abortcstr(ctx, "Expecting vec3");
		return (vec3){ 0, 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2])){
		sink_abortcstr(ctx, "Expecting vec3");
		return (vec3){ 0, 0, 0 };
	}
	return (vec3){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]) };
}

static inline vec4 fix_vec4(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting vec4");
		return (vec4){ 0, 0, 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 4){
		sink_abortcstr(ctx, "Expecting vec4");
		return (vec4){ 0, 0, 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3])){
		sink_abortcstr(ctx, "Expecting vec4");
		return (vec4){ 0, 0, 0, 0 };
	}
	return (vec4){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]) };
}

static inline quat fix_quat(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting quat");
		return (quat){ 0, 0, 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 4){
		sink_abortcstr(ctx, "Expecting quat");
		return (quat){ 0, 0, 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3])){
		sink_abortcstr(ctx, "Expecting quat");
		return (quat){ 0, 0, 0, 0 };
	}
	return (quat){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]) };
}

static inline mat2 fix_mat2(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting mat2");
		return (mat2){ 0, 0, 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 4){
		sink_abortcstr(ctx, "Expecting mat2");
		return (mat2){ 0, 0, 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3])){
		sink_abortcstr(ctx, "Expecting mat2");
		return (mat2){ 0, 0, 0, 0 };
	}
	return (mat2){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]) };
}

static inline mat3x2 fix_mat3x2(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting mat3x2");
		return (mat3x2){ 0, 0, 0, 0, 0, 0 };
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 6){
		sink_abortcstr(ctx, "Expecting mat3x2");
		return (mat3x2){ 0, 0, 0, 0, 0, 0 };
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3]) || !sink_isnum(ls->vals[4]) || !sink_isnum(ls->vals[5])){
		sink_abortcstr(ctx, "Expecting mat3x2");
		return (mat3x2){ 0, 0, 0, 0, 0, 0 };
	}
	return (mat3x2){ sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]), sink_castnum(ls->vals[4]), sink_castnum(ls->vals[5]) };
}

static mat3 mat3_cache[4];
static int mat3_next = 0;
static inline mat3 *next_mat3(float a, float b, float c, float d, float e, float f, float g,
	float h, float i){
	mat3_next = (mat3_next + 1) % 4;
	mat3_cache[mat3_next] = (mat3){ a, b, c, d, e, f, g, h, i };
	return &mat3_cache[mat3_next];
}

static inline mat3 *fix_mat3(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting mat3");
		return next_mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 9){
		sink_abortcstr(ctx, "Expecting mat3");
		return next_mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3]) || !sink_isnum(ls->vals[4]) || !sink_isnum(ls->vals[5]) ||
		!sink_isnum(ls->vals[6]) || !sink_isnum(ls->vals[7]) || !sink_isnum(ls->vals[8])){
		sink_abortcstr(ctx, "Expecting mat3");
		return next_mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	return next_mat3(sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]), sink_castnum(ls->vals[4]), sink_castnum(ls->vals[5]),
		sink_castnum(ls->vals[6]), sink_castnum(ls->vals[7]), sink_castnum(ls->vals[8]));
}

static mat4 mat4_cache[4];
static int mat4_next = 0;
static inline mat4 *next_mat4(float a, float b, float c, float d, float e, float f, float g,
	float h, float i, float j, float k, float l, float m, float n, float o, float p){
	mat4_next = (mat4_next + 1) % 4;
	mat4_cache[mat4_next] = (mat4){ a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p };
	return &mat4_cache[mat4_next];
}

static inline mat4 *fix_mat4(sink_ctx ctx, sink_val a){
	if (!sink_islist(a)){
		sink_abortcstr(ctx, "Expecting mat4");
		return next_mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	sink_list ls = sink_castlist(ctx, a);
	if (ls->size < 16){
		sink_abortcstr(ctx, "Expecting mat4");
		return next_mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	if (!sink_isnum(ls->vals[0]) || !sink_isnum(ls->vals[1]) || !sink_isnum(ls->vals[2]) ||
		!sink_isnum(ls->vals[3]) || !sink_isnum(ls->vals[4]) || !sink_isnum(ls->vals[5]) ||
		!sink_isnum(ls->vals[6]) || !sink_isnum(ls->vals[7]) || !sink_isnum(ls->vals[8]) ||
		!sink_isnum(ls->vals[9]) || !sink_isnum(ls->vals[10]) || !sink_isnum(ls->vals[11]) ||
		!sink_isnum(ls->vals[12]) || !sink_isnum(ls->vals[13]) || !sink_isnum(ls->vals[14]) ||
		!sink_isnum(ls->vals[15])){
		sink_abortcstr(ctx, "Expecting mat4");
		return next_mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	return next_mat4(sink_castnum(ls->vals[0]), sink_castnum(ls->vals[1]), sink_castnum(ls->vals[2]),
		sink_castnum(ls->vals[3]), sink_castnum(ls->vals[4]), sink_castnum(ls->vals[5]),
		sink_castnum(ls->vals[6]), sink_castnum(ls->vals[7]), sink_castnum(ls->vals[8]),
		sink_castnum(ls->vals[9]), sink_castnum(ls->vals[10]), sink_castnum(ls->vals[11]),
		sink_castnum(ls->vals[12]), sink_castnum(ls->vals[13]), sink_castnum(ls->vals[14]),
		sink_castnum(ls->vals[15]));
}

static inline bool check_args(sink_ctx ctx, int req, int actual, const char *err){
	if (req > actual){
		sink_abortcstr(ctx, err);
		return false;
	}
	return true;
}

#define P0(N, R, F) \
	FUNC(F, return_ ## R(ctx, F(), SINK_NIL))

#define P1(N, R, F, T1) \
	FUNC(F, check_args(ctx, 1, size, "Expecting " #T1) ? \
		return_ ## R(ctx, F(fix_ ## T1(ctx, args[0])), args[0]) : SINK_NIL)

#define P2(N, R, F, T1, T2) \
	FUNC(F, check_args(ctx, 2, size, "Expecting " #T1 ", " #T2) ? \
		return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1])), args[0]) : SINK_NIL)

#define P3(N, R, F, T1, T2, T3) \
	FUNC(F, check_args(ctx, 3, size, "Expecting " #T1 ", " #T2 ", " #T3) ? \
		return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1]), \
			fix_ ## T3(ctx, args[2])), args[0]) : SINK_NIL)

#define P4(N, R, F, T1, T2, T3, T4) \
	FUNC(F, check_args(ctx, 4, size, "Expecting " #T1 ", " #T2 ", " #T3 ", " #T4) ? \
		return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1]), \
			fix_ ## T3(ctx, args[2]), fix_ ## T4(ctx, args[3])), args[0]) : SINK_NIL)

#define P5(N, R, F, T1, T2, T3, T4, T5) \
	FUNC(F, check_args(ctx, 5, size, "Expecting " #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5) ? \
		return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1]), \
			fix_ ## T3(ctx, args[2]), fix_ ## T4(ctx, args[3]), fix_ ## T5(ctx, args[4])), \
		args[0]) : SINK_NIL)

#define P6(N, R, F, T1, T2, T3, T4, T5, T6) \
	FUNC(F, check_args(ctx, 6, size, "Expecting " #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " \
		#T6) ? return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1]), \
			fix_ ## T3(ctx, args[2]), fix_ ## T4(ctx, args[3]), fix_ ## T5(ctx, args[4]), \
			fix_ ## T6(ctx, args[5])), args[0]) : SINK_NIL)

#define P7(N, R, F, T1, T2, T3, T4, T5, T6, T7) \
	FUNC(F, check_args(ctx, 7, size, "Expecting " #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " \
		#T6 ", " #T7) ? return_ ## R(ctx, F(fix_ ## T1(ctx, args[0]), fix_ ## T2(ctx, args[1]), \
			fix_ ## T3(ctx, args[2]), fix_ ## T4(ctx, args[3]), fix_ ## T5(ctx, args[4]), \
			fix_ ## T6(ctx, args[5]), fix_ ## T7(ctx, args[6])), args[0]) : SINK_NIL)

FUNCS(P0, P1, P2, P3, P4, P5, P6, P7)

#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef P5
#undef P6
#undef P7

void sink_vqm_scr(sink_scr scr){
	#define P0(N, R, F)                             "declare " N " 'sink.vqm." N "';"
	#define P1(N, R, F, T1)                         "declare " N " 'sink.vqm." N "';"
	#define P2(N, R, F, T1, T2)                     "declare " N " 'sink.vqm." N "';"
	#define P3(N, R, F, T1, T2, T3)                 "declare " N " 'sink.vqm." N "';"
	#define P4(N, R, F, T1, T2, T3, T4)             "declare " N " 'sink.vqm." N "';"
	#define P5(N, R, F, T1, T2, T3, T4, T5)         "declare " N " 'sink.vqm." N "';"
	#define P6(N, R, F, T1, T2, T3, T4, T5, T6)     "declare " N " 'sink.vqm." N "';"
	#define P7(N, R, F, T1, T2, T3, T4, T5, T6, T7) "declare " N " 'sink.vqm." N "';"
	sink_scr_incbody(scr, "vqm",
		FUNCS(P0, P1, P2, P3, P4, P5, P6, P7)
	);
	#undef P0
	#undef P1
	#undef P2
	#undef P3
	#undef P4
	#undef P5
	#undef P6
	#undef P7
}

void sink_vqm_ctx(sink_ctx ctx){
	#define P0(N, R, F)                             sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P1(N, R, F, T1)                         sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P2(N, R, F, T1, T2)                     sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P3(N, R, F, T1, T2, T3)                 sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P4(N, R, F, T1, T2, T3, T4)             sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P5(N, R, F, T1, T2, T3, T4, T5)         sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P6(N, R, F, T1, T2, T3, T4, T5, T6)     sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	#define P7(N, R, F, T1, T2, T3, T4, T5, T6, T7) sink_ctx_native(ctx, "sink.vqm." N, NULL, L_ ## F);
	FUNCS(P0, P1, P2, P3, P4, P5, P6, P7)
	#undef P0
	#undef P1
	#undef P2
	#undef P3
	#undef P4
	#undef P5
	#undef P6
	#undef P7
}
