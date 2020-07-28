#include "StaticMesh.h"

namespace OSE {

	StaticMesh::StaticMesh() {
		this->VBO = 0;
		this->VAO = 0;
		this->EBO = 0;
	}

	StaticMesh::~StaticMesh() {
	}
}