#ifndef OSE_SCENE_H
#define OSE_SCENE_H

#include <OSE/Blueprints/Layer.h>

namespace OSE {
	class OSE_API Scene {
	public:
		Scene();
		virtual ~Scene();

		void add(Layer* layer);
		void insert(Layer* layer, int index);
		void remove(Layer* layer);
		void remove(int index);
		void clear();
		void free();

		void onEvent(Event& event);

	protected:
		std::vector<Layer*> m_layers;
	};
}

#endif