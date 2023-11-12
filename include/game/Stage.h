#ifndef GAME_STAGE_H_
#define GAME_STAGE_H_

#include <game/Box.h>
#include <game/Stefan.h>
#include <graphics/Sprite.h>
#include <graphics/Text.h>
#include <graphics/Texture.h>

#include <vector>

namespace game {

class Stage {
private:
	std::vector<graphics::Sprite> stableSprites;
	std::vector<graphics::Texture> textures;
	Stefan stefan;
	std::vector<Box> boxes;
	std::vector<graphics::Text> texts;
	sf::Font font;

	int frameCounter;
	int lastFrameBoxWaveSpawn;
	bool readyToQuit = false;

	void loadTextures();
	float countStageSpeed();

	void generateBoxWave();
	void addSprite(const std::string tag, const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale);
	void addText(const std::string tag, const std::string text, const sf::Vector2f position);
public:
	Stage();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);
	bool update();
	void render(sf::RenderWindow* window);
};

}

#endif