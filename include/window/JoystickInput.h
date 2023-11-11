#ifndef WINDOW_JOYSTICKINPUT_H_
#define WINDOW_JOYSTICKINPUT_H_

#include <vector>

namespace window {

enum class PressedButton { left, right, up, down, Y, B, A };

class JoystickInput {
public:
	JoystickInput();

	std::vector<PressedButton> getInput();
};

}

#endif