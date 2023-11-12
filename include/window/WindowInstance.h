#ifndef WINDOW_WINDOWINSTANCE_H_
#define WINDOW_WINDOWINSTANCE_H_

#include <string>

#include <SFML/Graphics.hpp>

#include <game/Stage.h>
#include <game/Titlescreen.h>
#include <window/JoystickInput.h>
#include <window/KeyboardInput.h>

namespace window {

enum class ProgramState { titlescreen, stage };

class WindowInstance {
private:
	sf::RenderWindow window;
	ProgramState state;

	//JoystickInput joystick;	// TODO: fix
	KeyboardInput keyboard;

	game::Stage stage;
	game::Titlescreen titlescreen;
	int waitFrames = 0;
public:
	WindowInstance(int width, int height, std::string name);

	void setFrameRate(int frames);

	int loop();
};

}

#endif