// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

var TAU = 6.28318530717958647692528676655900576839433879875021164195;

//
// num (scalars)
//

function num_abs(n){
	return n < 0 ? -n : n;
}

function num_acos(n){
	return Math.acos(n);
}

function num_asin(n){
	return Math.asin(n);
}

function num_atan2(a, b){
	return Math.atan2(a, b);
}

function num_ceil(a){
	return Math.ceil(a);
}

function num_clamp(n, min, max){
	return n < min ? min : (n > max ? max : n);
}

function num_cos(n){
	return Math.cos(n);
}

function num_floor(a){
	return Math.floor(a);
}

function num_lerp(a, b, t){
	return a + (b - a) * t;
}

function num_log(n){
	return Math.log(n);
}

function num_max(a, b){
	return a > b ? a : b;
}

function num_min(a, b){
	return a > b ? b : a;
}

function num_mod(a, b){
	return a % b;
}

function num_pow(a, b){
	return Math.pow(a, b);
}

function num_round(a){
	return Math.round(a);
}

function num_sin(n){
	return Math.sin(n);
}

function num_sqrt(n){
	return Math.sqrt(n);
}

function num_tan(n){
	return Math.tan(n);
}

//
// vec2
//

function vec2_add(a, b){
	return [a[0] + b[0], a[1] + b[1]];
}

function vec2_applymat2(a, b){
	var ax = a[0], ay = a[1];
	return [b[0] * ax + b[2] * ay, b[1] * ax + b[3] * ay];
}

function vec2_applymat3x2(a, b){
	var ax = a[0], ay = a[1];
	return [b[0] * ax + b[2] * ay + b[4], b[1] * ax + b[3] * ay + b[5]];
}

function vec2_applymat3(a, b){
	var ax = a[0], ay = a[1];
	return [b[0] * ax + b[3] * ay + b[6], b[1] * ax + b[4] * ay + b[7]];
}

function vec2_applymat4(a, b){
	var ax = a[0], ay = a[1];
	return [b[0] * ax + b[4] * ay + b[12], b[1] * ax + b[5] * ay + b[13]];
}

function vec2_clamp(a, min, max){
	return [num_clamp(a[0], min[0], max[0]), num_clamp(a[1], min[1], max[1])];
}

function vec2_dist(a, b){
	return num_sqrt(vec2_len2(vec2_sub(a, b)));
}

function vec2_dist2(a, b){
	return vec2_len2(vec2_sub(b, a));
}

function vec2_div(a, b){
	return [a[0] / b[0], a[1] / b[1]];
}

function vec2_dot(a, b){
	return a[0] * b[0] + a[1] * b[1];
}

function vec2_inverse(a){
	return [1 / a[0], 1 / a[1]];
}

function vec2_len(a){
	return num_sqrt(vec2_len2(a));
}

function vec2_len2(a){
	var ax = a[0], ay = a[1];
	return ax * ax + ay * ay;
}

function vec2_lerp(a, b, t){
	return [num_lerp(a[0], b[0], t), num_lerp(a[1], b[1], t)];
}

function vec2_max(a, b){
	return [num_max(a[0], b[0]), num_max(a[1], b[1])];
}

function vec2_min(a, b){
	return [num_min(a[0], b[0]), num_min(a[1], b[1])];
}

function vec2_mul(a, b){
	return [a[0] * b[0], a[1] * b[1]];
}

function vec2_neg(a){
	return [-a[0], -a[1]];
}

function vec2_normal(a){
	var ax = a[0], ay = a[1],
		len = ax * ax + ay * ay;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len];
	}
	return a;
}

function vec2_scale(a, s){
	return [a[0] * s, a[1] * s];
}

function vec2_sub(a, b){
	return [a[0] - b[0], a[1] - b[1]];
}

//
// vec3
//

function vec3_add(a, b){
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
}

function vec3_angle(a, b){
	return vec3_nangle(vec3_normal(a), vec3_normal(b));
}

function vec3_applymat3x2(a, b){
	var ax = a[0], ay = a[1], az = a[2];
	return [
		ax * b[0] + ay * b[2] + az * b[4],
		ax * b[1] + ay * b[3] + az * b[5],
		az
	];
}

function vec3_applymat3(a, b){
	var ax = a[0], ay = a[1], az = a[2];
	return [
		ax * b[0] + ay * b[3] + az * b[6],
		ax * b[1] + ay * b[4] + az * b[7],
		ax * b[2] + ay * b[5] + az * b[8]
	];
}

function vec3_applymat4(a, b){
	var ax = a[0], ay = a[1], az = a[2];
	var w = b[ 3] * ax + b[ 7] * ay + b[11] * az + b[15];
	if (w == 0)
		w = 1;
	return [
		(b[0] * ax + b[4] * ay + b[ 8] * az + b[12]) / w,
		(b[1] * ax + b[5] * ay + b[ 9] * az + b[13]) / w,
		(b[2] * ax + b[6] * ay + b[10] * az + b[14]) / w
	];
}

function vec3_applyquat(a, b){
	var
		ax = a[0], ay = a[1], az = a[2],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	var
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

function vec3_clamp(a, min, max){
	return [
		num_clamp(a[0], min[0], max[0]),
		num_clamp(a[1], min[1], max[1]),
		num_clamp(a[2], min[2], max[2])
	];
}

function vec3_cross(a, b){
	var
		ax = a[0], ay = a[1], az = a[2],
		bx = b[0], by = b[1], bz = b[2];
	return [ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx];
}

function vec3_dist(a, b){
	return num_sqrt(vec3_len2(vec3_sub(a, b)));
}

function vec3_dist2(a, b){
	return vec3_len2(vec3_sub(b, a));
}

function vec3_div(a, b){
	return [a[0] / b[0], a[1] / b[1], a[2] / b[2]];
}

function vec3_dot(a, b){
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

function vec3_inverse(a){
	return [1 / a[0], 1 / a[1], 1 / a[2]];
}

function vec3_len(a){
	return num_sqrt(vec3_len2(a));
}

function vec3_len2(a){
	var ax = a[0], ay = a[1], az = a[2];
	return ax * ax + ay * ay + az * az;
}

function vec3_lerp(a, b, t){
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t)
	];
}

function vec3_max(a, b){
	return [num_max(a[0], b[0]), num_max(a[1], b[1]), num_max(a[2], b[2])];
}

function vec3_min(a, b){
	return [num_min(a[0], b[0]), num_min(a[1], b[1]), num_min(a[2], b[2])];
}

function vec3_mul(a, b){
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2]];
}

function vec3_nangle(a, b){ // a and b are normalized
	var c = vec3_dot(a, b);
	if (c < -1 || c > 1)
		return 0;
	return num_acos(c);
}

function vec3_neg(a){
	return [-a[0], -a[1], -a[2]];
}

function vec3_normal(a){
	var ax = a[0], ay = a[1], az = a[2];
	var len = ax * ax + ay * ay + az * az;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len];
	}
	return a;
}

function vec3_orthogonal(a, b){
	return vec3_normal(vec3_cross(a, b));
}

function vec3_scale(a, s){
	return [a[0] * s, a[1] * s, a[2] * s];
}

function vec3_sub(a, b){
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
}

//
// vec4
//

function vec4_add(a, b){
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]];
}

function vec4_applymat4(a, b){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	return [
		b[0] * ax + b[4] * ay + b[ 8] * az + b[12] * aw,
		b[1] * ax + b[5] * ay + b[ 9] * az + b[13] * aw,
		b[2] * ax + b[6] * ay + b[10] * az + b[14] * aw,
		b[3] * ax + b[7] * ay + b[11] * az + b[15] * aw
	];
}

function vec4_applyquat(a, b){
	var
		ax = a[0], ay = a[1], az = a[2], aw = a[3],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	var
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

function vec4_clamp(a, min, max){
	return [
		num_clamp(a[0], min[0], max[0]),
		num_clamp(a[1], min[1], max[1]),
		num_clamp(a[2], min[2], max[2]),
		num_clamp(a[3], min[3], max[3])
	];
}

function vec4_dist(a, b){
	return num_sqrt(vec4_len2(vec4_sub(a, b)));
}

function vec4_dist2(a, b){
	return vec4_len2(vec4_sub(b, a));
}

function vec4_div(a, b){
	return [a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]];
}

function vec4_dot(a, b){
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

function vec4_inverse(a){
	return [1 / a[0], 1 / a[1], 1 / a[2], 1 / a[3]];
}

function vec4_len(a){
	return num_sqrt(vec4_len2(a));
}

function vec4_len2(a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	return ax * ax + ay * ay + az * az + aw * aw;
}

function vec4_lerp(a, b, t){
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t),
		num_lerp(a[3], b[3], t)
	];
}

function vec4_max(a, b){
	return [
		num_max(a[0], b[0]),
		num_max(a[1], b[1]),
		num_max(a[2], b[2]),
		num_max(a[3], b[3])
	];
}

function vec4_min(a, b){
	return [
		num_min(a[0], b[0]),
		num_min(a[1], b[1]),
		num_min(a[2], b[2]),
		num_min(a[3], b[3])
	];
}

function vec4_mul(a, b){
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]];
}

function vec4_neg(a){
	return [-a[0], -a[1], -a[2], -a[3]];
}

function vec4_normal(a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	var len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len, aw * len];
	}
	return a;
}

function vec4_scale(a, s){
	return [a[0] * s, a[1] * s, a[2] * s, a[3] * s];
}


function vec4_sub(a, b){
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]];
}

//
// quat
//

function quat_axisang(axis, ang){
	return quat_naxisang(vec3_normal(axis), ang);
}

function quat_between(from, to){
	return quat_nbetween(vec3_normal(from), vec3_normal(to));
}

function quat_dot(a, b){
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

function quat_euler_xyz(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

function quat_euler_xzy(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

function quat_euler_yxz(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

function quat_euler_yzx(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz + cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

function quat_euler_zxy(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz + sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	];
}

function quat_euler_zyx(rot){
	var a0 = rot[0] * 0.5;
	var a1 = rot[1] * 0.5;
	var a2 = rot[2] * 0.5;
	var cx = num_cos(a0);
	var cy = num_cos(a1);
	var cz = num_cos(a2);
	var sx = num_sin(a0);
	var sy = num_sin(a1);
	var sz = num_sin(a2);
	return [
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	];
}

function quat_identity(){
	return [0, 0, 0, 1];
}

function quat_invert(a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	var dot = ax * ax + ay * ay + az * az + aw * aw;
	var invDot = 0;
	if (dot != 0)
		invDot = 1 / dot;
	return [
		-ax * invDot,
		-ay * invDot,
		-az * invDot,
		 aw * invDot
	];
}

function quat_lerp(a, b, t){
	return [
		num_lerp(a[0], b[0], t),
		num_lerp(a[1], b[1], t),
		num_lerp(a[2], b[2], t),
		num_lerp(a[3], b[3], t)
	];
}

function quat_mul(a, b){
	var
		ax = a[0], ay = a[1], az = a[2], aw = a[3],
		bx = b[0], by = b[1], bz = b[2], bw = b[3];
	return [
		ax * bw + aw * bx + ay * bz - az * by,
		ay * bw + aw * by + az * bx - ax * bz,
		az * bw + aw * bz + ax * by - ay * bx,
		aw * bw - ax * bx - ay * by - az * bz
	];
}

function quat_naxisang(axis, ang){ // axis is normalized
	ang *= 0.5;
	var s = num_sin(ang);
	return [axis[0] * s, axis[1] * s, axis[2] * s, num_cos(ang)];
}

function quat_nbetween(from, to){ // from/to are normalized
	var r = vec3_dot(from, to) + 1;
	var cross;
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

function quat_neg(a){
	return [-a[0], -a[1], -a[2], -a[3]];
}

function quat_nlerp(a, b, t){
	return quat_normal(quat_lerp(a, b, t));
}

function quat_normal(a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	var len = ax * ax + ay * ay + az * az + aw * aw;
	if (len > 0){
		len = 1 / num_sqrt(len);
		return [ax * len, ay * len, az * len, aw * len];
	}
	return a;
}

function quat_slerp(a, b, t){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3];
	var bx = b[0], by = b[1], bz = b[2], bw = b[3];
	var omega, cosom, sinom, scale0, scale1;
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

function mat2_add(a, b){
	return [a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]];
}

function mat2_adjoint(a){
	return [a[3], -a[1], -a[2], a[0]];
}

function mat2_compmul(a, b){
	return [a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]];
}

function mat2_det(a){
	return a[0] * a[3] - a[2] * a[1];
}

function mat2_identity(){
	return [1, 0, 0, 1];
}

function mat2_invert(a){
	var a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
	var det = a0 * a3 - a2 * a1;
	if (det == 0)
		return [0, 0, 0, 0];
	det = 1 / det;
	return [a3 * det, -a1 * det, -a2 * det, a0 * det];
}

function mat2_mul(a, b){
	var
		a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3],
		b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
	return [a0 * b0 + a2 * b1, a1 * b0 + a3 * b1, a0 * b2 + a2 * b3, a1 * b2 + a3 * b3];
}

function mat2_rotate(a, ang){
	var a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], s = num_sin(ang), c = num_cos(ang);
	return [a0 * c + a2 * s, a1 * c + a3 * s, a0 * -s + a2 * c, a1 * -s + a3 * c];
}

function mat2_rotation(ang){
	var s = num_sin(ang), c = num_cos(ang);
	return [c, s, -s, c];
}

function mat2_scale(a, b){
	var
		a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3],
		b0 = b[0], b1 = b[1];
	return [a0 * b0, a1 * b0, a2 * b1, a3 * b1];
}

function mat2_scaling(a){
	return [a[0], 0, 0, a[1]];
}

function mat2_sub(a, b){
	return [a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]];
}

function mat2_transpose(a){
	return [a[0], a[2], a[1], a[3]];
}

//
// mat3x2
//

function mat3x2_add(a, b){
	return [
		a[0] + b[0], a[1] + b[1],
		a[2] + b[2], a[3] + b[3],
		a[4] + b[4], a[5] + b[5]
	];
}

function mat3x2_compmul(a, b){
	return [
		a[0] * b[0], a[1] * b[1],
		a[2] * b[2], a[3] * b[3],
		a[4] * b[4], a[5] * b[5]
	];
}

function mat3x2_det(a){
	return a[0] * a[3] - a[2] * a[1];
}

function mat3x2_identity(){
	return [1, 0, 0, 1, 0, 0];
}

function mat3x2_invert(a){
	var
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		a20 = a[4], a21 = a[5];
	var det = a00 * a11 - a01 * a10;
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

function mat3x2_mul(a, b){
	var
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

function mat3x2_rotate(a, ang){
	var
		a00 = a[0], a01 = a[1],
		a10 = a[2], a11 = a[3],
		s = num_sin(ang), c = num_cos(ang);
	return [
		c * a00 + s * a10, c * a01 + s * a11,
		c * a10 - s * a00, c * a11 - s * a01,
		a[4], a[5]
	];
}

function mat3x2_rotation(ang){
	var s = num_sin(ang), c = num_cos(ang);
	return [c, s, -s, c, 0, 0];
}

function mat3x2_scale(a, b){
	var bx = b[0], by = b[1];
	return [
		bx * a[0], bx * a[1],
		by * a[2], by * a[3],
		a[4], a[5],
	];
}

function mat3x2_scaling(a){
	return [a[0], 0, 0, a[1], 0, 0];
}

function mat3x2_sub(a, b){
	return [
		a[0] - b[0], a[1] - b[1],
		a[2] - b[2], a[3] - b[3],
		a[4] - b[4], a[5] - b[5]
	];
}

function mat3x2_translate(a, b){
	var
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

function mat3x2_translation(a){
	return [1, 0, 0, 1, a[0], a[1]];
}

//
// mat3
//

function mat3_add(out, a, b){
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

function mat3_adjoint(out, a){
	var
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

function mat3_compmul(out, a, b){
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

function mat3_copy(out, a){
	out[0] = a[0]; out[1] = a[1]; out[2] = a[2];
	out[3] = a[3]; out[4] = a[4]; out[5] = a[5];
	out[6] = a[6]; out[7] = a[7]; out[8] = a[8];
	return out;
}

function mat3_det(a){
	var
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8];
	return
		a00 * ( a22 * a11 - a12 * a21) +
		a01 * (-a22 * a10 + a12 * a20) +
		a02 * ( a21 * a10 - a11 * a20);
}

function mat3_identity(out){
	if (typeof out === 'undefined')
		out = [];
	out[0] = 1; out[1] = 0; out[2] = 0;
	out[3] = 0; out[4] = 1; out[5] = 0;
	out[6] = 0; out[7] = 0; out[8] = 1;
	return out;
}

function mat3_invert(out, a){
	var
		a00 = a[0], a01 = a[1], a02 = a[2],
		a10 = a[3], a11 = a[4], a12 = a[5],
		a20 = a[6], a21 = a[7], a22 = a[8],
		b01 =  a22 * a11 - a12 * a21,
		b11 = -a22 * a10 + a12 * a20,
		b21 =  a21 * a10 - a11 * a20;
	var det = a00 * b01 + a01 * b11 + a02 * b21;
	if (det == 0)
		return null;
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

function mat3_mul(out, a, b){
	var
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

function mat3_quat(out, a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3],
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

function mat3_rotate(out, a, ang){
	var
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

function mat3_rotation(out, ang){
	var s = num_sin(ang), c = num_cos(ang);
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

function mat3_scale(out, a, b){
	var bx = b[0], by = b[1];
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

function mat3_scaling(out, a){
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

function mat3_sub(out, a, b){
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

function mat3_translate(out, a, b){
	var
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

function mat3_translation(out, a){
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

function mat3_transpose(out, a){
	if (out === a) {
		var a01 = a[1], a02 = a[2], a12 = a[5];
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

function mat4_add(out, a, b){
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

function mat4_adjoint(out, a){
	var
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

function mat4_compmul(out, a, b){
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

function mat4_copy(out, a){
	out[ 0] = a[ 0]; out[ 1] = a[ 1]; out[ 2] = a[ 2]; out[ 3] = a[ 3];
	out[ 4] = a[ 4]; out[ 5] = a[ 5]; out[ 6] = a[ 6]; out[ 7] = a[ 7];
	out[ 8] = a[ 8]; out[ 9] = a[ 9]; out[10] = a[10]; out[11] = a[11];
	out[12] = a[12]; out[13] = a[13]; out[14] = a[14]; out[15] = a[15];
	return out;
}

function mat4_det(a){
	var
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

function mat4_frustum(out, L, R, B, T, N, F){
	var
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

function mat4_identity(out){
	if (typeof out === 'undefined')
		out = [];
	out[ 0] = 1; out[ 1] = 0; out[ 2] = 0; out[ 3] = 0;
	out[ 4] = 0; out[ 5] = 1; out[ 6] = 0; out[ 7] = 0;
	out[ 8] = 0; out[ 9] = 0; out[10] = 1; out[11] = 0;
	out[12] = 0; out[13] = 0; out[14] = 0; out[15] = 1;
	return out;
}

function mat4_invert(out, a){
	var
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
	var det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
	if (det == 0)
		return null;
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

function mat4_lookat(out, eye, position, up){
	var
		ex = eye[0], ey = eye[1], ez = eye[2],
		ux = up[0], uy = up[1], uz = up[2],
		px = position[0], py = position[1], pz = position[2];
	var z0 = ex - px, z1 = ey - py, z2 = ez - pz;
	if (z0 == 0 && z1 == 0 && z2 == 0)
		return mat4_identity(out);
	var len = 1 / num_sqrt(z0 * z0 + z1 * z1 + z2 * z2);
	z0 *= len;
	z1 *= len;
	z2 *= len;
	var x0 = uy * z2 - uz * z1;
	var x1 = uz * z0 - ux * z2;
	var x2 = ux * z1 - uy * z0;
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
	var y0 = z1 * x2 - z2 * x1;
	var y1 = z2 * x0 - z0 * x2;
	var y2 = z0 * x1 - z1 * x0;
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

function mat4_mul(out, a, b){
	var
		a00 = a[ 0], a01 = a[ 1], a02 = a[ 2], a03 = a[ 3],
		a10 = a[ 4], a11 = a[ 5], a12 = a[ 6], a13 = a[ 7],
		a20 = a[ 8], a21 = a[ 9], a22 = a[10], a23 = a[11],
		a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];
	var b0, b1, b2, b3;
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

function mat4_orthogonal(out, W, H, N, F){
	var nf = 1 / (N - F);
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

function mat4_perspective(out, fov, width, height, N, F){
	var
		f  = 1 / num_tan(fov * 0.5),
		nf = 1 / (N - F);
	out[ 0] = f;
	out[ 1] = 0;
	out[ 2] = 0;
	out[ 3] = 0;
	out[ 4] = 0;
	out[ 5] = f * width / height;
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

function mat4_quat(out, a){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3],
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

function mat4_rotate(out, a, axis, ang){
	var
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

function mat4_rotation(out, ang){
	var x = axis[0], y = axis[1], z = axis[2],
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

function mat4_rottrans(out, a, b){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3],
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

function mat4_rottransorigin(out, a, b, origin){
	var ax = a[0], ay = a[1], az = a[2], aw = a[3],
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

function mat4_scale(out, a, b){
	var bx = b[0], by = b[1], bz = b[2];
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

function mat4_scaling(out, a){
	out[ 0] = a[0]; out[ 1] =    0; out[ 2] =    0; out[ 3] = 0;
	out[ 4] =    0; out[ 5] = a[1]; out[ 6] =    0; out[ 7] = 0;
	out[ 8] =    0; out[ 9] =    0; out[10] = a[2]; out[11] = 0;
	out[12] =    0; out[13] =    0; out[14] =    0; out[15] = 1;
	return out;
}

function mat4_sub(out, a, b){
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

function mat4_translate(out, a, b){
	var bx = b[0], by = b[1], bz = b[2];
	if (out === a){
		out[12] = a[0] * bx + a[4] * by + a[ 8] * bz + a[12];
		out[13] = a[1] * bx + a[5] * by + a[ 9] * bz + a[13];
		out[14] = a[2] * bx + a[6] * by + a[10] * bz + a[14];
		out[15] = a[3] * bx + a[7] * by + a[11] * bz + a[15];
	}
	else{
		var
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

function mat4_translation(out, a){
	out[ 0] = 1; out[ 1] = 0; out[ 2] = 0; out[ 3] = 0;
	out[ 4] = 0; out[ 5] = 1; out[ 6] = 0; out[ 7] = 0;
	out[ 8] = 0; out[ 9] = 0; out[10] = 1; out[11] = 0;
	out[12] = a[0]; out[13] = a[1]; out[14] = a[2]; out[15] = 1;
	return out;
}

function mat4_transpose(out, a){
	if (out === a){
		var
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

if (typeof module !== 'undefined' && module.exports){
	// inside node.js, so export functions into global namespace
	global.TAU = TAU;

	// num (scalars)
	global.num_abs   = num_abs  ;
	global.num_acos  = num_acos ;
	global.num_asin  = num_asin ;
	global.num_atan2 = num_atan2;
	global.num_ceil  = num_ceil ;
	global.num_clamp = num_clamp;
	global.num_cos   = num_cos  ;
	global.num_floor = num_floor;
	global.num_lerp  = num_lerp ;
	global.num_log   = num_log  ;
	global.num_max   = num_max  ;
	global.num_min   = num_min  ;
	global.num_mod   = num_mod  ;
	global.num_pow   = num_pow  ;
	global.num_round = num_round;
	global.num_sin   = num_sin  ;
	global.num_sqrt  = num_sqrt ;
	global.num_tan   = num_tan  ;

	// vec2
	global.vec2_add         = vec2_add      ;
	global.vec2_applymat2   = vec2_applymat2;
	global.vec2_applymat3x2 = vec2_applymat3x2;
	global.vec2_applymat3   = vec2_applymat3;
	global.vec2_applymat4   = vec2_applymat4;
	global.vec2_clamp       = vec2_clamp    ;
	global.vec2_dist        = vec2_dist     ;
	global.vec2_dist2       = vec2_dist2    ;
	global.vec2_div         = vec2_div      ;
	global.vec2_dot         = vec2_dot      ;
	global.vec2_inverse     = vec2_inverse  ;
	global.vec2_len         = vec2_len      ;
	global.vec2_len2        = vec2_len2     ;
	global.vec2_lerp        = vec2_lerp     ;
	global.vec2_max         = vec2_max      ;
	global.vec2_min         = vec2_min      ;
	global.vec2_mul         = vec2_mul      ;
	global.vec2_neg         = vec2_neg      ;
	global.vec2_normal      = vec2_normal   ;
	global.vec2_scale       = vec2_scale    ;
	global.vec2_sub         = vec2_sub      ;

	// vec3
	global.vec3_add         = vec3_add      ;
	global.vec3_angle       = vec3_angle    ;
	global.vec3_applymat3x2 = vec3_applymat3x2;
	global.vec3_applymat3   = vec3_applymat3;
	global.vec3_applymat4   = vec3_applymat4;
	global.vec3_applyquat   = vec3_applyquat;
	global.vec3_clamp       = vec3_clamp    ;
	global.vec3_cross       = vec3_cross    ;
	global.vec3_div         = vec3_div      ;
	global.vec3_dist        = vec3_dist     ;
	global.vec3_dist2       = vec3_dist2    ;
	global.vec3_dot         = vec3_dot      ;
	global.vec3_inverse     = vec3_inverse  ;
	global.vec3_len         = vec3_len      ;
	global.vec3_len2        = vec3_len2     ;
	global.vec3_lerp        = vec3_lerp     ;
	global.vec3_max         = vec3_max      ;
	global.vec3_min         = vec3_min      ;
	global.vec3_mul         = vec3_mul      ;
	global.vec3_nangle      = vec3_nangle   ;
	global.vec3_neg         = vec3_neg      ;
	global.vec3_normal      = vec3_normal   ;
	global.vec3_scale       = vec3_scale    ;
	global.vec3_sub         = vec3_sub      ;

	// vec4
	global.vec4_add       = vec4_add      ;
	global.vec4_applymat4 = vec4_applymat4;
	global.vec4_applyquat = vec4_applyquat;
	global.vec4_clamp     = vec4_clamp    ;
	global.vec4_dist      = vec4_dist     ;
	global.vec4_dist2     = vec4_dist2    ;
	global.vec4_div       = vec4_div      ;
	global.vec4_dot       = vec4_dot      ;
	global.vec4_inverse   = vec4_inverse  ;
	global.vec4_len       = vec4_len      ;
	global.vec4_len2      = vec4_len2     ;
	global.vec4_lerp      = vec4_lerp     ;
	global.vec4_max       = vec4_max      ;
	global.vec4_min       = vec4_min      ;
	global.vec4_mul       = vec4_mul      ;
	global.vec4_neg       = vec4_neg      ;
	global.vec4_normal    = vec4_normal   ;
	global.vec4_scale     = vec4_scale    ;
	global.vec4_sub       = vec4_sub      ;

	// quat
	global.quat_axisang   = quat_axisang  ;
	global.quat_between   = quat_between  ;
	global.quat_dot       = quat_dot      ;
	global.quat_euler_xyz = quat_euler_xyz;
	global.quat_euler_xzy = quat_euler_xzy;
	global.quat_euler_yxz = quat_euler_yxz;
	global.quat_euler_yzx = quat_euler_yzx;
	global.quat_euler_zxy = quat_euler_zxy;
	global.quat_euler_zyx = quat_euler_zyx;
	global.quat_identity  = quat_identity ;
	global.quat_invert    = quat_invert   ;
	global.quat_lerp      = quat_lerp     ;
	global.quat_mul       = quat_mul      ;
	global.quat_naxisang  = quat_naxisang ;
	global.quat_nbetween  = quat_nbetween ;
	global.quat_neg       = quat_neg      ;
	global.quat_nlerp     = quat_nlerp    ;
	global.quat_normal    = quat_normal   ;
	global.quat_slerp     = quat_slerp    ;

	// mat2
	global.mat2_add       = mat2_add      ;
	global.mat2_adjoint   = mat2_adjoint  ;
	global.mat2_compmul   = mat2_compmul  ;
	global.mat2_det       = mat2_det      ;
	global.mat2_identity  = mat2_identity ;
	global.mat2_invert    = mat2_invert   ;
	global.mat2_mul       = mat2_mul      ;
	global.mat2_rotate    = mat2_rotate   ;
	global.mat2_rotation  = mat2_rotation ;
	global.mat2_scale     = mat2_scale    ;
	global.mat2_scaling   = mat2_scaling  ;
	global.mat2_sub       = mat2_sub      ;
	global.mat2_transpose = mat2_transpose;

	// mat3x2
	global.mat3x2_add         = mat3x2_add        ;
	global.mat3x2_compmul     = mat3x2_compmul    ;
	global.mat3x2_det         = mat3x2_det        ;
	global.mat3x2_identity    = mat3x2_identity   ;
	global.mat3x2_invert      = mat3x2_invert     ;
	global.mat3x2_mul         = mat3x2_mul        ;
	global.mat3x2_rotate      = mat3x2_rotate     ;
	global.mat3x2_rotation    = mat3x2_rotation   ;
	global.mat3x2_scale       = mat3x2_scale      ;
	global.mat3x2_scaling     = mat3x2_scaling    ;
	global.mat3x2_sub         = mat3x2_sub        ;
	global.mat3x2_translate   = mat3x2_translate  ;
	global.mat3x2_translation = mat3x2_translation;

	// mat3
	global.mat3_add         = mat3_add        ;
	global.mat3_adjoint     = mat3_adjoint    ;
	global.mat3_compmul     = mat3_compmul    ;
	global.mat3_copy        = mat3_copy       ;
	global.mat3_det         = mat3_det        ;
	global.mat3_identity    = mat3_identity   ;
	global.mat3_invert      = mat3_invert     ;
	global.mat3_mul         = mat3_mul        ;
	global.mat3_quat        = mat3_quat       ;
	global.mat3_rotate      = mat3_rotate     ;
	global.mat3_rotation    = mat3_rotation   ;
	global.mat3_scale       = mat3_scale      ;
	global.mat3_scaling     = mat3_scaling    ;
	global.mat3_sub         = mat3_sub        ;
	global.mat3_translate   = mat3_translate  ;
	global.mat3_translation = mat3_translation;
	global.mat3_transpose   = mat3_transpose  ;

	// mat4
	global.mat4_add            = mat4_add           ;
	global.mat4_adjoint        = mat4_adjoint       ;
	global.mat4_compmul        = mat4_compmul       ;
	global.mat4_copy           = mat4_copy          ;
	global.mat4_det            = mat4_det           ;
	global.mat4_frustum        = mat4_frustum       ;
	global.mat4_identity       = mat4_identity      ;
	global.mat4_invert         = mat4_invert        ;
	global.mat4_lookat         = mat4_lookat        ;
	global.mat4_mul            = mat4_mul           ;
	global.mat4_orthogonal     = mat4_orthogonal    ;
	global.mat4_perspective    = mat4_perspective   ;
	global.mat4_quat           = mat4_quat          ;
	global.mat4_rotate         = mat4_rotate        ;
	global.mat4_rotation       = mat4_rotation      ;
	global.mat4_rottrans       = mat4_rottrans      ;
	global.mat4_rottransorigin = mat4_rottransorigin;
	global.mat4_scale          = mat4_scale         ;
	global.mat4_scaling        = mat4_scaling       ;
	global.mat4_sub            = mat4_sub           ;
	global.mat4_translate      = mat4_translate     ;
	global.mat4_translation    = mat4_translation   ;
	global.mat4_transpose      = mat4_transpose     ;
}
