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

	vec3 cross(const vec3& a, const vec3& b) {
		return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	vec4 cross(const vec4& u, const vec4& v, const vec4& w) {
		t_float A = (v.x * w.y) - (v.y * w.x);
		t_float B = (v.x * w.z) - (v.z * w.x);
		t_float C = (v.x * w.w) - (v.w * w.x);
		t_float D = (v.y * w.z) - (v.z * w.y);
		t_float E = (v.y * w.w) - (v.w * w.y);
		t_float F = (v.z * w.w) - (v.w * w.z);
		// Calculate the result-vector components.
		vec4 result;
		result.x = (u.y * F) - (u.z * E) + (u.w * D);
		result.y = -(u.x * F) + (u.z * C) - (u.w * B);
		result.z = (u.x * E) - (u.y * C) + (u.w * A);
		result.w = -(u.x * D) + (u.y * B) - (u.z * A);
		return -result;
	}

	bool operator< (const vec4& a, const vec4& b) {
		return a.x == b.x ? (a.y == b.y ? (a.z == b.z ? (a.w < b.w) : a.z < b.z) : a.y < b.y) : a.x < b.x;
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

	t_float veccos(const vec2& a, const vec2& b) {
		return (a.x * b.x + a.y + b.y) / a.length() / b.length();
	}

	t_float veccos(const vec3& a, const vec3& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z) / a.length() / b.length();
	}

	t_float veccos(const vec4& a, const vec4& b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w) / a.length() / b.length();
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

	Tetravector4 operator^ (const Bivector4& a, const Bivector4& b) {
		Tetravector4 result;
		result.xyzw = a.xy * b.zw + a.yz * b.xw - a.xz * b.yw + a.xw + b.yz - a.yw * b.xz + a.zw * b.xy;
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
		result.v1 = a.scalar * b.v1 + a.v1 * b.scalar + vec4(
			 a.v2.xy * b.v1.y + a.v2.xz * b.v1.z + a.v2.xw * b.v1.w,
			-a.v2.xy * b.v1.x + a.v2.yz * b.v1.z + a.v2.yw * b.v1.w,
			-a.v2.yz * b.v1.y - a.v2.xz * b.v1.x + a.v2.zw * b.v1.w,
			-a.v2.xw * b.v1.x - a.v2.yw * b.v1.y - a.v2.zw * b.v1.z
		) + vec4(
			-b.v2.xy * a.v1.y - b.v2.xz * a.v1.z - b.v2.xw * a.v1.w,
			 b.v2.xy * a.v1.x - b.v2.yz * a.v1.z - b.v2.yw * a.v1.w,
			 b.v2.yz * a.v1.y + b.v2.xz * a.v1.x - b.v2.zw * a.v1.w,
			 b.v2.xw * a.v1.x + b.v2.yw * a.v1.y + b.v2.zw * a.v1.z
		);
		result.v2 = a.v2 * b.scalar + b.v2 * a.scalar + (a.v1 ^ b.v1) + Bivector4(
			a.v3.xyz * b.v1.z + a.v3.xyw * b.v1.w + b.v3.xyz * a.v1.z + b.v3.xyw * a.v1.w + a.v4.xyzw * b.v2.zw + b.v4.xyzw * a.v2.zw,
			a.v3.xyz * b.v1.x + a.v3.yzw * b.v1.w + b.v3.xyz * a.v1.x + b.v3.yzw * a.v1.w + a.v4.xyzw * b.v2.xw + b.v4.xyzw * a.v2.xw,
			-a.v3.xyz * b.v1.y + a.v3.xzw * b.v1.w - b.v3.xyz * a.v1.y + b.v3.xzw * a.v1.w + a.v4.xyzw * b.v2.yw + b.v4.xyzw * a.v2.yw,
			-a.v3.xyw * b.v1.y - a.v3.xzw * b.v1.z - b.v3.xyw * a.v1.y - b.v3.xzw * a.v1.z + a.v4.xyzw * b.v2.yz + b.v4.xyzw * a.v2.yz,
			a.v3.xyw * b.v1.x - a.v3.yzw * b.v1.z + b.v3.xyw * a.v1.x - b.v3.yzw * a.v1.z + a.v4.xyzw * b.v2.xz + b.v4.xyzw * a.v2.xz,
			a.v3.yzw * b.v1.y + a.v3.xzw * b.v1.x + b.v3.yzw * a.v1.y + b.v3.xzw * a.v1.x + a.v4.xyzw * b.v2.xy + b.v4.xyzw * a.v2.xy
		);
		result.v3 = a.v3 * b.scalar + b.v3 * a.scalar + Trivector4(
			//a.v2.xy * b.v1.z + b.v2.xy * a.v1.z + a.v2.yz * b.v1.x + b.v2.yz * a.v1.x + a.v2.
		);
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