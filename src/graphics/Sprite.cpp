#include <graphics/Sprite.h>

namespace graphics {

Sprite::Sprite(const std::string tag) : sprite(), tag(tag) {}

void Sprite::setTexture(const sf::Texture& texture) {
	this->sprite.setTexture(texture);
}

void Sprite::setTexture(const sf::Texture& texture, const sf::IntRect textureRect) {
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(textureRect);
}

void Sprite::setTextureRect(const sf::IntRect textureRect) {
	if (this->sprite.getTexture() != NULL) {
		this->sprite.setTextureRect(textureRect);
	}
}

void Sprite::setColor(const sf::Color color) {
	this->sprite.setColor(color);
}

void Sprite::setPosition(const sf::Vector2f position) {
	this->sprite.setPosition(position);
}

void Sprite::move(const sf::Vector2f offset) {
	this->sprite.move(offset);
}

void Sprite::setRotation(const float rotation) {
	this->sprite.setRotation(rotation);
}

void Sprite::rotate(const float offset) {
	this->sprite.rotate(offset);
}

void Sprite::setScale(const sf::Vector2f scale) {
	this->sprite.setScale(scale);
}

void Sprite::scale(const sf::Vector2f factor) {
	this->sprite.scale(factor);
}

void Sprite::setOriginCenter() {
	const auto bounds = this->sprite.getLocalBounds().getSize();
	this->sprite.setOrigin(sf::Vector2f(bounds.x / 2, bounds.y / 2));
}

const sf::Sprite& Sprite::getSprite() {
	return this->sprite;
}

const std::string Sprite::getTag() {
	return this->tag;
}

}