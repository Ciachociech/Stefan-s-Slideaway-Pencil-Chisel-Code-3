#include <window/WindowInstance.h>

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
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();
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