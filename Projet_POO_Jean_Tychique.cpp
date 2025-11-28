#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "Jeu.h"


int main()
{
	ifstream fichier("test.txt", ios::in);
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
	cout << "Generation initiale :" << endl << endl;
	grille->afficherGrille();

	Jeu jeu(grille);

	int generation = 0;
	while (true) {
		system("cls");
		std::cout << "Generation: " << generation++ << std::endl;
		grille = jeu.incrementerGeneration();
		grille->afficherGrille();
		cout << std::endl;
		this_thread::sleep_for(chrono::milliseconds(1000)); // Pause de 100 ms
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
}

 
