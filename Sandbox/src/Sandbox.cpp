#include<OSE.h>

class Sandbox : public OSE::Engine {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

OSE::Engine* OSE::CreateApplication() {
	return new Sandbox();
}