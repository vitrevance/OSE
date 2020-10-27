#ifndef OSE_CONVEX_H
#define OSE_CONVEX_H

#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Convex {
	public:
		std::set<vec4> vertices;

		Convex();
		~Convex() = default;
	};
}

#endif
