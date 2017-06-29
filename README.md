nvqm
====

Numeric, Vector, Quaternion, and Matrix functions, consistent across multiple programming languages.

The number of times I've had to lookup a simple vector operation is too damn high.  Here is my
attempt to pick a single reasonable API to consistently apply across any programming language I
happen to be using.

Implementations
---------------

* C99 (`nvqm.h`+`nvqm.c`)
  * Values stored as structured arrays to facilitate pass-by-value
  * Pass-by-value functions are `static inline`
  * Q16.16 fixed-point implementation (see notes below)
* JavaScript (`nvqm.js`)
  * Values stored as a flat array of numbers
  * Pass-by-value functions return new arrays, vs. pass-by-reference functions which modify and
    return the `out` parameter
  * When `require`d in node.js, functions are exported into global namespace
* [Sink](https://github.com/voidqk/sink) (`sink_vqm.js`, `sink_vqm.h`+`sink_vqm.c`)
  * Values are stored as a flat array of numbers
  * Pass-by-value functions return new arrays, vs. pass-by-reference functions which modify and
    return the `out` parameter
  * `num.*` functions aren't included due to them being native to sink itself

Fixed-Point
-----------

The C files also contains a signed Q16.16 fixed-point implementation.  It is deterministic and never
fails -- but will give incorrect results if numbers overflow.  Angles are not stored in radians, but
instead as 12 bit number (0 to 4095).

The implementation is okay for most functions, but is pretty terrible for `xint_pow`, and I suspect
slow for `xint_sqrt`.  I would love help, if anyone knows better.


Functions
---------

The `num`, `vec2`, `vec3`, `vec4`, `quat`, `mat2`, and `mat3x2` functions operate using
pass-by-value semantics, while `mat3` and `mat4` use pass-by-reference semantics.

```c
const float  TAU; // 2 * PI
const double TAUd;

// num (scalars)
float num_abs  (float a);
float num_acos (float a);
float num_asin (float a);
float num_atan2(float a, float b);
float num_ceil (float a);
float num_clamp(float a, float min, float max);
float num_cos  (float a);
float num_exp  (float a);
float num_floor(float a);
float num_lerp (float a, float b, float t);
float num_log  (float a);
float num_max  (float a, float b);
float num_min  (float a, float b);
float num_mod  (float a, float b);
float num_pow  (float a, float b);
float num_round(float a);
float num_sin  (float a);
float num_sqrt (float a);
float num_tan  (float a);

// vec2  [x, y]
vec2  vec2_add        (vec2 a, vec2 b);
vec2  vec2_applymat2  (vec2 a, mat2 b);
vec2  vec2_applymat3x2(vec2 a, mat3x2 b);
vec2  vec2_applymat3  (vec2 a, mat3 *b);
vec2  vec2_applymat4  (vec2 a, mat4 *b);
vec2  vec2_clamp      (vec2 a, vec2 min, vec2 max);
float vec2_dist       (vec2 a, vec2 b);
float vec2_dist2      (vec2 a, vec2 b); // distance squared
vec2  vec2_div        (vec2 a, vec2 b);
float vec2_dot        (vec2 a, vec2 b);
vec2  vec2_inverse    (vec2 a);
float vec2_len        (vec2 a);
float vec2_len2       (vec2 a); // length squared
vec2  vec2_lerp       (vec2 a, vec2 b, float t);
vec2  vec2_max        (vec2 a, vec2 b);
vec2  vec2_min        (vec2 a, vec2 b);
vec2  vec2_mul        (vec2 a, vec2 b);
vec2  vec2_neg        (vec2 a);
vec2  vec2_normal     (vec2 a);
vec2  vec2_scale      (vec2 a, float s);
vec2  vec2_sub        (vec2 a, vec2 b);

// vec3  [x, y, z]
vec3  vec3_add        (vec3 a, vec3 b);
float vec3_angle      (vec3 a, vec3 b);
vec3  vec3_applymat3x2(vec3 a, mat3x2 b);
vec3  vec3_applymat3  (vec3 a, mat3 *b);
vec3  vec3_applymat4  (vec3 a, mat4 *b);
vec3  vec3_applyquat  (vec3 a, quat b);
vec3  vec3_clamp      (vec3 a, vec3 min, vec3 max);
vec3  vec3_cross      (vec3 a, vec3 b);
float vec3_dist       (vec3 a, vec3 b);
float vec3_dist2      (vec3 a, vec3 b);
vec3  vec3_div        (vec3 a, vec3 b);
float vec3_dot        (vec3 a, vec3 b);
vec3  vec3_inverse    (vec3 a);
float vec3_len        (vec3 a);
float vec3_len2       (vec3 a);
vec3  vec3_lerp       (vec3 a, vec3 b, float t);
vec3  vec3_max        (vec3 a, vec3 b);
vec3  vec3_min        (vec3 a, vec3 b);
vec3  vec3_mul        (vec3 a, vec3 b);
float vec3_nangle     (vec3 a, vec3 b); // a and b are normalized
vec3  vec3_neg        (vec3 a);
vec3  vec3_normal     (vec3 a);
vec3  vec3_scale      (vec3 a, float s);
vec3  vec3_sub        (vec3 a, vec3 b);

// vec4  [x, y, z, w]
vec4  vec4_add      (vec4 a, vec4 b);
vec4  vec4_applymat4(vec4 a, mat4 *b);
vec4  vec4_applyquat(vec4 a, quat b);
vec4  vec4_clamp    (vec4 a, vec4 min, vec4 max);
vec4  vec4_div      (vec4 a, vec4 b);
float vec4_dist     (vec4 a, vec4 b);
float vec4_dist2    (vec4 a, vec4 b);
float vec4_dot      (vec4 a, vec4 b);
vec4  vec4_inverse  (vec4 a);
float vec4_len      (vec4 a);
float vec4_len2     (vec4 a);
vec4  vec4_lerp     (vec4 a, vec4 b, float t);
vec4  vec4_max      (vec4 a, vec4 b);
vec4  vec4_min      (vec4 a, vec4 b);
vec4  vec4_mul      (vec4 a, vec4 b);
vec4  vec4_neg      (vec4 a);
vec4  vec4_normal   (vec4 a);
vec4  vec4_scale    (vec4 a, float s);
vec4  vec4_sub      (vec4 a, vec4 b);

// quat  [x, y, z, w]
quat  quat_axisang  (vec3 axis, float ang);
quat  quat_between  (vec3 from, vec3 to);
float quat_dot      (quat a, quat b);
quat  quat_euler_xyz(vec3 rot);
quat  quat_euler_xzy(vec3 rot);
quat  quat_euler_yxz(vec3 rot);
quat  quat_euler_yzx(vec3 rot);
quat  quat_euler_zxy(vec3 rot);
quat  quat_euler_zyx(vec3 rot);
quat  quat_identity ();
quat  quat_invert   (quat a);
quat  quat_lerp     (quat a, quat b, float t);
quat  quat_mul      (quat a, quat b);
quat  quat_naxisang (vec3 axis, float ang); // axis is normalized
quat  quat_nbetween (vec3 from, vec3 to); // from/to are normalized
quat  quat_neg      (quat a);
quat  quat_nlerp    (quat a, quat b, float t);
quat  quat_normal   (quat a);
quat  quat_slerp    (quat a, quat b, float t);

// mat2
// [a, b, c, d] = | a c |
//                | b d |
mat2  mat2_add      (mat2 a, mat2 b);
mat2  mat2_adjoint  (mat2 a);
mat2  mat2_compmul  (mat2 a, mat2 b);
float mat2_det      (mat2 a);
mat2  mat2_identity ();
mat2  mat2_invert   (mat2 a);
mat2  mat2_mul      (mat2 a, mat2 b);
mat2  mat2_rotate   (mat2 a, float ang);
mat2  mat2_rotation (float ang);
mat2  mat2_scale    (mat2 a, vec2 b);
mat2  mat2_scaling  (vec2 a);
mat2  mat2_sub      (mat2 a, mat2 b);
mat2  mat2_transpose(mat2 a);

// mat3x2
//                      | a c e |
// [a, b, c, d, e, f] = | b d f |
//                      | 0 0 1 |
mat3x2 mat3x2_add        (mat3x2 a, mat3x2 b);
mat3x2 mat3x2_compmul    (mat3x2 a, mat3x2 b);
float  mat3x2_det        (mat3x2 a);
mat3x2 mat3x2_identity   ();
mat3x2 mat3x2_invert     (mat3x2 a);
mat3x2 mat3x2_mul        (mat3x2 a, mat3x2 b);
mat3x2 mat3x2_rotate     (mat3x2 a, float ang);
mat3x2 mat3x2_rotation   (float ang);
mat3x2 mat3x2_scale      (mat3x2 a, vec2 b);
mat3x2 mat3x2_scaling    (vec2 a);
mat3x2 mat3x2_sub        (mat3x2 a, mat3x2 b);
mat3x2 mat3x2_translate  (mat3x2 a, vec2 b);
mat3x2 mat3x2_translation(vec2 a);

// mat3
//                               | a d g |
// [a, b, c, d, e, f, g, h, i] = | b e h |
//                               | c f i |
mat3 *mat3_add        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_adjoint    (mat3 *out, mat3 *a);
mat3 *mat3_compmul    (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_copy       (mat3 *out, mat3 *a);
float mat3_det        (mat3 *a);
mat3 *mat3_identity   (mat3 *out);
mat3 *mat3_invert     (mat3 *out, mat3 *a);
mat3 *mat3_mul        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_quat       (mat3 *out, quat a);
mat3 *mat3_rotate     (mat3 *out, mat3 *a, float ang);
mat3 *mat3_rotation   (mat3 *out, float ang);
mat3 *mat3_scale      (mat3 *out, mat3 *a, vec2 b);
mat3 *mat3_scaling    (mat3 *out, vec2 a);
mat3 *mat3_sub        (mat3 *out, mat3 *a, mat3 *b);
mat3 *mat3_translate  (mat3 *out, mat3 *a, vec2 b);
mat3 *mat3_translation(mat3 *out, vec2 a);
mat3 *mat3_transpose  (mat3 *out, mat3 *a);

// mat4
//                                                    | a e i m |
// [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p] = | b f j n |
//                                                    | c g k o |
//                                                    | d h l p |
mat4 *mat4_add           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_adjoint       (mat4 *out, mat4 *a);
mat4 *mat4_compmul       (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_copy          (mat4 *out, mat4 *a);
float mat4_det           (mat4 *a);
mat4 *mat4_frustum       (mat4 *out, float L, float R, float B, float T, float N, float F);
mat4 *mat4_identity      (mat4 *out);
mat4 *mat4_invert        (mat4 *out, mat4 *a);
mat4 *mat4_lookat        (mat4 *out, vec3 eye, vec3 position, vec3 up);
mat4 *mat4_mul           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_orthogonal    (mat4 *out, float W, float H, float N, float F);
mat4 *mat4_perspective   (mat4 *out, float fov, float width, float height, float N, float F);
mat4 *mat4_quat          (mat4 *out, quat a);
mat4 *mat4_rotate        (mat4 *out, mat4 *a, vec3 axis, float ang);
mat4 *mat4_rotation      (mat4 *out, vec3 axis, float ang);
mat4 *mat4_rottrans      (mat4 *out, quat a, vec3 b);
mat4 *mat4_rottransorigin(mat4 *out, quat a, vec3 b, vec3 origin);
mat4 *mat4_scale         (mat4 *out, mat4 *a, vec3 b);
mat4 *mat4_scaling       (mat4 *out, vec3 a);
mat4 *mat4_sub           (mat4 *out, mat4 *a, mat4 *b);
mat4 *mat4_translate     (mat4 *out, mat4 *a, vec3 b);
mat4 *mat4_translation   (mat4 *out, vec3 a);
mat4 *mat4_transpose     (mat4 *out, mat4 *a);

//
// fixed-point 16.16 (only in C implementation)
//
typedef int32_t xint; // represents the signed Q16.16 fixed-point type
typedef int32_t xang; // represents a 12-bit angle type
#define XINT1    65536  /* the value 1 */
#define XINT(v)  ((xint)((v) * XINT1)) /* convert constant to xint */
#define XANG0    0x0000 /*  0 degrees */
#define XANG45   0x0200 /* 45 degrees */
#define XANG90   0x0400 /* ...etc     */
#define XANG135  0x0600
#define XANG180  0x0800
#define XANG225  0x0A00
#define XANG270  0x0C00
#define XANG315  0x0E00
#define XANG360  0x1000 /* can be thought of as TAU to some extent */

int    xint_toint     (xint a);
xint   xint_fromint   (int a);
float  xint_tofloat   (xint a);
xint   xint_fromfloat (float a);
double xint_todouble  (xint a);
xint   xint_fromdouble(double a);

xang   xang_wrap      (xang a); // wrap `a` between 0-4095
float  xang_tofloat   (xang a);
xang   xang_fromfloat (float ang);
double xang_todouble  (xang a);
xang   xang_fromdouble(double ang);

xint xint_add(xint a, xint b);
xint xint_sub(xint a, xint b);
xint xint_mul(xint a, xint b);
xint xint_div(xint a, xint b);

xint xint_abs  (xint a);
xang xint_acos (xint a);
xang xint_asin (xint a);
xang xint_atan2(xint a, xint b);
xint xint_ceil (xint a);
xint xint_clamp(xint a, xint min, xint max);
xint xint_cos  (xang a);
xint xint_exp  (xint a);
xint xint_floor(xint a);
xint xint_lerp (xint a, xint b, xint t);
xint xint_log  (xint a);
xint xint_max  (xint a, xint b);
xint xint_min  (xint a, xint b);
xint xint_mod  (xint a, xint b);
xint xint_pow  (xint a, xint b);
xint xint_round(xint a);
xint xint_sin  (xang a);
xint xint_sqrt (xint a);
xint xint_tan  (xang a);

// xvec2  fixed-point version of vec2
vec2  xvec2_tovec2     (xvec2 a);
xvec2 xvec2_fromvec2   (vec2 a);
xvec2 xvec2_add        (xvec2 a, xvec2 b);
xvec2 xvec2_applymat2  (xvec2 a, xmat2 b);
xvec2 xvec2_applymat3x2(xvec2 a, xmat3x2 b);
xvec2 xvec2_applymat3  (xvec2 a, xmat3 *b);
xvec2 xvec2_applymat4  (xvec2 a, xmat4 *b);
xvec2 xvec2_clamp      (xvec2 a, xvec2 min, xvec2 max);
xint  xvec2_dist       (xvec2 a, xvec2 b);
xint  xvec2_dist2      (xvec2 a, xvec2 b);
xvec2 xvec2_div        (xvec2 a, xvec2 b);
xint  xvec2_dot        (xvec2 a, xvec2 b);
xvec2 xvec2_inverse    (xvec2 a);
xint  xvec2_len        (xvec2 a);
xint  xvec2_len2       (xvec2 a);
xvec2 xvec2_lerp       (xvec2 a, xvec2 b, xint t);
xvec2 xvec2_max        (xvec2 a, xvec2 b);
xvec2 xvec2_min        (xvec2 a, xvec2 b);
xvec2 xvec2_mul        (xvec2 a, xvec2 b);
xvec2 xvec2_neg        (xvec2 a);
xvec2 xvec2_normal     (xvec2 a);
xvec2 xvec2_scale      (xvec2 a, xint s);
xvec2 xvec2_sub        (xvec2 a, xvec2 b);

// xvec3  fixed-point version of vec3
vec3  xvec3_tovec3     (xvec3 a);
xvec3 xvec3_fromvec3   (vec3 a);
xvec3 xvec3_add        (xvec3 a, xvec3 b);
xint  xvec3_angle      (xvec3 a, xvec3 b);
xvec3 xvec3_applymat3x2(xvec3 a, xmat3x2 b);
xvec3 xvec3_applymat3  (xvec3 a, xmat3 *b);
xvec3 xvec3_applymat4  (xvec3 a, xmat4 *b);
xvec3 xvec3_applyquat  (xvec3 a, xquat b);
xvec3 xvec3_clamp      (xvec3 a, xvec3 min, xvec3 max);
xvec3 xvec3_cross      (xvec3 a, xvec3 b);
xint  xvec3_dist       (xvec3 a, xvec3 b);
xint  xvec3_dist2      (xvec3 a, xvec3 b);
xvec3 xvec3_div        (xvec3 a, xvec3 b);
xint  xvec3_dot        (xvec3 a, xvec3 b);
xvec3 xvec3_inverse    (xvec3 a);
xint  xvec3_len        (xvec3 a);
xint  xvec3_len2       (xvec3 a);
xvec3 xvec3_lerp       (xvec3 a, xvec3 b, xint t);
xvec3 xvec3_max        (xvec3 a, xvec3 b);
xvec3 xvec3_min        (xvec3 a, xvec3 b);
xvec3 xvec3_mul        (xvec3 a, xvec3 b);
xint  xvec3_nangle     (xvec3 a, xvec3 b); // a and b are normalized
xvec3 xvec3_neg        (xvec3 a);
xvec3 xvec3_normal     (xvec3 a);
xvec3 xvec3_scale      (xvec3 a, xint s);
xvec3 xvec3_sub        (xvec3 a, xvec3 b);

// xvec4  fixed-point version of vec4
vec4  xvec4_tovec4   (xvec4 a);
xvec4 xvec4_fromvec4 (vec4 a);
xvec4 xvec4_add      (xvec4 a, xvec4 b);
xvec4 xvec4_applymat4(xvec4 a, xmat4 *b);
xvec4 xvec4_applyquat(xvec4 a, xquat b);
xvec4 xvec4_clamp    (xvec4 a, xvec4 min, xvec4 max);
xint  xvec4_dist     (xvec4 a, xvec4 b);
xint  xvec4_dist2    (xvec4 a, xvec4 b);
xvec4 xvec4_div      (xvec4 a, xvec4 b);
xint  xvec4_dot      (xvec4 a, xvec4 b);
xvec4 xvec4_inverse  (xvec4 a);
xint  xvec4_len      (xvec4 a);
xint  xvec4_len2     (xvec4 a);
xvec4 xvec4_lerp     (xvec4 a, xvec4 b, xint t);
xvec4 xvec4_max      (xvec4 a, xvec4 b);
xvec4 xvec4_min      (xvec4 a, xvec4 b);
xvec4 xvec4_mul      (xvec4 a, xvec4 b);
xvec4 xvec4_neg      (xvec4 a);
xvec4 xvec4_normal   (xvec4 a);
xvec4 xvec4_scale    (xvec4 a, xint s);
xvec4 xvec4_sub      (xvec4 a, xvec4 b);

// xquat  fixed-point version of quat
quat  xquat_toquat   (xquat a);
xquat xquat_fromquat (quat a);
xquat xquat_axisang  (xvec3 axis, xint ang);
xquat xquat_between  (xvec3 from, xvec3 to);
xint  xquat_dot      (xquat a, xquat b);
xquat xquat_euler_xyz(xvec3 rot);
xquat xquat_euler_xzy(xvec3 rot);
xquat xquat_euler_yxz(xvec3 rot);
xquat xquat_euler_yzx(xvec3 rot);
xquat xquat_euler_zxy(xvec3 rot);
xquat xquat_euler_zyx(xvec3 rot);
xquat xquat_identity ();
xquat xquat_invert   (xquat a);
xquat xquat_lerp     (xquat a, xquat b, xint t);
xquat xquat_mul      (xquat a, xquat b);
xquat xquat_naxisang (xvec3 axis, xint ang);
xquat xquat_nbetween (xvec3 from, xvec3 to);
xquat xquat_neg      (xquat a);
xquat xquat_nlerp    (xquat a, xquat b, xint t);
xquat xquat_normal   (xquat a);
xquat xquat_slerp    (xquat a, xquat b, xint t);
```
