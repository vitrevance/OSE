#include <OSE.h>

using OSE::vec2;
using OSE::vec3;
using OSE::vec4;

class TestActor : public OSE::Actor {
public:
	TestActor() {
	}

	void onEvent(OSE::TickEvent& event) override {
		t_float angle = OSE::Random::decimal() / event.getDeltaTime() / 1000;
		this->m_transform.rotate(angle / OSE::Random::integer(1, 4), angle / OSE::Random::integer(1, 4),
			angle / OSE::Random::integer(1, 4), angle / OSE::Random::integer(1, 4), angle / OSE::Random::integer(1, 4),
			angle / OSE::Random::integer(1, 4));
	}

	void onRender(OSE::Renderer* renderer) {
		renderer->drawStaticMesh(OSE::AssetSystem::instance->getStaticMesh("cube") , &this->m_transform);
	}
};

class Player : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent>, OSE::EventListener<OSE::KeyReleasedEvent>,
	OSE::EventListener<OSE::MouseMovedEvent> {
public:

	OSE::vec4 velocity;
	OSE::vec4 acceleration;
	OSE::Camera* camera;
	t_float speed = 0.0005;

	int f = 0, r = 0, u = 0, w = 0;

	Player() {
	}

	void onEvent(OSE::TickEvent& event) override {

		this->acceleration += vec4(this->camera->getForward().x, 0, this->camera->getForward().z, 0).normalized() * this->speed * f;
		this->acceleration += vec4(this->camera->getRight().x, 0, this->camera->getRight().z, 0).normalized() * this->speed * r;
		this->acceleration += OSE::vec4(0, 1, 0, 0) * this->speed * u;
		this->acceleration += OSE::vec4(0, 0, 0, 1) * this->speed * w;

		this->velocity += this->acceleration * event.getDeltaTime();
		this->m_transform.position += this->velocity * event.getDeltaTime();
		this->velocity *= 0.9;
		this->acceleration *= 0;
		this->camera->getTransform().position = this->m_transform.position;


		//std::cout << "W: " << this->m_transform.position.w << std::endl;
	}

	void onEvent(OSE::KeyPressedEvent& event) override {
		if (event.getRepeatCount() > 1) {
			return;
		}
		if (event.getKeyCode() == 'D') {
			r = 1;
		}
		else if (event.getKeyCode() == 'A') {
			r = -1;
		}
		else if (event.getKeyCode() == 'W') {
			f = 1;
		}
		else if (event.getKeyCode() == 'S') {
			f = -1;
		}
		else if (event.getKeyCode() == ' ') {
			u = 1;
		}
		else if (event.getKeyCode() == 'C') {
			u = -1;
		}
		else if (event.getKeyCode() == 'E') {
			w = 1;
		}
		else if (event.getKeyCode() == 'Q') {
			w = -1;
		}
		else if (event.getKeyCode() == 'L') {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (event.getKeyCode() == 'K') {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void onEvent(OSE::KeyReleasedEvent& event) override {
		if (event.getKeyCode() == 'D') {
			if (r == 1) r = 0;
		}
		else if (event.getKeyCode() == 'A') {
			if (r == -1) r = 0;
		}
		else if (event.getKeyCode() == 'W') {
			if (f == 1) f = 0;
		}
		else if (event.getKeyCode() == 'S') {
			if (f == -1) f = 0;
		}
		else if (event.getKeyCode() == ' ') {
			if (u == 1) u = 0;
		}
		else if (event.getKeyCode() == 'C') {
			if (u == -1) u = 0;
		}
		else if (event.getKeyCode() == 'E') {
			if (w == 1) w = 0;
		}
		else if (event.getKeyCode() == 'Q') {
			if (w == -1) w = 0;
		}
	}

	void onEvent(OSE::MouseMovedEvent& event) override {
		this->camera->getTransform().rotate(0, event.getX() / 500, event.getY() / 500, 0, 0, 0);
	}
};

class Sandbox : public OSE::Engine, OSE::EventListener<OSE::WindowClosedEvent>, OSE::EventListener<OSE::KeyPressedEvent>,
		OSE::EventListener<OSE::MouseButtonPressedEvent> {
public:

	Sandbox() {
		OSE_LOG(LOG_APP_TRACE, "Sandbox startup...")

		//OSE::AssetSystem::instance->setAssetDir("C:/Users/Ruslan/source/repos/OSE/bin/Debug-x64/Sandbox/assets/");

		OSE::AssetSystem::instance->loadStaticMesh("cube", "OSE/cube1.obj");
		OSE::AssetSystem::instance->loadTexture("crate", "OSE/cube1.bmp");
		OSE::AssetSystem::instance->createMaterial("flat", "#texture crate\nvec4 material() { vec4 matcol = texture(texture0, uv_coord); return matcol + vec4(0.2); }");
		OSE::AssetSystem::instance->attachMaterial("cube", "flat");

		this->createWindow();
		OSE::EventSystem::instance->subscribeEventListener(this);
		OSE::Scene* scene = new OSE::Scene();
		OSE::Layer* layer = new OSE::Layer();
		
		TestActor* floor = new TestActor();
		floor->getTransform().position = vec4(0, -2.7, 0, 0);
		floor->getTransform().scale(20, 1, 20, 20);
		TestActor* roof = new TestActor();
		roof->getTransform().position = vec4(0, -2.7 + 20, 0, 0);
		roof->getTransform().scale(20, 1, 20, 20);
		TestActor* wall1 = new TestActor();
		wall1->getTransform().position = vec4(20, -2.7 + 10, 0, 0);
		wall1->getTransform().scale(1, 10, 20, 20);
		TestActor* wall3 = new TestActor();
		wall3->getTransform().position = vec4(-20, -2.7 + 10, 0, 0);
		wall3->getTransform().scale(1, 10, 20, 20);
		TestActor* wall2 = new TestActor();
		wall2->getTransform().position = vec4(0, -2.7 + 10, 20, 0);
		wall2->getTransform().scale(20, 10, 1, 20);
		TestActor* wall4 = new TestActor();
		wall4->getTransform().position = vec4(0, -2.7 + 10, -20, 0);
		wall4->getTransform().scale(20, 10, 1, 20);

		for (int i = 0; i < 10; i++) {
			TestActor* cube = new TestActor();
			cube->getTransform().scale(0.5, 0.5, 0.5, 0.5);
			cube->getTransform().position.x = OSE::Random::signedDecimal() * 18;
			cube->getTransform().position.x = OSE::Random::signedDecimal() * 0.3 - 0.15;
			cube->getTransform().position.z = OSE::Random::signedDecimal() * 18;
			cube->getTransform().position.w = OSE::Random::signedDecimal() * 15;
			vec3 xyzrot = OSE::Random::vector3();
			vec3 wrot = OSE::Random::vector3();
			cube->getTransform().rotate(xyzrot.x, xyzrot.y, xyzrot.z, wrot.x, wrot.y, wrot.z);
			layer->addAndSubscribe(cube);
		}

		layer->add(floor);
		layer->add(roof);
		layer->add(wall1);
		layer->add(wall2);
		layer->add(wall3);
		layer->add(wall4);
		layer->addLightSource(new OSE::LightSource(OSE::LightSource::Type::DIRECTIONAL_LIGHT, OSE::vec3(1), OSE::lookAt(OSE::vec3(), OSE::vec3({1, -1, 1}))));
		//layer->addLightSource(new OSE::LightSource(OSE::LightSource::Type::POINT_LIGHT, OSE::vec3(1), OSE::vec4(0, 15, 0, 0)));
		layer->addLightSource(new OSE::LightSource(OSE::LightSource::Type::AMBIENT_LIGHT, OSE::vec3(0.4)));
		OSE::Camera* camera = new OSE::Camera(this->m_window->getWidth(), this->m_window->getHeight());
		Player* player = new Player();
		player->camera = camera;
		layer->addAndSubscribe(player);
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