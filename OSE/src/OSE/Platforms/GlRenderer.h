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

		virtual void onRenderPre() override;
		virtual void onRenderPost() override;
		virtual void drawStaticMesh(StaticMesh* mesh, Transform* transform) override;
		virtual Renderer::Shader createShader(string shaderName) override;
		virtual void enableShader(Renderer::Shader shader) override;
		virtual void disableShader() override;

		virtual void setCurrentCamera(Camera* camera);
		virtual void setLightData(std::set<LightSource*>& lightData) override;
	protected:
		unsigned int VAO, VBO, EBO;
		Renderer::Shader m_activeShader;
		Renderer::Shader m_mainShader;
		Camera* m_camera;

		std::vector<Vertex> verts;
		std::vector<unsigned int> inds;
		unsigned int indexOffset;
		std::vector<mat4> transforms;

		void setupStaticMesh(StaticMesh* mesh);
	};
}

#endif