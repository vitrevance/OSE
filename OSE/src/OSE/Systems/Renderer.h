#ifndef OSE_RENDERER_H
#define OSE_RENDERER_H

#include <OSE/Core.h>
#include <OSE/Blueprints/StaticMesh.h>

namespace OSE {
	class OSE_API Renderer {
	public:
		typedef unsigned int Shader;
		virtual ~Renderer();

		virtual void drawStaticMesh(StaticMesh* mesh) = 0;
		virtual Shader createShader(string shaderName) = 0;
		virtual void enableShader(Shader shader) = 0;
		virtual void disableShader() = 0;
	protected:
		Renderer();
	};
}

#endif