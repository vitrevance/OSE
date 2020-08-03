#ifndef OSE_LIGHTSOURCE_H
#define OSE_LIGHTSOURCE_H

#include <OSE/Core.h>
#include <OSE/Blueprints/Transform.h>

namespace OSE {
	class OSE_API LightSource {
	public:

		static enum Type {
			POINT_LIGHT,
			DIRECTIONAL_LIGHT
		};

		Transform transform;
		vec3 color;
		const Type type;

		LightSource(Type type) : type(type) {}
		LightSource(Type type, Transform transform) : type(type), transform(transform) {}
		LightSource(Type type, vecd position) : type(type), transform(Transform(position)) {}
		~LightSource() = default;
	};
}

#endif