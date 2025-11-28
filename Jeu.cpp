#include "Jeu.h"

Jeu::Jeu(Grille* grille) : grille(grille) {}

Jeu::~Jeu() {
	delete grille;
}

Grille* Jeu::getGrille() const {
	return grille;
}

Grille* Jeu::incrementerGeneration() {
	int nbVoisinsVivants = 0;
	Grille* nouvelleGrille = new Grille(grille->getNbLignes(), grille->getNbColonnes());

	for (int i = 0; i < grille->getNbLignes(); i++) {
		for (int j = 0; j < grille->getNbColonnes(); j++) {
			nbVoisinsVivants = 0;
			// Compter les voisins vivants
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (x == 0 && y == 0) continue; // Ignorer la cellule elle-même
					int voisinX = i + x;
					int voisinY = j + y;
					if (voisinX >= 0 && voisinX < grille->getNbLignes() &&
						voisinY >= 0 && voisinY < grille->getNbColonnes()) {
						if (dynamic_cast<CelluleVivante*>(grille->getCellule(voisinX, voisinY)) != nullptr) {
							nbVoisinsVivants++;
						}
					}
				}
			}
			// Appliquer les règles du jeu
			Cellule* celluleActuelle = grille->getCellule(i, j);
			if (dynamic_cast<CelluleVivante*>(celluleActuelle) != nullptr) {
				// Cellule vivante
				if (nbVoisinsVivants < 2 || nbVoisinsVivants > 3) {
					nouvelleGrille->setCellule(i, j, new CelluleMorte(i, j)); // Meurt
				} else {
					nouvelleGrille->setCellule(i, j, new CelluleVivante(i, j)); // Reste vivante
				}
			} 
			else if (dynamic_cast<CelluleMorte*>(celluleActuelle) != nullptr){
				// Cellule morte
				if (nbVoisinsVivants == 3) {
					nouvelleGrille->setCellule(i, j, new CelluleVivante(i, j)); // Revient à la vie
				} else {
					nouvelleGrille->setCellule(i, j, new CelluleMorte(i, j)); // Reste morte
				}
			}
			else {
				// Cellule obstacle ou autre type
				nouvelleGrille->setCellule(i, j, celluleActuelle); // Reste inchangée
			}
		}
	}
	delete grille;
	grille = nouvelleGrille;
	return grille;
}