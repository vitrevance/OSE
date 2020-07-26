#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = this->createShader("mainShader");
		this->enableShader(this->m_mainShader);
	}

	GlRenderer::~GlRenderer() {
		this->disableShader();
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh) {
		if (mesh->vertexBuffer == 0) {
			glGenBuffers(1, &mesh->vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), mesh->vertices, GL_STATIC_DRAW);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	Renderer::Shader GlRenderer::createShader(string shaderName) {
		string fragmentText = AssetSystem::instance->loadRawString(shaderName + ".frag");
		string vertexText = AssetSystem::instance->loadRawString(shaderName + ".vert");

		unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexChar = vertexText.c_str();
		glShaderSource(vertexId, 1, &vertexChar, NULL);
		glCompileShader(vertexId);
		unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentChar = fragmentText.c_str();
		glShaderSource(fragmentId, 1, &fragmentChar, NULL);
		glCompileShader(fragmentId);

		Renderer::Shader programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		glLinkProgram(programId);
		return programId;
	}

	void GlRenderer::enableShader(Renderer::Shader shader) {
		glUseProgram(shader);
	}

	void GlRenderer::disableShader() {
		glUseProgram(0);
	}
}