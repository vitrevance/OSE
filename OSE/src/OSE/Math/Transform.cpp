#include <OSE/Math/Transform.h>

namespace OSE {

	Transform::Transform() {}
	Transform::Transform(vec4 position) : position(position) {}
	Transform::Transform(vec4 position, mat4 rotation) : position(position), rotation(rotation) {}
	Transform::Transform(mat4 rotation) : rotation(rotation) {}

	void Transform::setRotation(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw) {
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

	void Transform::rotate(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw) {
		this->yaw += yaw;
		this->pitch += pitch;
		this->roll += roll;
		this->xw += xw;
		this->yw += yw;
		this->zw += zw;
		this->setRotation(this->yaw, this->pitch, this->roll, this->xw, this->yw, this->zw);
	}

	void Transform::scale(t_float x, t_float y, t_float z, t_float w) {
		this->rotation[0][0] *= x;
		this->rotation[1][1] *= y;
		this->rotation[2][2] *= z;
		this->rotation[3][3] *= w;
	}
}