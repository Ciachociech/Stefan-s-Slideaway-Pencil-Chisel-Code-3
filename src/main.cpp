#include <SFML/Graphics.hpp>

#include <graphics/Sprite.h>
#include <graphics/Texture.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(176, 360), "SFML works!");
    window.setFramerateLimit(60);

    graphics::Texture stefanTexture = graphics::Texture("assets/sprites/bulonais.png");
    graphics::Sprite stefanSprite = graphics::Sprite();
    stefanSprite.setTexture(stefanTexture.getTexture());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(stefanSprite.getSprite());
        window.display();
    }

    return 0;
}