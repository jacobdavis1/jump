#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H
#include <SFML/Graphics.hpp>
#include <vector>

class obstacleManager
{
    public:

        obstacleManager(int newDefaultObstacleWidth, int newDefaultObstacleHeightMax);
        virtual ~obstacleManager();

        int playerCollidesOnTop(sf::RectangleShape playerShape, sf::RectangleShape previousPlayerRect, float playerVelocity, sf::Time frameElapsed);

        void updateObstacles(int windowWidth, int windowHeight, sf::Time frameElapsed, sf::Time totalElapsed);
        void drawObstacles(sf::RenderWindow& window);

        void reset();

    protected:

    private:

        int defaultObstacleWidth;
        int defaultObstacleHeightMax;
        bool fullyDisabled;
        bool difficultyIncreasing;
        int difficultyLevel;
        int singleLevelObstacleCap;

        sf::Time difficultyTimeStamp;

        void createNewObstacle(int windowWidth, int windowHeight);
        void checkNewObstacleNeeded(int windowWidth, int windowHeight, sf::Time totalElapsed);

        bool checkAllDisabled();
        void normalizeObstacleSequence(int windowWidth);
        void increaseDifficulty(sf::Time totalElapsed);

        struct obstacle
        {
            bool inUse;
            sf::RectangleShape ownRect;
            sf::RectangleShape previousRect;
        };

        std::vector<obstacle> obstacles;
};

#endif // OBSTACLEMANAGER_H
