#ifndef WINDOW_KEYBOARDINPUT_H_
#define WINDOW_KEYBOARDINPUT_H_

#include <vector>

namespace window {

enum class PressedKey { left, right, up, down, space, shift, control };

class KeyboardInput {
public:
	KeyboardInput();

	std::vector<PressedKey> getInput();
};

}

#endif