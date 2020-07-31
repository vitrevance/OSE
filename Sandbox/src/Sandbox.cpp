#include <OSE.h>

class TestActor : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent>, OSE::EventListener<OSE::KeyReleasedEvent> {
public:

	OSE::vecd velocity;
	float angle = 0;

	TestActor() {
	}

	void onEvent(OSE::TickEvent& event) override {
		this->m_transform.position += this->velocity * event.getDeltaTime();
		this->angle += event.getDeltaTime();
		this->m_transform.rotate(angle * 0.78 / 2000, angle / 2000, -angle * 1.5 / 2000);
	}

	void onEvent(OSE::KeyPressedEvent& event) override {
		if (event.getRepeatCount() > 1) {
			return;
		}
		if (event.getKeyCode() == 'D') {
			this->velocity[0] = 0.001;
		}
		else if (event.getKeyCode() == 'A') {
			this->velocity[0] = -0.001;
		}
		else if (event.getKeyCode() == 'W') {
			this->velocity[2] = 0.001;
		}
		else if (event.getKeyCode() == 'S') {
			this->velocity[2] = -0.001;
		}
		else if (event.getKeyCode() == ' ') {
			this->velocity[1] = 0.001;
		}
		else if (event.getKeyCode() == 'C') {
			this->velocity[1] = -0.001;
		}
	}

	void onEvent(OSE::KeyReleasedEvent& event) override {
		if (event.getKeyCode() == 'D') {
			this->velocity[0] = 0;
		}
		else if (event.getKeyCode() == 'A') {
			this->velocity[0] = 0;
		}
		else if (event.getKeyCode() == 'W') {
			this->velocity[2] = 0;
		}
		else if (event.getKeyCode() == 'S') {
			this->velocity[2] = 0;
		}
		else if (event.getKeyCode() == ' ') {
			this->velocity[1] = 0;
		}
		else if (event.getKeyCode() == 'C') {
			this->velocity[1] = 0;
		}
	}

	void onRender(OSE::Renderer* renderer) {
		renderer->drawStaticMesh(OSE::AssetSystem::instance->primitiveCube, &this->m_transform);
	}
};

class Sandbox : public OSE::Engine, OSE::EventListener<OSE::WindowClosedEvent> {
public:

	Sandbox() {
		OSE_LOG(LOG_APP_TRACE, "Sandbox startup...")
		this->createWindow();
		OSE::EventSystem::instance->subscribeEventListener(this);
		OSE::Scene* scene = new OSE::Scene();
		OSE::Layer* layer = new OSE::Layer();
		layer->addAndSubscribe(new TestActor());
		scene->add(layer);
		this->setActiveScene(scene);
		OSE::Camera* camera = new OSE::Camera(this->m_window->getWidth(), this->m_window->getHeight());
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
};

OSE::Engine* OSE::CreateApplication() {
	return new Sandbox();
}