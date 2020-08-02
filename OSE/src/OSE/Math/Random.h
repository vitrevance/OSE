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

		template<unsigned int SIZE>
		vec<SIZE> vector() {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result[i] = signedDecimal() * integer();
			}
			return result;
		}

		template<unsigned int SIZE>
		vec<SIZE> normal() {
			return (vector<SIZE>()).normalized();
		}

		template<unsigned int SIZE>
		vec<SIZE> vector(t_float maxLength) {
			return normal<SIZE>() * decimal() * maxLength;
		}
	}
}

#endif