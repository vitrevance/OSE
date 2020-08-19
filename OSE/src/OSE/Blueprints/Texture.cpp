#include <OSE/Blueprints/Texture.h>

namespace OSE {

	Texture::Texture() {
	}

	Texture::~Texture() {
		if (this->pixels != nullptr) {
			delete[] this->pixels;
		}
	}
}