#ifndef GAME_STAGE_H_
#define GAME_STAGE_H_

#include <game/Stefan.h>
#include <graphics/Sprite.h>

#include <vector>

namespace game {

class Stage {
private:
	std::vector<graphics::Sprite> stableSprites;
	Stefan stefan;
public:
	Stage();

	void processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput);

	void render(sf::RenderWindow* window);
};

}

#endif