#ifndef OSE_SHADERPROGRAM_H
#define OSE_SHADERPROGRAM_H

#include <OSE/Core.h>
#include <GLFW/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>

namespace OSE {
	class OSE_API ShaderProgram {
	public:
		ShaderProgram();
		ShaderProgram(string& vertexText, string& fragmentText);
		~ShaderProgram();

		void enable();
		void disable();

	protected:
		unsigned int m_programId;
	};
}

#endif