#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacleManager.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jump!");
    player Player1(40, 40);
    obstacleManager ObstacleManager(40, 45);

    sf::Clock clock;
    clock.restart();
    sf::Time elapsed;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)//if a key was pressed
            {
                if (event.key.code == sf::Keyboard::Space)//if that key is space
                {
                    Player1.jump();
                }

                else if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }

            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        elapsed = clock.getElapsedTime();//Set the amount of time that has elapsed since the last frame.
        clock.restart();
        Player1.updateSelf(elapsed, ObstacleManager.playerCollidesOnTop(Player1.getShape(), Player1.getVelocity(), elapsed));
        ObstacleManager.updateObstacles(window.getSize().x, window.getSize().y, elapsed);

        window.clear();
        Player1.drawSelf(window);
        ObstacleManager.drawObstacles(window);
        window.display();
    }

    return 0;
}
