#ifndef OSE_GLRENDERER_H
#define OSE_GLRENDERER_H

#include <GLFW/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <OSE/Systems/Renderer.h>
#include <OSE/Platforms/AssetSystem.h>

namespace OSE {
	class OSE_API GlRenderer : public Renderer {
	public:
		GlRenderer();
		virtual ~GlRenderer();

		virtual void drawStaticMesh(StaticMesh* mesh) override;

	protected:
		ShaderProgram m_mainShader;
	};
}

#endif