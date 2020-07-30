#ifndef OSE_TRANSFORM_H
#define OSE_TRANSFORM_H

#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Transform {
	public:
		vecd position;
		matd rotation;
	};
}

#endif
