#include <graphics/Texture.h>

namespace graphics {

Texture::Texture(std::string path) {
	if (!this->texture.loadFromFile(path)) {
		printf("Error! Cannot load file during setting texture.");
	}
}

const sf::Texture& Texture::getTexture() { return this->texture; }

void Texture::setSmoothMode(bool smoothMode) {
	texture.setSmooth(smoothMode);
}

}