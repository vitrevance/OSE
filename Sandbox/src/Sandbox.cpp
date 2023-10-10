#include <OSE.hpp>
#include <OSE/Events/KeyEvent.hpp>
#include <OSE/Events/MouseEvent.hpp>
#include <OSE/Events/WindowEvent.hpp>

using OSE::vec2;
using OSE::vec3;
using OSE::vec4;

class TestActor : public OSE::Actor {
 public:
  OSE::RigidBody rigidBody;

  TestActor()
      : rigidBody(
            OSE::RigidBody(OSE::AssetSystem::instance->getConvex("cube"))) {
  }

  void onEvent(OSE::TickEvent& event) override {
    this->getTransform().rotation.rotate(
        OSE::Rotor4::xw(event.getDeltaTime() / 1000));
    this->getTransform().rotation.rotate(
        OSE::Rotor4::xz(event.getDeltaTime() / 1530));
    this->getTransform().rotation.rotate(
        OSE::Rotor4::zw(event.getDeltaTime() / 1010));
    this->getTransform().rotation.rotate(
        OSE::Rotor4::yw(event.getDeltaTime() / 1300));
  }

  void onRender(OSE::Renderer* renderer) override {
    renderer->drawStaticMesh(OSE::AssetSystem::instance->getStaticMesh("cube"),
                             &this->rigidBody.getTransform());
  }

  OSE::RigidBody* getPhysicsBody() override {
    return &this->rigidBody;
  }

  OSE::Transform& getTransform() override {
    return this->rigidBody.getTransform();
  }
};

class Player : public OSE::Actor,
               OSE::EventListener<OSE::KeyPressedEvent>,
               OSE::EventListener<OSE::KeyReleasedEvent>,
               OSE::EventListener<OSE::MouseMovedEvent> {
 public:
  OSE::Transform m_transform;

  OSE::vec4 velocity;
  OSE::vec4 acceleration;
  OSE::Camera* camera;
  t_float speed = 0.0005;

  int f = 0, r = 0, u = 0, w = 0;

  Player() {
  }

  void onEvent(OSE::TickEvent& event) override {
    this->acceleration +=
        vec4(this->camera->getForward().x, 0, this->camera->getForward().z, 0)
            .normalized() *
        this->speed * f;
    this->acceleration +=
        vec4(this->camera->getRight().x, 0, this->camera->getRight().z, 0)
            .normalized() *
        this->speed * r;
    this->acceleration += OSE::vec4(0, 1, 0, 0) * this->speed * u;
    this->acceleration += OSE::vec4(0, 0, 0, 1) * this->speed * w;

    this->velocity += this->acceleration * event.getDeltaTime();
    this->m_transform.position += this->velocity * event.getDeltaTime();
    this->velocity *= 0.9;
    this->acceleration = OSE::vec4(0);
    this->camera->getTransform().position = this->m_transform.position;

    // std::cout << "W: " << this->m_transform.position.w << std::endl;
  }

  void onEvent(OSE::KeyPressedEvent& event) override {
    if (event.getRepeatCount() > 1) {
      return;
    }
    if (event.getKeyCode() == 'D') {
      r = 1;
    } else if (event.getKeyCode() == 'A') {
      r = -1;
    } else if (event.getKeyCode() == 'W') {
      f = 1;
    } else if (event.getKeyCode() == 'S') {
      f = -1;
    } else if (event.getKeyCode() == ' ') {
      u = 1;
    } else if (event.getKeyCode() == 'C') {
      u = -1;
    } else if (event.getKeyCode() == 'E') {
      w = 1;
    } else if (event.getKeyCode() == 'Q') {
      w = -1;
    } else if (event.getKeyCode() == 'L') {
      // TODO: swicth render mode to lines
    } else if (event.getKeyCode() == 'K') {
      // TODO: swicth render mode to default
    }
  }

  void onEvent(OSE::KeyReleasedEvent& event) override {
    if (event.getKeyCode() == 'D') {
      if (r == 1) {
        r = 0;
      }
    } else if (event.getKeyCode() == 'A') {
      if (r == -1) {
        r = 0;
      }
    } else if (event.getKeyCode() == 'W') {
      if (f == 1) {
        f = 0;
      }
    } else if (event.getKeyCode() == 'S') {
      if (f == -1) {
        f = 0;
      }
    } else if (event.getKeyCode() == ' ') {
      if (u == 1) {
        u = 0;
      }
    } else if (event.getKeyCode() == 'C') {
      if (u == -1) {
        u = 0;
      }
    } else if (event.getKeyCode() == 'E') {
      if (w == 1) {
        w = 0;
      }
    } else if (event.getKeyCode() == 'Q') {
      if (w == -1) {
        w = 0;
      }
    }
  }

  void onEvent(OSE::MouseMovedEvent& event) override {
    this->camera->getTransform().rotation.rotate(
        OSE::Rotor4::xz(event.getX() / 1000.0));
    vec4 xz =
        vec4(this->camera->getForward().x, 0, this->camera->getForward().z, 0)
            .normalized();
    vec4 up =
        vec4(xz.x * cos(event.getY() / 1000.0), sin(event.getY() / 1000.0),
             xz.z * cos(event.getY() / 1000.0), 0);
    this->camera->getTransform().rotation.rotate(OSE::Rotor4(xz, up));
  }

  OSE::Transform& getTransform() override {
    return this->m_transform;
  }
};

class DebugBox : public OSE::Actor,
                 OSE::EventListener<OSE::KeyReleasedEvent> {
 public:
  OSE::RigidBody rigidBody;
  bool m_freeze = false;

  DebugBox()
      : rigidBody(
            OSE::RigidBody(OSE::AssetSystem::instance->getConvex("cube"))) {
    this->getTransform().scale = vec4(0.2) + vec4(0, 0, 0, 0.8);
  }

  void onEvent(OSE::TickEvent& event) override {
    if (this->m_freeze) {
      return;
    }
    // this->getTransform().position.x = DebugData::hit_pos[0];
    // this->getTransform().position.y = DebugData::hit_pos[1];
    // this->getTransform().position.z = DebugData::hit_pos[2];
    // this->getTransform().position.w = DebugData::hit_pos[3];
    this->getTransform().position =
        DebugData::Manager::instance->get<vec4>("hit_pos");
    if (this->getTransform().position.length() > 0) {
      OSE_LOG(LOG_OSE_WARNING, to_str(this->getTransform().position));
    }
  }

  void onEvent(OSE::KeyReleasedEvent& event) override {
    if (event.getKeyCode() == 'F') {
      this->m_freeze = !this->m_freeze;
    }
  }

  void onRender(OSE::Renderer* renderer) override {
    renderer->drawStaticMesh(OSE::AssetSystem::instance->getStaticMesh("cube"),
                             &this->rigidBody.getTransform());
  }

  OSE::Transform& getTransform() override {
    return this->rigidBody.getTransform();
  }
};

class Sandbox : public OSE::Engine,
                OSE::EventListener<OSE::WindowClosedEvent>,
                OSE::EventListener<OSE::KeyPressedEvent>,
                OSE::EventListener<OSE::MouseButtonPressedEvent> {
 public:
  Sandbox() {
    OSE_LOG(LOG_APP_TRACE, "Sandbox startup...");

    OSE::AssetSystem::instance->setAssetDir("assets/");

    OSE::AssetSystem::instance->loadStaticMesh("cube", "models/cube1.obj");
    OSE::AssetSystem::instance->loadTexture("crate", "models/cube1.bmp");
    OSE::AssetSystem::instance->loadMaterial("flat", "materials/crate.osem");
    OSE::AssetSystem::instance->attachMaterial("cube", "flat");
    OSE::AssetSystem::instance->genConvexForMesh("cube");

    this->createWindow();
    OSE::EventSystem::instance->subscribeEventListener(this);
    OSE::Scene* scene = new OSE::Scene();
    OSE::Layer* layer = new OSE::Layer();

    // std::cin.ignore();

    // TEST FIELD
    // GEOMETRIC ALGEBRA TEST
    /*
    t_float alpha = OSE::toRadians(30);
    vec4 ra = vec4(1, 0, 0, 0);
    vec4 rb = vec4(cos(alpha / 2), sin(alpha / 2), 0, 0);

    OSE::Multivector4 m = ra * rb;
    OSE::Multivector4 rm = rb * ra;

    OSE::Rotor4 r = OSE::Rotor4::xy(alpha);
    r.rotate(r);

    vec4 v = vec4(1, 0, 1, 2);

    vec4 vv = r * v;

    std::cout << OSE::to_str(vv) << std::endl;


    m = m * v * rm;

    std::cout << OSE::to_str(m.v0) << std::endl;
    std::cout << OSE::to_str(m.v1) << std::endl;
    std::cout << OSE::to_str(m.v2) << std::endl;
    std::cout << OSE::to_str(m.v3) << std::endl;
    std::cout << OSE::to_str(m.v4) << std::endl;
    //std::cout << b.x << " " << b.y << " " << b.z << " " << b.w << std::endl;

    this->stopEngine();
    */
    //----------------------------------------------------------------------

    TestActor* cube1 = new TestActor();
    cube1->getTransform().position = vec4(-2, -0.5, 5, 0);
    // cube1->getTransform().scale = vec4(0.7);
    // cube1->getTransform().rotation = OSE::Rotor4::xz(OSE::toRadians(30)) *
    // OSE::Rotor4::xy(OSE::toRadians(40)) *
    // OSE::Rotor4::zw(OSE::toRadians(35));
    cube1->getTransform().rotation = OSE::Rotor4::xy(OSE::toRadians(30)) *
                                     OSE::Rotor4::xz(OSE::toRadians(5));
    // cube1->getTransform().scale = vec4(2, 0.5, 1, 1);
    cube1->rigidBody.m_velocity.x = 0;

    TestActor* cube2 = new TestActor();
    cube2->getTransform().position = vec4(2, 0, 5, 0);
    // cube2->getTransform().rotation = OSE::Rotor4::xz(OSE::toRadians(0)) *
    // OSE::Rotor4::xz(OSE::toRadians(35));

    layer->addAndSubscribe(cube1);
    layer->addAndSubscribe(cube2);

    // layer->addLightSource(new
    // OSE::LightSource(OSE::LightSource::Type::DIRECTIONAL_LIGHT, OSE::vec3(1),
    // OSE::lookAt(OSE::vec3(), OSE::vec3({1, -1, 1}))));
    layer->addLightSource(
        new OSE::LightSource(OSE::LightSource::Type::POINT_LIGHT, OSE::vec3(1),
                             OSE::vec4(0, 15, 0, 0)));
    layer->addLightSource(new OSE::LightSource(
        OSE::LightSource::Type::AMBIENT_LIGHT, OSE::vec3(0.4)));
    OSE::Camera* camera = new OSE::Camera(this->m_window->getWidth(),
                                          this->m_window->getHeight());
    Player* player = new Player();
    player->camera = camera;
    layer->addAndSubscribe(player);

    layer->addAndSubscribe(new DebugBox());

    scene->add(layer);
    this->setActiveScene(scene);

    this->m_renderer->setCurrentCamera(camera);
  }

  ~Sandbox() {
    this->disposeWindow();
    OSE::EventSystem::instance->unsubscribeEventListener(this);
    this->getActiveScene()->clear();
    delete this->getActiveScene();
    this->setActiveScene(nullptr);
  }

  void onEvent(OSE::WindowClosedEvent& event) override {
    this->stopEngine();
    event.setHandled();
  }

  void onEvent(OSE::KeyPressedEvent& event) override {
    if (event.getKeyCode() == 342) {
      this->m_window->releaseMouse();
    }
  }

  void onEvent(OSE::MouseButtonPressedEvent& event) override {
    this->m_window->grabMouse();
  }
};

OSE::Engine* OSE::CreateApplication() {
  return new Sandbox();
}