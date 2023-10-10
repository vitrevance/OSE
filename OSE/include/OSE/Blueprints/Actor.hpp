#ifndef OSE_ACTOR_H
#define OSE_ACTOR_H

#include <OSE/Systems/EventSystem.hpp>
#include <OSE/Events/EngineEvent.hpp>
#include <OSE/Blueprints/Entity.hpp>
#include <OSE/Math/Transform.hpp>

namespace OSE {
class OSE_API Actor : public Entity,
                      EventListener<TickEvent> {
 public:
  Actor();
  virtual ~Actor();

  virtual Transform& getTransform() = 0;
};
}  // namespace OSE

#endif