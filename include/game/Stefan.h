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

	sf::Vector3f velocity;
	sf::Vector3f acceleration;
	float height;	// allow jump between 50-100
	int health;
	int blinkingFrames;

	int inputCooldown;
public:
	Stefan();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);
	void update();
	void render(sf::RenderWindow* window);

	const sf::FloatRect getHitbox();
	const float getHeight();
	const int getHealth();
	const void damage(int value);
};

}

#endif // !GAME_STEFAN_H_
