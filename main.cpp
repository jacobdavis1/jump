#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacleManager.h"
#include "score.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jump!");
    player Player1(40, 40);
    obstacleManager ObstacleManager(40, 45);
    score Score;

    enum gameState {Menu, Game, Death} GameState = Menu;
    bool canContinue = true;

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

                    if (GameState != Game && canContinue)
                    {
                        if (GameState == Menu)
                        {
                            GameState = Game;
                            canContinue = false;
                            totalClock.restart();
                            frameClock.restart();

                            Score.reset();
                            ObstacleManager.reset();
                        }
                        else
                        {
                            GameState = Menu;
                            canContinue = false;
                        }
                    }
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
                    canContinue = true;
                }
            }
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        switch (GameState)
        {
        case Menu:
            Score.drawMainMenu(window);
            break;

        case Game:
            if (!Player1.updateSelf(frameClock.getElapsedTime(), ObstacleManager.playerCollidesOnTop(Player1.getShape(), Player1.getPreviousShape(), Player1.getVelocity(), frameClock.getElapsedTime())))
            {
                GameState = Death;
                canContinue = false;
            }
            ObstacleManager.updateObstacles(window.getSize().x, window.getSize().y, frameClock.getElapsedTime(), totalClock.getElapsedTime());
            Score.setScore(totalClock.getElapsedTime());

            frameClock.restart();

            Player1.drawSelf(window);
            ObstacleManager.drawObstacles(window);
            Score.drawScore(window);
            break;

        case Death:
            canContinue = Score.drawDeathScore(window, frameClock.getElapsedTime());
            frameClock.restart();
            break;

        }

        window.display();
    }

    return 0;
}
