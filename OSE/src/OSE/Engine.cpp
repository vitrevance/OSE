#include <OSE/Engine.hpp>

#include <OSE/Platforms/WindowsWindow.hpp>
#include <OSE/Platforms/GlRenderer.hpp>

namespace OSE {

Engine* Engine::instance;

Engine::Engine() {
  (new Logger())->Start();
  Engine::instance = this;
  this->init();
}

Engine::~Engine() {
  this->stop();
  Logger::instance->Stop();
}

void Engine::init() {
  OSE_LOG(LOG_OSE_TRACE, "Engine initialization...");
  this->m_window = nullptr;
  this->m_activeScene = nullptr;
  EventSystem::instance = new EventSystem();
  AssetSystem::instance = new AssetSystem();
  AssetSystem::instance->setAssetDir("./");
}

void Engine::stop() {
  delete EventSystem::instance;
  delete AssetSystem::instance;
}

Window* Engine::createWindow(WindowProps windowProps) {
  this->m_window = new WindowsWindow(windowProps);
  this->m_renderer = new GlRenderer();
  return this->m_window;
}

void Engine::disposeWindow() {
  delete this->m_window;
  this->m_window = nullptr;
  delete this->m_renderer;
  this->m_renderer = nullptr;
}

void Engine::stopEngine() {
  this->m_isRunning = false;
}

void Engine::setActiveScene(Scene* scene) {
  this->m_activeScene = scene;
  EventSystem::instance->setSceneCallback(
      std::bind(&Scene::getLayerEventSystem, scene, std::placeholders::_1));
}

Scene* Engine::getActiveScene() {
  return this->m_activeScene;
}

void Engine::run() {
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::duration<float, std::milli> duration;

  static clock::time_point start = clock::now();
  duration elapsed = clock::now() - start;

  while (this->m_isRunning) {
    if (this->m_window != nullptr) {
      this->m_window->onUpdate();
      this->m_window->onRenderPre();
      this->m_renderer->onRenderPre();
      this->m_activeScene->render(this->m_renderer);
      this->m_renderer->onRenderPost();
      this->m_window->onRenderPost();
    }
    elapsed = clock::now() - start;
    if (elapsed.count() > 1) {
      TickEvent tickEvent(elapsed.count());
      EventSystem::instance->postEvent(tickEvent);
      this->m_activeScene->updatePhysics(elapsed.count() / 1000.0);
      start = clock::now();
    }
  }
}
}  // namespace OSE