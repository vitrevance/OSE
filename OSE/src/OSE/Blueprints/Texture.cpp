#include <OSE/Blueprints/Texture.h>

namespace OSE {

	Texture::Texture() : id(0) {
	}

	Texture::~Texture() {
		if (this->pixels != nullptr) {
			delete[] this->pixels;
		}
	}
}