/*
Keys:
OSE_BUILD - used only on OSE Engine build, must not be used in application
OSE_DISABLE_LOGGER - use to disable logging system (on Release)
WIN64 - target OS is Windows x64
*/
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