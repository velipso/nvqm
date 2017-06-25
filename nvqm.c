// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

#include "nvqm.h"

#ifndef NVQM_SKIP_FLOATING_POINT

//
// mat3
//

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

//
// mat4
//

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

mat4 *mat4_perspective(mat4 *out, float fov, float width, float height, float N, float F){
	float
		f  = 1.0f / num_tan(fov * 0.5f),
		nf = 1.0f / (N - F);
	out->v[ 0] = f;
	out->v[ 1] =  0.0f;
	out->v[ 2] =  0.0f;
	out->v[ 3] =  0.0f;
	out->v[ 4] =  0.0f;
	out->v[ 5] = f * width / height;
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
	out->v[12] = 0.0f; out->v[13] = 0.0f; out->v[14] = 0.0f; out->v[15] = 1.0f;
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

#endif // NVQM_SKIP_FLOATING_POINT

#ifndef NVQM_SKIP_FIXED_POINT

xang xint_atan2(xint y, xint x){
	// from all my testing, the max error is 8 units, i.e., TAU * 8 / 4096 radians
	// UNLESS one of the operations overflows... then the error is essentially random
	// so be careful with high values
	static const xint c1 = 0x0200, c2 = 0x0600, c3 = 0x0080, c4 = 0x0280;
	if (y == 0 && x == 0)
		return 0;
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
		return angle == 0 ? angle : XANG360 - angle;
	return angle;
}

static inline int64_t x_mul31(int64_t res, int64_t f){
	// res is Q33.31 and f is Q0.32
	return (int64_t)(((uint64_t)res * (uint64_t)f) >> 32);
}

static inline int64_t x_exp2f(int64_t f){
	// res is Q33.31 and f is Q0.32
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
	// a is Q32.32
	// 2^(whole+fraction) = 2^whole * 2^fraction
	int32_t whole = a >> 32;
	int64_t fract = x_exp2f(a & INT64_C(0xFFFFFFFF));
	if (whole < 15)
		return (xint)(fract >> (15 - whole));
	return (xint)(fract << (whole - 15));
}

xint xint_exp(xint a){
	// testing shows this is within +-5177/65536, with a higher error the larger `a` is
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
	static const int64_t log2e = INT64_C(0x171547653); // log2(e) at Q32.32
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
// TODO: actually test this
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

static inline xint x_log2f(xint f){ // f ranges from (1, 2]
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
	// testing shows this is within +-44/65536
	if (a <= 0)
		return XINTMIN;
	else if (a == 1) // must hard code these because it's too small to calculate
		return INT32_C(0xFFF4E8DF);
	else if (a == 2)
		return INT32_C(0xFFF59A51);
	int small = 0;
	if (a < XINT1){
		small = 1;
		a = xint_div(XINT1, a);
	}
	static const xint log2einv = 0xB172; // 1/(log2 e)
	xint res = xint_mul(x_log2(a), log2einv);
	if (small)
		res = -res;
	return res;
}

xint xint_pow(xint a, xint b){
	// TODO
	return 0;
}

xint xint_sqrt(xint a){
	// TODO
	return 0;
}

// sorry for the mess, but this is the lookup table for sine
#define X(a) INT32_C(a)
const xint xint_sin__lut[XANG360] = {
	X(0x00000000), X(0x00000065), X(0x000000C9), X(0x0000012E), X(0x00000192), X(0x000001F7),
	X(0x0000025B), X(0x000002C0), X(0x00000324), X(0x00000389), X(0x000003ED), X(0x00000452),
	X(0x000004B6), X(0x0000051B), X(0x0000057F), X(0x000005E4), X(0x00000648), X(0x000006AD),
	X(0x00000711), X(0x00000776), X(0x000007DA), X(0x0000083F), X(0x000008A3), X(0x00000908),
	X(0x0000096C), X(0x000009D1), X(0x00000A35), X(0x00000A9A), X(0x00000AFE), X(0x00000B62),
	X(0x00000BC7), X(0x00000C2B), X(0x00000C90), X(0x00000CF4), X(0x00000D59), X(0x00000DBD),
	X(0x00000E21), X(0x00000E86), X(0x00000EEA), X(0x00000F4E), X(0x00000FB3), X(0x00001017),
	X(0x0000107B), X(0x000010E0), X(0x00001144), X(0x000011A8), X(0x0000120D), X(0x00001271),
	X(0x000012D5), X(0x00001339), X(0x0000139E), X(0x00001402), X(0x00001466), X(0x000014CA),
	X(0x0000152E), X(0x00001593), X(0x000015F7), X(0x0000165B), X(0x000016BF), X(0x00001723),
	X(0x00001787), X(0x000017EB), X(0x00001850), X(0x000018B4), X(0x00001918), X(0x0000197C),
	X(0x000019E0), X(0x00001A44), X(0x00001AA8), X(0x00001B0C), X(0x00001B70), X(0x00001BD4),
	X(0x00001C38), X(0x00001C9B), X(0x00001CFF), X(0x00001D63), X(0x00001DC7), X(0x00001E2B),
	X(0x00001E8F), X(0x00001EF3), X(0x00001F56), X(0x00001FBA), X(0x0000201E), X(0x00002082),
	X(0x000020E5), X(0x00002149), X(0x000021AD), X(0x00002210), X(0x00002274), X(0x000022D7),
	X(0x0000233B), X(0x0000239F), X(0x00002402), X(0x00002466), X(0x000024C9), X(0x0000252D),
	X(0x00002590), X(0x000025F4), X(0x00002657), X(0x000026BA), X(0x0000271E), X(0x00002781),
	X(0x000027E4), X(0x00002848), X(0x000028AB), X(0x0000290E), X(0x00002971), X(0x000029D5),
	X(0x00002A38), X(0x00002A9B), X(0x00002AFE), X(0x00002B61), X(0x00002BC4), X(0x00002C27),
	X(0x00002C8A), X(0x00002CED), X(0x00002D50), X(0x00002DB3), X(0x00002E16), X(0x00002E79),
	X(0x00002EDC), X(0x00002F3F), X(0x00002FA1), X(0x00003004), X(0x00003067), X(0x000030CA),
	X(0x0000312C), X(0x0000318F), X(0x000031F1), X(0x00003254), X(0x000032B7), X(0x00003319),
	X(0x0000337C), X(0x000033DE), X(0x00003440), X(0x000034A3), X(0x00003505), X(0x00003568),
	X(0x000035CA), X(0x0000362C), X(0x0000368E), X(0x000036F1), X(0x00003753), X(0x000037B5),
	X(0x00003817), X(0x00003879), X(0x000038DB), X(0x0000393D), X(0x0000399F), X(0x00003A01),
	X(0x00003A63), X(0x00003AC5), X(0x00003B27), X(0x00003B88), X(0x00003BEA), X(0x00003C4C),
	X(0x00003CAE), X(0x00003D0F), X(0x00003D71), X(0x00003DD2), X(0x00003E34), X(0x00003E95),
	X(0x00003EF7), X(0x00003F58), X(0x00003FBA), X(0x0000401B), X(0x0000407C), X(0x000040DE),
	X(0x0000413F), X(0x000041A0), X(0x00004201), X(0x00004262), X(0x000042C3), X(0x00004324),
	X(0x00004385), X(0x000043E6), X(0x00004447), X(0x000044A8), X(0x00004509), X(0x0000456A),
	X(0x000045CB), X(0x0000462B), X(0x0000468C), X(0x000046EC), X(0x0000474D), X(0x000047AE),
	X(0x0000480E), X(0x0000486F), X(0x000048CF), X(0x0000492F), X(0x00004990), X(0x000049F0),
	X(0x00004A50), X(0x00004AB0), X(0x00004B10), X(0x00004B71), X(0x00004BD1), X(0x00004C31),
	X(0x00004C90), X(0x00004CF0), X(0x00004D50), X(0x00004DB0), X(0x00004E10), X(0x00004E70),
	X(0x00004ECF), X(0x00004F2F), X(0x00004F8E), X(0x00004FEE), X(0x0000504D), X(0x000050AD),
	X(0x0000510C), X(0x0000516C), X(0x000051CB), X(0x0000522A), X(0x00005289), X(0x000052E8),
	X(0x00005348), X(0x000053A7), X(0x00005406), X(0x00005464), X(0x000054C3), X(0x00005522),
	X(0x00005581), X(0x000055E0), X(0x0000563E), X(0x0000569D), X(0x000056FC), X(0x0000575A),
	X(0x000057B9), X(0x00005817), X(0x00005875), X(0x000058D4), X(0x00005932), X(0x00005990),
	X(0x000059EE), X(0x00005A4C), X(0x00005AAA), X(0x00005B08), X(0x00005B66), X(0x00005BC4),
	X(0x00005C22), X(0x00005C80), X(0x00005CDE), X(0x00005D3B), X(0x00005D99), X(0x00005DF6),
	X(0x00005E54), X(0x00005EB1), X(0x00005F0F), X(0x00005F6C), X(0x00005FC9), X(0x00006026),
	X(0x00006084), X(0x000060E1), X(0x0000613E), X(0x0000619B), X(0x000061F8), X(0x00006254),
	X(0x000062B1), X(0x0000630E), X(0x0000636B), X(0x000063C7), X(0x00006424), X(0x00006480),
	X(0x000064DD), X(0x00006539), X(0x00006595), X(0x000065F2), X(0x0000664E), X(0x000066AA),
	X(0x00006706), X(0x00006762), X(0x000067BE), X(0x0000681A), X(0x00006876), X(0x000068D1),
	X(0x0000692D), X(0x00006989), X(0x000069E4), X(0x00006A40), X(0x00006A9B), X(0x00006AF6),
	X(0x00006B52), X(0x00006BAD), X(0x00006C08), X(0x00006C63), X(0x00006CBE), X(0x00006D19),
	X(0x00006D74), X(0x00006DCF), X(0x00006E2A), X(0x00006E85), X(0x00006EDF), X(0x00006F3A),
	X(0x00006F94), X(0x00006FEF), X(0x00007049), X(0x000070A3), X(0x000070FE), X(0x00007158),
	X(0x000071B2), X(0x0000720C), X(0x00007266), X(0x000072C0), X(0x0000731A), X(0x00007373),
	X(0x000073CD), X(0x00007427), X(0x00007480), X(0x000074DA), X(0x00007533), X(0x0000758D),
	X(0x000075E6), X(0x0000763F), X(0x00007698), X(0x000076F1), X(0x0000774A), X(0x000077A3),
	X(0x000077FC), X(0x00007855), X(0x000078AD), X(0x00007906), X(0x0000795F), X(0x000079B7),
	X(0x00007A10), X(0x00007A68), X(0x00007AC0), X(0x00007B18), X(0x00007B70), X(0x00007BC8),
	X(0x00007C20), X(0x00007C78), X(0x00007CD0), X(0x00007D28), X(0x00007D7F), X(0x00007DD7),
	X(0x00007E2F), X(0x00007E86), X(0x00007EDD), X(0x00007F35), X(0x00007F8C), X(0x00007FE3),
	X(0x0000803A), X(0x00008091), X(0x000080E8), X(0x0000813F), X(0x00008195), X(0x000081EC),
	X(0x00008243), X(0x00008299), X(0x000082F0), X(0x00008346), X(0x0000839C), X(0x000083F2),
	X(0x00008449), X(0x0000849F), X(0x000084F5), X(0x0000854A), X(0x000085A0), X(0x000085F6),
	X(0x0000864C), X(0x000086A1), X(0x000086F7), X(0x0000874C), X(0x000087A1), X(0x000087F6),
	X(0x0000884C), X(0x000088A1), X(0x000088F6), X(0x0000894A), X(0x0000899F), X(0x000089F4),
	X(0x00008A49), X(0x00008A9D), X(0x00008AF2), X(0x00008B46), X(0x00008B9A), X(0x00008BEF),
	X(0x00008C43), X(0x00008C97), X(0x00008CEB), X(0x00008D3F), X(0x00008D93), X(0x00008DE6),
	X(0x00008E3A), X(0x00008E8D), X(0x00008EE1), X(0x00008F34), X(0x00008F88), X(0x00008FDB),
	X(0x0000902E), X(0x00009081), X(0x000090D4), X(0x00009127), X(0x00009179), X(0x000091CC),
	X(0x0000921F), X(0x00009271), X(0x000092C4), X(0x00009316), X(0x00009368), X(0x000093BA),
	X(0x0000940C), X(0x0000945E), X(0x000094B0), X(0x00009502), X(0x00009554), X(0x000095A5),
	X(0x000095F7), X(0x00009648), X(0x0000969A), X(0x000096EB), X(0x0000973C), X(0x0000978D),
	X(0x000097DE), X(0x0000982F), X(0x00009880), X(0x000098D0), X(0x00009921), X(0x00009972),
	X(0x000099C2), X(0x00009A12), X(0x00009A63), X(0x00009AB3), X(0x00009B03), X(0x00009B53),
	X(0x00009BA3), X(0x00009BF2), X(0x00009C42), X(0x00009C92), X(0x00009CE1), X(0x00009D31),
	X(0x00009D80), X(0x00009DCF), X(0x00009E1E), X(0x00009E6D), X(0x00009EBC), X(0x00009F0B),
	X(0x00009F5A), X(0x00009FA8), X(0x00009FF7), X(0x0000A045), X(0x0000A094), X(0x0000A0E2),
	X(0x0000A130), X(0x0000A17E), X(0x0000A1CC), X(0x0000A21A), X(0x0000A268), X(0x0000A2B5),
	X(0x0000A303), X(0x0000A350), X(0x0000A39E), X(0x0000A3EB), X(0x0000A438), X(0x0000A485),
	X(0x0000A4D2), X(0x0000A51F), X(0x0000A56C), X(0x0000A5B8), X(0x0000A605), X(0x0000A652),
	X(0x0000A69E), X(0x0000A6EA), X(0x0000A736), X(0x0000A782), X(0x0000A7CE), X(0x0000A81A),
	X(0x0000A866), X(0x0000A8B2), X(0x0000A8FD), X(0x0000A949), X(0x0000A994), X(0x0000A9DF),
	X(0x0000AA2A), X(0x0000AA76), X(0x0000AAC1), X(0x0000AB0B), X(0x0000AB56), X(0x0000ABA1),
	X(0x0000ABEB), X(0x0000AC36), X(0x0000AC80), X(0x0000ACCA), X(0x0000AD14), X(0x0000AD5E),
	X(0x0000ADA8), X(0x0000ADF2), X(0x0000AE3C), X(0x0000AE85), X(0x0000AECF), X(0x0000AF18),
	X(0x0000AF62), X(0x0000AFAB), X(0x0000AFF4), X(0x0000B03D), X(0x0000B086), X(0x0000B0CE),
	X(0x0000B117), X(0x0000B160), X(0x0000B1A8), X(0x0000B1F0), X(0x0000B239), X(0x0000B281),
	X(0x0000B2C9), X(0x0000B311), X(0x0000B358), X(0x0000B3A0), X(0x0000B3E8), X(0x0000B42F),
	X(0x0000B477), X(0x0000B4BE), X(0x0000B505), X(0x0000B54C), X(0x0000B593), X(0x0000B5DA),
	X(0x0000B620), X(0x0000B667), X(0x0000B6AD), X(0x0000B6F4), X(0x0000B73A), X(0x0000B780),
	X(0x0000B7C6), X(0x0000B80C), X(0x0000B852), X(0x0000B898), X(0x0000B8DD), X(0x0000B923),
	X(0x0000B968), X(0x0000B9AE), X(0x0000B9F3), X(0x0000BA38), X(0x0000BA7D), X(0x0000BAC1),
	X(0x0000BB06), X(0x0000BB4B), X(0x0000BB8F), X(0x0000BBD4), X(0x0000BC18), X(0x0000BC5C),
	X(0x0000BCA0), X(0x0000BCE4), X(0x0000BD28), X(0x0000BD6B), X(0x0000BDAF), X(0x0000BDF2),
	X(0x0000BE36), X(0x0000BE79), X(0x0000BEBC), X(0x0000BEFF), X(0x0000BF42), X(0x0000BF85),
	X(0x0000BFC7), X(0x0000C00A), X(0x0000C04C), X(0x0000C08F), X(0x0000C0D1), X(0x0000C113),
	X(0x0000C155), X(0x0000C197), X(0x0000C1D8), X(0x0000C21A), X(0x0000C25C), X(0x0000C29D),
	X(0x0000C2DE), X(0x0000C31F), X(0x0000C360), X(0x0000C3A1), X(0x0000C3E2), X(0x0000C423),
	X(0x0000C463), X(0x0000C4A4), X(0x0000C4E4), X(0x0000C524), X(0x0000C564), X(0x0000C5A4),
	X(0x0000C5E4), X(0x0000C624), X(0x0000C663), X(0x0000C6A3), X(0x0000C6E2), X(0x0000C721),
	X(0x0000C761), X(0x0000C7A0), X(0x0000C7DE), X(0x0000C81D), X(0x0000C85C), X(0x0000C89A),
	X(0x0000C8D9), X(0x0000C917), X(0x0000C955), X(0x0000C993), X(0x0000C9D1), X(0x0000CA0F),
	X(0x0000CA4D), X(0x0000CA8A), X(0x0000CAC7), X(0x0000CB05), X(0x0000CB42), X(0x0000CB7F),
	X(0x0000CBBC), X(0x0000CBF9), X(0x0000CC35), X(0x0000CC72), X(0x0000CCAE), X(0x0000CCEB),
	X(0x0000CD27), X(0x0000CD63), X(0x0000CD9F), X(0x0000CDDB), X(0x0000CE17), X(0x0000CE52),
	X(0x0000CE8E), X(0x0000CEC9), X(0x0000CF04), X(0x0000CF3F), X(0x0000CF7A), X(0x0000CFB5),
	X(0x0000CFF0), X(0x0000D02A), X(0x0000D065), X(0x0000D09F), X(0x0000D0D9), X(0x0000D113),
	X(0x0000D14D), X(0x0000D187), X(0x0000D1C1), X(0x0000D1FA), X(0x0000D234), X(0x0000D26D),
	X(0x0000D2A6), X(0x0000D2DF), X(0x0000D318), X(0x0000D351), X(0x0000D38A), X(0x0000D3C2),
	X(0x0000D3FB), X(0x0000D433), X(0x0000D46B), X(0x0000D4A3), X(0x0000D4DB), X(0x0000D513),
	X(0x0000D54B), X(0x0000D582), X(0x0000D5BA), X(0x0000D5F1), X(0x0000D628), X(0x0000D65F),
	X(0x0000D696), X(0x0000D6CD), X(0x0000D703), X(0x0000D73A), X(0x0000D770), X(0x0000D7A6),
	X(0x0000D7DC), X(0x0000D812), X(0x0000D848), X(0x0000D87E), X(0x0000D8B4), X(0x0000D8E9),
	X(0x0000D91E), X(0x0000D954), X(0x0000D989), X(0x0000D9BE), X(0x0000D9F2), X(0x0000DA27),
	X(0x0000DA5C), X(0x0000DA90), X(0x0000DAC4), X(0x0000DAF8), X(0x0000DB2C), X(0x0000DB60),
	X(0x0000DB94), X(0x0000DBC8), X(0x0000DBFB), X(0x0000DC2F), X(0x0000DC62), X(0x0000DC95),
	X(0x0000DCC8), X(0x0000DCFB), X(0x0000DD2D), X(0x0000DD60), X(0x0000DD92), X(0x0000DDC5),
	X(0x0000DDF7), X(0x0000DE29), X(0x0000DE5B), X(0x0000DE8C), X(0x0000DEBE), X(0x0000DEF0),
	X(0x0000DF21), X(0x0000DF52), X(0x0000DF83), X(0x0000DFB4), X(0x0000DFE5), X(0x0000E016),
	X(0x0000E046), X(0x0000E077), X(0x0000E0A7), X(0x0000E0D7), X(0x0000E107), X(0x0000E137),
	X(0x0000E167), X(0x0000E196), X(0x0000E1C6), X(0x0000E1F5), X(0x0000E224), X(0x0000E253),
	X(0x0000E282), X(0x0000E2B1), X(0x0000E2DF), X(0x0000E30E), X(0x0000E33C), X(0x0000E36B),
	X(0x0000E399), X(0x0000E3C7), X(0x0000E3F4), X(0x0000E422), X(0x0000E450), X(0x0000E47D),
	X(0x0000E4AA), X(0x0000E4D7), X(0x0000E504), X(0x0000E531), X(0x0000E55E), X(0x0000E58B),
	X(0x0000E5B7), X(0x0000E5E3), X(0x0000E610), X(0x0000E63C), X(0x0000E667), X(0x0000E693),
	X(0x0000E6BF), X(0x0000E6EA), X(0x0000E716), X(0x0000E741), X(0x0000E76C), X(0x0000E797),
	X(0x0000E7C2), X(0x0000E7EC), X(0x0000E817), X(0x0000E841), X(0x0000E86B), X(0x0000E895),
	X(0x0000E8BF), X(0x0000E8E9), X(0x0000E913), X(0x0000E93C), X(0x0000E966), X(0x0000E98F),
	X(0x0000E9B8), X(0x0000E9E1), X(0x0000EA0A), X(0x0000EA32), X(0x0000EA5B), X(0x0000EA83),
	X(0x0000EAAB), X(0x0000EAD4), X(0x0000EAFC), X(0x0000EB23), X(0x0000EB4B), X(0x0000EB73),
	X(0x0000EB9A), X(0x0000EBC1), X(0x0000EBE8), X(0x0000EC0F), X(0x0000EC36), X(0x0000EC5D),
	X(0x0000EC83), X(0x0000ECAA), X(0x0000ECD0), X(0x0000ECF6), X(0x0000ED1C), X(0x0000ED42),
	X(0x0000ED68), X(0x0000ED8D), X(0x0000EDB3), X(0x0000EDD8), X(0x0000EDFD), X(0x0000EE22),
	X(0x0000EE47), X(0x0000EE6B), X(0x0000EE90), X(0x0000EEB4), X(0x0000EED9), X(0x0000EEFD),
	X(0x0000EF21), X(0x0000EF45), X(0x0000EF68), X(0x0000EF8C), X(0x0000EFAF), X(0x0000EFD2),
	X(0x0000EFF5), X(0x0000F018), X(0x0000F03B), X(0x0000F05E), X(0x0000F080), X(0x0000F0A3),
	X(0x0000F0C5), X(0x0000F0E7), X(0x0000F109), X(0x0000F12B), X(0x0000F14C), X(0x0000F16E),
	X(0x0000F18F), X(0x0000F1B1), X(0x0000F1D2), X(0x0000F1F3), X(0x0000F213), X(0x0000F234),
	X(0x0000F254), X(0x0000F275), X(0x0000F295), X(0x0000F2B5), X(0x0000F2D5), X(0x0000F2F5),
	X(0x0000F314), X(0x0000F334), X(0x0000F353), X(0x0000F372), X(0x0000F391), X(0x0000F3B0),
	X(0x0000F3CF), X(0x0000F3ED), X(0x0000F40C), X(0x0000F42A), X(0x0000F448), X(0x0000F466),
	X(0x0000F484), X(0x0000F4A2), X(0x0000F4BF), X(0x0000F4DD), X(0x0000F4FA), X(0x0000F517),
	X(0x0000F534), X(0x0000F551), X(0x0000F56E), X(0x0000F58A), X(0x0000F5A6), X(0x0000F5C3),
	X(0x0000F5DF), X(0x0000F5FB), X(0x0000F616), X(0x0000F632), X(0x0000F64E), X(0x0000F669),
	X(0x0000F684), X(0x0000F69F), X(0x0000F6BA), X(0x0000F6D5), X(0x0000F6EF), X(0x0000F70A),
	X(0x0000F724), X(0x0000F73E), X(0x0000F758), X(0x0000F772), X(0x0000F78C), X(0x0000F7A5),
	X(0x0000F7BF), X(0x0000F7D8), X(0x0000F7F1), X(0x0000F80A), X(0x0000F823), X(0x0000F83B),
	X(0x0000F854), X(0x0000F86C), X(0x0000F885), X(0x0000F89D), X(0x0000F8B4), X(0x0000F8CC),
	X(0x0000F8E4), X(0x0000F8FB), X(0x0000F913), X(0x0000F92A), X(0x0000F941), X(0x0000F958),
	X(0x0000F96E), X(0x0000F985), X(0x0000F99B), X(0x0000F9B2), X(0x0000F9C8), X(0x0000F9DE),
	X(0x0000F9F3), X(0x0000FA09), X(0x0000FA1F), X(0x0000FA34), X(0x0000FA49), X(0x0000FA5E),
	X(0x0000FA73), X(0x0000FA88), X(0x0000FA9C), X(0x0000FAB1), X(0x0000FAC5), X(0x0000FAD9),
	X(0x0000FAED), X(0x0000FB01), X(0x0000FB15), X(0x0000FB28), X(0x0000FB3C), X(0x0000FB4F),
	X(0x0000FB62), X(0x0000FB75), X(0x0000FB88), X(0x0000FB9A), X(0x0000FBAD), X(0x0000FBBF),
	X(0x0000FBD1), X(0x0000FBE3), X(0x0000FBF5), X(0x0000FC07), X(0x0000FC18), X(0x0000FC2A),
	X(0x0000FC3B), X(0x0000FC4C), X(0x0000FC5D), X(0x0000FC6E), X(0x0000FC7F), X(0x0000FC8F),
	X(0x0000FCA0), X(0x0000FCB0), X(0x0000FCC0), X(0x0000FCD0), X(0x0000FCDF), X(0x0000FCEF),
	X(0x0000FCFE), X(0x0000FD0E), X(0x0000FD1D), X(0x0000FD2C), X(0x0000FD3B), X(0x0000FD49),
	X(0x0000FD58), X(0x0000FD66), X(0x0000FD74), X(0x0000FD83), X(0x0000FD90), X(0x0000FD9E),
	X(0x0000FDAC), X(0x0000FDB9), X(0x0000FDC7), X(0x0000FDD4), X(0x0000FDE1), X(0x0000FDEE),
	X(0x0000FDFA), X(0x0000FE07), X(0x0000FE13), X(0x0000FE1F), X(0x0000FE2B), X(0x0000FE37),
	X(0x0000FE43), X(0x0000FE4F), X(0x0000FE5A), X(0x0000FE66), X(0x0000FE71), X(0x0000FE7C),
	X(0x0000FE87), X(0x0000FE91), X(0x0000FE9C), X(0x0000FEA6), X(0x0000FEB0), X(0x0000FEBA),
	X(0x0000FEC4), X(0x0000FECE), X(0x0000FED8), X(0x0000FEE1), X(0x0000FEEB), X(0x0000FEF4),
	X(0x0000FEFD), X(0x0000FF06), X(0x0000FF0E), X(0x0000FF17), X(0x0000FF1F), X(0x0000FF28),
	X(0x0000FF30), X(0x0000FF38), X(0x0000FF3F), X(0x0000FF47), X(0x0000FF4E), X(0x0000FF56),
	X(0x0000FF5D), X(0x0000FF64), X(0x0000FF6B), X(0x0000FF71), X(0x0000FF78), X(0x0000FF7E),
	X(0x0000FF85), X(0x0000FF8B), X(0x0000FF91), X(0x0000FF96), X(0x0000FF9C), X(0x0000FFA2),
	X(0x0000FFA7), X(0x0000FFAC), X(0x0000FFB1), X(0x0000FFB6), X(0x0000FFBB), X(0x0000FFBF),
	X(0x0000FFC4), X(0x0000FFC8), X(0x0000FFCC), X(0x0000FFD0), X(0x0000FFD4), X(0x0000FFD7),
	X(0x0000FFDB), X(0x0000FFDE), X(0x0000FFE1), X(0x0000FFE4), X(0x0000FFE7), X(0x0000FFEA),
	X(0x0000FFEC), X(0x0000FFEF), X(0x0000FFF1), X(0x0000FFF3), X(0x0000FFF5), X(0x0000FFF7),
	X(0x0000FFF8), X(0x0000FFFA), X(0x0000FFFB), X(0x0000FFFC), X(0x0000FFFD), X(0x0000FFFE),
	X(0x0000FFFF), X(0x0000FFFF), X(0x00010000), X(0x00010000), X(0x00010000), X(0x00010000),
	X(0x00010000), X(0x0000FFFF), X(0x0000FFFF), X(0x0000FFFE), X(0x0000FFFD), X(0x0000FFFC),
	X(0x0000FFFB), X(0x0000FFFA), X(0x0000FFF8), X(0x0000FFF7), X(0x0000FFF5), X(0x0000FFF3),
	X(0x0000FFF1), X(0x0000FFEF), X(0x0000FFEC), X(0x0000FFEA), X(0x0000FFE7), X(0x0000FFE4),
	X(0x0000FFE1), X(0x0000FFDE), X(0x0000FFDB), X(0x0000FFD7), X(0x0000FFD4), X(0x0000FFD0),
	X(0x0000FFCC), X(0x0000FFC8), X(0x0000FFC4), X(0x0000FFBF), X(0x0000FFBB), X(0x0000FFB6),
	X(0x0000FFB1), X(0x0000FFAC), X(0x0000FFA7), X(0x0000FFA2), X(0x0000FF9C), X(0x0000FF96),
	X(0x0000FF91), X(0x0000FF8B), X(0x0000FF85), X(0x0000FF7E), X(0x0000FF78), X(0x0000FF71),
	X(0x0000FF6B), X(0x0000FF64), X(0x0000FF5D), X(0x0000FF56), X(0x0000FF4E), X(0x0000FF47),
	X(0x0000FF3F), X(0x0000FF38), X(0x0000FF30), X(0x0000FF28), X(0x0000FF1F), X(0x0000FF17),
	X(0x0000FF0E), X(0x0000FF06), X(0x0000FEFD), X(0x0000FEF4), X(0x0000FEEB), X(0x0000FEE1),
	X(0x0000FED8), X(0x0000FECE), X(0x0000FEC4), X(0x0000FEBA), X(0x0000FEB0), X(0x0000FEA6),
	X(0x0000FE9C), X(0x0000FE91), X(0x0000FE87), X(0x0000FE7C), X(0x0000FE71), X(0x0000FE66),
	X(0x0000FE5A), X(0x0000FE4F), X(0x0000FE43), X(0x0000FE37), X(0x0000FE2B), X(0x0000FE1F),
	X(0x0000FE13), X(0x0000FE07), X(0x0000FDFA), X(0x0000FDEE), X(0x0000FDE1), X(0x0000FDD4),
	X(0x0000FDC7), X(0x0000FDB9), X(0x0000FDAC), X(0x0000FD9E), X(0x0000FD90), X(0x0000FD83),
	X(0x0000FD74), X(0x0000FD66), X(0x0000FD58), X(0x0000FD49), X(0x0000FD3B), X(0x0000FD2C),
	X(0x0000FD1D), X(0x0000FD0E), X(0x0000FCFE), X(0x0000FCEF), X(0x0000FCDF), X(0x0000FCD0),
	X(0x0000FCC0), X(0x0000FCB0), X(0x0000FCA0), X(0x0000FC8F), X(0x0000FC7F), X(0x0000FC6E),
	X(0x0000FC5D), X(0x0000FC4C), X(0x0000FC3B), X(0x0000FC2A), X(0x0000FC18), X(0x0000FC07),
	X(0x0000FBF5), X(0x0000FBE3), X(0x0000FBD1), X(0x0000FBBF), X(0x0000FBAD), X(0x0000FB9A),
	X(0x0000FB88), X(0x0000FB75), X(0x0000FB62), X(0x0000FB4F), X(0x0000FB3C), X(0x0000FB28),
	X(0x0000FB15), X(0x0000FB01), X(0x0000FAED), X(0x0000FAD9), X(0x0000FAC5), X(0x0000FAB1),
	X(0x0000FA9C), X(0x0000FA88), X(0x0000FA73), X(0x0000FA5E), X(0x0000FA49), X(0x0000FA34),
	X(0x0000FA1F), X(0x0000FA09), X(0x0000F9F3), X(0x0000F9DE), X(0x0000F9C8), X(0x0000F9B2),
	X(0x0000F99B), X(0x0000F985), X(0x0000F96E), X(0x0000F958), X(0x0000F941), X(0x0000F92A),
	X(0x0000F913), X(0x0000F8FB), X(0x0000F8E4), X(0x0000F8CC), X(0x0000F8B4), X(0x0000F89D),
	X(0x0000F885), X(0x0000F86C), X(0x0000F854), X(0x0000F83B), X(0x0000F823), X(0x0000F80A),
	X(0x0000F7F1), X(0x0000F7D8), X(0x0000F7BF), X(0x0000F7A5), X(0x0000F78C), X(0x0000F772),
	X(0x0000F758), X(0x0000F73E), X(0x0000F724), X(0x0000F70A), X(0x0000F6EF), X(0x0000F6D5),
	X(0x0000F6BA), X(0x0000F69F), X(0x0000F684), X(0x0000F669), X(0x0000F64E), X(0x0000F632),
	X(0x0000F616), X(0x0000F5FB), X(0x0000F5DF), X(0x0000F5C3), X(0x0000F5A6), X(0x0000F58A),
	X(0x0000F56E), X(0x0000F551), X(0x0000F534), X(0x0000F517), X(0x0000F4FA), X(0x0000F4DD),
	X(0x0000F4BF), X(0x0000F4A2), X(0x0000F484), X(0x0000F466), X(0x0000F448), X(0x0000F42A),
	X(0x0000F40C), X(0x0000F3ED), X(0x0000F3CF), X(0x0000F3B0), X(0x0000F391), X(0x0000F372),
	X(0x0000F353), X(0x0000F334), X(0x0000F314), X(0x0000F2F5), X(0x0000F2D5), X(0x0000F2B5),
	X(0x0000F295), X(0x0000F275), X(0x0000F254), X(0x0000F234), X(0x0000F213), X(0x0000F1F3),
	X(0x0000F1D2), X(0x0000F1B1), X(0x0000F18F), X(0x0000F16E), X(0x0000F14C), X(0x0000F12B),
	X(0x0000F109), X(0x0000F0E7), X(0x0000F0C5), X(0x0000F0A3), X(0x0000F080), X(0x0000F05E),
	X(0x0000F03B), X(0x0000F018), X(0x0000EFF5), X(0x0000EFD2), X(0x0000EFAF), X(0x0000EF8C),
	X(0x0000EF68), X(0x0000EF45), X(0x0000EF21), X(0x0000EEFD), X(0x0000EED9), X(0x0000EEB4),
	X(0x0000EE90), X(0x0000EE6B), X(0x0000EE47), X(0x0000EE22), X(0x0000EDFD), X(0x0000EDD8),
	X(0x0000EDB3), X(0x0000ED8D), X(0x0000ED68), X(0x0000ED42), X(0x0000ED1C), X(0x0000ECF6),
	X(0x0000ECD0), X(0x0000ECAA), X(0x0000EC83), X(0x0000EC5D), X(0x0000EC36), X(0x0000EC0F),
	X(0x0000EBE8), X(0x0000EBC1), X(0x0000EB9A), X(0x0000EB73), X(0x0000EB4B), X(0x0000EB23),
	X(0x0000EAFC), X(0x0000EAD4), X(0x0000EAAB), X(0x0000EA83), X(0x0000EA5B), X(0x0000EA32),
	X(0x0000EA0A), X(0x0000E9E1), X(0x0000E9B8), X(0x0000E98F), X(0x0000E966), X(0x0000E93C),
	X(0x0000E913), X(0x0000E8E9), X(0x0000E8BF), X(0x0000E895), X(0x0000E86B), X(0x0000E841),
	X(0x0000E817), X(0x0000E7EC), X(0x0000E7C2), X(0x0000E797), X(0x0000E76C), X(0x0000E741),
	X(0x0000E716), X(0x0000E6EA), X(0x0000E6BF), X(0x0000E693), X(0x0000E667), X(0x0000E63C),
	X(0x0000E610), X(0x0000E5E3), X(0x0000E5B7), X(0x0000E58B), X(0x0000E55E), X(0x0000E531),
	X(0x0000E504), X(0x0000E4D7), X(0x0000E4AA), X(0x0000E47D), X(0x0000E450), X(0x0000E422),
	X(0x0000E3F4), X(0x0000E3C7), X(0x0000E399), X(0x0000E36B), X(0x0000E33C), X(0x0000E30E),
	X(0x0000E2DF), X(0x0000E2B1), X(0x0000E282), X(0x0000E253), X(0x0000E224), X(0x0000E1F5),
	X(0x0000E1C6), X(0x0000E196), X(0x0000E167), X(0x0000E137), X(0x0000E107), X(0x0000E0D7),
	X(0x0000E0A7), X(0x0000E077), X(0x0000E046), X(0x0000E016), X(0x0000DFE5), X(0x0000DFB4),
	X(0x0000DF83), X(0x0000DF52), X(0x0000DF21), X(0x0000DEF0), X(0x0000DEBE), X(0x0000DE8C),
	X(0x0000DE5B), X(0x0000DE29), X(0x0000DDF7), X(0x0000DDC5), X(0x0000DD92), X(0x0000DD60),
	X(0x0000DD2D), X(0x0000DCFB), X(0x0000DCC8), X(0x0000DC95), X(0x0000DC62), X(0x0000DC2F),
	X(0x0000DBFB), X(0x0000DBC8), X(0x0000DB94), X(0x0000DB60), X(0x0000DB2C), X(0x0000DAF8),
	X(0x0000DAC4), X(0x0000DA90), X(0x0000DA5C), X(0x0000DA27), X(0x0000D9F2), X(0x0000D9BE),
	X(0x0000D989), X(0x0000D954), X(0x0000D91E), X(0x0000D8E9), X(0x0000D8B4), X(0x0000D87E),
	X(0x0000D848), X(0x0000D812), X(0x0000D7DC), X(0x0000D7A6), X(0x0000D770), X(0x0000D73A),
	X(0x0000D703), X(0x0000D6CD), X(0x0000D696), X(0x0000D65F), X(0x0000D628), X(0x0000D5F1),
	X(0x0000D5BA), X(0x0000D582), X(0x0000D54B), X(0x0000D513), X(0x0000D4DB), X(0x0000D4A3),
	X(0x0000D46B), X(0x0000D433), X(0x0000D3FB), X(0x0000D3C2), X(0x0000D38A), X(0x0000D351),
	X(0x0000D318), X(0x0000D2DF), X(0x0000D2A6), X(0x0000D26D), X(0x0000D234), X(0x0000D1FA),
	X(0x0000D1C1), X(0x0000D187), X(0x0000D14D), X(0x0000D113), X(0x0000D0D9), X(0x0000D09F),
	X(0x0000D065), X(0x0000D02A), X(0x0000CFF0), X(0x0000CFB5), X(0x0000CF7A), X(0x0000CF3F),
	X(0x0000CF04), X(0x0000CEC9), X(0x0000CE8E), X(0x0000CE52), X(0x0000CE17), X(0x0000CDDB),
	X(0x0000CD9F), X(0x0000CD63), X(0x0000CD27), X(0x0000CCEB), X(0x0000CCAE), X(0x0000CC72),
	X(0x0000CC35), X(0x0000CBF9), X(0x0000CBBC), X(0x0000CB7F), X(0x0000CB42), X(0x0000CB05),
	X(0x0000CAC7), X(0x0000CA8A), X(0x0000CA4D), X(0x0000CA0F), X(0x0000C9D1), X(0x0000C993),
	X(0x0000C955), X(0x0000C917), X(0x0000C8D9), X(0x0000C89A), X(0x0000C85C), X(0x0000C81D),
	X(0x0000C7DE), X(0x0000C7A0), X(0x0000C761), X(0x0000C721), X(0x0000C6E2), X(0x0000C6A3),
	X(0x0000C663), X(0x0000C624), X(0x0000C5E4), X(0x0000C5A4), X(0x0000C564), X(0x0000C524),
	X(0x0000C4E4), X(0x0000C4A4), X(0x0000C463), X(0x0000C423), X(0x0000C3E2), X(0x0000C3A1),
	X(0x0000C360), X(0x0000C31F), X(0x0000C2DE), X(0x0000C29D), X(0x0000C25C), X(0x0000C21A),
	X(0x0000C1D8), X(0x0000C197), X(0x0000C155), X(0x0000C113), X(0x0000C0D1), X(0x0000C08F),
	X(0x0000C04C), X(0x0000C00A), X(0x0000BFC7), X(0x0000BF85), X(0x0000BF42), X(0x0000BEFF),
	X(0x0000BEBC), X(0x0000BE79), X(0x0000BE36), X(0x0000BDF2), X(0x0000BDAF), X(0x0000BD6B),
	X(0x0000BD28), X(0x0000BCE4), X(0x0000BCA0), X(0x0000BC5C), X(0x0000BC18), X(0x0000BBD4),
	X(0x0000BB8F), X(0x0000BB4B), X(0x0000BB06), X(0x0000BAC1), X(0x0000BA7D), X(0x0000BA38),
	X(0x0000B9F3), X(0x0000B9AE), X(0x0000B968), X(0x0000B923), X(0x0000B8DD), X(0x0000B898),
	X(0x0000B852), X(0x0000B80C), X(0x0000B7C6), X(0x0000B780), X(0x0000B73A), X(0x0000B6F4),
	X(0x0000B6AD), X(0x0000B667), X(0x0000B620), X(0x0000B5DA), X(0x0000B593), X(0x0000B54C),
	X(0x0000B505), X(0x0000B4BE), X(0x0000B477), X(0x0000B42F), X(0x0000B3E8), X(0x0000B3A0),
	X(0x0000B358), X(0x0000B311), X(0x0000B2C9), X(0x0000B281), X(0x0000B239), X(0x0000B1F0),
	X(0x0000B1A8), X(0x0000B160), X(0x0000B117), X(0x0000B0CE), X(0x0000B086), X(0x0000B03D),
	X(0x0000AFF4), X(0x0000AFAB), X(0x0000AF62), X(0x0000AF18), X(0x0000AECF), X(0x0000AE85),
	X(0x0000AE3C), X(0x0000ADF2), X(0x0000ADA8), X(0x0000AD5E), X(0x0000AD14), X(0x0000ACCA),
	X(0x0000AC80), X(0x0000AC36), X(0x0000ABEB), X(0x0000ABA1), X(0x0000AB56), X(0x0000AB0B),
	X(0x0000AAC1), X(0x0000AA76), X(0x0000AA2A), X(0x0000A9DF), X(0x0000A994), X(0x0000A949),
	X(0x0000A8FD), X(0x0000A8B2), X(0x0000A866), X(0x0000A81A), X(0x0000A7CE), X(0x0000A782),
	X(0x0000A736), X(0x0000A6EA), X(0x0000A69E), X(0x0000A652), X(0x0000A605), X(0x0000A5B8),
	X(0x0000A56C), X(0x0000A51F), X(0x0000A4D2), X(0x0000A485), X(0x0000A438), X(0x0000A3EB),
	X(0x0000A39E), X(0x0000A350), X(0x0000A303), X(0x0000A2B5), X(0x0000A268), X(0x0000A21A),
	X(0x0000A1CC), X(0x0000A17E), X(0x0000A130), X(0x0000A0E2), X(0x0000A094), X(0x0000A045),
	X(0x00009FF7), X(0x00009FA8), X(0x00009F5A), X(0x00009F0B), X(0x00009EBC), X(0x00009E6D),
	X(0x00009E1E), X(0x00009DCF), X(0x00009D80), X(0x00009D31), X(0x00009CE1), X(0x00009C92),
	X(0x00009C42), X(0x00009BF2), X(0x00009BA3), X(0x00009B53), X(0x00009B03), X(0x00009AB3),
	X(0x00009A63), X(0x00009A12), X(0x000099C2), X(0x00009972), X(0x00009921), X(0x000098D0),
	X(0x00009880), X(0x0000982F), X(0x000097DE), X(0x0000978D), X(0x0000973C), X(0x000096EB),
	X(0x0000969A), X(0x00009648), X(0x000095F7), X(0x000095A5), X(0x00009554), X(0x00009502),
	X(0x000094B0), X(0x0000945E), X(0x0000940C), X(0x000093BA), X(0x00009368), X(0x00009316),
	X(0x000092C4), X(0x00009271), X(0x0000921F), X(0x000091CC), X(0x00009179), X(0x00009127),
	X(0x000090D4), X(0x00009081), X(0x0000902E), X(0x00008FDB), X(0x00008F88), X(0x00008F34),
	X(0x00008EE1), X(0x00008E8D), X(0x00008E3A), X(0x00008DE6), X(0x00008D92), X(0x00008D3F),
	X(0x00008CEB), X(0x00008C97), X(0x00008C43), X(0x00008BEF), X(0x00008B9A), X(0x00008B46),
	X(0x00008AF2), X(0x00008A9D), X(0x00008A49), X(0x000089F4), X(0x0000899F), X(0x0000894A),
	X(0x000088F6), X(0x000088A1), X(0x0000884C), X(0x000087F6), X(0x000087A1), X(0x0000874C),
	X(0x000086F7), X(0x000086A1), X(0x0000864C), X(0x000085F6), X(0x000085A0), X(0x0000854A),
	X(0x000084F5), X(0x0000849F), X(0x00008449), X(0x000083F2), X(0x0000839C), X(0x00008346),
	X(0x000082F0), X(0x00008299), X(0x00008243), X(0x000081EC), X(0x00008195), X(0x0000813F),
	X(0x000080E8), X(0x00008091), X(0x0000803A), X(0x00007FE3), X(0x00007F8C), X(0x00007F35),
	X(0x00007EDD), X(0x00007E86), X(0x00007E2F), X(0x00007DD7), X(0x00007D7F), X(0x00007D28),
	X(0x00007CD0), X(0x00007C78), X(0x00007C20), X(0x00007BC8), X(0x00007B70), X(0x00007B18),
	X(0x00007AC0), X(0x00007A68), X(0x00007A10), X(0x000079B7), X(0x0000795F), X(0x00007906),
	X(0x000078AD), X(0x00007855), X(0x000077FC), X(0x000077A3), X(0x0000774A), X(0x000076F1),
	X(0x00007698), X(0x0000763F), X(0x000075E6), X(0x0000758D), X(0x00007533), X(0x000074DA),
	X(0x00007480), X(0x00007427), X(0x000073CD), X(0x00007373), X(0x0000731A), X(0x000072C0),
	X(0x00007266), X(0x0000720C), X(0x000071B2), X(0x00007158), X(0x000070FE), X(0x000070A3),
	X(0x00007049), X(0x00006FEF), X(0x00006F94), X(0x00006F3A), X(0x00006EDF), X(0x00006E85),
	X(0x00006E2A), X(0x00006DCF), X(0x00006D74), X(0x00006D19), X(0x00006CBE), X(0x00006C63),
	X(0x00006C08), X(0x00006BAD), X(0x00006B52), X(0x00006AF6), X(0x00006A9B), X(0x00006A40),
	X(0x000069E4), X(0x00006989), X(0x0000692D), X(0x000068D1), X(0x00006876), X(0x0000681A),
	X(0x000067BE), X(0x00006762), X(0x00006706), X(0x000066AA), X(0x0000664E), X(0x000065F2),
	X(0x00006595), X(0x00006539), X(0x000064DD), X(0x00006480), X(0x00006424), X(0x000063C7),
	X(0x0000636B), X(0x0000630E), X(0x000062B1), X(0x00006254), X(0x000061F8), X(0x0000619B),
	X(0x0000613E), X(0x000060E1), X(0x00006084), X(0x00006026), X(0x00005FC9), X(0x00005F6C),
	X(0x00005F0F), X(0x00005EB1), X(0x00005E54), X(0x00005DF6), X(0x00005D99), X(0x00005D3B),
	X(0x00005CDE), X(0x00005C80), X(0x00005C22), X(0x00005BC4), X(0x00005B66), X(0x00005B08),
	X(0x00005AAA), X(0x00005A4C), X(0x000059EE), X(0x00005990), X(0x00005932), X(0x000058D4),
	X(0x00005875), X(0x00005817), X(0x000057B9), X(0x0000575A), X(0x000056FC), X(0x0000569D),
	X(0x0000563E), X(0x000055E0), X(0x00005581), X(0x00005522), X(0x000054C3), X(0x00005464),
	X(0x00005406), X(0x000053A7), X(0x00005348), X(0x000052E8), X(0x00005289), X(0x0000522A),
	X(0x000051CB), X(0x0000516C), X(0x0000510C), X(0x000050AD), X(0x0000504D), X(0x00004FEE),
	X(0x00004F8E), X(0x00004F2F), X(0x00004ECF), X(0x00004E70), X(0x00004E10), X(0x00004DB0),
	X(0x00004D50), X(0x00004CF0), X(0x00004C90), X(0x00004C31), X(0x00004BD1), X(0x00004B70),
	X(0x00004B10), X(0x00004AB0), X(0x00004A50), X(0x000049F0), X(0x00004990), X(0x0000492F),
	X(0x000048CF), X(0x0000486F), X(0x0000480E), X(0x000047AE), X(0x0000474D), X(0x000046EC),
	X(0x0000468C), X(0x0000462B), X(0x000045CB), X(0x0000456A), X(0x00004509), X(0x000044A8),
	X(0x00004447), X(0x000043E6), X(0x00004385), X(0x00004324), X(0x000042C3), X(0x00004262),
	X(0x00004201), X(0x000041A0), X(0x0000413F), X(0x000040DE), X(0x0000407C), X(0x0000401B),
	X(0x00003FBA), X(0x00003F58), X(0x00003EF7), X(0x00003E95), X(0x00003E34), X(0x00003DD2),
	X(0x00003D71), X(0x00003D0F), X(0x00003CAE), X(0x00003C4C), X(0x00003BEA), X(0x00003B88),
	X(0x00003B27), X(0x00003AC5), X(0x00003A63), X(0x00003A01), X(0x0000399F), X(0x0000393D),
	X(0x000038DB), X(0x00003879), X(0x00003817), X(0x000037B5), X(0x00003753), X(0x000036F1),
	X(0x0000368E), X(0x0000362C), X(0x000035CA), X(0x00003568), X(0x00003505), X(0x000034A3),
	X(0x00003440), X(0x000033DE), X(0x0000337C), X(0x00003319), X(0x000032B7), X(0x00003254),
	X(0x000031F1), X(0x0000318F), X(0x0000312C), X(0x000030CA), X(0x00003067), X(0x00003004),
	X(0x00002FA1), X(0x00002F3F), X(0x00002EDC), X(0x00002E79), X(0x00002E16), X(0x00002DB3),
	X(0x00002D50), X(0x00002CED), X(0x00002C8A), X(0x00002C27), X(0x00002BC4), X(0x00002B61),
	X(0x00002AFE), X(0x00002A9B), X(0x00002A38), X(0x000029D5), X(0x00002971), X(0x0000290E),
	X(0x000028AB), X(0x00002848), X(0x000027E4), X(0x00002781), X(0x0000271E), X(0x000026BA),
	X(0x00002657), X(0x000025F4), X(0x00002590), X(0x0000252D), X(0x000024C9), X(0x00002466),
	X(0x00002402), X(0x0000239F), X(0x0000233B), X(0x000022D7), X(0x00002274), X(0x00002210),
	X(0x000021AD), X(0x00002149), X(0x000020E5), X(0x00002082), X(0x0000201E), X(0x00001FBA),
	X(0x00001F56), X(0x00001EF3), X(0x00001E8F), X(0x00001E2B), X(0x00001DC7), X(0x00001D63),
	X(0x00001CFF), X(0x00001C9B), X(0x00001C38), X(0x00001BD4), X(0x00001B70), X(0x00001B0C),
	X(0x00001AA8), X(0x00001A44), X(0x000019E0), X(0x0000197C), X(0x00001918), X(0x000018B4),
	X(0x00001850), X(0x000017EB), X(0x00001787), X(0x00001723), X(0x000016BF), X(0x0000165B),
	X(0x000015F7), X(0x00001593), X(0x0000152E), X(0x000014CA), X(0x00001466), X(0x00001402),
	X(0x0000139E), X(0x00001339), X(0x000012D5), X(0x00001271), X(0x0000120D), X(0x000011A8),
	X(0x00001144), X(0x000010E0), X(0x0000107B), X(0x00001017), X(0x00000FB3), X(0x00000F4E),
	X(0x00000EEA), X(0x00000E86), X(0x00000E21), X(0x00000DBD), X(0x00000D58), X(0x00000CF4),
	X(0x00000C90), X(0x00000C2B), X(0x00000BC7), X(0x00000B62), X(0x00000AFE), X(0x00000A9A),
	X(0x00000A35), X(0x000009D1), X(0x0000096C), X(0x00000908), X(0x000008A3), X(0x0000083F),
	X(0x000007DA), X(0x00000776), X(0x00000711), X(0x000006AD), X(0x00000648), X(0x000005E4),
	X(0x0000057F), X(0x0000051B), X(0x000004B6), X(0x00000452), X(0x000003ED), X(0x00000389),
	X(0x00000324), X(0x000002C0), X(0x0000025B), X(0x000001F7), X(0x00000192), X(0x0000012E),
	X(0x000000C9), X(0x00000065), X(0x00000000), X(0xFFFFFF9B), X(0xFFFFFF37), X(0xFFFFFED2),
	X(0xFFFFFE6E), X(0xFFFFFE09), X(0xFFFFFDA5), X(0xFFFFFD40), X(0xFFFFFCDC), X(0xFFFFFC77),
	X(0xFFFFFC13), X(0xFFFFFBAE), X(0xFFFFFB4A), X(0xFFFFFAE5), X(0xFFFFFA81), X(0xFFFFFA1C),
	X(0xFFFFF9B8), X(0xFFFFF953), X(0xFFFFF8EF), X(0xFFFFF88A), X(0xFFFFF826), X(0xFFFFF7C1),
	X(0xFFFFF75D), X(0xFFFFF6F8), X(0xFFFFF694), X(0xFFFFF62F), X(0xFFFFF5CB), X(0xFFFFF566),
	X(0xFFFFF502), X(0xFFFFF49E), X(0xFFFFF439), X(0xFFFFF3D5), X(0xFFFFF370), X(0xFFFFF30C),
	X(0xFFFFF2A7), X(0xFFFFF243), X(0xFFFFF1DF), X(0xFFFFF17A), X(0xFFFFF116), X(0xFFFFF0B2),
	X(0xFFFFF04D), X(0xFFFFEFE9), X(0xFFFFEF85), X(0xFFFFEF20), X(0xFFFFEEBC), X(0xFFFFEE58),
	X(0xFFFFEDF3), X(0xFFFFED8F), X(0xFFFFED2B), X(0xFFFFECC7), X(0xFFFFEC62), X(0xFFFFEBFE),
	X(0xFFFFEB9A), X(0xFFFFEB36), X(0xFFFFEAD2), X(0xFFFFEA6D), X(0xFFFFEA09), X(0xFFFFE9A5),
	X(0xFFFFE941), X(0xFFFFE8DD), X(0xFFFFE879), X(0xFFFFE815), X(0xFFFFE7B0), X(0xFFFFE74C),
	X(0xFFFFE6E8), X(0xFFFFE684), X(0xFFFFE620), X(0xFFFFE5BC), X(0xFFFFE558), X(0xFFFFE4F4),
	X(0xFFFFE490), X(0xFFFFE42C), X(0xFFFFE3C8), X(0xFFFFE365), X(0xFFFFE301), X(0xFFFFE29D),
	X(0xFFFFE239), X(0xFFFFE1D5), X(0xFFFFE171), X(0xFFFFE10D), X(0xFFFFE0AA), X(0xFFFFE046),
	X(0xFFFFDFE2), X(0xFFFFDF7E), X(0xFFFFDF1B), X(0xFFFFDEB7), X(0xFFFFDE53), X(0xFFFFDDF0),
	X(0xFFFFDD8C), X(0xFFFFDD29), X(0xFFFFDCC5), X(0xFFFFDC61), X(0xFFFFDBFE), X(0xFFFFDB9A),
	X(0xFFFFDB37), X(0xFFFFDAD3), X(0xFFFFDA70), X(0xFFFFDA0C), X(0xFFFFD9A9), X(0xFFFFD946),
	X(0xFFFFD8E2), X(0xFFFFD87F), X(0xFFFFD81C), X(0xFFFFD7B8), X(0xFFFFD755), X(0xFFFFD6F2),
	X(0xFFFFD68F), X(0xFFFFD62B), X(0xFFFFD5C8), X(0xFFFFD565), X(0xFFFFD502), X(0xFFFFD49F),
	X(0xFFFFD43C), X(0xFFFFD3D9), X(0xFFFFD376), X(0xFFFFD313), X(0xFFFFD2B0), X(0xFFFFD24D),
	X(0xFFFFD1EA), X(0xFFFFD187), X(0xFFFFD124), X(0xFFFFD0C1), X(0xFFFFD05F), X(0xFFFFCFFC),
	X(0xFFFFCF99), X(0xFFFFCF36), X(0xFFFFCED4), X(0xFFFFCE71), X(0xFFFFCE0F), X(0xFFFFCDAC),
	X(0xFFFFCD49), X(0xFFFFCCE7), X(0xFFFFCC84), X(0xFFFFCC22), X(0xFFFFCBC0), X(0xFFFFCB5D),
	X(0xFFFFCAFB), X(0xFFFFCA98), X(0xFFFFCA36), X(0xFFFFC9D4), X(0xFFFFC972), X(0xFFFFC90F),
	X(0xFFFFC8AD), X(0xFFFFC84B), X(0xFFFFC7E9), X(0xFFFFC787), X(0xFFFFC725), X(0xFFFFC6C3),
	X(0xFFFFC661), X(0xFFFFC5FF), X(0xFFFFC59D), X(0xFFFFC53B), X(0xFFFFC4D9), X(0xFFFFC478),
	X(0xFFFFC416), X(0xFFFFC3B4), X(0xFFFFC352), X(0xFFFFC2F1), X(0xFFFFC28F), X(0xFFFFC22E),
	X(0xFFFFC1CC), X(0xFFFFC16B), X(0xFFFFC109), X(0xFFFFC0A8), X(0xFFFFC046), X(0xFFFFBFE5),
	X(0xFFFFBF84), X(0xFFFFBF22), X(0xFFFFBEC1), X(0xFFFFBE60), X(0xFFFFBDFF), X(0xFFFFBD9E),
	X(0xFFFFBD3D), X(0xFFFFBCDC), X(0xFFFFBC7B), X(0xFFFFBC1A), X(0xFFFFBBB9), X(0xFFFFBB58),
	X(0xFFFFBAF7), X(0xFFFFBA96), X(0xFFFFBA35), X(0xFFFFB9D5), X(0xFFFFB974), X(0xFFFFB914),
	X(0xFFFFB8B3), X(0xFFFFB852), X(0xFFFFB7F2), X(0xFFFFB791), X(0xFFFFB731), X(0xFFFFB6D1),
	X(0xFFFFB670), X(0xFFFFB610), X(0xFFFFB5B0), X(0xFFFFB550), X(0xFFFFB4F0), X(0xFFFFB48F),
	X(0xFFFFB42F), X(0xFFFFB3CF), X(0xFFFFB36F), X(0xFFFFB310), X(0xFFFFB2B0), X(0xFFFFB250),
	X(0xFFFFB1F0), X(0xFFFFB190), X(0xFFFFB131), X(0xFFFFB0D1), X(0xFFFFB072), X(0xFFFFB012),
	X(0xFFFFAFB3), X(0xFFFFAF53), X(0xFFFFAEF4), X(0xFFFFAE94), X(0xFFFFAE35), X(0xFFFFADD6),
	X(0xFFFFAD77), X(0xFFFFAD18), X(0xFFFFACB8), X(0xFFFFAC59), X(0xFFFFABFA), X(0xFFFFAB9B),
	X(0xFFFFAB3D), X(0xFFFFAADE), X(0xFFFFAA7F), X(0xFFFFAA20), X(0xFFFFA9C2), X(0xFFFFA963),
	X(0xFFFFA904), X(0xFFFFA8A6), X(0xFFFFA847), X(0xFFFFA7E9), X(0xFFFFA78B), X(0xFFFFA72C),
	X(0xFFFFA6CE), X(0xFFFFA670), X(0xFFFFA612), X(0xFFFFA5B4), X(0xFFFFA556), X(0xFFFFA4F8),
	X(0xFFFFA49A), X(0xFFFFA43C), X(0xFFFFA3DE), X(0xFFFFA380), X(0xFFFFA322), X(0xFFFFA2C5),
	X(0xFFFFA267), X(0xFFFFA20A), X(0xFFFFA1AC), X(0xFFFFA14F), X(0xFFFFA0F1), X(0xFFFFA094),
	X(0xFFFFA037), X(0xFFFF9FDA), X(0xFFFF9F7C), X(0xFFFF9F1F), X(0xFFFF9EC2), X(0xFFFF9E65),
	X(0xFFFF9E08), X(0xFFFF9DAC), X(0xFFFF9D4F), X(0xFFFF9CF2), X(0xFFFF9C95), X(0xFFFF9C39),
	X(0xFFFF9BDC), X(0xFFFF9B80), X(0xFFFF9B23), X(0xFFFF9AC7), X(0xFFFF9A6B), X(0xFFFF9A0E),
	X(0xFFFF99B2), X(0xFFFF9956), X(0xFFFF98FA), X(0xFFFF989E), X(0xFFFF9842), X(0xFFFF97E6),
	X(0xFFFF978A), X(0xFFFF972F), X(0xFFFF96D3), X(0xFFFF9677), X(0xFFFF961C), X(0xFFFF95C0),
	X(0xFFFF9565), X(0xFFFF9509), X(0xFFFF94AE), X(0xFFFF9453), X(0xFFFF93F8), X(0xFFFF939D),
	X(0xFFFF9342), X(0xFFFF92E7), X(0xFFFF928C), X(0xFFFF9231), X(0xFFFF91D6), X(0xFFFF917B),
	X(0xFFFF9121), X(0xFFFF90C6), X(0xFFFF906C), X(0xFFFF9011), X(0xFFFF8FB7), X(0xFFFF8F5D),
	X(0xFFFF8F02), X(0xFFFF8EA8), X(0xFFFF8E4E), X(0xFFFF8DF4), X(0xFFFF8D9A), X(0xFFFF8D40),
	X(0xFFFF8CE6), X(0xFFFF8C8D), X(0xFFFF8C33), X(0xFFFF8BD9), X(0xFFFF8B80), X(0xFFFF8B26),
	X(0xFFFF8ACD), X(0xFFFF8A73), X(0xFFFF8A1A), X(0xFFFF89C1), X(0xFFFF8968), X(0xFFFF890F),
	X(0xFFFF88B6), X(0xFFFF885D), X(0xFFFF8804), X(0xFFFF87AB), X(0xFFFF8753), X(0xFFFF86FA),
	X(0xFFFF86A1), X(0xFFFF8649), X(0xFFFF85F0), X(0xFFFF8598), X(0xFFFF8540), X(0xFFFF84E8),
	X(0xFFFF8490), X(0xFFFF8438), X(0xFFFF83E0), X(0xFFFF8388), X(0xFFFF8330), X(0xFFFF82D8),
	X(0xFFFF8281), X(0xFFFF8229), X(0xFFFF81D1), X(0xFFFF817A), X(0xFFFF8123), X(0xFFFF80CB),
	X(0xFFFF8074), X(0xFFFF801D), X(0xFFFF7FC6), X(0xFFFF7F6F), X(0xFFFF7F18), X(0xFFFF7EC1),
	X(0xFFFF7E6B), X(0xFFFF7E14), X(0xFFFF7DBD), X(0xFFFF7D67), X(0xFFFF7D10), X(0xFFFF7CBA),
	X(0xFFFF7C64), X(0xFFFF7C0E), X(0xFFFF7BB7), X(0xFFFF7B61), X(0xFFFF7B0B), X(0xFFFF7AB6),
	X(0xFFFF7A60), X(0xFFFF7A0A), X(0xFFFF79B4), X(0xFFFF795F), X(0xFFFF7909), X(0xFFFF78B4),
	X(0xFFFF785F), X(0xFFFF780A), X(0xFFFF77B4), X(0xFFFF775F), X(0xFFFF770A), X(0xFFFF76B5),
	X(0xFFFF7661), X(0xFFFF760C), X(0xFFFF75B7), X(0xFFFF7563), X(0xFFFF750E), X(0xFFFF74BA),
	X(0xFFFF7466), X(0xFFFF7411), X(0xFFFF73BD), X(0xFFFF7369), X(0xFFFF7315), X(0xFFFF72C1),
	X(0xFFFF726D), X(0xFFFF721A), X(0xFFFF71C6), X(0xFFFF7173), X(0xFFFF711F), X(0xFFFF70CC),
	X(0xFFFF7078), X(0xFFFF7025), X(0xFFFF6FD2), X(0xFFFF6F7F), X(0xFFFF6F2C), X(0xFFFF6ED9),
	X(0xFFFF6E87), X(0xFFFF6E34), X(0xFFFF6DE1), X(0xFFFF6D8F), X(0xFFFF6D3C), X(0xFFFF6CEA),
	X(0xFFFF6C98), X(0xFFFF6C46), X(0xFFFF6BF4), X(0xFFFF6BA2), X(0xFFFF6B50), X(0xFFFF6AFE),
	X(0xFFFF6AAC), X(0xFFFF6A5B), X(0xFFFF6A09), X(0xFFFF69B8), X(0xFFFF6966), X(0xFFFF6915),
	X(0xFFFF68C4), X(0xFFFF6873), X(0xFFFF6822), X(0xFFFF67D1), X(0xFFFF6780), X(0xFFFF6730),
	X(0xFFFF66DF), X(0xFFFF668E), X(0xFFFF663E), X(0xFFFF65EE), X(0xFFFF659D), X(0xFFFF654D),
	X(0xFFFF64FD), X(0xFFFF64AD), X(0xFFFF645D), X(0xFFFF640E), X(0xFFFF63BE), X(0xFFFF636E),
	X(0xFFFF631F), X(0xFFFF62CF), X(0xFFFF6280), X(0xFFFF6231), X(0xFFFF61E2), X(0xFFFF6193),
	X(0xFFFF6144), X(0xFFFF60F5), X(0xFFFF60A6), X(0xFFFF6058), X(0xFFFF6009), X(0xFFFF5FBB),
	X(0xFFFF5F6C), X(0xFFFF5F1E), X(0xFFFF5ED0), X(0xFFFF5E82), X(0xFFFF5E34), X(0xFFFF5DE6),
	X(0xFFFF5D98), X(0xFFFF5D4B), X(0xFFFF5CFD), X(0xFFFF5CB0), X(0xFFFF5C62), X(0xFFFF5C15),
	X(0xFFFF5BC8), X(0xFFFF5B7B), X(0xFFFF5B2E), X(0xFFFF5AE1), X(0xFFFF5A94), X(0xFFFF5A48),
	X(0xFFFF59FB), X(0xFFFF59AE), X(0xFFFF5962), X(0xFFFF5916), X(0xFFFF58CA), X(0xFFFF587E),
	X(0xFFFF5832), X(0xFFFF57E6), X(0xFFFF579A), X(0xFFFF574E), X(0xFFFF5703), X(0xFFFF56B7),
	X(0xFFFF566C), X(0xFFFF5621), X(0xFFFF55D5), X(0xFFFF558A), X(0xFFFF553F), X(0xFFFF54F5),
	X(0xFFFF54AA), X(0xFFFF545F), X(0xFFFF5415), X(0xFFFF53CA), X(0xFFFF5380), X(0xFFFF5336),
	X(0xFFFF52EC), X(0xFFFF52A2), X(0xFFFF5258), X(0xFFFF520E), X(0xFFFF51C4), X(0xFFFF517B),
	X(0xFFFF5131), X(0xFFFF50E8), X(0xFFFF509E), X(0xFFFF5055), X(0xFFFF500C), X(0xFFFF4FC3),
	X(0xFFFF4F7A), X(0xFFFF4F32), X(0xFFFF4EE9), X(0xFFFF4EA0), X(0xFFFF4E58), X(0xFFFF4E10),
	X(0xFFFF4DC7), X(0xFFFF4D7F), X(0xFFFF4D37), X(0xFFFF4CEF), X(0xFFFF4CA8), X(0xFFFF4C60),
	X(0xFFFF4C18), X(0xFFFF4BD1), X(0xFFFF4B89), X(0xFFFF4B42), X(0xFFFF4AFB), X(0xFFFF4AB4),
	X(0xFFFF4A6D), X(0xFFFF4A26), X(0xFFFF49E0), X(0xFFFF4999), X(0xFFFF4952), X(0xFFFF490C),
	X(0xFFFF48C6), X(0xFFFF4880), X(0xFFFF483A), X(0xFFFF47F4), X(0xFFFF47AE), X(0xFFFF4768),
	X(0xFFFF4723), X(0xFFFF46DD), X(0xFFFF4698), X(0xFFFF4652), X(0xFFFF460D), X(0xFFFF45C8),
	X(0xFFFF4583), X(0xFFFF453F), X(0xFFFF44FA), X(0xFFFF44B5), X(0xFFFF4471), X(0xFFFF442C),
	X(0xFFFF43E8), X(0xFFFF43A4), X(0xFFFF4360), X(0xFFFF431C), X(0xFFFF42D8), X(0xFFFF4295),
	X(0xFFFF4251), X(0xFFFF420E), X(0xFFFF41CA), X(0xFFFF4187), X(0xFFFF4144), X(0xFFFF4101),
	X(0xFFFF40BE), X(0xFFFF407B), X(0xFFFF4039), X(0xFFFF3FF6), X(0xFFFF3FB4), X(0xFFFF3F71),
	X(0xFFFF3F2F), X(0xFFFF3EED), X(0xFFFF3EAB), X(0xFFFF3E69), X(0xFFFF3E28), X(0xFFFF3DE6),
	X(0xFFFF3DA4), X(0xFFFF3D63), X(0xFFFF3D22), X(0xFFFF3CE1), X(0xFFFF3CA0), X(0xFFFF3C5F),
	X(0xFFFF3C1E), X(0xFFFF3BDD), X(0xFFFF3B9D), X(0xFFFF3B5C), X(0xFFFF3B1C), X(0xFFFF3ADC),
	X(0xFFFF3A9C), X(0xFFFF3A5C), X(0xFFFF3A1C), X(0xFFFF39DC), X(0xFFFF399D), X(0xFFFF395D),
	X(0xFFFF391E), X(0xFFFF38DF), X(0xFFFF389F), X(0xFFFF3860), X(0xFFFF3822), X(0xFFFF37E3),
	X(0xFFFF37A4), X(0xFFFF3766), X(0xFFFF3727), X(0xFFFF36E9), X(0xFFFF36AB), X(0xFFFF366D),
	X(0xFFFF362F), X(0xFFFF35F1), X(0xFFFF35B3), X(0xFFFF3576), X(0xFFFF3538), X(0xFFFF34FB),
	X(0xFFFF34BE), X(0xFFFF3481), X(0xFFFF3444), X(0xFFFF3407), X(0xFFFF33CB), X(0xFFFF338E),
	X(0xFFFF3352), X(0xFFFF3315), X(0xFFFF32D9), X(0xFFFF329D), X(0xFFFF3261), X(0xFFFF3225),
	X(0xFFFF31E9), X(0xFFFF31AE), X(0xFFFF3172), X(0xFFFF3137), X(0xFFFF30FC), X(0xFFFF30C1),
	X(0xFFFF3086), X(0xFFFF304B), X(0xFFFF3010), X(0xFFFF2FD6), X(0xFFFF2F9B), X(0xFFFF2F61),
	X(0xFFFF2F27), X(0xFFFF2EED), X(0xFFFF2EB3), X(0xFFFF2E79), X(0xFFFF2E3F), X(0xFFFF2E06),
	X(0xFFFF2DCC), X(0xFFFF2D93), X(0xFFFF2D5A), X(0xFFFF2D21), X(0xFFFF2CE8), X(0xFFFF2CAF),
	X(0xFFFF2C76), X(0xFFFF2C3E), X(0xFFFF2C05), X(0xFFFF2BCD), X(0xFFFF2B95), X(0xFFFF2B5D),
	X(0xFFFF2B25), X(0xFFFF2AED), X(0xFFFF2AB5), X(0xFFFF2A7E), X(0xFFFF2A46), X(0xFFFF2A0F),
	X(0xFFFF29D8), X(0xFFFF29A1), X(0xFFFF296A), X(0xFFFF2933), X(0xFFFF28FD), X(0xFFFF28C6),
	X(0xFFFF2890), X(0xFFFF285A), X(0xFFFF2824), X(0xFFFF27EE), X(0xFFFF27B8), X(0xFFFF2782),
	X(0xFFFF274C), X(0xFFFF2717), X(0xFFFF26E2), X(0xFFFF26AC), X(0xFFFF2677), X(0xFFFF2642),
	X(0xFFFF260E), X(0xFFFF25D9), X(0xFFFF25A4), X(0xFFFF2570), X(0xFFFF253C), X(0xFFFF2508),
	X(0xFFFF24D4), X(0xFFFF24A0), X(0xFFFF246C), X(0xFFFF2438), X(0xFFFF2405), X(0xFFFF23D1),
	X(0xFFFF239E), X(0xFFFF236B), X(0xFFFF2338), X(0xFFFF2305), X(0xFFFF22D3), X(0xFFFF22A0),
	X(0xFFFF226E), X(0xFFFF223B), X(0xFFFF2209), X(0xFFFF21D7), X(0xFFFF21A5), X(0xFFFF2174),
	X(0xFFFF2142), X(0xFFFF2110), X(0xFFFF20DF), X(0xFFFF20AE), X(0xFFFF207D), X(0xFFFF204C),
	X(0xFFFF201B), X(0xFFFF1FEA), X(0xFFFF1FBA), X(0xFFFF1F89), X(0xFFFF1F59), X(0xFFFF1F29),
	X(0xFFFF1EF9), X(0xFFFF1EC9), X(0xFFFF1E99), X(0xFFFF1E6A), X(0xFFFF1E3A), X(0xFFFF1E0B),
	X(0xFFFF1DDC), X(0xFFFF1DAD), X(0xFFFF1D7E), X(0xFFFF1D4F), X(0xFFFF1D21), X(0xFFFF1CF2),
	X(0xFFFF1CC4), X(0xFFFF1C95), X(0xFFFF1C67), X(0xFFFF1C39), X(0xFFFF1C0C), X(0xFFFF1BDE),
	X(0xFFFF1BB0), X(0xFFFF1B83), X(0xFFFF1B56), X(0xFFFF1B29), X(0xFFFF1AFC), X(0xFFFF1ACF),
	X(0xFFFF1AA2), X(0xFFFF1A75), X(0xFFFF1A49), X(0xFFFF1A1D), X(0xFFFF19F0), X(0xFFFF19C4),
	X(0xFFFF1999), X(0xFFFF196D), X(0xFFFF1941), X(0xFFFF1916), X(0xFFFF18EA), X(0xFFFF18BF),
	X(0xFFFF1894), X(0xFFFF1869), X(0xFFFF183E), X(0xFFFF1814), X(0xFFFF17E9), X(0xFFFF17BF),
	X(0xFFFF1795), X(0xFFFF176B), X(0xFFFF1741), X(0xFFFF1717), X(0xFFFF16ED), X(0xFFFF16C4),
	X(0xFFFF169A), X(0xFFFF1671), X(0xFFFF1648), X(0xFFFF161F), X(0xFFFF15F6), X(0xFFFF15CE),
	X(0xFFFF15A5), X(0xFFFF157D), X(0xFFFF1555), X(0xFFFF152C), X(0xFFFF1504), X(0xFFFF14DD),
	X(0xFFFF14B5), X(0xFFFF148D), X(0xFFFF1466), X(0xFFFF143F), X(0xFFFF1418), X(0xFFFF13F1),
	X(0xFFFF13CA), X(0xFFFF13A3), X(0xFFFF137D), X(0xFFFF1356), X(0xFFFF1330), X(0xFFFF130A),
	X(0xFFFF12E4), X(0xFFFF12BE), X(0xFFFF1298), X(0xFFFF1273), X(0xFFFF124D), X(0xFFFF1228),
	X(0xFFFF1203), X(0xFFFF11DE), X(0xFFFF11B9), X(0xFFFF1195), X(0xFFFF1170), X(0xFFFF114C),
	X(0xFFFF1127), X(0xFFFF1103), X(0xFFFF10DF), X(0xFFFF10BB), X(0xFFFF1098), X(0xFFFF1074),
	X(0xFFFF1051), X(0xFFFF102E), X(0xFFFF100B), X(0xFFFF0FE8), X(0xFFFF0FC5), X(0xFFFF0FA2),
	X(0xFFFF0F80), X(0xFFFF0F5D), X(0xFFFF0F3B), X(0xFFFF0F19), X(0xFFFF0EF7), X(0xFFFF0ED5),
	X(0xFFFF0EB4), X(0xFFFF0E92), X(0xFFFF0E71), X(0xFFFF0E4F), X(0xFFFF0E2E), X(0xFFFF0E0D),
	X(0xFFFF0DED), X(0xFFFF0DCC), X(0xFFFF0DAC), X(0xFFFF0D8B), X(0xFFFF0D6B), X(0xFFFF0D4B),
	X(0xFFFF0D2B), X(0xFFFF0D0B), X(0xFFFF0CEC), X(0xFFFF0CCC), X(0xFFFF0CAD), X(0xFFFF0C8E),
	X(0xFFFF0C6F), X(0xFFFF0C50), X(0xFFFF0C31), X(0xFFFF0C13), X(0xFFFF0BF4), X(0xFFFF0BD6),
	X(0xFFFF0BB8), X(0xFFFF0B9A), X(0xFFFF0B7C), X(0xFFFF0B5E), X(0xFFFF0B41), X(0xFFFF0B23),
	X(0xFFFF0B06), X(0xFFFF0AE9), X(0xFFFF0ACC), X(0xFFFF0AAF), X(0xFFFF0A92), X(0xFFFF0A76),
	X(0xFFFF0A5A), X(0xFFFF0A3D), X(0xFFFF0A21), X(0xFFFF0A05), X(0xFFFF09EA), X(0xFFFF09CE),
	X(0xFFFF09B2), X(0xFFFF0997), X(0xFFFF097C), X(0xFFFF0961), X(0xFFFF0946), X(0xFFFF092B),
	X(0xFFFF0911), X(0xFFFF08F6), X(0xFFFF08DC), X(0xFFFF08C2), X(0xFFFF08A8), X(0xFFFF088E),
	X(0xFFFF0874), X(0xFFFF085B), X(0xFFFF0841), X(0xFFFF0828), X(0xFFFF080F), X(0xFFFF07F6),
	X(0xFFFF07DD), X(0xFFFF07C5), X(0xFFFF07AC), X(0xFFFF0794), X(0xFFFF077B), X(0xFFFF0763),
	X(0xFFFF074C), X(0xFFFF0734), X(0xFFFF071C), X(0xFFFF0705), X(0xFFFF06ED), X(0xFFFF06D6),
	X(0xFFFF06BF), X(0xFFFF06A8), X(0xFFFF0692), X(0xFFFF067B), X(0xFFFF0665), X(0xFFFF064E),
	X(0xFFFF0638), X(0xFFFF0622), X(0xFFFF060D), X(0xFFFF05F7), X(0xFFFF05E1), X(0xFFFF05CC),
	X(0xFFFF05B7), X(0xFFFF05A2), X(0xFFFF058D), X(0xFFFF0578), X(0xFFFF0564), X(0xFFFF054F),
	X(0xFFFF053B), X(0xFFFF0527), X(0xFFFF0513), X(0xFFFF04FF), X(0xFFFF04EB), X(0xFFFF04D8),
	X(0xFFFF04C4), X(0xFFFF04B1), X(0xFFFF049E), X(0xFFFF048B), X(0xFFFF0478), X(0xFFFF0466),
	X(0xFFFF0453), X(0xFFFF0441), X(0xFFFF042F), X(0xFFFF041D), X(0xFFFF040B), X(0xFFFF03F9),
	X(0xFFFF03E8), X(0xFFFF03D6), X(0xFFFF03C5), X(0xFFFF03B4), X(0xFFFF03A3), X(0xFFFF0392),
	X(0xFFFF0381), X(0xFFFF0371), X(0xFFFF0360), X(0xFFFF0350), X(0xFFFF0340), X(0xFFFF0330),
	X(0xFFFF0321), X(0xFFFF0311), X(0xFFFF0302), X(0xFFFF02F2), X(0xFFFF02E3), X(0xFFFF02D4),
	X(0xFFFF02C5), X(0xFFFF02B7), X(0xFFFF02A8), X(0xFFFF029A), X(0xFFFF028C), X(0xFFFF027D),
	X(0xFFFF0270), X(0xFFFF0262), X(0xFFFF0254), X(0xFFFF0247), X(0xFFFF0239), X(0xFFFF022C),
	X(0xFFFF021F), X(0xFFFF0212), X(0xFFFF0206), X(0xFFFF01F9), X(0xFFFF01ED), X(0xFFFF01E1),
	X(0xFFFF01D5), X(0xFFFF01C9), X(0xFFFF01BD), X(0xFFFF01B1), X(0xFFFF01A6), X(0xFFFF019A),
	X(0xFFFF018F), X(0xFFFF0184), X(0xFFFF0179), X(0xFFFF016F), X(0xFFFF0164), X(0xFFFF015A),
	X(0xFFFF0150), X(0xFFFF0146), X(0xFFFF013C), X(0xFFFF0132), X(0xFFFF0128), X(0xFFFF011F),
	X(0xFFFF0115), X(0xFFFF010C), X(0xFFFF0103), X(0xFFFF00FA), X(0xFFFF00F2), X(0xFFFF00E9),
	X(0xFFFF00E1), X(0xFFFF00D8), X(0xFFFF00D0), X(0xFFFF00C8), X(0xFFFF00C1), X(0xFFFF00B9),
	X(0xFFFF00B2), X(0xFFFF00AA), X(0xFFFF00A3), X(0xFFFF009C), X(0xFFFF0095), X(0xFFFF008F),
	X(0xFFFF0088), X(0xFFFF0082), X(0xFFFF007B), X(0xFFFF0075), X(0xFFFF006F), X(0xFFFF006A),
	X(0xFFFF0064), X(0xFFFF005E), X(0xFFFF0059), X(0xFFFF0054), X(0xFFFF004F), X(0xFFFF004A),
	X(0xFFFF0045), X(0xFFFF0041), X(0xFFFF003C), X(0xFFFF0038), X(0xFFFF0034), X(0xFFFF0030),
	X(0xFFFF002C), X(0xFFFF0029), X(0xFFFF0025), X(0xFFFF0022), X(0xFFFF001F), X(0xFFFF001C),
	X(0xFFFF0019), X(0xFFFF0016), X(0xFFFF0014), X(0xFFFF0011), X(0xFFFF000F), X(0xFFFF000D),
	X(0xFFFF000B), X(0xFFFF0009), X(0xFFFF0008), X(0xFFFF0006), X(0xFFFF0005), X(0xFFFF0004),
	X(0xFFFF0003), X(0xFFFF0002), X(0xFFFF0001), X(0xFFFF0001), X(0xFFFF0000), X(0xFFFF0000),
	X(0xFFFF0000), X(0xFFFF0000), X(0xFFFF0000), X(0xFFFF0001), X(0xFFFF0001), X(0xFFFF0002),
	X(0xFFFF0003), X(0xFFFF0004), X(0xFFFF0005), X(0xFFFF0006), X(0xFFFF0008), X(0xFFFF0009),
	X(0xFFFF000B), X(0xFFFF000D), X(0xFFFF000F), X(0xFFFF0011), X(0xFFFF0014), X(0xFFFF0016),
	X(0xFFFF0019), X(0xFFFF001C), X(0xFFFF001F), X(0xFFFF0022), X(0xFFFF0025), X(0xFFFF0029),
	X(0xFFFF002C), X(0xFFFF0030), X(0xFFFF0034), X(0xFFFF0038), X(0xFFFF003C), X(0xFFFF0041),
	X(0xFFFF0045), X(0xFFFF004A), X(0xFFFF004F), X(0xFFFF0054), X(0xFFFF0059), X(0xFFFF005E),
	X(0xFFFF0064), X(0xFFFF006A), X(0xFFFF006F), X(0xFFFF0075), X(0xFFFF007B), X(0xFFFF0082),
	X(0xFFFF0088), X(0xFFFF008F), X(0xFFFF0095), X(0xFFFF009C), X(0xFFFF00A3), X(0xFFFF00AA),
	X(0xFFFF00B2), X(0xFFFF00B9), X(0xFFFF00C1), X(0xFFFF00C8), X(0xFFFF00D0), X(0xFFFF00D8),
	X(0xFFFF00E1), X(0xFFFF00E9), X(0xFFFF00F2), X(0xFFFF00FA), X(0xFFFF0103), X(0xFFFF010C),
	X(0xFFFF0115), X(0xFFFF011F), X(0xFFFF0128), X(0xFFFF0132), X(0xFFFF013C), X(0xFFFF0146),
	X(0xFFFF0150), X(0xFFFF015A), X(0xFFFF0164), X(0xFFFF016F), X(0xFFFF0179), X(0xFFFF0184),
	X(0xFFFF018F), X(0xFFFF019A), X(0xFFFF01A6), X(0xFFFF01B1), X(0xFFFF01BD), X(0xFFFF01C9),
	X(0xFFFF01D5), X(0xFFFF01E1), X(0xFFFF01ED), X(0xFFFF01F9), X(0xFFFF0206), X(0xFFFF0212),
	X(0xFFFF021F), X(0xFFFF022C), X(0xFFFF0239), X(0xFFFF0247), X(0xFFFF0254), X(0xFFFF0262),
	X(0xFFFF0270), X(0xFFFF027D), X(0xFFFF028C), X(0xFFFF029A), X(0xFFFF02A8), X(0xFFFF02B7),
	X(0xFFFF02C5), X(0xFFFF02D4), X(0xFFFF02E3), X(0xFFFF02F2), X(0xFFFF0302), X(0xFFFF0311),
	X(0xFFFF0321), X(0xFFFF0330), X(0xFFFF0340), X(0xFFFF0350), X(0xFFFF0360), X(0xFFFF0371),
	X(0xFFFF0381), X(0xFFFF0392), X(0xFFFF03A3), X(0xFFFF03B4), X(0xFFFF03C5), X(0xFFFF03D6),
	X(0xFFFF03E8), X(0xFFFF03F9), X(0xFFFF040B), X(0xFFFF041D), X(0xFFFF042F), X(0xFFFF0441),
	X(0xFFFF0453), X(0xFFFF0466), X(0xFFFF0478), X(0xFFFF048B), X(0xFFFF049E), X(0xFFFF04B1),
	X(0xFFFF04C4), X(0xFFFF04D8), X(0xFFFF04EB), X(0xFFFF04FF), X(0xFFFF0513), X(0xFFFF0527),
	X(0xFFFF053B), X(0xFFFF054F), X(0xFFFF0564), X(0xFFFF0578), X(0xFFFF058D), X(0xFFFF05A2),
	X(0xFFFF05B7), X(0xFFFF05CC), X(0xFFFF05E1), X(0xFFFF05F7), X(0xFFFF060D), X(0xFFFF0622),
	X(0xFFFF0638), X(0xFFFF064E), X(0xFFFF0665), X(0xFFFF067B), X(0xFFFF0692), X(0xFFFF06A8),
	X(0xFFFF06BF), X(0xFFFF06D6), X(0xFFFF06ED), X(0xFFFF0705), X(0xFFFF071C), X(0xFFFF0734),
	X(0xFFFF074C), X(0xFFFF0763), X(0xFFFF077B), X(0xFFFF0794), X(0xFFFF07AC), X(0xFFFF07C5),
	X(0xFFFF07DD), X(0xFFFF07F6), X(0xFFFF080F), X(0xFFFF0828), X(0xFFFF0841), X(0xFFFF085B),
	X(0xFFFF0874), X(0xFFFF088E), X(0xFFFF08A8), X(0xFFFF08C2), X(0xFFFF08DC), X(0xFFFF08F6),
	X(0xFFFF0911), X(0xFFFF092B), X(0xFFFF0946), X(0xFFFF0961), X(0xFFFF097C), X(0xFFFF0997),
	X(0xFFFF09B2), X(0xFFFF09CE), X(0xFFFF09EA), X(0xFFFF0A05), X(0xFFFF0A21), X(0xFFFF0A3D),
	X(0xFFFF0A5A), X(0xFFFF0A76), X(0xFFFF0A92), X(0xFFFF0AAF), X(0xFFFF0ACC), X(0xFFFF0AE9),
	X(0xFFFF0B06), X(0xFFFF0B23), X(0xFFFF0B41), X(0xFFFF0B5E), X(0xFFFF0B7C), X(0xFFFF0B9A),
	X(0xFFFF0BB8), X(0xFFFF0BD6), X(0xFFFF0BF4), X(0xFFFF0C13), X(0xFFFF0C31), X(0xFFFF0C50),
	X(0xFFFF0C6F), X(0xFFFF0C8E), X(0xFFFF0CAD), X(0xFFFF0CCC), X(0xFFFF0CEC), X(0xFFFF0D0B),
	X(0xFFFF0D2B), X(0xFFFF0D4B), X(0xFFFF0D6B), X(0xFFFF0D8B), X(0xFFFF0DAC), X(0xFFFF0DCC),
	X(0xFFFF0DED), X(0xFFFF0E0D), X(0xFFFF0E2E), X(0xFFFF0E4F), X(0xFFFF0E71), X(0xFFFF0E92),
	X(0xFFFF0EB4), X(0xFFFF0ED5), X(0xFFFF0EF7), X(0xFFFF0F19), X(0xFFFF0F3B), X(0xFFFF0F5D),
	X(0xFFFF0F80), X(0xFFFF0FA2), X(0xFFFF0FC5), X(0xFFFF0FE8), X(0xFFFF100B), X(0xFFFF102E),
	X(0xFFFF1051), X(0xFFFF1074), X(0xFFFF1098), X(0xFFFF10BB), X(0xFFFF10DF), X(0xFFFF1103),
	X(0xFFFF1127), X(0xFFFF114C), X(0xFFFF1170), X(0xFFFF1195), X(0xFFFF11B9), X(0xFFFF11DE),
	X(0xFFFF1203), X(0xFFFF1228), X(0xFFFF124D), X(0xFFFF1273), X(0xFFFF1298), X(0xFFFF12BE),
	X(0xFFFF12E4), X(0xFFFF130A), X(0xFFFF1330), X(0xFFFF1356), X(0xFFFF137D), X(0xFFFF13A3),
	X(0xFFFF13CA), X(0xFFFF13F1), X(0xFFFF1418), X(0xFFFF143F), X(0xFFFF1466), X(0xFFFF148D),
	X(0xFFFF14B5), X(0xFFFF14DD), X(0xFFFF1504), X(0xFFFF152C), X(0xFFFF1555), X(0xFFFF157D),
	X(0xFFFF15A5), X(0xFFFF15CE), X(0xFFFF15F6), X(0xFFFF161F), X(0xFFFF1648), X(0xFFFF1671),
	X(0xFFFF169A), X(0xFFFF16C4), X(0xFFFF16ED), X(0xFFFF1717), X(0xFFFF1741), X(0xFFFF176B),
	X(0xFFFF1795), X(0xFFFF17BF), X(0xFFFF17E9), X(0xFFFF1814), X(0xFFFF183E), X(0xFFFF1869),
	X(0xFFFF1894), X(0xFFFF18BF), X(0xFFFF18EA), X(0xFFFF1916), X(0xFFFF1941), X(0xFFFF196D),
	X(0xFFFF1999), X(0xFFFF19C4), X(0xFFFF19F0), X(0xFFFF1A1D), X(0xFFFF1A49), X(0xFFFF1A75),
	X(0xFFFF1AA2), X(0xFFFF1ACF), X(0xFFFF1AFC), X(0xFFFF1B29), X(0xFFFF1B56), X(0xFFFF1B83),
	X(0xFFFF1BB0), X(0xFFFF1BDE), X(0xFFFF1C0C), X(0xFFFF1C39), X(0xFFFF1C67), X(0xFFFF1C95),
	X(0xFFFF1CC4), X(0xFFFF1CF2), X(0xFFFF1D21), X(0xFFFF1D4F), X(0xFFFF1D7E), X(0xFFFF1DAD),
	X(0xFFFF1DDC), X(0xFFFF1E0B), X(0xFFFF1E3A), X(0xFFFF1E6A), X(0xFFFF1E99), X(0xFFFF1EC9),
	X(0xFFFF1EF9), X(0xFFFF1F29), X(0xFFFF1F59), X(0xFFFF1F89), X(0xFFFF1FBA), X(0xFFFF1FEA),
	X(0xFFFF201B), X(0xFFFF204C), X(0xFFFF207D), X(0xFFFF20AE), X(0xFFFF20DF), X(0xFFFF2110),
	X(0xFFFF2142), X(0xFFFF2174), X(0xFFFF21A5), X(0xFFFF21D7), X(0xFFFF2209), X(0xFFFF223B),
	X(0xFFFF226E), X(0xFFFF22A0), X(0xFFFF22D3), X(0xFFFF2305), X(0xFFFF2338), X(0xFFFF236B),
	X(0xFFFF239E), X(0xFFFF23D1), X(0xFFFF2405), X(0xFFFF2438), X(0xFFFF246C), X(0xFFFF24A0),
	X(0xFFFF24D4), X(0xFFFF2508), X(0xFFFF253C), X(0xFFFF2570), X(0xFFFF25A4), X(0xFFFF25D9),
	X(0xFFFF260E), X(0xFFFF2642), X(0xFFFF2677), X(0xFFFF26AC), X(0xFFFF26E2), X(0xFFFF2717),
	X(0xFFFF274C), X(0xFFFF2782), X(0xFFFF27B8), X(0xFFFF27EE), X(0xFFFF2824), X(0xFFFF285A),
	X(0xFFFF2890), X(0xFFFF28C6), X(0xFFFF28FD), X(0xFFFF2933), X(0xFFFF296A), X(0xFFFF29A1),
	X(0xFFFF29D8), X(0xFFFF2A0F), X(0xFFFF2A46), X(0xFFFF2A7E), X(0xFFFF2AB5), X(0xFFFF2AED),
	X(0xFFFF2B25), X(0xFFFF2B5D), X(0xFFFF2B95), X(0xFFFF2BCD), X(0xFFFF2C05), X(0xFFFF2C3E),
	X(0xFFFF2C76), X(0xFFFF2CAF), X(0xFFFF2CE8), X(0xFFFF2D21), X(0xFFFF2D5A), X(0xFFFF2D93),
	X(0xFFFF2DCC), X(0xFFFF2E06), X(0xFFFF2E3F), X(0xFFFF2E79), X(0xFFFF2EB3), X(0xFFFF2EED),
	X(0xFFFF2F27), X(0xFFFF2F61), X(0xFFFF2F9B), X(0xFFFF2FD6), X(0xFFFF3010), X(0xFFFF304B),
	X(0xFFFF3086), X(0xFFFF30C1), X(0xFFFF30FC), X(0xFFFF3137), X(0xFFFF3172), X(0xFFFF31AE),
	X(0xFFFF31E9), X(0xFFFF3225), X(0xFFFF3261), X(0xFFFF329D), X(0xFFFF32D9), X(0xFFFF3315),
	X(0xFFFF3352), X(0xFFFF338E), X(0xFFFF33CB), X(0xFFFF3407), X(0xFFFF3444), X(0xFFFF3481),
	X(0xFFFF34BE), X(0xFFFF34FB), X(0xFFFF3539), X(0xFFFF3576), X(0xFFFF35B3), X(0xFFFF35F1),
	X(0xFFFF362F), X(0xFFFF366D), X(0xFFFF36AB), X(0xFFFF36E9), X(0xFFFF3727), X(0xFFFF3766),
	X(0xFFFF37A4), X(0xFFFF37E3), X(0xFFFF3822), X(0xFFFF3860), X(0xFFFF389F), X(0xFFFF38DF),
	X(0xFFFF391E), X(0xFFFF395D), X(0xFFFF399D), X(0xFFFF39DC), X(0xFFFF3A1C), X(0xFFFF3A5C),
	X(0xFFFF3A9C), X(0xFFFF3ADC), X(0xFFFF3B1C), X(0xFFFF3B5C), X(0xFFFF3B9D), X(0xFFFF3BDD),
	X(0xFFFF3C1E), X(0xFFFF3C5F), X(0xFFFF3CA0), X(0xFFFF3CE1), X(0xFFFF3D22), X(0xFFFF3D63),
	X(0xFFFF3DA4), X(0xFFFF3DE6), X(0xFFFF3E28), X(0xFFFF3E69), X(0xFFFF3EAB), X(0xFFFF3EED),
	X(0xFFFF3F2F), X(0xFFFF3F71), X(0xFFFF3FB4), X(0xFFFF3FF6), X(0xFFFF4039), X(0xFFFF407B),
	X(0xFFFF40BE), X(0xFFFF4101), X(0xFFFF4144), X(0xFFFF4187), X(0xFFFF41CA), X(0xFFFF420E),
	X(0xFFFF4251), X(0xFFFF4295), X(0xFFFF42D8), X(0xFFFF431C), X(0xFFFF4360), X(0xFFFF43A4),
	X(0xFFFF43E8), X(0xFFFF442C), X(0xFFFF4471), X(0xFFFF44B5), X(0xFFFF44FA), X(0xFFFF453F),
	X(0xFFFF4583), X(0xFFFF45C8), X(0xFFFF460D), X(0xFFFF4652), X(0xFFFF4698), X(0xFFFF46DD),
	X(0xFFFF4723), X(0xFFFF4768), X(0xFFFF47AE), X(0xFFFF47F4), X(0xFFFF483A), X(0xFFFF4880),
	X(0xFFFF48C6), X(0xFFFF490C), X(0xFFFF4953), X(0xFFFF4999), X(0xFFFF49E0), X(0xFFFF4A26),
	X(0xFFFF4A6D), X(0xFFFF4AB4), X(0xFFFF4AFB), X(0xFFFF4B42), X(0xFFFF4B89), X(0xFFFF4BD1),
	X(0xFFFF4C18), X(0xFFFF4C60), X(0xFFFF4CA8), X(0xFFFF4CEF), X(0xFFFF4D37), X(0xFFFF4D7F),
	X(0xFFFF4DC7), X(0xFFFF4E10), X(0xFFFF4E58), X(0xFFFF4EA0), X(0xFFFF4EE9), X(0xFFFF4F32),
	X(0xFFFF4F7A), X(0xFFFF4FC3), X(0xFFFF500C), X(0xFFFF5055), X(0xFFFF509E), X(0xFFFF50E8),
	X(0xFFFF5131), X(0xFFFF517B), X(0xFFFF51C4), X(0xFFFF520E), X(0xFFFF5258), X(0xFFFF52A2),
	X(0xFFFF52EC), X(0xFFFF5336), X(0xFFFF5380), X(0xFFFF53CA), X(0xFFFF5415), X(0xFFFF545F),
	X(0xFFFF54AA), X(0xFFFF54F5), X(0xFFFF5540), X(0xFFFF558A), X(0xFFFF55D6), X(0xFFFF5621),
	X(0xFFFF566C), X(0xFFFF56B7), X(0xFFFF5703), X(0xFFFF574E), X(0xFFFF579A), X(0xFFFF57E6),
	X(0xFFFF5832), X(0xFFFF587E), X(0xFFFF58CA), X(0xFFFF5916), X(0xFFFF5962), X(0xFFFF59AE),
	X(0xFFFF59FB), X(0xFFFF5A48), X(0xFFFF5A94), X(0xFFFF5AE1), X(0xFFFF5B2E), X(0xFFFF5B7B),
	X(0xFFFF5BC8), X(0xFFFF5C15), X(0xFFFF5C62), X(0xFFFF5CB0), X(0xFFFF5CFD), X(0xFFFF5D4B),
	X(0xFFFF5D98), X(0xFFFF5DE6), X(0xFFFF5E34), X(0xFFFF5E82), X(0xFFFF5ED0), X(0xFFFF5F1E),
	X(0xFFFF5F6C), X(0xFFFF5FBB), X(0xFFFF6009), X(0xFFFF6058), X(0xFFFF60A6), X(0xFFFF60F5),
	X(0xFFFF6144), X(0xFFFF6193), X(0xFFFF61E2), X(0xFFFF6231), X(0xFFFF6280), X(0xFFFF62CF),
	X(0xFFFF631F), X(0xFFFF636E), X(0xFFFF63BE), X(0xFFFF640E), X(0xFFFF645D), X(0xFFFF64AD),
	X(0xFFFF64FD), X(0xFFFF654D), X(0xFFFF659D), X(0xFFFF65EE), X(0xFFFF663E), X(0xFFFF668E),
	X(0xFFFF66DF), X(0xFFFF6730), X(0xFFFF6780), X(0xFFFF67D1), X(0xFFFF6822), X(0xFFFF6873),
	X(0xFFFF68C4), X(0xFFFF6915), X(0xFFFF6966), X(0xFFFF69B8), X(0xFFFF6A09), X(0xFFFF6A5B),
	X(0xFFFF6AAC), X(0xFFFF6AFE), X(0xFFFF6B50), X(0xFFFF6BA2), X(0xFFFF6BF4), X(0xFFFF6C46),
	X(0xFFFF6C98), X(0xFFFF6CEA), X(0xFFFF6D3C), X(0xFFFF6D8F), X(0xFFFF6DE1), X(0xFFFF6E34),
	X(0xFFFF6E87), X(0xFFFF6ED9), X(0xFFFF6F2C), X(0xFFFF6F7F), X(0xFFFF6FD2), X(0xFFFF7025),
	X(0xFFFF7078), X(0xFFFF70CC), X(0xFFFF711F), X(0xFFFF7173), X(0xFFFF71C6), X(0xFFFF721A),
	X(0xFFFF726E), X(0xFFFF72C1), X(0xFFFF7315), X(0xFFFF7369), X(0xFFFF73BD), X(0xFFFF7411),
	X(0xFFFF7466), X(0xFFFF74BA), X(0xFFFF750E), X(0xFFFF7563), X(0xFFFF75B7), X(0xFFFF760C),
	X(0xFFFF7661), X(0xFFFF76B6), X(0xFFFF770A), X(0xFFFF775F), X(0xFFFF77B4), X(0xFFFF780A),
	X(0xFFFF785F), X(0xFFFF78B4), X(0xFFFF7909), X(0xFFFF795F), X(0xFFFF79B4), X(0xFFFF7A0A),
	X(0xFFFF7A60), X(0xFFFF7AB6), X(0xFFFF7B0B), X(0xFFFF7B61), X(0xFFFF7BB7), X(0xFFFF7C0E),
	X(0xFFFF7C64), X(0xFFFF7CBA), X(0xFFFF7D10), X(0xFFFF7D67), X(0xFFFF7DBD), X(0xFFFF7E14),
	X(0xFFFF7E6B), X(0xFFFF7EC1), X(0xFFFF7F18), X(0xFFFF7F6F), X(0xFFFF7FC6), X(0xFFFF801D),
	X(0xFFFF8074), X(0xFFFF80CB), X(0xFFFF8123), X(0xFFFF817A), X(0xFFFF81D1), X(0xFFFF8229),
	X(0xFFFF8281), X(0xFFFF82D8), X(0xFFFF8330), X(0xFFFF8388), X(0xFFFF83E0), X(0xFFFF8438),
	X(0xFFFF8490), X(0xFFFF84E8), X(0xFFFF8540), X(0xFFFF8598), X(0xFFFF85F0), X(0xFFFF8649),
	X(0xFFFF86A1), X(0xFFFF86FA), X(0xFFFF8753), X(0xFFFF87AB), X(0xFFFF8804), X(0xFFFF885D),
	X(0xFFFF88B6), X(0xFFFF890F), X(0xFFFF8968), X(0xFFFF89C1), X(0xFFFF8A1A), X(0xFFFF8A73),
	X(0xFFFF8ACD), X(0xFFFF8B26), X(0xFFFF8B80), X(0xFFFF8BD9), X(0xFFFF8C33), X(0xFFFF8C8D),
	X(0xFFFF8CE6), X(0xFFFF8D40), X(0xFFFF8D9A), X(0xFFFF8DF4), X(0xFFFF8E4E), X(0xFFFF8EA8),
	X(0xFFFF8F02), X(0xFFFF8F5D), X(0xFFFF8FB7), X(0xFFFF9011), X(0xFFFF906C), X(0xFFFF90C6),
	X(0xFFFF9121), X(0xFFFF917B), X(0xFFFF91D6), X(0xFFFF9231), X(0xFFFF928C), X(0xFFFF92E7),
	X(0xFFFF9342), X(0xFFFF939D), X(0xFFFF93F8), X(0xFFFF9453), X(0xFFFF94AE), X(0xFFFF950A),
	X(0xFFFF9565), X(0xFFFF95C0), X(0xFFFF961C), X(0xFFFF9677), X(0xFFFF96D3), X(0xFFFF972F),
	X(0xFFFF978A), X(0xFFFF97E6), X(0xFFFF9842), X(0xFFFF989E), X(0xFFFF98FA), X(0xFFFF9956),
	X(0xFFFF99B2), X(0xFFFF9A0E), X(0xFFFF9A6B), X(0xFFFF9AC7), X(0xFFFF9B23), X(0xFFFF9B80),
	X(0xFFFF9BDC), X(0xFFFF9C39), X(0xFFFF9C95), X(0xFFFF9CF2), X(0xFFFF9D4F), X(0xFFFF9DAC),
	X(0xFFFF9E08), X(0xFFFF9E65), X(0xFFFF9EC2), X(0xFFFF9F1F), X(0xFFFF9F7C), X(0xFFFF9FDA),
	X(0xFFFFA037), X(0xFFFFA094), X(0xFFFFA0F1), X(0xFFFFA14F), X(0xFFFFA1AC), X(0xFFFFA20A),
	X(0xFFFFA267), X(0xFFFFA2C5), X(0xFFFFA322), X(0xFFFFA380), X(0xFFFFA3DE), X(0xFFFFA43C),
	X(0xFFFFA49A), X(0xFFFFA4F8), X(0xFFFFA556), X(0xFFFFA5B4), X(0xFFFFA612), X(0xFFFFA670),
	X(0xFFFFA6CE), X(0xFFFFA72C), X(0xFFFFA78B), X(0xFFFFA7E9), X(0xFFFFA847), X(0xFFFFA8A6),
	X(0xFFFFA904), X(0xFFFFA963), X(0xFFFFA9C2), X(0xFFFFAA20), X(0xFFFFAA7F), X(0xFFFFAADE),
	X(0xFFFFAB3D), X(0xFFFFAB9C), X(0xFFFFABFA), X(0xFFFFAC59), X(0xFFFFACB8), X(0xFFFFAD18),
	X(0xFFFFAD77), X(0xFFFFADD6), X(0xFFFFAE35), X(0xFFFFAE94), X(0xFFFFAEF4), X(0xFFFFAF53),
	X(0xFFFFAFB3), X(0xFFFFB012), X(0xFFFFB072), X(0xFFFFB0D1), X(0xFFFFB131), X(0xFFFFB190),
	X(0xFFFFB1F0), X(0xFFFFB250), X(0xFFFFB2B0), X(0xFFFFB310), X(0xFFFFB370), X(0xFFFFB3CF),
	X(0xFFFFB42F), X(0xFFFFB490), X(0xFFFFB4F0), X(0xFFFFB550), X(0xFFFFB5B0), X(0xFFFFB610),
	X(0xFFFFB670), X(0xFFFFB6D1), X(0xFFFFB731), X(0xFFFFB791), X(0xFFFFB7F2), X(0xFFFFB852),
	X(0xFFFFB8B3), X(0xFFFFB914), X(0xFFFFB974), X(0xFFFFB9D5), X(0xFFFFBA35), X(0xFFFFBA96),
	X(0xFFFFBAF7), X(0xFFFFBB58), X(0xFFFFBBB9), X(0xFFFFBC1A), X(0xFFFFBC7B), X(0xFFFFBCDC),
	X(0xFFFFBD3D), X(0xFFFFBD9E), X(0xFFFFBDFF), X(0xFFFFBE60), X(0xFFFFBEC1), X(0xFFFFBF22),
	X(0xFFFFBF84), X(0xFFFFBFE5), X(0xFFFFC046), X(0xFFFFC0A8), X(0xFFFFC109), X(0xFFFFC16B),
	X(0xFFFFC1CC), X(0xFFFFC22E), X(0xFFFFC28F), X(0xFFFFC2F1), X(0xFFFFC352), X(0xFFFFC3B4),
	X(0xFFFFC416), X(0xFFFFC478), X(0xFFFFC4D9), X(0xFFFFC53B), X(0xFFFFC59D), X(0xFFFFC5FF),
	X(0xFFFFC661), X(0xFFFFC6C3), X(0xFFFFC725), X(0xFFFFC787), X(0xFFFFC7E9), X(0xFFFFC84B),
	X(0xFFFFC8AD), X(0xFFFFC90F), X(0xFFFFC972), X(0xFFFFC9D4), X(0xFFFFCA36), X(0xFFFFCA98),
	X(0xFFFFCAFB), X(0xFFFFCB5D), X(0xFFFFCBC0), X(0xFFFFCC22), X(0xFFFFCC84), X(0xFFFFCCE7),
	X(0xFFFFCD49), X(0xFFFFCDAC), X(0xFFFFCE0F), X(0xFFFFCE71), X(0xFFFFCED4), X(0xFFFFCF37),
	X(0xFFFFCF99), X(0xFFFFCFFC), X(0xFFFFD05F), X(0xFFFFD0C1), X(0xFFFFD124), X(0xFFFFD187),
	X(0xFFFFD1EA), X(0xFFFFD24D), X(0xFFFFD2B0), X(0xFFFFD313), X(0xFFFFD376), X(0xFFFFD3D9),
	X(0xFFFFD43C), X(0xFFFFD49F), X(0xFFFFD502), X(0xFFFFD565), X(0xFFFFD5C8), X(0xFFFFD62B),
	X(0xFFFFD68F), X(0xFFFFD6F2), X(0xFFFFD755), X(0xFFFFD7B8), X(0xFFFFD81C), X(0xFFFFD87F),
	X(0xFFFFD8E2), X(0xFFFFD946), X(0xFFFFD9A9), X(0xFFFFDA0C), X(0xFFFFDA70), X(0xFFFFDAD3),
	X(0xFFFFDB37), X(0xFFFFDB9A), X(0xFFFFDBFE), X(0xFFFFDC61), X(0xFFFFDCC5), X(0xFFFFDD29),
	X(0xFFFFDD8C), X(0xFFFFDDF0), X(0xFFFFDE53), X(0xFFFFDEB7), X(0xFFFFDF1B), X(0xFFFFDF7E),
	X(0xFFFFDFE2), X(0xFFFFE046), X(0xFFFFE0AA), X(0xFFFFE10D), X(0xFFFFE171), X(0xFFFFE1D5),
	X(0xFFFFE239), X(0xFFFFE29D), X(0xFFFFE301), X(0xFFFFE365), X(0xFFFFE3C8), X(0xFFFFE42C),
	X(0xFFFFE490), X(0xFFFFE4F4), X(0xFFFFE558), X(0xFFFFE5BC), X(0xFFFFE620), X(0xFFFFE684),
	X(0xFFFFE6E8), X(0xFFFFE74C), X(0xFFFFE7B0), X(0xFFFFE815), X(0xFFFFE879), X(0xFFFFE8DD),
	X(0xFFFFE941), X(0xFFFFE9A5), X(0xFFFFEA09), X(0xFFFFEA6D), X(0xFFFFEAD2), X(0xFFFFEB36),
	X(0xFFFFEB9A), X(0xFFFFEBFE), X(0xFFFFEC62), X(0xFFFFECC7), X(0xFFFFED2B), X(0xFFFFED8F),
	X(0xFFFFEDF3), X(0xFFFFEE58), X(0xFFFFEEBC), X(0xFFFFEF20), X(0xFFFFEF85), X(0xFFFFEFE9),
	X(0xFFFFF04D), X(0xFFFFF0B2), X(0xFFFFF116), X(0xFFFFF17A), X(0xFFFFF1DF), X(0xFFFFF243),
	X(0xFFFFF2A8), X(0xFFFFF30C), X(0xFFFFF370), X(0xFFFFF3D5), X(0xFFFFF439), X(0xFFFFF49E),
	X(0xFFFFF502), X(0xFFFFF566), X(0xFFFFF5CB), X(0xFFFFF62F), X(0xFFFFF694), X(0xFFFFF6F8),
	X(0xFFFFF75D), X(0xFFFFF7C1), X(0xFFFFF826), X(0xFFFFF88A), X(0xFFFFF8EF), X(0xFFFFF953),
	X(0xFFFFF9B8), X(0xFFFFFA1C), X(0xFFFFFA81), X(0xFFFFFAE5), X(0xFFFFFB4A), X(0xFFFFFBAE),
	X(0xFFFFFC13), X(0xFFFFFC77), X(0xFFFFFCDC), X(0xFFFFFD40), X(0xFFFFFDA5), X(0xFFFFFE09),
	X(0xFFFFFE6E), X(0xFFFFFED2), X(0xFFFFFF37), X(0xFFFFFF9B)
};
#undef X

#endif // NVQM_SKIP_FIXED_POINT
