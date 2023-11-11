#include <window/KeyboardInput.h>

#include <SFML/Window.hpp>

namespace window {

KeyboardInput::KeyboardInput() {}

std::vector<PressedKey> KeyboardInput::getInput() {
	std::vector<PressedKey> input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num8)) {
		input.push_back(PressedKey::up);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num2)) {
		input.push_back(PressedKey::down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num4)) {
		input.push_back(PressedKey::left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num6)) {
		input.push_back(PressedKey::right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num3)) {
		input.push_back(PressedKey::space);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num1)) {
		input.push_back(PressedKey::shift);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num0)) {
		input.push_back(PressedKey::control);
	}

	return input;
}



}