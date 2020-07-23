#ifndef OSE_RENDERER_H
#define OSE_RENDERER_H

#include <OSE/Core.h>
#include <OSE/Blueprints/StaticMesh.h>

namespace OSE {
	class OSE_API Renderer {
	public:
		virtual ~Renderer();

		virtual void drawStaticMesh(StaticMesh* mesh) = 0;
	protected:
		Renderer();
	};
}

#endif