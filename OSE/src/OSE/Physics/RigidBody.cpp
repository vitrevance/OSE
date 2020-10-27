#include <OSE/Physics/RigidBody.h>

namespace OSE {
	RigidBody::RigidBody(Convex* convex) {
		this->m_convex = convex;
	}

	RigidBody::~RigidBody() {
	}

	Convex* RigidBody::getConvex() {
		return this->m_convex;
	}

	Transform& RigidBody::getTransform() {
		return this->m_transform;
	}
}