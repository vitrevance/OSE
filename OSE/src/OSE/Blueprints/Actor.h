#ifndef OSE_ACTOR_H
#define OSE_ACTOR_H

#include <OSE/Systems/EventSystem.h>
#include <OSE/Events/EngineEvent.h>
#include <OSE/Blueprints/Entity.h>
#include <OSE/Blueprints/Transform.h>

namespace OSE {
	class OSE_API Actor : public Entity, EventListener<TickEvent> {
	public:
		Actor();
		virtual ~Actor();
	protected:
		Transform m_transform;
	};
}

#endif