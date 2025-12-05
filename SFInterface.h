#pragma once
#include "Grille.h"
#include <SFML/Graphics.hpp>
class SFInterface
{
private:
	int width;
	int height;
	int cellSize;
	sf::RenderWindow window;
public:
	SFInterface(int width, int height, float cellSize);
	~SFInterface();
	sf::RenderWindow& getWindow();
	void closeWindow();
	void renderGrid(const Grille* grid);
	
};

