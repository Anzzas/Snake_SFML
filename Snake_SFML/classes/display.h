#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include <iostream>
#include <deque>
#include <array>
#include <SFML/Graphics.hpp>
#include <optional>

namespace DisplaySettings
{
    inline const std::string windowName{ "Snake Game" };
    constexpr int window_Dimensions{ 500 };
    constexpr int charSize{ 16 };
    constexpr float cell_Size{ 20.0f };
    constexpr float borderOffset{ 20.0f };
    constexpr sf::Color snake_HeadColor{ sf::Color::Green };
    constexpr sf::Color snake_BodyColor{ sf::Color(0, 180, 0) };
    constexpr sf::Color food_Color{ sf::Color::Red };
    constexpr sf::Color border_Color{ sf::Color::Yellow };
    constexpr sf::Color background_Color{ sf::Color(50, 50, 50) };
    constexpr sf::Color text_Color{ sf::Color::White };
    constexpr sf::Vector2f playAgainCursorPos{ 210.0f, 222.0f };
    constexpr sf::Vector2f difficultyCursorPos{ 150.0f, 262.0f };
    constexpr sf::Vector2f quitCursorPos{ 210.0f, 302.0f };
}

//* Class in charge of displaying everything
class Display
{
public:

    Display()
    {
        if (!m_font.openFromFile("police/07558_CenturyGothic.ttf"))
            throw std::runtime_error{"Could not load Police text"};
    }

    /**
     * Interface principale pour le rendu du jeu
     * Appelle toutes les autres fonctions de rendu
     */
    void renderGame(const std::deque<Position>& snakeBody, const Position& food, const int& score, sf::RenderWindow& m_window);


    /** Displaying once the Replay Menu and the select Cursor in real time*/
    void renderMenu(sf::RenderWindow& m_window, const int& score, const sf::Keyboard::Scancode& input, MenuType menuType, const DifficultyMode& difficulty);

private:


    /**
     * Dessine les bordures du jeu
     */
    void renderBorders(sf::RenderWindow& m_window);


    /**
     * Dessine le serpent (t�te et corps)
     */
    void renderSnake(const std::deque<Position>& snakeBody, sf::RenderWindow& m_window);


    /**
     * Dessine la nourriture
     */
    void renderFood(const Position& foodPos, sf::RenderWindow& m_window);


    /**
     * Affiche le score actuel
     */
    void renderScore(const int& score, sf::RenderWindow& m_window);


    void renderMenuBorders(sf::RenderWindow& m_window);


    void renderMenuText(const int& score, MenuType menuType, const DifficultyMode& difficulty, sf::RenderWindow& m_window);


    void renderMenuSelectCursor(const sf::Keyboard::Scancode& input, sf::RenderWindow& m_window);


    /** Position state to keep in memory the select Cursor position*/
    sf::Vector2f m_currentCursorPos{ DisplaySettings::difficultyCursorPos };


    /**
     * Convertit une position de grille en coordonn�es d'�cran
     */
    sf::Vector2f gridToScreenPosition(const Position& gridPos) const;


    /**
    * Convertit la position au centre r�el du cerle 
    */
    sf::Vector2f positionShapeCenter(const sf::Vector2f& centerPos, const sf::CircleShape& shape) const;


    // Police pour le texte
    sf::Font m_font;
};

#endif