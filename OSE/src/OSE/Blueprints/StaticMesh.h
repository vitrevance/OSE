#ifndef OSE_STATICMESH_H
#define OSE_STATICMESH_H

#include <OSE/Core.h>

namespace OSE {
	class OSE_API StaticMesh {
	public:
		StaticMesh(float* vertices, unsigned int size);
		~StaticMesh();

		unsigned int VAO, VBO, EBO;
		const float* vertices;
		const unsigned int size;
	};
}

#endif