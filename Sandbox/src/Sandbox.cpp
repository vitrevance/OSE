#include <OSE.h>

class TestActor : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent> {
public:
	TestActor() {
	}

	void onEvent(OSE::TickEvent& event) override {
	}

	void onEvent(OSE::KeyPressedEvent& event) override {
		if (event.getKeyCode() == 'D') {
			this->m_transform.position[0] += 0.02;
		}
		else if (event.getKeyCode() == 'A') {
			this->m_transform.position[0] -= 0.02;
		}
		else if (event.getKeyCode() == 'W') {
			this->m_transform.position[2] += 0.02;
		}
		else if (event.getKeyCode() == 'S') {
			this->m_transform.position[2] -= 0.02;
		}
	}

	void onRender(OSE::Renderer* renderer) {
		renderer->drawStaticMesh(OSE::AssetSystem::instance->primitiveTriangle, this->m_transform);
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