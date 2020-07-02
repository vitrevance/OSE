#ifndef OSE_ENGINE_H
#define OSE_ENGINE_H

#include <OSE/Core.h>
#include <OSE/Logger.h>
#include <OSE/Systems/EventSystem.h>

namespace OSE {

	class OSE_API Engine {
	public:
		static Engine* instance;

		Engine();
		~Engine();

		void run();

	private:
		void init();

		void stop();
	};
}

#endif