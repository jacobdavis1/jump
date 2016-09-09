#ifndef SCORE_H
#define SCORE_H

#include "SFML/Graphics.hpp"


class score
{
    public:
        score();
        virtual ~score();

        void setScore(sf::Time totalElapsed);
        void drawScore(sf::RenderWindow& window);

        void drawMainMenu(sf::RenderWindow& window);
        bool drawDeathScore(sf::RenderWindow& window, sf::Time frameElapsed);

        void reset();

    protected:

    private:
        sf::Font ownFont;
        sf::Text currentScore;
        sf::Text scoreSubText;
        sf::Text title;
        sf::Text titleInstructions;
        double currentScoreNumber;
};

#endif // SCORE_H
