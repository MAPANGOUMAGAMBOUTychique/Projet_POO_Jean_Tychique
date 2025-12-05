#include "SFInterface.h"

SFInterface::SFInterface(int width, int height, float cellSize)
	: width(width), height(height), cellSize(static_cast<int>(cellSize)),
	window(sf::VideoMode(width * cellSize, height * cellSize), "Game of Life")
{
}


SFInterface::~SFInterface()
{
}
sf::RenderWindow& SFInterface::getWindow() {
	return window;
}

void SFInterface::closeWindow() {
	window.close();
}

void SFInterface::renderGrid(const Grille* grid) {
	int x, y;
	window.clear();
	sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			if (dynamic_cast<CelluleVivante*>(grid->getCellule(x, y)) != nullptr) {
				cell.setPosition(y * cellSize, x * cellSize);
				window.draw(cell);
			}
			else if (dynamic_cast<CelluleObstacle*>(grid->getCellule(x, y)) != nullptr) {
				cell.setFillColor(sf::Color::Red);
				cell.setPosition(y * cellSize, x * cellSize);
				window.draw(cell);
				cell.setFillColor(sf::Color::White);
			}
			else {
				cell.setFillColor(sf::Color::Magenta);
				cell.setPosition(y * cellSize, x * cellSize);
				window.draw(cell);
				cell.setFillColor(sf::Color::White);
			}
		}
	}
	window.display();
}