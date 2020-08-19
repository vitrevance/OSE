#ifndef OSE_RENDERER_H
#define OSE_RENDERER_H

#include <OSE/Core.h>
#include <OSE/Blueprints/Camera.h>
#include <OSE/Blueprints/StaticMesh.h>
#include <OSE/Math/Transform.h>
#include <OSE/Blueprints/LightSource.h>

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
}

#endif