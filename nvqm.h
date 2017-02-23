// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

#ifndef NVQM__H
#define NVQM__H

#include <math.h>

typedef struct { float v[ 2]; } vec2;
typedef struct { float v[ 3]; } vec3;
typedef struct { float v[ 4]; } vec4;
typedef struct { float v[ 4]; } quat;
typedef struct { float v[ 4]; } mat2;
typedef struct { float v[ 6]; } mat3x2;
typedef struct { float v[ 9]; } mat3;
typedef struct { float v[16]; } mat4;

static const float TAU = 6.28318530717958647692528676655900576839433879875021164195f;

//
// num (scalars)
//

static inline float num_abs(float a){
	return a < 0 ? -a : a;
}

static inline float num_acos(float a){
	return acosf(a);
}

static inline float num_asin(float a){
	return asinf(a);
}

static inline float num_atan2(float a, float b){
	return atan2f(a, b);
}

static inline float num_ceil(float a){
	return ceilf(a);
}

static inline float num_clamp(float a, float min, float max){
	return a < min ? min : (a > max ? max : a);
}

static inline float num_cos(float a){
	return cosf(a);
}

static inline float num_floor(float a){
	return floorf(a);
}

static inline float num_lerp(float a, float b, float t){
	return a + (b - a) * t;
}

static inline float num_log(float a){
	return logf(a);
}

static inline float num_max(float a, float b){
	return a > b ? a : b;
}

static inline float num_min(float a, float b){
	return a > b ? b : a;
}

static inline float num_mod(float a, float b){
	return fmodf(a, b);
}

static inline float num_pow(float a, float b){
	return powf(a, b);
}

static inline float num_round(float a){
	return roundf(a);
}

static inline float num_sin(float a){
	return sinf(a);
}

static inline float num_sqrt(float a){
	return sqrtf(a);
}

static inline float num_tan(float a){
	return tanf(a);
}

//
// vec2
//

static inline vec2 vec2_neg(vec2 a){
	return (vec2){ -a.v[0], -a.v[1] };
}

static inline vec2 vec2_add(vec2 a, vec2 b){
	return (vec2){ a.v[0] + b.v[0], a.v[1] + b.v[1] };
}

static inline vec2 vec2_sub(vec2 a, vec2 b){
	return (vec2){ a.v[0] - b.v[0], a.v[1] - b.v[1] };
}

static inline vec2 vec2_mul(vec2 a, vec2 b){
	return (vec2){ a.v[0] * b.v[0], a.v[1] * b.v[1] };
}

static inline vec2 vec2_div(vec2 a, vec2 b){
	return (vec2){ a.v[0] / b.v[0], a.v[1] / b.v[1] };
}

static inline vec2 vec2_min(vec2 a, vec2 b){
	return (vec2){ num_min(a.v[0], b.v[0]), num_min(a.v[1], b.v[1]) };
}

static inline vec2 vec2_max(vec2 a, vec2 b){
	return (vec2){ num_max(a.v[0], b.v[0]), num_max(a.v[1], b.v[1]) };
}

static inline vec2 vec2_clamp(vec2 a, vec2 min, vec2 max){
	return (vec2){ num_clamp(a.v[0], min.v[0], max.v[0]), num_clamp(a.v[1], min.v[1], max.v[1]) };
}

static inline vec2 vec2_lerp(vec2 a, vec2 b, float t){
	return (vec2){ num_lerp(a.v[0], b.v[0], t), num_lerp(a.v[1], b.v[1], t) };
}

static inline vec2 vec2_inverse(vec2 a){
	return (vec2){ 1.0f / a.v[0], 1.0f / a.v[1] };
}

static inline vec2 vec2_normal(vec2 a){
	float ax = a.v[0], ay = a.v[1],
		len = ax * ax + ay * ay;
	if (len > 0.0f){
		len = 1.0f / num_sqrt(len);
		return (vec2){ ax * len, ay * len };
	}
	return a;
}

static inline vec2 vec2_scale(vec2 a, float s){
	return (vec2){ a.v[0] * s, a.v[1] * s };
}

static inline vec2 vec2_applymat2(vec2 a, mat2 b){
	float ax = a.v[0], ay = a.v[1];
	return (vec2){ b.v[0] * ax + b.v[2] * ay, b.v[1] * ax + b.v[3] * ay };
}

static inline vec2 vec2_applymat3(vec2 a, mat3 *b){
	float ax = a.v[0], ay = a.v[1];
	return (vec2){ b->v[0] * ax + b->v[3] * ay + b->v[6], b->v[1] * ax + b->v[4] * ay + b->v[7] };
}

static inline vec2 vec2_applymat4(vec2 a, mat4 *b){
	float ax = a.v[0], ay = a.v[1];
	return (vec2){ b->v[0] * ax + b->v[4] * ay + b->v[12], b->v[1] * ax + b->v[5] * ay + b->v[13] };
}

static inline float vec2_dot(vec2 a, vec2 b){
	return a.v[0] * b.v[0] + a.v[1] * b.v[1];
}

static inline float vec2_len2(vec2 a){
	float ax = a.v[0], ay = a.v[1];
	return ax * ax + ay * ay;
}

static inline float vec2_len(vec2 a){
	return num_sqrt(vec2_len2(a));
}

static inline float vec2_dist2(vec2 a, vec2 b){
	return vec2_len2(vec2_sub(b, a));
}

static inline float vec2_dist(vec2 a, vec2 b){
	return num_sqrt(vec2_len2(vec2_sub(a, b)));
}

//
// vec3
//

static inline vec3 vec3_neg(vec3 a){
	return (vec3){ -a.v[0], -a.v[1], -a.v[2] };
}

static inline vec3 vec3_add(vec3 a, vec3 b){
	return (vec3){ a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2] };
}

static inline vec3 vec3_sub(vec3 a, vec3 b){
	return (vec3){ a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2] };
}

static inline vec3 vec3_mul(vec3 a, vec3 b){
	return (vec3){ a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2] };
}

static inline vec3 vec3_div(vec3 a, vec3 b){
	return (vec3){ a.v[0] / b.v[0], a.v[1] / b.v[1], a.v[2] / b.v[2] };
}

static inline vec3 vec3_min(vec3 a, vec3 b){
	return (vec3){ num_min(a.v[0], b.v[0]), num_min(a.v[1], b.v[1]), num_min(a.v[2], b.v[2]) };
}

static inline vec3 vec3_max(vec3 a, vec3 b){
	return (vec3){ num_max(a.v[0], b.v[0]), num_max(a.v[1], b.v[1]), num_max(a.v[2], b.v[2]) };
}

static inline vec3 vec3_clamp(vec3 a, vec3 min, vec3 max){
	return (vec3){
		num_clamp(a.v[0], min.v[0], max.v[0]),
		num_clamp(a.v[1], min.v[1], max.v[1]),
		num_clamp(a.v[2], min.v[2], max.v[2])
	};
}

static inline vec3 vec3_lerp(vec3 a, vec3 b, float t){
	return (vec3){
		num_lerp(a.v[0], b.v[0], t),
		num_lerp(a.v[1], b.v[1], t),
		num_lerp(a.v[2], b.v[2], t)
	};
}

static inline vec3 vec3_inverse(vec3 a){
	return (vec3){ 1.0f / a.v[0], 1.0f / a.v[1], 1.0f / a.v[2] };
}

static inline vec3 vec3_normal(vec3 a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2];
	float len = ax * ax + ay * ay + az * az;
	if (len > 0.0f){
		len = 1.0f / num_sqrt(len);
		return (vec3){ ax * len, ay * len, az * len };
	}
	return a;
}

static inline vec3 vec3_cross(vec3 a, vec3 b){
	float
		ax = a.v[0], ay = a.v[1], az = a.v[2],
		bx = b.v[0], by = b.v[1], bz = b.v[2];
	return (vec3){ ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx };
}

static inline vec3 vec3_scale(vec3 a, float s){
	return (vec3){ a.v[0] * s, a.v[1] * s, a.v[2] * s };
}

static inline vec3 vec3_applymat3(vec3 a, mat3 *b){
	float ax = a.v[0], ay = a.v[1], az = a.v[2];
	return (vec3){
		ax * b->v[0] + ay * b->v[3] + az * b->v[6],
		ax * b->v[1] + ay * b->v[4] + az * b->v[7],
		ax * b->v[2] + ay * b->v[5] + az * b->v[8]
	};
}

static inline vec3 vec3_applymat4(vec3 a, mat4 *b){
	float ax = a.v[0], ay = a.v[1], az = a.v[2];
	float w = b->v[ 3] * ax + b->v[ 7] * ay + b->v[11] * az + b->v[15];
	if (w == 0.0f)
		w = 1.0f;
	return (vec3){
		(b->v[0] * ax + b->v[4] * ay + b->v[ 8] * az + b->v[12]) / w,
		(b->v[1] * ax + b->v[5] * ay + b->v[ 9] * az + b->v[13]) / w,
		(b->v[2] * ax + b->v[6] * ay + b->v[10] * az + b->v[14]) / w
	};
}

static inline vec3 vec3_applyquat(vec3 a, quat b){
	float
		ax = a.v[0], ay = a.v[1], az = a.v[2],
		bx = b.v[0], by = b.v[1], bz = b.v[2], bw = b.v[3];
	float
		ix =  bw * ax + by * az - bz * ay,
		iy =  bw * ay + bz * ax - bx * az,
		iz =  bw * az + bx * ay - by * ax,
		iw = -bx * ax - by * ay - bz * az;
	return (vec3){
		ix * bw + iw * -bx + iy * -bz - iz * -by,
		iy * bw + iw * -by + iz * -bx - ix * -bz,
		iz * bw + iw * -bz + ix * -by - iy * -bx
	};
}

static inline float vec3_dot(vec3 a, vec3 b){
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

static inline float vec3_nangle(vec3 a, vec3 b){ // a and b are normalized
	float c = vec3_dot(a, b);
	if (c < -1.0f || c > 1.0f)
		return 0;
	return num_acos(c);
}

static inline float vec3_angle(vec3 a, vec3 b){
	return vec3_nangle(vec3_normal(a), vec3_normal(b));
}

static inline float vec3_len2(vec3 a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2];
	return ax * ax + ay * ay + az * az;
}

static inline float vec3_len(vec3 a){
	return num_sqrt(vec3_len2(a));
}

static inline float vec3_dist2(vec3 a, vec3 b){
	return vec3_len2(vec3_sub(b, a));
}

static inline float vec3_dist(vec3 a, vec3 b){
	return num_sqrt(vec3_len2(vec3_sub(a, b)));
}

//
// vec4
//

static inline vec4 vec4_neg(vec4 a){
	return (vec4){ -a.v[0], -a.v[1], -a.v[2], -a.v[3] };
}

static inline vec4 vec4_add(vec4 a, vec4 b){
	return (vec4){ a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2], a.v[3] + b.v[3] };
}

static inline vec4 vec4_sub(vec4 a, vec4 b){
	return (vec4){ a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] - b.v[3] };
}

static inline vec4 vec4_mul(vec4 a, vec4 b){
	return (vec4){ a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2], a.v[3] * b.v[3] };
}

static inline vec4 vec4_div(vec4 a, vec4 b){
	return (vec4){ a.v[0] / b.v[0], a.v[1] / b.v[1], a.v[2] / b.v[2], a.v[3] / b.v[3] };
}

static inline vec4 vec4_min(vec4 a, vec4 b){
	return (vec4){
		num_min(a.v[0], b.v[0]),
		num_min(a.v[1], b.v[1]),
		num_min(a.v[2], b.v[2]),
		num_min(a.v[3], b.v[3])
	};
}

static inline vec4 vec4_max(vec4 a, vec4 b){
	return (vec4){
		num_max(a.v[0], b.v[0]),
		num_max(a.v[1], b.v[1]),
		num_max(a.v[2], b.v[2]),
		num_max(a.v[3], b.v[3])
	};
}

static inline vec4 vec4_clamp(vec4 a, vec4 min, vec4 max){
	return (vec4){
		num_clamp(a.v[0], min.v[0], max.v[0]),
		num_clamp(a.v[1], min.v[1], max.v[1]),
		num_clamp(a.v[2], min.v[2], max.v[2]),
		num_clamp(a.v[3], min.v[3], max.v[3])
	};
}

static inline vec4 vec4_lerp(vec4 a, vec4 b, float t){
	return (vec4){
		num_lerp(a.v[0], b.v[0], t),
		num_lerp(a.v[1], b.v[1], t),
		num_lerp(a.v[2], b.v[2], t),
		num_lerp(a.v[3], b.v[3], t)
	};
}

static inline vec4 vec4_inverse(vec4 a){
	return (vec4){ 1.0f / a.v[0], 1.0f / a.v[1], 1.0f / a.v[2], 1.0f / a.v[3] };
}

static inline vec4 vec4_normal(vec4 a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	float len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0.0f){
		len = 1.0f / num_sqrt(len);
		return (vec4){ ax * len, ay * len, az * len, aw * len };
	}
	return a;
}

static inline vec4 vec4_scale(vec4 a, float s){
	return (vec4){ a.v[0] * s, a.v[1] * s, a.v[2] * s, a.v[3] * s };
}

static inline vec4 vec4_applymat4(vec4 a, mat4 *b){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	return (vec4){
		b->v[0] * ax + b->v[4] * ay + b->v[ 8] * az + b->v[12] * aw,
		b->v[1] * ax + b->v[5] * ay + b->v[ 9] * az + b->v[13] * aw,
		b->v[2] * ax + b->v[6] * ay + b->v[10] * az + b->v[14] * aw,
		b->v[3] * ax + b->v[7] * ay + b->v[11] * az + b->v[15] * aw
	};
}

static inline vec4 vec4_applyquat(vec4 a, quat b){
	float
		ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		bx = b.v[0], by = b.v[1], bz = b.v[2], bw = b.v[3];
	float
		ix =  bw * ax + by * az - bz * ay,
		iy =  bw * ay + bz * ax - bx * az,
		iz =  bw * az + bx * ay - by * ax,
		iw = -bx * ax - by * ay - bz * az;
	return (vec4){
		ix * bw + iw * -bx + iy * -bz - iz * -by,
		iy * bw + iw * -by + iz * -bx - ix * -bz,
		iz * bw + iw * -bz + ix * -by - iy * -bx,
		aw
	};
}

static inline float vec4_dot(vec4 a, vec4 b){
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3];
}

static inline float vec4_len2(vec4 a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	return ax * ax + ay * ay + az * az + aw * aw;
}

static inline float vec4_len(vec4 a){
	return num_sqrt(vec4_len2(a));
}

static inline float vec4_dist2(vec4 a, vec4 b){
	return vec4_len2(vec4_sub(b, a));
}

static inline float vec4_dist(vec4 a, vec4 b){
	return num_sqrt(vec4_len2(vec4_sub(a, b)));
}

//
// quat
//

static inline quat quat_naxisang(vec3 axis, float ang);
static inline quat quat_axisang(vec3 axis, float ang){
	return quat_naxisang(vec3_normal(axis), ang);
}

static inline quat quat_nbetween(vec3 from, vec3 to);
static inline quat quat_between(vec3 from, vec3 to){
	return quat_nbetween(vec3_normal(from), vec3_normal(to));
}

static inline float quat_dot(quat a, quat b){
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3];
}

#define NVQM_QUAT_EULER_ROT      \
	float a0 = rot.v[0] * 0.5f;  \
	float a1 = rot.v[1] * 0.5f;  \
	float a2 = rot.v[2] * 0.5f;  \
	float cx = num_cos(a0);      \
	float cy = num_cos(a1);      \
	float cz = num_cos(a2);      \
	float sx = num_sin(a0);      \
	float sy = num_sin(a1);      \
	float sz = num_sin(a2);

static inline quat quat_euler_xyz(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	};
}

static inline quat quat_euler_xzy(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	};
}

static inline quat quat_euler_yxz(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	};
}

static inline quat quat_euler_yzx(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	};
}

static inline quat quat_euler_zxy(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	};
}

static inline quat quat_euler_zyx(vec3 rot){
	NVQM_QUAT_EULER_ROT
	return (quat){
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	};
}

static inline quat quat_identity(){
	return (quat){ 0, 0, 0, 1 };
}

static inline quat quat_invert(quat a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	float dot = ax * ax + ay * ay + az * az + aw * aw;
	float invDot = 0;
	if (dot != 0.0f)
		invDot = 1.0f / dot;
	return (quat){
		-ax * invDot,
		-ay * invDot,
		-az * invDot,
		 aw * invDot
	};
}

static inline quat quat_lerp(quat a, quat b, float t){
	return (quat){
		num_lerp(a.v[0], b.v[0], t),
		num_lerp(a.v[1], b.v[1], t),
		num_lerp(a.v[2], b.v[2], t),
		num_lerp(a.v[3], b.v[3], t)
	};
}

static inline quat quat_mul(quat a, quat b){
	float
		ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		bx = b.v[0], by = b.v[1], bz = b.v[2], bw = b.v[3];
	return (quat){
		ax * bw + aw * bx + ay * bz - az * by,
		ay * bw + aw * by + az * bx - ax * bz,
		az * bw + aw * bz + ax * by - ay * bx,
		aw * bw - ax * bx - ay * by - az * bz
	};
}

static inline quat quat_naxisang(vec3 axis, float ang){ // axis is normalized
	ang *= 0.5f;
	float s = num_sin(ang);
	return (quat){ axis.v[0] * s, axis.v[1] * s, axis.v[2] * s, num_cos(ang) };
}

static inline quat quat_normal(quat a);
static inline quat quat_nbetween(vec3 from, vec3 to){ // from/to are normalized
	float r = vec3_dot(from, to) + 1.0f;
	vec3 cross;
	if (r < 0.000001f){
		if (num_abs(from.v[0]) > num_abs(from.v[2]))
			cross = (vec3){ -from.v[1], from.v[0], 0.0f };
		else
			cross = (vec3){ 0.0f, -from.v[2], from.v[1] };
	}
	else
		cross = vec3_cross(from, to);
	return quat_normal((quat){ cross.v[0], cross.v[1], cross.v[2], r });
}

static inline quat quat_neg(quat a){
	return (quat){ -a.v[0], -a.v[1], -a.v[2], -a.v[3] };
}

static inline quat quat_nlerp(quat a, quat b, float t){
	return quat_normal(quat_lerp(a, b, t));
}

static inline quat quat_normal(quat a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	float len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0.0f){
		len = 1.0f / num_sqrt(len);
		return (quat){ ax * len, ay * len, az * len, aw * len };
	}
	return a;
}

static inline quat quat_slerp(quat a, quat b, float t){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3];
	float bx = b.v[0], by = b.v[1], bz = b.v[2], bw = b.v[3];
	float omega, cosom, sinom, scale0, scale1;
	cosom = ax * bx + ay * by + az * bz + aw * bw;
	if (cosom < 0.0f){
		cosom = -cosom;
		bx    = -bx   ;
		by    = -by   ;
		bz    = -bz   ;
		bw    = -bw   ;
	}
	if ((1.0f - cosom) > 0.000001f){
		omega  = num_acos(cosom);
		sinom  = num_sin(omega);
		scale0 = num_sin((1.0f - t) * omega) / sinom;
		scale1 = num_sin(t * omega) / sinom;
	}
	else {
		scale0 = 1.0f - t;
		scale1 = t;
	}
	return (quat){
		scale0 * ax + scale1 * bx,
		scale0 * ay + scale1 * by,
		scale0 * az + scale1 * bz,
		scale0 * aw + scale1 * bw
	};
}

//
// mat2
//

static inline mat2 mat2_identity(){
	return (mat2){ 1, 0, 0, 1 };
}

static inline mat2 mat2_rotation(float ang){
	float s = num_sin(ang), c = num_cos(ang);
	return (mat2){ c, s, -s, c };
}

static inline mat2 mat2_scaling(vec2 s){
	return (mat2){ s.v[0], 0, 0, s.v[1] };
}

static inline mat2 mat2_transpose(mat2 a){
	return (mat2){ a.v[0], a.v[2], a.v[1], a.v[3] };
}

static inline mat2 mat2_invert(mat2 a){
	float a0 = a.v[0], a1 = a.v[1], a2 = a.v[2], a3 = a.v[3];
	float det = a0 * a3 - a2 * a1;
	if (det == 0.0f)
		return (mat2){ 0, 0, 0, 0 };
	det = 1.0f / det;
	return (mat2){ a3 * det, -a1 * det, -a2 * det, a0 * det };
}

static inline mat2 mat2_adjoint(mat2 a){
	return (mat2){ a.v[3], -a.v[1], -a.v[2], a.v[0] };
}

static inline float mat2_det(mat2 a){
	return a.v[0] * a.v[3] - a.v[2] * a.v[1];
}

static inline mat2 mat2_add(mat2 a, mat2 b){
	return (mat2){ a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2], a.v[3] + b.v[3] };
}

static inline mat2 mat2_sub(mat2 a, mat2 b){
	return (mat2){ a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] - b.v[3] };
}

static inline mat2 mat2_mul(mat2 a, mat2 b){
	float
		a0 = a.v[0], a1 = a.v[1], a2 = a.v[2], a3 = a.v[3],
		b0 = b.v[0], b1 = b.v[1], b2 = b.v[2], b3 = b.v[3];
	return (mat2){ a0 * b0 + a2 * b1, a1 * b0 + a3 * b1, a0 * b2 + a2 * b3, a1 * b2 + a3 * b3 };
}

static inline mat2 mat2_compmul(mat2 a, mat2 b){
	return (mat2){ a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2], a.v[3] * b.v[3] };
}

static inline mat2 mat2_rotate(mat2 a, float ang){
	float a0 = a.v[0], a1 = a.v[1], a2 = a.v[2], a3 = a.v[3], s = num_sin(ang), c = num_cos(ang);
	return (mat2){ a0 * c + a2 * s, a1 * c + a3 * s, a0 * -s + a2 * c, a1 * -s + a3 * c };
}

static inline mat2 mat2_scale(mat2 a, vec2 b){
	float
		a0 = a.v[0], a1 = a.v[1], a2 = a.v[2], a3 = a.v[3],
		b0 = b.v[0], b1 = b.v[1];
	return (mat2){ a0 * b0, a1 * b0, a2 * b1, a3 * b1 };
}

//
// TODO: mat3x2
//

//
// mat3
//

mat3 *mat3_quat       (mat3 *out, quat a);
mat3 *mat3_identity   (mat3 *out);
mat3 *mat3_rotation   (mat3 *out, float ang);
mat3 *mat3_scaling    (mat3 *out, vec2 a);
mat3 *mat3_translation(mat3 *out, vec2 a);
mat3 *mat3_copy       (mat3 *out, mat3 *a);
mat3 *mat3_transpose  (mat3 *out, mat3 *a);
mat3 *mat3_invert     (mat3 *out, mat3 *a);
mat3 *mat3_adjoint    (mat3 *out, mat3 *a);
float mat3_det        (mat3 *a);
mat3 *mat3_add        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_sub        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_mul        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_compmul    (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_rotate     (mat3 *out, mat3 *a, float ang);
mat3 *mat3_scale      (mat3 *out, mat3 *a, vec2 b);
mat3 *mat3_translate  (mat3 *out, mat3 *a, vec2 b);

//
// mat4
//

mat4 *mat4_quat          (mat4 *out, quat a);
mat4 *mat4_identity      (mat4 *out);
mat4 *mat4_rotation      (mat4 *out, vec3 axis, float ang);
mat4 *mat4_scaling       (mat4 *out, vec3 a);
mat4 *mat4_translation   (mat4 *out, vec3 a);
mat4 *mat4_frustum       (mat4 *out, float L, float R, float B, float T, float N, float F);
mat4 *mat4_perspective   (mat4 *out, float fov, float width, float height, float N, float F);
mat4 *mat4_orthogonal    (mat4 *out, float W, float H, float N, float F);
mat4 *mat4_lookat        (mat4 *out, vec3 eye, vec3 position, vec3 up);
mat4 *mat4_rottrans      (mat4 *out, quat a, vec3 b);
mat4 *mat4_rottransorigin(mat4 *out, quat a, vec3 b, vec3 origin);
mat4 *mat4_copy          (mat4 *out, mat4 *a);
mat4 *mat4_transpose     (mat4 *out, mat4 *a);
mat4 *mat4_invert        (mat4 *out, mat4 *a);
mat4 *mat4_adjoint       (mat4 *out, mat4 *a);
float mat4_det           (mat4 *a);
mat4 *mat4_add           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_sub           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_mul           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_compmul       (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_rotate        (mat4 *out, mat4 *a, vec3 axis, float ang);
mat4 *mat4_scale         (mat4 *out, mat4 *a, vec3 b);
mat4 *mat4_translate     (mat4 *out, mat4 *a, vec3 b);

#endif // NVQM__H
