#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class player
{
    public:
        player(float newWidth, float newHeight);
        virtual ~player();

        void updateSelf(sf::Time timeElapsed, bool collisionWithObstacle);
        void jump();
        void drawSelf(sf::RenderWindow& window);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        float getVelocity();

    protected:

    private:
        float ownVelocity;
        sf::RectangleShape ownShape;
        bool isJumping;
};

#endif // PLAYER_H
