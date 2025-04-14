# Snake SFML

A classic Snake game developed in C++ with the SFML graphics library.

## Description

Control a snake moving on a game board, eat food to grow, and avoid hitting the walls or your own body. A modern version of the 90s classic!

## Installation

### Download and Play

1. Download the latest release from the "Releases" section
2. Extract the zip archive
3. Run `Snake_SFML.exe`

## How to Play

- **Arrow keys**: Control the snake
- **Escape**: Quit the game
- **Enter**: Select an option in the menu

## Technologies Used

- C++17
- SFML 2.6
- CMake

## Building from Source

### Prerequisites
- C++17 or higher
- CMake 3.0 or higher
- SFML 2.6 or higher

### Steps
1. Clone the repository: `git clone https://github.com/Anzzas/Snake_SFML.git`
2. Create a build directory: `mkdir build && cd build`
3. Generate build files: `cmake ..`
4. Compile: `cmake --build .`
5. The compiled game will be in `build/Snake_SFML.exe`

## Project Structure

- `classes/`: Contains the game class definitions
- `SFML/`: Main files and entry point
- `police/`: Fonts used in the game
- `audio/`: Sound files

Feel free to open an issue if you encounter any problems or have suggestions for improvement!
