#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const float gravity = 981;

player::player(float newWidth, float newHeight)
{
    ownShape.setPosition(100, 100);
    ownVelocity = 10;
    isJumping = true;

    ownShape.setSize(sf::Vector2f(newWidth, newHeight));
    ownShape.setFillColor(sf::Color::Green);
}

player::~player()
{
    //dtor
}

void player::updateSelf(sf::Time timeElapsed, bool collisionWithObstacle)//Update position
{
    ownVelocity += gravity*timeElapsed.asSeconds(); //emulate the gravitational pull of the bottom of the screen

    if ((ownShape.getPosition().y + ownVelocity*timeElapsed.asSeconds()) >= (600 - ownShape.getSize().y)) //if ball will go offscreen
    {
        ownVelocity = 0; //stop
        ownShape.setPosition(sf::Vector2f(ownShape.getPosition().x, 600 - ownShape.getSize().y)); //at the edge
    }
    else if (collisionWithObstacle)
    {
        ownVelocity = 0;
    }

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

sf::Vector2f player::getPosition()
{
    return ownShape.getPosition();
}

sf::Vector2f player::getSize()
{
    return ownShape.getSize();
}

float player::getVelocity()
{
    return ownVelocity;
}
