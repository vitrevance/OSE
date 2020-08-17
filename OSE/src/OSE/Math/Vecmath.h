#ifndef OSE_VECMATH_H
#define OSE_VECMATH_H

#include <OSE/Math/Vector.h>
#include <OSE/Math/Matrix.h>

#define CONST_PI 3.141592653589793238462643383279502884L

namespace OSE {

	vec2 OSE_API operator* (vec2 v, mat<2, 2> m);

	vec3 OSE_API operator* (vec3 v, mat<3, 3> m);

	vec4 OSE_API operator* (vec4 v, mat<4, 4> m);

	vec2 OSE_API operator* (mat<2, 2> m, vec2 v);

	vec3 OSE_API operator* (mat<3, 3> m, vec3 v);

	vec4 OSE_API operator* (mat<4, 4> m, vec4 v);

	vec3 OSE_API operator* (mat<3, 4> m, vec4 v);

	vec3 OSE_API cross(vec3 a, vec3 b);

	mat<4, 4> OSE_API lookAt(vec3 from, vec3 at);

	t_float OSE_API toRadians(t_float degrees);

	typedef mat<2, 2> mat2;
	typedef mat<3, 3> mat3;
	typedef mat<4, 4> mat4;
}

#endif