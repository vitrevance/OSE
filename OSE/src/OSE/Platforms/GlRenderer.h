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
		struct GLTransform {
			mat4 transform;
			vec4 translation;
		};
		Renderer::Shader m_activeShader;
		Renderer::Shader m_mainShader;
		Camera* m_camera;

		std::set<StaticMesh*> m_drawQuery;
		std::map<StaticMesh*, unsigned int> m_instanceBuffers;
		std::map<StaticMesh*, std::vector<GLTransform> > m_batch;

		void setupStaticMesh(StaticMesh* mesh);
		Renderer::Shader createShader(string vertexText, string geometryText, string fragmentText);
		void setupShader();
	};
}

#endif