#include <SFML/Graphics.hpp>
#include "inputHandler.h"
#include "main.h"

int windowWidth = 1000;
int windowHeight = 1000;
int squareSize = 10; // Size of each cell in pixels
int spacing = 1; // Spacing between cells
bool mousePressed = false;
bool mousePressedRight = false;
int mouseX, mouseY;
bool isRunning = false;// Flag to control the simulation state
int gameSpeed = 50; // Speed of the game in milliseconds

int main(){

int timerNextGeneration = 0; // Timer for next generation update
int cellStep = squareSize + spacing; // Calculate the total size of each cell including spacing
int cells [windowWidth/cellStep][windowHeight/cellStep]={0};
int  gridX, gridY;
int gridWidth = windowWidth / cellStep;
int gridHeight = windowHeight / cellStep;


sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
	"Kat's Game of Life");
window.clear(sf::Color::Black);

sf::RectangleShape cell(sf::Vector2f(squareSize,squareSize));
cell.setFillColor(sf::Color::Green);

while (window.isOpen()) {
//event loop. receives keyboard and mouse events

inputHandler(window, &cells[0][0], gridHeight, gridWidth, cellStep);

//render stage
if(isRunning) 
{// Update cells based on Game of Life rules
if(timerNextGeneration < gameSpeed) {
	timerNextGeneration++; // Increment timer
}
else{
timerNextGeneration = 0; // Reset timer
nextGeneration(&cells[0][0], windowWidth, windowHeight); // Call the function to update cells
}
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


int editCell(int *cells,int gridX,int gridY,int cellStep,int alive ) {
	int gridWidth = windowWidth / cellStep;
	if(gridX >= 0 && gridX < windowWidth / cellStep &&
		gridY >= 0 && gridY < windowHeight / cellStep) {
					cells[gridY+gridX*gridWidth] = alive;
				}
				return 0; // Return 0 to indicate success
}

int nextGeneration(int* cells, int width, int height) 
{//handles moving to the next generation of cells
	int cellStep = squareSize + spacing; // Calculate the total size of each cell including spacing
	int gridWidth = width / cellStep;
	int gridHeight = height / cellStep;
	int* newCells = new int[gridWidth * gridHeight](); // Temporary array for new state

	//grid loop
	for(int j=0; j<gridHeight; j++) {
		for(int i=0; i<gridWidth; i++) {
			int idx = j * gridWidth + i;
			int aliveNeighbors = 0;
			// Check all 8 neighbors
			for(int y = -1; y <= 1; y++) {
				for(int x = -1; x <= 1; x++) {
					if(x == 0 && y == 0) continue;// Skip the cell itself
					int ni = i + x;//neighbor index x
					int nj = j + y;//neighbor index y
					if(ni >= 0 && ni < gridWidth && nj >= 0 && nj < gridHeight) {// Check bounds
						if(cells[nj * gridWidth + ni] == 1) aliveNeighbors++;// Count alive neighbors
					}
				}
			}
			//current cell=: original state if 2 neighbors, plus alive if 3 neighbors
			newCells[idx]=cells[idx]*(aliveNeighbors ==2? 1 : 0) + 1*(aliveNeighbors==3?1:0); // Default to current state, update based on neighbors
			/*commented code for reference of original logic
			if ((aliveNeighbors < 2 || aliveNeighbors > 3)) {
				newCells[idx] = 0; // Cell dies if less than 2 or more than 3 neighbors
			}
			else if(aliveNeighbors == 3) {
				newCells[idx] = 1; // Cell becomes alive if exactly 3 neighbors
			}
			else{
				newCells[idx] = cells[idx]; // Cell remains the same, still adds to newCells for later update
			}
				*/
		}
	}// end of grid loop
	// Update the original cells array with the new state
	for(int j=0; j<gridHeight; j++) {
		for(int i=0; i<gridWidth; i++) {
			int idx = j * gridWidth + i;// Calculate the index in the 1D array
			cells[idx] = newCells[idx]; // Update the original cells array
		}
	}
delete[] newCells;// Free the temporary array
return 0;
}// end of nextGeneration