#include <window/WindowInstance.h>

#include <game/Stefan.h>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>

namespace window {
	
WindowInstance::WindowInstance(int width, int height, std::string name) : window(sf::VideoMode(width, height), name), stage(), state(ProgramState::titlescreen), titlescreen() {
    sf::Image icon;
    icon.loadFromFile("assets/sprites/stefan-head2.png");
    this->window.setIcon(32, 32, icon.getPixelsPtr());
}

int WindowInstance::loop() {
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
            if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickMoved) {
                joystickInput = this->joystick.getInput();
            }
        }

        switch (this->state) {
            case ProgramState::titlescreen: { 
                this->titlescreen.processInput(keyboardInput, joystickInput);

                if (this->waitFrames++ > 60 && !titlescreen.update()) {
                    this->state = ProgramState::stage;
                    this->waitFrames = 0;
                }

                this->window.clear(sf::Color(0, 0, 0, 255));
                titlescreen.render(&this->window);
                break; 
            }
            case ProgramState::stage: { 
                stage.processInput(keyboardInput, joystickInput);

                if (!stage.update()) {
                    if (this->waitFrames++ > 120) {
                        this->window.close();
                    }
                }

                this->window.clear(sf::Color(0, 0, 0, 255));
                stage.render(&this->window);
                break; 
            }

        }

        this->window.display();
    }

    return 0;
}

void WindowInstance::setFrameRate(int frames) {
    this->window.setFramerateLimit(frames);
}

}