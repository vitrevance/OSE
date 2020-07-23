#include<OSE.h>

class TestActor : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent> {
public:
	OSE::StaticMesh* mesh;
	TestActor() {
		this->mesh = new OSE::StaticMesh();
	}

	void onEvent(OSE::TickEvent& event) override {
		//OSE_LOG(LOG_APP_TRACE, "TestActor tick")
	}

	void onEvent(OSE::KeyPressedEvent& event) override {
		OSE_LOG(LOG_APP_TRACE, "Key pressed")
	}

	void onRender(OSE::Renderer* renderer) {
		
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