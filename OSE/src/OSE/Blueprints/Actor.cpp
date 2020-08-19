#include "Actor.h"

namespace OSE {
	Actor::Actor() {
	}

	Actor::~Actor() {

	}

	Transform& Actor::getTransform() {
		return this->m_transform;
	}
}