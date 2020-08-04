#ifndef OSE_VECMATH_H
#define OSE_VECMATH_H

#include <OSE/Math/Vector.h>
#include <OSE/Math/Matrix.h>

#define CONST_PI 3.141592653589793238462643383279502884L

namespace OSE {
	template<unsigned int ROWS, unsigned int COLS>
	vec<COLS> operator* (vec<ROWS> v, mat<ROWS, COLS> m) {
		vec<COLS> result;
		for (unsigned int col = 0; col < COLS; col++) {
			for (unsigned int row = 0; row < ROWS; row++) {
				result[col] += v[row] * m[row][col];
			}
		}
		return result;
	}

	template<unsigned int ROWS, unsigned int COLS>
	vec<ROWS> operator* (mat<ROWS, COLS> m, vec<COLS> v) {
		vec<ROWS> result;
		for (unsigned int row = 0; row < ROWS; row++) {
			for (unsigned int col = 0; col < COLS; col++) {
				result[row] += v[col] * m[row][col];
			}
		}
		return result;
	}

	vec<3> OSE_API cross(vec<3> a, vec<3> b);

	mat<4, 4> OSE_API lookAt(vec<3> from, vec<3> at);

	typedef vec<2> vec2;
	typedef vec<3> vec3;
	typedef vec<4> vec4;
	typedef mat<2, 2> mat2;
	typedef mat<3, 3> mat3;
	typedef mat<4, 4> mat4;

	typedef vec<I_DIMENSIONS> vecd;
	typedef mat<I_DIMENSIONS, I_DIMENSIONS> matd;
	typedef mat<I_DIMENSIONS + 1, I_DIMENSIONS + 1> matdi;
}

#endif