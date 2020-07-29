#include "Actor.h"

namespace OSE {
	Actor::Actor() {
		vec<3> pos;
		pos.x() = 1;
		OSE_LOG(LOG_OSE_INFO, std::to_string(pos[0]))
	}

	Actor::~Actor() {

	}
}