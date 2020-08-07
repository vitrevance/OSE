#ifndef OSE_RANDOM_H
#define OSE_RANDOM_H

#include <OSE/Core.h>
#include <OSE/Math/Vecmath.h>

namespace OSE {
	namespace Random {

		int integer() {
			return rand();
		}

		int integer(int low, int high) {
			return rand() % high + low;
		}

		t_float decimal() {
			return (t_float)rand() / RAND_MAX;
		}

		t_float decimal(int decimalPoints) {
			t_float div = pow(10, decimalPoints);
			return (t_float)integer(0, div + 1) / div;
		}

		t_float signedDecimal() {
			return decimal() * 2 - 1;
		}

		vec2 vector2() {
			vec2 result;
			for (unsigned int i = 0; i < 2; i++) {
				result[i] = signedDecimal() * integer();
			}
			return result;
		}

		vec3 vector3() {
			vec3 result;
			for (unsigned int i = 0; i < 3; i++) {
				result[i] = signedDecimal() * integer();
			}
			return result;
		}

		vec4 vector4() {
			vec4 result;
			for (unsigned int i = 0; i < 4; i++) {
				result[i] = signedDecimal() * integer();
			}
			return result;
		}

		vec2 normal2() {
			return (vector2()).normalized();
		}

		vec3 normal3() {
			return (vector3()).normalized();
		}

		vec4 normal4() {
			return (vector4()).normalized();
		}

		vec2 vector2(t_float maxLength) {
			return normal2() * decimal() * maxLength;
		}

		vec3 vector3(t_float maxLength) {
			return normal3() * decimal() * maxLength;
		}

		vec4 vector4(t_float maxLength) {
			return normal4() * decimal() * maxLength;
		}
	}
}

#endif