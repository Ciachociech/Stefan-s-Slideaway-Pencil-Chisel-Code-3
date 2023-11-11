#ifndef GAME_STEFAN_H_
#define GAME_STEFAN_H_

#include <SFML/Graphics.hpp>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>
#include <window/JoystickInput.h>
#include <window/KeyboardInput.h>

namespace game {

class Stefan {
private:
	graphics::Texture texture;
	graphics::Sprite sprite;
public:
	Stefan();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);
	void update();

	void render(sf::RenderWindow* window);
};

}

#endif // !GAME_STEFAN_H_
