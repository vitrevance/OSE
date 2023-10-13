#include <OSE/Physics/RigidBody.hpp>

namespace OSE {
RigidBody::RigidBody(Convex* convex) {
  this->m_convex = convex;
  this->m_mass = 100;
}

RigidBody::~RigidBody() {
}

vec4 RigidBody::getFurthestVertex(vec4 direction) {
  float highest = std::numeric_limits<float>::min();
  vec4 support;

  for (vec4 vertex : this->m_convex->vertices) {
    vec4 translated = this->m_transform.rotation * vertex;
    float dp = dot(translated, direction);
    if (dp > highest) {
      highest = dp;
      support = translated + this->m_transform.position;
    }
  }
  return support;
}

Convex* RigidBody::getConvex() {
  return this->m_convex;
}

Transform& RigidBody::getTransform() {
  return this->m_transform;
}
}  // namespace OSE