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
    spacePressed = false;

    ownShape.setSize(sf::Vector2f(newWidth, newHeight));
    ownShape.setFillColor(sf::Color::Green);
}

player::~player()
{
    //dtor
}

void player::updateSelf(sf::Time frameElapsed, int collisionWithObstacle)//Update position
{
    jump();

    ownVelocity += gravity*frameElapsed.asSeconds(); //emulate the gravitational pull of the bottom of the screen

    if ((ownShape.getPosition().y + ownVelocity*frameElapsed.asSeconds()) >= (600 - ownShape.getSize().y)) //if ball will go offscreen
    {
        ownVelocity = 0; //stop
        isJumping = false;
        ownShape.setPosition(sf::Vector2f(ownShape.getPosition().x, 600 - ownShape.getSize().y)); //at the edge
    }

    if (collisionWithObstacle == 1)//if there is collision and it isn't death causing
    {
        ownVelocity = 0; //set speed to 0
        isJumping = false;
        ownShape = previousShape; //move back a frame
    }
    else if (collisionWithObstacle == 2)//if there is a death causing collision
    {
        ownVelocity = 0;
        isJumping = false;
        ownShape.setPosition(100, 100); //respawn (temproary)
    }

    previousShape = ownShape; //store this frame's info for next frame
    ownShape.move(sf::Vector2f(0, ownVelocity*frameElapsed.asSeconds()));//move
}

void player::jump()
{
    if (!isJumping && ownVelocity == 0 && spacePressed) //if we are stopped
    {
        //jump
        ownVelocity = -400;//with a power of -400
        isJumping = true;
    }
}

void player::drawSelf(sf::RenderWindow& window)
{
    window.draw(ownShape);
}

sf::RectangleShape player::getShape()
{
    return ownShape;
}

sf::RectangleShape player::getPreviousShape()
{
    return previousShape;
}

float player::getVelocity()
{
    return ownVelocity;
}

void player::setSpaceKeyPressed(bool isSpacePressed)
{
    spacePressed = isSpacePressed;
}
