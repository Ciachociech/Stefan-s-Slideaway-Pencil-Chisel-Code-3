#include <window/WindowInstance.h>

#include <game/Stefan.h>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>

namespace window {
	
WindowInstance::WindowInstance(int width, int height, std::string name) : window(sf::VideoMode(width, height), name) {}

int WindowInstance::loop() {
    game::Stefan stefan;

    while (this->window.isOpen())
    {
        std::vector<PressedKey> keyboardInput;
        std::vector<PressedButton> joystickInput;
        
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                keyboardInput = this->keyboard.getInput();
            }
            if (event.type == sf::Event::JoystickButtonPressed) {
                //joystickInput = this->joystick.getInput();
            }
        }

        stefan.processInput(keyboardInput, joystickInput);

        this->window.clear();
        stefan.render(&this->window);
        this->window.display();
    }

    return 0;
}

void WindowInstance::setFrameRate(int frames) {
    this->window.setFramerateLimit(frames);
}

}