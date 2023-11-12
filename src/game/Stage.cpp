#include <game/Stage.h>

#include <algorithm>
#include <ctime>
#include <random>

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

float Stage::countStageSpeed() {
	if (this->frameCounter < 900) { return 0.5f; }
	if (this->frameCounter < 1800) { return 0.6f; }
	if (this->frameCounter < 2700) { return 0.7f; }
	if (this->frameCounter < 3600) { return 0.8f; }
	if (this->frameCounter < 4500) { return 0.9f; }
	if (this->frameCounter < 5400) { return 1.0f; }
	if (this->frameCounter < 6000) { return 1.1f; }
	if (this->frameCounter < 6600) { return 1.2f; }
	if (this->frameCounter < 7200) { return 1.3f; }
	if (this->frameCounter < 7800) { return 1.4f; }
	if (this->frameCounter < 8400) { return 1.5f; }
	if (this->frameCounter < 9000) { return 1.6f; }
	if (this->frameCounter < 9600) { return 1.7f; }
	if (this->frameCounter < 10200) { return 1.8f; }
	if (this->frameCounter < 10800) { return 1.9f; }

	return 2.0f;
}

void Stage::generateBoxWave() {
	std::vector<BoxLane> availableLanes{ BoxLane::left, BoxLane::middle, BoxLane::right };
	float x;

	for (int it = 0; it <= rand() % 3; ++it) {
		auto lane = rand() % availableLanes.size();
		switch (availableLanes[lane]) {
			case BoxLane::left: {
				x = 4.f;
				break;
			}
			case BoxLane::middle: default: {
				x = 128.f;
				break;
			}
			case BoxLane::right: {
				x = 224.f;
				break;
			}
		}
		availableLanes.erase(availableLanes.begin() + lane);

		auto type = rand() % (it == 2 ? 2 : 3);
		switch (type) {
			case 0:
			{
				boxes.push_back(game::Box(sf::Vector2f(x, 658.f), BoxType::passUp, this->textures[6].getTexture()));
				break;
			}
			case 1: default:
			{
				boxes.push_back(game::Box(sf::Vector2f(x, 638.f), BoxType::passDown, this->textures[5].getTexture()));
				break;
			}
			case 2:
			{
				boxes.push_back(game::Box(sf::Vector2f(x, 638.f), BoxType::noPass, this->textures[4].getTexture()));
				break;
			}
		}
	}
}

Stage::Stage() : stableSprites(), stefan(), frameCounter(0) {
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

	srand(time(NULL));
}

void Stage::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	stefan.processInput(keyboardInput, joystickInput);
}

void Stage::update() {
	stefan.update();

	for (auto& box : this->boxes) {
		box.update(this->countStageSpeed());

		bool intersectHeight;
		switch (box.getType()) {
		case BoxType::passUp: {
			intersectHeight = box.getHealth() == 2 && stefan.getHeight() == 0;
			break;
		}
		case BoxType::passDown: {
			intersectHeight = stefan.getHeight() > 0;
			break;
		}
		default: {
			intersectHeight = true;
			break;
		}
		}
		if (box.getHitbox().intersects(stefan.getHitbox())) {
			if (box.getType() == BoxType::passUp && box.getHealth() == 2) { 
				box.damage(); 
			}
			if (intersectHeight) {
				stefan.damage(1);
				box.damage();
				if (box.getType() != BoxType::passUp) { 
					box.damage();
				}
			}
		}
	}

	this->boxes.erase(std::remove_if(this->boxes.begin(), this->boxes.end(), [](Box& box) { return box.readyToClean(); }), this->boxes.end());

	if (frameCounter % static_cast<int>(120 / this->countStageSpeed()) == 0) {
		this->generateBoxWave();
	}

frameCounter++;
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