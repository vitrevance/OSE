#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = this->createShader("OSE/Shaders/mainShader");

		for (std::pair<const string, StaticMesh*> it : AssetSystem::instance->getStaticMeshes()) {
			this->setupStaticMesh(it.second);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	GlRenderer::~GlRenderer() {
		for (std::pair<const string, StaticMesh*> it : AssetSystem::instance->getStaticMeshes()) {
			glDeleteBuffers(1, &it.second->VBO);
			glDeleteBuffers(1, &it.second->VBO);
			glDeleteBuffers(1, &this->m_instanceBuffers[it.second]);
			glDeleteVertexArrays(1, &it.second->VAO);
		}
	}

	void GlRenderer::onRenderPre() {
		this->m_batch.clear();
		this->m_drawQuery.clear();
	}

	void GlRenderer::onRenderPost() {
		this->enableShader(this->m_mainShader);

		for (StaticMesh* mesh : this->m_drawQuery) {

			glBindVertexArray(mesh->VAO);

			unsigned int MBO = this->m_instanceBuffers[mesh];
			glBindBuffer(GL_ARRAY_BUFFER, MBO);
			std::vector<mat4>& batch = this->m_batch[mesh];
			glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * batch.size(), &(batch[0]), GL_DYNAMIC_DRAW);
			for (unsigned int i = 0; i < 4; i++) {
				glEnableVertexAttribArray(2 + i);
				glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (const GLvoid*)(sizeof(GLfloat) * i * 4));
				glVertexAttribDivisor(2 + i, 1);
			}

			int projectionLoc = glGetUniformLocation(this->m_mainShader, "uMatProjection");
			int viewLoc = glGetUniformLocation(this->m_mainShader, "uMatView");
			int wProjLoc = glGetUniformLocation(this->m_mainShader, "uFWProjection");

			mat4 matView = this->m_camera->getView();
			mat4 matProj = this->m_camera->getProjection();

			glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &matProj[0][0]);
			glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &matView[0][0]);
			glUniform1f(wProjLoc, this->m_camera->getTransform().position.w);

			//glDrawElements(GL_TRIANGLES, mesh->isize, GL_UNSIGNED_INT, 0);
			glDrawElementsInstanced(GL_TRIANGLES, mesh->isize, GL_UNSIGNED_INT, 0, this->m_batch[mesh].size());
			glBindVertexArray(0);
		}
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh, Transform* transform) {
		/*
		vec4 tPos = transform->position * transform->rotation;
		vec4 cPos = this->m_camera->getTransform().position;
		mat<3, 4> proj4D({
			1 / (cPos.w - tPos.w), 0, 0, 0,
			0, 1 / (cPos.w - tPos.w), 0, 0,
			0, 0, 1 / (cPos.w - tPos.w), 0
			});
		vec3 pPos = proj4D * tPos;
		*/
		/*mat4 matModel({
			1 / (cPos.w - tPos.w), 0, 0, tPos.x,
			0, 1 / (cPos.w - tPos.w), 0, tPos.y,
			0, 0, 1 / (cPos.w - tPos.w), tPos.z,
			0, 0, 0, 1
			});*/
		vec4 tPos = transform->position * transform->rotation;
		mat4 matModel({
			1, 0, 0, tPos.x,
			0, 1, 0, tPos.y,
			0, 0, 1, tPos.z,
			0, 0, 0, tPos.w
			});
		this->m_drawQuery.insert(mesh);
		this->m_batch[mesh].push_back((transform->rotation * matModel).transposed());
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
		std::vector<mat4> lights;
		int i = 0;
		for (LightSource* it : lightData) {
			if (i >= 20) {
				break;
			}
			mat4 light(it->transform.rotation);
			light[3][0] = it->color[0];
			light[3][1] = it->color[1];
			light[3][2] = it->color[2];
			light[0][3] = it->transform.position[0];
			light[1][3] = it->transform.position[1];
			light[2][3] = it->transform.position[2];
			light[3][3] = it->type;
			lights.push_back(light);
			i++;
		}
		int lightNumLoc = glGetUniformLocation(this->m_mainShader, "uNumLights");
		glUniform1i(lightNumLoc, i);
		if (i > 0) {
			int lightsLoc = glGetUniformLocation(this->m_mainShader, "uLights");
			glUniformMatrix4fv(lightsLoc, i, GL_TRUE, &lights[0][0][0]);
		}
	}

	void GlRenderer::setupStaticMesh(StaticMesh* mesh) {
		glGenVertexArrays(1, &(mesh->VAO));
		glBindVertexArray(mesh->VAO);

		glGenBuffers(1, &(mesh->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vsize, mesh->vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
		unsigned int MBO;
		glGenBuffers(1, &MBO);
		this->m_instanceBuffers[mesh] = MBO;
		glGenBuffers(1, &mesh->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->isize, mesh->indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}