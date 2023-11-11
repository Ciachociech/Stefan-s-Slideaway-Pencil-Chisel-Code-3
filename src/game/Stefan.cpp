#include <game/Stefan.h>

#include <algorithm>

#include <graphics/Texture.h>

namespace game {

namespace {

constexpr float maxVelocity = 10.f;

}

Stefan::Stefan() : texture("assets/sprites/bulonais.png"), sprite(), velocity() {
	this->sprite.setTexture(texture.getTexture());
}

void Stefan::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::down) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::down) != joystickInput.end()) {
		this->accuracy.y = 2;
	} else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::up) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::up) != joystickInput.end()) {
		this->accuracy.y = -2;
	}
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::left) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::left) != joystickInput.end()) {
		this->accuracy.x = -2;
	}
	else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::right) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::right) != joystickInput.end()) {
		this->accuracy.x = 2;
	}
}

void Stefan::update() {
	this->velocity.x += this->accuracy.x;
	this->velocity.y += this->accuracy.y;

	this->accuracy.x = 0;
	this->accuracy.y = 0;

	const float speedRatio = std::sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) / maxVelocity;
	if (speedRatio > 1.f) {
		this->velocity.x /= speedRatio;
		this->velocity.y /= speedRatio;
	}

	const sf::Vector2f movement = this->velocity;
	this->sprite.move(movement);

	this->velocity.x *= 0.9;
	this->velocity.y *= 0.98;

	const sf::FloatRect movementRect = sf::FloatRect(32, 0, 288, 120);
	const sf::Vector2f actualPosition = this->sprite.getSprite().getPosition();
	const sf::Vector2u textureSize = this->sprite.getSprite().getTexture()->getSize();
	if (actualPosition.x < movementRect.left) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left, actualPosition.y));
		this->velocity.x = 0.0;
	} else if (actualPosition.x > movementRect.left + movementRect.width - textureSize.x) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left + movementRect.width - textureSize.x, actualPosition.y));
		this->velocity.x = 0.0;
	}
	if (actualPosition.y < movementRect.top) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top));
		this->velocity.y = 0.0;
	}
	else if (actualPosition.y > movementRect.top + movementRect.height - textureSize.y) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top + movementRect.height - textureSize.y));
		this->velocity.y = 0.0;
	}
}

void Stefan::render(sf::RenderWindow* window) {
	window->draw(this->sprite.getSprite());
}

}