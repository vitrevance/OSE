#include "StaticMesh.h"

namespace OSE {

	StaticMesh::StaticMesh(float* vertices, unsigned int vsize, unsigned int* indices, unsigned int isize)
		: vertices(vertices), vsize(vsize), indices(indices), isize(isize) {
		this->VBO = 0;
		this->VAO = 0;
		this->EBO = 0;
	}

	StaticMesh::~StaticMesh() {
		delete[] this->vertices;
		delete[] this->indices;
	}
}