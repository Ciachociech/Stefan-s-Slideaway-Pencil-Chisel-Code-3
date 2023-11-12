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
	this->textures.push_back(graphics::Texture("assets/sprites/stefan-head.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/gameover-frame.png"));
}

float Stage::countStageSpeed() {
	if (this->frameCounter < 1200) { return 0.7f; }
	if (this->frameCounter < 2100) { return 0.8f; }
	if (this->frameCounter < 3000) { return 0.9f; }
	if (this->frameCounter < 3900) { return 1.0f; }
	if (this->frameCounter < 4800) { return 1.1f; }
	
	return 1.2f + 0.1f * static_cast<int>((this->frameCounter - 4800) / 600);
}

void Stage::generateBoxWave() {
	std::vector<BoxLane> availableLanes{ BoxLane::left, BoxLane::middle, BoxLane::right };
	float x;

	for (int it = 0; it <= rand() % 3; ++it) {
		auto lane = rand() % availableLanes.size();
		switch (availableLanes[lane]) {
			case BoxLane::left: {
				x = 104.f;
				break;
			}
			case BoxLane::middle: default: {
				x = 228.f;
				break;
			}
			case BoxLane::right: {
				x = 324.f;
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

Stage::Stage() : stableSprites(), stefan(), frameCounter(0), font(), sound() {
	this->loadTextures();

	this->addSprite("stage", "assets/sprites/stage.png", sf::Vector2f(100.f, 0.f), 0.f, sf::Vector2f(2.f, 2.f));
	this->addSprite("rouletteApple1", "assets/sprites/apple.png", sf::Vector2f(500.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteApple2", "assets/sprites/apple.png", sf::Vector2f(500.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteApple3", "assets/sprites/apple.png", sf::Vector2f(500.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCarrot1", "assets/sprites/carrot.png", sf::Vector2f(540.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCarrot2", "assets/sprites/carrot.png", sf::Vector2f(540.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCarrot3", "assets/sprites/carrot.png", sf::Vector2f(540.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCauliflower1", "assets/sprites/cauliflower.png", sf::Vector2f(580.f, 200.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCauliflower2", "assets/sprites/cauliflower.png", sf::Vector2f(580.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("rouletteCauliflower3", "assets/sprites/cauliflower.png", sf::Vector2f(580.f, 280.f), 0.f, sf::Vector2f(1.f, 1.f));
	this->addSprite("life", "assets/sprites/stefan-head.png", sf::Vector2f(1082.f, 64.f), 0.f, sf::Vector2f(1.5f, 1.5f));
	this->addSprite("gameoverFrame", "assets/sprites/gameover-frame.png", sf::Vector2f(406.f, 240.f), 0.f, sf::Vector2f(1.f, 1.f));

	srand(time(NULL));

	this->font.loadFromFile("assets/fonts/NerkoOne-Regular.ttf");
	this->addText("scoreTitle", "Score:", sf::Vector2f(552.f, 8.f));
	this->addText("scoreValue", "0", sf::Vector2f(552.f, 64.f));
	this->addText("healthTitle", "Lifes:", sf::Vector2f(1010.f, 8.f));
	this->addText("powerUp", "Power-up: none", sf::Vector2f(552.f, 120.f));
	this->addText("gameoverTitle", "GAME OVER!", sf::Vector2f(424.f, 242.f));
	this->texts[this->texts.size() - 1].setCharacterSize(96);
	this->addText("gameoverAddText1", "press any button", sf::Vector2f(478.f, 344.f));
	this->addText("gameoverAddText2", "to quit the game", sf::Vector2f(483.f, 400.f));

	this->bufferJump.loadFromFile("assets/audio/jump.wav");
	this->bufferHit.loadFromFile("assets/audio/hit.wav");
	this->bufferOption.loadFromFile("assets/audio/option.wav");
}

void Stage::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	stefan.processInput(keyboardInput, joystickInput);
	if (this->stefan.getHealth() > 0 && this->stefan.getHeight() == 0 && std::find_if(keyboardInput.begin(), keyboardInput.end(), [](const auto& input) { return input == window::PressedKey::space; }) != keyboardInput.end()) {
		this->sound.setBuffer(this->bufferJump);
		this->sound.play();
	}
	if (this->stefan.getHealth() <= 0 && keyboardInput.size() != 0) { 
		this->sound.setBuffer(this->bufferOption);
		this->sound.play();
		this->readyToQuit = true; return; 
	}
}

bool Stage::update() {
	if (stefan.getHealth() <= 0) { 
		return !this->readyToQuit; 
	}
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
				this->sound.setBuffer(this->bufferHit);
				this->sound.play();
				stefan.damage(1);
				box.damage();
				if (box.getType() != BoxType::passUp) { 
					box.damage();
				}
			}
		}
	}

	this->boxes.erase(std::remove_if(this->boxes.begin(), this->boxes.end(), [](Box& box) { return box.readyToClean(); }), this->boxes.end());

	auto spawnFactor = static_cast<int>(120 / this->countStageSpeed());
	if (this->frameCounter > 300 && this->frameCounter - lastFrameBoxWaveSpawn >= spawnFactor) {
		this->generateBoxWave();
		lastFrameBoxWaveSpawn = this->frameCounter;
	}

	auto iter = std::find_if(this->texts.begin(), this->texts.end(), [](graphics::Text& text) { return text.getTag() == "scoreValue"; });
	iter->setTextContent(std::to_string(this->frameCounter / 10) + "0");
	frameCounter++;

	return true;
}

void Stage::render(sf::RenderWindow* window) {
	for (auto sprite : this->stableSprites) {
		if (sprite.getTag().substr(0, 8) != "gameover" || this->stefan.getHealth() <= 0) { window->draw(sprite.getSprite()); }
	}
	auto iter = std::find_if(this->stableSprites.begin(), this->stableSprites.end(), [](graphics::Sprite& sprite) { return sprite.getTag() == "life"; });
	for (auto it = stefan.getHealth(); it > 1; --it) {
		iter->move(sf::Vector2f(- 60, 0));
		window->draw(iter->getSprite());
	}
	if (stefan.getHealth() > 0) { iter->move(sf::Vector2f(60 * (stefan.getHealth() - 1), 0)); }
	else { iter->move(sf::Vector2f(2137, 0)); }

	if (this->stefan.getHealth() >= 0) {
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

	for (auto& text : this->texts) {
		if (text.getTag().substr(0, 8) != "gameover" || this->stefan.getHealth() <= 0) { window->draw(text.getText()); }
	}
}

void Stage::addSprite(const std::string tag, const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale) {
	auto textureIterator = std::find_if(this->textures.begin(), this->textures.end(), [&texturePath](graphics::Texture& texture) { return texture.getPath() == texturePath; });
	this->stableSprites.push_back(graphics::Sprite(tag));
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

void Stage::addText(const std::string tag, const std::string text, const sf::Vector2f position) {
	this->texts.push_back(graphics::Text(tag));
	this->texts[this->texts.size() - 1].setTextContent(text);
	this->texts[this->texts.size() - 1].setFont(font);
	this->texts[this->texts.size() - 1].setPosition(position);
	this->texts[this->texts.size() - 1].setFillColor(sf::Color(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128, 255));
	this->texts[this->texts.size() - 1].setCharacterSize(48);
}

}