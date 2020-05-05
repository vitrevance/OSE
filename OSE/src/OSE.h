#ifndef OSE_H
#define OSE_H

#include"OSE/Engine.h"

namespace OSE {

	extern Engine* CreateApplication();
}

int main(int argc, char** argv) {
	OSE::Engine* engine = OSE::CreateApplication();
	engine->run();
	delete engine;
	return 0;
}

#endif