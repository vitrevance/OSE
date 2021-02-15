#include <OSE/Math/Transform.h>

namespace OSE {

	Transform::Transform() {
		this->scale = vec4(1);
	}

	Transform::Transform(vec4 position) {
		this->scale = vec4(1);
		this->position = position;
	}

	mat4 Transform::toMatrix() {
		mat4 result;


		vec4 x = this->rotation * vec4(1, 0, 0, 0);
		vec4 y = this->rotation * vec4(0, 1, 0, 0);
		vec4 z = this->rotation * vec4(0, 0, 1, 0);
		vec4 w = this->rotation * vec4(0, 0, 0, 1);

		for (int i = 0; i < 4; i++) {
			result[0][i] = x[i];
			result[1][i] = y[i];
			result[2][i] = z[i];
			result[3][i] = w[i];
		}

		result[0][0] *= this->scale.x;
		result[1][1] *= this->scale.y;
		result[2][2] *= this->scale.z;
		result[3][3] *= this->scale.w;

		return result;
	}

	mat4 Transform::toMatrixTransposed() {
		mat4 result;


		vec4 x = this->rotation * vec4(1, 0, 0, 0);
		vec4 y = this->rotation * vec4(0, 1, 0, 0);
		vec4 z = this->rotation * vec4(0, 0, 1, 0);
		vec4 w = this->rotation * vec4(0, 0, 0, 1);

		for (int i = 0; i < 4; i++) {
			result[i][0] = x[i];
			result[i][1] = y[i];
			result[i][2] = z[i];
			result[i][3] = w[i];
		}

		result[0][0] *= this->scale.x;
		result[1][1] *= this->scale.y;
		result[2][2] *= this->scale.z;
		result[3][3] *= this->scale.w;

		return result;
	}
}