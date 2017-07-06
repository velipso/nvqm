// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

// requires the nvqm.js file in the global scope

// usage: the SinkVqm() function returns an include/native library object for Sink
// example: Sink.run(..., [SinkVqm()], ...)
// inside sink:
//   include 'vqm'
//   say vec3.add {1, 2, 3}, {4, 5, 6}  # => {5, 7, 9}

// (sorry for the long lines, I wanted to keep things tabular)
function SinkVqm(){

	// type checking
	function ct(a, n, name){
		if (n === 0){
			if (typeof a !== 'number')
				throw new Error('Expecting ' + name);
		}
		else{
			if (Object.prototype.toString.call(a) !== '[object Array]' ||
				a.length !== n)
				throw new Error('Expecting ' + name);
			for (var i = 0; i < n; i++){
				if (typeof a[i] !== 'number')
					throw new Error('Expecting ' + name);
			}
		}
		return a;
	}

	function nm(a){ return ct(a,  0, 'num'   ); }
	function v2(a){ return ct(a,  2, 'vec2'  ); }
	function v3(a){ return ct(a,  3, 'vec3'  ); }
	function v4(a){ return ct(a,  4, 'vec4'  ); }
	function qt(a){ return ct(a,  4, 'quat'  ); }
	function m2(a){ return ct(a,  4, 'mat2'  ); }
	function mx(a){ return ct(a,  6, 'mat3x2'); }
	function m3(a){ return ct(a,  9, 'mat3'  ); }
	function m4(a){ return ct(a, 16, 'mat4'  ); }

	function m3u(a){
		if (typeof a === 'undefined' || a === null)
			return void 0;
		return ct(a, 9, 'mat3 or nil');
	}

	function m4u(a){
		if (typeof a === 'undefined' || a === null)
			return void 0;
		return ct(a, 16, 'mat4 or nil');
	}

	var funcs = {
		// vec2
		'vec2.add'        : function(a, b       ){ return vec2_add        (v2(a), v2(b)           ); },
		'vec2.applymat2'  : function(a, b       ){ return vec2_applymat2  (v2(a), m2(b)           ); },
		'vec2.applymat3x2': function(a, b       ){ return vec2_applymat3x2(v2(a), mx(b)           ); },
		'vec2.applymat3'  : function(a, b       ){ return vec2_applymat3  (v2(a), m3(b)           ); },
		'vec2.applymat4'  : function(a, b       ){ return vec2_applymat4  (v2(a), m4(b)           ); },
		'vec2.clamp'      : function(a, min, max){ return vec2_clamp      (v2(a), v2(min), v2(max)); },
		'vec2.dist'       : function(a, b       ){ return vec2_dist       (v2(a), v2(b)           ); },
		'vec2.dist2'      : function(a, b       ){ return vec2_dist2      (v2(a), v2(b)           ); },
		'vec2.div'        : function(a, b       ){ return vec2_div        (v2(a), v2(b)           ); },
		'vec2.dot'        : function(a, b       ){ return vec2_dot        (v2(a), v2(b)           ); },
		'vec2.inverse'    : function(a          ){ return vec2_inverse    (v2(a)                  ); },
		'vec2.len'        : function(a          ){ return vec2_len        (v2(a)                  ); },
		'vec2.len2'       : function(a          ){ return vec2_len2       (v2(a)                  ); },
		'vec2.lerp'       : function(a, b, t    ){ return vec2_lerp       (v2(a), v2(b), nm(t)    ); },
		'vec2.max'        : function(a, b       ){ return vec2_max        (v2(a), v2(b)           ); },
		'vec2.min'        : function(a, b       ){ return vec2_min        (v2(a), v2(b)           ); },
		'vec2.mul'        : function(a, b       ){ return vec2_mul        (v2(a), v2(b)           ); },
		'vec2.neg'        : function(a          ){ return vec2_neg        (v2(a)                  ); },
		'vec2.normal'     : function(a          ){ return vec2_normal     (v2(a)                  ); },
		'vec2.scale'      : function(a, s       ){ return vec2_scale      (v2(a), nm(s)           ); },
		'vec2.sub'        : function(a, b       ){ return vec2_sub        (v2(a), v2(b)           ); },

		// vec3
		'vec3.add'        : function(a, b       ){ return vec3_add        (v3(a), v3(b)           ); },
		'vec3.angle'      : function(a, b       ){ return vec3_angle      (v3(a), v3(b)           ); },
		'vec3.applymat3x2': function(a, b       ){ return vec3_applymat3x2(v3(a), mx(b)           ); },
		'vec3.applymat3'  : function(a, b       ){ return vec3_applymat3  (v3(a), m3(b)           ); },
		'vec3.applymat4'  : function(a, b       ){ return vec3_applymat4  (v3(a), m4(b)           ); },
		'vec3.applyquat'  : function(a, b       ){ return vec3_applyquat  (v3(a), qt(b)           ); },
		'vec3.clamp'      : function(a, min, max){ return vec3_clamp      (v3(a), v3(b)           ); },
		'vec3.cross'      : function(a, b       ){ return vec3_cross      (v3(a), v3(b)           ); },
		'vec3.div'        : function(a, b       ){ return vec3_div        (v3(a), v3(b)           ); },
		'vec3.dist'       : function(a, b       ){ return vec3_dist       (v3(a), v3(b)           ); },
		'vec3.dist2'      : function(a, b       ){ return vec3_dist2      (v3(a), v3(b)           ); },
		'vec3.dot'        : function(a, b       ){ return vec3_dot        (v3(a), v3(b)           ); },
		'vec3.inverse'    : function(a          ){ return vec3_inverse    (v3(a)                  ); },
		'vec3.len'        : function(a          ){ return vec3_len        (v3(a)                  ); },
		'vec3.len2'       : function(a          ){ return vec3_len2       (v3(a)                  ); },
		'vec3.lerp'       : function(a, b, t    ){ return vec3_lerp       (v3(a), v3(b), nm(t)    ); },
		'vec3.max'        : function(a, b       ){ return vec3_max        (v3(a), v3(b)           ); },
		'vec3.min'        : function(a, b       ){ return vec3_min        (v3(a), v3(b)           ); },
		'vec3.mul'        : function(a, b       ){ return vec3_mul        (v3(a), v3(b)           ); },
		'vec3.nangle'     : function(a, b       ){ return vec3_nangle     (v3(a), v3(b)           ); },
		'vec3.neg'        : function(a          ){ return vec3_neg        (v3(a)                  ); },
		'vec3.normal'     : function(a          ){ return vec3_normal     (v3(a)                  ); },
		'vec3.orthogonal' : function(a, b       ){ return vec3_orthogonal (v3(a), v3(b)           ); },
		'vec3.scale'      : function(a, s       ){ return vec3_scale      (v3(a), nm(s)           ); },
		'vec3.sub'        : function(a, b       ){ return vec3_sub        (v3(a), v3(b)           ); },

		// vec4
		'vec4.add'      : function(a, b       ){ return vec4_add      (v4(a), v4(b)           ); },
		'vec4.applymat4': function(a, b       ){ return vec4_applymat4(v4(a), m4(b)           ); },
		'vec4.applyquat': function(a, b       ){ return vec4_applyquat(v4(a), qt(b)           ); },
		'vec4.clamp'    : function(a, min, max){ return vec4_clamp    (v4(a), v4(min), v4(max)); },
		'vec4.dist'     : function(a, b       ){ return vec4_dist     (v4(a), v4(b)           ); },
		'vec4.dist2'    : function(a, b       ){ return vec4_dist2    (v4(a), v4(b)           ); },
		'vec4.div'      : function(a, b       ){ return vec4_div      (v4(a), v4(b)           ); },
		'vec4.dot'      : function(a, b       ){ return vec4_dot      (v4(a), v4(b)           ); },
		'vec4.inverse'  : function(a          ){ return vec4_inverse  (v4(a)                  ); },
		'vec4.len'      : function(a          ){ return vec4_len      (v4(a)                  ); },
		'vec4.len2'     : function(a          ){ return vec4_len2     (v4(a)                  ); },
		'vec4.lerp'     : function(a, b, t    ){ return vec4_lerp     (v4(a), v4(b), nm(t)    ); },
		'vec4.max'      : function(a, b       ){ return vec4_max      (v4(a), v4(b)           ); },
		'vec4.min'      : function(a, b       ){ return vec4_min      (v4(a), v4(b)           ); },
		'vec4.mul'      : function(a, b       ){ return vec4_mul      (v4(a), v4(b)           ); },
		'vec4.neg'      : function(a          ){ return vec4_neg      (v4(a)                  ); },
		'vec4.normal'   : function(a          ){ return vec4_normal   (v4(a)                  ); },
		'vec4.scale'    : function(a, s       ){ return vec4_scale    (v4(a), nm(s)           ); },
		'vec4.sub'      : function(a, b       ){ return vec4_sub      (v4(a), v4(b)           ); },

		// quat
		'quat.axisang'  : function(axis, ang){ return quat_axisang  (v3(axis), nm(ang)  ); },
		'quat.between'  : function(from, to ){ return quat_between  (v3(from), v3(to)   ); },
		'quat.dot'      : function(a, b     ){ return quat_dot      (qt(a), qt(b)       ); },
		'quat.euler_xyz': function(rot      ){ return quat_euler_xyz(v3(rot)            ); },
		'quat.euler_xzy': function(rot      ){ return quat_euler_xzy(v3(rot)            ); },
		'quat.euler_yxz': function(rot      ){ return quat_euler_yxz(v3(rot)            ); },
		'quat.euler_yzx': function(rot      ){ return quat_euler_yzx(v3(rot)            ); },
		'quat.euler_zxy': function(rot      ){ return quat_euler_zxy(v3(rot)            ); },
		'quat.euler_zyx': function(rot      ){ return quat_euler_zyx(v3(rot)            ); },
		'quat.identity' : quat_identity,
		'quat.invert'   : function(a        ){ return quat_invert   (qt(a)              ); },
		'quat.lerp'     : function(a, b, t  ){ return quat_lerp     (qt(a), qt(b), nm(t)); },
		'quat.mul'      : function(a, b     ){ return quat_mul      (qt(a), qt(b)       ); },
		'quat.naxisang' : function(axis, ang){ return quat_naxisang (v3(axis), nm(ang)  ); },
		'quat.nbetween' : function(from, to ){ return quat_nbetween (v3(from), v3(to)   ); },
		'quat.neg'      : function(a        ){ return quat_neg      (qt(a)              ); },
		'quat.nlerp'    : function(a, b, t  ){ return quat_nlerp    (qt(a), qt(b), nm(t)); },
		'quat.normal'   : function(a        ){ return quat_normal   (qt(a)              ); },
		'quat.slerp'    : function(a, b, t  ){ return quat_slerp    (qt(a), qt(b), nm(t)); },

		// mat2
		'mat2.add'      : function(a, b  ){ return mat2_add      (m2(a), m2(b)  ); },
		'mat2.adjoint'  : function(a     ){ return mat2_adjoint  (m2(a)         ); },
		'mat2.compmul'  : function(a, b  ){ return mat2_compmul  (m2(a), m2(b)  ); },
		'mat2.det'      : function(a     ){ return mat2_det      (m2(a)         ); },
		'mat2.identity' : mat2_identity,
		'mat2.invert'   : function(a     ){ return mat2_invert   (m2(a)         ); },
		'mat2.mul'      : function(a, b  ){ return mat2_mul      (m2(a), m2(b)  ); },
		'mat2.rotate'   : function(a, ang){ return mat2_rotate   (m2(a), nm(ang)); },
		'mat2.rotation' : function(ang   ){ return mat2_rotation (nm(ang)       ); },
		'mat2.scale'    : function(a, b  ){ return mat2_scale    (m2(a), v2(b)  ); },
		'mat2.scaling'  : function(a     ){ return mat2_scaling  (v2(a)         ); },
		'mat2.sub'      : function(a, b  ){ return mat2_sub      (m2(a), m2(b)  ); },
		'mat2.transpose': function(a     ){ return mat2_transpose(m2(a)         ); },

		// mat3x2
		'mat3x2.add'        : function(a, b  ){ return mat3x2_add        (mx(a), mx(b)  ); },
		'mat3x2.compmul'    : function(a, b  ){ return mat3x2_compmul    (mx(a), mx(b)  ); },
		'mat3x2.det'        : function(a     ){ return mat3x2_det        (mx(a)         ); },
		'mat3x2.identity'   : mat3x2_identity,
		'mat3x2.invert'     : function(a     ){ return mat3x2_invert     (mx(a)         ); },
		'mat3x2.mul'        : function(a, b  ){ return mat3x2_mul        (mx(a), mx(b)  ); },
		'mat3x2.rotate'     : function(a, ang){ return mat3x2_rotate     (mx(a), nm(ang)); },
		'mat3x2.rotation'   : function(ang   ){ return mat3x2_rotation   (nm(ang)       ); },
		'mat3x2.scale'      : function(a, b  ){ return mat3x2_scale      (mx(a), v2(b)  ); },
		'mat3x2.scaling'    : function(a     ){ return mat3x2_scaling    (v2(a)         ); },
		'mat3x2.sub'        : function(a, b  ){ return mat3x2_sub        (mx(a), mx(b)  ); },
		'mat3x2.translate'  : function(a, b  ){ return mat3x2_translate  (mx(a), v2(b)  ); },
		'mat3x2.translation': function(a     ){ return mat3x2_translation(v2(a)         ); },

		// mat3
		'mat3.add'        : function(out, a, b  ){ return mat3_add        (m3(out), m3(a), m3(b)  ); },
		'mat3.adjoint'    : function(out, a     ){ return mat3_adjoint    (m3(out), m3(a)         ); },
		'mat3.compmul'    : function(out, a, b  ){ return mat3_compmul    (m3(out), m3(a), m3(b)  ); },
		'mat3.copy'       : function(out, a     ){ return mat3_copy       (m3(out), m3(a)         ); },
		'mat3.det'        : function(a          ){ return mat3_det        (m3(a)                  ); },
		'mat3.identity'   : function(out        ){ return mat3_identity   (m3u(out)               ); },
		'mat3.invert'     : function(out, a     ){ return mat3_invert     (m3(out), m3(a)         ); },
		'mat3.mul'        : function(out, a, b  ){ return mat3_mul        (m3(out), m3(a), m3(b)  ); },
		'mat3.quat'       : function(out, a     ){ return mat3_quat       (m3(out), qt(a)         ); },
		'mat3.rotate'     : function(out, a, ang){ return mat3_rotate     (m3(out), m3(a), nm(ang)); },
		'mat3.rotation'   : function(out, ang   ){ return mat3_rotation   (m3(out), nm(ang)       ); },
		'mat3.scale'      : function(out, a, b  ){ return mat3_scale      (m3(out), m3(a), v2(b)  ); },
		'mat3.scaling'    : function(out, a     ){ return mat3_scaling    (m3(out), v2(a)         ); },
		'mat3.sub'        : function(out, a, b  ){ return mat3_sub        (m3(out), m3(a), m3(b)  ); },
		'mat3.translate'  : function(out, a, b  ){ return mat3_translate  (m3(out), m3(a), v2(b)  ); },
		'mat3.translation': function(out, a     ){ return mat3_translation(m3(out), v2(a)         ); },
		'mat3.transpose'  : function(out, a     ){ return mat3_transpose  (m3(out), m3(a)         ); },

		// mat4
		'mat4.add':            function(out, a, b                    ){ return mat4_add           (m4(out), m4(a), m4(b)                                ); },
		'mat4.adjoint':        function(out, a                       ){ return mat4_adjoint       (m4(out), m4(a)                                       ); },
		'mat4.compmul':        function(out, a, b                    ){ return mat4_compmul       (m4(out), m4(a), m4(b)                                ); },
		'mat4.copy':           function(out, a                       ){ return mat4_copy          (m4(out), m4(a)                                       ); },
		'mat4.det':            function(a                            ){ return mat4_det           (m4(a)                                                ); },
		'mat4.frustum':        function(out, L, R, B, T, N, F        ){ return mat4_frustum       (m4(out), nm(L), nm(R), nm(B), nm(T), nm(N), nm(F)    ); },
		'mat4.identity':       function(out                          ){ return mat4_identity      (m4u(out)                                             ); },
		'mat4.invert':         function(out, a                       ){ return mat4_invert        (m4(out), m4(a)                                       ); },
		'mat4.lookat':         function(out, eye, position, up       ){ return mat4_lookat        (m4(out), v3(eye), v3(position), v3(up)               ); },
		'mat4.mul':            function(out, a, b                    ){ return mat4_mul           (m4(out), m4(a), m4(b)                                ); },
		'mat4.orthogonal':     function(out, W, H, N, F              ){ return mat4_orthogonal    (m4(out), nm(W), nm(H), nm(N), nm(F)                  ); },
		'mat4.perspective':    function(out, fov, width, height, N, F){ return mat4_perspective   (m4(out), nm(fov), nm(width), nm(height), nm(N), nm(F)); },
		'mat4.quat':           function(out, a                       ){ return mat4_quat          (m4(out), qt(a)                                       ); },
		'mat4.rotate':         function(out, a, axis, ang            ){ return mat4_rotate        (m4(out), m4(a), v3(axis), nm(ang)                    ); },
		'mat4.rotation':       function(out, axis, ang               ){ return mat4_rotation      (m4(out), v3(axis), nm(ang)                           ); },
		'mat4.rottrans':       function(out, a, b                    ){ return mat4_rottrans      (m4(out), qt(a), v3(b)                                ); },
		'mat4.rottransorigin': function(out, a, b, origin            ){ return mat4_rottransorigin(m4(out), qt(a), v3(b), v3(origin)                    ); },
		'mat4.scale':          function(out, a, b                    ){ return mat4_scale         (m4(out), m4(a), v3(b)                                ); },
		'mat4.scaling':        function(out, a                       ){ return mat4_scaling       (m4(out), v3(a)                                       ); },
		'mat4.sub':            function(out, a, b                    ){ return mat4_sub           (m4(out), m4(a), m4(b)                                ); },
		'mat4.translate':      function(out, a, b                    ){ return mat4_translate     (m4(out), m4(a), v3(b)                                ); },
		'mat4.translation':    function(out, a                       ){ return mat4_translation   (m4(out), v3(a)                                       ); },
		'mat4.transpose':      function(out, a                       ){ return mat4_transpose     (m4(out), m4(a)                                       ); }
	};

	var include = '';
	var natives = {};
	for (var k in funcs){
		var sk = 'sink.vqm.' + k;
		include += 'declare ' + k + ' "' + sk + '";';
		natives[sk] = funcs[k];
	}
	return { includes: { vqm: include }, natives: natives };
}

if (typeof module !== 'undefined' && module.exports)
	module.exports = SinkVqm; // export single function for node.js
