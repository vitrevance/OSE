#ifndef OSE_SCENE_H
#define OSE_SCENE_H

#include <OSE/Blueprints/Layer.hpp>

namespace OSE {
class OSE_API Scene {
 public:
  Scene();
  virtual ~Scene();

  void add(Layer* layer);
  void insert(Layer* layer, int index);
  void remove(Layer* layer);
  void remove(int index);
  void clear();
  void free();

  virtual void render(Renderer* renderer);
  void updatePhysics(t_float delta);
  EventSystem* getLayerEventSystem(int index);

 protected:
  std::vector<Layer*> m_layers;
};
}  // namespace OSE

#endif