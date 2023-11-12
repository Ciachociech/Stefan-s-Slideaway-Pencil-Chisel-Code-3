#ifndef GRAPHICS_TEXT_H_
#define GRAPHICS_TEXT_H_

#include <string>

#include <SFML/Graphics.hpp>

namespace graphics {

class Text {
private:
	sf::Text text;
	std::string tag;
public:
	Text(const std::string tag);

	void setFont(const sf::Font& font);
	void setTextContent(const std::string text);
	void setCharacterSize(const unsigned int size);
	void setFillColor(const sf::Color color);
	void setPosition(const sf::Vector2f position);

	const sf::Text& getText();
	const std::string getTag();
};

}

#endif