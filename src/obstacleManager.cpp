#include "obstacleManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>


obstacleManager::obstacleManager(int newDefaultObstacleWidth, int newDefaultObstacleHeightMax)
{
    defaultObstacleWidth = newDefaultObstacleWidth;
    defaultObstacleHeightMax = newDefaultObstacleHeightMax;
    fullyDisabled = true;
    obstacles.clear();
}

obstacleManager::~obstacleManager()
{
    //dtor
}

void obstacleManager::createNewObstacle(int windowWidth, int windowHeight)
{
    obstacle newObstacle;
    newObstacle.ownRect.setSize(sf::Vector2f(defaultObstacleWidth, (std::rand() % defaultObstacleHeightMax) + 10));
    newObstacle.ownRect.setPosition(windowWidth + newObstacle.ownRect.getSize().x, windowHeight - newObstacle.ownRect.getSize().y);
    newObstacle.ownRect.setFillColor((sf::Color::Green));
    newObstacle.inUse = false;
    obstacles.insert(obstacles.end(), newObstacle);
}

void obstacleManager::updateObstacles(int windowWidth, int windowHeight, sf::Time frameElapsed, sf::Time totalElapsed)
{
    for (int numberOfObstacles = floor(sqrt(totalElapsed.asSeconds())); numberOfObstacles > obstacles.size(); numberOfObstacles--)
    {
        fullyDisabled = true;
        createNewObstacle(windowWidth, windowHeight);
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles.at(i).previousRect = obstacles.at(i).ownRect;

        if (obstacles.at(i).inUse == true)//if the object is in use
        {
            if (obstacles.at(i).ownRect.getPosition().x < -40)//if the obstacle is off screen to the left
            {
                obstacles.at(i).inUse = false;//the object is no longer in use
            }

            else
            {
                obstacles.at(i).ownRect.move(-300*frameElapsed.asSeconds(), 0);//otherwise move the obstacle
            }
        }

        else if (obstacles.at(i).inUse == false)//if its not in use
        {
            obstacles.at(i).ownRect.setSize(sf::Vector2f(sf::Vector2f(defaultObstacleWidth, (std::rand() % defaultObstacleHeightMax) + 10)));//get a new random height
            obstacles.at(i).ownRect.setPosition(windowWidth + obstacles.at(i).ownRect.getSize().x, windowHeight - obstacles.at(i).ownRect.getSize().y);//reset the obstacle's position to offscreen to the right

            if (!fullyDisabled)
            {
                obstacles.at(i).inUse = true;
            }
        }
    }

    if (fullyDisabled)
    {
        if (checkAllDisabled())
        {
            normalizeObstacleSequence(windowWidth);
            fullyDisabled = false;
        }
    }
}

void obstacleManager::drawObstacles(sf::RenderWindow& window)
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles.at(i).inUse == true)
        {
            window.draw(obstacles.at(i).ownRect);
        }
    }
}

void obstacleManager::normalizeObstacleSequence(int windowWidth)
{
    float averageDistance;

    if (obstacles.size() > 0)
    {
        averageDistance = windowWidth/obstacles.size();
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles.at(i).ownRect.setPosition(windowWidth + obstacles.at(i).ownRect.getSize().x + averageDistance*i, obstacles.at(i).ownRect.getPosition().y);
        obstacles.at(i).inUse = true;
    }
}

bool obstacleManager::checkAllDisabled()//cycle through all of the obstacles to check whether they are all disabled
{
    for (int i=0; i < obstacles.size(); i++)
    {
        if (obstacles.at(i).inUse == true)
        {
            return false;
        }
    }

    return true;
}

void obstacleManager::increaseDifficulty(sf::Time totalElapsed)
{

}

int obstacleManager::playerCollidesOnTop(sf::RectangleShape playerRect, sf::RectangleShape previousPlayerRect, float playerVelocity, sf::Time frameElapsed)
{
   for (int i = 0; i < obstacles.size(); i++)
   {
        if (playerRect.getGlobalBounds().intersects(obstacles.at(i).ownRect.getGlobalBounds()))//if the object collides with the player
        {
            if (previousPlayerRect.getPosition().y + previousPlayerRect.getSize().y <= obstacles.at(i).previousRect.getPosition().y)//if, one frame ago, the player would have been directly above
            {
                return 1;//the player lands
            }

            return 2;//otherwise the player is dead
        }
   }

   return 0;//no collision
}
