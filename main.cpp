#include <SFML/Graphics.hpp>
#include "main.h"

int windowWidth = 1000;
int windowHeight = 1000;
bool isRunning = false;// Flag to control the simulation state
bool mousePressed = false;
bool mousePressedRight = false;
int squareSize = 10; // Size of each cell in pixels
int spacing = 1; // Spacing between cells

int main(){

int cellStep = squareSize + spacing; // Calculate the total size of each cell including spacing
int cells [windowWidth/cellStep][windowHeight/cellStep]={0};
int mouseX, mouseY, gridX, gridY;
int gridWidth = windowWidth / cellStep;
int gridHeight = windowHeight / cellStep;


sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
	"Game of Life");
sf::RectangleShape cell(sf::Vector2f(squareSize,squareSize));


while (window.isOpen()) {
//event loop. receives keyboard and mouse events
	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
		 	window.close();}//close window

			
			
		//mouse events
		if(event.type == sf::Event::MouseButtonPressed){
			
			mouseX = event.mouseButton.x;
			mouseY = event.mouseButton.y;
			if(event.mouseButton.button == sf::Mouse::Left) {
				mousePressed = true;
				gridX = mouseX / cellStep; // Calculate grid position
				gridY = mouseY / cellStep;

				if (gridX >= 0 && gridX < windowWidth / cellStep && 
					gridY >= 0 && gridY < windowHeight / cellStep) {
					cells[gridX][gridY] = 1;//make cell alive
				}
			}
			else if(event.mouseButton.button == sf::Mouse::Right) {
				mousePressedRight = true;
				gridX = mouseX / cellStep;
				gridY = mouseY / cellStep;

				if (gridX >= 0 && gridX < windowWidth / cellStep && 
					gridY >= 0 && gridY < windowHeight / cellStep) {
					cells[gridX][gridY] = 0;//kill cell
				}
			}
	}//end of mouse button event

	//mouse button release event
		if(event.type == sf::Event::MouseButtonReleased){
			if(event.mouseButton.button == sf::Mouse::Left) {
				mousePressed = false;
			}
			if(event.mouseButton.button == sf::Mouse::Right) {
				mousePressedRight = false;
			}
		}//end of mouse button release event
		
		//mouse move event
		if(event.type == sf::Event::MouseMoved) {
			if(mousePressed) {
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
				gridX = mouseX / cellStep; // Calculate grid position
			    gridY = mouseY / cellStep;
				if(gridX >= 0 && gridX < windowWidth / cellStep &&
					gridY >= 0 && gridY < windowHeight / cellStep) {
					cells[gridX][gridY] = 1;
				}
			}
			if(mousePressedRight) {
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
				gridX = mouseX / cellStep; // Calculate grid position
			    gridY = mouseY / cellStep;
				if(gridX >= 0 && gridX < windowWidth / cellStep &&
					gridY >= 0 && gridY < windowHeight / cellStep) {
					cells[gridX][gridY] = 0;
				}
			}
		}//end of mouse move event

		//keyboard events
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Space) {
				isRunning = !isRunning; // Toggle running state
			}
			if(event.key.code == sf::Keyboard::Escape) {
				window.close();// Close the window on escape key press
			}
		}
	
		}//end of event loop

//render stage
window.clear(sf::Color::Black);
cell.setFillColor(sf::Color::Green);

if(isRunning) 
{// Update cells based on Game of Life rules
	nextGeneration(&cells[0][0], windowWidth, windowHeight); // Call the function to update cells
}


// Draw stage
for(int j=0; j<gridWidth;j++){// Loop through each row in the grid
	for(int i=0; i<gridHeight; i++){// Loop through each cell in the row
		cell.setFillColor(cells[i][j]==1 ? sf::Color::Green : sf::Color::Black);

		//set position of the cell as 0 + the offset*square size + offset for spacing
		cell.setPosition(0+i*10+i,0+j*10+j);
		window.draw(cell);
	}
}

window.display();
}//end of while open

return 0;
}// end of main

int nextGeneration(int* cells, int width, int height) {
	int cellStep = squareSize + spacing; // Calculate the total size of each cell including spacing
	int gridWidth = width / cellStep;
	int gridHeight = height / cellStep;

	int* newCells = new int[gridWidth * gridHeight](); // Temporary array for new state

	for(int j=0; j<gridHeight; j++) {
		for(int i=0; i<gridWidth; i++) {
			int idx = j * gridWidth + i;
			int aliveNeighbors = 0;
			// Check all 8 neighbors
			for(int y = -1; y <= 1; y++) {
				for(int x = -1; x <= 1; x++) {
					if(x == 0 && y == 0) continue;
					int ni = i + x;
					int nj = j + y;
					if(ni >= 0 && ni < gridWidth && nj >= 0 && nj < gridHeight) {
						if(cells[nj * gridWidth + ni] == 1) aliveNeighbors++;
					}
				}
			}
			if ((cells[idx] == 1)&& (aliveNeighbors < 2 || aliveNeighbors > 3)) {
				newCells[idx] = 0; // Cell dies
			}
			else if(cells[idx] == 0 && aliveNeighbors == 3) {
				newCells[idx] = 1; // Cell becomes alive
			}
			else{
				newCells[idx] = cells[idx]; // Cell remains the same
			}
		}
	}

	for(int j=0; j<gridHeight; j++) {
		for(int i=0; i<gridWidth; i++) {
			int idx = j * gridWidth + i;
			cells[idx] = newCells[idx]; // Update the original cells array
		}
	}
	delete[] newCells;
	
	return 0;
}