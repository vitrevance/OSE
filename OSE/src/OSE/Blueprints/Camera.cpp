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
	}

	Camera::~Camera() {

	}

	mat4 Camera::getProjection() {
		return this->m_projection;
	}

	mat4 Camera::getView() {
		vec4 pos = this->m_transform.position;
		mat4 matPos({
			1, 0, 0, pos.x,
			0, 1, 0, pos.y,
			0, 0, 1, pos.z,
			0, 0, 0, 1
			});
		return matPos * this->m_transform.toMatrix();
	}

	Transform& Camera::getTransform() {
		return this->m_transform;
	}

	vec4 Camera::getForward() {
		return (this->m_transform.rotation * vec4(0, 0, 1, 0)).normalized();
	}

	vec4 Camera::getUp() {
		return (this->m_transform.rotation * vec4(0, 1, 0, 0)).normalized();
	}

	vec4 Camera::getRight() {
		return (this->m_transform.rotation * vec4(1, 0, 0, 0)).normalized();
	}
}