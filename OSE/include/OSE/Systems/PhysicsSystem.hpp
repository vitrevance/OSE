#ifndef OSE_PHYSICSSYSTEM_H
#define OSE_PHYSICSSYSTEM_H

#include <OSE/Core.hpp>
#include <OSE/Physics/RigidBody.hpp>
#include <OSE/Blueprints/StaticMesh.hpp>
#include <OSE/Math/Vecmath.hpp>

namespace OSE {
class OSE_API PhysicsSystem {
 public:
  PhysicsSystem() = default;
  ~PhysicsSystem() = default;

  void add(RigidBody* rigidBody);
  void remove(RigidBody* rigidBody);

  void free();

  void update(float delta);

 private:
  struct CollisionData {
    vec4 normal;
    vec4 location;
  };

  std::set<RigidBody*> m_physicsBodies;

  vec4 getSupport(RigidBody* a, RigidBody* b, vec4 direction);
  PhysicsSystem::CollisionData GJK(RigidBody* a, RigidBody* b);
  vec4 EPA(RigidBody* rba, RigidBody* rbb, std::vector<vec4>& simplex);
  void updateBodies(RigidBody* a, RigidBody* b, float delta);

  int SimplexCheck(std::vector<vec4>& simplex, vec4& direction);
  int Line(std::vector<vec4>& simplex, vec4& direction);
  int Triangle(std::vector<vec4>& simplex, vec4& direction);
  int FTetrahedron(std::vector<vec4>& simplex, vec4& direction);
  int FiveCell(std::vector<vec4>& simplex, vec4& direction);
};
}  // namespace OSE

#endif