#include <OSE/Blueprints/Scene.hpp>

namespace OSE {

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add(Layer* layer) {
  this->m_layers.push_back(layer);
}

void Scene::insert(Layer* layer, int index) {
  this->m_layers.insert(this->m_layers.begin() + index, layer);
}

void Scene::remove(Layer* layer) {
  for (std::vector<Layer*>::iterator it = this->m_layers.begin();
       it != this->m_layers.end(); it++) {
    if (*it == layer) {
      this->m_layers.erase(it);
      break;
    }
  }
}

void Scene::remove(int index) {
  this->m_layers.erase(this->m_layers.begin() + index);
}

void Scene::clear() {
  for (Layer* layer : this->m_layers) {
    layer->clear();
    delete layer;
  }
  this->m_layers.clear();
}

void Scene::free() {
  this->m_layers.clear();
}

void Scene::render(Renderer* renderer) {
  for (Layer* layer : this->m_layers) {
    layer->onRender(renderer);
  }
}

void Scene::updatePhysics(t_float delta) {
  for (Layer* layer : this->m_layers) {
    layer->updatePhysics(delta);
  }
}

EventSystem* Scene::getLayerEventSystem(int index) {
  int size = this->m_layers.size();
  if (index < size) {
    return &this->m_layers.at(size - index - 1)->eventSystem();
  }
  return nullptr;
}
}  // namespace OSE