#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = this->createShader("OSE/mainShader");

		for (std::pair<const string, StaticMesh*>& mesh : AssetSystem::instance->getStaticMeshes()) {
			this->setupStaticMesh(mesh.second);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}

	GlRenderer::~GlRenderer() {
	}

	void GlRenderer::onRenderPre() {
	}

	void GlRenderer::onRenderPost() {
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh, Transform* transform) {
		this->enableShader(this->m_mainShader);
		glBindVertexArray(mesh->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
		
		int projectionLoc = glGetUniformLocation(this->m_mainShader, "uMatProjection");
		int viewLoc = glGetUniformLocation(this->m_mainShader, "uMatView");
		int modelLoc = glGetUniformLocation(this->m_mainShader, "uMatModel");
		int rotationLoc = glGetUniformLocation(this->m_mainShader, "uMatRotation");

		vec3 transformSlice = transform->getSlicePosition(this->m_camera->getSlice());

		mat4 matModel({
			1, 0, 0, transformSlice[0],
			0, 1, 0, transformSlice[1],
			0, 0, 1, transformSlice[2],
			0, 0, 0, 1
			});

		mat4 matView = this->m_camera->getSliceView();
		mat4 matProj = this->m_camera->getProjection();
		mat4 matRotation = transform->rotation;

		glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &matProj[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &matView[0][0]);
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &matModel[0][0]);
		glUniformMatrix4fv(rotationLoc, 1, GL_TRUE, &matRotation[0][0]);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	Renderer::Shader GlRenderer::createShader(string shaderName) {
		string fragmentText = AssetSystem::instance->loadRawString(shaderName + ".frag");
		string vertexText = AssetSystem::instance->loadRawString(shaderName + ".vert");

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

		return programId;
	}

	void GlRenderer::enableShader(Renderer::Shader shader) {
		if (this->m_activeShader != shader) {
			glUseProgram(shader);
			this->m_activeShader = shader;
		}
	}

	void GlRenderer::disableShader() {
		if (this->m_activeShader != 0) {
			glUseProgram(0);
			this->m_activeShader = 0;
		}
	}

	void GlRenderer::setCurrentCamera(Camera* camera) {
		this->m_camera = camera;
	}

	void GlRenderer::setLightData(std::set<LightSource*>& lightData) {
		this->enableShader(this->m_mainShader);
		std::vector<LightSource> lights;
		int i = 0;
		for (LightSource* it : lightData) {
			if (i >= 20) {
				break;
			}
			lights.push_back(*it);
			i++;
		}
		if (i > 0) {
			int lightNumLoc = glGetUniformLocation(this->m_mainShader, "uNumLights");
			int lightsLoc = glGetUniformLocation(this->m_mainShader, "uLights");
			glUniform1i(lightNumLoc, i);
			glUniform1fv(lightsLoc, sizeof(LightSource) * i / sizeof(float), (float*)(&lights[0]));
		}
	}

	void GlRenderer::setupStaticMesh(StaticMesh* mesh) {
		glGenVertexArrays(1, &(mesh->VAO));
		glBindVertexArray(mesh->VAO);

		glGenBuffers(1, &(mesh->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vsize, mesh->vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &mesh->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->isize, mesh->indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}