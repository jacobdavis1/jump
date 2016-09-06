#include "obstacleManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



obstacleManager::obstacleManager(int newDefaultObstacleWidth, int newDefaultObstacleHeightMax)
{
    defaultObstacleWidth = newDefaultObstacleWidth;
    defaultObstacleHeightMax = newDefaultObstacleHeightMax;
    obstacles.clear();
}

obstacleManager::~obstacleManager()
{
    //dtor
}

void obstacleManager::createNewObstacle(int windowWidth, int windowHeight)
{
    obstacle newObstacle;
    newObstacle.rect.setSize(sf::Vector2f(defaultObstacleWidth, (std::rand() % defaultObstacleHeightMax) + 10));
    newObstacle.rect.setPosition(windowWidth + newObstacle.rect.getSize().x, windowHeight - newObstacle.rect.getSize().y);
    newObstacle.rect.setFillColor((sf::Color::Green));
    newObstacle.inUse = false;
    obstacles.insert(obstacles.end(), newObstacle);
}

void obstacleManager::updateObstacles(int windowWidth, int windowHeight, sf::Time elapsed)
{
    float timeMultiplier = elapsed.asSeconds();

    if (obstacles.size() == 0)
    {
        createNewObstacle(windowWidth, windowHeight);
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles.at(i).inUse == true)
        {
            if (obstacles.at(i).rect.getPosition().x < -40)
            {
                obstacles.at(i).inUse = false;
            }

            else
            {
                obstacles.at(i).rect.move(-300*timeMultiplier, 0);
            }
        }

        else if (obstacles.at(i).inUse == false)
        {
            obstacles.at(i).rect.setSize(sf::Vector2f(sf::Vector2f(defaultObstacleWidth, (std::rand() % defaultObstacleHeightMax) + 10)));
            obstacles.at(i).rect.setPosition(windowWidth + obstacles.at(i).rect.getSize().x, windowHeight - obstacles.at(i).rect.getSize().y);
            obstacles.at(i).inUse = true;
        }
    }
}

void obstacleManager::drawObstacles(sf::RenderWindow& window)
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles.at(i).inUse == true)
        {
            window.draw(obstacles.at(i).rect);
        }
    }
}

int obstacleManager::playerCollidesOnTop(sf::RectangleShape playerShape, float playerVelocity, sf::Time timeElapsed)
{
   for (int i = 0; i < obstacles.size(); i++)
   {
        if (playerShape.getGlobalBounds().intersects(obstacles.at(i).rect.getGlobalBounds()))
        {
            sf::RectangleShape testShape = playerShape;
            testShape.move(sf::Vector2f(0, -playerVelocity));

            if (testShape.getGlobalBounds().intersects(obstacles.at(i).rect.getGlobalBounds()))
            {
                return 2;
            }

            return 1;
        }
   }

   return 0;
}
