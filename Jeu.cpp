#include "Jeu.h"

Jeu::Jeu(Grille* grille) : grille(grille) {}

Jeu::~Jeu() {
}

Grille* Jeu::getGrille() const {
	return grille;
}

void Jeu::setGrille(Grille* grille) {
	this->grille = grille;
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
					if (voisinX == -1) voisinX = grille->getNbLignes() - 1;
					if (voisinY == -1) voisinY = grille->getNbColonnes() - 1;
					if (voisinX == grille->getNbLignes()) voisinX = 0;
					if (voisinY == grille->getNbColonnes()) voisinY = 0;
					if (dynamic_cast<CelluleVivante*>(grille->getCellule(voisinX, voisinY)) != nullptr) {
						nbVoisinsVivants++;
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
				nouvelleGrille->setCellule(i, j, new CelluleObstacle(i, j)); // Reste inchangée
			}
		}
	}
	delete grille;
	grille = nouvelleGrille;
	return grille;
}

void Jeu::modeConsole(int iterations, string nomfichier) {
	for (int i = 0; i < iterations; i++) {
		setGrille(incrementerGeneration());
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


void Jeu::modeGraphique(int iterations, double periode) {
	int cellSize = 10;
	SFInterface sfInterface(grille->getNbLignes(), grille->getNbColonnes(), cellSize);
	sfInterface.renderGrid(grille);

	int generation = 0;
	bool jeuTermine = false;

	while (sfInterface.getWindow().isOpen()) {
		if (!jeuTermine){
			sf::Event event;
			while (sfInterface.getWindow().pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					sfInterface.closeWindow();
			}

			Grille ancienGrille(*grille);
			setGrille(incrementerGeneration());
			sfInterface.renderGrid(grille);
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

void Jeu::testUnitaire(string nomFichInitial, string nomFichAttendu, int iterations) {
	ifstream fichierInitial(nomFichInitial, ios::in);
	if (!fichierInitial) {
		cout << "Fichier initial non trouve !" << endl;
		exit(1);
	}
	int nblignes, nbcolonnes;
	fichierInitial >> nblignes >> nbcolonnes;
	Grille* grilleInitiale = new Grille(nblignes, nbcolonnes);
	grilleInitiale->initialiseGrille(fichierInitial);
	fichierInitial.close();
	delete this->grille;
	this->grille = grilleInitiale;

	for (int i = 0; i < iterations; i++) {
		setGrille(incrementerGeneration());
	}
	ifstream fichierAttendu(nomFichAttendu, ios::in);
	if (!fichierAttendu) {
		cout << "Fichier attendu non trouve !" << endl;
		exit(1);
	}
	int nblignesAttendu, nbcolonnesAttendu;
	if (!(fichierAttendu >> nblignesAttendu >> nbcolonnesAttendu)) {
		cout << "Erreur lecture entete fichier attendu" << endl;
		return;
	}
	Grille* grilleAttendue = new Grille(nblignesAttendu, nbcolonnesAttendu);
	grilleAttendue->initialiseGrille(fichierAttendu);
	fichierAttendu.close();
	if (*this->grille == *grilleAttendue) {
		cout << "\nFichier attendu et fichier obtenu sont identiques. Test unitaire reussi !" << endl;
	}
	else {
		cout << "\nFichier attendu et fichier obtenu sont differents. Test unitaire echoue !" << endl;
	}
	delete grilleAttendue;
}