#ifndef OSE_RIGIDBODY_H
#define OSE_RIGIDBODY_H

#include <OSE/Blueprints/Convex.h>
#include <OSE/Math/Transform.h>

namespace OSE {
	class OSE_API RigidBody {
	public:
		vec4 m_velocity;

		RigidBody(Convex* convex);
		~RigidBody();

		Convex* getConvex();
		Transform& getTransform();

		friend class PhysicsSystem;
	private:
		Convex* m_convex;
		Transform m_transform;
	};
}

#endif