#ifndef OSE_VECTOR_H
#define OSE_VECTOR_H

#include <OSE/Core.h>

namespace OSE {
	template<unsigned int SIZE>
	class vec {
	public:
		vec() {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] = 0;
			}
		}

		vec(t_float value) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] = value;
			}
		}

		vec(t_float values[SIZE]) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] = values[i];
			}
		}

		vec(const std::initializer_list<t_float>& values) {
			std::initializer_list<t_float>::iterator it = values.begin();
			for (unsigned int i = 0; i < SIZE; i++) {
				if (i < values.size()) {
					this->m_coords[i] = *it;
					it++;
				}
				else {
					this->m_coords[i] = 0;
				}
			}
		}

		template<unsigned int OTHER_SIZE>
		vec(const vec<OTHER_SIZE>& v) {
			for (unsigned int i = 0; i < SIZE; i++) {
				if (i >= OTHER_SIZE) {
					this->m_coords[i] = 0;
				}
				else {
					this->m_coords[i] = v[i];
				}
			}
		}

		inline t_float& x() { return this->m_coords[0]; }
		inline t_float& y() { return SIZE > 1 ? this->m_coords[1] : 0; }
		inline t_float& z() { return SIZE > 2 ? this->m_coords[2] : 0; }
		inline t_float& w() { return SIZE > 3 ? this->m_coords[3] : 0; }
		
		t_float& operator[] (unsigned int index) { return this->m_coords[index]; }

		vec<SIZE> operator+ (vec<SIZE>& a) {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result.m_coords[i] = this->m_coords[i] + a.m_coords[i];
			}
			return result;
		}

		vec<SIZE>& operator+= (const vec<SIZE>& a) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] += a.m_coords[i];
			}
			return *this;
		}

		vec<SIZE> operator- (vec<SIZE>& a) {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result.m_coords[i] = this->m_coords[i] - a.m_coords[i];
			}
			return result;
		}

		vec<SIZE> operator- () {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result.m_coords[i] = -this->m_coords[i];
			}
			return result;
		}

		vec<SIZE> operator* (t_float a) {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result.m_coords[i] = this->m_coords[i] * a;
			}
			return result;
		}

		vec<SIZE> operator/ (t_float a) {
			vec<SIZE> result;
			for (unsigned int i = 0; i < SIZE; i++) {
				result.m_coords[i] = this->m_coords[i] / a;
			}
			return result;
		}

		vec<SIZE>& operator*= (t_float a) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] *= a;
			}
			return *this;
		}

		vec<SIZE>& operator/= (t_float a) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] /= a;
			}
			return *this;
		}

		t_float length() {
			t_float sqareSum = 0;
			for (unsigned int i = 0; i < SIZE; i++) {
				sqareSum += this->m_coords[i] * this->m_coords[i];
			}
			return sqrt(sqareSum);
		}

		t_float dot(vec<SIZE>& a) {
			t_float dotSum = 0;
			for (unsigned int i = 0; i < SIZE; i++) {
				dotSum += this->m_coords[i] * a.m_coords[i];
			}
			return dotSum;
		}

		vec<SIZE>& normalize() {
			if (length() <= 0) {
				return *this;
			}
			(*this) /= this->length();
			return *this;
		}

		vec<SIZE> normalized() {
			vec<SIZE> result = *this;
			if (length() <= 0) {
				return result;
			}
			result /= result.length();
			return result;
		}

	private:
		t_float m_coords[SIZE];
	};
}

#endif