// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

export let TAU = 6.28318530717958647692528676655900576839433879875021164195;

export type vec2   = [number, number];
export type vec3   = [number, number, number];
export type vec4   = [number, number, number, number];
export type quat   = [number, number, number, number];
export type mat2   = [number, number, number, number];
export type mat3x2 = [number, number, number, number, number, number];
export type mat3   = [number, number, number, number, number, number, number, number, number];
export type mat4   = [
	number, number, number, number,
	number, number, number, number,
	number, number, number, number,
	number, number, number, number
];

//
// num (scalars)
//

export function num_abs(n: number): number {
	return n < 0 ? -n : n;
}

export let num_acos  = Math.acos;
export let num_asin  = Math.asin;
export let num_atan2 = Math.atan2;
export let num_ceil  = Math.ceil;

export function num_clamp(n: number, min: number, max: number): number {
	return n < min ? min : (n > max ? max : n);
}

export let num_cos   = Math.cos;
export let num_floor = Math.floor;

export function num_lerp(a: number, b: number, t: number): number {
	return a + (b - a) * t;
}

export let num_log = Math.log;

export function num_max(a: number, b: number): number {
	return a > b ? a : b;
}

export function num_min(a: number, b: number): number {
	return a > b ? b : a;
}

export function num_mod(a: number, b: number): number {
	return a % b;
}

export let num_pow   = Math.pow;
export let num_round = Math.round;
export let num_sin   = Math.sin;
export let num_sqrt  = Math.sqrt;
export let num_tan   = Math.tan;

//
// vec2
//

export function vec2_add(a: vec2, b: vec2): vec2 {
	return [a[0] + b[0], a[1] + b[1]];
}

export function vec2_applymat2(a: vec2, b: mat2): vec2 {
	let ax = a[0], ay = a[1];
	return [b[0] * ax + b[2] * ay, b[1] * ax + b[3] * ay];
}

export function vec2_applymat3x2(a: vec2, b: mat3x2): vec2 {
	let ax = a[0], ay = a[1];
	return [b[0] * ax + b[2] * ay + b[4], b[1] * ax + b[3] * ay + b[5]];
}

export function vec2_applymat3(a: vec2, b: mat3): vec2 {
	let ax = a[0], ay = a[1];
	return [b[0] * ax + b[3] * ay + b[6], b[1] * ax + b[4] * ay + b[7]];
}

export function vec2_applymat4(a: vec2, b: vec2): vec2 {
	let ax = a[0], ay = a[1];
	return [b[0] * ax + b[4] * ay + b[12], b[1] * ax + b[5] * ay + b[13]];
}

export function vec2_clamp(a: vec2, min: vec2, max: vec2): vec2 {
	return [num_clamp(a[0], min[0], max[0]), num_clamp(a[1], min[1], max[1])];
}

export function vec2_dist(a: vec2, b: vec2): number {
	return num_sqrt(vec2_len2(vec2_sub(a, b)));
}

export function vec2_dist2(a: vec2, b: vec2): number {
	return vec2_len2(vec2_sub(b, a));
}

export function vec2_div(a: vec2, b: vec2): vec2 {
	return [a[0] / b[0], a[1] / b[1]];
}

export function vec2_dot(a: vec2, b: vec2): number {
	return a[0] * b[0] + a[1] * b[1];
}

export function vec2_inverse(a: vec2): vec2 {
	return [1 / a[0], 1 / a[1]];
}

export function vec2_len(a: vec2): number {
	return num_sqrt(vec2_len2(a));
}

export function vec2_len2(a: vec2): number {
	let ax = a[0], ay = a[1];
	return ax * ax + ay * ay;
}

export function vec2_lerp(a: vec2, b: vec2, t: number): vec2 {
	return [num_lerp(a[0], b[0], t), num_lerp(a[1], b[1], t)];
}

export function vec2_max(a: vec2, b: vec2): vec2 {
	return [num_max(a[0], b[0]), num_max(a[1], b[1])];
}

export function vec2_min(a: vec2, b: vec2): vec2 {
	return [num_min(a[0], b[0]), num_min(a[1], b[1])];
}

export function vec2_mul(a: vec2, b: vec2): vec2 {
	return [a[0] * b[0], a[1] * b[1]];
}

export function vec2_neg(a: vec2): vec2 {
	return [-a[0], -a[1]];
}

export function vec2_normal(a: vec2): vec2 {
	let ax = a[0], ay = a[1],
		len = ax * ax + ay * ay;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len];
	}
	return a;
}

export function vec2_scale(a: vec2, s: number): vec2 {
	return [a[0] * s, a[1] * s];
}

export function vec2_sub(a: vec2, b: vec2): vec2 {
	return [a[0] - b[0], a[1] - b[1]];
}

//
// vec3
//

export function vec3_add(a: vec3, b: vec3): vec3 {
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
}

export function vec3_angle(a: vec3, b: vec3): number {
	return vec3_nangle(vec3_normal(a), vec3_normal(b));
}

export function vec3_applymat3x2(a: vec3, b: mat3x2): vec3 {
	let ax = a[0], ay = a[1], az = a[2];
	return [
		ax * b[0] + ay * b[2] + az * b[4],
		ax * b[1] + ay * b[3] + az * b[5],
		az
	];
}

export function vec3_applymat3(a: vec3, b: mat3): vec3 {
	let ax = a[0], ay = a[1], az = a[2];
	return [
		ax * b[0] + ay * b[3] + az * b[6],
		ax * b[1] + ay * b[4] + az * b[7],
		ax * b[2] + ay * b[5] + az * b[8]
	];
}

export function vec3_applymat4(a: vec3, b: mat4){
	let ax = a[0], ay = a[1], az = a[2];
	let w = b[ 3] * ax + b[ 7] * ay + b[11] * az + b[15];
	if (w == 0)
		w = 1;
	return [
		(b[0] * ax + b[4] * ay + b[ 8] * az + b[12]) / w,
		(b[1] * ax + b[5] * ay + b[ 9] * az + b[13]) / w,
		(b[2] * ax + b[6] * ay + b[10] * az + b[14]) / w
	];
}

export function vec3_applyquat(a: vec3, b: quat){
	let
		ax = a[0], ay = a[1], az = a[2],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	let
		ix =  bw * ax + by * az - bz * ay,
		iy =  bw * ay + bz * ax - bx * az,
		iz =  bw * az + bx * ay - by * ax,
		iw = -bx * ax - by * ay - bz * az;
	return [
		ix * bw + iw * -bx + iy * -bz - iz * -by,
		iy * bw + iw * -by + iz * -bx - ix * -bz,
		iz * bw + iw * -bz + ix * -by - iy * -bx
	];
}

export function vec3_clamp(a: vec3, min: vec3, max: vec3): vec3 {
	return [
		num_clamp(a[0], min[0], max[0]),
		num_clamp(a[1], min[1], max[1]),
		num_clamp(a[2], min[2], max[2])
	];
}

export function vec3_cross(a: vec3, b: vec3): vec3 {
	let
		ax = a[0], ay = a[1], az = a[2],
		bx = b[0], by = b[1], bz = b[2];
	return [ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx];
}

export function vec3_dist(a: vec3, b: vec3): number {
	return num_sqrt(vec3_len2(vec3_sub(a, b)));
}

export function vec3_dist2(a: vec3, b: vec3): number {
	return vec3_len2(vec3_sub(b, a));
}

export function vec3_div(a: vec3, b: vec3): vec3 {
	return [a[0] / b[0], a[1] / b[1], a[2] / b[2]];
}

export function vec3_dot(a: vec3, b: vec3): number {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

export function vec3_inverse(a: vec3): vec3 {
	return [1 / a[0], 1 / a[1], 1 / a[2]];
}

export function vec3_len(a: vec3): number {
	return num_sqrt(vec3_len2(a));
}

export function vec3_len2(a: vec3): number {
	let ax = a[0], ay = a[1], az = a[2];
	return ax * ax + ay * ay + az * az;
}

export function vec3_lerp(a: vec3, b: vec3, t: number): vec3 {
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t)
	];
}

export function vec3_max(a: vec3, b: vec3): vec3 {
	return [num_max(a[0], b[0]), num_max(a[1], b[1]), num_max(a[2], b[2])];
}

export function vec3_min(a: vec3, b: vec3): vec3 {
	return [num_min(a[0], b[0]), num_min(a[1], b[1]), num_min(a[2], b[2])];
}

export function vec3_mul(a: vec3, b: vec3): vec3 {
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2]];
}

export function vec3_nangle(a: vec3, b: vec3): number { // a and b are normalized
	let c = vec3_dot(a, b);
	if (c < -1 || c > 1)
		return 0;
	return num_acos(c);
}

export function vec3_neg(a: vec3): vec3 {
	return [-a[0], -a[1], -a[2]];
}

export function vec3_normal(a: vec3): vec3 {
	let ax = a[0], ay = a[1], az = a[2];
	let len = ax * ax + ay * ay + az * az;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len];
	}
	return a;
}

export function vec3_orthogonal(a: vec3, b: vec3): vec3 {
	return vec3_normal(vec3_cross(a, b));
}

export function vec3_scale(a: vec3, s: number): vec3 {
	return [a[0] * s, a[1] * s, a[2] * s];
}

export function vec3_sub(a: vec3, b: vec3): vec3 {
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
}

//
// vec4
//

export function vec4_add(a: vec4, b: vec4){
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]];
}

export function vec4_applymat4(a: vec4, b: mat4): vec4 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	return [
		b[0] * ax + b[4] * ay + b[ 8] * az + b[12] * aw,
		b[1] * ax + b[5] * ay + b[ 9] * az + b[13] * aw,
		b[2] * ax + b[6] * ay + b[10] * az + b[14] * aw,
		b[3] * ax + b[7] * ay + b[11] * az + b[15] * aw
	];
}

export function vec4_applyquat(a: vec4, b: quat): vec4 {
	let
		ax = a[0], ay = a[1], az = a[2], aw = a[3],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	let
		ix =  bw * ax + by * az - bz * ay,
		iy =  bw * ay + bz * ax - bx * az,
		iz =  bw * az + bx * ay - by * ax,
		iw = -bx * ax - by * ay - bz * az;
	return [
		ix * bw + iw * -bx + iy * -bz - iz * -by,
		iy * bw + iw * -by + iz * -bx - ix * -bz,
		iz * bw + iw * -bz + ix * -by - iy * -bx,
		aw
	];
}

export function vec4_clamp(a: vec4, min: vec4, max: vec4): vec4 {
	return [
		num_clamp(a[0], min[0], max[0]),
		num_clamp(a[1], min[1], max[1]),
		num_clamp(a[2], min[2], max[2]),
		num_clamp(a[3], min[3], max[3])
	];
}

export function vec4_dist(a: vec4, b: vec4): number {
	return num_sqrt(vec4_len2(vec4_sub(a, b)));
}

export function vec4_dist2(a: vec4, b: vec4): number {
	return vec4_len2(vec4_sub(b, a));
}

export function vec4_div(a: vec4, b: vec4): vec4 {
	return [a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]];
}

export function vec4_dot(a: vec4, b: vec4): number {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

export function vec4_inverse(a: vec4): vec4 {
	return [1 / a[0], 1 / a[1], 1 / a[2], 1 / a[3]];
}

export function vec4_len(a: vec4): number {
	return num_sqrt(vec4_len2(a));
}

export function vec4_len2(a: vec4): number {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	return ax * ax + ay * ay + az * az + aw * aw;
}

export function vec4_lerp(a: vec4, b: vec4, t: number): vec4 {
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t),
		num_lerp(a[3], b[3], t)
	];
}

export function vec4_max(a: vec4, b: vec4): vec4 {
	return [
		num_max(a[0], b[0]),
		num_max(a[1], b[1]),
		num_max(a[2], b[2]),
		num_max(a[3], b[3])
	];
}

export function vec4_min(a: vec4, b: vec4): vec4 {
	return [
		num_min(a[0], b[0]),
		num_min(a[1], b[1]),
		num_min(a[2], b[2]),
		num_min(a[3], b[3])
	];
}

export function vec4_mul(a: vec4, b: vec4): vec4 {
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]];
}

export function vec4_neg(a: vec4): vec4 {
	return [-a[0], -a[1], -a[2], -a[3]];
}

export function vec4_normal(a: vec4): vec4 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	let len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len, aw * len];
	}
	return a;
}

export function vec4_scale(a: vec4, s: number): vec4 {
	return [a[0] * s, a[1] * s, a[2] * s, a[3] * s];
}


export function vec4_sub(a: vec4, b: vec4): vec4 {
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]];
}

//
// quat
//

export function quat_axisang(axis: vec3, ang: number): quat {
	return quat_naxisang(vec3_normal(axis), ang);
}

export function quat_between(from: vec3, to: vec3): quat {
	return quat_nbetween(vec3_normal(from), vec3_normal(to));
}

export function quat_dot(a: quat, b: quat): number {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

export function quat_euler_xyz(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

export function quat_euler_xzy(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

export function quat_euler_yxz(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

export function quat_euler_yzx(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

export function quat_euler_zxy(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

export function quat_euler_zyx(rot: vec3): quat {
	let a0 = rot[0] * 0.5;
	let a1 = rot[1] * 0.5;
	let a2 = rot[2] * 0.5;
	let cx = num_cos(a0);
	let cy = num_cos(a1);
	let cz = num_cos(a2);
	let sx = num_sin(a0);
	let sy = num_sin(a1);
	let sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

export function quat_identity(): quat {
	return [0, 0, 0, 1];
}

export function quat_invert(a: quat): quat {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	let dot = ax * ax + ay * ay + az * az + aw * aw;
	let invDot = 0;
	if (dot != 0)
		invDot = 1 / dot;
	return [
		-ax * invDot,
		-ay * invDot,
		-az * invDot,
		 aw * invDot
	];
}

export function quat_lerp(a: quat, b: quat, t: number): quat {
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t),
		num_lerp(a[3], b[3], t)
	];
}

export function quat_mul(a: quat, b: quat): quat {
	let
		ax = a[0], ay = a[1], az = a[2], aw = a[3],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	return [
		ax * bw + aw * bx + ay * bz - az * by,
		ay * bw + aw * by + az * bx - ax * bz,
		az * bw + aw * bz + ax * by - ay * bx,
		aw * bw - ax * bx - ay * by - az * bz
	];
}

export function quat_naxisang(axis: vec3, ang: number): quat { // axis is normalized
	ang *= 0.5;
	let s = num_sin(ang);
	return [axis[0] * s, axis[1] * s, axis[2] * s, num_cos(ang)];
}

export function quat_nbetween(from: vec3, to: vec3): quat { // from/to are normalized
	let r = vec3_dot(from, to) + 1;
	let cross;
	if (r < 0.000001){
		if (num_abs(from[0]) > num_abs(from[2]))
			cross = [-from[1], from[0], 0];
		else
			cross = [0, -from[2], from[1]];
	}
	else
		cross = vec3_cross(from, to);
	return quat_normal([cross[0], cross[1], cross[2], r]);
}

export function quat_neg(a: quat): quat {
	return [-a[0], -a[1], -a[2], -a[3]];
}

export function quat_nlerp(a: quat, b: quat, t: number): quat {
	return quat_normal(quat_lerp(a, b, t));
}

export function quat_normal(a: quat): quat {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	let len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len, aw * len];
	}
	return a;
}

export function quat_slerp(a: quat, b: quat, t: number): quat {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3];
	let bx = b[0], by = b[1], bz = b[2], bw = b[3];
	let omega, cosom, sinom, scale0, scale1;
	cosom = ax * bx + ay * by + az * bz + aw * bw;
	if (cosom < 0){
		cosom = -cosom;
		bx    = -bx   ;
		by    = -by   ;
		bz    = -bz   ;
		bw    = -bw   ;
	}
	if ((1 - cosom) > 0.000001){
		omega  = num_acos(cosom);
		sinom  = num_sin(omega);
		scale0 = num_sin((1 - t) * omega) / sinom;
		scale1 = num_sin(t * omega) / sinom;
	}
	else {
		scale0 = 1 - t;
		scale1 = t;
	}
	return [
		scale0 * ax + scale1 * bx,
		scale0 * ay + scale1 * by,
		scale0 * az + scale1 * bz,
		scale0 * aw + scale1 * bw
	];
}

//
// mat2
//

export function mat2_add(a: mat2, b: mat2): mat2 {
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]];
}

export function mat2_adjoint(a: mat2): mat2 {
	return [a[3], -a[1], -a[2], a[0]];
}

export function mat2_compmul(a: mat2, b: mat2): mat2 {
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]];
}

export function mat2_det(a: mat2): number {
	return a[0] * a[3] - a[2] * a[1];
}

export function mat2_identity(): mat2 {
	return [1, 0, 0, 1];
}

export function mat2_invert(a: mat2): mat2 {
	let a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
	let det = a0 * a3 - a2 * a1;
	if (det == 0)
		return [0, 0, 0, 0];
	det = 1 / det;
	return [a3 * det, -a1 * det, -a2 * det, a0 * det];
}

export function mat2_mul(a: mat2, b: mat2): mat2 {
	let
		a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3],
		b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
	return [a0 * b0 + a2 * b1, a1 * b0 + a3 * b1, a0 * b2 + a2 * b3, a1 * b2 + a3 * b3];
}

export function mat2_rotate(a: mat2, ang: number): mat2 {
	let a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], s = num_sin(ang), c = num_cos(ang);
	return [a0 * c + a2 * s, a1 * c + a3 * s, a0 * -s + a2 * c, a1 * -s + a3 * c];
}

export function mat2_rotation(ang: number): mat2 {
	let s = num_sin(ang), c = num_cos(ang);
	return [c, s, -s, c];
}

export function mat2_scale(a: mat2, b: vec2): mat2 {
	let
		a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3],
		b0 = b[0], b1 = b[1];
	return [a0 * b0, a1 * b0, a2 * b1, a3 * b1];
}

export function mat2_scaling(a: vec2): mat2 {
	return [a[0], 0, 0, a[1]];
}

export function mat2_sub(a: mat2, b: mat2): mat2 {
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]];
}

export function mat2_transpose(a: mat2): mat2 {
	return [a[0], a[2], a[1], a[3]];
}

//
// mat3x2
//

export function mat3x2_add(a: mat3x2, b: mat3x2): mat3x2 {
	return [
		a[0] + b[0], a[1] + b[1],
		a[2] + b[2], a[3] + b[3],
		a[4] + b[4], a[5] + b[5]
	];
}

export function mat3x2_compmul(a: mat3x2, b: mat3x2): mat3x2 {
	return [
		a[0] * b[0], a[1] * b[1],
		a[2] * b[2], a[3] * b[3],
		a[4] * b[4], a[5] * b[5]
	];
}

export function mat3x2_det(a: mat3x2): number {
	return a[0] * a[3] - a[2] * a[1];
}

export function mat3x2_identity(): mat3x2 {
	return [1, 0, 0, 1, 0, 0];
}

export function mat3x2_invert(a: mat3x2): mat3x2 {
	let
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		a20 = a[4], a21 = a[5];
	let det = a00 * a11 - a01 * a10;
	if (det == 0)
		return [0, 0, 0, 0, 0, 0];
	det = 1 / det;
	return [
		 a11 * det, -a01 * det,
		-a10 * det,  a00 * det,
		( a21 * a10 - a11 * a20) * det,
		(-a21 * a00 + a01 * a20) * det
	];
}

export function mat3x2_mul(a: mat3x2, b: mat3x2): mat3x2 {
	let
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		a20 = a[4], a21 = a[5],
		b00 = b[0], b01 = b[1],
		b10 = b[2], b11 = b[3],
		b20 = b[4], b21 = b[5];
	return [
		b00 * a00 + b01 * a10      , b00 * a01 + b01 * a11,
		b10 * a00 + b11 * a10      , b10 * a01 + b11 * a11,
		b20 * a00 + b21 * a10 + a20, b20 * a01 + b21 * a11 + a21
	];
}

export function mat3x2_rotate(a: mat3x2, ang: number): mat3x2 {
	let
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		s = num_sin(ang), c = num_cos(ang);
	return [
		c * a00 + s * a10, c * a01 + s * a11,
		c * a10 - s * a00, c * a11 - s * a01,
		a[4], a[5]
	];
}

export function mat3x2_rotation(ang: number): mat3x2 {
	let s = num_sin(ang), c = num_cos(ang);
	return [c, s, -s, c, 0, 0];
}

export function mat3x2_scale(a: mat3x2, b: vec2): mat3x2 {
	let bx = b[0], by = b[1];
	return [
		bx * a[0], bx * a[1],
		by * a[2], by * a[3],
		a[4], a[5],
	];
}

export function mat3x2_scaling(a: vec2): mat3x2 {
	return [a[0], 0, 0, a[1], 0, 0];
}

export function mat3x2_sub(a: mat3x2, b: mat3x2): mat3x2 {
	return [
		a[0] - b[0], a[1] - b[1],
		a[2] - b[2], a[3] - b[3],
		a[4] - b[4], a[5] - b[5]
	];
}

export function mat3x2_translate(a: mat3x2, b: vec2): mat3x2 {
	let
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		bx = b[0], by = b[1];
	return [
		a00, a01,
		a10, a11,
		bx * a00 + by * a10 + a[4],
		bx * a01 + by * a11 + a[5]
	];
}

export function mat3x2_translation(a: vec2): mat3x2 {
	return [1, 0, 0, 1, a[0], a[1]];
}

//
// mat3
//

export function mat3_add(out: mat3, a: mat3, b: mat3): mat3 {
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
	out[3] = a[3] + b[3];
	out[4] = a[4] + b[4];
	out[5] = a[5] + b[5];
	out[6] = a[6] + b[6];
	out[7] = a[7] + b[7];
	out[8] = a[8] + b[8];
	return out;
}

export function mat3_adjoint(out: mat3, a: mat3): mat3 {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8];
	out[0] = a11 * a22 - a12 * a21;
	out[1] = a02 * a21 - a01 * a22;
	out[2] = a01 * a12 - a02 * a11;
	out[3] = a12 * a20 - a10 * a22;
	out[4] = a00 * a22 - a02 * a20;
	out[5] = a02 * a10 - a00 * a12;
	out[6] = a10 * a21 - a11 * a20;
	out[7] = a01 * a20 - a00 * a21;
	out[8] = a00 * a11 - a01 * a10;
	return out;
}

export function mat3_compmul(out: mat3, a: mat3, b: mat3): mat3 {
	out[0] = a[0] * b[0];
	out[1] = a[1] * b[1];
	out[2] = a[2] * b[2];
	out[3] = a[3] * b[3];
	out[4] = a[4] * b[4];
	out[5] = a[5] * b[5];
	out[6] = a[6] * b[6];
	out[7] = a[7] * b[7];
	out[8] = a[8] * b[8];
	return out;
}

export function mat3_copy(out: mat3, a: mat3): mat3 {
	out[0] = a[0]; out[1] = a[1]; out[2] = a[2];
	out[3] = a[3]; out[4] = a[4]; out[5] = a[5];
	out[6] = a[6]; out[7] = a[7]; out[8] = a[8];
	return out;
}

export function mat3_det(a: mat3): number {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8];
	return a00 * ( a22 * a11 - a12 * a21) +
		a01 * (-a22 * a10 + a12 * a20) +
		a02 * ( a21 * a10 - a11 * a20);
}

export function mat3_identity(out: mat3 | undefined): mat3 {
	if (typeof out === 'undefined')
		return [1, 0, 0, 0, 1, 0, 0, 0, 1];
	out[0] = 1; out[1] = 0; out[2] = 0;
	out[3] = 0; out[4] = 1; out[5] = 0;
	out[6] = 0; out[7] = 0; out[8] = 1;
	return out;
}

export function mat3_invert(out: mat3, a: mat3): mat3 {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8],
		b01 =  a22 * a11 - a12 * a21,
		b11 = -a22 * a10 + a12 * a20,
		b21 =  a21 * a10 - a11 * a20;
	let det = a00 * b01 + a01 * b11 + a02 * b21;
	if (det == 0)
		throw new Error('Cannot invert mat3');
	det = 1 / det;
	out[0] =   b01                    * det;
	out[1] = (-a22 * a01 + a02 * a21) * det;
	out[2] = ( a12 * a01 - a02 * a11) * det;
	out[3] =   b11                    * det;
	out[4] = ( a22 * a00 - a02 * a20) * det;
	out[5] = (-a12 * a00 + a02 * a10) * det;
	out[6] =   b21                    * det;
	out[7] = (-a21 * a00 + a01 * a20) * det;
	out[8] = ( a11 * a00 - a01 * a10) * det;
	return out;
}

export function mat3_mul(out: mat3, a: mat3, b: mat3): mat3 {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8],
		b00 = b[0], b01 = b[1], b02 = b[2],
		b10 = b[3], b11 = b[4], b12 = b[5],
		b20 = b[6], b21 = b[7], b22 = b[8];
	out[0] = b00 * a00 + b01 * a10 + b02 * a20;
	out[1] = b00 * a01 + b01 * a11 + b02 * a21;
	out[2] = b00 * a02 + b01 * a12 + b02 * a22;
	out[3] = b10 * a00 + b11 * a10 + b12 * a20;
	out[4] = b10 * a01 + b11 * a11 + b12 * a21;
	out[5] = b10 * a02 + b11 * a12 + b12 * a22;
	out[6] = b20 * a00 + b21 * a10 + b22 * a20;
	out[7] = b20 * a01 + b21 * a11 + b22 * a21;
	out[8] = b20 * a02 + b21 * a12 + b22 * a22;
	return out;
}

export function mat3_quat(out: mat3, a: quat): mat3 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3],
		ax2 = ax + ax,
		ay2 = ay + ay,
		az2 = az + az,
		axx = ax * ax2,
		ayx = ay * ax2,
		ayy = ay * ay2,
		azx = az * ax2,
		azy = az * ay2,
		azz = az * az2,
		awx = aw * ax2,
		awy = aw * ay2,
		awz = aw * az2;
	out[0] = 1 - ayy - azz;
	out[1] =     ayx + awz;
	out[2] =     azx - awy;
	out[3] =     ayx - awz;
	out[4] = 1 - axx - azz;
	out[5] =     azy + awx;
	out[6] =     azx + awy;
	out[7] =     azy - awx;
	out[8] = 1 - axx - ayy;
	return out;
}

export function mat3_rotate(out: mat3, a: mat3, ang: number): mat3 {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8],
		s = num_sin(ang), c = num_cos(ang);
	out[0] = c * a00 + s * a10;
	out[1] = c * a01 + s * a11;
	out[2] = c * a02 + s * a12;
	out[3] = c * a10 - s * a00;
	out[4] = c * a11 - s * a01;
	out[5] = c * a12 - s * a02;
	out[6] = a20;
	out[7] = a21;
	out[8] = a22;
	return out;
}

export function mat3_rotation(out: mat3, ang: number): mat3 {
	let s = num_sin(ang), c = num_cos(ang);
	out[0] =  c;
	out[1] =  s;
	out[2] =  0;
	out[3] = -s;
	out[4] =  c;
	out[5] =  0;
	out[6] =  0;
	out[7] =  0;
	out[8] =  1;
	return out;
}

export function mat3_scale(out: mat3, a: mat3, b: vec2): mat3 {
	let bx = b[0], by = b[1];
	out[0] = bx * a[0];
	out[1] = bx * a[1];
	out[2] = bx * a[2];
	out[3] = by * a[3];
	out[4] = by * a[4];
	out[5] = by * a[5];
	out[6] = a[6];
	out[7] = a[7];
	out[8] = a[8];
	return out;
}

export function mat3_scaling(out: mat3, a: vec2): mat3 {
	out[0] = a[0];
	out[1] = 0;
	out[2] = 0;
	out[3] = 0;
	out[4] = a[1];
	out[5] = 0;
	out[6] = 0;
	out[7] = 0;
	out[8] = 1;
	return out;
}

export function mat3_sub(out: mat3, a: mat3, b: mat3): mat3 {
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
	out[3] = a[3] - b[3];
	out[4] = a[4] - b[4];
	out[5] = a[5] - b[5];
	out[6] = a[6] - b[6];
	out[7] = a[7] - b[7];
	out[8] = a[8] - b[8];
	return out;
}

export function mat3_translate(out: mat3, a: mat3, b: vec2): mat3 {
	let
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8],
		bx = b[0], by = b[1];
	out[0] = a00;
	out[1] = a01;
	out[2] = a02;
	out[3] = a10;
	out[4] = a11;
	out[5] = a12;
	out[6] = bx * a00 + by * a10 + a20;
	out[7] = bx * a01 + by * a11 + a21;
	out[8] = bx * a02 + by * a12 + a22;
	return out;
}

export function mat3_translation(out: mat3, a: vec2): mat3 {
	out[0] = 1;
	out[1] = 0;
	out[2] = 0;
	out[3] = 0;
	out[4] = 1;
	out[5] = 0;
	out[6] = a[0];
	out[7] = a[1];
	out[8] = 1;
	return out;
}

export function mat3_transpose(out: mat3, a: mat3): mat3 {
	if (out === a) {
		let a01 = a[1], a02 = a[2], a12 = a[5];
		out[1] = a[3];
		out[2] = a[6];
		out[3] = a01;
		out[5] = a[7];
		out[6] = a02;
		out[7] = a12;
	}
	else{
		out[0] = a[0];
		out[1] = a[3];
		out[2] = a[6];
		out[3] = a[1];
		out[4] = a[4];
		out[5] = a[7];
		out[6] = a[2];
		out[7] = a[5];
		out[8] = a[8];
	}
	return out;
}

//
// mat4
//

export function mat4_add(out: mat4, a: mat4, b: mat4): mat4 {
	out[ 0] = a[ 0] + b[ 0];
	out[ 1] = a[ 1] + b[ 1];
	out[ 2] = a[ 2] + b[ 2];
	out[ 3] = a[ 3] + b[ 3];
	out[ 4] = a[ 4] + b[ 4];
	out[ 5] = a[ 5] + b[ 5];
	out[ 6] = a[ 6] + b[ 6];
	out[ 7] = a[ 7] + b[ 7];
	out[ 8] = a[ 8] + b[ 8];
	out[ 9] = a[ 9] + b[ 9];
	out[10] = a[10] + b[10];
	out[11] = a[11] + b[11];
	out[12] = a[12] + b[12];
	out[13] = a[13] + b[13];
	out[14] = a[14] + b[14];
	out[15] = a[15] + b[15];
	return out;
}

export function mat4_adjoint(out: mat4, a: mat4){
	let
		a00 = a[ 0], a01 = a[ 1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[ 4], a11 = a[ 5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[ 8], a21 = a[ 9], a22 = a[10], a23 = a[11],
		a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];
	out[ 0] =  (
		a11 * (a22 * a33 - a23 * a32) -
		a21 * (a12 * a33 - a13 * a32) +
		a31 * (a12 * a23 - a13 * a22));
	out[ 1] = -(
		a01 * (a22 * a33 - a23 * a32) -
		a21 * (a02 * a33 - a03 * a32) +
		a31 * (a02 * a23 - a03 * a22));
	out[ 2] =  (
		a01 * (a12 * a33 - a13 * a32) -
		a11 * (a02 * a33 - a03 * a32) +
		a31 * (a02 * a13 - a03 * a12));
	out[ 3] = -(
		a01 * (a12 * a23 - a13 * a22) -
		a11 * (a02 * a23 - a03 * a22) +
		a21 * (a02 * a13 - a03 * a12));
	out[ 4] = -(
		a10 * (a22 * a33 - a23 * a32) -
		a20 * (a12 * a33 - a13 * a32) +
		a30 * (a12 * a23 - a13 * a22));
	out[ 5] =  (
		a00 * (a22 * a33 - a23 * a32) -
		a20 * (a02 * a33 - a03 * a32) +
		a30 * (a02 * a23 - a03 * a22));
	out[ 6] = -(
		a00 * (a12 * a33 - a13 * a32) -
		a10 * (a02 * a33 - a03 * a32) +
		a30 * (a02 * a13 - a03 * a12));
	out[ 7] =  (
		a00 * (a12 * a23 - a13 * a22) -
		a10 * (a02 * a23 - a03 * a22) +
		a20 * (a02 * a13 - a03 * a12));
	out[ 8] =  (
		a10 * (a21 * a33 - a23 * a31) -
		a20 * (a11 * a33 - a13 * a31) +
		a30 * (a11 * a23 - a13 * a21));
	out[ 9] = -(
		a00 * (a21 * a33 - a23 * a31) -
		a20 * (a01 * a33 - a03 * a31) +
		a30 * (a01 * a23 - a03 * a21));
	out[10] =  (
		a00 * (a11 * a33 - a13 * a31) -
		a10 * (a01 * a33 - a03 * a31) +
		a30 * (a01 * a13 - a03 * a11));
	out[11] = -(
		a00 * (a11 * a23 - a13 * a21) -
		a10 * (a01 * a23 - a03 * a21) +
		a20 * (a01 * a13 - a03 * a11));
	out[12] = -(
		a10 * (a21 * a32 - a22 * a31) -
		a20 * (a11 * a32 - a12 * a31) +
		a30 * (a11 * a22 - a12 * a21));
	out[13] =  (
		a00 * (a21 * a32 - a22 * a31) -
		a20 * (a01 * a32 - a02 * a31) +
		a30 * (a01 * a22 - a02 * a21));
	out[14] = -(
		a00 * (a11 * a32 - a12 * a31) -
		a10 * (a01 * a32 - a02 * a31) +
		a30 * (a01 * a12 - a02 * a11));
	out[15] =  (
		a00 * (a11 * a22 - a12 * a21) -
		a10 * (a01 * a22 - a02 * a21) +
		a20 * (a01 * a12 - a02 * a11));
	return out;
}

export function mat4_compmul(out: mat4, a: mat4, b: mat4): mat4 {
	out[ 0] = a[ 0] * b[ 0];
	out[ 1] = a[ 1] * b[ 1];
	out[ 2] = a[ 2] * b[ 2];
	out[ 3] = a[ 3] * b[ 3];
	out[ 4] = a[ 4] * b[ 4];
	out[ 5] = a[ 5] * b[ 5];
	out[ 6] = a[ 6] * b[ 6];
	out[ 7] = a[ 7] * b[ 7];
	out[ 8] = a[ 8] * b[ 8];
	out[ 9] = a[ 9] * b[ 9];
	out[10] = a[10] * b[10];
	out[11] = a[11] * b[11];
	out[12] = a[12] * b[12];
	out[13] = a[13] * b[13];
	out[14] = a[14] * b[14];
	out[15] = a[15] * b[15];
	return out;
}

export function mat4_copy(out: mat4, a: mat4): mat4 {
	out[ 0] = a[ 0]; out[ 1] = a[ 1]; out[ 2] = a[ 2]; out[ 3] = a[ 3];
	out[ 4] = a[ 4]; out[ 5] = a[ 5]; out[ 6] = a[ 6]; out[ 7] = a[ 7];
	out[ 8] = a[ 8]; out[ 9] = a[ 9]; out[10] = a[10]; out[11] = a[11];
	out[12] = a[12]; out[13] = a[13]; out[14] = a[14]; out[15] = a[15];
	return out;
}

export function mat4_det(a: mat4): number {
	let
		a00 = a[ 0], a01 = a[ 1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[ 4], a11 = a[ 5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[ 8], a21 = a[ 9], a22 = a[10], a23 = a[11],
		a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15],
		b00 = a00 * a11 - a01 * a10,
		b01 = a00 * a12 - a02 * a10,
		b02 = a00 * a13 - a03 * a10,
		b03 = a01 * a12 - a02 * a11,
		b04 = a01 * a13 - a03 * a11,
		b05 = a02 * a13 - a03 * a12,
		b06 = a20 * a31 - a21 * a30,
		b07 = a20 * a32 - a22 * a30,
		b08 = a20 * a33 - a23 * a30,
		b09 = a21 * a32 - a22 * a31,
		b10 = a21 * a33 - a23 * a31,
		b11 = a22 * a33 - a23 * a32;
	return b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
}

export function mat4_frustum(
	out: mat4, L: number, R: number, B: number, T: number, N: number, F: number): mat4 {
	let
		rl = 1 / (R - L),
		tb = 1 / (T - B),
		nf = 1 / (N - F);
	out[ 0] = (2 * N) * rl;
	out[ 1] =  0;
	out[ 2] =  0;
	out[ 3] =  0;
	out[ 4] =  0;
	out[ 5] = (2 * N) * tb;
	out[ 6] =  0;
	out[ 7] =  0;
	out[ 8] = (R + L) * rl;
	out[ 9] = (T + B) * tb;
	out[10] = (F + N) * nf;
	out[11] = -1;
	out[12] =  0;
	out[13] =  0;
	out[14] = (2 * N * F) * nf;
	out[15] =  0;
	return out;
}

export function mat4_identity(out: mat4 | undefined): mat4 {
	if (typeof out === 'undefined')
		return [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
	out[ 0] = 1; out[ 1] = 0; out[ 2] = 0; out[ 3] = 0;
	out[ 4] = 0; out[ 5] = 1; out[ 6] = 0; out[ 7] = 0;
	out[ 8] = 0; out[ 9] = 0; out[10] = 1; out[11] = 0;
	out[12] = 0; out[13] = 0; out[14] = 0; out[15] = 1;
	return out;
}

export function mat4_invert(out: mat4, a: mat4): mat4 {
	let
		a00 = a[ 0], a01 = a[ 1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[ 4], a11 = a[ 5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[ 8], a21 = a[ 9], a22 = a[10], a23 = a[11],
		a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15],
		b00 = a00 * a11 - a01 * a10,
		b01 = a00 * a12 - a02 * a10,
		b02 = a00 * a13 - a03 * a10,
		b03 = a01 * a12 - a02 * a11,
		b04 = a01 * a13 - a03 * a11,
		b05 = a02 * a13 - a03 * a12,
		b06 = a20 * a31 - a21 * a30,
		b07 = a20 * a32 - a22 * a30,
		b08 = a20 * a33 - a23 * a30,
		b09 = a21 * a32 - a22 * a31,
		b10 = a21 * a33 - a23 * a31,
		b11 = a22 * a33 - a23 * a32;
	let det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
	if (det == 0)
		throw new Error('Cannot invert mat4');
	det = 1 / det;
	out[ 0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
	out[ 1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
	out[ 2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
	out[ 3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
	out[ 4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
	out[ 5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
	out[ 6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
	out[ 7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
	out[ 8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
	out[ 9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
	out[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
	out[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
	out[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
	out[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
	out[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
	out[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
	return out;
}

export function mat4_lookat(out: mat4, eye: vec3, position: vec3, up: vec3): mat4 {
	let
		ex = eye[0], ey = eye[1], ez = eye[2],
		ux = up[0], uy = up[1], uz = up[2],
		px = position[0], py = position[1], pz = position[2];
	let z0 = ex - px, z1 = ey - py, z2 = ez - pz;
	if (z0 == 0 && z1 == 0 && z2 == 0)
		return mat4_identity(out);
	let len = 1 / num_sqrt(z0 * z0 + z1 * z1 + z2 * z2);
	z0 *= len;
	z1 *= len;
	z2 *= len;
	let x0 = uy * z2 - uz * z1;
	let x1 = uz * z0 - ux * z2;
	let x2 = ux * z1 - uy * z0;
	len = num_sqrt(
		x0 * x0 +
		x1 * x1 +
		x2 * x2
	);
	if (len == 0){
		x0 = 0;
		x1 = 0;
		x2 = 0;
	}
	else{
		len = 1 / len;
		x0 *= len;
		x1 *= len;
		x2 *= len;
	}
	let y0 = z1 * x2 - z2 * x1;
	let y1 = z2 * x0 - z0 * x2;
	let y2 = z0 * x1 - z1 * x0;
	len = num_sqrt(
		y0 * y0 +
		y1 * y1 +
		y2 * y2
	);
	if (len == 0){
		y0 = 0;
		y1 = 0;
		y2 = 0;
	}
	else{
		len = 1 / len;
		y0 *= len;
		y1 *= len;
		y2 *= len;
	}
	out[ 0] = x0;
	out[ 1] = y0;
	out[ 2] = z0;
	out[ 3] = 0;
	out[ 4] = x1;
	out[ 5] = y1;
	out[ 6] = z1;
	out[ 7] = 0;
	out[ 8] = x2;
	out[ 9] = y2;
	out[10] = z2;
	out[11] = 0;
	out[12] = -(x0 * ex + x1 * ey + x2 * ez);
	out[13] = -(y0 * ex + y1 * ey + y2 * ez);
	out[14] = -(z0 * ex + z1 * ey + z2 * ez);
	out[15] = 1;
	return out;
}

export function mat4_mul(out: mat4, a: mat4, b: mat4): mat4 {
	let
		a00 = a[ 0], a01 = a[ 1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[ 4], a11 = a[ 5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[ 8], a21 = a[ 9], a22 = a[10], a23 = a[11],
		a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];
	let b0, b1, b2, b3;
	b0 = b[ 0];
	b1 = b[ 1];
	b2 = b[ 2];
	b3 = b[ 3];
	out[ 0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[ 1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[ 2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[ 3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b[ 4];
	b1 = b[ 5];
	b2 = b[ 6];
	b3 = b[ 7];
	out[ 4] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[ 5] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[ 6] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[ 7] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b[ 8];
	b1 = b[ 9];
	b2 = b[10];
	b3 = b[11];
	out[ 8] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[ 9] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[10] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[11] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b[12];
	b1 = b[13];
	b2 = b[14];
	b3 = b[15];
	out[12] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[13] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[14] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[15] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	return out;
}

export function mat4_orthogonal(out: mat4, W: number, H: number, N: number, F: number): mat4 {
	let nf = 1 / (N - F);
	out[ 0] = 2 / W;
	out[ 1] = 0;
	out[ 2] = 0;
	out[ 3] = 0;
	out[ 4] = 0;
	out[ 5] = 2 / H;
	out[ 6] = 0;
	out[ 7] = 0;
	out[ 8] = 0;
	out[ 9] = 0;
	out[10] = 2 * nf;
	out[11] = 0;
	out[12] = 0;
	out[13] = 0;
	out[14] = (N + F) * nf;
	out[15] = 1;
	return out;
}

export function mat4_perspective(
	out: mat4, fov: number, W: number, H: number, N: number, F: number): mat4 {
	let
		f  = 1 / num_tan(fov * 0.5),
		nf = 1 / (N - F);
	out[ 0] = f;
	out[ 1] = 0;
	out[ 2] = 0;
	out[ 3] = 0;
	out[ 4] = 0;
	out[ 5] = f * W / H;
	out[ 6] = 0;
	out[ 7] = 0;
	out[ 8] = 0;
	out[ 9] = 0;
	out[10] = (F + N) * nf;
	out[11] = -1;
	out[12] = 0;
	out[13] = 0;
	out[14] = (2 * F * N) * nf;
	out[15] = 0;
	return out;
}

export function mat4_quat(out: mat4, a: quat): mat4 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3],
		ax2 = ax + ax,
		ay2 = ay + ay,
		az2 = az + az,
		axx = ax * ax2,
		ayx = ay * ax2,
		ayy = ay * ay2,
		azx = az * ax2,
		azy = az * ay2,
		azz = az * az2,
		awx = aw * ax2,
		awy = aw * ay2,
		awz = aw * az2;
	out[ 0] = 1 - ayy - azz;
	out[ 1] =     ayx + awz;
	out[ 2] =     azx - awy;
	out[ 3] = 0;
	out[ 4] =     ayx - awz;
	out[ 5] = 1 - axx - azz;
	out[ 6] =     azy + awx;
	out[ 7] = 0;
	out[ 8] =     azx + awy;
	out[ 9] =     azy - awx;
	out[10] = 1 - axx - ayy;
	out[11] = 0;
	out[12] = 0;
	out[13] = 0;
	out[14] = 0;
	out[15] = 1;
	return out;
}

export function mat4_rotate(out: mat4, a: mat4, axis: vec3, ang: number): mat4 {
	let
		x = axis[0], y = axis[1], z = axis[2],
		a00 = a[0], a01 = a[1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[4], a11 = a[5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11],
		s = num_sin(ang), c = num_cos(ang),
		t = 1 - c,
		b00 = x * x * t + c    , b01 = y * x * t + z * s, b02 = z * x * t - y * s,
		b10 = x * y * t - z * s, b11 = y * y * t + c    , b12 = z * y * t + x * s,
		b20 = x * z * t + y * s, b21 = y * z * t - x * s, b22 = z * z * t + c    ;
	out[ 0] = a00 * b00 + a10 * b01 + a20 * b02;
	out[ 1] = a01 * b00 + a11 * b01 + a21 * b02;
	out[ 2] = a02 * b00 + a12 * b01 + a22 * b02;
	out[ 3] = a03 * b00 + a13 * b01 + a23 * b02;
	out[ 4] = a00 * b10 + a10 * b11 + a20 * b12;
	out[ 5] = a01 * b10 + a11 * b11 + a21 * b12;
	out[ 6] = a02 * b10 + a12 * b11 + a22 * b12;
	out[ 7] = a03 * b10 + a13 * b11 + a23 * b12;
	out[ 8] = a00 * b20 + a10 * b21 + a20 * b22;
	out[ 9] = a01 * b20 + a11 * b21 + a21 * b22;
	out[10] = a02 * b20 + a12 * b21 + a22 * b22;
	out[11] = a03 * b20 + a13 * b21 + a23 * b22;
	if (out !== a){
		out[12] = a[12];
		out[13] = a[13];
		out[14] = a[14];
		out[15] = a[15];
	}
	return out;
}

export function mat4_rotation(out: mat4, axis: vec3, ang: number): mat4 {
	let x = axis[0], y = axis[1], z = axis[2],
		s = num_sin(ang), c = num_cos(ang),
		t = 1 - c;
	out[ 0] = x * x * t + c;
	out[ 1] = y * x * t + z * s;
	out[ 2] = z * x * t - y * s;
	out[ 3] = 0;
	out[ 4] = x * y * t - z * s;
	out[ 5] = y * y * t + c;
	out[ 6] = z * y * t + x * s;
	out[ 7] = 0;
	out[ 8] = x * z * t + y * s;
	out[ 9] = y * z * t - x * s;
	out[10] = z * z * t + c;
	out[11] = 0;
	out[12] = 0; out[13] = 0; out[14] = 0; out[15] = 1;
	return out;
}

export function mat4_rottrans(out: mat4, a: quat, b: vec3): mat4 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3],
		ax2 = ax + ax,
		ay2 = ay + ay,
		az2 = az + az,
		axx = ax * ax2,
		axy = ax * ay2,
		axz = ax * az2,
		ayy = ay * ay2,
		ayz = ay * az2,
		azz = az * az2,
		awx = aw * ax2,
		awy = aw * ay2,
		awz = aw * az2;
	out[ 0] = 1 - ayy - azz;
	out[ 1] =     axy + awz;
	out[ 2] =     axz - awy;
	out[ 3] = 0;
	out[ 4] =     axy - awz;
	out[ 5] = 1 - axx - azz;
	out[ 6] =     ayz + awx;
	out[ 7] = 0;
	out[ 8] =     axz + awy;
	out[ 9] =     ayz - awx;
	out[10] = 1 - axx - ayy;
	out[11] = 0;
	out[12] = b[0];
	out[13] = b[1];
	out[14] = b[2];
	out[15] = 1;
	return out;
}

export function mat4_rottransorigin(out: mat4, a: quat, b: vec3, origin: vec3): mat4 {
	let ax = a[0], ay = a[1], az = a[2], aw = a[3],
		ax2 = ax + ax,
		ay2 = ay + ay,
		az2 = az + az,
		axx = ax * ax2,
		axy = ax * ay2,
		axz = ax * az2,
		ayy = ay * ay2,
		ayz = ay * az2,
		azz = az * az2,
		awx = aw * ax2,
		awy = aw * ay2,
		awz = aw * az2,
		ox = origin[0], oy = origin[1], oz = origin[2];
	out[ 0] = 1 - ayy - azz;
	out[ 1] =     axy + awz;
	out[ 2] =     axz - awy;
	out[ 3] = 0;
	out[ 4] =     axy - awz;
	out[ 5] = 1 - axx - azz;
	out[ 6] =     ayz + awx;
	out[ 7] = 0;
	out[ 8] =     axz + awy;
	out[ 9] =     ayz - awx;
	out[10] = 1 - axx - ayy;
	out[11] = 0;
	out[12] = b[0] + ox - (out[0] * ox + out[4] * oy + out[ 8] * oz);
	out[13] = b[1] + oy - (out[1] * ox + out[5] * oy + out[ 9] * oz);
	out[14] = b[2] + oz - (out[2] * ox + out[6] * oy + out[10] * oz);
	out[15] = 1;
	return out;
}

export function mat4_scale(out: mat4, a: mat4, b: vec3): mat4 {
	let bx = b[0], by = b[1], bz = b[2];
	out[ 0] = a[ 0] * bx;
	out[ 1] = a[ 1] * bx;
	out[ 2] = a[ 2] * bx;
	out[ 3] = a[ 3] * bx;
	out[ 4] = a[ 4] * by;
	out[ 5] = a[ 5] * by;
	out[ 6] = a[ 6] * by;
	out[ 7] = a[ 7] * by;
	out[ 8] = a[ 8] * bz;
	out[ 9] = a[ 9] * bz;
	out[10] = a[10] * bz;
	out[11] = a[11] * bz;
	out[12] = a[12]     ;
	out[13] = a[13]     ;
	out[14] = a[14]     ;
	out[15] = a[15]     ;
	return out;
}

export function mat4_scaling(out: mat4, a: vec3): mat4 {
	out[ 0] = a[0]; out[ 1] =    0; out[ 2] =    0; out[ 3] = 0;
	out[ 4] =    0; out[ 5] = a[1]; out[ 6] =    0; out[ 7] = 0;
	out[ 8] =    0; out[ 9] =    0; out[10] = a[2]; out[11] = 0;
	out[12] =    0; out[13] =    0; out[14] =    0; out[15] = 1;
	return out;
}

export function mat4_sub(out: mat4, a: mat4, b: mat4): mat4 {
	out[ 0] = a[ 0] - b[ 0];
	out[ 1] = a[ 1] - b[ 1];
	out[ 2] = a[ 2] - b[ 2];
	out[ 3] = a[ 3] - b[ 3];
	out[ 4] = a[ 4] - b[ 4];
	out[ 5] = a[ 5] - b[ 5];
	out[ 6] = a[ 6] - b[ 6];
	out[ 7] = a[ 7] - b[ 7];
	out[ 8] = a[ 8] - b[ 8];
	out[ 9] = a[ 9] - b[ 9];
	out[10] = a[10] - b[10];
	out[11] = a[11] - b[11];
	out[12] = a[12] - b[12];
	out[13] = a[13] - b[13];
	out[14] = a[14] - b[14];
	out[15] = a[15] - b[15];
	return out;
}

export function mat4_translate(out: mat4, a: mat4, b: vec3): mat4 {
	let bx = b[0], by = b[1], bz = b[2];
	if (out === a){
		out[12] = a[0] * bx + a[4] * by + a[ 8] * bz + a[12];
		out[13] = a[1] * bx + a[5] * by + a[ 9] * bz + a[13];
		out[14] = a[2] * bx + a[6] * by + a[10] * bz + a[14];
		out[15] = a[3] * bx + a[7] * by + a[11] * bz + a[15];
	}
	else{
		let
			a00 = a[0], a01 = a[1], a02 = a[ 2], a03 = a[ 3],
			a10 = a[4], a11 = a[5], a12 = a[ 6], a13 = a[ 7],
			a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11];
		out[ 0] = a00;
		out[ 1] = a01;
		out[ 2] = a02;
		out[ 3] = a03;
		out[ 4] = a10;
		out[ 5] = a11;
		out[ 6] = a12;
		out[ 7] = a13;
		out[ 8] = a20;
		out[ 9] = a21;
		out[10] = a22;
		out[11] = a23;
		out[12] = a00 * bx + a10 * by + a20 * bz + a[12];
		out[13] = a01 * bx + a11 * by + a21 * bz + a[13];
		out[14] = a02 * bx + a12 * by + a22 * bz + a[14];
		out[15] = a03 * bx + a13 * by + a23 * bz + a[15];
	}
	return out;
}

export function mat4_translation(out: mat4, a: vec3): mat4 {
	out[ 0] = 1; out[ 1] = 0; out[ 2] = 0; out[ 3] = 0;
	out[ 4] = 0; out[ 5] = 1; out[ 6] = 0; out[ 7] = 0;
	out[ 8] = 0; out[ 9] = 0; out[10] = 1; out[11] = 0;
	out[12] = a[0]; out[13] = a[1]; out[14] = a[2]; out[15] = 1;
	return out;
}

export function mat4_transpose(out: mat4, a: mat4): mat4 {
	if (out === a){
		let
			a01 = a[1], a02 = a[2], a03 = a[ 3],
			/*       */ a12 = a[6], a13 = a[ 7],
			/*                   */ a23 = a[11];
		out[ 1] = a[ 4];
		out[ 2] = a[ 8];
		out[ 3] = a[12];
		out[ 4] = a01;
		out[ 6] = a[ 9];
		out[ 7] = a[13];
		out[ 8] = a02;
		out[ 9] = a12;
		out[11] = a[14];
		out[12] = a03;
		out[13] = a13;
		out[14] = a23;
	}
	else{
		out[ 0] = a[ 0]; out[ 1] = a[ 4]; out[ 2] = a[ 8]; out[ 3] = a[12];
		out[ 4] = a[ 1]; out[ 5] = a[ 5]; out[ 6] = a[ 9]; out[ 7] = a[13];
		out[ 8] = a[ 2]; out[ 9] = a[ 6]; out[10] = a[10]; out[11] = a[14];
		out[12] = a[ 3]; out[13] = a[ 7]; out[14] = a[11]; out[15] = a[15];
	}
	return out;
}
