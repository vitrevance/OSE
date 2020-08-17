#ifndef OSE_TRANSFORM_H
#define OSE_TRANSFORM_H

#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Transform {
	public:
		vec4 position;
		mat4 rotation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		float yaw = 0, pitch = 0, roll = 0, xw = 0, yw = 0, zw = 0;

		Transform() {}
		Transform(vec4 position) : position(position) {}
		Transform(vec4 position, mat4 rotation) : position(position), rotation(rotation) {}
		Transform(mat4 rotation) : rotation(rotation) {}

		void setRotation(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw) {
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
			mat4 mxw({
				cos(xw), 0, 0, -sin(xw),
				0, 1, 0, 0,
				0, 0, 1, 0,
				sin(xw), 0, 0, cos(xw)
				});
			mat4 myw({
				1, 0, 0, 0,
				0, cos(yw), 0, sin(yw),
				0, 0, 1, 0,
				0, -sin(yw), 0, cos(yw)
				});
			mat4 mzw({
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, cos(zw), -sin(zw),
				0, 0, sin(zw), cos(zw)
				});
			this->rotation = myaw * mpitch * mroll * mxw * myw * mzw;
		}

		void rotate(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw) {
			this->yaw += yaw;
			this->pitch += pitch;
			this->roll += roll;
			this->xw += xw;
			this->yw += yw;
			this->zw += zw;
			this->setRotation(this->yaw, this->pitch, this->roll, this->xw, this->yw, this->zw);
		}
	};
}

#endif
