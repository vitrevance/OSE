#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = this->createShader("OSE/mainShader");
		this->setupStaticMesh(AssetSystem::instance->primitiveTriangle);
	}

	GlRenderer::~GlRenderer() {
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh) {
		this->enableShader(this->m_mainShader);
		glBindVertexArray(mesh->vertexArray);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}

	Renderer::Shader GlRenderer::createShader(string shaderName) {
		string fragmentText = AssetSystem::instance->loadRawString(shaderName + ".frag");
		string vertexText = AssetSystem::instance->loadRawString(shaderName + ".vert");
		
		OSE_LOG(LOG_OSE_TRACE, vertexText)
		OSE_LOG(LOG_OSE_TRACE, fragmentText);

		unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexChar = vertexText.c_str();
		glShaderSource(vertexId, 1, &vertexChar, NULL);
		glCompileShader(vertexId);

		GLint result;
		glGetShaderiv(vertexId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertexId, length, &length, &error[0]);
			OSE_LOG(LOG_OSE_ERROR, string(&error[0]))
			glDeleteShader(vertexId);

			return 0;
		}

		unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentChar = fragmentText.c_str();
		glShaderSource(fragmentId, 1, &fragmentChar, NULL);
		glCompileShader(fragmentId);

		glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragmentId, length, &length, &error[0]);
			OSE_LOG(LOG_OSE_ERROR, string(&error[0]))
			glDeleteShader(fragmentId);

			return 0;
		}

		OSE_LOG(LOG_OSE_TRACE, "Shader compiled " + shaderName)

		Renderer::Shader programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		glLinkProgram(programId);
		glValidateProgram(programId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		return programId;
	}

	void GlRenderer::enableShader(Renderer::Shader shader) {
		glUseProgram(shader);
	}

	void GlRenderer::disableShader() {
		glUseProgram(0);
	}

	void GlRenderer::setupStaticMesh(StaticMesh* mesh) {
		glGenVertexArrays(1, &mesh->vertexArray);
		glBindVertexArray(mesh->vertexArray);

		glGenBuffers(1, &mesh->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), mesh->vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}