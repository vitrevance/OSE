#include <OSE.h>

class TestActor : public OSE::Actor {
public:

	OSE::vecd velocity;
	float angle = 0;

	TestActor() {
		this->m_transform.position = OSE::vecd({0, 0, 10});
	}

	void onEvent(OSE::TickEvent& event) override {
		this->m_transform.position += this->velocity * event.getDeltaTime();
		this->angle += event.getDeltaTime() / OSE::Random::integer(800, 850);
		//this->m_transform.rotate(angle * 0.78, angle, -angle * 1.5);
		this->angle = 0;
	}

	void onRender(OSE::Renderer* renderer) {
		renderer->drawStaticMesh(OSE::AssetSystem::instance->getStaticMesh("building"), &this->m_transform);
		renderer->drawStaticMesh(OSE::AssetSystem::instance->getStaticMesh("cube") , &this->m_transform);
	}
};

class Player : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent>, OSE::EventListener<OSE::KeyReleasedEvent>,
	OSE::EventListener<OSE::MouseMovedEvent> {
public:

	OSE::vecd velocity;
	OSE::vecd acceleration;
	OSE::Camera* camera;

	int f = 0, r = 0, u = 0;

	Player() {
	}

	void onEvent(OSE::TickEvent& event) override {

		this->acceleration += this->camera->getForward() * 0.0005 * f;
		this->acceleration += this->camera->getRight() * 0.0005 * r;
		this->acceleration += OSE::vecd({0, 1}) * 0.0005 * u;

		this->velocity += this->acceleration * event.getDeltaTime();
		this->m_transform.position += this->velocity * event.getDeltaTime();
		this->velocity *= 0.9;
		this->acceleration *= 0;
		this->camera->getTransform().position = this->m_transform.position;
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
	}

	void onEvent(OSE::MouseMovedEvent& event) override {
		this->camera->getTransform().rotate(0, event.getX() / 500, event.getY() / 500);
	}
};

class Sandbox : public OSE::Engine, OSE::EventListener<OSE::WindowClosedEvent>, OSE::EventListener<OSE::KeyPressedEvent>,
		OSE::EventListener<OSE::MouseButtonPressedEvent> {
public:

	Sandbox() {
		OSE_LOG(LOG_APP_TRACE, "Sandbox startup...")

			//OSE::AssetSystem::instance->setAssetDir("C:/Users/Ruslan/source/repos/OSE/bin/Debug-x64/Sandbox/assets/");

		OSE::AssetSystem::instance->loadStaticMesh("building", "OSE/low poly buildings.obj");
		OSE::AssetSystem::instance->loadStaticMesh("cube", "OSE/cube.obj");
		this->createWindow();
		OSE::EventSystem::instance->subscribeEventListener(this);
		OSE::Scene* scene = new OSE::Scene();
		OSE::Layer* layer = new OSE::Layer();
		for (int i = 0; i < 0; i++) {
			TestActor* actor = new TestActor();
			actor->velocity = OSE::Random::vector<I_DIMENSIONS>(1.0/250.0);
			layer->addAndSubscribe(actor);
		}
		layer->addAndSubscribe(new TestActor());
		layer->addLightSource(new OSE::LightSource(OSE::LightSource::Type::DIRECTIONAL_LIGHT, OSE::vec3(1), OSE::lookAt(OSE::vec3(), OSE::vec3({1, -1, 1}))));
		layer->addLightSource(new OSE::LightSource(OSE::LightSource::Type::AMBIENT_LIGHT, OSE::vec3(0.2)));
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