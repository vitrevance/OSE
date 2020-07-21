#ifndef OSE_LAYER_H
#define OSE_LAYER_H

#include <OSE/Core.h>
#include <OSE/Blueprints/Entity.h>
#include <OSE/Systems/EventSystem.h>

namespace OSE {

	class OSE_API Layer {
	public:
		Layer();
		virtual ~Layer();

		void add(Entity* entity);
		void remove(Entity* entity);
		void subscribeEventListener(EventListenerBase* eventListener);
		void unsubscribeEventListener(EventListenerBase* eventListener);
		void addAndSubscribe(Entity* entity);
		void clear();
		void free();

		virtual void onRender(Renderer* renderer);
		EventSystem& eventSystem();
	protected:
		std::set<Entity*> m_entities;
		EventSystem m_eventSystem;
	};
}

#endif