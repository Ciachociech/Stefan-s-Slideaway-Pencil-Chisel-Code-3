#ifndef WINDOW_WINDOWINSTANCE_H_
#define WINDOW_WINDOWINSTANCE_H_

#include <string>

#include <SFML/Graphics.hpp>

namespace window {

class WindowInstance {
private:
	sf::RenderWindow window;
public:
	WindowInstance(int width, int height, std::string name);

	void setFrameRate(int frames);

	int loop();
};

}

#endif