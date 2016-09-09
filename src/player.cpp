#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const float gravity = 2000;

player::player(float newWidth, float newHeight)
{
    ownShape.setPosition(100, 100);
    previousShape = ownShape;
    ownVelocity = 10;
    isJumping = true;
    spacePressed = false;
    canDoubleJump = true;

    ownShape.setSize(sf::Vector2f(newWidth, newHeight));
    ownShape.setFillColor(sf::Color::Green);
}

player::~player()
{
    //dtor
}

bool player::updateSelf(sf::Time frameElapsed, int collisionWithObstacle)//Update position
{
    jump();

    ownVelocity += gravity*frameElapsed.asSeconds(); //changes in any kind of speed have to be time-regulated, hence *frameElapsed.asSeconds()

    if ((ownShape.getPosition().y + ownVelocity*frameElapsed.asSeconds()) >= (600 - ownShape.getSize().y)) //if ball will go offscreen
    {
        ownVelocity = 0; //stop
        isJumping = false;
        canDoubleJump = true;
        ownShape.setPosition(sf::Vector2f(ownShape.getPosition().x, 600 - ownShape.getSize().y)); //at the edge
    }

    if (collisionWithObstacle == 1)//if there is collision and it isn't death causing
    {
        ownVelocity = 0;
        isJumping = false;
        canDoubleJump = true;
        ownShape = previousShape; //move back a frame
    }
    else if (collisionWithObstacle == 2)//if there is a death causing collision
    {
        ownVelocity = 0;
        isJumping = false;
        canDoubleJump = true;
        ownShape.setPosition(100, 100); //respawn (temporary)
        return false;
    }

    previousShape = ownShape; //store this frame's info for next frame
    ownShape.move(sf::Vector2f(0, ownVelocity*frameElapsed.asSeconds()));
    return true;
}

void player::jump()
{
    if (!isJumping && ownVelocity == 0 && spacePressed)
    {
        ownVelocity = -600;
        isJumping = true;
        canDoubleJump = true;
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
    if (isJumping && canDoubleJump
        && !spacePressed && isSpacePressed)//basically, did the player just press the space bar
    {
        ownVelocity = -600;
        canDoubleJump = false;
    }

    spacePressed = isSpacePressed;
}
