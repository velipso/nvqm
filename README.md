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
* JavaScript (`nvqm.js`)
  * Values stored as a flat array of numbers
  * Pass-by-value functions return new arrays, vs. pass-by-reference functions which modify and
    return the `out` parameter
  * When `require`d in node.js, functions are exported into global namespace
* [Sink](https://github.com/voidqk/sink) (`sink_vqm.js`, `sink_vqm.h`+`sink_vqm.c`)
  * Values are stored as a flat array of numbers
  * Pass-by-value functions return new arrays, vs. pass-by-reference functions which modify and
    return the `out` parameter

Functions
---------

The `num`, `vec2`, `vec3`, `vec4`, `quat`, `mat2`, and `mat3x2` functions operate using
pass-by-value semantics, while `mat3` and `mat4` use pass-by-reference semantics.

```c
const float TAU; // 2 * PI

// num (scalars)
float num_abs  (float a);
float num_acos (float a);
float num_asin (float a);
float num_atan2(float a, float b);
float num_ceil (float a);
float num_clamp(float a, float min, float max);
float num_cos  (float a);
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

// vec2
vec2  vec2_add      (vec2 a, vec2 b);
vec2  vec2_applymat2(vec2 a, mat2 b);
vec2  vec2_applymat3(vec2 a, mat3 *b);
vec2  vec2_applymat4(vec2 a, mat4 *b);
vec2  vec2_clamp    (vec2 a, vec2 min, vec2 max);
float vec2_dist     (vec2 a, vec2 b);
float vec2_dist2    (vec2 a, vec2 b); // distance squared
vec2  vec2_div      (vec2 a, vec2 b);
float vec2_dot      (vec2 a, vec2 b);
vec2  vec2_inverse  (vec2 a);
float vec2_len      (vec2 a);
float vec2_len2     (vec2 a); // length squared
vec2  vec2_lerp     (vec2 a, vec2 b, float t);
vec2  vec2_max      (vec2 a, vec2 b);
vec2  vec2_min      (vec2 a, vec2 b);
vec2  vec2_mul      (vec2 a, vec2 b);
vec2  vec2_neg      (vec2 a);
vec2  vec2_normal   (vec2 a);
vec2  vec2_scale    (vec2 a, float s);
vec2  vec2_sub      (vec2 a, vec2 b);

// vec3
vec3  vec3_add      (vec3 a, vec3 b);
float vec3_angle    (vec3 a, vec3 b);
vec3  vec3_applymat3(vec3 a, mat3 *b);
vec3  vec3_applymat4(vec3 a, mat4 *b);
vec3  vec3_applyquat(vec3 a, quat b);
vec3  vec3_clamp    (vec3 a, vec3 min, vec3 max);
vec3  vec3_cross    (vec3 a, vec3 b);
float vec3_dist     (vec3 a, vec3 b);
float vec3_dist2    (vec3 a, vec3 b);
vec3  vec3_div      (vec3 a, vec3 b);
float vec3_dot      (vec3 a, vec3 b);
vec3  vec3_inverse  (vec3 a);
float vec3_len      (vec3 a);
float vec3_len2     (vec3 a);
vec3  vec3_lerp     (vec3 a, vec3 b, float t);
vec3  vec3_max      (vec3 a, vec3 b);
vec3  vec3_min      (vec3 a, vec3 b);
vec3  vec3_mul      (vec3 a, vec3 b);
float vec3_nangle   (vec3 a, vec3 b); // a and b are normalized
vec3  vec3_neg      (vec3 a);
vec3  vec3_normal   (vec3 a);
vec3  vec3_scale    (vec3 a, float s);
vec3  vec3_sub      (vec3 a, vec3 b);

// vec4
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

// quat
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
mat2  mat2_scaling  (vec2 s);
mat2  mat2_sub      (mat2 a, mat2 b);
mat2  mat2_transpose(mat2 a);

// mat3x2
// TODO: this

// mat3
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
```
