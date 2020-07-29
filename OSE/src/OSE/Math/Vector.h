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

		vec(unsigned int values[SIZE]) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->m_coords[i] = values[i];
			}
		}

		template<unsigned int OTHER_SIZE>
		vec(vec<OTHER_SIZE>& v) {
			for (unsigned int i = 0; i < SIZE; i++) {
				if (i >= OTHER_SIZE) {
					this->m_coords[i] = 0;
				}
				else {
					this->m_coords[i] = v.m_coords[i];
				}
			}
		}

		t_float& operator[](unsigned int index) { return this->m_coords[index]; }
		inline t_float& x() { return this->m_coords[0]; }
		inline t_float& y() { return SIZE > 1 ? this->m_coords[1] : 0; }
		inline t_float& z() { return SIZE > 2 ? this->m_coords[2] : 0; }
		inline t_float& w() { return SIZE > 3 ? this->m_coords[3] : 0; }

	private:
		t_float m_coords[SIZE];
	};
}

#endif