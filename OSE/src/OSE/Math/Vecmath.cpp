#include <OSE/Math/Vecmath.h>

namespace OSE {

	vec2 operator* (vec2 v, mat<2, 2> m) {
		vec2 result;
		for (unsigned int col = 0; col < 2; col++) {
			for (unsigned int row = 0; row < 2; row++) {
				result[col] += v[row] * m[row][col];
			}
		}
		return result;
	}

	vec3 operator* (vec3 v, mat<3, 3> m) {
		vec3 result;
		for (unsigned int col = 0; col < 3; col++) {
			for (unsigned int row = 0; row < 3; row++) {
				result[col] += v[row] * m[row][col];
			}
		}
		return result;
	}

	vec4 operator* (vec4 v, mat<4, 4> m) {
		vec4 result;
		for (unsigned int col = 0; col < 4; col++) {
			for (unsigned int row = 0; row < 4; row++) {
				result[col] += v[row] * m[row][col];
			}
		}
		return result;
	}

	vec2 operator* (mat<2, 2> m, vec2 v) {
		vec2 result;
		for (unsigned int row = 0; row < 2; row++) {
			for (unsigned int col = 0; col < 2; col++) {
				result[row] += v[col] * m[row][col];
			}
		}
		return result;
	}

	vec3 operator* (mat<3, 3> m, vec3 v) {
		vec3 result;
		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int col = 0; col < 3; col++) {
				result[row] += v[col] * m[row][col];
			}
		}
		return result;
	}

	vec4 operator* (mat<4, 4> m, vec4 v) {
		vec4 result;
		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int col = 0; col < 4; col++) {
				result[row] += v[col] * m[row][col];
			}
		}
		return result;
	}

	vec3 operator* (mat<3, 4> m, vec4 v) {
		vec3 result;
		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int col = 0; col < 4; col++) {
				result[row] += v[col] * m[row][col];
			}
		}
		return result;
	}

	vec2 operator* (t_float a, const vec2& b) {
		return b * a;
	}

	vec3 operator* (t_float a, const vec3& b) {
		return b * a;
	}

	vec4 operator* (t_float a, const vec4& b) {
		return b * a;
	}

	vec3 cross(vec3 a, vec3 b) {
		return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	t_float dot(const vec2& a, const vec2& b) {
		return a.x * b.x + a.y + b.y;
	}

	t_float dot(const vec3& a, const vec3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	t_float dot(const vec4& a, const vec4& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	mat<4, 4> lookAt(vec3 from, vec3 at) {
		vec3 zaxis = (at - from).normalized();
		vec3 xaxis = (cross(vec3({ 0, 1, 0 }), zaxis));
		vec3 yaxis = cross(zaxis, xaxis);
		return mat<4, 4>({ xaxis.x, yaxis.y, zaxis.z, 0,
					xaxis.y, yaxis.y, zaxis.y, 0,
					xaxis.z, yaxis.z, zaxis.z, 0,
					0, 0, 0, 1 });
	}

	t_float toRadians(t_float degrees) {
		return degrees / 180.0 * CONST_PI;
	}

	Bivector4 operator^ (const vec4& a, const vec4& b) {
		Bivector4 result(a.x * b.y - a.y * b.x, a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x,
			a.x * b.w - a.w * b.x, a.y * b.w - a.w * b.y, a.z * b.w - a.w * b.z);
		return result;
	}

	Trivector4 operator^ (const Bivector4& a, const vec4& b) {
		Trivector4 result;
		result.xyz = a.xy * b.z + a.yz * b.x - a.xz * b.y;
		result.yzw = a.yz * b.w + a.zw * b.y - a.yw * b.z;
		result.xyw = a.xy * b.w + a.yw * b.x - a.xw * b.y;
		result.xzw = a.xz * b.w + a.zw * b.x - a.xw * b.z;
		return result;
	}

	Tetravector4 operator^ (const Trivector4& a, const vec4& b) {
		Tetravector4 result;
		result.xyzw = a.xyz * b.w - a.yzw * b.x - a.xyw * b.z + a.xzw * b.y;
		return result;
	}

	Multivector4 operator* (const vec4& a, const vec4& b) {
		Multivector4 result;
		result.scalar = dot(a, b);
		result.v2 = a ^ b;
		return result;
	}

	Multivector4 operator* (const Multivector4& a, const vec4& b) {
		Multivector4 result;
		result.v1 = b * a.scalar + vec4(
			a.v2.xy * b.y + a.v2.xz * b.z + a.v2.xw * b.w,
			-a.v2.xy * b.x + a.v2.yz * b.z + a.v2.yw * b.w,
			-a.v2.yz * b.y - a.v2.xz * b.x + a.v2.zw * b.w,
			-a.v2.xw * b.x - a.v2.yw * b.y - a.v2.zw * b.z
		);
		result.v2 = a.v1 ^ b;
		result.v3 = a.v2 ^ b;
		result.v4 = a.v3 ^ b;
		return result;
	}

	Multivector4 operator* (const Multivector4& a, const Multivector4& b) {
		Multivector4 result;
		result.scalar = a.scalar * b.scalar;
		return result;
	}
	/*
	Rotor4 operator* (const vec4& a, const vec4& b) {
		Rotor4 result;
		result.real = dot(a, b);
		result.wedge = a ^ b;
		return result;
	}
	*/
	Rotor4 operator* (const Rotor4& a, const Rotor4& b) {
		return Rotor4();
	}
}