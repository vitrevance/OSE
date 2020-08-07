#ifndef OSE_CAMERA_H
#define OSE_CAMERA_H

#include <OSE/Core.h>
#include <OSE/Math/Vecmath.h>
#include <OSE/Blueprints/Transform.h>

namespace OSE {
	class OSE_API Camera {
	public:
		Camera(int width, int height);
		~Camera();

		mat4 getProjection();
		mat4 getView();
		Transform& getTransform();
		vec4 getForward();
		vec4 getUp();
		vec4 getRight();

	protected:
		Transform m_transform;
		mat4 m_projection;
	};
}

#endif