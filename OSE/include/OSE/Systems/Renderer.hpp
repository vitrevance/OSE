#ifndef OSE_RENDERER_H
#define OSE_RENDERER_H

#include <OSE/Core.hpp>
#include <OSE/Blueprints/Camera.hpp>
#include <OSE/Blueprints/StaticMesh.hpp>
#include <OSE/Math/Transform.hpp>
#include <OSE/Blueprints/LightSource.hpp>

namespace OSE {
class OSE_API Renderer {
 public:
  typedef unsigned int Shader;
  virtual ~Renderer();

  virtual void onRenderPre() = 0;
  virtual void onRenderPost() = 0;
  virtual void drawStaticMesh(StaticMesh* mesh, Transform* transform) = 0;
  virtual Shader createShader(string shaderName) = 0;
  virtual void enableShader(Shader shader) = 0;
  virtual void disableShader() = 0;

  virtual void setCurrentCamera(Camera* camera) = 0;
  virtual void setLightData(std::set<LightSource*>& lightData) = 0;

 protected:
  Renderer();
};
}  // namespace OSE

#endif