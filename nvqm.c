/* (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
 * MIT License
 * Project Home: https://github.com/voidqk/nvqm
 */

#include "nvqm.h"

#ifndef NVQM_SKIP_FLOATING_POINT

/*
 * mat3
 */

mat3 *mat3_add(mat3 *out, mat3 *a, mat3 *b){
	out->v[0] = a->v[0] + b->v[0];
	out->v[1] = a->v[1] + b->v[1];
	out->v[2] = a->v[2] + b->v[2];
	out->v[3] = a->v[3] + b->v[3];
	out->v[4] = a->v[4] + b->v[4];
	out->v[5] = a->v[5] + b->v[5];
	out->v[6] = a->v[6] + b->v[6];
	out->v[7] = a->v[7] + b->v[7];
	out->v[8] = a->v[8] + b->v[8];
	return out;
}

mat3 *mat3_adjoint(mat3 *out, mat3 *a){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8];
	out->v[0] = a11 * a22 - a12 * a21;
	out->v[1] = a02 * a21 - a01 * a22;
	out->v[2] = a01 * a12 - a02 * a11;
	out->v[3] = a12 * a20 - a10 * a22;
	out->v[4] = a00 * a22 - a02 * a20;
	out->v[5] = a02 * a10 - a00 * a12;
	out->v[6] = a10 * a21 - a11 * a20;
	out->v[7] = a01 * a20 - a00 * a21;
	out->v[8] = a00 * a11 - a01 * a10;
	return out;
}

mat3 *mat3_compmul(mat3 *out, mat3 *a, mat3 *b){
	out->v[0] = a->v[0] * b->v[0];
	out->v[1] = a->v[1] * b->v[1];
	out->v[2] = a->v[2] * b->v[2];
	out->v[3] = a->v[3] * b->v[3];
	out->v[4] = a->v[4] * b->v[4];
	out->v[5] = a->v[5] * b->v[5];
	out->v[6] = a->v[6] * b->v[6];
	out->v[7] = a->v[7] * b->v[7];
	out->v[8] = a->v[8] * b->v[8];
	return out;
}

mat3 *mat3_copy(mat3 *out, mat3 *a){
	out->v[0] = a->v[0]; out->v[1] = a->v[1]; out->v[2] = a->v[2];
	out->v[3] = a->v[3]; out->v[4] = a->v[4]; out->v[5] = a->v[5];
	out->v[6] = a->v[6]; out->v[7] = a->v[7]; out->v[8] = a->v[8];
	return out;
}

float mat3_det(mat3 *a){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8];
	return
		a00 * ( a22 * a11 - a12 * a21) +
		a01 * (-a22 * a10 + a12 * a20) +
		a02 * ( a21 * a10 - a11 * a20);
}

mat3 *mat3_identity(mat3 *out){
	out->v[0] = 1.0f; out->v[1] = 0.0f; out->v[2] = 0.0f;
	out->v[3] = 0.0f; out->v[4] = 1.0f; out->v[5] = 0.0f;
	out->v[6] = 0.0f; out->v[7] = 0.0f; out->v[8] = 1.0f;
	return out;
}

mat3 *mat3_invert(mat3 *out, mat3 *a){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		b01 =  a22 * a11 - a12 * a21,
		b11 = -a22 * a10 + a12 * a20,
		b21 =  a21 * a10 - a11 * a20;
	float det = a00 * b01 + a01 * b11 + a02 * b21;
	if (det == 0.0f)
		return (mat3 *)0;
	det = 1.0f / det;
	out->v[0] =   b01                    * det;
	out->v[1] = (-a22 * a01 + a02 * a21) * det;
	out->v[2] = ( a12 * a01 - a02 * a11) * det;
	out->v[3] =   b11                    * det;
	out->v[4] = ( a22 * a00 - a02 * a20) * det;
	out->v[5] = (-a12 * a00 + a02 * a10) * det;
	out->v[6] =   b21                    * det;
	out->v[7] = (-a21 * a00 + a01 * a20) * det;
	out->v[8] = ( a11 * a00 - a01 * a10) * det;
	return out;
}

mat3 *mat3_mul(mat3 *out, mat3 *a, mat3 *b){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		b00 = b->v[0], b01 = b->v[1], b02 = b->v[2],
		b10 = b->v[3], b11 = b->v[4], b12 = b->v[5],
		b20 = b->v[6], b21 = b->v[7], b22 = b->v[8];
	out->v[0] = b00 * a00 + b01 * a10 + b02 * a20;
	out->v[1] = b00 * a01 + b01 * a11 + b02 * a21;
	out->v[2] = b00 * a02 + b01 * a12 + b02 * a22;
	out->v[3] = b10 * a00 + b11 * a10 + b12 * a20;
	out->v[4] = b10 * a01 + b11 * a11 + b12 * a21;
	out->v[5] = b10 * a02 + b11 * a12 + b12 * a22;
	out->v[6] = b20 * a00 + b21 * a10 + b22 * a20;
	out->v[7] = b20 * a01 + b21 * a11 + b22 * a21;
	out->v[8] = b20 * a02 + b21 * a12 + b22 * a22;
	return out;
}

mat3 *mat3_quat(mat3 *out, quat a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
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
	out->v[0] = 1.0f - ayy - azz;
	out->v[1] =        ayx + awz;
	out->v[2] =        azx - awy;
	out->v[3] =        ayx - awz;
	out->v[4] = 1.0f - axx - azz;
	out->v[5] =        azy + awx;
	out->v[6] =        azx + awy;
	out->v[7] =        azy - awx;
	out->v[8] = 1.0f - axx - ayy;
	return out;
}

mat3 *mat3_rotate(mat3 *out, mat3 *a, float ang){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		s = num_sin(ang), c = num_cos(ang);
	out->v[0] = c * a00 + s * a10;
	out->v[1] = c * a01 + s * a11;
	out->v[2] = c * a02 + s * a12;
	out->v[3] = c * a10 - s * a00;
	out->v[4] = c * a11 - s * a01;
	out->v[5] = c * a12 - s * a02;
	out->v[6] = a20;
	out->v[7] = a21;
	out->v[8] = a22;
	return out;
}

mat3 *mat3_rotation(mat3 *out, float ang){
	float s = num_sin(ang), c = num_cos(ang);
	out->v[0] =  c;
	out->v[1] =  s;
	out->v[2] =  0.0f;
	out->v[3] = -s;
	out->v[4] =  c;
	out->v[5] =  0.0f;
	out->v[6] =  0.0f;
	out->v[7] =  0.0f;
	out->v[8] =  1.0f;
	return out;
}

mat3 *mat3_scale(mat3 *out, mat3 *a, vec2 b){
	float bx = b.v[0], by = b.v[1];
	out->v[0] = bx * a->v[0];
	out->v[1] = bx * a->v[1];
	out->v[2] = bx * a->v[2];
	out->v[3] = by * a->v[3];
	out->v[4] = by * a->v[4];
	out->v[5] = by * a->v[5];
	out->v[6] = a->v[6];
	out->v[7] = a->v[7];
	out->v[8] = a->v[8];
	return out;
}

mat3 *mat3_scaling(mat3 *out, vec2 a){
	out->v[0] = a.v[0];
	out->v[1] = 0.0f;
	out->v[2] = 0.0f;
	out->v[3] = 0.0f;
	out->v[4] = a.v[1];
	out->v[5] = 0.0f;
	out->v[6] = 0.0f;
	out->v[7] = 0.0f;
	out->v[8] = 1.0f;
	return out;
}

mat3 *mat3_sub(mat3 *out, mat3 *a, mat3 *b){
	out->v[0] = a->v[0] - b->v[0];
	out->v[1] = a->v[1] - b->v[1];
	out->v[2] = a->v[2] - b->v[2];
	out->v[3] = a->v[3] - b->v[3];
	out->v[4] = a->v[4] - b->v[4];
	out->v[5] = a->v[5] - b->v[5];
	out->v[6] = a->v[6] - b->v[6];
	out->v[7] = a->v[7] - b->v[7];
	out->v[8] = a->v[8] - b->v[8];
	return out;
}

mat3 *mat3_translate(mat3 *out, mat3 *a, vec2 b){
	float
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		bx = b.v[0], by = b.v[1];
	out->v[0] = a00;
	out->v[1] = a01;
	out->v[2] = a02;
	out->v[3] = a10;
	out->v[4] = a11;
	out->v[5] = a12;
	out->v[6] = bx * a00 + by * a10 + a20;
	out->v[7] = bx * a01 + by * a11 + a21;
	out->v[8] = bx * a02 + by * a12 + a22;
	return out;
}

mat3 *mat3_translation(mat3 *out, vec2 a){
	out->v[0] = 1.0f;
	out->v[1] = 0.0f;
	out->v[2] = 0.0f;
	out->v[3] = 0.0f;
	out->v[4] = 1.0f;
	out->v[5] = 0.0f;
	out->v[6] = a.v[0];
	out->v[7] = a.v[1];
	out->v[8] = 1.0f;
	return out;
}

mat3 *mat3_transpose(mat3 *out, mat3 *a){
	if (out == a) {
		float a01 = a->v[1], a02 = a->v[2], a12 = a->v[5];
		out->v[1] = a->v[3];
		out->v[2] = a->v[6];
		out->v[3] = a01;
		out->v[5] = a->v[7];
		out->v[6] = a02;
		out->v[7] = a12;
	}
	else{
		out->v[0] = a->v[0];
		out->v[1] = a->v[3];
		out->v[2] = a->v[6];
		out->v[3] = a->v[1];
		out->v[4] = a->v[4];
		out->v[5] = a->v[7];
		out->v[6] = a->v[2];
		out->v[7] = a->v[5];
		out->v[8] = a->v[8];
	}
	return out;
}

/*
 * mat4
 */

mat4 *mat4_add(mat4 *out, mat4 *a, mat4 *b){
	out->v[ 0] = a->v[ 0] + b->v[ 0];
	out->v[ 1] = a->v[ 1] + b->v[ 1];
	out->v[ 2] = a->v[ 2] + b->v[ 2];
	out->v[ 3] = a->v[ 3] + b->v[ 3];
	out->v[ 4] = a->v[ 4] + b->v[ 4];
	out->v[ 5] = a->v[ 5] + b->v[ 5];
	out->v[ 6] = a->v[ 6] + b->v[ 6];
	out->v[ 7] = a->v[ 7] + b->v[ 7];
	out->v[ 8] = a->v[ 8] + b->v[ 8];
	out->v[ 9] = a->v[ 9] + b->v[ 9];
	out->v[10] = a->v[10] + b->v[10];
	out->v[11] = a->v[11] + b->v[11];
	out->v[12] = a->v[12] + b->v[12];
	out->v[13] = a->v[13] + b->v[13];
	out->v[14] = a->v[14] + b->v[14];
	out->v[15] = a->v[15] + b->v[15];
	return out;
}

mat4 *mat4_adjoint(mat4 *out, mat4 *a){
	float
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15];
	out->v[ 0] =  (
		a11 * (a22 * a33 - a23 * a32) -
		a21 * (a12 * a33 - a13 * a32) +
		a31 * (a12 * a23 - a13 * a22));
	out->v[ 1] = -(
		a01 * (a22 * a33 - a23 * a32) -
		a21 * (a02 * a33 - a03 * a32) +
		a31 * (a02 * a23 - a03 * a22));
	out->v[ 2] =  (
		a01 * (a12 * a33 - a13 * a32) -
		a11 * (a02 * a33 - a03 * a32) +
		a31 * (a02 * a13 - a03 * a12));
	out->v[ 3] = -(
		a01 * (a12 * a23 - a13 * a22) -
		a11 * (a02 * a23 - a03 * a22) +
		a21 * (a02 * a13 - a03 * a12));
	out->v[ 4] = -(
		a10 * (a22 * a33 - a23 * a32) -
		a20 * (a12 * a33 - a13 * a32) +
		a30 * (a12 * a23 - a13 * a22));
	out->v[ 5] =  (
		a00 * (a22 * a33 - a23 * a32) -
		a20 * (a02 * a33 - a03 * a32) +
		a30 * (a02 * a23 - a03 * a22));
	out->v[ 6] = -(
		a00 * (a12 * a33 - a13 * a32) -
		a10 * (a02 * a33 - a03 * a32) +
		a30 * (a02 * a13 - a03 * a12));
	out->v[ 7] =  (
		a00 * (a12 * a23 - a13 * a22) -
		a10 * (a02 * a23 - a03 * a22) +
		a20 * (a02 * a13 - a03 * a12));
	out->v[ 8] =  (
		a10 * (a21 * a33 - a23 * a31) -
		a20 * (a11 * a33 - a13 * a31) +
		a30 * (a11 * a23 - a13 * a21));
	out->v[ 9] = -(
		a00 * (a21 * a33 - a23 * a31) -
		a20 * (a01 * a33 - a03 * a31) +
		a30 * (a01 * a23 - a03 * a21));
	out->v[10] =  (
		a00 * (a11 * a33 - a13 * a31) -
		a10 * (a01 * a33 - a03 * a31) +
		a30 * (a01 * a13 - a03 * a11));
	out->v[11] = -(
		a00 * (a11 * a23 - a13 * a21) -
		a10 * (a01 * a23 - a03 * a21) +
		a20 * (a01 * a13 - a03 * a11));
	out->v[12] = -(
		a10 * (a21 * a32 - a22 * a31) -
		a20 * (a11 * a32 - a12 * a31) +
		a30 * (a11 * a22 - a12 * a21));
	out->v[13] =  (
		a00 * (a21 * a32 - a22 * a31) -
		a20 * (a01 * a32 - a02 * a31) +
		a30 * (a01 * a22 - a02 * a21));
	out->v[14] = -(
		a00 * (a11 * a32 - a12 * a31) -
		a10 * (a01 * a32 - a02 * a31) +
		a30 * (a01 * a12 - a02 * a11));
	out->v[15] =  (
		a00 * (a11 * a22 - a12 * a21) -
		a10 * (a01 * a22 - a02 * a21) +
		a20 * (a01 * a12 - a02 * a11));
	return out;
}

mat4 *mat4_compmul(mat4 *out, mat4 *a, mat4 *b){
	out->v[ 0] = a->v[ 0] * b->v[ 0];
	out->v[ 1] = a->v[ 1] * b->v[ 1];
	out->v[ 2] = a->v[ 2] * b->v[ 2];
	out->v[ 3] = a->v[ 3] * b->v[ 3];
	out->v[ 4] = a->v[ 4] * b->v[ 4];
	out->v[ 5] = a->v[ 5] * b->v[ 5];
	out->v[ 6] = a->v[ 6] * b->v[ 6];
	out->v[ 7] = a->v[ 7] * b->v[ 7];
	out->v[ 8] = a->v[ 8] * b->v[ 8];
	out->v[ 9] = a->v[ 9] * b->v[ 9];
	out->v[10] = a->v[10] * b->v[10];
	out->v[11] = a->v[11] * b->v[11];
	out->v[12] = a->v[12] * b->v[12];
	out->v[13] = a->v[13] * b->v[13];
	out->v[14] = a->v[14] * b->v[14];
	out->v[15] = a->v[15] * b->v[15];
	return out;
}

mat4 *mat4_copy(mat4 *out, mat4 *a){
	out->v[ 0] = a->v[ 0]; out->v[ 1] = a->v[ 1]; out->v[ 2] = a->v[ 2]; out->v[ 3] = a->v[ 3];
	out->v[ 4] = a->v[ 4]; out->v[ 5] = a->v[ 5]; out->v[ 6] = a->v[ 6]; out->v[ 7] = a->v[ 7];
	out->v[ 8] = a->v[ 8]; out->v[ 9] = a->v[ 9]; out->v[10] = a->v[10]; out->v[11] = a->v[11];
	out->v[12] = a->v[12]; out->v[13] = a->v[13]; out->v[14] = a->v[14]; out->v[15] = a->v[15];
	return out;
}

float mat4_det(mat4 *a){
	float
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15],
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

mat4 *mat4_frustum(mat4 *out, float L, float R, float B, float T, float N, float F){
	float
		rl = 1.0f / (R - L),
		tb = 1.0f / (T - B),
		nf = 1.0f / (N - F);
	out->v[ 0] = (2.0f * N) * rl;
	out->v[ 1] =  0.0f;
	out->v[ 2] =  0.0f;
	out->v[ 3] =  0.0f;
	out->v[ 4] =  0.0f;
	out->v[ 5] = (2.0f * N) * tb;
	out->v[ 6] =  0.0f;
	out->v[ 7] =  0.0f;
	out->v[ 8] = (R + L) * rl;
	out->v[ 9] = (T + B) * tb;
	out->v[10] = (F + N) * nf;
	out->v[11] = -1.0f;
	out->v[12] =  0.0f;
	out->v[13] =  0.0f;
	out->v[14] = (2.0f * N * F) * nf;
	out->v[15] =  0.0f;
	return out;
}

mat4 *mat4_identity(mat4 *out){
	out->v[ 0] = 1.0f; out->v[ 1] = 0.0f; out->v[ 2] = 0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] = 0.0f; out->v[ 5] = 1.0f; out->v[ 6] = 0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] = 0.0f; out->v[ 9] = 0.0f; out->v[10] = 1.0f; out->v[11] = 0.0f;
	out->v[12] = 0.0f; out->v[13] = 0.0f; out->v[14] = 0.0f; out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_invert(mat4 *out, mat4 *a){
	float
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15],
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
	float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
	if (det == 0.0f)
		return (mat4 *)0;
	det = 1.0f / det;
	out->v[ 0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
	out->v[ 1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
	out->v[ 2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
	out->v[ 3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
	out->v[ 4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
	out->v[ 5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
	out->v[ 6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
	out->v[ 7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
	out->v[ 8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
	out->v[ 9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
	out->v[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
	out->v[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
	out->v[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
	out->v[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
	out->v[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
	out->v[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
	return out;
}

mat4 *mat4_lookat(mat4 *out, vec3 eye, vec3 position, vec3 up){
	float
		ex = eye.v[0], ey = eye.v[1], ez = eye.v[2],
		ux = up.v[0], uy = up.v[1], uz = up.v[2],
		px = position.v[0], py = position.v[1], pz = position.v[2];
	float z0 = ex - px, z1 = ey - py, z2 = ez - pz;
	if (z0 == 0.0f && z1 == 0.0f && z2 == 0.0f)
		return mat4_identity(out);
	float len = 1.0f / num_sqrt(z0 * z0 + z1 * z1 + z2 * z2);
	z0 *= len;
	z1 *= len;
	z2 *= len;
	float x0 = uy * z2 - uz * z1;
	float x1 = uz * z0 - ux * z2;
	float x2 = ux * z1 - uy * z0;
	len = num_sqrt(
		x0 * x0 +
		x1 * x1 +
		x2 * x2
	);
	if (len == 0.0f){
		x0 = 0.0f;
		x1 = 0.0f;
		x2 = 0.0f;
	}
	else{
		len = 1.0f / len;
		x0 *= len;
		x1 *= len;
		x2 *= len;
	}
	float y0 = z1 * x2 - z2 * x1;
	float y1 = z2 * x0 - z0 * x2;
	float y2 = z0 * x1 - z1 * x0;
	len = num_sqrt(
		y0 * y0 +
		y1 * y1 +
		y2 * y2
	);
	if (len == 0.0f){
		y0 = 0.0f;
		y1 = 0.0f;
		y2 = 0.0f;
	}
	else{
		len = 1.0f / len;
		y0 *= len;
		y1 *= len;
		y2 *= len;
	}
	out->v[ 0] = x0;
	out->v[ 1] = y0;
	out->v[ 2] = z0;
	out->v[ 3] = 0.0f;
	out->v[ 4] = x1;
	out->v[ 5] = y1;
	out->v[ 6] = z1;
	out->v[ 7] = 0.0f;
	out->v[ 8] = x2;
	out->v[ 9] = y2;
	out->v[10] = z2;
	out->v[11] = 0.0f;
	out->v[12] = -(x0 * ex + x1 * ey + x2 * ez);
	out->v[13] = -(y0 * ex + y1 * ey + y2 * ez);
	out->v[14] = -(z0 * ex + z1 * ey + z2 * ez);
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_mul(mat4 *out, mat4 *a, mat4 *b){
	float
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15];
	float b0, b1, b2, b3;
	b0 = b->v[ 0];
	b1 = b->v[ 1];
	b2 = b->v[ 2];
	b3 = b->v[ 3];
	out->v[ 0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->v[ 1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->v[ 2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->v[ 3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b->v[ 4];
	b1 = b->v[ 5];
	b2 = b->v[ 6];
	b3 = b->v[ 7];
	out->v[ 4] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->v[ 5] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->v[ 6] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->v[ 7] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b->v[ 8];
	b1 = b->v[ 9];
	b2 = b->v[10];
	b3 = b->v[11];
	out->v[ 8] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->v[ 9] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->v[10] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->v[11] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	b0 = b->v[12];
	b1 = b->v[13];
	b2 = b->v[14];
	b3 = b->v[15];
	out->v[12] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->v[13] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->v[14] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->v[15] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
	return out;
}

mat4 *mat4_orthogonal(mat4 *out, float W, float H, float N, float F){
	float nf = 1.0f / (N - F);
	out->v[ 0] = 2.0f / W;
	out->v[ 1] = 0.0f;
	out->v[ 2] = 0.0f;
	out->v[ 3] = 0.0f;
	out->v[ 4] = 0.0f;
	out->v[ 5] = 2.0f / H;
	out->v[ 6] = 0.0f;
	out->v[ 7] = 0.0f;
	out->v[ 8] = 0.0f;
	out->v[ 9] = 0.0f;
	out->v[10] = 2.0f * nf;
	out->v[11] = 0.0f;
	out->v[12] = 0.0f;
	out->v[13] = 0.0f;
	out->v[14] = (N + F) * nf;
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_perspective(mat4 *out, float fov, float W, float H, float N, float F){
	float
		f  = 1.0f / num_tan(fov * 0.5f),
		nf = 1.0f / (N - F);
	out->v[ 0] = f;
	out->v[ 1] =  0.0f;
	out->v[ 2] =  0.0f;
	out->v[ 3] =  0.0f;
	out->v[ 4] =  0.0f;
	out->v[ 5] = f * W / H;
	out->v[ 6] =  0.0f;
	out->v[ 7] =  0.0f;
	out->v[ 8] =  0.0f;
	out->v[ 9] =  0.0f;
	out->v[10] = (F + N) * nf;
	out->v[11] = -1.0f;
	out->v[12] =  0.0f;
	out->v[13] =  0.0f;
	out->v[14] = (2.0f * F * N) * nf;
	out->v[15] =  0.0f;
	return out;
}

mat4 *mat4_quat(mat4 *out, quat a){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
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
	out->v[ 0] = 1.0f - ayy - azz;
	out->v[ 1] =        ayx + awz;
	out->v[ 2] =        azx - awy;
	out->v[ 3] = 0.0f;
	out->v[ 4] =        ayx - awz;
	out->v[ 5] = 1.0f - axx - azz;
	out->v[ 6] =        azy + awx;
	out->v[ 7] = 0.0f;
	out->v[ 8] =        azx + awy;
	out->v[ 9] =        azy - awx;
	out->v[10] = 1.0f - axx - ayy;
	out->v[11] = 0.0f;
	out->v[12] = 0.0f;
	out->v[13] = 0.0f;
	out->v[14] = 0.0f;
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_rotate(mat4 *out, mat4 *a, vec3 axis, float ang){
	float
		x = axis.v[0], y = axis.v[1], z = axis.v[2],
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[4], a11 = a->v[5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[8], a21 = a->v[9], a22 = a->v[10], a23 = a->v[11],
		s = num_sin(ang), c = num_cos(ang),
		t = 1.0f - c,
		b00 = x * x * t + c    , b01 = y * x * t + z * s, b02 = z * x * t - y * s,
		b10 = x * y * t - z * s, b11 = y * y * t + c    , b12 = z * y * t + x * s,
		b20 = x * z * t + y * s, b21 = y * z * t - x * s, b22 = z * z * t + c    ;
	out->v[ 0] = a00 * b00 + a10 * b01 + a20 * b02;
	out->v[ 1] = a01 * b00 + a11 * b01 + a21 * b02;
	out->v[ 2] = a02 * b00 + a12 * b01 + a22 * b02;
	out->v[ 3] = a03 * b00 + a13 * b01 + a23 * b02;
	out->v[ 4] = a00 * b10 + a10 * b11 + a20 * b12;
	out->v[ 5] = a01 * b10 + a11 * b11 + a21 * b12;
	out->v[ 6] = a02 * b10 + a12 * b11 + a22 * b12;
	out->v[ 7] = a03 * b10 + a13 * b11 + a23 * b12;
	out->v[ 8] = a00 * b20 + a10 * b21 + a20 * b22;
	out->v[ 9] = a01 * b20 + a11 * b21 + a21 * b22;
	out->v[10] = a02 * b20 + a12 * b21 + a22 * b22;
	out->v[11] = a03 * b20 + a13 * b21 + a23 * b22;
	if (out != a){
		out->v[12] = a->v[12];
		out->v[13] = a->v[13];
		out->v[14] = a->v[14];
		out->v[15] = a->v[15];
	}
	return out;
}

mat4 *mat4_rotation(mat4 *out, vec3 axis, float ang){
	float x = axis.v[0], y = axis.v[1], z = axis.v[2],
		s = num_sin(ang), c = num_cos(ang),
		t = 1.0f - c;
	out->v[ 0] = x * x * t + c;
	out->v[ 1] = y * x * t + z * s;
	out->v[ 2] = z * x * t - y * s;
	out->v[ 3] = 0.0f;
	out->v[ 4] = x * y * t - z * s;
	out->v[ 5] = y * y * t + c;
	out->v[ 6] = z * y * t + x * s;
	out->v[ 7] = 0.0f;
	out->v[ 8] = x * z * t + y * s;
	out->v[ 9] = y * z * t - x * s;
	out->v[10] = z * z * t + c;
	out->v[11] = 0.0f;
	out->v[12] = 0.0f;
	out->v[13] = 0.0f;
	out->v[14] = 0.0f;
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_rottrans(mat4 *out, quat a, vec3 b){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
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
	out->v[ 0] = 1.0f - ayy - azz;
	out->v[ 1] =        axy + awz;
	out->v[ 2] =        axz - awy;
	out->v[ 3] = 0.0f;
	out->v[ 4] =        axy - awz;
	out->v[ 5] = 1.0f - axx - azz;
	out->v[ 6] =        ayz + awx;
	out->v[ 7] = 0.0f;
	out->v[ 8] =        axz + awy;
	out->v[ 9] =        ayz - awx;
	out->v[10] = 1.0f - axx - ayy;
	out->v[11] = 0.0f;
	out->v[12] = b.v[0];
	out->v[13] = b.v[1];
	out->v[14] = b.v[2];
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_rottransorigin(mat4 *out, quat a, vec3 b, vec3 origin){
	float ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
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
		ox = origin.v[0], oy = origin.v[1], oz = origin.v[2];
	out->v[ 0] = 1.0f - ayy - azz;
	out->v[ 1] =        axy + awz;
	out->v[ 2] =        axz - awy;
	out->v[ 3] = 0.0f;
	out->v[ 4] =        axy - awz;
	out->v[ 5] = 1.0f - axx - azz;
	out->v[ 6] =        ayz + awx;
	out->v[ 7] = 0.0f;
	out->v[ 8] =        axz + awy;
	out->v[ 9] =        ayz - awx;
	out->v[10] = 1.0f - axx - ayy;
	out->v[11] = 0.0f;
	out->v[12] = b.v[0] + ox - (out->v[0] * ox + out->v[4] * oy + out->v[ 8] * oz);
	out->v[13] = b.v[1] + oy - (out->v[1] * ox + out->v[5] * oy + out->v[ 9] * oz);
	out->v[14] = b.v[2] + oz - (out->v[2] * ox + out->v[6] * oy + out->v[10] * oz);
	out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_scale(mat4 *out, mat4 *a, vec3 b){
	float bx = b.v[0], by = b.v[1], bz = b.v[2];
	out->v[ 0] = a->v[ 0] * bx;
	out->v[ 1] = a->v[ 1] * bx;
	out->v[ 2] = a->v[ 2] * bx;
	out->v[ 3] = a->v[ 3] * bx;
	out->v[ 4] = a->v[ 4] * by;
	out->v[ 5] = a->v[ 5] * by;
	out->v[ 6] = a->v[ 6] * by;
	out->v[ 7] = a->v[ 7] * by;
	out->v[ 8] = a->v[ 8] * bz;
	out->v[ 9] = a->v[ 9] * bz;
	out->v[10] = a->v[10] * bz;
	out->v[11] = a->v[11] * bz;
	out->v[12] = a->v[12]     ;
	out->v[13] = a->v[13]     ;
	out->v[14] = a->v[14]     ;
	out->v[15] = a->v[15]     ;
	return out;
}

mat4 *mat4_scaling(mat4 *out, vec3 a){
	out->v[ 0] = a.v[0]; out->v[ 1] =   0.0f; out->v[ 2] =   0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] =   0.0f; out->v[ 5] = a.v[1]; out->v[ 6] =   0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] =   0.0f; out->v[ 9] =   0.0f; out->v[10] = a.v[2]; out->v[11] = 0.0f;
	out->v[12] =   0.0f; out->v[13] =   0.0f; out->v[14] =   0.0f; out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_sub(mat4 *out, mat4 *a, mat4 *b){
	out->v[ 0] = a->v[ 0] - b->v[ 0];
	out->v[ 1] = a->v[ 1] - b->v[ 1];
	out->v[ 2] = a->v[ 2] - b->v[ 2];
	out->v[ 3] = a->v[ 3] - b->v[ 3];
	out->v[ 4] = a->v[ 4] - b->v[ 4];
	out->v[ 5] = a->v[ 5] - b->v[ 5];
	out->v[ 6] = a->v[ 6] - b->v[ 6];
	out->v[ 7] = a->v[ 7] - b->v[ 7];
	out->v[ 8] = a->v[ 8] - b->v[ 8];
	out->v[ 9] = a->v[ 9] - b->v[ 9];
	out->v[10] = a->v[10] - b->v[10];
	out->v[11] = a->v[11] - b->v[11];
	out->v[12] = a->v[12] - b->v[12];
	out->v[13] = a->v[13] - b->v[13];
	out->v[14] = a->v[14] - b->v[14];
	out->v[15] = a->v[15] - b->v[15];
	return out;
}

mat4 *mat4_translate(mat4 *out, mat4 *a, vec3 b){
	float bx = b.v[0], by = b.v[1], bz = b.v[2];
	if (out == a){
		out->v[12] = a->v[0] * bx + a->v[4] * by + a->v[ 8] * bz + a->v[12];
		out->v[13] = a->v[1] * bx + a->v[5] * by + a->v[ 9] * bz + a->v[13];
		out->v[14] = a->v[2] * bx + a->v[6] * by + a->v[10] * bz + a->v[14];
		out->v[15] = a->v[3] * bx + a->v[7] * by + a->v[11] * bz + a->v[15];
	}
	else{
		float
			a00 = a->v[0], a01 = a->v[1], a02 = a->v[ 2], a03 = a->v[ 3],
			a10 = a->v[4], a11 = a->v[5], a12 = a->v[ 6], a13 = a->v[ 7],
			a20 = a->v[8], a21 = a->v[9], a22 = a->v[10], a23 = a->v[11];
		out->v[ 0] = a00;
		out->v[ 1] = a01;
		out->v[ 2] = a02;
		out->v[ 3] = a03;
		out->v[ 4] = a10;
		out->v[ 5] = a11;
		out->v[ 6] = a12;
		out->v[ 7] = a13;
		out->v[ 8] = a20;
		out->v[ 9] = a21;
		out->v[10] = a22;
		out->v[11] = a23;
		out->v[12] = a00 * bx + a10 * by + a20 * bz + a->v[12];
		out->v[13] = a01 * bx + a11 * by + a21 * bz + a->v[13];
		out->v[14] = a02 * bx + a12 * by + a22 * bz + a->v[14];
		out->v[15] = a03 * bx + a13 * by + a23 * bz + a->v[15];
	}
	return out;
}

mat4 *mat4_translation(mat4 *out, vec3 a){
	out->v[ 0] = 1.0f; out->v[ 1] = 0.0f; out->v[ 2] = 0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] = 0.0f; out->v[ 5] = 1.0f; out->v[ 6] = 0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] = 0.0f; out->v[ 9] = 0.0f; out->v[10] = 1.0f; out->v[11] = 0.0f;
	out->v[12] = a.v[0]; out->v[13] = a.v[1]; out->v[14] = a.v[2]; out->v[15] = 1;
	return out;
}

mat4 *mat4_transpose(mat4 *out, mat4 *a){
	if (out == a){
		float
			a01 = a->v[1], a02 = a->v[2], a03 = a->v[ 3],
			/*          */ a12 = a->v[6], a13 = a->v[ 7],
			/*                         */ a23 = a->v[11];
		out->v[ 1] = a->v[ 4];
		out->v[ 2] = a->v[ 8];
		out->v[ 3] = a->v[12];
		out->v[ 4] = a01;
		out->v[ 6] = a->v[ 9];
		out->v[ 7] = a->v[13];
		out->v[ 8] = a02;
		out->v[ 9] = a12;
		out->v[11] = a->v[14];
		out->v[12] = a03;
		out->v[13] = a13;
		out->v[14] = a23;
	}
	else{
		out->v[ 0] = a->v[ 0]; out->v[ 1] = a->v[ 4]; out->v[ 2] = a->v[ 8]; out->v[ 3] = a->v[12];
		out->v[ 4] = a->v[ 1]; out->v[ 5] = a->v[ 5]; out->v[ 6] = a->v[ 9]; out->v[ 7] = a->v[13];
		out->v[ 8] = a->v[ 2]; out->v[ 9] = a->v[ 6]; out->v[10] = a->v[10]; out->v[11] = a->v[14];
		out->v[12] = a->v[ 3]; out->v[13] = a->v[ 7]; out->v[14] = a->v[11]; out->v[15] = a->v[15];
	}
	return out;
}

#endif /* NVQM_SKIP_FLOATING_POINT */

#ifndef NVQM_SKIP_FIXED_POINT

xang xint_atan2(xint y, xint x){
	static const xint c1 = 0x0200, c2 = 0x0600, c3 = 0x0080, c4 = 0x0280;
	if (y == 0 && x == 0)
		return 0;
	if (x == XINT1){
		/* hard-code some atan2(y, 1) values at the limits */
		if (y <= -42722234) return (xang)3073;
		if (y >=  42722235) return (xang)1023;
	}
	xint abs_y = xint_abs(y);
	xang angle;
	if (x >= 0){
		xint d = xint_add(x, abs_y);
		if (d == 0)
			return 0;
		xint r = xint_div(xint_sub(x, abs_y), d);
		xint r3 = xint_mul(xint_mul(r, r), r);
		angle = (xang)xint_add(xint_sub(xint_mul(c3, r3), xint_mul(c4, r)), c1);
	}
	else{
		xint d = xint_sub(abs_y, x);
		if (d == 0)
			return 0;
		xint r = xint_div(xint_add(x, abs_y), d);
		xint r3 = xint_mul(xint_mul(r, r), r);
		angle = (xang)xint_add(xint_sub(xint_mul(c3, r3), xint_mul(c4, r)), c2);
	}
	if (y < 0)
		return angle == 0 ? 0 : XANG360 - angle;
	return angle;
}

xang xint_atan(xint a){
	return xint_atan2(a, XINT1);
}

xang xint_acos(xint a){
	if (a <= -XINT1)
		return XANG180;
	if (a >= XINT1)
		return XANG0;
	if (a > -51 && a < 51) /* high error rate right around 0, so just do it manually */
		return XANG90;
	xint res = xint_atan2(xint_div(xint_sqrt(xint_sub(XINT1, xint_mul(a, a))), a), XINT1);
	if (a < 0)
		res = (res + XANG180) % XANG360;
	return res;
}

xang xint_asin(xint a){
	if (a <= -XINT1)
		return XANG270;
	if (a >= XINT1)
		return XANG90;
	if (a > -51 && a < 51) /* high error rate right around 0, so just do it manually */
		return XANG0;
	return xint_atan2(xint_div(a, xint_sqrt(xint_sub(XINT1, xint_mul(a, a)))), XINT1);
}

static inline int64_t x_mul31(int64_t res, int64_t f){
	/* res is Q33.31 and f is Q0.32 */
	return (int64_t)(((uint64_t)res * (uint64_t)f) >> 32);
}

static inline int64_t x_exp2f(int64_t f){
	/* res is Q33.31 and f is Q0.32 */
	static const int64_t
		c0 = INT64_C(0x80000000),
		c1 = INT64_C(0x58B45A41),
		c2 = INT64_C(0x1EEB1ABA),
		c3 = INT64_C(0x069F8E50),
		c4 = INT64_C(0x01C0FCB2);
	int64_t res = c4;
	res = c3 + x_mul31(res, f);
	res = c2 + x_mul31(res, f);
	res = c1 + x_mul31(res, f);
	return c0 + x_mul31(res, f);
}

static inline xint x_exp2(int64_t a){
	/* a is Q32.32
	 * 2^(whole+fraction) = 2^whole * 2^fraction
	 */
	int32_t whole = a >> 32;
	int64_t fract = x_exp2f(a & 0xFFFFFFFF);
	if (whole < 15)
		return (xint)(fract >> (15 - whole));
	return (xint)(fract << (whole - 15));
}

xint xint_exp(xint a){
	if (a == 0)
		return XINT1;
	if (a > 681391)
		return XINTMAX;
	if (a < -681391)
		return 0;
	int neg = 0;
	if (a < 0){
		neg = 1;
		a = -a;
	}
	static const int64_t log2e = INT64_C(0x171547653); /* log2(e) at Q32.32 */
	xint res = x_exp2((log2e * (int64_t)a) >> 16);
	if (neg)
		res = xint_div(XINT1, res);
	return res;
}

#if defined(__GNUC__)
static inline int x_log2w(int w){
	return (((int)(sizeof(int) * 8)) - __builtin_clz(w));
}
#elif defined(_MSC_VER)
/* TODO: actually test this */
#include <intrin.h>
static inline int x_log2w(int w){
	return (((int)(sizeof(int) * 8)) - __lzcnt(w));
}
#else
static inline int x_log2w(int w){
	if (!(w >>  0)) return  0;
	if (!(w >>  1)) return  1;
	if (!(w >>  2)) return  2;
	if (!(w >>  3)) return  3;
	if (!(w >>  4)) return  4;
	if (!(w >>  5)) return  5;
	if (!(w >>  6)) return  6;
	if (!(w >>  7)) return  7;
	if (!(w >>  8)) return  8;
	if (!(w >>  9)) return  9;
	if (!(w >> 10)) return 10;
	if (!(w >> 11)) return 11;
	if (!(w >> 12)) return 12;
	if (!(w >> 13)) return 13;
	if (!(w >> 14)) return 14;
	if (!(w >> 15)) return 15;
	return 16;
}
#endif

static inline xint x_log2f(xint f){ /* f ranges from (1, 2] */
	static const xint c1 = 0x16C40, c2 = INT32_C(0xFFFF6AFD), c3 = 0x28C2;
	f = xint_sub(f, XINT1);
	xint res = c3;
	res = xint_add(c2, xint_mul(res, f));
	res = xint_add(c1, xint_mul(res, f));
	return xint_mul(res, f);
}

static inline xint x_log2(xint a){
	int base = x_log2w(a >> 16) - 1;
	xint frac = x_log2f(xint_div(a, 1 << (base + 16)));
	return xint_add(xint_fromint(base), frac);
}

xint xint_log(xint a){
	if (a <= 0)
		return XINTMIN;
	else if (a == 1) /* must hard code these because it's too small to calculate */
		return INT32_C(0xFFF4E8DF);
	else if (a == 2)
		return INT32_C(0xFFF59A51);
	int small = 0;
	if (a < XINT1){
		small = 1;
		a = xint_div(XINT1, a);
	}
	static const xint log2einv = 0xB172; /* 1/(log2 e) */
	xint res = xint_mul(x_log2(a), log2einv);
	if (small)
		res = -res;
	return res;
}

xint xint_pow(xint a, xint b){
	if (a < 0)
		return -xint_pow(-a, b);
	if (a == 0)
		return XINTMIN;

	int flip = 0;
	if (b < 0){
		b = -b;
		if (a < XINT1)
			a = xint_div(XINT1, a); /* double flip -> no flip */
		else
			flip = 1;
	}
	else if (a < XINT1){
		a = xint_div(XINT1, a);
		flip = 1;
	}

	/* res = a^(integer + fraction)
	 *     = a^(integer) * a^(fraction)
	 *     = a^(integer) * (2^(log2 a))^(fraction)
	 *     = a^(integer) * 2^(fraction * log2 a)
	 */
	xint res = XINT1;
	xint base = a;
	int pow_int = xint_toint(b);
	while (pow_int){
		if (pow_int & 1)
			res = xint_mul(res, base);
		pow_int >>= 1;
		base = xint_mul(base, base);
	}

	int64_t pow_frac = b & 0xFFFF;
	if (pow_frac)
		res = xint_mul(res, x_exp2(pow_frac * x_log2(a)));

	if (flip)
		res = xint_div(XINT1, res);
	return res;
}

xint xint_sqrt(xint a){
	if (a < 0)
		return -xint_sqrt(-a);
	xint res = 0;
	xint res2, m;
	#define X(b)                  \
		res2 = res | b;           \
		m = xint_mul(res2, res2); \
		if (m >= 0 && m < a)      \
			res = res2;
	X(0x00800000);
	X(0x00400000);
	X(0x00200000);
	X(0x00100000);
	X(0x00080000);
	X(0x00040000);
	X(0x00020000);
	X(0x00010000);
	X(0x00008000);
	X(0x00004000);
	X(0x00002000);
	X(0x00001000);
	X(0x00000800);
	X(0x00000400);
	X(0x00000200);
	X(0x00000100);
	X(0x00000080);
	X(0x00000040);
	X(0x00000010);
	X(0x00000008);
	X(0x00000004);
	X(0x00000002);
	X(0x00000001);
	#undef X
	return res;
}

/*
 * xmat3
 */

xmat3 *xmat3_add(xmat3 *out, xmat3 *a, xmat3 *b){
	out->v[0] = xint_add(a->v[0], b->v[0]);
	out->v[1] = xint_add(a->v[1], b->v[1]);
	out->v[2] = xint_add(a->v[2], b->v[2]);
	out->v[3] = xint_add(a->v[3], b->v[3]);
	out->v[4] = xint_add(a->v[4], b->v[4]);
	out->v[5] = xint_add(a->v[5], b->v[5]);
	out->v[6] = xint_add(a->v[6], b->v[6]);
	out->v[7] = xint_add(a->v[7], b->v[7]);
	out->v[8] = xint_add(a->v[8], b->v[8]);
	return out;
}

xmat3 *xmat3_adjoint(xmat3 *out, xmat3 *a){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8];
	out->v[0] = xint_sub(xint_mul(a11, a22), xint_mul(a12, a21));
	out->v[1] = xint_sub(xint_mul(a02, a21), xint_mul(a01, a22));
	out->v[2] = xint_sub(xint_mul(a01, a12), xint_mul(a02, a11));
	out->v[3] = xint_sub(xint_mul(a12, a20), xint_mul(a10, a22));
	out->v[4] = xint_sub(xint_mul(a00, a22), xint_mul(a02, a20));
	out->v[5] = xint_sub(xint_mul(a02, a10), xint_mul(a00, a12));
	out->v[6] = xint_sub(xint_mul(a10, a21), xint_mul(a11, a20));
	out->v[7] = xint_sub(xint_mul(a01, a20), xint_mul(a00, a21));
	out->v[8] = xint_sub(xint_mul(a00, a11), xint_mul(a01, a10));
	return out;
}

xmat3 *xmat3_compmul(xmat3 *out, xmat3 *a, xmat3 *b){
	out->v[0] = xint_mul(a->v[0], b->v[0]);
	out->v[1] = xint_mul(a->v[1], b->v[1]);
	out->v[2] = xint_mul(a->v[2], b->v[2]);
	out->v[3] = xint_mul(a->v[3], b->v[3]);
	out->v[4] = xint_mul(a->v[4], b->v[4]);
	out->v[5] = xint_mul(a->v[5], b->v[5]);
	out->v[6] = xint_mul(a->v[6], b->v[6]);
	out->v[7] = xint_mul(a->v[7], b->v[7]);
	out->v[8] = xint_mul(a->v[8], b->v[8]);
	return out;
}

xmat3 *xmat3_copy(xmat3 *out, xmat3 *a){
	out->v[0] = a->v[0]; out->v[1] = a->v[1]; out->v[2] = a->v[2];
	out->v[3] = a->v[3]; out->v[4] = a->v[4]; out->v[5] = a->v[5];
	out->v[6] = a->v[6]; out->v[7] = a->v[7]; out->v[8] = a->v[8];
	return out;
}

xint xmat3_det(xmat3 *a){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8];
	return xint_add(xint_add(
		xint_mul(a00, xint_sub(xint_mul( a22, a11), xint_mul(a12, a21))),
		xint_mul(a01, xint_add(xint_mul(-a22, a10), xint_mul(a12, a20)))),
		xint_mul(a02, xint_sub(xint_mul( a21, a10), xint_mul(a11, a20)))
	);
}

xmat3 *xmat3_identity(xmat3 *out){
	out->v[0] = XINT1; out->v[1] = 0; out->v[2] = 0;
	out->v[3] = 0; out->v[4] = XINT1; out->v[5] = 0;
	out->v[6] = 0; out->v[7] = 0; out->v[8] = XINT1;
	return out;
}

xmat3 *xmat3_invert(xmat3 *out, xmat3 *a){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		b01 = xint_sub(xint_mul( a22, a11), xint_mul(a12, a21)),
		b11 = xint_add(xint_mul(-a22, a10), xint_mul(a12, a20)),
		b21 = xint_sub(xint_mul( a21, a10), xint_mul(a11, a20));
	xint det = xint_add(xint_add(xint_mul(a00, b01), xint_mul(a01, b11)), xint_mul(a02, b21));
	if (det == 0)
		return (xmat3 *)0;
	det = xint_div(XINT1, det);
	out->v[0] = xint_mul(b01                                              , det);
	out->v[1] = xint_mul(xint_add(xint_mul(-a22, a01), xint_mul(a02, a21)), det);
	out->v[2] = xint_mul(xint_sub(xint_mul( a12, a01), xint_mul(a02, a11)), det);
	out->v[3] = xint_mul(b11                                              , det);
	out->v[4] = xint_mul(xint_sub(xint_mul( a22, a00), xint_mul(a02, a20)), det);
	out->v[5] = xint_mul(xint_add(xint_mul(-a12, a00), xint_mul(a02, a10)), det);
	out->v[6] = xint_mul(b21                                              , det);
	out->v[7] = xint_mul(xint_add(xint_mul(-a21, a00), xint_mul(a01, a20)), det);
	out->v[8] = xint_mul(xint_sub(xint_mul( a11, a00), xint_mul(a01, a10)), det);
	return out;
}

xmat3 *xmat3_mul(xmat3 *out, xmat3 *a, xmat3 *b){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		b00 = b->v[0], b01 = b->v[1], b02 = b->v[2],
		b10 = b->v[3], b11 = b->v[4], b12 = b->v[5],
		b20 = b->v[6], b21 = b->v[7], b22 = b->v[8];
	out->v[0] = xint_add(xint_add(xint_mul(b00, a00), xint_mul(b01, a10)), xint_mul(b02, a20));
	out->v[1] = xint_add(xint_add(xint_mul(b00, a01), xint_mul(b01, a11)), xint_mul(b02, a21));
	out->v[2] = xint_add(xint_add(xint_mul(b00, a02), xint_mul(b01, a12)), xint_mul(b02, a22));
	out->v[3] = xint_add(xint_add(xint_mul(b10, a00), xint_mul(b11, a10)), xint_mul(b12, a20));
	out->v[4] = xint_add(xint_add(xint_mul(b10, a01), xint_mul(b11, a11)), xint_mul(b12, a21));
	out->v[5] = xint_add(xint_add(xint_mul(b10, a02), xint_mul(b11, a12)), xint_mul(b12, a22));
	out->v[6] = xint_add(xint_add(xint_mul(b20, a00), xint_mul(b21, a10)), xint_mul(b22, a20));
	out->v[7] = xint_add(xint_add(xint_mul(b20, a01), xint_mul(b21, a11)), xint_mul(b22, a21));
	out->v[8] = xint_add(xint_add(xint_mul(b20, a02), xint_mul(b21, a12)), xint_mul(b22, a22));
	return out;
}

xmat3 *xmat3_quat(xmat3 *out, xquat a){
	xint ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		ax2 = ax << 1,
		ay2 = ay << 1,
		az2 = az << 1,
		axx = xint_mul(ax, ax2),
		ayx = xint_mul(ay, ax2),
		ayy = xint_mul(ay, ay2),
		azx = xint_mul(az, ax2),
		azy = xint_mul(az, ay2),
		azz = xint_mul(az, az2),
		awx = xint_mul(aw, ax2),
		awy = xint_mul(aw, ay2),
		awz = xint_mul(aw, az2);
	out->v[0] = xint_sub(XINT1, xint_add(ayy, azz));
	out->v[1] =                 xint_add(ayx, awz);
	out->v[2] =                 xint_sub(azx, awy);
	out->v[3] =                 xint_sub(ayx, awz);
	out->v[4] = xint_sub(XINT1, xint_add(axx, azz));
	out->v[5] =                 xint_add(azy, awx);
	out->v[6] =                 xint_add(azx, awy);
	out->v[7] =                 xint_sub(azy, awx);
	out->v[8] = xint_sub(XINT1, xint_add(axx, ayy));
	return out;
}

xmat3 *xmat3_rotate(xmat3 *out, xmat3 *a, xang ang){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		s = xint_sin(ang), c = xint_cos(ang);
	out->v[0] = xint_add(xint_mul(c, a00), xint_mul(s, a10));
	out->v[1] = xint_add(xint_mul(c, a01), xint_mul(s, a11));
	out->v[2] = xint_add(xint_mul(c, a02), xint_mul(s, a12));
	out->v[3] = xint_sub(xint_mul(c, a10), xint_mul(s, a00));
	out->v[4] = xint_sub(xint_mul(c, a11), xint_mul(s, a01));
	out->v[5] = xint_sub(xint_mul(c, a12), xint_mul(s, a02));
	out->v[6] = a20;
	out->v[7] = a21;
	out->v[8] = a22;
	return out;
}

xmat3 *xmat3_rotation(xmat3 *out, xang ang){
	xint s = xint_sin(ang), c = xint_cos(ang);
	out->v[0] =  c;
	out->v[1] =  s;
	out->v[2] =  0;
	out->v[3] = -s;
	out->v[4] =  c;
	out->v[5] =  0;
	out->v[6] =  0;
	out->v[7] =  0;
	out->v[8] = XINT1;
	return out;
}

xmat3 *xmat3_scale(xmat3 *out, xmat3 *a, xvec2 b){
	xint bx = b.v[0], by = b.v[1];
	out->v[0] = xint_mul(bx, a->v[0]);
	out->v[1] = xint_mul(bx, a->v[1]);
	out->v[2] = xint_mul(bx, a->v[2]);
	out->v[3] = xint_mul(by, a->v[3]);
	out->v[4] = xint_mul(by, a->v[4]);
	out->v[5] = xint_mul(by, a->v[5]);
	out->v[6] = a->v[6];
	out->v[7] = a->v[7];
	out->v[8] = a->v[8];
	return out;
}

xmat3 *xmat3_scaling(xmat3 *out, xvec2 a){
	out->v[0] = a.v[0];
	out->v[1] = 0;
	out->v[2] = 0;
	out->v[3] = 0;
	out->v[4] = a.v[1];
	out->v[5] = 0;
	out->v[6] = 0;
	out->v[7] = 0;
	out->v[8] = XINT1;
	return out;
}

xmat3 *xmat3_sub(xmat3 *out, xmat3 *a, xmat3 *b){
	out->v[0] = xint_sub(a->v[0], b->v[0]);
	out->v[1] = xint_sub(a->v[1], b->v[1]);
	out->v[2] = xint_sub(a->v[2], b->v[2]);
	out->v[3] = xint_sub(a->v[3], b->v[3]);
	out->v[4] = xint_sub(a->v[4], b->v[4]);
	out->v[5] = xint_sub(a->v[5], b->v[5]);
	out->v[6] = xint_sub(a->v[6], b->v[6]);
	out->v[7] = xint_sub(a->v[7], b->v[7]);
	out->v[8] = xint_sub(a->v[8], b->v[8]);
	return out;
}

xmat3 *xmat3_translate(xmat3 *out, xmat3 *a, xvec2 b){
	xint
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[2],
		a10 = a->v[3], a11 = a->v[4], a12 = a->v[5],
		a20 = a->v[6], a21 = a->v[7], a22 = a->v[8],
		bx = b.v[0], by = b.v[1];
	out->v[0] = a00;
	out->v[1] = a01;
	out->v[2] = a02;
	out->v[3] = a10;
	out->v[4] = a11;
	out->v[5] = a12;
	out->v[6] = xint_add(xint_add(xint_mul(bx, a00), xint_mul(by, a10)), a20);
	out->v[7] = xint_add(xint_add(xint_mul(bx, a01), xint_mul(by, a11)), a21);
	out->v[8] = xint_add(xint_add(xint_mul(bx, a02), xint_mul(by, a12)), a22);
	return out;
}

xmat3 *xmat3_translation(xmat3 *out, xvec2 a){
	out->v[0] = XINT1;
	out->v[1] = 0;
	out->v[2] = 0;
	out->v[3] = 0;
	out->v[4] = XINT1;
	out->v[5] = 0;
	out->v[6] = a.v[0];
	out->v[7] = a.v[1];
	out->v[8] = XINT1;
	return out;
}

xmat3 *xmat3_transpose(xmat3 *out, xmat3 *a){
	if (out == a) {
		xint a01 = a->v[1], a02 = a->v[2], a12 = a->v[5];
		out->v[1] = a->v[3];
		out->v[2] = a->v[6];
		out->v[3] = a01;
		out->v[5] = a->v[7];
		out->v[6] = a02;
		out->v[7] = a12;
	}
	else{
		out->v[0] = a->v[0];
		out->v[1] = a->v[3];
		out->v[2] = a->v[6];
		out->v[3] = a->v[1];
		out->v[4] = a->v[4];
		out->v[5] = a->v[7];
		out->v[6] = a->v[2];
		out->v[7] = a->v[5];
		out->v[8] = a->v[8];
	}
	return out;
}

/*
 * xmat4
 */

xmat4 *xmat4_add(xmat4 *out, xmat4 *a, xmat4 *b){
	out->v[ 0] = xint_add(a->v[ 0], b->v[ 0]);
	out->v[ 1] = xint_add(a->v[ 1], b->v[ 1]);
	out->v[ 2] = xint_add(a->v[ 2], b->v[ 2]);
	out->v[ 3] = xint_add(a->v[ 3], b->v[ 3]);
	out->v[ 4] = xint_add(a->v[ 4], b->v[ 4]);
	out->v[ 5] = xint_add(a->v[ 5], b->v[ 5]);
	out->v[ 6] = xint_add(a->v[ 6], b->v[ 6]);
	out->v[ 7] = xint_add(a->v[ 7], b->v[ 7]);
	out->v[ 8] = xint_add(a->v[ 8], b->v[ 8]);
	out->v[ 9] = xint_add(a->v[ 9], b->v[ 9]);
	out->v[10] = xint_add(a->v[10], b->v[10]);
	out->v[11] = xint_add(a->v[11], b->v[11]);
	out->v[12] = xint_add(a->v[12], b->v[12]);
	out->v[13] = xint_add(a->v[13], b->v[13]);
	out->v[14] = xint_add(a->v[14], b->v[14]);
	out->v[15] = xint_add(a->v[15], b->v[15]);
	return out;
}

xmat4 *xmat4_adjoint(xmat4 *out, xmat4 *a){
	xint
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15];
	out->v[ 0] =  xint_add(xint_sub(
		xint_mul(a11, xint_sub(xint_mul(a22, a33), xint_mul(a23, a32))),
		xint_mul(a21, xint_sub(xint_mul(a12, a33), xint_mul(a13, a32)))),
		xint_mul(a31, xint_sub(xint_mul(a12, a23), xint_mul(a13, a22))));
	out->v[ 1] = -xint_add(xint_sub(
		xint_mul(a01, xint_sub(xint_mul(a22, a33), xint_mul(a23, a32))),
		xint_mul(a21, xint_sub(xint_mul(a02, a33), xint_mul(a03, a32)))),
		xint_mul(a31, xint_sub(xint_mul(a02, a23), xint_mul(a03, a22))));
	out->v[ 2] =  xint_add(xint_sub(
		xint_mul(a01, xint_sub(xint_mul(a12, a33), xint_mul(a13, a32))),
		xint_mul(a11, xint_sub(xint_mul(a02, a33), xint_mul(a03, a32)))),
		xint_mul(a31, xint_sub(xint_mul(a02, a13), xint_mul(a03, a12))));
	out->v[ 3] = -xint_add(xint_sub(
		xint_mul(a01, xint_sub(xint_mul(a12, a23), xint_mul(a13, a22))),
		xint_mul(a11, xint_sub(xint_mul(a02, a23), xint_mul(a03, a22)))),
		xint_mul(a21, xint_sub(xint_mul(a02, a13), xint_mul(a03, a12))));
	out->v[ 4] = -xint_add(xint_sub(
		xint_mul(a10, xint_sub(xint_mul(a22, a33), xint_mul(a23, a32))),
		xint_mul(a20, xint_sub(xint_mul(a12, a33), xint_mul(a13, a32)))),
		xint_mul(a30, xint_sub(xint_mul(a12, a23), xint_mul(a13, a22))));
	out->v[ 5] =  xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a22, a33), xint_mul(a23, a32))),
		xint_mul(a20, xint_sub(xint_mul(a02, a33), xint_mul(a03, a32)))),
		xint_mul(a30, xint_sub(xint_mul(a02, a23), xint_mul(a03, a22))));
	out->v[ 6] = -xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a12, a33), xint_mul(a13, a32))),
		xint_mul(a10, xint_sub(xint_mul(a02, a33), xint_mul(a03, a32)))),
		xint_mul(a30, xint_sub(xint_mul(a02, a13), xint_mul(a03, a12))));
	out->v[ 7] =  xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a12, a23), xint_mul(a13, a22))),
		xint_mul(a10, xint_sub(xint_mul(a02, a23), xint_mul(a03, a22)))),
		xint_mul(a20, xint_sub(xint_mul(a02, a13), xint_mul(a03, a12))));
	out->v[ 8] =  xint_add(xint_sub(
		xint_mul(a10, xint_sub(xint_mul(a21, a33), xint_mul(a23, a31))),
		xint_mul(a20, xint_sub(xint_mul(a11, a33), xint_mul(a13, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a11, a23), xint_mul(a13, a21))));
	out->v[ 9] = -xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a21, a33), xint_mul(a23, a31))),
		xint_mul(a20, xint_sub(xint_mul(a01, a33), xint_mul(a03, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a01, a23), xint_mul(a03, a21))));
	out->v[10] =  xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a11, a33), xint_mul(a13, a31))),
		xint_mul(a10, xint_sub(xint_mul(a01, a33), xint_mul(a03, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a01, a13), xint_mul(a03, a11))));
	out->v[11] = -xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a11, a23), xint_mul(a13, a21))),
		xint_mul(a10, xint_sub(xint_mul(a01, a23), xint_mul(a03, a21)))),
		xint_mul(a20, xint_sub(xint_mul(a01, a13), xint_mul(a03, a11))));
	out->v[12] = -xint_add(xint_sub(
		xint_mul(a10, xint_sub(xint_mul(a21, a32), xint_mul(a22, a31))),
		xint_mul(a20, xint_sub(xint_mul(a11, a32), xint_mul(a12, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a11, a22), xint_mul(a12, a21))));
	out->v[13] =  xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a21, a32), xint_mul(a22, a31))),
		xint_mul(a20, xint_sub(xint_mul(a01, a32), xint_mul(a02, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a01, a22), xint_mul(a02, a21))));
	out->v[14] = -xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a11, a32), xint_mul(a12, a31))),
		xint_mul(a10, xint_sub(xint_mul(a01, a32), xint_mul(a02, a31)))),
		xint_mul(a30, xint_sub(xint_mul(a01, a12), xint_mul(a02, a11))));
	out->v[15] =  xint_add(xint_sub(
		xint_mul(a00, xint_sub(xint_mul(a11, a22), xint_mul(a12, a21))),
		xint_mul(a10, xint_sub(xint_mul(a01, a22), xint_mul(a02, a21)))),
		xint_mul(a20, xint_sub(xint_mul(a01, a12), xint_mul(a02, a11))));
	return out;
}

xmat4 *xmat4_compmul(xmat4 *out, xmat4 *a, xmat4 *b){
	out->v[ 0] = xint_mul(a->v[ 0], b->v[ 0]);
	out->v[ 1] = xint_mul(a->v[ 1], b->v[ 1]);
	out->v[ 2] = xint_mul(a->v[ 2], b->v[ 2]);
	out->v[ 3] = xint_mul(a->v[ 3], b->v[ 3]);
	out->v[ 4] = xint_mul(a->v[ 4], b->v[ 4]);
	out->v[ 5] = xint_mul(a->v[ 5], b->v[ 5]);
	out->v[ 6] = xint_mul(a->v[ 6], b->v[ 6]);
	out->v[ 7] = xint_mul(a->v[ 7], b->v[ 7]);
	out->v[ 8] = xint_mul(a->v[ 8], b->v[ 8]);
	out->v[ 9] = xint_mul(a->v[ 9], b->v[ 9]);
	out->v[10] = xint_mul(a->v[10], b->v[10]);
	out->v[11] = xint_mul(a->v[11], b->v[11]);
	out->v[12] = xint_mul(a->v[12], b->v[12]);
	out->v[13] = xint_mul(a->v[13], b->v[13]);
	out->v[14] = xint_mul(a->v[14], b->v[14]);
	out->v[15] = xint_mul(a->v[15], b->v[15]);
	return out;
}

xmat4 *xmat4_copy(xmat4 *out, xmat4 *a){
	out->v[ 0] = a->v[ 0]; out->v[ 1] = a->v[ 1]; out->v[ 2] = a->v[ 2]; out->v[ 3] = a->v[ 3];
	out->v[ 4] = a->v[ 4]; out->v[ 5] = a->v[ 5]; out->v[ 6] = a->v[ 6]; out->v[ 7] = a->v[ 7];
	out->v[ 8] = a->v[ 8]; out->v[ 9] = a->v[ 9]; out->v[10] = a->v[10]; out->v[11] = a->v[11];
	out->v[12] = a->v[12]; out->v[13] = a->v[13]; out->v[14] = a->v[14]; out->v[15] = a->v[15];
	return out;
}

xint xmat4_det(xmat4 *a){
	xint
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15],
		b00 = xint_sub(xint_mul(a00, a11), xint_mul(a01, a10)),
		b01 = xint_sub(xint_mul(a00, a12), xint_mul(a02, a10)),
		b02 = xint_sub(xint_mul(a00, a13), xint_mul(a03, a10)),
		b03 = xint_sub(xint_mul(a01, a12), xint_mul(a02, a11)),
		b04 = xint_sub(xint_mul(a01, a13), xint_mul(a03, a11)),
		b05 = xint_sub(xint_mul(a02, a13), xint_mul(a03, a12)),
		b06 = xint_sub(xint_mul(a20, a31), xint_mul(a21, a30)),
		b07 = xint_sub(xint_mul(a20, a32), xint_mul(a22, a30)),
		b08 = xint_sub(xint_mul(a20, a33), xint_mul(a23, a30)),
		b09 = xint_sub(xint_mul(a21, a32), xint_mul(a22, a31)),
		b10 = xint_sub(xint_mul(a21, a33), xint_mul(a23, a31)),
		b11 = xint_sub(xint_mul(a22, a33), xint_mul(a23, a32));
	return xint_add(xint_sub(xint_add(xint_add(xint_sub(
		xint_mul(b00, b11), xint_mul(b01, b10)), xint_mul(b02, b09)), xint_mul(b03, b08)),
		xint_mul(b04, b07)), xint_mul(b05, b06));
}

xmat4 *xmat4_frustum(xmat4 *out, xint L, xint R, xint B, xint T, xint N, xint F){
	xint
		rl = xint_div(XINT1, xint_sub(R, L)),
		tb = xint_div(XINT1, xint_sub(T, B)),
		nf = xint_div(XINT1, xint_sub(N, F));
	out->v[ 0] = xint_mul(N << 1, rl);
	out->v[ 1] =  0;
	out->v[ 2] =  0;
	out->v[ 3] =  0;
	out->v[ 4] =  0;
	out->v[ 5] = xint_mul(N << 1, tb);
	out->v[ 6] =  0;
	out->v[ 7] =  0;
	out->v[ 8] = xint_mul(xint_add(R, L), rl);
	out->v[ 9] = xint_mul(xint_add(T, B), tb);
	out->v[10] = xint_mul(xint_add(F, N), nf);
	out->v[11] = -XINT1;
	out->v[12] =  0;
	out->v[13] =  0;
	out->v[14] = xint_mul(xint_mul(N, F) << 1, nf);
	out->v[15] =  0;
	return out;
}

xmat4 *xmat4_identity(xmat4 *out){
	out->v[ 0] = XINT1; out->v[ 1] = 0; out->v[ 2] = 0; out->v[ 3] = 0;
	out->v[ 4] = 0; out->v[ 5] = XINT1; out->v[ 6] = 0; out->v[ 7] = 0;
	out->v[ 8] = 0; out->v[ 9] = 0; out->v[10] = XINT1; out->v[11] = 0;
	out->v[12] = 0; out->v[13] = 0; out->v[14] = 0; out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_invert(xmat4 *out, xmat4 *a){
	xint
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15],
		b00 = xint_sub(xint_mul(a00, a11), xint_mul(a01, a10)),
		b01 = xint_sub(xint_mul(a00, a12), xint_mul(a02, a10)),
		b02 = xint_sub(xint_mul(a00, a13), xint_mul(a03, a10)),
		b03 = xint_sub(xint_mul(a01, a12), xint_mul(a02, a11)),
		b04 = xint_sub(xint_mul(a01, a13), xint_mul(a03, a11)),
		b05 = xint_sub(xint_mul(a02, a13), xint_mul(a03, a12)),
		b06 = xint_sub(xint_mul(a20, a31), xint_mul(a21, a30)),
		b07 = xint_sub(xint_mul(a20, a32), xint_mul(a22, a30)),
		b08 = xint_sub(xint_mul(a20, a33), xint_mul(a23, a30)),
		b09 = xint_sub(xint_mul(a21, a32), xint_mul(a22, a31)),
		b10 = xint_sub(xint_mul(a21, a33), xint_mul(a23, a31)),
		b11 = xint_sub(xint_mul(a22, a33), xint_mul(a23, a32));
	xint det = xint_add(xint_sub(xint_add(xint_add(xint_sub(
		xint_mul(b00, b11), xint_mul(b01, b10)), xint_mul(b02, b09)), xint_mul(b03, b08)),
		xint_mul(b04, b07)), xint_mul(b05, b06));
	if (det == 0)
		return (xmat4 *)0;
	det = xint_div(XINT1, det);
	out->v[ 0] = xint_mul(
		xint_add(xint_sub(xint_mul(a11, b11), xint_mul(a12, b10)), xint_mul(a13, b09)), det);
	out->v[ 1] = xint_mul(
		xint_sub(xint_sub(xint_mul(a02, b10), xint_mul(a01, b11)), xint_mul(a03, b09)), det);
	out->v[ 2] = xint_mul(
		xint_add(xint_sub(xint_mul(a31, b05), xint_mul(a32, b04)), xint_mul(a33, b03)), det);
	out->v[ 3] = xint_mul(
		xint_sub(xint_sub(xint_mul(a22, b04), xint_mul(a21, b05)), xint_mul(a23, b03)), det);
	out->v[ 4] = xint_mul(
		xint_sub(xint_sub(xint_mul(a12, b08), xint_mul(a10, b11)), xint_mul(a13, b07)), det);
	out->v[ 5] = xint_mul(
		xint_add(xint_sub(xint_mul(a00, b11), xint_mul(a02, b08)), xint_mul(a03, b07)), det);
	out->v[ 6] = xint_mul(
		xint_sub(xint_sub(xint_mul(a32, b02), xint_mul(a30, b05)), xint_mul(a33, b01)), det);
	out->v[ 7] = xint_mul(
		xint_add(xint_sub(xint_mul(a20, b05), xint_mul(a22, b02)), xint_mul(a23, b01)), det);
	out->v[ 8] = xint_mul(
		xint_add(xint_sub(xint_mul(a10, b10), xint_mul(a11, b08)), xint_mul(a13, b06)), det);
	out->v[ 9] = xint_mul(
		xint_sub(xint_sub(xint_mul(a01, b08), xint_mul(a00, b10)), xint_mul(a03, b06)), det);
	out->v[10] = xint_mul(
		xint_add(xint_sub(xint_mul(a30, b04), xint_mul(a31, b02)), xint_mul(a33, b00)), det);
	out->v[11] = xint_mul(
		xint_sub(xint_sub(xint_mul(a21, b02), xint_mul(a20, b04)), xint_mul(a23, b00)), det);
	out->v[12] = xint_mul(
		xint_sub(xint_sub(xint_mul(a11, b07), xint_mul(a10, b09)), xint_mul(a12, b06)), det);
	out->v[13] = xint_mul(
		xint_add(xint_sub(xint_mul(a00, b09), xint_mul(a01, b07)), xint_mul(a02, b06)), det);
	out->v[14] = xint_mul(
		xint_sub(xint_sub(xint_mul(a31, b01), xint_mul(a30, b03)), xint_mul(a32, b00)), det);
	out->v[15] = xint_mul(
		xint_add(xint_sub(xint_mul(a20, b03), xint_mul(a21, b01)), xint_mul(a22, b00)), det);
	return out;
}

xmat4 *xmat4_lookat(xmat4 *out, xvec3 eye, xvec3 position, xvec3 up){
	xint
		ex = eye.v[0], ey = eye.v[1], ez = eye.v[2],
		ux = up.v[0], uy = up.v[1], uz = up.v[2],
		px = position.v[0], py = position.v[1], pz = position.v[2];
	xint z0 = xint_sub(ex, px), z1 = xint_sub(ey, py), z2 = xint_sub(ez, pz);
	if (z0 == 0 && z1 == 0 && z2 == 0)
		return xmat4_identity(out);
	xint len = xint_add(xint_add(xint_mul(z0, z0), xint_mul(z1, z1)), xint_mul(z2, z2));
	if (len == 0)
		return xmat4_identity(out);
	len = xint_sqrt(len);
	if (len == 0)
		return xmat4_identity(out);
	len = xint_div(XINT1, len);
	z0 = xint_mul(z0, len);
	z1 = xint_mul(z1, len);
	z2 = xint_mul(z2, len);
	xint x0 = xint_sub(xint_mul(uy, z2), xint_mul(uz, z1));
	xint x1 = xint_sub(xint_mul(uz, z0), xint_mul(ux, z2));
	xint x2 = xint_sub(xint_mul(ux, z1), xint_mul(uy, z0));
	len = xint_add(xint_add(xint_mul(x0, x0), xint_mul(x1, x1)), xint_mul(x2, x2));
	if (len == 0)
		x0 = x1 = x2 = 0;
	else{
		len = xint_sqrt(len);
		if (len == 0)
			x0 = x1 = x2 = 0;
		else{
			len = xint_div(XINT1, len);
			x0 = xint_mul(x0, len);
			x1 = xint_mul(x1, len);
			x2 = xint_mul(x2, len);
		}
	}
	xint y0 = xint_sub(xint_mul(z1, x2), xint_mul(z2, x1));
	xint y1 = xint_sub(xint_mul(z2, x0), xint_mul(z0, x2));
	xint y2 = xint_sub(xint_mul(z0, x1), xint_mul(z1, x0));
	len = xint_add(xint_add(xint_mul(y0, y0), xint_mul(y1, y1)), xint_mul(y2, y2));
	if (len == 0)
		y0 = y1 = y2 = 0;
	else{
		len = xint_sqrt(len);
		if (len == 0)
			y0 = y1 = y2 = 0;
		else{
			len = xint_div(XINT1, len);
			y0 = xint_mul(y0, len);
			y1 = xint_mul(y1, len);
			y2 = xint_mul(y2, len);
		}
	}
	out->v[ 0] = x0;
	out->v[ 1] = y0;
	out->v[ 2] = z0;
	out->v[ 3] = 0;
	out->v[ 4] = x1;
	out->v[ 5] = y1;
	out->v[ 6] = z1;
	out->v[ 7] = 0;
	out->v[ 8] = x2;
	out->v[ 9] = y2;
	out->v[10] = z2;
	out->v[11] = 0;
	out->v[12] = -xint_add(xint_add(xint_mul(x0, ex), xint_mul(x1, ey)), xint_mul(x2, ez));
	out->v[13] = -xint_add(xint_add(xint_mul(y0, ex), xint_mul(y1, ey)), xint_mul(y2, ez));
	out->v[14] = -xint_add(xint_add(xint_mul(z0, ex), xint_mul(z1, ey)), xint_mul(z2, ez));
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_mul(xmat4 *out, xmat4 *a, xmat4 *b){
	xint
		a00 = a->v[ 0], a01 = a->v[ 1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[ 4], a11 = a->v[ 5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[ 8], a21 = a->v[ 9], a22 = a->v[10], a23 = a->v[11],
		a30 = a->v[12], a31 = a->v[13], a32 = a->v[14], a33 = a->v[15];
	xint b0, b1, b2, b3;
	b0 = b->v[ 0];
	b1 = b->v[ 1];
	b2 = b->v[ 2];
	b3 = b->v[ 3];
	out->v[ 0] = xint_add(xint_add(xint_add(
		xint_mul(b0, a00), xint_mul(b1, a10)), xint_mul(b2, a20)), xint_mul(b3, a30));
	out->v[ 1] = xint_add(xint_add(xint_add(
		xint_mul(b0, a01), xint_mul(b1, a11)), xint_mul(b2, a21)), xint_mul(b3, a31));
	out->v[ 2] = xint_add(xint_add(xint_add(
		xint_mul(b0, a02), xint_mul(b1, a12)), xint_mul(b2, a22)), xint_mul(b3, a32));
	out->v[ 3] = xint_add(xint_add(xint_add(
		xint_mul(b0, a03), xint_mul(b1, a13)), xint_mul(b2, a23)), xint_mul(b3, a33));
	b0 = b->v[ 4];
	b1 = b->v[ 5];
	b2 = b->v[ 6];
	b3 = b->v[ 7];
	out->v[ 4] = xint_add(xint_add(xint_add(
		xint_mul(b0, a00), xint_mul(b1, a10)), xint_mul(b2, a20)), xint_mul(b3, a30));
	out->v[ 5] = xint_add(xint_add(xint_add(
		xint_mul(b0, a01), xint_mul(b1, a11)), xint_mul(b2, a21)), xint_mul(b3, a31));
	out->v[ 6] = xint_add(xint_add(xint_add(
		xint_mul(b0, a02), xint_mul(b1, a12)), xint_mul(b2, a22)), xint_mul(b3, a32));
	out->v[ 7] = xint_add(xint_add(xint_add(
		xint_mul(b0, a03), xint_mul(b1, a13)), xint_mul(b2, a23)), xint_mul(b3, a33));
	b0 = b->v[ 8];
	b1 = b->v[ 9];
	b2 = b->v[10];
	b3 = b->v[11];
	out->v[ 8] = xint_add(xint_add(xint_add(
		xint_mul(b0, a00), xint_mul(b1, a10)), xint_mul(b2, a20)), xint_mul(b3, a30));
	out->v[ 9] = xint_add(xint_add(xint_add(
		xint_mul(b0, a01), xint_mul(b1, a11)), xint_mul(b2, a21)), xint_mul(b3, a31));
	out->v[10] = xint_add(xint_add(xint_add(
		xint_mul(b0, a02), xint_mul(b1, a12)), xint_mul(b2, a22)), xint_mul(b3, a32));
	out->v[11] = xint_add(xint_add(xint_add(
		xint_mul(b0, a03), xint_mul(b1, a13)), xint_mul(b2, a23)), xint_mul(b3, a33));
	b0 = b->v[12];
	b1 = b->v[13];
	b2 = b->v[14];
	b3 = b->v[15];
	out->v[12] = xint_add(xint_add(xint_add(
		xint_mul(b0, a00), xint_mul(b1, a10)), xint_mul(b2, a20)), xint_mul(b3, a30));
	out->v[13] = xint_add(xint_add(xint_add(
		xint_mul(b0, a01), xint_mul(b1, a11)), xint_mul(b2, a21)), xint_mul(b3, a31));
	out->v[14] = xint_add(xint_add(xint_add(
		xint_mul(b0, a02), xint_mul(b1, a12)), xint_mul(b2, a22)), xint_mul(b3, a32));
	out->v[15] = xint_add(xint_add(xint_add(
		xint_mul(b0, a03), xint_mul(b1, a13)), xint_mul(b2, a23)), xint_mul(b3, a33));
	return out;
}

xmat4 *xmat4_orthogonal(xmat4 *out, xint W, xint H, xint N, xint F){
	xint nf = xint_div(XINT1, xint_sub(N, F));
	out->v[ 0] = xint_div(XINT(2), W);
	out->v[ 1] = 0;
	out->v[ 2] = 0;
	out->v[ 3] = 0;
	out->v[ 4] = 0;
	out->v[ 5] = xint_div(XINT(2), H);
	out->v[ 6] = 0;
	out->v[ 7] = 0;
	out->v[ 8] = 0;
	out->v[ 9] = 0;
	out->v[10] = nf << 1;
	out->v[11] = 0;
	out->v[12] = 0;
	out->v[13] = 0;
	out->v[14] = xint_mul(xint_add(N, F), nf);
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_perspective(xmat4 *out, xang fov, xint W, xint H, xint N, xint F){
	xint
		f  = xint_div(XINT1, xint_tan(fov >> 1)),
		nf = xint_div(XINT1, xint_sub(N, F));
	out->v[ 0] = f;
	out->v[ 1] =  0;
	out->v[ 2] =  0;
	out->v[ 3] =  0;
	out->v[ 4] =  0;
	out->v[ 5] = xint_div(xint_mul(f, W), H);
	out->v[ 6] =  0;
	out->v[ 7] =  0;
	out->v[ 8] =  0;
	out->v[ 9] =  0;
	out->v[10] = xint_mul(xint_add(F, N), nf);
	out->v[11] = -XINT1;
	out->v[12] =  0;
	out->v[13] =  0;
	out->v[14] = xint_mul(xint_mul(F, N) << 1, nf);
	out->v[15] =  0;
	return out;
}

xmat4 *xmat4_quat(xmat4 *out, xquat a){
	xint ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		ax2 = ax << 1,
		ay2 = ay << 1,
		az2 = az << 1,
		axx = xint_mul(ax, ax2),
		ayx = xint_mul(ay, ax2),
		ayy = xint_mul(ay, ay2),
		azx = xint_mul(az, ax2),
		azy = xint_mul(az, ay2),
		azz = xint_mul(az, az2),
		awx = xint_mul(aw, ax2),
		awy = xint_mul(aw, ay2),
		awz = xint_mul(aw, az2);
	out->v[ 0] = xint_sub(XINT1, xint_add(ayy, azz));
	out->v[ 1] =                 xint_add(ayx, awz);
	out->v[ 2] =                 xint_sub(azx, awy);
	out->v[ 3] = 0;
	out->v[ 4] =                 xint_sub(ayx, awz);
	out->v[ 5] = xint_sub(XINT1, xint_add(axx, azz));
	out->v[ 6] =                 xint_add(azy, awx);
	out->v[ 7] = 0;
	out->v[ 8] =                 xint_add(azx, awy);
	out->v[ 9] =                 xint_sub(azy, awx);
	out->v[10] = xint_sub(XINT1, xint_add(axx, ayy));
	out->v[11] = 0;
	out->v[12] = 0;
	out->v[13] = 0;
	out->v[14] = 0;
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_rotate(xmat4 *out, xmat4 *a, xvec3 axis, xang ang){
	xint
		x = axis.v[0], y = axis.v[1], z = axis.v[2],
		a00 = a->v[0], a01 = a->v[1], a02 = a->v[ 2], a03 = a->v[ 3],
		a10 = a->v[4], a11 = a->v[5], a12 = a->v[ 6], a13 = a->v[ 7],
		a20 = a->v[8], a21 = a->v[9], a22 = a->v[10], a23 = a->v[11],
		s = xint_sin(ang), c = xint_cos(ang),
		t = xint_sub(XINT1, c),
		b00 = xint_add(xint_mul(xint_mul(x, x), t), c             ),
		b01 = xint_add(xint_mul(xint_mul(y, x), t), xint_mul(z, s)),
		b02 = xint_sub(xint_mul(xint_mul(z, x), t), xint_mul(y, s)),
		b10 = xint_sub(xint_mul(xint_mul(x, y), t), xint_mul(z, s)),
		b11 = xint_add(xint_mul(xint_mul(y, y), t), c             ),
		b12 = xint_add(xint_mul(xint_mul(z, y), t), xint_mul(x, s)),
		b20 = xint_add(xint_mul(xint_mul(x, z), t), xint_mul(y, s)),
		b21 = xint_sub(xint_mul(xint_mul(y, z), t), xint_mul(x, s)),
		b22 = xint_add(xint_mul(xint_mul(z, z), t), c             );
	out->v[ 0] = xint_add(xint_add(xint_mul(a00, b00), xint_mul(a10, b01)), xint_mul(a20, b02));
	out->v[ 1] = xint_add(xint_add(xint_mul(a01, b00), xint_mul(a11, b01)), xint_mul(a21, b02));
	out->v[ 2] = xint_add(xint_add(xint_mul(a02, b00), xint_mul(a12, b01)), xint_mul(a22, b02));
	out->v[ 3] = xint_add(xint_add(xint_mul(a03, b00), xint_mul(a13, b01)), xint_mul(a23, b02));
	out->v[ 4] = xint_add(xint_add(xint_mul(a00, b10), xint_mul(a10, b11)), xint_mul(a20, b12));
	out->v[ 5] = xint_add(xint_add(xint_mul(a01, b10), xint_mul(a11, b11)), xint_mul(a21, b12));
	out->v[ 6] = xint_add(xint_add(xint_mul(a02, b10), xint_mul(a12, b11)), xint_mul(a22, b12));
	out->v[ 7] = xint_add(xint_add(xint_mul(a03, b10), xint_mul(a13, b11)), xint_mul(a23, b12));
	out->v[ 8] = xint_add(xint_add(xint_mul(a00, b20), xint_mul(a10, b21)), xint_mul(a20, b22));
	out->v[ 9] = xint_add(xint_add(xint_mul(a01, b20), xint_mul(a11, b21)), xint_mul(a21, b22));
	out->v[10] = xint_add(xint_add(xint_mul(a02, b20), xint_mul(a12, b21)), xint_mul(a22, b22));
	out->v[11] = xint_add(xint_add(xint_mul(a03, b20), xint_mul(a13, b21)), xint_mul(a23, b22));
	if (out != a){
		out->v[12] = a->v[12];
		out->v[13] = a->v[13];
		out->v[14] = a->v[14];
		out->v[15] = a->v[15];
	}
	return out;
}

xmat4 *xmat4_rotation(xmat4 *out, xvec3 axis, xang ang){
	xint x = axis.v[0], y = axis.v[1], z = axis.v[2],
		s = xint_sin(ang), c = xint_cos(ang),
		t = xint_sub(XINT1, c);
	out->v[ 0] = xint_add(xint_mul(xint_mul(x, x), t), c);
	out->v[ 1] = xint_add(xint_mul(xint_mul(y, x), t), xint_mul(z, s));
	out->v[ 2] = xint_sub(xint_mul(xint_mul(z, x), t), xint_mul(y, s));
	out->v[ 3] = 0;
	out->v[ 4] = xint_sub(xint_mul(xint_mul(x, y), t), xint_mul(z, s));
	out->v[ 5] = xint_add(xint_mul(xint_mul(y, y), t), c);
	out->v[ 6] = xint_add(xint_mul(xint_mul(z, y), t), xint_mul(x, s));
	out->v[ 7] = 0;
	out->v[ 8] = xint_add(xint_mul(xint_mul(x, z), t), xint_mul(y, s));
	out->v[ 9] = xint_sub(xint_mul(xint_mul(y, z), t), xint_mul(x, s));
	out->v[10] = xint_add(xint_mul(xint_mul(z, z), t), c);
	out->v[11] = 0;
	out->v[12] = 0;
	out->v[13] = 0;
	out->v[14] = 0;
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_rottrans(xmat4 *out, xquat a, xvec3 b){
	xint ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		ax2 = ax << 1,
		ay2 = ay << 1,
		az2 = az << 1,
		axx = xint_mul(ax, ax2),
		axy = xint_mul(ax, ay2),
		axz = xint_mul(ax, az2),
		ayy = xint_mul(ay, ay2),
		ayz = xint_mul(ay, az2),
		azz = xint_mul(az, az2),
		awx = xint_mul(aw, ax2),
		awy = xint_mul(aw, ay2),
		awz = xint_mul(aw, az2);
	out->v[ 0] = xint_sub(XINT1, xint_add(ayy, azz));
	out->v[ 1] =                 xint_add(axy, awz);
	out->v[ 2] =                 xint_sub(axz, awy);
	out->v[ 3] = 0;
	out->v[ 4] =                 xint_sub(axy, awz);
	out->v[ 5] = xint_sub(XINT1, xint_add(axx, azz));
	out->v[ 6] =                 xint_add(ayz, awx);
	out->v[ 7] = 0;
	out->v[ 8] =                 xint_add(axz, awy);
	out->v[ 9] =                 xint_sub(ayz, awx);
	out->v[10] = xint_sub(XINT1, xint_add(axx, ayy));
	out->v[11] = 0;
	out->v[12] = b.v[0];
	out->v[13] = b.v[1];
	out->v[14] = b.v[2];
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_rottransorigin(xmat4 *out, xquat a, xvec3 b, xvec3 origin){
	xint ax = a.v[0], ay = a.v[1], az = a.v[2], aw = a.v[3],
		ax2 = ax << 1,
		ay2 = ay << 1,
		az2 = az << 1,
		axx = xint_mul(ax, ax2),
		axy = xint_mul(ax, ay2),
		axz = xint_mul(ax, az2),
		ayy = xint_mul(ay, ay2),
		ayz = xint_mul(ay, az2),
		azz = xint_mul(az, az2),
		awx = xint_mul(aw, ax2),
		awy = xint_mul(aw, ay2),
		awz = xint_mul(aw, az2),
		ox = origin.v[0], oy = origin.v[1], oz = origin.v[2];
	out->v[ 0] = xint_sub(XINT1, xint_add(ayy, azz));
	out->v[ 1] =                 xint_add(axy, awz);
	out->v[ 2] =                 xint_sub(axz, awy);
	out->v[ 3] = 0;
	out->v[ 4] =                 xint_sub(axy, awz);
	out->v[ 5] = xint_sub(XINT1, xint_add(axx, azz));
	out->v[ 6] =                 xint_add(ayz, awx);
	out->v[ 7] = 0;
	out->v[ 8] =                 xint_add(axz, awy);
	out->v[ 9] =                 xint_sub(ayz, awx);
	out->v[10] = xint_sub(XINT1, xint_add(axx, ayy));
	out->v[11] = 0;
	out->v[12] = xint_sub(xint_add(b.v[0], ox), xint_add(xint_add(
		xint_mul(out->v[0], ox), xint_mul(out->v[4], oy)), xint_mul(out->v[ 8], oz)));
	out->v[13] = xint_sub(xint_add(b.v[1], oy), xint_add(xint_add(
		xint_mul(out->v[1], ox), xint_mul(out->v[5], oy)), xint_mul(out->v[ 9], oz)));
	out->v[14] = xint_sub(xint_add(b.v[2], oz), xint_add(xint_add(
		xint_mul(out->v[2], ox), xint_mul(out->v[6], oy)), xint_mul(out->v[10], oz)));
	out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_scale(xmat4 *out, xmat4 *a, xvec3 b){
	xint bx = b.v[0], by = b.v[1], bz = b.v[2];
	out->v[ 0] = xint_mul(a->v[ 0], bx);
	out->v[ 1] = xint_mul(a->v[ 1], bx);
	out->v[ 2] = xint_mul(a->v[ 2], bx);
	out->v[ 3] = xint_mul(a->v[ 3], bx);
	out->v[ 4] = xint_mul(a->v[ 4], by);
	out->v[ 5] = xint_mul(a->v[ 5], by);
	out->v[ 6] = xint_mul(a->v[ 6], by);
	out->v[ 7] = xint_mul(a->v[ 7], by);
	out->v[ 8] = xint_mul(a->v[ 8], bz);
	out->v[ 9] = xint_mul(a->v[ 9], bz);
	out->v[10] = xint_mul(a->v[10], bz);
	out->v[11] = xint_mul(a->v[11], bz);
	out->v[12] =          a->v[12]     ;
	out->v[13] =          a->v[13]     ;
	out->v[14] =          a->v[14]     ;
	out->v[15] =          a->v[15]     ;
	return out;
}

xmat4 *xmat4_scaling(xmat4 *out, xvec3 a){
	out->v[ 0] = a.v[0]; out->v[ 1] =      0; out->v[ 2] =      0; out->v[ 3] =     0;
	out->v[ 4] =      0; out->v[ 5] = a.v[1]; out->v[ 6] =      0; out->v[ 7] =     0;
	out->v[ 8] =      0; out->v[ 9] =      0; out->v[10] = a.v[2]; out->v[11] =     0;
	out->v[12] =      0; out->v[13] =      0; out->v[14] =      0; out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_sub(xmat4 *out, xmat4 *a, xmat4 *b){
	out->v[ 0] = xint_sub(a->v[ 0], b->v[ 0]);
	out->v[ 1] = xint_sub(a->v[ 1], b->v[ 1]);
	out->v[ 2] = xint_sub(a->v[ 2], b->v[ 2]);
	out->v[ 3] = xint_sub(a->v[ 3], b->v[ 3]);
	out->v[ 4] = xint_sub(a->v[ 4], b->v[ 4]);
	out->v[ 5] = xint_sub(a->v[ 5], b->v[ 5]);
	out->v[ 6] = xint_sub(a->v[ 6], b->v[ 6]);
	out->v[ 7] = xint_sub(a->v[ 7], b->v[ 7]);
	out->v[ 8] = xint_sub(a->v[ 8], b->v[ 8]);
	out->v[ 9] = xint_sub(a->v[ 9], b->v[ 9]);
	out->v[10] = xint_sub(a->v[10], b->v[10]);
	out->v[11] = xint_sub(a->v[11], b->v[11]);
	out->v[12] = xint_sub(a->v[12], b->v[12]);
	out->v[13] = xint_sub(a->v[13], b->v[13]);
	out->v[14] = xint_sub(a->v[14], b->v[14]);
	out->v[15] = xint_sub(a->v[15], b->v[15]);
	return out;
}

xmat4 *xmat4_translate(xmat4 *out, xmat4 *a, xvec3 b){
	xint bx = b.v[0], by = b.v[1], bz = b.v[2];
	if (out == a){
		out->v[12] = xint_add(xint_add(xint_add(
			xint_mul(a->v[0], bx), xint_mul(a->v[4], by)), xint_mul(a->v[ 8], bz)), a->v[12]);
		out->v[13] = xint_add(xint_add(xint_add(
			xint_mul(a->v[1], bx), xint_mul(a->v[5], by)), xint_mul(a->v[ 9], bz)), a->v[13]);
		out->v[14] = xint_add(xint_add(xint_add(
			xint_mul(a->v[2], bx), xint_mul(a->v[6], by)), xint_mul(a->v[10], bz)), a->v[14]);
		out->v[15] = xint_add(xint_add(xint_add(
			xint_mul(a->v[3], bx), xint_mul(a->v[7], by)), xint_mul(a->v[11], bz)), a->v[15]);
	}
	else{
		xint
			a00 = a->v[0], a01 = a->v[1], a02 = a->v[ 2], a03 = a->v[ 3],
			a10 = a->v[4], a11 = a->v[5], a12 = a->v[ 6], a13 = a->v[ 7],
			a20 = a->v[8], a21 = a->v[9], a22 = a->v[10], a23 = a->v[11];
		out->v[ 0] = a00;
		out->v[ 1] = a01;
		out->v[ 2] = a02;
		out->v[ 3] = a03;
		out->v[ 4] = a10;
		out->v[ 5] = a11;
		out->v[ 6] = a12;
		out->v[ 7] = a13;
		out->v[ 8] = a20;
		out->v[ 9] = a21;
		out->v[10] = a22;
		out->v[11] = a23;
		out->v[12] = xint_add(xint_add(xint_add(
			xint_mul(a00, bx), xint_mul(a10, by)), xint_mul(a20, bz)), a->v[12]);
		out->v[13] = xint_add(xint_add(xint_add(
			xint_mul(a01, bx), xint_mul(a11, by)), xint_mul(a21, bz)), a->v[13]);
		out->v[14] = xint_add(xint_add(xint_add(
			xint_mul(a02, bx), xint_mul(a12, by)), xint_mul(a22, bz)), a->v[14]);
		out->v[15] = xint_add(xint_add(xint_add(
			xint_mul(a03, bx), xint_mul(a13, by)), xint_mul(a23, bz)), a->v[15]);
	}
	return out;
}

xmat4 *xmat4_translation(xmat4 *out, xvec3 a){
	out->v[ 0] = XINT1; out->v[ 1] =     0; out->v[ 2] =     0; out->v[ 3] =    0;
	out->v[ 4] =     0; out->v[ 5] = XINT1; out->v[ 6] =     0; out->v[ 7] =    0;
	out->v[ 8] =     0; out->v[ 9] =     0; out->v[10] = XINT1; out->v[11] =    0;
	out->v[12] = a.v[0]; out->v[13] = a.v[1]; out->v[14] = a.v[2]; out->v[15] = XINT1;
	return out;
}

xmat4 *xmat4_transpose(xmat4 *out, xmat4 *a){
	if (out == a){
		xint
			a01 = a->v[1], a02 = a->v[2], a03 = a->v[ 3],
			/*          */ a12 = a->v[6], a13 = a->v[ 7],
			/*                         */ a23 = a->v[11];
		out->v[ 1] = a->v[ 4];
		out->v[ 2] = a->v[ 8];
		out->v[ 3] = a->v[12];
		out->v[ 4] = a01;
		out->v[ 6] = a->v[ 9];
		out->v[ 7] = a->v[13];
		out->v[ 8] = a02;
		out->v[ 9] = a12;
		out->v[11] = a->v[14];
		out->v[12] = a03;
		out->v[13] = a13;
		out->v[14] = a23;
	}
	else{
		out->v[ 0] = a->v[ 0]; out->v[ 1] = a->v[ 4]; out->v[ 2] = a->v[ 8]; out->v[ 3] = a->v[12];
		out->v[ 4] = a->v[ 1]; out->v[ 5] = a->v[ 5]; out->v[ 6] = a->v[ 9]; out->v[ 7] = a->v[13];
		out->v[ 8] = a->v[ 2]; out->v[ 9] = a->v[ 6]; out->v[10] = a->v[10]; out->v[11] = a->v[14];
		out->v[12] = a->v[ 3]; out->v[13] = a->v[ 7]; out->v[14] = a->v[11]; out->v[15] = a->v[15];
	}
	return out;
}

/* sorry for the mess, but this is the lookup table for sin and tan */
const xint xint_sin__lut[XANG360] = {
	0, 101, 201, 302, 402, 503, 603, 704, 804, 905, 1005, 1106, 1206, 1307, 1407, 1508, 1608, 1709,
	1809, 1910, 2010, 2111, 2211, 2312, 2412, 2513, 2613, 2714, 2814, 2914, 3015, 3115, 3216, 3316,
	3417, 3517, 3617, 3718, 3818, 3918, 4019, 4119, 4219, 4320, 4420, 4520, 4621, 4721, 4821, 4921,
	5022, 5122, 5222, 5322, 5422, 5523, 5623, 5723, 5823, 5923, 6023, 6123, 6224, 6324, 6424, 6524,
	6624, 6724, 6824, 6924, 7024, 7124, 7224, 7323, 7423, 7523, 7623, 7723, 7823, 7923, 8022, 8122,
	8222, 8322, 8421, 8521, 8621, 8720, 8820, 8919, 9019, 9119, 9218, 9318, 9417, 9517, 9616, 9716,
	9815, 9914, 10014, 10113, 10212, 10312, 10411, 10510, 10609, 10709, 10808, 10907, 11006, 11105,
	11204, 11303, 11402, 11501, 11600, 11699, 11798, 11897, 11996, 12095, 12193, 12292, 12391,
	12490, 12588, 12687, 12785, 12884, 12983, 13081, 13180, 13278, 13376, 13475, 13573, 13672,
	13770, 13868, 13966, 14065, 14163, 14261, 14359, 14457, 14555, 14653, 14751, 14849, 14947,
	15045, 15143, 15240, 15338, 15436, 15534, 15631, 15729, 15826, 15924, 16021, 16119, 16216,
	16314, 16411, 16508, 16606, 16703, 16800, 16897, 16994, 17091, 17188, 17285, 17382, 17479,
	17576, 17673, 17770, 17867, 17963, 18060, 18156, 18253, 18350, 18446, 18543, 18639, 18735,
	18832, 18928, 19024, 19120, 19216, 19313, 19409, 19505, 19600, 19696, 19792, 19888, 19984,
	20080, 20175, 20271, 20366, 20462, 20557, 20653, 20748, 20844, 20939, 21034, 21129, 21224,
	21320, 21415, 21510, 21604, 21699, 21794, 21889, 21984, 22078, 22173, 22268, 22362, 22457,
	22551, 22645, 22740, 22834, 22928, 23022, 23116, 23210, 23304, 23398, 23492, 23586, 23680,
	23774, 23867, 23961, 24054, 24148, 24241, 24335, 24428, 24521, 24614, 24708, 24801, 24894,
	24987, 25080, 25172, 25265, 25358, 25451, 25543, 25636, 25728, 25821, 25913, 26005, 26098,
	26190, 26282, 26374, 26466, 26558, 26650, 26742, 26833, 26925, 27017, 27108, 27200, 27291,
	27382, 27474, 27565, 27656, 27747, 27838, 27929, 28020, 28111, 28202, 28293, 28383, 28474,
	28564, 28655, 28745, 28835, 28926, 29016, 29106, 29196, 29286, 29376, 29466, 29555, 29645,
	29735, 29824, 29914, 30003, 30093, 30182, 30271, 30360, 30449, 30538, 30627, 30716, 30805,
	30893, 30982, 31071, 31159, 31248, 31336, 31424, 31512, 31600, 31688, 31776, 31864, 31952,
	32040, 32127, 32215, 32303, 32390, 32477, 32565, 32652, 32739, 32826, 32913, 33000, 33087,
	33173, 33260, 33347, 33433, 33520, 33606, 33692, 33778, 33865, 33951, 34037, 34122, 34208,
	34294, 34380, 34465, 34551, 34636, 34721, 34806, 34892, 34977, 35062, 35146, 35231, 35316,
	35401, 35485, 35570, 35654, 35738, 35823, 35907, 35991, 36075, 36159, 36243, 36326, 36410,
	36493, 36577, 36660, 36744, 36827, 36910, 36993, 37076, 37159, 37241, 37324, 37407, 37489,
	37572, 37654, 37736, 37818, 37900, 37982, 38064, 38146, 38228, 38309, 38391, 38472, 38554,
	38635, 38716, 38797, 38878, 38959, 39040, 39120, 39201, 39282, 39362, 39442, 39523, 39603,
	39683, 39763, 39843, 39922, 40002, 40082, 40161, 40241, 40320, 40399, 40478, 40557, 40636,
	40715, 40794, 40872, 40951, 41029, 41108, 41186, 41264, 41342, 41420, 41498, 41576, 41653,
	41731, 41808, 41886, 41963, 42040, 42117, 42194, 42271, 42348, 42424, 42501, 42578, 42654,
	42730, 42806, 42882, 42958, 43034, 43110, 43186, 43261, 43337, 43412, 43487, 43563, 43638,
	43713, 43787, 43862, 43937, 44011, 44086, 44160, 44234, 44308, 44382, 44456, 44530, 44604,
	44677, 44751, 44824, 44898, 44971, 45044, 45117, 45190, 45262, 45335, 45408, 45480, 45552,
	45625, 45697, 45769, 45841, 45912, 45984, 46056, 46127, 46199, 46270, 46341, 46412, 46483,
	46554, 46624, 46695, 46766, 46836, 46906, 46976, 47046, 47116, 47186, 47256, 47325, 47395,
	47464, 47534, 47603, 47672, 47741, 47809, 47878, 47947, 48015, 48084, 48152, 48220, 48288,
	48356, 48424, 48491, 48559, 48626, 48694, 48761, 48828, 48895, 48962, 49029, 49095, 49162,
	49228, 49295, 49361, 49427, 49493, 49559, 49624, 49690, 49756, 49821, 49886, 49951, 50016,
	50081, 50146, 50211, 50275, 50340, 50404, 50468, 50532, 50596, 50660, 50724, 50787, 50851,
	50914, 50977, 51041, 51104, 51166, 51229, 51292, 51354, 51417, 51479, 51541, 51603, 51665,
	51727, 51789, 51850, 51911, 51973, 52034, 52095, 52156, 52217, 52277, 52338, 52398, 52459,
	52519, 52579, 52639, 52699, 52759, 52818, 52878, 52937, 52996, 53055, 53114, 53173, 53232,
	53290, 53349, 53407, 53465, 53523, 53581, 53639, 53697, 53754, 53812, 53869, 53926, 53983,
	54040, 54097, 54154, 54210, 54267, 54323, 54379, 54435, 54491, 54547, 54603, 54658, 54714,
	54769, 54824, 54879, 54934, 54989, 55043, 55098, 55152, 55206, 55260, 55314, 55368, 55422,
	55476, 55529, 55582, 55636, 55689, 55742, 55794, 55847, 55900, 55952, 56004, 56056, 56108,
	56160, 56212, 56264, 56315, 56367, 56418, 56469, 56520, 56571, 56621, 56672, 56722, 56773,
	56823, 56873, 56923, 56972, 57022, 57072, 57121, 57170, 57219, 57268, 57317, 57366, 57414,
	57463, 57511, 57559, 57607, 57655, 57703, 57750, 57798, 57845, 57892, 57939, 57986, 58033,
	58079, 58126, 58172, 58219, 58265, 58311, 58356, 58402, 58448, 58493, 58538, 58583, 58628,
	58673, 58718, 58763, 58807, 58851, 58896, 58940, 58983, 59027, 59071, 59114, 59158, 59201,
	59244, 59287, 59330, 59372, 59415, 59457, 59499, 59541, 59583, 59625, 59667, 59708, 59750,
	59791, 59832, 59873, 59914, 59954, 59995, 60035, 60075, 60116, 60156, 60195, 60235, 60275,
	60314, 60353, 60392, 60431, 60470, 60509, 60547, 60586, 60624, 60662, 60700, 60738, 60776,
	60813, 60851, 60888, 60925, 60962, 60999, 61035, 61072, 61108, 61145, 61181, 61217, 61253,
	61288, 61324, 61359, 61394, 61429, 61464, 61499, 61534, 61568, 61603, 61637, 61671, 61705,
	61739, 61772, 61806, 61839, 61873, 61906, 61939, 61971, 62004, 62036, 62069, 62101, 62133,
	62165, 62197, 62228, 62260, 62291, 62322, 62353, 62384, 62415, 62445, 62476, 62506, 62536,
	62566, 62596, 62626, 62655, 62685, 62714, 62743, 62772, 62801, 62830, 62858, 62886, 62915,
	62943, 62971, 62998, 63026, 63054, 63081, 63108, 63135, 63162, 63189, 63215, 63242, 63268,
	63294, 63320, 63346, 63372, 63397, 63423, 63448, 63473, 63498, 63523, 63547, 63572, 63596,
	63621, 63645, 63668, 63692, 63716, 63739, 63763, 63786, 63809, 63832, 63854, 63877, 63899,
	63922, 63944, 63966, 63987, 64009, 64031, 64052, 64073, 64094, 64115, 64136, 64156, 64177,
	64197, 64217, 64237, 64257, 64277, 64296, 64316, 64335, 64354, 64373, 64392, 64410, 64429,
	64447, 64465, 64483, 64501, 64519, 64536, 64554, 64571, 64588, 64605, 64622, 64639, 64655,
	64672, 64688, 64704, 64720, 64735, 64751, 64766, 64782, 64797, 64812, 64827, 64841, 64856,
	64870, 64884, 64899, 64912, 64926, 64940, 64953, 64967, 64980, 64993, 65006, 65018, 65031,
	65043, 65055, 65067, 65079, 65091, 65103, 65114, 65126, 65137, 65148, 65159, 65169, 65180,
	65190, 65200, 65210, 65220, 65230, 65240, 65249, 65259, 65268, 65277, 65286, 65294, 65303,
	65311, 65320, 65328, 65336, 65343, 65351, 65358, 65366, 65373, 65380, 65387, 65393, 65400,
	65406, 65413, 65419, 65425, 65430, 65436, 65442, 65447, 65452, 65457, 65462, 65467, 65471,
	65476, 65480, 65484, 65488, 65492, 65495, 65499, 65502, 65505, 65508, 65511, 65514, 65516,
	65519, 65521, 65523, 65525, 65527, 65528, 65530, 65531, 65532, 65533, 65534, 65535, 65535,
	65536, 65536, 65536, 65536, 65536, 65535, 65535, 65534, 65533, 65532, 65531, 65530, 65528,
	65527, 65525, 65523, 65521, 65519, 65516, 65514, 65511, 65508, 65505, 65502, 65499, 65495,
	65492, 65488, 65484, 65480, 65476, 65471, 65467, 65462, 65457, 65452, 65447, 65442, 65436,
	65430, 65425, 65419, 65413, 65406, 65400, 65393, 65387, 65380, 65373, 65366, 65358, 65351,
	65343, 65336, 65328, 65320, 65311, 65303, 65294, 65286, 65277, 65268, 65259, 65249, 65240,
	65230, 65220, 65210, 65200, 65190, 65180, 65169, 65159, 65148, 65137, 65126, 65114, 65103,
	65091, 65079, 65067, 65055, 65043, 65031, 65018, 65006, 64993, 64980, 64967, 64953, 64940,
	64926, 64912, 64899, 64884, 64870, 64856, 64841, 64827, 64812, 64797, 64782, 64766, 64751,
	64735, 64720, 64704, 64688, 64672, 64655, 64639, 64622, 64605, 64588, 64571, 64554, 64536,
	64519, 64501, 64483, 64465, 64447, 64429, 64410, 64392, 64373, 64354, 64335, 64316, 64296,
	64277, 64257, 64237, 64217, 64197, 64177, 64156, 64136, 64115, 64094, 64073, 64052, 64031,
	64009, 63987, 63966, 63944, 63922, 63899, 63877, 63854, 63832, 63809, 63786, 63763, 63739,
	63716, 63692, 63668, 63645, 63621, 63596, 63572, 63547, 63523, 63498, 63473, 63448, 63423,
	63397, 63372, 63346, 63320, 63294, 63268, 63242, 63215, 63189, 63162, 63135, 63108, 63081,
	63054, 63026, 62998, 62971, 62943, 62915, 62886, 62858, 62830, 62801, 62772, 62743, 62714,
	62685, 62655, 62626, 62596, 62566, 62536, 62506, 62476, 62445, 62415, 62384, 62353, 62322,
	62291, 62260, 62228, 62197, 62165, 62133, 62101, 62069, 62036, 62004, 61971, 61939, 61906,
	61873, 61839, 61806, 61772, 61739, 61705, 61671, 61637, 61603, 61568, 61534, 61499, 61464,
	61429, 61394, 61359, 61324, 61288, 61253, 61217, 61181, 61145, 61108, 61072, 61035, 60999,
	60962, 60925, 60888, 60851, 60813, 60776, 60738, 60700, 60662, 60624, 60586, 60547, 60509,
	60470, 60431, 60392, 60353, 60314, 60275, 60235, 60195, 60156, 60116, 60075, 60035, 59995,
	59954, 59914, 59873, 59832, 59791, 59750, 59708, 59667, 59625, 59583, 59541, 59499, 59457,
	59415, 59372, 59330, 59287, 59244, 59201, 59158, 59114, 59071, 59027, 58983, 58940, 58896,
	58851, 58807, 58763, 58718, 58673, 58628, 58583, 58538, 58493, 58448, 58402, 58356, 58311,
	58265, 58219, 58172, 58126, 58079, 58033, 57986, 57939, 57892, 57845, 57798, 57750, 57703,
	57655, 57607, 57559, 57511, 57463, 57414, 57366, 57317, 57268, 57219, 57170, 57121, 57072,
	57022, 56972, 56923, 56873, 56823, 56773, 56722, 56672, 56621, 56571, 56520, 56469, 56418,
	56367, 56315, 56264, 56212, 56160, 56108, 56056, 56004, 55952, 55900, 55847, 55794, 55742,
	55689, 55636, 55582, 55529, 55476, 55422, 55368, 55314, 55260, 55206, 55152, 55098, 55043,
	54989, 54934, 54879, 54824, 54769, 54714, 54658, 54603, 54547, 54491, 54435, 54379, 54323,
	54267, 54210, 54154, 54097, 54040, 53983, 53926, 53869, 53812, 53754, 53697, 53639, 53581,
	53523, 53465, 53407, 53349, 53290, 53232, 53173, 53114, 53055, 52996, 52937, 52878, 52818,
	52759, 52699, 52639, 52579, 52519, 52459, 52398, 52338, 52277, 52217, 52156, 52095, 52034,
	51973, 51911, 51850, 51789, 51727, 51665, 51603, 51541, 51479, 51417, 51354, 51292, 51229,
	51166, 51104, 51041, 50977, 50914, 50851, 50787, 50724, 50660, 50596, 50532, 50468, 50404,
	50340, 50275, 50211, 50146, 50081, 50016, 49951, 49886, 49821, 49756, 49690, 49624, 49559,
	49493, 49427, 49361, 49295, 49228, 49162, 49095, 49029, 48962, 48895, 48828, 48761, 48694,
	48626, 48559, 48491, 48424, 48356, 48288, 48220, 48152, 48084, 48015, 47947, 47878, 47809,
	47741, 47672, 47603, 47534, 47464, 47395, 47325, 47256, 47186, 47116, 47046, 46976, 46906,
	46836, 46766, 46695, 46624, 46554, 46483, 46412, 46341, 46270, 46199, 46127, 46056, 45984,
	45912, 45841, 45769, 45697, 45625, 45552, 45480, 45408, 45335, 45262, 45190, 45117, 45044,
	44971, 44898, 44824, 44751, 44677, 44604, 44530, 44456, 44382, 44308, 44234, 44160, 44086,
	44011, 43937, 43862, 43787, 43713, 43638, 43562, 43487, 43412, 43337, 43261, 43186, 43110,
	43034, 42958, 42882, 42806, 42730, 42654, 42578, 42501, 42424, 42348, 42271, 42194, 42117,
	42040, 41963, 41886, 41808, 41731, 41653, 41576, 41498, 41420, 41342, 41264, 41186, 41108,
	41029, 40951, 40872, 40794, 40715, 40636, 40557, 40478, 40399, 40320, 40241, 40161, 40082,
	40002, 39922, 39843, 39763, 39683, 39603, 39523, 39442, 39362, 39282, 39201, 39120, 39040,
	38959, 38878, 38797, 38716, 38635, 38554, 38472, 38391, 38309, 38228, 38146, 38064, 37982,
	37900, 37818, 37736, 37654, 37572, 37489, 37407, 37324, 37241, 37159, 37076, 36993, 36910,
	36827, 36744, 36660, 36577, 36493, 36410, 36326, 36242, 36159, 36075, 35991, 35907, 35823,
	35738, 35654, 35570, 35485, 35401, 35316, 35231, 35146, 35062, 34977, 34892, 34806, 34721,
	34636, 34551, 34465, 34380, 34294, 34208, 34122, 34037, 33951, 33865, 33778, 33692, 33606,
	33520, 33433, 33347, 33260, 33173, 33087, 33000, 32913, 32826, 32739, 32652, 32565, 32477,
	32390, 32303, 32215, 32127, 32040, 31952, 31864, 31776, 31688, 31600, 31512, 31424, 31336,
	31248, 31159, 31071, 30982, 30893, 30805, 30716, 30627, 30538, 30449, 30360, 30271, 30182,
	30093, 30003, 29914, 29824, 29735, 29645, 29555, 29466, 29376, 29286, 29196, 29106, 29016,
	28926, 28835, 28745, 28655, 28564, 28474, 28383, 28293, 28202, 28111, 28020, 27929, 27838,
	27747, 27656, 27565, 27474, 27382, 27291, 27200, 27108, 27017, 26925, 26833, 26742, 26650,
	26558, 26466, 26374, 26282, 26190, 26098, 26005, 25913, 25821, 25728, 25636, 25543, 25451,
	25358, 25265, 25172, 25080, 24987, 24894, 24801, 24708, 24614, 24521, 24428, 24335, 24241,
	24148, 24054, 23961, 23867, 23774, 23680, 23586, 23492, 23398, 23304, 23210, 23116, 23022,
	22928, 22834, 22740, 22645, 22551, 22457, 22362, 22268, 22173, 22078, 21984, 21889, 21794,
	21699, 21604, 21510, 21415, 21320, 21224, 21129, 21034, 20939, 20844, 20748, 20653, 20557,
	20462, 20366, 20271, 20175, 20080, 19984, 19888, 19792, 19696, 19600, 19505, 19409, 19312,
	19216, 19120, 19024, 18928, 18832, 18735, 18639, 18543, 18446, 18350, 18253, 18156, 18060,
	17963, 17867, 17770, 17673, 17576, 17479, 17382, 17285, 17188, 17091, 16994, 16897, 16800,
	16703, 16606, 16508, 16411, 16314, 16216, 16119, 16021, 15924, 15826, 15729, 15631, 15534,
	15436, 15338, 15240, 15143, 15045, 14947, 14849, 14751, 14653, 14555, 14457, 14359, 14261,
	14163, 14065, 13966, 13868, 13770, 13672, 13573, 13475, 13376, 13278, 13180, 13081, 12983,
	12884, 12785, 12687, 12588, 12490, 12391, 12292, 12193, 12095, 11996, 11897, 11798, 11699,
	11600, 11501, 11402, 11303, 11204, 11105, 11006, 10907, 10808, 10709, 10609, 10510, 10411,
	10312, 10212, 10113, 10014, 9914, 9815, 9716, 9616, 9517, 9417, 9318, 9218, 9119, 9019, 8919,
	8820, 8720, 8621, 8521, 8421, 8322, 8222, 8122, 8022, 7923, 7823, 7723, 7623, 7523, 7423, 7323,
	7224, 7124, 7024, 6924, 6824, 6724, 6624, 6524, 6424, 6324, 6224, 6123, 6023, 5923, 5823, 5723,
	5623, 5523, 5422, 5322, 5222, 5122, 5022, 4921, 4821, 4721, 4621, 4520, 4420, 4320, 4219, 4119,
	4019, 3918, 3818, 3718, 3617, 3517, 3416, 3316, 3216, 3115, 3015, 2914, 2814, 2714, 2613, 2513,
	2412, 2312, 2211, 2111, 2010, 1910, 1809, 1709, 1608, 1508, 1407, 1307, 1206, 1106, 1005, 905,
	804, 704, 603, 503, 402, 302, 201, 101, 0, -101, -201, -302, -402, -503, -603, -704, -804, -905,
	-1005, -1106, -1206, -1307, -1407, -1508, -1608, -1709, -1809, -1910, -2010, -2111, -2211,
	-2312, -2412, -2513, -2613, -2714, -2814, -2914, -3015, -3115, -3216, -3316, -3417, -3517,
	-3617, -3718, -3818, -3918, -4019, -4119, -4219, -4320, -4420, -4520, -4621, -4721, -4821,
	-4921, -5022, -5122, -5222, -5322, -5422, -5523, -5623, -5723, -5823, -5923, -6023, -6123,
	-6224, -6324, -6424, -6524, -6624, -6724, -6824, -6924, -7024, -7124, -7224, -7323, -7423,
	-7523, -7623, -7723, -7823, -7923, -8022, -8122, -8222, -8322, -8421, -8521, -8621, -8720,
	-8820, -8919, -9019, -9119, -9218, -9318, -9417, -9517, -9616, -9716, -9815, -9914, -10014,
	-10113, -10212, -10312, -10411, -10510, -10609, -10709, -10808, -10907, -11006, -11105, -11204,
	-11303, -11402, -11501, -11600, -11699, -11798, -11897, -11996, -12095, -12193, -12292, -12391,
	-12490, -12588, -12687, -12785, -12884, -12983, -13081, -13180, -13278, -13376, -13475, -13573,
	-13672, -13770, -13868, -13966, -14065, -14163, -14261, -14359, -14457, -14555, -14653, -14751,
	-14849, -14947, -15045, -15143, -15240, -15338, -15436, -15534, -15631, -15729, -15826, -15924,
	-16021, -16119, -16216, -16314, -16411, -16508, -16606, -16703, -16800, -16897, -16994, -17091,
	-17188, -17285, -17382, -17479, -17576, -17673, -17770, -17867, -17963, -18060, -18157, -18253,
	-18350, -18446, -18543, -18639, -18735, -18832, -18928, -19024, -19120, -19216, -19313, -19409,
	-19505, -19600, -19696, -19792, -19888, -19984, -20080, -20175, -20271, -20366, -20462, -20557,
	-20653, -20748, -20844, -20939, -21034, -21129, -21224, -21320, -21415, -21510, -21605, -21699,
	-21794, -21889, -21984, -22078, -22173, -22268, -22362, -22457, -22551, -22645, -22740, -22834,
	-22928, -23022, -23116, -23210, -23304, -23398, -23492, -23586, -23680, -23774, -23867, -23961,
	-24054, -24148, -24241, -24335, -24428, -24521, -24614, -24708, -24801, -24894, -24987, -25080,
	-25172, -25265, -25358, -25451, -25543, -25636, -25728, -25821, -25913, -26005, -26098, -26190,
	-26282, -26374, -26466, -26558, -26650, -26742, -26833, -26925, -27017, -27108, -27200, -27291,
	-27383, -27474, -27565, -27656, -27747, -27838, -27929, -28020, -28111, -28202, -28293, -28383,
	-28474, -28564, -28655, -28745, -28835, -28926, -29016, -29106, -29196, -29286, -29376, -29466,
	-29555, -29645, -29735, -29824, -29914, -30003, -30093, -30182, -30271, -30360, -30449, -30538,
	-30627, -30716, -30805, -30893, -30982, -31071, -31159, -31248, -31336, -31424, -31512, -31600,
	-31688, -31776, -31864, -31952, -32040, -32127, -32215, -32303, -32390, -32477, -32565, -32652,
	-32739, -32826, -32913, -33000, -33087, -33173, -33260, -33347, -33433, -33520, -33606, -33692,
	-33778, -33865, -33951, -34037, -34122, -34208, -34294, -34380, -34465, -34551, -34636, -34721,
	-34806, -34892, -34977, -35062, -35146, -35231, -35316, -35401, -35485, -35570, -35654, -35738,
	-35823, -35907, -35991, -36075, -36159, -36243, -36326, -36410, -36493, -36577, -36660, -36744,
	-36827, -36910, -36993, -37076, -37159, -37241, -37324, -37407, -37489, -37572, -37654, -37736,
	-37818, -37900, -37982, -38064, -38146, -38228, -38309, -38391, -38472, -38554, -38635, -38716,
	-38797, -38878, -38959, -39040, -39120, -39201, -39282, -39362, -39442, -39523, -39603, -39683,
	-39763, -39843, -39922, -40002, -40082, -40161, -40241, -40320, -40399, -40478, -40557, -40636,
	-40715, -40794, -40872, -40951, -41029, -41108, -41186, -41264, -41342, -41420, -41498, -41576,
	-41653, -41731, -41808, -41886, -41963, -42040, -42117, -42194, -42271, -42348, -42424, -42501,
	-42578, -42654, -42730, -42806, -42882, -42958, -43034, -43110, -43186, -43261, -43337, -43412,
	-43487, -43563, -43638, -43713, -43787, -43862, -43937, -44011, -44086, -44160, -44234, -44308,
	-44382, -44456, -44530, -44604, -44677, -44751, -44824, -44898, -44971, -45044, -45117, -45190,
	-45262, -45335, -45408, -45480, -45552, -45625, -45697, -45769, -45841, -45912, -45984, -46056,
	-46127, -46199, -46270, -46341, -46412, -46483, -46554, -46624, -46695, -46766, -46836, -46906,
	-46976, -47046, -47116, -47186, -47256, -47325, -47395, -47464, -47534, -47603, -47672, -47741,
	-47809, -47878, -47947, -48015, -48084, -48152, -48220, -48288, -48356, -48424, -48491, -48559,
	-48626, -48694, -48761, -48828, -48895, -48962, -49029, -49095, -49162, -49228, -49295, -49361,
	-49427, -49493, -49559, -49624, -49690, -49756, -49821, -49886, -49951, -50016, -50081, -50146,
	-50211, -50275, -50340, -50404, -50468, -50532, -50596, -50660, -50724, -50787, -50851, -50914,
	-50977, -51041, -51104, -51166, -51229, -51292, -51354, -51417, -51479, -51541, -51603, -51665,
	-51727, -51789, -51850, -51912, -51973, -52034, -52095, -52156, -52217, -52277, -52338, -52398,
	-52459, -52519, -52579, -52639, -52699, -52759, -52818, -52878, -52937, -52996, -53055, -53114,
	-53173, -53232, -53290, -53349, -53407, -53465, -53523, -53581, -53639, -53697, -53754, -53812,
	-53869, -53926, -53983, -54040, -54097, -54154, -54210, -54267, -54323, -54379, -54435, -54491,
	-54547, -54603, -54658, -54714, -54769, -54824, -54879, -54934, -54989, -55043, -55098, -55152,
	-55206, -55261, -55314, -55368, -55422, -55476, -55529, -55582, -55636, -55689, -55742, -55794,
	-55847, -55900, -55952, -56004, -56056, -56108, -56160, -56212, -56264, -56315, -56367, -56418,
	-56469, -56520, -56571, -56621, -56672, -56722, -56773, -56823, -56873, -56923, -56972, -57022,
	-57072, -57121, -57170, -57219, -57268, -57317, -57366, -57414, -57463, -57511, -57559, -57607,
	-57655, -57703, -57750, -57798, -57845, -57892, -57939, -57986, -58033, -58079, -58126, -58172,
	-58219, -58265, -58311, -58356, -58402, -58448, -58493, -58538, -58583, -58628, -58673, -58718,
	-58763, -58807, -58851, -58896, -58940, -58983, -59027, -59071, -59114, -59158, -59201, -59244,
	-59287, -59330, -59372, -59415, -59457, -59499, -59541, -59583, -59625, -59667, -59708, -59750,
	-59791, -59832, -59873, -59914, -59954, -59995, -60035, -60075, -60116, -60156, -60195, -60235,
	-60275, -60314, -60353, -60392, -60431, -60470, -60509, -60547, -60586, -60624, -60662, -60700,
	-60738, -60776, -60813, -60851, -60888, -60925, -60962, -60999, -61035, -61072, -61108, -61145,
	-61181, -61217, -61253, -61288, -61324, -61359, -61394, -61429, -61464, -61499, -61534, -61568,
	-61603, -61637, -61671, -61705, -61739, -61772, -61806, -61839, -61873, -61906, -61939, -61971,
	-62004, -62036, -62069, -62101, -62133, -62165, -62197, -62228, -62260, -62291, -62322, -62353,
	-62384, -62415, -62445, -62476, -62506, -62536, -62566, -62596, -62626, -62655, -62685, -62714,
	-62743, -62772, -62801, -62830, -62858, -62886, -62915, -62943, -62971, -62998, -63026, -63054,
	-63081, -63108, -63135, -63162, -63189, -63215, -63242, -63268, -63294, -63320, -63346, -63372,
	-63397, -63423, -63448, -63473, -63498, -63523, -63547, -63572, -63596, -63621, -63645, -63668,
	-63692, -63716, -63739, -63763, -63786, -63809, -63832, -63854, -63877, -63899, -63922, -63944,
	-63966, -63987, -64009, -64031, -64052, -64073, -64094, -64115, -64136, -64156, -64177, -64197,
	-64217, -64237, -64257, -64277, -64296, -64316, -64335, -64354, -64373, -64392, -64410, -64429,
	-64447, -64465, -64483, -64501, -64519, -64536, -64554, -64571, -64588, -64605, -64622, -64639,
	-64655, -64672, -64688, -64704, -64720, -64735, -64751, -64766, -64782, -64797, -64812, -64827,
	-64841, -64856, -64870, -64884, -64899, -64912, -64926, -64940, -64953, -64967, -64980, -64993,
	-65006, -65018, -65031, -65043, -65055, -65067, -65079, -65091, -65103, -65114, -65126, -65137,
	-65148, -65159, -65169, -65180, -65190, -65200, -65210, -65220, -65230, -65240, -65249, -65259,
	-65268, -65277, -65286, -65294, -65303, -65311, -65320, -65328, -65336, -65343, -65351, -65358,
	-65366, -65373, -65380, -65387, -65393, -65400, -65406, -65413, -65419, -65425, -65430, -65436,
	-65442, -65447, -65452, -65457, -65462, -65467, -65471, -65476, -65480, -65484, -65488, -65492,
	-65495, -65499, -65502, -65505, -65508, -65511, -65514, -65516, -65519, -65521, -65523, -65525,
	-65527, -65528, -65530, -65531, -65532, -65533, -65534, -65535, -65535, -65536, -65536, -65536,
	-65536, -65536, -65535, -65535, -65534, -65533, -65532, -65531, -65530, -65528, -65527, -65525,
	-65523, -65521, -65519, -65516, -65514, -65511, -65508, -65505, -65502, -65499, -65495, -65492,
	-65488, -65484, -65480, -65476, -65471, -65467, -65462, -65457, -65452, -65447, -65442, -65436,
	-65430, -65425, -65419, -65413, -65406, -65400, -65393, -65387, -65380, -65373, -65366, -65358,
	-65351, -65343, -65336, -65328, -65320, -65311, -65303, -65294, -65286, -65277, -65268, -65259,
	-65249, -65240, -65230, -65220, -65210, -65200, -65190, -65180, -65169, -65159, -65148, -65137,
	-65126, -65114, -65103, -65091, -65079, -65067, -65055, -65043, -65031, -65018, -65006, -64993,
	-64980, -64967, -64953, -64940, -64926, -64912, -64899, -64884, -64870, -64856, -64841, -64827,
	-64812, -64797, -64782, -64766, -64751, -64735, -64720, -64704, -64688, -64672, -64655, -64639,
	-64622, -64605, -64588, -64571, -64554, -64536, -64519, -64501, -64483, -64465, -64447, -64429,
	-64410, -64392, -64373, -64354, -64335, -64316, -64296, -64277, -64257, -64237, -64217, -64197,
	-64177, -64156, -64136, -64115, -64094, -64073, -64052, -64031, -64009, -63987, -63966, -63944,
	-63922, -63899, -63877, -63854, -63832, -63809, -63786, -63763, -63739, -63716, -63692, -63668,
	-63645, -63621, -63596, -63572, -63547, -63523, -63498, -63473, -63448, -63423, -63397, -63372,
	-63346, -63320, -63294, -63268, -63242, -63215, -63189, -63162, -63135, -63108, -63081, -63054,
	-63026, -62998, -62971, -62943, -62915, -62886, -62858, -62830, -62801, -62772, -62743, -62714,
	-62685, -62655, -62626, -62596, -62566, -62536, -62506, -62476, -62445, -62415, -62384, -62353,
	-62322, -62291, -62260, -62228, -62197, -62165, -62133, -62101, -62069, -62036, -62004, -61971,
	-61939, -61906, -61873, -61839, -61806, -61772, -61739, -61705, -61671, -61637, -61603, -61568,
	-61534, -61499, -61464, -61429, -61394, -61359, -61324, -61288, -61253, -61217, -61181, -61145,
	-61108, -61072, -61035, -60999, -60962, -60925, -60888, -60851, -60813, -60776, -60738, -60700,
	-60662, -60624, -60586, -60547, -60509, -60470, -60431, -60392, -60353, -60314, -60275, -60235,
	-60195, -60156, -60116, -60075, -60035, -59995, -59954, -59914, -59873, -59832, -59791, -59750,
	-59708, -59667, -59625, -59583, -59541, -59499, -59457, -59415, -59372, -59330, -59287, -59244,
	-59201, -59158, -59114, -59071, -59027, -58983, -58940, -58896, -58851, -58807, -58763, -58718,
	-58673, -58628, -58583, -58538, -58493, -58448, -58402, -58356, -58311, -58265, -58219, -58172,
	-58126, -58079, -58033, -57986, -57939, -57892, -57845, -57798, -57750, -57703, -57655, -57607,
	-57559, -57511, -57463, -57414, -57366, -57317, -57268, -57219, -57170, -57121, -57072, -57022,
	-56972, -56923, -56873, -56823, -56773, -56722, -56672, -56621, -56571, -56520, -56469, -56418,
	-56367, -56315, -56264, -56212, -56160, -56108, -56056, -56004, -55952, -55900, -55847, -55794,
	-55742, -55689, -55636, -55582, -55529, -55476, -55422, -55368, -55314, -55260, -55206, -55152,
	-55098, -55043, -54989, -54934, -54879, -54824, -54769, -54714, -54658, -54603, -54547, -54491,
	-54435, -54379, -54323, -54267, -54210, -54154, -54097, -54040, -53983, -53926, -53869, -53812,
	-53754, -53697, -53639, -53581, -53523, -53465, -53407, -53349, -53290, -53232, -53173, -53114,
	-53055, -52996, -52937, -52878, -52818, -52759, -52699, -52639, -52579, -52519, -52459, -52398,
	-52338, -52277, -52217, -52156, -52095, -52034, -51973, -51911, -51850, -51789, -51727, -51665,
	-51603, -51541, -51479, -51417, -51354, -51292, -51229, -51166, -51104, -51041, -50977, -50914,
	-50851, -50787, -50724, -50660, -50596, -50532, -50468, -50404, -50340, -50275, -50211, -50146,
	-50081, -50016, -49951, -49886, -49821, -49756, -49690, -49624, -49559, -49493, -49427, -49361,
	-49295, -49228, -49162, -49095, -49029, -48962, -48895, -48828, -48761, -48694, -48626, -48559,
	-48491, -48424, -48356, -48288, -48220, -48152, -48084, -48015, -47947, -47878, -47809, -47741,
	-47672, -47603, -47534, -47464, -47395, -47325, -47256, -47186, -47116, -47046, -46976, -46906,
	-46836, -46765, -46695, -46624, -46554, -46483, -46412, -46341, -46270, -46199, -46127, -46056,
	-45984, -45912, -45841, -45769, -45697, -45625, -45552, -45480, -45408, -45335, -45262, -45190,
	-45117, -45044, -44971, -44898, -44824, -44751, -44677, -44604, -44530, -44456, -44382, -44308,
	-44234, -44160, -44086, -44011, -43937, -43862, -43787, -43713, -43638, -43562, -43487, -43412,
	-43337, -43261, -43186, -43110, -43034, -42958, -42882, -42806, -42730, -42654, -42578, -42501,
	-42424, -42348, -42271, -42194, -42117, -42040, -41963, -41886, -41808, -41731, -41653, -41576,
	-41498, -41420, -41342, -41264, -41186, -41108, -41029, -40951, -40872, -40794, -40715, -40636,
	-40557, -40478, -40399, -40320, -40241, -40161, -40082, -40002, -39922, -39843, -39763, -39683,
	-39603, -39523, -39442, -39362, -39282, -39201, -39120, -39040, -38959, -38878, -38797, -38716,
	-38635, -38554, -38472, -38391, -38309, -38228, -38146, -38064, -37982, -37900, -37818, -37736,
	-37654, -37572, -37489, -37407, -37324, -37241, -37159, -37076, -36993, -36910, -36827, -36743,
	-36660, -36577, -36493, -36410, -36326, -36243, -36159, -36075, -35991, -35907, -35823, -35738,
	-35654, -35570, -35485, -35401, -35316, -35231, -35146, -35062, -34977, -34892, -34806, -34721,
	-34636, -34551, -34465, -34380, -34294, -34208, -34122, -34037, -33951, -33865, -33778, -33692,
	-33606, -33520, -33433, -33347, -33260, -33173, -33087, -33000, -32913, -32826, -32739, -32652,
	-32565, -32477, -32390, -32303, -32215, -32127, -32040, -31952, -31864, -31776, -31688, -31600,
	-31512, -31424, -31336, -31248, -31159, -31071, -30982, -30893, -30805, -30716, -30627, -30538,
	-30449, -30360, -30271, -30182, -30093, -30003, -29914, -29824, -29735, -29645, -29555, -29466,
	-29376, -29286, -29196, -29106, -29016, -28926, -28835, -28745, -28655, -28564, -28474, -28383,
	-28293, -28202, -28111, -28020, -27929, -27838, -27747, -27656, -27565, -27474, -27382, -27291,
	-27200, -27108, -27017, -26925, -26833, -26742, -26650, -26558, -26466, -26374, -26282, -26190,
	-26098, -26005, -25913, -25821, -25728, -25636, -25543, -25451, -25358, -25265, -25172, -25080,
	-24987, -24894, -24801, -24708, -24614, -24521, -24428, -24335, -24241, -24148, -24054, -23961,
	-23867, -23774, -23680, -23586, -23492, -23398, -23304, -23210, -23116, -23022, -22928, -22834,
	-22740, -22645, -22551, -22457, -22362, -22268, -22173, -22078, -21984, -21889, -21794, -21699,
	-21604, -21510, -21415, -21320, -21224, -21129, -21034, -20939, -20844, -20748, -20653, -20557,
	-20462, -20366, -20271, -20175, -20080, -19984, -19888, -19792, -19696, -19600, -19505, -19409,
	-19312, -19216, -19120, -19024, -18928, -18832, -18735, -18639, -18543, -18446, -18350, -18253,
	-18156, -18060, -17963, -17866, -17770, -17673, -17576, -17479, -17382, -17285, -17188, -17091,
	-16994, -16897, -16800, -16703, -16606, -16508, -16411, -16314, -16216, -16119, -16021, -15924,
	-15826, -15729, -15631, -15534, -15436, -15338, -15240, -15143, -15045, -14947, -14849, -14751,
	-14653, -14555, -14457, -14359, -14261, -14163, -14065, -13966, -13868, -13770, -13672, -13573,
	-13475, -13376, -13278, -13180, -13081, -12983, -12884, -12785, -12687, -12588, -12490, -12391,
	-12292, -12193, -12095, -11996, -11897, -11798, -11699, -11600, -11501, -11402, -11303, -11204,
	-11105, -11006, -10907, -10808, -10709, -10609, -10510, -10411, -10312, -10212, -10113, -10014,
	-9914, -9815, -9716, -9616, -9517, -9417, -9318, -9218, -9119, -9019, -8919, -8820, -8720,
	-8621, -8521, -8421, -8322, -8222, -8122, -8022, -7923, -7823, -7723, -7623, -7523, -7423,
	-7323, -7224, -7124, -7024, -6924, -6824, -6724, -6624, -6524, -6424, -6324, -6224, -6123,
	-6023, -5923, -5823, -5723, -5623, -5523, -5422, -5322, -5222, -5122, -5022, -4921, -4821,
	-4721, -4621, -4520, -4420, -4320, -4219, -4119, -4019, -3918, -3818, -3718, -3617, -3517,
	-3417, -3316, -3216, -3115, -3015, -2914, -2814, -2714, -2613, -2513, -2412, -2312, -2211,
	-2111, -2010, -1910, -1809, -1709, -1608, -1508, -1407, -1307, -1206, -1106, -1005, -905, -804,
	-704, -603, -503, -402, -302, -201, -101
};

const xint xint_tan__lut[XANG180] = {
	0, 101, 201, 302, 402, 503, 603, 704, 804, 905, 1005, 1106, 1207, 1307, 1408, 1508, 1609, 1709,
	1810, 1911, 2011, 2112, 2213, 2313, 2414, 2515, 2615, 2716, 2817, 2917, 3018, 3119, 3220, 3320,
	3421, 3522, 3623, 3724, 3825, 3925, 4026, 4127, 4228, 4329, 4430, 4531, 4632, 4733, 4834, 4935,
	5036, 5138, 5239, 5340, 5441, 5542, 5644, 5745, 5846, 5948, 6049, 6150, 6252, 6353, 6455, 6556,
	6658, 6759, 6861, 6963, 7064, 7166, 7268, 7370, 7471, 7573, 7675, 7777, 7879, 7981, 8083, 8185,
	8287, 8389, 8492, 8594, 8696, 8798, 8901, 9003, 9106, 9208, 9311, 9413, 9516, 9619, 9721, 9824,
	9927, 10030, 10133, 10236, 10339, 10442, 10545, 10648, 10751, 10854, 10958, 11061, 11165, 11268,
	11372, 11475, 11579, 11682, 11786, 11890, 11994, 12098, 12202, 12306, 12410, 12514, 12618,
	12723, 12827, 12931, 13036, 13140, 13245, 13350, 13454, 13559, 13664, 13769, 13874, 13979,
	14084, 14189, 14295, 14400, 14506, 14611, 14717, 14822, 14928, 15034, 15140, 15246, 15352,
	15458, 15564, 15670, 15776, 15883, 15989, 16096, 16202, 16309, 16416, 16523, 16630, 16737,
	16844, 16951, 17058, 17166, 17273, 17381, 17489, 17596, 17704, 17812, 17920, 18028, 18136,
	18245, 18353, 18461, 18570, 18679, 18787, 18896, 19005, 19114, 19223, 19332, 19442, 19551,
	19661, 19770, 19880, 19990, 20100, 20210, 20320, 20430, 20541, 20651, 20762, 20872, 20983,
	21094, 21205, 21316, 21427, 21539, 21650, 21762, 21873, 21985, 22097, 22209, 22321, 22433,
	22546, 22658, 22771, 22884, 22997, 23110, 23223, 23336, 23449, 23563, 23676, 23790, 23904,
	24018, 24132, 24246, 24360, 24475, 24590, 24704, 24819, 24934, 25049, 25165, 25280, 25396,
	25511, 25627, 25743, 25859, 25975, 26092, 26208, 26325, 26442, 26559, 26676, 26793, 26911,
	27028, 27146, 27264, 27382, 27500, 27618, 27737, 27855, 27974, 28093, 28212, 28331, 28451,
	28570, 28690, 28810, 28930, 29050, 29170, 29291, 29412, 29533, 29654, 29775, 29896, 30018,
	30139, 30261, 30383, 30506, 30628, 30751, 30873, 30996, 31119, 31243, 31366, 31490, 31614,
	31738, 31862, 31986, 32111, 32236, 32360, 32486, 32611, 32736, 32862, 32988, 33114, 33240,
	33367, 33494, 33621, 33748, 33875, 34002, 34130, 34258, 34386, 34514, 34643, 34772, 34901,
	35030, 35159, 35289, 35418, 35548, 35679, 35809, 35940, 36071, 36202, 36333, 36465, 36596,
	36728, 36861, 36993, 37126, 37259, 37392, 37525, 37659, 37793, 37927, 38061, 38196, 38330,
	38465, 38601, 38736, 38872, 39008, 39144, 39281, 39418, 39555, 39692, 39829, 39967, 40105,
	40244, 40382, 40521, 40660, 40799, 40939, 41079, 41219, 41360, 41500, 41641, 41782, 41924,
	42066, 42208, 42350, 42493, 42636, 42779, 42923, 43066, 43210, 43355, 43500, 43644, 43790,
	43935, 44081, 44227, 44374, 44521, 44668, 44815, 44963, 45111, 45259, 45408, 45557, 45706,
	45856, 46005, 46156, 46306, 46457, 46608, 46760, 46912, 47064, 47216, 47369, 47523, 47676,
	47830, 47984, 48139, 48294, 48449, 48605, 48761, 48917, 49074, 49231, 49388, 49546, 49704,
	49863, 50022, 50181, 50341, 50501, 50661, 50822, 50983, 51145, 51307, 51469, 51632, 51795,
	51958, 52122, 52287, 52451, 52617, 52782, 52948, 53114, 53281, 53448, 53616, 53784, 53952,
	54121, 54291, 54460, 54631, 54801, 54972, 55144, 55316, 55488, 55661, 55834, 56008, 56182,
	56357, 56532, 56707, 56883, 57060, 57237, 57414, 57592, 57771, 57950, 58129, 58309, 58489,
	58670, 58851, 59033, 59216, 59398, 59582, 59766, 59950, 60135, 60320, 60506, 60693, 60880,
	61067, 61255, 61444, 61633, 61823, 62013, 62204, 62395, 62587, 62780, 62973, 63167, 63361,
	63556, 63751, 63947, 64143, 64341, 64538, 64737, 64936, 65135, 65335, 65536, 65737, 65939,
	66142, 66345, 66549, 66754, 66959, 67165, 67371, 67578, 67786, 67994, 68203, 68413, 68624,
	68835, 69046, 69259, 69472, 69686, 69900, 70116, 70332, 70548, 70766, 70984, 71203, 71422,
	71642, 71864, 72085, 72308, 72531, 72755, 72980, 73206, 73432, 73659, 73887, 74116, 74345,
	74576, 74807, 75039, 75271, 75505, 75739, 75974, 76210, 76447, 76685, 76924, 77163, 77404,
	77645, 77887, 78130, 78374, 78618, 78864, 79111, 79358, 79607, 79856, 80106, 80357, 80609,
	80863, 81117, 81372, 81628, 81885, 82143, 82402, 82662, 82923, 83185, 83448, 83712, 83977,
	84243, 84510, 84778, 85047, 85318, 85589, 85862, 86135, 86410, 86686, 86963, 87241, 87520,
	87801, 88082, 88365, 88649, 88934, 89220, 89508, 89796, 90086, 90377, 90670, 90963, 91258,
	91554, 91852, 92150, 92450, 92751, 93054, 93358, 93663, 93970, 94278, 94587, 94897, 95209,
	95523, 95838, 96154, 96471, 96791, 97111, 97433, 97757, 98082, 98408, 98736, 99065, 99396,
	99729, 100063, 100399, 100736, 101075, 101415, 101757, 102101, 102447, 102794, 103142, 103493,
	103845, 104199, 104554, 104911, 105270, 105631, 105994, 106358, 106724, 107092, 107462, 107834,
	108208, 108583, 108961, 109340, 109722, 110105, 110490, 110877, 111267, 111658, 112051, 112447,
	112844, 113244, 113646, 114050, 114456, 114864, 115275, 115687, 116102, 116519, 116939, 117361,
	117785, 118211, 118640, 119071, 119505, 119941, 120379, 120820, 121264, 121710, 122158, 122609,
	123063, 123519, 123978, 124440, 124904, 125371, 125841, 126314, 126789, 127267, 127748, 128232,
	128719, 129209, 129702, 130198, 130697, 131198, 131703, 132211, 132723, 133237, 133755, 134276,
	134800, 135328, 135858, 136393, 136930, 137471, 138016, 138564, 139116, 139671, 140230, 140793,
	141359, 141929, 142503, 143081, 143663, 144248, 144838, 145432, 146029, 146631, 147237, 147847,
	148461, 149080, 149703, 150330, 150962, 151598, 152239, 152884, 153534, 154189, 154848, 155512,
	156181, 156855, 157534, 158218, 158907, 159601, 160300, 161005, 161715, 162430, 163151, 163878,
	164610, 165347, 166091, 166840, 167595, 168356, 169123, 169896, 170675, 171461, 172252, 173051,
	173855, 174667, 175485, 176309, 177141, 177979, 178825, 179677, 180537, 181404, 182279, 183161,
	184050, 184948, 185853, 186766, 187687, 188616, 189553, 190499, 191453, 192416, 193388, 194368,
	195357, 196356, 197363, 198380, 199407, 200443, 201489, 202544, 203610, 204686, 205773, 206870,
	207977, 209096, 210225, 211366, 212518, 213681, 214856, 216043, 217242, 218454, 219678, 220914,
	222163, 223426, 224701, 225990, 227293, 228610, 229941, 231286, 232646, 234021, 235411, 236817,
	238238, 239675, 241128, 242598, 244084, 245588, 247109, 248648, 250205, 251780, 253373, 254986,
	256618, 258270, 259942, 261634, 263348, 265082, 266838, 268617, 270417, 272241, 274088, 275959,
	277854, 279774, 281720, 283691, 285689, 287713, 289765, 291845, 293954, 296091, 298259, 300457,
	302686, 304947, 307241, 309568, 311929, 314324, 316755, 319222, 321727, 324269, 326851, 329472,
	332134, 334837, 337584, 340374, 343208, 346089, 349017, 351993, 355019, 358095, 361223, 364405,
	367641, 370934, 374284, 377693, 381164, 384696, 388293, 391956, 395687, 399487, 403360, 407306,
	411328, 415428, 419609, 423872, 428221, 432659, 437187, 441808, 446526, 451344, 456265, 461292,
	466428, 471678, 477046, 482534, 488148, 493892, 499770, 505787, 511949, 518260, 524725, 531352,
	538146, 545113, 552260, 559594, 567123, 574854, 582796, 590958, 599349, 607979, 616857, 625996,
	635407, 645102, 655095, 665398, 676028, 686999, 698329, 710036, 722138, 734656, 747613, 761031,
	774935, 789354, 804315, 819850, 835993, 852781, 870253, 888451, 907422, 927216, 947889, 969500,
	992114, 1015804, 1040646, 1066730, 1094150, 1123011, 1153431, 1185539, 1219479, 1255415,
	1293526, 1334017, 1377118, 1423090, 1472230, 1524878, 1581424, 1642317, 1708078, 1779316,
	1856747, 1941213, 2033721, 2135477, 2247940, 2372895, 2512547, 2669651, 2847698, 3051176,
	3285934, 3559832, 3883524, 4271948, 4746681, 5340090, 6103035, 7120284, 8544423, 10680619,
	14240938, 21361592, 42723892, -2147483648, -42721456, -21360982, -14240667, -10680467, -8544325,
	-7120217, -6102985, -5340052, -4746651, -4271924, -3883504, -3559815, -3285919, -3051164,
	-2847687, -2669641, -2512538, -2372887, -2247933, -2135471, -2033716, -1941208, -1856742,
	-1779312, -1708074, -1642313, -1581421, -1524875, -1472227, -1423087, -1377115, -1334014,
	-1293523, -1255413, -1219478, -1185537, -1153429, -1123010, -1094148, -1066728, -1040644,
	-1015803, -992113, -969499, -947888, -927215, -907421, -888450, -870252, -852780, -835993,
	-819849, -804314, -789353, -774934, -761030, -747612, -734655, -722137, -710035, -698328,
	-686998, -676027, -665398, -655094, -645102, -635407, -625996, -616857, -607979, -599349,
	-590958, -582796, -574854, -567122, -559593, -552259, -545112, -538145, -531352, -524725,
	-518259, -511948, -505787, -499770, -493892, -488148, -482534, -477045, -471678, -466428,
	-461291, -456264, -451344, -446526, -441808, -437186, -432658, -428221, -423872, -419608,
	-415428, -411327, -407305, -403359, -399487, -395687, -391956, -388293, -384696, -381163,
	-377693, -374284, -370934, -367641, -364405, -361223, -358095, -355019, -351993, -349017,
	-346089, -343208, -340373, -337584, -334837, -332134, -329472, -326851, -324269, -321727,
	-319222, -316755, -314324, -311928, -309568, -307241, -304947, -302686, -300457, -298259,
	-296091, -293954, -291845, -289765, -287713, -285689, -283691, -281720, -279774, -277854,
	-275959, -274088, -272241, -270417, -268617, -266838, -265082, -263348, -261634, -259942,
	-258270, -256618, -254986, -253373, -251779, -250204, -248648, -247109, -245588, -244084,
	-242598, -241128, -239675, -238238, -236817, -235411, -234021, -232646, -231286, -229941,
	-228610, -227293, -225990, -224701, -223426, -222163, -220914, -219677, -218454, -217242,
	-216043, -214856, -213681, -212518, -211366, -210225, -209096, -207977, -206870, -205773,
	-204686, -203610, -202544, -201489, -200443, -199407, -198380, -197363, -196356, -195357,
	-194368, -193388, -192416, -191453, -190499, -189553, -188616, -187687, -186766, -185853,
	-184948, -184050, -183161, -182279, -181404, -180537, -179677, -178825, -177979, -177141,
	-176309, -175485, -174667, -173855, -173051, -172252, -171460, -170675, -169896, -169123,
	-168356, -167595, -166840, -166090, -165347, -164610, -163878, -163151, -162430, -161715,
	-161005, -160300, -159601, -158907, -158218, -157534, -156855, -156181, -155512, -154848,
	-154188, -153534, -152884, -152239, -151598, -150962, -150330, -149703, -149080, -148461,
	-147847, -147237, -146631, -146029, -145432, -144838, -144248, -143663, -143081, -142503,
	-141929, -141359, -140793, -140230, -139671, -139116, -138564, -138016, -137471, -136930,
	-136393, -135858, -135327, -134800, -134276, -133755, -133237, -132723, -132211, -131703,
	-131198, -130696, -130198, -129702, -129209, -128719, -128232, -127748, -127267, -126789,
	-126314, -125841, -125371, -124904, -124440, -123978, -123519, -123063, -122609, -122158,
	-121710, -121264, -120820, -120379, -119941, -119505, -119071, -118640, -118211, -117785,
	-117360, -116939, -116519, -116102, -115687, -115275, -114864, -114456, -114050, -113646,
	-113244, -112844, -112447, -112051, -111658, -111267, -110877, -110490, -110105, -109722,
	-109340, -108961, -108583, -108208, -107834, -107462, -107092, -106724, -106358, -105994,
	-105631, -105270, -104911, -104554, -104199, -103845, -103493, -103142, -102794, -102447,
	-102101, -101757, -101415, -101075, -100736, -100399, -100063, -99729, -99396, -99065, -98736,
	-98408, -98082, -97757, -97433, -97111, -96791, -96472, -96154, -95838, -95523, -95209, -94897,
	-94587, -94277, -93970, -93663, -93358, -93054, -92751, -92450, -92150, -91852, -91554, -91258,
	-90963, -90670, -90377, -90086, -89796, -89508, -89220, -88934, -88649, -88365, -88082, -87801,
	-87520, -87241, -86963, -86686, -86410, -86135, -85862, -85589, -85318, -85047, -84778, -84510,
	-84243, -83977, -83712, -83447, -83184, -82922, -82662, -82402, -82143, -81885, -81628, -81372,
	-81117, -80863, -80609, -80357, -80106, -79856, -79607, -79358, -79111, -78864, -78618, -78374,
	-78130, -77887, -77645, -77404, -77163, -76924, -76685, -76447, -76210, -75974, -75739, -75505,
	-75271, -75039, -74807, -74575, -74345, -74116, -73887, -73659, -73432, -73206, -72980, -72755,
	-72531, -72308, -72085, -71864, -71642, -71422, -71203, -70984, -70766, -70548, -70332, -70116,
	-69900, -69686, -69472, -69259, -69046, -68835, -68623, -68413, -68203, -67994, -67786, -67578,
	-67371, -67165, -66959, -66754, -66549, -66345, -66142, -65939, -65737, -65536, -65335, -65135,
	-64936, -64737, -64538, -64341, -64143, -63947, -63751, -63556, -63361, -63167, -62973, -62780,
	-62587, -62395, -62204, -62013, -61823, -61633, -61444, -61255, -61067, -60880, -60693, -60506,
	-60320, -60135, -59950, -59766, -59582, -59398, -59215, -59033, -58851, -58670, -58489, -58309,
	-58129, -57949, -57771, -57592, -57414, -57237, -57060, -56883, -56707, -56532, -56357, -56182,
	-56008, -55834, -55661, -55488, -55316, -55144, -54972, -54801, -54631, -54460, -54291, -54121,
	-53952, -53784, -53616, -53448, -53281, -53114, -52948, -52782, -52617, -52451, -52287, -52122,
	-51958, -51795, -51632, -51469, -51307, -51145, -50983, -50822, -50661, -50501, -50341, -50181,
	-50022, -49863, -49704, -49546, -49388, -49231, -49074, -48917, -48761, -48605, -48449, -48294,
	-48139, -47984, -47830, -47676, -47523, -47369, -47216, -47064, -46912, -46760, -46608, -46457,
	-46306, -46156, -46005, -45856, -45706, -45557, -45408, -45259, -45111, -44963, -44815, -44668,
	-44521, -44374, -44227, -44081, -43935, -43790, -43644, -43500, -43355, -43210, -43066, -42923,
	-42779, -42636, -42493, -42350, -42208, -42066, -41924, -41782, -41641, -41500, -41359, -41219,
	-41079, -40939, -40799, -40660, -40521, -40382, -40244, -40105, -39967, -39829, -39692, -39555,
	-39418, -39281, -39144, -39008, -38872, -38736, -38601, -38465, -38330, -38196, -38061, -37927,
	-37793, -37659, -37525, -37392, -37259, -37126, -36993, -36861, -36728, -36596, -36465, -36333,
	-36202, -36071, -35940, -35809, -35679, -35548, -35418, -35289, -35159, -35030, -34901, -34772,
	-34643, -34514, -34386, -34258, -34130, -34002, -33875, -33748, -33621, -33494, -33367, -33240,
	-33114, -32988, -32862, -32736, -32611, -32486, -32360, -32236, -32111, -31986, -31862, -31738,
	-31614, -31490, -31366, -31243, -31119, -30996, -30873, -30751, -30628, -30506, -30383, -30261,
	-30139, -30018, -29896, -29775, -29654, -29533, -29412, -29291, -29170, -29050, -28930, -28810,
	-28690, -28570, -28451, -28331, -28212, -28093, -27974, -27855, -27737, -27618, -27500, -27382,
	-27264, -27146, -27028, -26911, -26793, -26676, -26559, -26442, -26325, -26208, -26092, -25975,
	-25859, -25743, -25627, -25511, -25396, -25280, -25165, -25049, -24934, -24819, -24704, -24590,
	-24475, -24360, -24246, -24132, -24018, -23904, -23790, -23676, -23563, -23449, -23336, -23223,
	-23110, -22997, -22884, -22771, -22658, -22546, -22433, -22321, -22209, -22097, -21985, -21873,
	-21762, -21650, -21539, -21427, -21316, -21205, -21094, -20983, -20872, -20762, -20651, -20541,
	-20430, -20320, -20210, -20100, -19990, -19880, -19770, -19661, -19551, -19442, -19332, -19223,
	-19114, -19005, -18896, -18787, -18679, -18570, -18461, -18353, -18245, -18136, -18028, -17920,
	-17812, -17704, -17596, -17489, -17381, -17273, -17166, -17058, -16951, -16844, -16737, -16630,
	-16523, -16416, -16309, -16202, -16096, -15989, -15883, -15776, -15670, -15564, -15458, -15352,
	-15246, -15140, -15034, -14928, -14822, -14717, -14611, -14506, -14400, -14295, -14189, -14084,
	-13979, -13874, -13769, -13664, -13559, -13454, -13350, -13245, -13140, -13036, -12931, -12827,
	-12723, -12618, -12514, -12410, -12306, -12202, -12098, -11994, -11890, -11786, -11682, -11579,
	-11475, -11372, -11268, -11165, -11061, -10958, -10854, -10751, -10648, -10545, -10442, -10339,
	-10236, -10133, -10030, -9927, -9824, -9721, -9619, -9516, -9413, -9311, -9208, -9106, -9003,
	-8901, -8798, -8696, -8594, -8492, -8389, -8287, -8185, -8083, -7981, -7879, -7777, -7675,
	-7573, -7471, -7370, -7268, -7166, -7064, -6963, -6861, -6759, -6658, -6556, -6455, -6353,
	-6252, -6150, -6049, -5948, -5846, -5745, -5644, -5542, -5441, -5340, -5239, -5138, -5036,
	-4935, -4834, -4733, -4632, -4531, -4430, -4329, -4228, -4127, -4026, -3925, -3824, -3724,
	-3623, -3522, -3421, -3320, -3220, -3119, -3018, -2917, -2817, -2716, -2615, -2515, -2414,
	-2313, -2213, -2112, -2011, -1911, -1810, -1709, -1609, -1508, -1408, -1307, -1207, -1106,
	-1005, -905, -804, -704, -603, -503, -402, -302, -201, -101
};

#endif /* NVQM_SKIP_FIXED_POINT */
