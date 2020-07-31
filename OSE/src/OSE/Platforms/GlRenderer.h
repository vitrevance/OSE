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

		virtual void drawStaticMesh(StaticMesh* mesh, Transform* transform) override;
		virtual Renderer::Shader createShader(string shaderName) override;
		virtual void enableShader(Renderer::Shader shader) override;
		virtual void disableShader() override;

		virtual void setCurrentCamera(Camera* camera);
	protected:
		Renderer::Shader m_mainShader;
		Camera* m_camera;

		void setupStaticMesh(StaticMesh* mesh);
	};
}

#endif