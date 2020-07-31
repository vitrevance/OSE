#ifndef OSE_CAMERA_H
#define OSE_CAMERA_H

#include <OSE/Core.h>
#include <OSE/Math/Vecmath.h>

namespace OSE {
	class OSE_API Camera {
	public:
		Camera(int width, int height);
		~Camera();

		mat4 getProjection();
		vec3 getSlicePosition();
		mat4 getSliceView();
		unsigned int* getSlice();

	protected:
		unsigned int m_slice[3];
		vecd m_position;
		mat4 m_projection;
	};
}

#endif