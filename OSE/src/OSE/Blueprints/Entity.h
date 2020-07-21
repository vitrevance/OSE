#ifndef OSE_ENTITY_H
#define OSE_ENTITY_H

#include <OSE/Core.h>
#include <OSE/Events/Event.h>
#include <OSE/Systems/Renderer.h>

namespace OSE {
	class OSE_API Entity : public virtual EventListenerBase {
	public:
		Entity();
		virtual ~Entity();

		virtual void onRender(Renderer* renderer);
	};
}

#endif