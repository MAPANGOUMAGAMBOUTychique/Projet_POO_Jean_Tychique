#include <iostream>
#include <fstream>
#include "Jeu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <filesystem>
using namespace std;



void renderGrid(sf::RenderWindow& window, int gridWidth, int gridHeight, int cellSize, const Grille* grid);
const int cellSize = 10;
void modeConsole(Grille* grille, int iterations, string nomfichier);
void modeGraphique(Grille* grille, int nblignes, int nbcolonnes, int iterations, int periode);

int main()
{
	cout << "Bienvenu dans le jeu de la vie !" << endl;
	string nomfichier;
	cout << "Saisissez le chemin du fichier de configuration (ex : fich.txt) : " << endl;
	cin >> nomfichier;
	ifstream fichier(nomfichier, ios::in);
	if (!fichier) {
		cout << "Fichier non trouve !" << endl;
		exit(1);
	}
	int nblignes, nbcolonnes;
	fichier >> nblignes >> nbcolonnes;

	Grille* grille = new Grille(nblignes, nbcolonnes);

	// Initialisation de la grille à partir du fichier
	for (int i = 0; i < nblignes; i++) {
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


	char mode;
	cout << "\nEn quel mode voulez-vous lancer le jeu ? Console (C) ou Graphique (G) " << endl;
	cin >> mode;
	int iterations;
	if (mode == 'C') {
		cout << "Combien de générations voulez-vous ? " << endl;
		cin >> iterations;
		modeConsole(grille, iterations, nomfichier);
		cout << "Jeu terminé ! Retrouvez les générations du jeu dans le dossier :" << nomfichier << "_out" << endl;
	}
	else if (mode == 'G') {
		float periode;
		cout << "Combien de générations voulez-vous ? Saisir 999 pour infini" << endl;
		cin >> iterations;
		cout << "Periode d'evolution en second (ex: 0.5, 1, 3..) ? ";
		cin >> periode;
		modeGraphique(grille, nblignes, nbcolonnes, iterations, periode);
	}
	else cout << "Commande introuvable! Veuillez réssayer.";

	return 0;
}



void renderGrid(sf::RenderWindow& window, int gridWidth, int gridHeight,int cellSize, const Grille* grid) {
	int x, y;

	window.clear();
	sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
	for (x = 0; x < gridWidth; x++) {
		for (y = 0; y < gridHeight; y++) {
			if (dynamic_cast<CelluleVivante*>(grid->getCellule(x, y)) != nullptr) {
				cell.setPosition(y * cellSize, x * cellSize);
				window.draw(cell);
			}
		}
	}
	window.display();
}


void modeConsole(Grille* grille, int iterations, string nomfichier) {
	Jeu jeu(grille);
	for (int i = 0; i < iterations; i++) {
		cout << "Generation " << i + 1 << " :" << endl << endl;
		grille = jeu.incrementerGeneration();
		string nomDossier;
		nomDossier = nomfichier + "_out";
		if (!filesystem::exists(nomDossier)) {
			filesystem::create_directory(nomDossier);
		}
		ofstream fichier(nomDossier + "/"+nomfichier + "_G" + to_string(i + 1) + ".txt", ios::out);
		fichier << grille->getNbLignes() << " " << grille->getNbColonnes() << endl;
		for (int x = 0; x < grille->getNbLignes(); x++) {
			for (int y = 0; y < grille->getNbColonnes(); y++) {
				Cellule* cellule = grille->getCellule(x, y);
				if (dynamic_cast<CelluleVivante*>(cellule) != nullptr) {
					fichier << '1' << " ";
				}
				else if (dynamic_cast<CelluleMorte*>(cellule) != nullptr) {
					fichier << '0' << " ";
				}
				else if (dynamic_cast<CelluleObstacle*>(cellule) != nullptr) {
					fichier << 'X' << " ";
				}
			}
			fichier << endl;
		}
		fichier.close();
	}
}


void modeGraphique(Grille* grille, int nblignes, int nbcolonnes, int iterations, int periode) {
	sf::RenderWindow window(sf::VideoMode(nbcolonnes * cellSize, nblignes * cellSize), "Game of Life");
	renderGrid(window, nblignes, nbcolonnes, cellSize, grille);
	Jeu jeu(grille);
	int generation = 0;
	bool jeuTermine = false;

	while (window.isOpen()) {
		if (!jeuTermine){
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			Grille ancienGrille(*grille);
			grille = jeu.incrementerGeneration();
			system("cls");
			renderGrid(window, nblignes, nbcolonnes, cellSize, grille);
			generation++;

			if (iterations != 999 && generation >= iterations) {
				cout << "Jeu terminé !";
				jeuTermine = true;
			}
			else if (iterations == 999 && ancienGrille == *grille) {
				cout << "Jeu terminé, car les generations n'evoluent plus après " << generation - 1 << "iterations." << endl;
				jeuTermine = true;
			}
		}

		sf::sleep(sf::seconds(periode));
	}
	
}