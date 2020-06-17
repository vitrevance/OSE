#include<OSE.h>

class Sandbox : public OSE::Engine {
public:
	Sandbox() {
		OSE_LOG(LOG_APP_TRACE, "Sandbox startup...");
	}

	~Sandbox() {

	}
};

OSE::Engine* OSE::CreateApplication() {
	return new Sandbox();
}