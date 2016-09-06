#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H
#include <SFML/Graphics.hpp>
#include <vector>

class obstacleManager
{
    public:
        obstacleManager(int newDefaultObstacleWidth, int newDefaultObstacleHeightMax);
        virtual ~obstacleManager();

        int defaultObstacleWidth;
        int defaultObstacleHeightMax;

        void createNewObstacle(int windowWidth, int windowHeight);
        void updateObstacles(int windowWidth, int windowHeight, sf::Time elapsed);
        void drawObstacles(sf::RenderWindow& window);

        int playerCollidesOnTop(sf::RectangleShape playerShape, float playerVelocity, sf::Time timeElapsed);

        struct obstacle
        {
            float x, y;
            int width, height;
            bool inUse;
            sf::RectangleShape rect;
        };

        std::vector<obstacle> obstacles;


    protected:

    private:
};

#endif // OBSTACLEMANAGER_H
