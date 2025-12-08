#pragma once
#include "Cellule.h"
#include "CelluleMorte.h"
#include "CelluleVivante.h"
#include "CelluleObstacle.h"
#include <iostream>
#include <fstream>
using namespace std;

class Grille
{
private :
	int nbLignes;
	int nbColonnes;
	Cellule*** grille;
public:
	Grille(int nbLignes, int nbColonnes);
	Grille(const Grille& other);
	~Grille();
	void initialiseGrille(std::ifstream& fichier);
	Cellule* getCellule(int x, int y) const;
	void setCellule(int x, int y, Cellule* cellule);
	int getNbLignes() const;
	int getNbColonnes() const;
	//bool operator ==(Grille grille);
	bool operator==(const Grille& other) const;
	void afficherGrille() const;
};


