#ifndef OSE_TEXTURE_H
#define OSE_TEXTURE_H

#include <OSE/Core.h>

namespace OSE{
	class OSE_API Texture {
	public:
		unsigned int id;
		int width, height;
		unsigned char* pixels;

		Texture();
		~Texture();
	};
}

#endif