#include <game/Stefan.h>

#include <algorithm>

#include <graphics/Texture.h>

namespace game {

Stefan::Stefan() : texture("assets/sprites/bulonais.png"), sprite() {
	this->sprite.setTexture(texture.getTexture());
}

void Stefan::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::down) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::down) != joystickInput.end()) {
		this->sprite.move(sf::Vector2f(0, 2));
	} else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::up) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::up) != joystickInput.end()) {
		this->sprite.move(sf::Vector2f(0, -2));
	}
	if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::left) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::left) != joystickInput.end()) {
		this->sprite.move(sf::Vector2f(-2, 0));
	}
	else if (std::find(keyboardInput.begin(), keyboardInput.end(), window::PressedKey::right) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), window::PressedButton::right) != joystickInput.end()) {
		this->sprite.move(sf::Vector2f(2, 0));
	}
}

void Stefan::update() {
	const sf::FloatRect movementRect = sf::FloatRect(32, 0, 288, 120);
	const sf::Vector2f actualPosition = this->sprite.getSprite().getPosition();
	const sf::Vector2u textureSize = this->sprite.getSprite().getTexture()->getSize();
	if (actualPosition.x < movementRect.left) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left, actualPosition.y));
	} else if (actualPosition.x > movementRect.left + movementRect.width - textureSize.x) {
		this->sprite.setPosition(sf::Vector2f(movementRect.left + movementRect.width - textureSize.x, actualPosition.y));
	}
	if (actualPosition.y < movementRect.top) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top));
	}
	else if (actualPosition.y > movementRect.top + movementRect.height - textureSize.y) {
		this->sprite.setPosition(sf::Vector2f(actualPosition.x, movementRect.top + movementRect.height - textureSize.y));
	}
}

void Stefan::render(sf::RenderWindow* window) {
	window->draw(this->sprite.getSprite());
}

}