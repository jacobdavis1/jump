#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class player
{
    public:

        player(float newWidth, float newHeight);
        virtual ~player();

        sf::RectangleShape getShape();
        sf::RectangleShape getPreviousShape();
        float getVelocity();
        void setSpaceKeyPressed(bool isSpacePressed);

        bool updateSelf(sf::Time frameElapsed, int collisionWithObstacle);
        void drawSelf(sf::RenderWindow& window);

    protected:

    private:

        float ownVelocity;
        sf::RectangleShape ownShape, previousShape;
        bool isJumping, spacePressed, canDoubleJump;

        void jump();
};

#endif // PLAYER_H
