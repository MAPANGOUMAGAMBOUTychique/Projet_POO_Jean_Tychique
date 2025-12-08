#include "Grille.h"

Grille::Grille(int nbLignes, int nbColonnes) : nbLignes(nbLignes), nbColonnes(nbColonnes)
{
	grille = new Cellule**[nbLignes];
	for (int i = 0; i < nbLignes; i++)
	{
		grille[i] = new Cellule*[nbColonnes];
		for (int j = 0; j < nbColonnes; j++)
		{
			grille[i][j] = new CelluleMorte(i, j);
		}
	}
}

Grille::Grille(const Grille& other) : nbLignes(other.nbLignes), nbColonnes(other.nbColonnes)
{
	grille = new Cellule**[nbLignes];
	for (int i = 0; i < nbLignes; i++)
	{
		grille[i] = new Cellule*[nbColonnes];
		for (int j = 0; j < nbColonnes; j++)
		{
			Cellule* cellule = other.getCellule(i, j);
			if (dynamic_cast<CelluleVivante*>(cellule) != nullptr)
			{
				grille[i][j] = new CelluleVivante(i, j);
			}
			else if (dynamic_cast<CelluleObstacle*>(cellule) != nullptr)
			{
				grille[i][j] = new CelluleObstacle(i, j);
			}
			else
			{
				grille[i][j] = new CelluleMorte(i, j);
			}
		}
	}
}

void Grille::initialiseGrille(std::ifstream& fichier)
{	
	fichier.clear();
	fichier.seekg(0);
	int l, c;
	fichier >> l >> c;
    for (int i = 0; i < nbLignes; i++)
    {
        for (int j = 0; j < nbColonnes; j++)
        {
            char caractere;
            fichier >> std::ws >> caractere; // Ajout de std::ws pour ignorer les espaces blancs
            if (caractere == '1')
            {
                setCellule(i, j, new CelluleVivante(i, j));
            }
            else if (caractere == 'X')
            {
                setCellule(i, j, new CelluleObstacle(i, j));
            }
            else
            {
                setCellule(i, j, new CelluleMorte(i, j));
            }
        }
    }
}


Grille::~Grille()
{
	for (int i = 0; i < nbLignes; i++)
	{
		for (int j = 0; j < nbColonnes; j++)
		{
			delete grille[i][j];
		}
		delete[] grille[i];
	}
	delete[] grille;
}

Cellule* Grille::getCellule(int x, int y) const
{
	return grille[x][y];
}

void Grille::setCellule(int x, int y, Cellule* cellule)
{
	delete grille[x][y]; // Libérer la mémoire de l'ancienne cellule
	grille[x][y] = cellule;
}

int Grille::getNbLignes() const
{
	return nbLignes;
}

int Grille::getNbColonnes() const
{
	return nbColonnes;
}

//bool Grille::operator ==(Grille grille) {
//	for (int i = 0; i < nbLignes; i++) {
//		for (int j = 0; j < nbColonnes; j++) {
//			if (getCellule(i, j) != grille.getCellule(i, j)) {
//				return false;
//			}
//		}
//	}
//	return true;
//}


bool Grille::operator==(const Grille& other) const {
	if (getNbLignes() != other.getNbLignes() || getNbColonnes() != other.getNbColonnes())
		return false;

	for (int i = 0; i < getNbLignes(); ++i) {
		for (int j = 0; j < getNbColonnes(); ++j) {
			Cellule* a = getCellule(i, j);
			Cellule* b = other.getCellule(i, j);

			if ((a == nullptr) != (b == nullptr)) // un est null et pas l'autre
				return false;

			if (a && b) {
				// comparer le type dynamique
				if (typeid(*a) != typeid(*b))
					return false;

				// si vous devez comparer d'autres propriétés (ex: état interne), ajoutez-les ici
			}
		}
	}
	return true;
}

void Grille::afficherGrille() const
{
	for (int i = 0; i < nbLignes; i++)
	{
		for (int j = 0; j < nbColonnes; j++)
		{
			if (dynamic_cast<CelluleVivante*>(grille[i][j]) != nullptr)
			{
				cout << "1 ";
			}
			else if (dynamic_cast<CelluleObstacle*>(grille[i][j]) != nullptr)
			{
				cout << "X ";
			}
			else
			{
				cout << "0 ";
			}
		}
		cout << endl;
	}
}