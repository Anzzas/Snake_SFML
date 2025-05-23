﻿#include "display.h"

using namespace DisplaySettings;


void Display::renderGame(const std::deque<Position>& snakeBody, const Position& food, const int& score, sf::RenderWindow& m_window, const int& highScore)
{

        m_window.clear();


        renderBorders(m_window);


        renderSnake(snakeBody, m_window);


        renderFood(food, m_window);


        renderScore(score, m_window);


        renderHighScore(highScore, m_window);


        m_window.display();
}


void Display::renderBorders(sf::RenderWindow& m_window)
{

    const float borderThickness = 10.0f;


    sf::RectangleShape topBorder;
    topBorder.setSize(sf::Vector2f(window_Dimensions - 40.0f, borderThickness));
    topBorder.setPosition(sf::Vector2f(20.0f, 20.0f));
    topBorder.setFillColor(DisplaySettings::border_Color);


    sf::RectangleShape leftBorder;
    leftBorder.setSize(sf::Vector2f(borderThickness, window_Dimensions - 40.0f));
    leftBorder.setPosition(sf::Vector2f(20.0f, 20.0f));
    leftBorder.setFillColor(DisplaySettings::border_Color);


    sf::RectangleShape downBorder;
    downBorder.setSize(sf::Vector2f(window_Dimensions - 40.0f, borderThickness));
    downBorder.setPosition(sf::Vector2f(20.0f, (window_Dimensions - borderThickness) - 20.0f));
    downBorder.setFillColor(DisplaySettings::border_Color);


    sf::RectangleShape rightBorder;
    rightBorder.setSize(sf::Vector2f(borderThickness, window_Dimensions - 40.0f));
    rightBorder.setPosition(sf::Vector2f((window_Dimensions - borderThickness) - 20.0f, 20.0f));
    rightBorder.setFillColor(DisplaySettings::border_Color);


    m_window.draw(topBorder);
    m_window.draw(leftBorder);
    m_window.draw(rightBorder);
    m_window.draw(downBorder);

}

void Display::renderSnake(const std::deque<Position>& snakeBody, sf::RenderWindow& m_window)
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


void Display::renderFood(const Position& foodPos, sf::RenderWindow& m_window)
{
    sf::CircleShape foodSprite{ cell_Size / 2 };


    sf::Vector2f screenPos{ gridToScreenPosition(foodPos) };


    foodSprite.setPosition(positionShapeCenter(screenPos, foodSprite));


    foodSprite.setFillColor(food_Color);

    
    m_window.draw(foodSprite);
}


void Display::renderScore(const int& score, sf::RenderWindow& m_window)
{    

    sf::Text scoreText{ m_font, "Score: " + std::to_string(score) };


    scoreText.setCharacterSize(charSize);


    scoreText.setFillColor(text_Color);


    m_window.draw(scoreText);
}


void Display::renderHighScore(const int& highScore, sf::RenderWindow& m_window)
{
    sf::Text highScoreText{ m_font, "High score: " + std::to_string(highScore) };


    highScoreText.setCharacterSize(charSize);


    highScoreText.setFillColor(text_Color);


    highScoreText.setPosition(sf::Vector2f{ 360.0f, 0.0f });


    m_window.draw(highScoreText);
}


void Display::renderMenu(sf::RenderWindow& m_window, const int& score, const std::optional<sf::Event>& input, MenuType menuType, const DifficultyMode& difficulty)
{
    m_window.clear();


    renderMenuBorders(m_window);


    renderMenuText(score, menuType, difficulty, m_window);


    renderMenuSelectCursor(input, m_window, menuType);


    m_window.display();
}


void Display::renderMenuBorders(sf::RenderWindow& m_window)
{
    const float borderThickness = 5.0f;
    const float borderOffset = 50.0f;
    const float width = window_Dimensions - 2 * borderOffset;
    const float height = window_Dimensions - 2 * borderOffset;


    sf::Color borderColor(200, 200, 200);


    sf::RectangleShape topBorder;
    topBorder.setSize(sf::Vector2f(width, borderThickness));
    topBorder.setPosition(sf::Vector2f(borderOffset, borderOffset));
    topBorder.setFillColor(borderColor);


    sf::RectangleShape rightBorder;
    rightBorder.setSize(sf::Vector2f(borderThickness, height));
    rightBorder.setPosition(sf::Vector2f(borderOffset + width - borderThickness, borderOffset));
    rightBorder.setFillColor(borderColor);


    sf::RectangleShape bottomBorder;
    bottomBorder.setSize(sf::Vector2f(width, borderThickness));
    bottomBorder.setPosition(sf::Vector2f(borderOffset, borderOffset + height - borderThickness));
    bottomBorder.setFillColor(borderColor);


    sf::RectangleShape leftBorder;
    leftBorder.setSize(sf::Vector2f(borderThickness, height));
    leftBorder.setPosition(sf::Vector2f(borderOffset, borderOffset));
    leftBorder.setFillColor(borderColor);


    sf::RectangleShape middleBorder;
    middleBorder.setSize(sf::Vector2f(width, borderThickness));

    middleBorder.setPosition(sf::Vector2f(borderOffset, borderOffset + height / 4));
    middleBorder.setFillColor(borderColor);


    m_window.draw(topBorder);
    m_window.draw(rightBorder);
    m_window.draw(bottomBorder);
    m_window.draw(leftBorder);
    m_window.draw(middleBorder);
}


void Display::renderMenuText(const int& score, MenuType menuType, const DifficultyMode& difficulty, sf::RenderWindow& m_window)
{
    const float borderOffset = 50.0f;
    const float menuWidth = window_Dimensions - 2 * borderOffset;

    sf::Text titleText{ m_font };
    switch (menuType)
    {
    case MenuType::main_menu:
        titleText.setString("SNAKE");
        break;
    case MenuType::replay_menu:
        titleText.setString("GAME OVER!");
        break;
    case MenuType::difficulty_menu:
        titleText.setString("CHOOSE DIFFICULTY");
        break;
    }

    titleText.setCharacterSize(charSize * 2);
    titleText.setFillColor(sf::Color(50, 255, 50));

    float titleX = 250.0f - (titleText.getString().getSize() * charSize * 0.6f);
    titleText.setPosition(sf::Vector2f{ titleX, 90.0f });
    m_window.draw(titleText);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // TEXT2PREFIX


    sf::Text text2Prefix{ m_font };
    switch (menuType)
    {
    case MenuType::main_menu:
        text2Prefix.setString(" ");
        break;
    case MenuType::replay_menu:
        text2Prefix.setString("Final score: ");
        break;
    case MenuType::difficulty_menu:
        text2Prefix.setString("Current: ");
        break;
    }

    text2Prefix.setCharacterSize(charSize);
    text2Prefix.setFillColor(text_Color);
    text2Prefix.setPosition(sf::Vector2f{ 180.0f, 160.0f });
    m_window.draw(text2Prefix);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // TEXT2


    sf::Text text2{ m_font };
    switch (menuType)
    {
    case MenuType::main_menu:
        text2.setString(" ");
        break;

    case MenuType::replay_menu:
        text2.setString(std::to_string(score));
        break;

    case MenuType::difficulty_menu:
        switch (difficulty)
        {
        case DifficultyMode::easy:
            text2.setString("easy");
            break;
        case DifficultyMode::medium:
            text2.setString("medium");
            break;
        case DifficultyMode::hard:
            text2.setString("hard");
            break;
        }
    }

    text2.setCharacterSize(charSize);
    text2.setFillColor(text_Color);
    text2.setPosition(sf::Vector2f{ menuType == MenuType::replay_menu ? 280.0f : 250.0f, 160.0f });
    m_window.draw(text2);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // OPTION1


    const int menuItemSize = charSize * 1.3;
    const float menuStartY = 220.0f;
    const float menuSpacing = 40.0f;

    sf::Text option1{ m_font };
    switch (menuType)
    {
    case MenuType::main_menu:
        option1.setString("Play");
        break;
    case MenuType::replay_menu:
        option1.setString("Replay");
        break;
    case MenuType::difficulty_menu:
        option1.setString("Easy");
        break;
    }
    option1.setCharacterSize(menuItemSize);
    option1.setFillColor(text_Color);
    option1.setPosition(sf::Vector2f{ 250.0f - 25.0f, menuStartY });
    m_window.draw(option1);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // OPTION2


    sf::Text option2{ m_font, menuType == MenuType::difficulty_menu ? "Medium" : "Change Difficulty" };
    option2.setCharacterSize(menuItemSize);
    option2.setFillColor(text_Color);
    float option2X = 250.0f - (option2.getString().getSize() * menuItemSize * 0.25f);
    option2.setPosition(sf::Vector2f{ option2X, menuStartY + menuSpacing });
    m_window.draw(option2);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // OPTION3


    sf::Text option3{ m_font, menuType == MenuType::difficulty_menu ? "Hard" : "Quit" };
    option3.setCharacterSize(menuItemSize);
    option3.setFillColor(text_Color);
    float option3X = 250.0f - (option3.getString().getSize() * menuItemSize * 0.25f);
    option3.setPosition(sf::Vector2f{ option3X, menuStartY + menuSpacing * 2.0f });
    m_window.draw(option3);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // INSTRUCTION1


    sf::Text instruction1{ m_font, "[UP/DOWN]: Navigate" };
    instruction1.setCharacterSize(charSize);
    instruction1.setFillColor(text_Color);
    float instruction1X = 250.0f - (instruction1.getString().getSize() * charSize * 0.25f);
    instruction1.setPosition(sf::Vector2f{ instruction1X, 390.0f });
    m_window.draw(instruction1);


    ///////////////////////////////////////////////////////////////////////////////////////////
    // INSTRUCTION2


    sf::Text instruction2{ m_font, "[ENTER]: Select" };
    instruction2.setCharacterSize(charSize);
    instruction2.setFillColor(text_Color);
    float instruction2X = 250.0f - (instruction2.getString().getSize() * charSize * 0.25f);
    instruction2.setPosition(sf::Vector2f{ instruction2X, 420.0f });
    m_window.draw(instruction2);
}


void Display::renderMenuSelectCursor(const std::optional<sf::Event>& input, sf::RenderWindow& m_window, MenuType menuType)
{

        sf::Text cursor{ m_font, " "};
        cursor.setPosition(sf::Vector2f{ static_cast<float>(m_currentCursorPos.x), static_cast<float>(m_currentCursorPos.y) });
        m_window.draw(cursor);

        if (input && input->getIf<sf::Event::KeyPressed>())
        {
            const auto* keyEvent = input->getIf<sf::Event::KeyPressed>();

            switch (keyEvent->scancode)
            {
            case sf::Keyboard::Scancode::Up:

                if (m_currentCursorPos == option1Pos)
                    m_currentCursorPos = option3Pos;


                else if (m_currentCursorPos == option2Pos || m_currentCursorPos == option2PosBis)
                    m_currentCursorPos = option1Pos;


                else if (m_currentCursorPos == option3Pos)
                    m_currentCursorPos = menuType == MenuType::difficulty_menu ? option2PosBis : option2Pos;


                break;


            case sf::Keyboard::Scancode::Down:

                if (m_currentCursorPos == option1Pos)
                    m_currentCursorPos = menuType == MenuType::difficulty_menu ? option2PosBis : option2Pos;


                else if (m_currentCursorPos == option2Pos || m_currentCursorPos == option2PosBis)
                    m_currentCursorPos = option3Pos;


                else if (m_currentCursorPos == option3Pos)
                    m_currentCursorPos = option1Pos;
            }
        }

        cursor.setString(">");
        cursor.setCharacterSize(charSize);
        cursor.setFillColor(text_Color);
        cursor.setPosition(sf::Vector2f{ m_currentCursorPos.x, m_currentCursorPos.y });
        m_window.draw(cursor);
}


sf::Vector2f Display::gridToScreenPosition(const Position& gridPos) const
{
    return sf::Vector2f(gridPos.x * cell_Size + borderOffset + cell_Size / 2, gridPos.y * cell_Size + borderOffset + cell_Size / 2);
}


sf::Vector2f Display::positionShapeCenter(const sf::Vector2f& centerPos, const sf::CircleShape& shape) const
{
    return sf::Vector2f(centerPos.x - shape.getRadius(), centerPos.y - shape.getRadius());
}