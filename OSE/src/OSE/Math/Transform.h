#ifndef OSE_TRANSFORM_H
#define OSE_TRANSFORM_H

#include <OSE/Math/Rotor.h>

namespace OSE {
	class OSE_API Transform {
	public:
		vec4 position;
		Rotor4 rotation;
		vec4 scale;

		Transform();
		Transform(vec4 position);

		mat4 toMatrix();
		mat4 toMatrixTransposed();
	};
}

#endif
