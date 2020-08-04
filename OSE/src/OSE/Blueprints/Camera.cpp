#include <OSE/Blueprints/Camera.h>

namespace OSE {

	Camera::Camera(int width, int height) {
		float zFar = 32768;
		float zNear = 0.625;
		float FOV = 75;
		this->m_projection = mat4({
			1 / (float)tan(FOV * 0.5 * CONST_PI / 180), 0, 0, 0,
			0, width / (float)tan(FOV * 0.5 * CONST_PI / 180) / height, 0, 0,
			0, 0, (zFar + zNear) / (zFar - zNear), -zFar * zNear / (zFar - zNear),
			0, 0, 1, 0
			});
		this->m_slice[0] = 0;
		this->m_slice[1] = 1;
		this->m_slice[2] = 2;
	}

	Camera::~Camera() {

	}

	mat4 Camera::getProjection() {
		return this->m_projection;
	}

	vec3 Camera::getSlicePosition() {
		return this->m_transform.getSlicePosition(this->m_slice);
	}

	mat4 Camera::getSliceView() {
		vec3 slicePos = this->getSlicePosition();
		mat4 matPos({
			1, 0, 0, slicePos[0],
			0, 1, 0, slicePos[1],
			0, 0, 1, slicePos[2],
			0, 0, 0, 1
			});
		return matPos * this->m_transform.rotation;
	}

	unsigned int* Camera::getSlice() {
		return this->m_slice;
	}

	Transform& Camera::getTransform() {
		return this->m_transform;
	}

	vecd Camera::getForward() {
		return ((matd)this->m_transform.rotation * vecd({ 0, 0, 1 })).normalized();
	}

	vecd Camera::getUp() {
		return ((matd)this->m_transform.rotation * vecd({ 0, 1 })).normalized();
	}

	vecd Camera::getRight() {
		return ((matd)this->m_transform.rotation * vecd({ 1 })).normalized();
	}
}