#include <game/Box.h>

#include <vector>

namespace game {

namespace {

constexpr float halfUltimateSize = 48.f / 2;

}

// Box health 2 for BoxType::up means box is not checked for collision, 1 is checked, but player jumped, 0 is checked and collide with player
// for another box types 2 is equal to 1 and in case of collision, damaging is twice
Box::Box(const sf::Vector2f position, const BoxType boxType, const sf::Texture& texture) : sprite("box"), type(boxType), health(2) {
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
	
	if (position.x == 104.f) { 
		this->lane = BoxLane::left;
		this->sprite.setScale(sf::Vector2f(62.f / halfUltimateSize, 62.f / halfUltimateSize));
	}
	else if (position.x == 324.f) { 
		this->lane = BoxLane::right; 
		this->sprite.setScale(sf::Vector2f(62.f / halfUltimateSize, 62.f / halfUltimateSize));
	}
	else { 
		this->lane = BoxLane::middle; 
		this->sprite.setScale(sf::Vector2f(48.f / halfUltimateSize, 62.f / halfUltimateSize));
	}
}

void Box::update(float speed) {
	const float y = -3.f * speed;

	float x = 0.f;
	float factor = 62.f;
	std::vector<int> conditionsY { 608, 578, 548, 518, 488, 454, 424, 394, 334, 274, 214, 154, 94, 34 };
	for (auto it = 0; it < conditionsY.size(); ++it) {
		if (static_cast<int>(this->sprite.getSprite().getPosition().y - y) > conditionsY[it] + (this->type == BoxType::passUp ? 20 : 0)) {
			break;
		}
		factor -= 1.f;
	}

	switch (this->lane) {
		case BoxLane::left: {
			this->sprite.setScale(sf::Vector2f(factor / halfUltimateSize, factor / halfUltimateSize));
			x += ((104.f - this->sprite.getSprite().getPosition().x) / 2 + 62.f - factor);
			break;
		}
		case BoxLane::right: {
			this->sprite.setScale(sf::Vector2f(factor / halfUltimateSize, factor / halfUltimateSize));
			break;
		}
		case BoxLane::middle: default: {
			this->sprite.setScale(sf::Vector2f(48.f / halfUltimateSize, factor / halfUltimateSize));
			break;
		}
	}

	this->sprite.move(sf::Vector2f(x, y));
}

void Box::render(sf::RenderWindow* window) {
	window->draw(this->sprite.getSprite());
}

const sf::FloatRect Box::getHitbox() {
	return this->sprite.getSprite().getGlobalBounds();
}

const BoxType& Box::getType() {
	return this->type;
}

const bool Box::readyToClean() {
	return (this->sprite.getSprite().getPosition().y <= -100.f) || (this->health == 0);
}

const int Box::getHealth() {
	return this->health;
}

const void Box::damage() {
	this->health -= 1;
}

}