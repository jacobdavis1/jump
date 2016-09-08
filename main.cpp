#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacleManager.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jump!");
    player Player1(40, 40);
    obstacleManager ObstacleManager(40, 45);

    //one clock is the frame-to frame elapsed time,
    //the other is total time
    sf::Clock frameClock;
    sf::Clock totalClock;

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    Player1.setSpaceKeyPressed(true);
                }

                else if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }

            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    Player1.setSpaceKeyPressed(false);
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!Player1.updateSelf(frameClock.getElapsedTime(), ObstacleManager.playerCollidesOnTop(Player1.getShape(), Player1.getPreviousShape(), Player1.getVelocity(), frameClock.getElapsedTime())))
        {
            ObstacleManager.reset();
            totalClock.restart();
        }
        ObstacleManager.updateObstacles(window.getSize().x, window.getSize().y, frameClock.getElapsedTime(), totalClock.getElapsedTime());

        frameClock.restart();

        window.clear();
        Player1.drawSelf(window);
        ObstacleManager.drawObstacles(window);
        window.display();
    }

    return 0;
}
