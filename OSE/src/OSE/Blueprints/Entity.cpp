#include <OSE/Blueprints/Entity.hpp>

namespace OSE {
Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::onRender(Renderer* renderer) {
}

RigidBody* Entity::getPhysicsBody() {
  return nullptr;
}
}  // namespace OSE