#ifndef OSE_CAMERA_H
#define OSE_CAMERA_H

#include <OSE/Core.hpp>
#include <OSE/Math/Vecmath.hpp>
#include <OSE/Math/Transform.hpp>

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
}  // namespace OSE

#endif