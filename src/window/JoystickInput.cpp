#include <window/JoystickInput.h>

#include <SFML/Window.hpp>

namespace window {

JoystickInput::JoystickInput() {}

std::vector<PressedButton> JoystickInput::getInput() {
	if (!sf::Joystick::isConnected(0)) {
		return {};
	}

	std::vector<PressedButton> input;

	if (sf::Joystick::hasAxis(0, sf::Joystick::X) || sf::Joystick::hasAxis(0, sf::Joystick::PovX)) {
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -0.1 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -0.1) {
			input.push_back(PressedButton::left);
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 0.1 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 0.1) {
			input.push_back(PressedButton::right);
		}
	}
	if (sf::Joystick::hasAxis(0, sf::Joystick::Y) || sf::Joystick::hasAxis(0, sf::Joystick::PovY)) {
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -0.1 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 0.1) {
			input.push_back(PressedButton::up);
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 0.1 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -0.1) {
			input.push_back(PressedButton::down);
		}
	}
	if (sf::Joystick::isButtonPressed(0, 3) || sf::Joystick::isButtonPressed(0, 5)) {
		input.push_back(PressedButton::Y);
	}
	if (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 4)) {
		input.push_back(PressedButton::A);
	}
	if (sf::Joystick::isButtonPressed(0, 1)) {
		input.push_back(PressedButton::B);
	}

	return input;
}



}