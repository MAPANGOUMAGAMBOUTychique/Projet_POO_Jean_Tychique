#pragma once
#include <filesystem>
#include <fstream>
#include "Grille.h"
#include "SFInterface.h"
#include <typeinfo>
class Jeu
{
private:
	Grille* grille;
public:
	Jeu(Grille* grille);
	~Jeu();
	Grille* getGrille() const ;
	void setGrille(Grille* grille);
	Grille* incrementerGeneration();
	void modeConsole(int iterations, string nomfichier);
	void modeGraphique(int iterations, double periode);
	void testUnitaire(string nomFichInitial, string nomFichAttendu, int iterations);
};

