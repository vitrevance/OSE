#ifndef OSE_MATRIX_H
#define OSE_MATRIX_H

#include <OSE/Core.h>

namespace OSE {
	template<unsigned int ROWS, unsigned int COLS>
	class mat {
	public:
		mat() {
			for (unsigned int x = 0; x < ROWS; x++) {
				for (unsigned int y = 0; y < COLS; y++) {
					this->m_values[x][y] = 0;
				}
			}
		}

		mat(t_float values[ROWS][COLS]) {
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					this->m_values[row][col] = values[row][col];
				}
			}
		}

		mat(t_float values[ROWS*COLS]) {
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					this->m_values[row][col] = values[col+row*COLS];
				}
			}
		}

		mat(const std::initializer_list<t_float>& values) {
			std::initializer_list<t_float>::iterator it = values.begin();
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					this->m_values[row][col] = *it;
					it++;
				}
			}
		}

		template<unsigned int OTHER_ROWS, unsigned int OTHER_COLS>
		mat(mat<OTHER_ROWS, OTHER_COLS> m) {
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					if (row < OTHER_ROWS && col < OTHER_COLS) {
						this->m_values[row][col] = m[row][col];
					}
					else if (row == col) {
						this->m_values[row][col] = 1;
					}
					else {
						this->m_values[row][col] = 0;
					}
				}
			}
		}

		template<unsigned int OTHER_COLS>
		mat<ROWS, OTHER_COLS> operator* (mat<COLS, OTHER_COLS> m) {
			mat<ROWS, OTHER_COLS> result;
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < OTHER_COLS; col++) {
					for (unsigned int this_col = 0; this_col < COLS; this_col++) {
						result[row][col] += this->m_values[row][this_col] * m[this_col][col];
					}
				}
			}
			return result;
		}

		mat<COLS, ROWS> transposed() {
			mat<COLS, ROWS> result;
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					result[col][row] == this->m_values[row][col];
				}
			}
			return result;
		}

		mat<ROWS, COLS> operator+ (mat<ROWS, COLS> m) {
			mat<ROWS, COLS> result;
			for (unsigned int row = 0; row < ROWS; row++) {
				for (unsigned int col = 0; col < COLS; col++) {
					result[row][col] = this->m_values[row][col] + m[row][col];
				}
			}
			return result;
		}

		t_float* operator[] (unsigned int row) {
			return this->m_values[row];
		}

	private:
		t_float m_values[ROWS][COLS];
	};
}

#endif