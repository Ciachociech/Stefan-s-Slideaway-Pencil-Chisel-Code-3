#include <game/Stage.h>

namespace game {

Stage::Stage() : stableSprites(), stefan() {}

void Stage::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	stefan.processInput(keyboardInput, joystickInput);
}

void Stage::render(sf::RenderWindow* window) {
	for (auto sprite : this->stableSprites) {
		window->draw(sprite.getSprite());
	}
	stefan.render(window);
}



}