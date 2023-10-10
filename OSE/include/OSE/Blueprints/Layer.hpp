#ifndef OSE_LAYER_H
#define OSE_LAYER_H

#include <OSE/Core.hpp>
#include <OSE/Blueprints/Entity.hpp>
#include <OSE/Systems/EventSystem.hpp>
#include <OSE/Systems/PhysicsSystem.hpp>

namespace OSE {

class OSE_API Layer {
 public:
  Layer();
  virtual ~Layer();

  void add(Entity* entity);
  void remove(Entity* entity);
  void subscribeEventListener(EventListenerBase* eventListener);
  void unsubscribeEventListener(EventListenerBase* eventListener);
  void addAndSubscribe(Entity* entity);

  void addLightSource(LightSource* lightSource);
  void removeLightSource(LightSource* lightSource);

  void clear();
  void free();

  virtual void onRender(Renderer* renderer);
  void updatePhysics(t_float delta);
  EventSystem& eventSystem();

 protected:
  std::set<Entity*> m_entities;
  std::set<LightSource*> m_lights;
  EventSystem m_eventSystem;
  PhysicsSystem m_physicsSystem;
};
}  // namespace OSE

#endif