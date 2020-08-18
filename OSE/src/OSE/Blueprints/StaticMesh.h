#ifndef OSE_STATICMESH_H
#define OSE_STATICMESH_H

#include <OSE/Core.h>
#include <OSE/Math/Vecmath.h>

namespace OSE {
	struct OSE_API Tetrahedron {
		vec4 vertex;
		vec4 base_1;
		vec4 base_2;
		vec4 base_3;
		vec2 uvvertex;
		vec2 uvbase_1;
		vec2 uvbase_2;
		vec2 uvbase_3;
	};

	class OSE_API StaticMesh {
	public:
		StaticMesh();
		~StaticMesh();

		unsigned int VAO, VBO;
		std::vector<Tetrahedron> cells;
	};
}

#endif