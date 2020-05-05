#ifndef ENGINE_H
#define ENGINE_H

#include"Core.h"

namespace OSE {

	class OSE_API Engine {
	public:
		Engine();
		~Engine();

		void run();
	};
}

#endif