#include "ShaderProgram.h"

namespace OSE {
	ShaderProgram::ShaderProgram() {
		this->m_programId = 0;
	}

	ShaderProgram::ShaderProgram(string& vertexText, string& fragmentText) {
		unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexChar = vertexText.c_str();
		glShaderSource(vertexId, 1, &vertexChar, NULL);
		glCompileShader(vertexId);
		unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentChar = fragmentText.c_str();
		glShaderSource(fragmentId, 1, &fragmentChar, NULL);
		glCompileShader(fragmentId);

		this->m_programId = glCreateProgram();
		glAttachShader(this->m_programId, vertexId);
		glAttachShader(this->m_programId, fragmentId);
		glLinkProgram(this->m_programId);
	}

	ShaderProgram::~ShaderProgram() {
	}

	void ShaderProgram::enable() {
		glUseProgram(this->m_programId);
	}

	void ShaderProgram::disable() {
		glUseProgram(0);
	}
}