#ifndef OSE_TRANSFORM_H
#define OSE_TRANSFORM_H

#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Transform {
	public:
		vec4 position;
		mat4 rotation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		float yaw = 0, pitch = 0, roll = 0, xw = 0, yw = 0, zw = 0;

		Transform();
		Transform(vec4 position);
		Transform(vec4 position, mat4 rotation);
		Transform(mat4 rotation);

		void setRotation(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw);

		void rotate(t_float yaw, t_float pitch, t_float roll, t_float xw, t_float yw, t_float zw);
		void scale(t_float x, t_float y, t_float z, t_float w);
	};
}

#endif
