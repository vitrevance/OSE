#ifndef OSE_ENGINE_H
#define OSE_ENGINE_H

#include <OSE/Core.hpp>
#include <chrono>
#include <OSE/Systems/EventSystem.hpp>
#include <OSE/Platforms/AssetSystem.hpp>
#include <OSE/Window.hpp>
#include <OSE/Blueprints/Scene.hpp>
#include <OSE/Blueprints/Actor.hpp>
#include <OSE/Math/Random.hpp>

namespace OSE {

class OSE_API Engine {
 public:
  static Engine* instance;

  Engine();
  virtual ~Engine();

  void run();
  void stopEngine();
  void setActiveScene(Scene* scene);
  Scene* getActiveScene();

 protected:
  Window* m_window;
  Scene* m_activeScene;
  Renderer* m_renderer;
  PhysicsSystem* m_physics;

  virtual Window* createWindow(
      WindowProps windowProps = Window::getDefaultWindowProps());
  virtual void disposeWindow();

 private:
  bool m_isRunning = true;

  void init();
  void stop();
};
}  // namespace OSE

#endif