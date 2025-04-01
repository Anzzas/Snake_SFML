#include "display.h"

using namespace DisplaySettings;


void Display::renderGame(const std::deque<Position>& snakeBody, const Position& food, const int& score)
{
    createWindow();


    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (!isWindowOpen(event))
                m_window.close();
        }

        m_window.clear();


        renderBorders();


        renderSnake(snakeBody);


        renderFood(food);


        renderScore(score);


        m_window.display();
    }
}


void Display::createWindow()
{
	m_window.create(sf::VideoMode({ window_Dimensions, window_Dimensions }), windowName);
    m_window.setVerticalSyncEnabled(true);
}


bool Display::isWindowOpen(const std::optional<sf::Event>& event)
{
	return !event->is<sf::Event::Closed>();
}


void Display::renderBorders()
{
    // Définir l'épaisseur de vos bordures
    const float borderThickness = 10.0f; // à vous de choisir

    // Créer les quatre rectangles pour les bordures
    // 1. Bordure du haut
    sf::RectangleShape topBorder;
    topBorder.setSize(sf::Vector2f(window_Dimensions - 40.0f, borderThickness));
    topBorder.setPosition(sf::Vector2f(20.0f, 20.0f));
    topBorder.setFillColor(DisplaySettings::border_Color);

    // 2. Bordure de gauche
    sf::RectangleShape leftBorder;
    leftBorder.setSize(sf::Vector2f(borderThickness, window_Dimensions - 40.0f));
    leftBorder.setPosition(sf::Vector2f(20.0f, 20.0f));
    leftBorder.setFillColor(DisplaySettings::border_Color);

    // 3. Bordure du bas
    sf::RectangleShape downBorder;
    downBorder.setSize(sf::Vector2f(window_Dimensions - 40.0f, borderThickness));
    downBorder.setPosition(sf::Vector2f(20.0f, (window_Dimensions - borderThickness) - 20.0f));
    downBorder.setFillColor(DisplaySettings::border_Color);

    // 4. Bordure de droite
    sf::RectangleShape rightBorder;
    rightBorder.setSize(sf::Vector2f(borderThickness, window_Dimensions - 40.0f));
    rightBorder.setPosition(sf::Vector2f((window_Dimensions - borderThickness) - 20.0f, 20.0f));
    rightBorder.setFillColor(DisplaySettings::border_Color);

    // Dessiner chaque bordure sur la fenêtre
    m_window.draw(topBorder);
    m_window.draw(leftBorder);
    m_window.draw(rightBorder);
    m_window.draw(downBorder);
    // etc.
}

void Display::renderSnake(const std::deque<Position>& snakeBody)
{
    for (const auto& e : snakeBody)
    {       

        sf::CircleShape body{ cell_Size / 2 };


        sf::Vector2f screenPos{ gridToScreenPosition(e) };


        body.setPosition(positionShapeCenter(screenPos, body));


        body.setFillColor(snakeBody.front() == e ? snake_HeadColor : snake_BodyColor);


        m_window.draw(body);
    }
}


void Display::renderFood(const Position& foodPos)
{
    sf::CircleShape foodSprite{ cell_Size / 2 };


    sf::Vector2f screenPos{ gridToScreenPosition(foodPos) };


    foodSprite.setPosition(positionShapeCenter(screenPos, foodSprite));


    foodSprite.setFillColor(food_Color);

    
    m_window.draw(foodSprite);
}


void Display::renderScore(const int& score)
{    

    sf::Text scoreText{ m_font, "Score: " + std::to_string(score) };


    scoreText.setCharacterSize(charSize);


    scoreText.setFillColor(text_Color);


    m_window.draw(scoreText);
}


sf::Vector2f Display::gridToScreenPosition(const Position& gridPos) const
{
    return sf::Vector2f(gridPos.x * cell_Size + borderOffset + cell_Size / 2, gridPos.y * cell_Size + borderOffset + cell_Size / 2);
}


sf::Vector2f Display::positionShapeCenter(const sf::Vector2f& centerPos, const sf::CircleShape& shape) const
{
    return sf::Vector2f(centerPos.x - shape.getRadius(), centerPos.y - shape.getRadius());
}