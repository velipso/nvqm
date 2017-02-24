// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

#include "nvqm.h"

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
	out->v[0] = a->v[0];
	out->v[1] = a->v[1];
	out->v[2] = a->v[2];
	out->v[3] = a->v[3];
	out->v[4] = a->v[4];
	out->v[5] = a->v[5];
	out->v[6] = a->v[6];
	out->v[7] = a->v[7];
	out->v[8] = a->v[8];
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

mat4 *mat4_identity(mat4 *out){
	out->v[ 0] = 1.0f; out->v[ 1] = 0.0f; out->v[ 2] = 0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] = 0.0f; out->v[ 5] = 1.0f; out->v[ 6] = 0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] = 0.0f; out->v[ 9] = 0.0f; out->v[10] = 1.0f; out->v[11] = 0.0f;
	out->v[12] = 0.0f; out->v[13] = 0.0f; out->v[14] = 0.0f; out->v[15] = 1.0f;
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

mat4 *mat4_scaling(mat4 *out, vec3 a){
	out->v[ 0] = a.v[0]; out->v[ 1] =   0.0f; out->v[ 2] =   0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] =   0.0f; out->v[ 5] = a.v[1]; out->v[ 6] =   0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] =   0.0f; out->v[ 9] =   0.0f; out->v[10] = a.v[2]; out->v[11] = 0.0f;
	out->v[12] =   0.0f; out->v[13] =   0.0f; out->v[14] =   0.0f; out->v[15] = 1.0f;
	return out;
}

mat4 *mat4_translation(mat4 *out, vec3 a){
	out->v[ 0] = 1.0f; out->v[ 1] = 0.0f; out->v[ 2] = 0.0f; out->v[ 3] = 0.0f;
	out->v[ 4] = 0.0f; out->v[ 5] = 1.0f; out->v[ 6] = 0.0f; out->v[ 7] = 0.0f;
	out->v[ 8] = 0.0f; out->v[ 9] = 0.0f; out->v[10] = 1.0f; out->v[11] = 0.0f;
	out->v[12] = a.v[0]; out->v[13] = a.v[1]; out->v[14] = a.v[2]; out->v[15] = 1;
	return out;
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

mat4 *mat4_copy(mat4 *out, mat4 *a){
	out->v[ 0] = a->v[ 0]; out->v[ 1] = a->v[ 1]; out->v[ 2] = a->v[ 2]; out->v[ 3] = a->v[ 3];
	out->v[ 4] = a->v[ 4]; out->v[ 5] = a->v[ 5]; out->v[ 6] = a->v[ 6]; out->v[ 7] = a->v[ 7];
	out->v[ 8] = a->v[ 8]; out->v[ 9] = a->v[ 9]; out->v[10] = a->v[10]; out->v[11] = a->v[11];
	out->v[12] = a->v[12]; out->v[13] = a->v[13]; out->v[14] = a->v[14]; out->v[15] = a->v[15];
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
