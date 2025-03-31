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
    constexpr int frameLimit{ 60 };
    constexpr float cell_Size{ 20.0f };
    constexpr float borderOffset{ 20.0f };
    constexpr sf::Color snake_HeadColor{ sf::Color::Green };
    constexpr sf::Color snake_BodyColor{ sf::Color(0, 180, 0) };
    constexpr sf::Color food_Color{ sf::Color::Red };
    constexpr sf::Color border_Color{ sf::Color::Yellow };
    constexpr sf::Color background_Color{ sf::Color(50, 50, 50) };
    constexpr sf::Color text_Color{ sf::Color::White };
}

//* Class in charge of displaying everything
class Display
{
public:

    Display() = default;

    /**
     * Interface principale pour le rendu du jeu
     * Appelle toutes les autres fonctions de rendu
     */
    void renderGame(const std::deque<Position>& snakeBody, const Position& food /*const int& score*/ );

    /**
     * Traite les �v�nements de la fen�tre
     * Retourne un std::optional<sf::Event> s'il y a un �v�nement
     */
    std::optional<sf::Event> pollEvent();

    /**
     * V�rifie si la fen�tre est ouverte
     */
    bool isWindowOpen(const std::optional<sf::Event>& event);

private:

    /**
    * Cr�er la fen�tre de jeu
    */
    void Display::createWindow();


    /**
     * Dessine les bordures du jeu
     */
    void renderBorders();


    /**
     * Dessine le serpent (t�te et corps)
     */
    void renderSnake(const std::deque<Position>& snakeBody);


    /**
     * Dessine la nourriture
     */
    void renderFood(const Position& foodPos);


    /**
     * Affiche le score actuel
     */
    void renderScore(const int& score);


    /**
     * Convertit une position de grille en coordonn�es d'�cran
     */
    sf::Vector2f gridToScreenPosition(const Position& gridPos) const;


    /**
    * Convertit la position au centre r�el du cerle 
    */
    sf::Vector2f positionShapeCenter(const sf::Vector2f& centerPos, const sf::CircleShape& shape) const;


    // La fen�tre SFML
    sf::RenderWindow m_window;


    // Police pour le texte
    sf::Font m_font;
};

#endif