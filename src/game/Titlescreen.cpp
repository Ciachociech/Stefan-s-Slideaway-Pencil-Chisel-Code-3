#include <game/Titlescreen.h>

namespace game {

void Titlescreen::loadTextures() {
	this->textures.push_back(graphics::Texture("assets/sprites/logoEN.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/logoPL.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/bulonais.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-avoid.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-down.png"));
	this->textures.push_back(graphics::Texture("assets/sprites/box-up.png"));
}

void Titlescreen::addSprite(const std::string tag, const std::string texturePath, const sf::Vector2f position, const float rotation, const sf::Vector2f scale) {
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

void Titlescreen::addText(const std::string tag, const std::string text, const sf::Vector2f position) {
	this->texts.push_back(graphics::Text(tag));
	this->texts[this->texts.size() - 1].setTextContent(text);
	this->texts[this->texts.size() - 1].setFont(font);
	this->texts[this->texts.size() - 1].setPosition(position);
	this->texts[this->texts.size() - 1].setFillColor(sf::Color(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128, 255));
	this->texts[this->texts.size() - 1].setCharacterSize(48);
}

Titlescreen::Titlescreen() : textures(), texts(), font(), frameCounter(0) {
	this->loadTextures();

	this->addSprite("logo", "assets/sprites/logoEN.png", sf::Vector2f(440.f, 80.f), 0.f, sf::Vector2f(0.5f, 0.5f));
	this->addSprite("stefan", "assets/sprites/bulonais.png", sf::Vector2f(112.f, 80.f), 0.f, sf::Vector2f(4.f, 4.f));
	this->addSprite("greenBox", "assets/sprites/box-up.png", sf::Vector2f(998.f, 100.f), 0.f, sf::Vector2f(2.f, 2.f));
	this->addSprite("blueBox", "assets/sprites/box-down.png", sf::Vector2f(998.f, 180.f), 0.f, sf::Vector2f(2.f, 2.f));
	this->addSprite("redBox", "assets/sprites/box-avoid.png", sf::Vector2f(998.f, 260.f), 0.f, sf::Vector2f(2.f, 2.f));

	this->font.loadFromFile("assets/fonts/NerkoOne-Regular.ttf");
	this->addText("enterGame", "press any key to start game", sf::Vector2f(362.f, 540.f));
	this->addText("storyOneOne", "This is rabbit,", sf::Vector2f(113.f, 360.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyOneTwo", "his name is Stefan!", sf::Vector2f(87.f, 390.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyOneThree", "Unfortunately, he is stuck", sf::Vector2f(55.f, 420.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyOneFour", "in infinite slip", sf::Vector2f(113.f, 450.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);

	this->addText("storyTwoOne", "Jump over green boxes,", sf::Vector2f(930.f, 360.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyTwoTwo", "slide under blue boxes", sf::Vector2f(937.f, 390.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyTwoThree", "and avoid red ones", sf::Vector2f(952.f, 420.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);
	this->addText("storyTwoFour", "to keep slippery story", sf::Vector2f(935.f, 450.f));
	this->texts[this->texts.size() - 1].setCharacterSize(24);

	this->bufferOption.loadFromFile("assets/audio/option.wav");

}

void Titlescreen::processInput(const std::vector<window::PressedKey>& keyboardInput, const std::vector<window::PressedButton>& joystickInput) {
	if (keyboardInput.size() != 0) { 
		this->sound.setBuffer(this->bufferOption);
		this->sound.play();
		this->readyToQuit = true; 
	}
}

bool Titlescreen::update() {
	if (this->frameCounter % 30 == 0) {
		auto iter = std::find_if(this->texts.begin(), this->texts.end(), [](graphics::Text& text) { return text.getTag() == "enterGame"; });
		if (iter != this->texts.end()) {
			iter->setFillColor(sf::Color(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128, 255));
		}
	}

	frameCounter++;

	return !this->readyToQuit;
}

void Titlescreen::render(sf::RenderWindow* window) {
	for (auto sprite : this->stableSprites) {
		window->draw(sprite.getSprite());
	}
	for (auto& text : this->texts) {
		window->draw(text.getText());
	}
}



}