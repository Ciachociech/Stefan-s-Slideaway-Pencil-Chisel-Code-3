#include <game/Box.h>

#include <vector>

namespace game {

namespace {

constexpr float halfUltimateSize = 48.f / 2;

}

Box::Box(const sf::Vector2f position, const BoxType boxType, const sf::Texture& texture) : sprite(), type(boxType) {
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
	
	if (position.x == 4.f) { 
		this->lane = BoxLane::left;
		this->sprite.setScale(sf::Vector2f(62.f / halfUltimateSize, 62.f / halfUltimateSize));
	}
	else if (position.x == 224.f) { 
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
			x += ((4.f - this->sprite.getSprite().getPosition().x) / 2 + 62.f - factor);
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

const BoxType& Box::getType() {
	return this->type;
}

}