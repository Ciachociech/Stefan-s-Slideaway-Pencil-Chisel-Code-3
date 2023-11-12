#include <graphics/Text.h>

namespace graphics {

Text::Text(const std::string tag) : text(), tag(tag) {}

void Text::setFont(const sf::Font& font) {
	this->text.setFont(font);
}

void Text::setTextContent(const std::string text) {
	this->text.setString(text);
}

void Text::setCharacterSize(const unsigned int size) {
	this->text.setCharacterSize(size);
}

void Text::setFillColor(const sf::Color color) {
	this->text.setFillColor(color);
}

void Text::setPosition(const sf::Vector2f position) {
	this->text.setPosition(position);
}

const sf::Text& Text::getText() {
	return this->text;
}

const std::string Text::getTag() {
	return this->tag;
}

}