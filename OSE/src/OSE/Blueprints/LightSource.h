#ifndef OSE_LIGHTSOURCE_H
#define OSE_LIGHTSOURCE_H

#include <OSE/Core.h>
#include <OSE/Math/Transform.h>

namespace OSE {
	class OSE_API LightSource {
	public:

		enum Type {
			POINT_LIGHT,
			DIRECTIONAL_LIGHT,
			AMBIENT_LIGHT
		};

		Transform transform;
		vec3 color;
		const Type type;

		LightSource(Type type) : type(type), color(vec3(1)) {}
		LightSource(Type type, vec3 color) : type(type), color(color) {}
		LightSource(Type type, vec3 color, Transform transform) : type(type), color(color), transform(transform) {}
		LightSource(Type type, vec3 color, vec4 position) : type(type), color(color), transform(Transform(position)) {}
		~LightSource() = default;
	};
}

#endif