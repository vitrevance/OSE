#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		//this->m_mainShader = this->createShader("OSE/Shaders/mainShader");

		for (std::pair<const string, StaticMesh*> it : AssetSystem::instance->getStaticMeshes()) {
			this->setupStaticMesh(it.second);
		}
		for (std::pair<const string, Material*> it : AssetSystem::instance->getMaterials()) {
			for (string textureName : it.second->textures) {
				Texture* texture = AssetSystem::instance->getTexture(textureName);
				if (texture == nullptr) {
					OSE_LOG(LOG_OSE_ERROR, "GlRenderer: unresolved texture <" + textureName + ">!")
					break;
				}
				if (texture->id == 0) {
					glGenTextures(1, &texture->id);
					glBindTexture(GL_TEXTURE_2D, texture->id);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
					glGenerateMipmap(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
				this->m_textures[it.second].push_back(texture->id);
			}
		}

		setupShader();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
	}

	GlRenderer::~GlRenderer() {
		for (std::pair<const string, StaticMesh*> it : AssetSystem::instance->getStaticMeshes()) {
			glDeleteBuffers(1, &it.second->VBO);
			glDeleteBuffers(1, &it.second->VBO);
			glDeleteBuffers(1, &this->m_instanceBuffers[it.second]);
			glDeleteVertexArrays(1, &it.second->VAO);
		}
		for (std::pair<Material*, std::vector<unsigned int> > it : this->m_textures) {
			
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
			std::vector<GLTransform>& batch = this->m_batch[mesh];
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLTransform) * batch.size(), &(batch[0]), GL_DYNAMIC_DRAW);
			int VAA = 6;
			for (unsigned int i = 0; i < 5; i++) {
				glEnableVertexAttribArray(VAA + i);
				glVertexAttribPointer(VAA + i, 4, GL_FLOAT, GL_FALSE, sizeof(GLTransform), (const GLvoid*)(sizeof(GLfloat) * i * 4));
				glVertexAttribDivisor(VAA + i, 1);
			}
			/*
#define printv(v) std::cout << v.x << " " << v.y << " " << v.z << " " << v.w << std::endl
#define printt(t) printv(t.vertex); printv(t.base_1); printv(t.base_2); printv(t.base_3)
#define printm(m) for (int MII = 0; MII < 16; MII++) {std::cout << m[MII / 4][MII % 4] << " "; if (MII % 4 == 0) {std::cout << std::endl;}}
*/
			int projectionLoc = glGetUniformLocation(this->m_mainShader, "uMatProjection");
			int viewLoc = glGetUniformLocation(this->m_mainShader, "uMatView");
			int wProjLoc = glGetUniformLocation(this->m_mainShader, "uFWProjection");
			int materialIdLoc = glGetUniformLocation(this->m_mainShader, "uMaterialID");

			mat4 matView = this->m_camera->getView();
			mat4 matProj = this->m_camera->getProjection();
			Material* material = AssetSystem::instance->getMeshMaterial(mesh);

			glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &matProj[0][0]);
			glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &matView[0][0]);
			glUniform1f(wProjLoc, this->m_camera->getTransform().position.w);
			glUniform1i(materialIdLoc, material == nullptr ? 0 : material->id);

			std::vector<unsigned int>& textureId = this->m_textures[material];
			for (int i = 0; i < textureId.size(); i++) {
				glUniform1i(glGetUniformLocation(this->m_mainShader, ("texture" + std::to_string(i)).c_str()), i);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureId[i]);
			}

			//glDrawElements(GL_TRIANGLES, mesh->isize, GL_UNSIGNED_INT, 0);
			//glDrawElementsInstanced(GL_TRIANGLES, mesh->isize, GL_UNSIGNED_INT, 0, this->m_batch[mesh].size());
			glDrawArraysInstanced(GL_POINTS, 0, mesh->cells.size(), this->m_batch[mesh].size());
		}
		glBindVertexArray(0);
	}

	void GlRenderer::drawStaticMesh(StaticMesh* mesh, Transform* transform) {
		GLTransform batch;
		batch.translation = transform->position;
		batch.transform = transform->toMatrixTransposed();
		this->m_drawQuery.insert(mesh);
		this->m_batch[mesh].push_back(batch);
	}

	Renderer::Shader GlRenderer::createShader(string shaderName) {
		string fragmentText = AssetSystem::instance->loadRawString(shaderName + ".frag");
		string vertexText = AssetSystem::instance->loadRawString(shaderName + ".vert");
		string geometryText = AssetSystem::instance->loadRawString(shaderName + ".geom");

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

		unsigned int geometryId = 0;
		if (geometryText.size() > 0) {
			geometryId = glCreateShader(GL_GEOMETRY_SHADER);
			const char* geometryChar = geometryText.c_str();
			glShaderSource(geometryId, 1, &geometryChar, NULL);
			glCompileShader(geometryId);

			glGetShaderiv(geometryId, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(geometryId, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(geometryId, length, &length, &error[0]);
				OSE_LOG(LOG_OSE_ERROR, string(&error[0]))
					glDeleteShader(geometryId);

				return 0;
			}
		}

		Renderer::Shader programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		if (geometryId > 0) {
			glAttachShader(programId, geometryId);
		}
		glLinkProgram(programId);
		glValidateProgram(programId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		if (geometryId > 0) {
			glDeleteShader(geometryId);
		}

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
			mat4 light(it->transform.toMatrix());
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
		/*
		glGenBuffers(1, &(mesh->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tetrahedron) * mesh->cells.size(), &mesh->cells[0], GL_STATIC_DRAW);
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
		*/

		glGenBuffers(1, &(mesh->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tetrahedron) * mesh->cells.size(), &mesh->cells[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), (void*)offsetof(Tetrahedron, base_1));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), (void*)offsetof(Tetrahedron, base_2));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), (void*)offsetof(Tetrahedron, base_3));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), (void*)offsetof(Tetrahedron, uvvertex));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Tetrahedron), (void*)offsetof(Tetrahedron, uvbase_2));
		unsigned int MBO;
		glGenBuffers(1, &MBO);
		this->m_instanceBuffers[mesh] = MBO;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Renderer::Shader GlRenderer::createShader(string vertexText, string geometryText, string fragmentText) {
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

		unsigned int geometryId = 0;
		if (geometryText.size() > 0) {
			geometryId = glCreateShader(GL_GEOMETRY_SHADER);
			const char* geometryChar = geometryText.c_str();
			glShaderSource(geometryId, 1, &geometryChar, NULL);
			glCompileShader(geometryId);

			glGetShaderiv(geometryId, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(geometryId, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(geometryId, length, &length, &error[0]);
				OSE_LOG(LOG_OSE_ERROR, string(&error[0]))
					glDeleteShader(geometryId);

				return 0;
			}
		}

		Renderer::Shader programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		if (geometryId > 0) {
			glAttachShader(programId, geometryId);
		}
		glLinkProgram(programId);
		glValidateProgram(programId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		if (geometryId > 0) {
			glDeleteShader(geometryId);
		}

		return programId;
	}

	void GlRenderer::setupShader() {
		string vertexText = AssetSystem::instance->loadRawString("OSE/Shaders/mainShader.vert");
		string geometryText = AssetSystem::instance->loadRawString("OSE/Shaders/mainShader.geom");
		string fragmentText = AssetSystem::instance->loadRawString("OSE/Shaders/mainShader.frag");

		string materialSwitch = "vec4 applyMaterial(int id) {switch(id) {";
		string materialText;
		
		std::map<string, Material*>& materials = AssetSystem::instance->getMaterials();
		int maxTextureCount = 0;
		for (std::pair<const string, Material*>& it : materials) {
			Material* m = it.second;
			materialSwitch += "case " + std::to_string(m->id) + ": return material" + std::to_string(m->id) + "();";
			materialText += m->text;
			if (m->textures.size() > maxTextureCount) {
				maxTextureCount = m->textures.size();
			}
		}
		materialSwitch += "}return vec4(1);}";

		string uniformTextures;
		for (int i = 0; i < maxTextureCount; i++) {
			uniformTextures += "uniform sampler2D texture" + std::to_string(i) + ";\n";
		}

		fragmentText += "\n" + uniformTextures + materialText + materialSwitch;

		this->m_mainShader = createShader(vertexText, geometryText, fragmentText);
	}
}