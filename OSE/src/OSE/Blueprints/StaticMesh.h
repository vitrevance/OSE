#ifndef OSE_STATICMESH_H
#define OSE_STATICMESH_H

#include <OSE/Core.h>

namespace OSE {
	class OSE_API StaticMesh {
	public:
		StaticMesh();
		~StaticMesh();

		unsigned int vertexBuffer;
		t_float* vertices;
		unsigned int* indices;
	};
}

#endif