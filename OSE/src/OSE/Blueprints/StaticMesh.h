#ifndef OSE_STATICMESH_H
#define OSE_STATICMESH_H

#include <OSE/Core.h>

namespace OSE {
	struct OSE_API Vertex {
		float x, y, z, normx, normy, normz;
	};

	class OSE_API StaticMesh {
	public:
		StaticMesh(Vertex* vertices, unsigned int vsize, unsigned int* indices, unsigned int isize);
		~StaticMesh();

		unsigned int VAO, VBO, EBO;
		const unsigned int vsize;
		const unsigned int isize;
		const Vertex* vertices;
		const unsigned int* indices;
	};
}

#endif