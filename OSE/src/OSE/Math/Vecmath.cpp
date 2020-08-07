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

	vec3 cross(vec3 a, vec3 b) {
		return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
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
}