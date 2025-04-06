#include "display.h"

using namespace DisplaySettings;


void Display::renderGame(const std::deque<Position>& snakeBody, const Position& food, const int& score, sf::RenderWindow& m_window)
{

        m_window.clear();


        renderBorders(m_window);


        renderSnake(snakeBody, m_window);


        renderFood(food, m_window);


        renderScore(score, m_window);


        m_window.display();
}


void Display::renderBorders(sf::RenderWindow& m_window)
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


void Display::renderMenu(sf::RenderWindow& m_window, const int& score, const InputType& input, MenuType menuType, const DifficultyMode& difficulty)
{
    m_window.clear();


    renderMenuBorders(m_window);


    renderMenuText(score, menuType, difficulty, m_window);


    renderMenuSelectCursor(input);


    m_window.display();
}


void Display::renderMenuBorders(sf::RenderWindow& m_window)
{
    const float borderThickness = 5.0f;  // Épaisseur des bordures
    const float borderOffset = 50.0f;    // Distance depuis le bord de la fenêtre
    const float width = window_Dimensions - 2 * borderOffset;
    const float height = window_Dimensions - 2 * borderOffset;

    // Couleur des bordures (blanc ou gris clair)
    sf::Color borderColor(200, 200, 200);

    // 1. Bordure du haut
    sf::RectangleShape topBorder;
    topBorder.setSize(sf::Vector2f(width, borderThickness));
    topBorder.setPosition(sf::Vector2f(borderOffset, borderOffset));
    topBorder.setFillColor(borderColor);

    // 2. Bordure de droite
    sf::RectangleShape rightBorder;
    rightBorder.setSize(sf::Vector2f(borderThickness, height));
    rightBorder.setPosition(sf::Vector2f(borderOffset + width - borderThickness, borderOffset));
    rightBorder.setFillColor(borderColor);

    // 3. Bordure du bas
    sf::RectangleShape bottomBorder;
    bottomBorder.setSize(sf::Vector2f(width, borderThickness));
    bottomBorder.setPosition(sf::Vector2f(borderOffset, borderOffset + height - borderThickness));
    bottomBorder.setFillColor(borderColor);

    // 4. Bordure de gauche
    sf::RectangleShape leftBorder;
    leftBorder.setSize(sf::Vector2f(borderThickness, height));
    leftBorder.setPosition(sf::Vector2f(borderOffset, borderOffset));
    leftBorder.setFillColor(borderColor);

    // 5. Ligne horizontale du milieu (séparant le titre du reste)
    sf::RectangleShape middleBorder;
    middleBorder.setSize(sf::Vector2f(width, borderThickness));
    // Position à environ 1/4 de la hauteur totale pour séparer le titre du menu
    middleBorder.setPosition(sf::Vector2f(borderOffset, borderOffset + height / 4));
    middleBorder.setFillColor(borderColor);

    // Dessiner toutes les bordures
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
    text2Prefix.setPosition(sf::Vector2f{ 180.0f, 150.0f });
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
    text2.setPosition(sf::Vector2f{ 280.0f, 150.0f });
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
        option1.setString("Play again");
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


void Display::renderMenuSelectCursor(const InputType& input, sf::RenderWindow& m_window)
{

    if (input == InputType::up_arrow || input == InputType::down_arrow)
    {
        econio_gotoxy(static_cast<int>(m_currentCursorPos.x), static_cast<int>(m_currentCursorPos.y));
        std::cout << " ";


        switch (input)
        {
        case InputType::up_arrow:

            if (m_currentCursorPos == playAgainCursorPos)
                m_currentCursorPos = quitCursorPos;


            else if (m_currentCursorPos == difficultyCursorPos)
                m_currentCursorPos = playAgainCursorPos;


            else if (m_currentCursorPos == quitCursorPos)
                m_currentCursorPos = difficultyCursorPos;


            break;


        case InputType::down_arrow:

            if (m_currentCursorPos == playAgainCursorPos)
                m_currentCursorPos = difficultyCursorPos;


            else if (m_currentCursorPos == difficultyCursorPos)
                m_currentCursorPos = quitCursorPos;


            else if (m_currentCursorPos == quitCursorPos)
                m_currentCursorPos = playAgainCursorPos;
        }


        econio_gotoxy(static_cast<int>(m_currentCursorPos.x), static_cast<int>(m_currentCursorPos.y));
        std::cout << ">";
    }
}


sf::Vector2f Display::gridToScreenPosition(const Position& gridPos) const
{
    return sf::Vector2f(gridPos.x * cell_Size + borderOffset + cell_Size / 2, gridPos.y * cell_Size + borderOffset + cell_Size / 2);
}


sf::Vector2f Display::positionShapeCenter(const sf::Vector2f& centerPos, const sf::CircleShape& shape) const
{
    return sf::Vector2f(centerPos.x - shape.getRadius(), centerPos.y - shape.getRadius());
}