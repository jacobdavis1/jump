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
        bool fullyDisabled;

        void createNewObstacle(int windowWidth, int windowHeight);
        void updateObstacles(int windowWidth, int windowHeight, sf::Time frameElapsed, sf::Time totalElapsed);
        void drawObstacles(sf::RenderWindow& window);

        bool checkAllDisabled();
        void normalizeObstacleSequence(int windowWidth);
        void increaseDifficulty(sf::Time totalElapsed);

        int playerCollidesOnTop(sf::RectangleShape playerShape, sf::RectangleShape previousPlayerRect, float playerVelocity, sf::Time frameElapsed);

        struct obstacle
        {
            bool inUse;
            sf::RectangleShape ownRect;
            sf::RectangleShape previousRect;
        };

        std::vector<obstacle> obstacles;


    protected:

    private:
};

#endif // OBSTACLEMANAGER_H
