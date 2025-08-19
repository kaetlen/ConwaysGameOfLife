#ifndef MAIN_HPP
#define MAIN_HPP
#include <SFML/Graphics.hpp>

int main();
int nextGeneration(int* cells, int width, int height);
int editCell(int *cells, int gridX, int gridY, int cellStep ,int alive);
//int inputHandler(sf::RenderWindow &window, int *cells, int gridHeight, int gridWidth, int cellStep);

extern int windowWidth;
extern int windowHeight;
extern int squareSize; // Size of each cell in pixels
extern int spacing ; // Spacing between cells
extern bool mousePressed;
extern bool mousePressedRight;
extern int mouseX, mouseY;
extern bool isRunning;// Flag to control the simulation state



#endif // MAIN_HPP

