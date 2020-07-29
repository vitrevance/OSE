#include "StaticMesh.h"

namespace OSE {

	StaticMesh::StaticMesh(float* vertices, unsigned int size) : vertices(vertices), size(size) {
		this->VBO = 0;
		this->VAO = 0;
		this->EBO = 0;
	}

	StaticMesh::~StaticMesh() {
	}
}