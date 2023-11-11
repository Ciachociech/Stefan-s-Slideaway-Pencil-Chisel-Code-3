#ifndef GAME_STAGE_H_
#define GAME_STAGE_H_

#include <game/Stefan.h>
#include <graphics/Sprite.h>
#include <graphics/Texture.h>

#include <vector>

namespace game {

class Stage {
private:
	std::vector<graphics::Sprite> stableSprites;
	std::vector<graphics::Texture> textures;
	Stefan stefan;

	void loadTextures();
public:
	Stage();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);
	void update();
	void render(sf::RenderWindow* window);

	void addSprite(const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale);
};

}

#endif