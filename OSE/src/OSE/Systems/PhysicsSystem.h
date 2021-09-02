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
		struct CollisionData {
			vec4 normal;
			vec4 location;
		};

		std::set<RigidBody*> m_physicsBodies;

		vec4 getSupport(RigidBody* a, RigidBody* b, vec4 direction);
		PhysicsSystem::CollisionData GJK(RigidBody* a, RigidBody* b);
		vec4 EPA(RigidBody* rba, RigidBody* rbb, std::vector<vec4>& simplex);
		void updateBodies(RigidBody* a, RigidBody* b, t_float delta);

		int SimplexCheck(std::vector<vec4>& simplex, vec4& direction);
		int Line(std::vector<vec4>& simplex, vec4& direction);
		int Triangle(std::vector<vec4>& simplex, vec4& direction);
		int FTetrahedron(std::vector<vec4>& simplex, vec4& direction);
		int FiveCell(std::vector<vec4>& simplex, vec4& direction);
	};
}

#endif