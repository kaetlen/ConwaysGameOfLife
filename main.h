#ifndef MAIN_HPP

#include <SFML/Graphics.hpp>

int main();
int nextGeneration(int* cells, int width, int height);
int editCell(int *cells, int gridX, int gridY, int cellStep ,int alive);
int inputHandler(sf::RenderWindow &window, int *cells, int gridHeight, int gridWidth, int cellStep);


#define MAIN_HPP
#endif // MAIN_HPP

