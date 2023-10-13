#include <OSE/Blueprints/Layer.hpp>

namespace OSE {
Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::add(Entity* entity) {
  this->m_entities.insert(entity);
  if (entity->getPhysicsBody() != nullptr) {
    this->m_physicsSystem.add(entity->getPhysicsBody());
  }
}

void Layer::remove(Entity* entity) {
  this->m_entities.erase(entity);
  EventListenerBase* asEventListener = dynamic_cast<EventListenerBase*>(entity);
  if (asEventListener != nullptr) {
    this->unsubscribeEventListener(asEventListener);
  }
  if (entity->getPhysicsBody() != nullptr) {
    this->m_physicsSystem.remove(entity->getPhysicsBody());
  }
}

void Layer::subscribeEventListener(EventListenerBase* eventListener) {
  this->m_eventSystem.subscribeEventListener(eventListener);
}

void Layer::unsubscribeEventListener(EventListenerBase* eventListener) {
  this->m_eventSystem.unsubscribeEventListener(eventListener);
}

void Layer::addAndSubscribe(Entity* entity) {
  this->add(entity);
  this->subscribeEventListener(entity);
}

void Layer::addLightSource(LightSource* lightSource) {
  this->m_lights.insert(lightSource);
}

void Layer::removeLightSource(LightSource* lightSource) {
  this->m_lights.erase(lightSource);
}

void Layer::clear() {
  for (Entity* entity : this->m_entities) {
    delete entity;
  }
  this->m_entities.clear();
  this->m_eventSystem = EventSystem();

  for (LightSource* lightSource : this->m_lights) {
    delete lightSource;
  }
  this->m_lights.clear();
}

void Layer::free() {
  this->m_entities.clear();
  this->m_eventSystem = EventSystem();
  this->m_lights.clear();
}

void Layer::onRender(Renderer* renderer) {
  if (!this->m_lights.empty()) {
    renderer->setLightData(this->m_lights);
  }
  for (Entity* entity : this->m_entities) {
    entity->onRender(renderer);
  }
}

void Layer::updatePhysics(float delta) {
  this->m_physicsSystem.update(delta);
}

EventSystem& Layer::eventSystem() {
  return this->m_eventSystem;
}
}  // namespace OSE