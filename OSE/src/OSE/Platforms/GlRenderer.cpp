#include "GlRenderer.h"

namespace OSE {

	GlRenderer::GlRenderer() {
		this->m_mainShader = AssetSystem::instance->loadShader("OSE/mainShader");
		this->m_mainShader.enable();
	}

	GlRenderer::~GlRenderer() {
		this->m_mainShader.disable();
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
}