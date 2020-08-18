#ifndef OSE_MATERIAL_H
#define OSE_MATERIAL_H

#include <OSE/Core.h>

namespace OSE {
	class OSE_API Material {
	public:
		const int id;
		string text;
		std::vector<string> textures;

		Material(int id);
		~Material();
	};
}

#endif