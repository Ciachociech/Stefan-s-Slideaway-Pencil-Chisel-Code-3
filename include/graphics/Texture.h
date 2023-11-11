#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include <string>

#include <SFML/Graphics.hpp>

namespace graphics {

class Texture {
private:
	sf::Texture texture;
	std::string path;
public:
	Texture(std::string path);

	const sf::Texture& getTexture();
	const std::string& getPath();

	void setSmoothMode(bool smoothMode);
};

}

#endif