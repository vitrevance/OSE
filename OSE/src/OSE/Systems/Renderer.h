#ifndef OSE_RENDERER_H
#define OSE_RENDERER_H

#include <OSE/Core.h>
#include <OSE/Blueprints/Camera.h>
#include <OSE/Blueprints/StaticMesh.h>
#include <OSE/Blueprints/Transform.h>

namespace OSE {
	class OSE_API Renderer {
	public:
		typedef unsigned int Shader;
		virtual ~Renderer();

		virtual void drawStaticMesh(StaticMesh* mesh, Transform* transform) = 0;
		virtual Shader createShader(string shaderName) = 0;
		virtual void enableShader(Shader shader) = 0;
		virtual void disableShader() = 0;

		virtual void setCurrentCamera(Camera* camera) = 0;
	protected:
		Renderer();
	};
}

#endif