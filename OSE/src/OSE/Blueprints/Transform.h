#ifndef OSE_TRANSFORM_H
#define OSE_TRANSFORM_H

#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Transform {
	public:
		vecd position;
		mat4 rotation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		float yaw = 0, pitch = 0, roll = 0;

		Transform() : position(vecd()), rotation(mat4()) {}
		Transform(vecd position) : position(position) {}
		Transform(vecd position, mat4 rotation) : position(position), rotation(rotation) {}
		Transform(mat4 rotation) : rotation(rotation) {}

		vec3 getSlicePosition(unsigned int* slice) {
			return vec3({ this->position[slice[0]], this->position[slice[1]], this->position[slice[2]] });
		}

		void setRotation(float yaw, float pitch, float roll) {
			mat4 myaw({
				cos(yaw), -sin(yaw), 0, 0,
				sin(yaw), cos(yaw), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				});
			mat4 mpitch({
				cos(pitch), 0, sin(pitch), 0,
				0, 1, 0, 0,
				-sin(pitch), 0, cos(pitch), 0,
				0, 0, 0, 1
				});
			mat4 mroll({
				1, 0, 0, 0,
				0, cos(roll), -sin(roll), 0,
				0, sin(roll), cos(roll), 0,
				0, 0, 0, 1
				});
			this->rotation = myaw * mpitch * mroll;
		}

		void rotate(float yaw, float pitch, float roll) {
			this->yaw += yaw;
			this->pitch += pitch;
			this->roll += roll;
			this->setRotation(this->yaw, this->pitch, this->roll);
		}
	};
}

#endif
