#include <SFML/Graphics.hpp>
#include "inputHandler.h"
#include "main.h"


int inputHandler(sf::RenderWindow& window, int* cells,int gridHeight, int gridWidth,int cellStep){
	int gridX=mouseX/cellStep;
	int gridY=mouseY/cellStep;

	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
		 	window.close();}//close window

		//mouse events
		if(event.type == sf::Event::MouseButtonPressed){
			mouseX = event.mouseButton.x;
			mouseY = event.mouseButton.y;
			gridX = mouseX / cellStep;
			gridY = mouseY / cellStep;
			// Check which button was pressed for drawing or killing cells
			//draw cell on left click
			if(event.mouseButton.button == sf::Mouse::Left) {
				mousePressed = true;
				editCell(cells, gridX, gridY, cellStep, 1); // Call editCell to mark the cell alive
			}
			//kill cell on right click
			else if(event.mouseButton.button == sf::Mouse::Right) {
				mousePressedRight = true;
				editCell(cells, gridX, gridY, cellStep, 0); // Call editCell to kill the cell
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
				editCell(cells, gridX, gridY, cellStep, 1); // Call editCell to update the cell state
				// if(gridX >= 0 && gridX < windowWidth / cellStep &&
				// 	gridY >= 0 && gridY < windowHeight / cellStep) {
				// 	cells[gridX][gridY] = 1;
				// }
			}
			if(mousePressedRight) {
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
				gridX = mouseX / cellStep; // Calculate grid position
			    gridY = mouseY / cellStep;
				editCell(cells, gridX, gridY, cellStep, 0); // Call editCell to update the cell state
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
			if(event.key.code == sf::Keyboard::R) {
				isRunning = false; // Stop the simulation when resetting
				for(int j=0; j<gridHeight; j++) {// Loop through each row in the grid
					for(int i=0; i<gridWidth; i++) {// Loop through each cell in the row
						cells[i*gridWidth+j] = 0; // Reset all cells to dead state
						}
					}
				}
			if(event.key.code == sf::Keyboard::Left){
				if(gameSpeed < 500) {
					gameSpeed += 10; // Increase game speed
				}
			}
			if(event.key.code == sf::Keyboard::Right){
				if(gameSpeed > 0) {
					gameSpeed -= 10; // Decrease game speed
				}
			}
			}//end of keyboard event
	
		}//end of event loop
		return 0; // Return 0 to indicate success
}// end of inputHandler