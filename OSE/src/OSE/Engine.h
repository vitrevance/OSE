#ifndef OSE_ENGINE_H
#define OSE_ENGINE_H

#include"Core.h"
#include"Logger.h"

namespace OSE {

	class OSE_API Engine {
	public:
		Engine();
		~Engine();

		void run();

		void init();
	};
}

#endif