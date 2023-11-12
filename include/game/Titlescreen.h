#ifndef GAME_TITLESCREEN_H_
#define GAME_TITLESCREEN_H_

#include <string>
#include <vector>

#include <graphics/Sprite.h>
#include <graphics/Text.h>
#include <graphics/Texture.h>
#include <window/KeyboardInput.h>
#include <window/JoystickInput.h>

namespace game {

class Titlescreen {
private:
	std::vector<graphics::Sprite> stableSprites;
	std::vector<graphics::Texture> textures;
	std::vector<graphics::Text> texts;
	sf::Font font;

	int frameCounter;
	bool readyToQuit = false;

	void loadTextures();

	void addSprite(const std::string tag, const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale);
	void addText(const std::string tag, const std::string text, const sf::Vector2f position);
public:
	Titlescreen();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);
	bool update();
	void render(sf::RenderWindow* window);

	static std::string lang;
};

}

#endif // !GAME_TITLESCREEN_H_
