#include <iostream>
#include <fstream>
#include "Jeu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>



//void initializeGrid(int gridWidth, int gridHeight, std::vector<std::vector<int>>& grid);
void renderGrid(sf::RenderWindow& window, int gridWidth, int gridHeight, int cellSize, const Grille* grid);
const int cellSize = 10;

int main()
{
	
	
	ifstream fichier("test_.txt", ios::in);
	int ndlignes, nbcolonnes;

	fichier >> ndlignes >> nbcolonnes;

	
	Grille* grille = new Grille(ndlignes, nbcolonnes);
	for (int i = 0; i < ndlignes; i++) {
		for (int j = 0; j < nbcolonnes; j++) {
			char caractere;
			fichier >> caractere;
			if (caractere == '1') {
				grille->setCellule(i, j, new CelluleVivante(i, j));
			}
			else if (caractere == '0') {
				grille->setCellule(i, j, new CelluleMorte(i, j));
			}
			else if (caractere == 'X') {
				grille->setCellule(i, j, new CelluleObstacle(i, j));
			}
		}
	}
	fichier.close();
	//cout << "Generation initiale :" << endl << endl;
	grille->afficherGrille();
	
	//std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

	

	sf::RenderWindow window(sf::VideoMode(ndlignes * cellSize, nbcolonnes * cellSize), "Game of Life");
	renderGrid(window, ndlignes, nbcolonnes, cellSize, grille);
	Jeu jeu(grille);
	
	while (window.isOpen()) {

		grille = jeu.incrementerGeneration();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		system("cls");
		grille->afficherGrille();
		renderGrid(window, ndlignes, nbcolonnes, cellSize, grille);

		sf::sleep(sf::milliseconds(100));

	}


	/*
	Grille* grille = new Grille(5, 5);
	grille->setCellule(1, 2, new CelluleVivante(1, 2));
	grille->setCellule(2, 2, new CelluleVivante(2, 2));
	grille->setCellule(3, 2, new CelluleVivante(3, 2));
	grille->setCellule(2, 1, new CelluleVivante(2, 1));
	grille->setCellule(2, 3, new CelluleVivante(2, 3));
	grille->setCellule(0, 0, new CelluleVivante(0, 0));
	grille->afficherGrille();

	cout << "Generation suivante :" << endl << endl;

	Jeu jeu(grille);
	grille = jeu.incrementerGeneration();
	grille->afficherGrille();*/

	return 0;
}



/*
void initializeGrid(int gridWidth, int gridHeight, std::vector<std::vector<int>>& grid) {
	std::srand(std::time(0));
	for (int x = 0; x < gridWidth; ++x) {
		for (int y = 0; y < gridHeight; ++y) {
			grid[x][y] = std::rand() % 2;  // Randomly initialize cells as alive or dead
		}
	}
}*/

void renderGrid(sf::RenderWindow& window, int gridWidth, int gridHeight,int cellSize, const Grille* grid) {
	int x, y;

	window.clear();
	sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
	for (x = 0; x < gridWidth; x++) {
		for (y = 0; y < gridHeight; y++) {
			if (dynamic_cast<CelluleVivante*>(grid->getCellule(x, y)) != nullptr) {
				cell.setPosition(x * cellSize, y * cellSize);
				window.draw(cell);
			}
		}
	}
	window.display();
}
