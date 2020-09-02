#ifndef OSE_ROTOR_H
#define OSE_ROTOR_H

#include <OSE/Math/Vector.h>
#include <OSE/Math/Multivector.h>

namespace OSE {
	class OSE_API Rotor4 {
	public:
		t_float real;
		Bivector4 wedge;
		t_float xyzw;

		Rotor4();
	};
}

#endif