Description
Control a snake moving on a game board, eat food to grow, and avoid hitting the walls or your own body. A modern version of the 90s classic!
Features

Smooth snake movement
Score system with high score saving
Main menu with multiple options
Responsive sound effects
Multiple difficulty levels
Collision detection with the edges and the snake's body
Attractive graphical interface

Installation
Download and Play

Download the latest release from the "Releases" section
Extract the zip archive
Run Snake_SFML.exe

How to Play

Arrow keys: Control the snake
Escape: Quit the game
Enter: Select an option in the menu

Technologies Used

C++17
SFML 2.6
CMake

Building from Source
Prerequisites

C++17 or higher
CMake 3.0 or higher
SFML 2.6 or higher

Steps

Clone the repository: git clone https://github.com/yourusername/Snake_SFML.git
Create a build directory: mkdir build && cd build
Generate build files: cmake ..
Compile: cmake --build .
The compiled game will be in build/Snake_SFML.exe

Project Structure

classes/: Contains the game class definitions
SFML/: Main files and entry point
police/: Fonts used in the game
audio/: Sound files

Future Improvements

Add multiplayer mode
Implementation of power-ups
Levels with obstacles
Online leaderboard
