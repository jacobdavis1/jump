#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class player
{
    public:
        player(float newWidth, float newHeight);
        virtual ~player();

        void updateSelf(sf::Time frameElapsed, int collisionWithObstacle);
        void jump();
        void drawSelf(sf::RenderWindow& window);

        sf::RectangleShape getShape();
        sf::RectangleShape getPreviousShape();
        float getVelocity();
        void setSpaceKeyPressed(bool isSpacePressed);

    protected:

    private:
        float ownVelocity;
        sf::RectangleShape ownShape, previousShape;
        bool isJumping, spacePressed;
};

#endif // PLAYER_H
