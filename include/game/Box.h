#ifndef GAME_BOX_H_
#define GAME_BOX_H_

#include <SFML/Graphics.hpp>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>

namespace game {

enum class BoxType { passUp, passDown, noPass };
enum class BoxLane { left, middle, right};

class Box {
private:
	graphics::Sprite sprite;
	BoxType type;
	BoxLane lane;
public:
	Box(const sf::Vector2f position, const BoxType boxType, const sf::Texture& texture);

	void update(float speed);
	void render(sf::RenderWindow* window);

	const BoxType& getType();
};

}

#endif