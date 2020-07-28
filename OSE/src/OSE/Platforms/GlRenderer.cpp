#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = this->createShader("OSE/mainShader");
		this->setupStaticMesh(AssetSystem::instance->primitiveTriangle);
	}

	GlRenderer::~GlRenderer() {
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh) {
		glClearColor(0.25, 0.5, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->enableShader(this->m_mainShader);
		glBindVertexArray(mesh->VAO);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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

		Renderer::Shader programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		glLinkProgram(programId);
		glValidateProgram(programId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);

		OSE_LOG(LOG_OSE_TRACE, "Shader compiled " + shaderName + " " + std::to_string(programId))

		return programId;
	}

	void GlRenderer::enableShader(Renderer::Shader shader) {
		glUseProgram(shader);
	}

	void GlRenderer::disableShader() {
		glUseProgram(0);
	}

	void GlRenderer::setupStaticMesh(StaticMesh* mesh) {
		glGenVertexArrays(1, &mesh->VAO);
		glBindVertexArray(mesh->VAO);

		glGenBuffers(1, &mesh->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), mesh->vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &mesh->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}