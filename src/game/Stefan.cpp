#include <game/Stefan.h>

#include <algorithm>

#include <graphics/Texture.h>

namespace game {

namespace {

constexpr float maxVelocity = 10.f;

}

Stefan::Stefan() : texture("assets/sprites/bulonais.png"), sprite(), velocity(), height(0), health(3) {
	this->sprite.setTexture(texture.getTexture());
	this->sprite.setPosition(sf::Vector2f(260, 32));
	this->sprite.setOriginCenter();
}

void Stefan::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::down) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::down) != joystickInput.end()) {
		this->acceleration.y = 2;
	} else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::up) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::up) != joystickInput.end()) {
		this->acceleration.y = -2;
	}
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::left) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::left) != joystickInput.end()) {
		this->acceleration.x = -2;
	}
	else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::right) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::right) != joystickInput.end()) {
		this->acceleration.x = 2;
	}
	if (this->getHeight() == 0, std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::space) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::Y) != joystickInput.end()) {
		this->acceleration.z = 2;
	}
}

void Stefan::update() {
	this->velocity.x += this->acceleration.x;
	this->velocity.y += this->acceleration.y;
	this->velocity.z += this->acceleration.z;

	this->acceleration.x = 0;
	this->acceleration.y = 0;
	if (this->acceleration.z > 0.0) {
		this->acceleration.z -= 0.1;
	} else {
		this->acceleration.z -= 0.51;
	}

	const float speedRatio = std::sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) / maxVelocity;
	if (speedRatio > 1.f) {
		this->velocity.x /= speedRatio;
		this->velocity.y /= speedRatio;
	}

	const sf::Vector2f movement = sf::Vector2f(this->velocity.x, this->velocity.y);
	this->sprite.move(movement);
	this->height += this->velocity.z;

	this->velocity.x *= 0.95;
	this->velocity.y *= 0.98;
	this->velocity.z *= 0.8;

	const sf::FloatRect movementRect = sf::FloatRect(132, 0, 288, 180);
	const sf::Vector2f actualPosition = this->sprite.getSprite().getPosition();
	const sf::Vector2u textureSize = this->sprite.getSprite().getTexture()->getSize();
	if (actualPosition.x - textureSize.x / 2 < movementRect.left) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left + textureSize.x / 2, actualPosition.y));
		this->velocity.x = 0.0;
	} else if (actualPosition.x > movementRect.left + movementRect.width - textureSize.x / 2) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left + movementRect.width - textureSize.x / 2, actualPosition.y));
		this->velocity.x = 0.0;
	}
	if (actualPosition.y - textureSize.y / 2 < movementRect.top) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top + textureSize.y / 2));
		this->velocity.y = 0.0;
	}
	else if (actualPosition.y > movementRect.top + movementRect.height - textureSize.y / 2) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top + movementRect.height - textureSize.y / 2));
		this->velocity.y = 0.0;
	}
	if (this->height < 0) { 
		this->height = 0; 
		this->velocity.z = 0;
		this->acceleration.z = 0;
	}

	this->sprite.setScale(sf::Vector2f(1.0 + 0.001 * this->height, 1.0 + 0.001 * this->height));
}

void Stefan::render(sf::RenderWindow* window) {
	window->draw(this->sprite.getSprite());
}

const float Stefan::getHeight() {
	return this->height;
}

const sf::FloatRect Stefan::getHitbox() {
	return this->sprite.getSprite().getGlobalBounds();
}

const int Stefan::getHealth() {
	return this->health;
}

const void Stefan::damage(int value) {
	this->health -= value;
}

}