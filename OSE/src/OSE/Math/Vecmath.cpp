#include <OSE/Math/Vecmath.h>

namespace OSE {

	vec<3> cross(vec<3> a, vec<3> b) {
		return vec<3>({ a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0] });
	}

	mat<4, 4> lookAt(vec<3> from, vec<3> at) {
		vec<3> zaxis = (at - from).normalized();
		vec<3> xaxis = (cross(vec<3>({ 0, 1, 0 }), zaxis));
		vec<3> yaxis = cross(zaxis, xaxis);
		return mat<4, 4>({ xaxis[0], yaxis[0], zaxis[0], 0,
					xaxis[1], yaxis[1], zaxis[1], 0,
					xaxis[2], yaxis[2], zaxis[2], 0,
					0, 0, 0, 1 });
	}
}