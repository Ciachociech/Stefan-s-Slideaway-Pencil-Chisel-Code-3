#ifndef WINDOW_WINDOWINSTANCE_H_
#define WINDOW_WINDOWINSTANCE_H_

#include <string>

#include <SFML/Graphics.hpp>

#include <game/Stage.h>
#include <window/JoystickInput.h>
#include <window/KeyboardInput.h>

namespace window {

class WindowInstance {
private:
	sf::RenderWindow window;

	//JoystickInput joystick;	// TODO: fix
	KeyboardInput keyboard;

	game::Stage stage;
public:
	WindowInstance(int width, int height, std::string name);

	void setFrameRate(int frames);

	int loop();
};

}

#endif