#pragma once
#include "Cellule.h"
#include "CelluleMorte.h"
#include "CelluleVivante.h"
#include "CelluleObstacle.h"
#include <iostream>
using namespace std;

class Grille
{
private :
	int nbLignes;
	int nbColonnes;
	Cellule*** grille;
public:
	Grille(int nbLignes, int nbColonnes);
	~Grille();
	Cellule* getCellule(int x, int y) const;
	void setCellule(int x, int y, Cellule* cellule);
	int getNbLignes() const;
	int getNbColonnes() const;
	void afficherGrille() const;
};

