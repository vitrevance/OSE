#ifndef OSE_ENTITY_H
#define OSE_ENTITY_H

#include <OSE/Core.hpp>
#include <OSE/Events/Event.hpp>
#include <OSE/Systems/Renderer.hpp>
#include <OSE/Physics/RigidBody.hpp>

namespace OSE {
class OSE_API Entity : public virtual EventListenerBase {
 public:
  Entity();
  virtual ~Entity();

  virtual void onRender(Renderer* renderer);
  virtual RigidBody* getPhysicsBody();
};
}  // namespace OSE

#endif