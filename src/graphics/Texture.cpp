#include <graphics/Texture.h>

namespace graphics {

Texture::Texture(std::string path) : path(std::move(path)) {
	if (!this->texture.loadFromFile(this->path)) {
		printf("Error! Cannot load file during setting texture.");
	}
}

const sf::Texture& Texture::getTexture() { 
	return this->texture; 
}

const std::string& Texture::getPath() {
	return this->path;
}

void Texture::setSmoothMode(bool smoothMode) {
	texture.setSmooth(smoothMode);
}

}