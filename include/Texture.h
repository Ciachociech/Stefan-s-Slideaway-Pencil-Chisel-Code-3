#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

#include <SFML/Graphics.hpp>

class Texture {
private:
	sf::Texture texture;
public:
	Texture(std::string path);

	const sf::Texture& getTexture();
	
	void setSmoothMode(bool smoothMode);
};

#endif