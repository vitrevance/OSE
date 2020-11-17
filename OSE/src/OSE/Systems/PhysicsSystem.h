#ifndef OSE_PHYSICSSYSTEM_H
#define OSE_PHYSICSSYSTEM_H

#include <OSE/Core.h>
#include <OSE/Physics/RigidBody.h>
#include <OSE/Blueprints/StaticMesh.h>
#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API PhysicsSystem {
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void add(RigidBody* rigidBody);
		void remove(RigidBody* rigidBody);

		void free();

		void update(t_float delta);
	private:
		std::set<RigidBody*> m_physicsBodies;

		vec4 getSupport(Convex* convex, Transform& transform, vec4 d);
		vec4 GJK(Convex* a, Transform& ta, Convex* b, Transform& tb);
		vec4 orderedDiagonals(Convex* a, Transform& ta, Convex* b, Transform& tb);
		vec4 volumes(Convex* a, Transform& ta, Convex* b, Transform& tb);
		void updateBodies(RigidBody* a, RigidBody* b, t_float delta);
	};
}

#endif