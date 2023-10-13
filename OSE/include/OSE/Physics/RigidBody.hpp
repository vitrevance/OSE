#ifndef OSE_RIGIDBODY_H
#define OSE_RIGIDBODY_H

#include <OSE/Blueprints/Convex.hpp>
#include <OSE/Math/Transform.hpp>

namespace OSE {
class OSE_API RigidBody {
 public:
  vec4 m_velocity;
  Rotor4 m_rotation;
  Bivector4 m_angVelocity;
  float m_mass;

  RigidBody(Convex* convex);
  ~RigidBody();

  vec4 getFurthestVertex(vec4 direction);

  Convex* getConvex();
  Transform& getTransform();

 protected:
  Convex* m_convex;
  Transform m_transform;
};
}  // namespace OSE

#endif