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
    difficultyIncreasing = false;
    difficultyLevel = 0;
    singleLevelObstacleCap = 6;
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
    checkNewObstacleNeeded(windowWidth, windowHeight, totalElapsed);

    //new func: moveObjects
    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles.at(i).previousRect = obstacles.at(i).ownRect;

        if (obstacles.at(i).inUse == true)//if the object is in use
        {
            if (obstacles.at(i).ownRect.getPosition().x < -obstacles.at(i).ownRect.getSize().x)//if the obstacle is off screen to the left
            {
                obstacles.at(i).inUse = false;//the object is no longer in use
            }

            else
            {
                obstacles.at(i).ownRect.move(((-300 - (50*difficultyLevel))*frameElapsed.asSeconds()), 0);//otherwise move the obstacle
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

    if (obstacles.size() == singleLevelObstacleCap && !difficultyIncreasing)
    {
        fullyDisabled = true;
        difficultyIncreasing = true;
    }

    increaseDifficulty(totalElapsed);
    normalizeObstacleSequence(windowWidth);
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

void obstacleManager::reset()
{
    fullyDisabled = true;
    obstacles.clear();
    difficultyLevel = 0;
}

void obstacleManager::normalizeObstacleSequence(int windowWidth)//make the distance between all of the objects the same
{
    float averageDistance;

    if (fullyDisabled)//if the obstacleManager is disabled
    {
        if (checkAllDisabled())//if every obstacle is not in use
        {
            if (obstacles.size() > 0)
            {
                averageDistance = (windowWidth + defaultObstacleWidth)/obstacles.size();
            }

            for (int i = 0; i < obstacles.size(); i++)
            {
                obstacles.at(i).ownRect.setPosition(windowWidth + obstacles.at(i).ownRect.getSize().x + averageDistance*i, obstacles.at(i).ownRect.getPosition().y);//the actual distribution
                obstacles.at(i).inUse = true;
            }

            fullyDisabled = false;//enable the obstacleManager
        }
    }


}

void obstacleManager::increaseDifficulty(sf::Time totalElapsed)
{
    if (fullyDisabled && difficultyIncreasing)//if the obstacleManager is disabled
    {
        if (checkAllDisabled())//if every obstacle is not in use
        {
            obstacles.clear();
            difficultyTimeStamp = totalElapsed;
            difficultyIncreasing = false;
            fullyDisabled = false;//enable the obstacleManager
            difficultyLevel++;
        }
    }
}

void obstacleManager::checkNewObstacleNeeded(int windowWidth, int windowHeight, sf::Time totalElapsed)
{
    double numberOfObstaclesNeeded = floor(sqrt(totalElapsed.asSeconds() - difficultyTimeStamp.asSeconds()));

    if (numberOfObstaclesNeeded < 0)
    {
        numberOfObstaclesNeeded = 0;
    }

    for (numberOfObstaclesNeeded; numberOfObstaclesNeeded > obstacles.size(); numberOfObstaclesNeeded--)
    {
        fullyDisabled = true;
        createNewObstacle(windowWidth, windowHeight);
    }
}

bool obstacleManager::checkAllDisabled()//cycle through all of the obstacles to check whether they are all disabled
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles.at(i).inUse == true)
        {
            return false;
        }
    }

    return true;
}

int obstacleManager::playerCollidesOnTop(sf::RectangleShape playerRect, sf::RectangleShape previousPlayerRect, float playerVelocity, sf::Time frameElapsed)
{
   for (int i = 0; i < obstacles.size(); i++)
   {
        if (playerRect.getGlobalBounds().intersects(obstacles.at(i).ownRect.getGlobalBounds()))//if the object collides with the player
        {
            if (previousPlayerRect.getPosition().y + previousPlayerRect.getSize().y <= obstacles.at(i).previousRect.getPosition().y)//if, one frame ago, the player would have been above
            {
                return 1;//the player lands
            }

            return 2;//otherwise the player is dead
        }
   }

   return 0;//no collision
}
