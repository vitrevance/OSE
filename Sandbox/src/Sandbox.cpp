#include<OSE.h>

class TestActor : public OSE::Actor, OSE::EventListener<OSE::KeyPressedEvent> {
public:
	TestActor() {

	}

	void onEvent(OSE::TickEvent& event) override {
		OSE_LOG(LOG_APP_TRACE, "TestActor tick")
	}

	void onEvent(OSE::KeyPressedEvent& event) override {
		OSE_LOG(LOG_APP_TRACE, "Key pressed")
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
		OSE::Entity* entity = new TestActor();
		OSE::EventSystem::instance->subscribeEventListener(entity);
		//layer->addAndSubscribe(new TestActor());
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