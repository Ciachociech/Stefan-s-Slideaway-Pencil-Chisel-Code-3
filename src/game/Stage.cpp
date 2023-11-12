#include <game/Stage.h>

#include <algorithm>

namespace game {
	
void Stage::loadTextures() {
	this->textures.push_back(graphics::Texture("assets/sprites/stage.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/apple.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/carrot.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/cauliflower.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-avoid.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-down.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-up.png"));
}

Stage::Stage() : stableSprites(), stefan() {
	this->loadTextures();

	this->addSprite("assets/sprites/stage.png", sf::Vector2f(0.f, 0.f), 0.f, sf::Vector2f(2.f, 2.f));
	this->addSprite("assets/sprites/apple.png", sf::Vector2f(400.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/apple.png", sf::Vector2f(400.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/apple.png", sf::Vector2f(400.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/carrot.png", sf::Vector2f(440.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/carrot.png", sf::Vector2f(440.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/carrot.png", sf::Vector2f(440.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/cauliflower.png", sf::Vector2f(480.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/cauliflower.png", sf::Vector2f(480.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("assets/sprites/cauliflower.png", sf::Vector2f(480.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));

	boxes.push_back(game::Box(sf::Vector2f(4.f, 658.f), BoxType::passUp, this->textures[6].getTexture()));
	boxes.push_back(game::Box(sf::Vector2f(128.f, 638.f), BoxType::passDown, this->textures[5].getTexture()));
	boxes.push_back(game::Box(sf::Vector2f(224.f, 638.f), BoxType::noPass, this->textures[4].getTexture()));
}

void Stage::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	stefan.processInput(keyboardInput, joystickInput);
}

void Stage::update() {
	stefan.update();
	for (auto& box : this->boxes) {
		box.update(1.0);
	}
}

void Stage::render(sf::RenderWindow* window) {
	for (auto sprite : this->stableSprites) {
		window->draw(sprite.getSprite());
	}
	for (auto& box : this->boxes) {
		if (box.getType() == BoxType::passUp) {
			box.render(window);
		}
	}
	stefan.render(window);
	for (auto& box : this->boxes) {
		if (box.getType() != BoxType::passUp) {
			box.render(window);
		}
	}
}

void Stage::addSprite(const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale) {
	auto textureIterator = std::find_if(this->textures.begin(), this->textures.end(), [&texturePath](graphics::Texture& texture) { return texture.getPath() == texturePath; });
	this->stableSprites.push_back(graphics::Sprite());
	if (textureIterator == this->textures.end()) {
		this->textures.push_back(graphics::Texture(texturePath));
		this->stableSprites[this->stableSprites.size() - 1].setTexture(this->textures[this->textures.size() - 1].getTexture());
	}
	else {
		this->stableSprites[this->stableSprites.size() - 1].setTexture(textureIterator->getTexture());
	}

	this->stableSprites[this->stableSprites.size() - 1].setPosition(position);
	this->stableSprites[this->stableSprites.size() - 1].setRotation(rotation);
	this->stableSprites[this->stableSprites.size() - 1].setScale(scale);
}

}