#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const float gravity = 981;

player::player(float newWidth, float newHeight)
{
    ownShape.setPosition(100, 100);
    previousShape = ownShape;
    ownVelocity = 10;
    isJumping = true;

    ownShape.setSize(sf::Vector2f(newWidth, newHeight));
    ownShape.setFillColor(sf::Color::Green);
}

player::~player()
{
    //dtor
}

void player::updateSelf(sf::Time timeElapsed, int collisionWithObstacle)//Update position
{
    ownVelocity += gravity*timeElapsed.asSeconds(); //emulate the gravitational pull of the bottom of the screen

    if ((ownShape.getPosition().y + ownVelocity*timeElapsed.asSeconds()) >= (600 - ownShape.getSize().y)) //if ball will go offscreen
    {
        ownVelocity = 0; //stop
        ownShape.setPosition(sf::Vector2f(ownShape.getPosition().x, 600 - ownShape.getSize().y)); //at the edge
    }

    if (collisionWithObstacle == 1)
    {
        ownVelocity = 0;
        ownShape = previousShape;
    }
    else if (collisionWithObstacle == 2)
    {
        ownVelocity = 0;
        ownShape.setPosition(100, 100);
    }

    previousShape = ownShape;
    ownShape.move(sf::Vector2f(0, ownVelocity*timeElapsed.asSeconds()));//move
}

void player::jump()
{
    if (ownVelocity == 0) //if we are stopped
    {
        //jump
        ownVelocity = -400;//with a power of -400
    }
}

void player::drawSelf(sf::RenderWindow& window)
{
    window.draw(ownShape);
}

sf::RectangleShape  player::getShape()
{
    return ownShape;
}

float player::getVelocity()
{
    return ownVelocity;
}
