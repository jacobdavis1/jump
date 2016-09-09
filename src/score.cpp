#include "score.h"
#include "SFML/Graphics.hpp"
#include "math.h"
#include <sstream>
#include <string>

score::score()
{
    ownFont.loadFromFile("ledsled.ttf");

    currentScore.setFont(ownFont);
    currentScore.setCharacterSize(20);
    currentScore.setFillColor(sf::Color::Green);
    currentScore.setPosition(sf::Vector2f(50, 50));

    scoreSubText.setFont(ownFont);
    scoreSubText.setCharacterSize(20);
    scoreSubText.setFillColor(sf::Color::Green);
    scoreSubText.setPosition(sf::Vector2f(200, 450));
    scoreSubText.setString("You died! Space to continue...");

    title.setFont(ownFont);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Green);
    title.setPosition(sf::Vector2f(100, 100));
    title.setString("Jump!");

    titleInstructions.setFont(ownFont);
    titleInstructions.setCharacterSize(25);
    titleInstructions.setFillColor(sf::Color::Green);
    titleInstructions.setPosition(sf::Vector2f(100, 400));
    titleInstructions.setString("Press Space to Begin or Escape to Quit");
}

score::~score()
{
    //dtor
}

void score::setScore(sf::Time totalElapsed)
{
    currentScoreNumber = floor(totalElapsed.asSeconds());
    std::stringstream stream;
    stream << currentScoreNumber;
    currentScore.setString("Score: "+stream.str());
}

void score::drawScore(sf::RenderWindow& window)
{
    window.draw(currentScore);
}

void score::drawMainMenu(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(titleInstructions);
}

bool score::drawDeathScore(sf::RenderWindow& window, sf::Time frameElapsed)
{
    if (currentScore.getPosition().x < 200)
    {
        currentScore.move(sf::Vector2f(150*frameElapsed.asSeconds(), 0));
    }

    if (currentScore.getPosition().y < 300)
    {
        currentScore.move(sf::Vector2f(0, 275*frameElapsed.asSeconds()));
    }

    window.draw(currentScore);

    if (currentScore.getPosition().x >= 200
        && currentScore.getPosition().y >= 300)
    {
        window.draw(scoreSubText);
        return true;
    }
    else return false;
}

void score::reset()
{
    currentScore.setPosition(sf::Vector2f(50, 50));
}
