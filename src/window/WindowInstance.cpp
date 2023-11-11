#include <window/WindowInstance.h>

#include <algorithm>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>

namespace window {
	
WindowInstance::WindowInstance(int width, int height, std::string name) : window(sf::VideoMode(width, height), name) {}

int WindowInstance::loop() {
    graphics::Texture stefanTexture = graphics::Texture("assets/sprites/bulonais.png");
    graphics::Sprite stefanSprite = graphics::Sprite();
    stefanSprite.setTexture(stefanTexture.getTexture());

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

        if (std::find(keyboardInput.begin(), keyboardInput.end(), PressedKey::down) != keyboardInput.end() || std::find(joystickInput.begin(), joystickInput.end(), PressedButton::down) != joystickInput.end()) {
            stefanSprite.move(sf::Vector2f(0, 2));
        }

        this->window.clear();
        this->window.draw(stefanSprite.getSprite());
        this->window.display();
    }

    return 0;
}

void WindowInstance::setFrameRate(int frames) {
    this->window.setFramerateLimit(frames);
}

}