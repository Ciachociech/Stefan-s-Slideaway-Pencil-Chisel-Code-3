#ifndef GRAPHICS_SPRITE_H_
#define GRAPHICS_SPRITE_H_

#include <SFML/Graphics.hpp>

namespace graphics {

class Sprite {
private:
	sf::Sprite sprite;
public:
	Sprite();

	void setTexture(const sf::Texture& texture);
	void setTexture(const sf::Texture& texture, const sf::IntRect textureRect);
	void setTextureRect(const sf::IntRect textureRect);
	void setColor(const sf::Color color);
	void setPosition(const sf::Vector2f position);
	void move(const sf::Vector2f offset);
	void setRotation(const float rotation);
	void rotate(const float offset);
	void setScale(const sf::Vector2f scale);
	void scale(const sf::Vector2f factor);
	void setOriginCenter();

	const sf::Sprite& getSprite();
};

}

#endif