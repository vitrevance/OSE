#include <OSE/Blueprints/Texture.hpp>

namespace OSE {

Texture::Texture()
    : id(0) {
}

Texture::~Texture() {
  if (this->pixels != nullptr) {
    delete[] this->pixels;
  }
}
}  // namespace OSE