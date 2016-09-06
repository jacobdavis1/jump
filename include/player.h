#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class player
{
    public:
        player(float newWidth, float newHeight);
        virtual ~player();

        void updateSelf(sf::Time timeElapsed, int collisionWithObstacle);
        void jump();
        void drawSelf(sf::RenderWindow& window);

        sf::RectangleShape getShape();
        float getVelocity();

    protected:

    private:
        float ownVelocity;
        sf::RectangleShape ownShape, previousShape;
        bool isJumping;
};

#endif // PLAYER_H
