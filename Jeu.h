#pragma once
#include "Grille.h"
class Jeu
{
private:
	Grille* grille;
public:
	Jeu(Grille* grille);
	~Jeu();
	Grille* getGrille() const ;
	Grille* incrementerGeneration();
};

