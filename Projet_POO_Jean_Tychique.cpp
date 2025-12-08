#include <iostream>
#include <fstream>
#include "Jeu.h"
#include "SFInterface.h"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
	cout << "Bienvenu dans le jeu de la vie !" << endl;
	string nomfichier;
	cout << "Saisissez le chemin du fichier de configuration sans l'extension (ex : fichierTest) : ";
	cin >> nomfichier;
	ifstream fichier(nomfichier + ".txt", ios::in);
	if (!fichier) {
		cout << "Fichier non trouve !" << endl;
		exit(1);
	}
	
	int nblignes, nbcolonnes;
	
	//Vérifions si le format attendue est respectée
	fichier >> nblignes >> nbcolonnes;
	for (char c; fichier.get(c); ) {
		if (!(c == '0' || c == '1' || c == 'X' || c == '\n' || c == ' ')) {
			cout << "Format du fichier incorrect ! Veuillez respecter le format attendu." << endl;
			exit(1);
			
		}
	}

	Grille* grille = new Grille(nblignes, nbcolonnes);

	// Initialisation de la grille à partir du fichier
	grille->initialiseGrille(fichier);
	fichier.close();

	Jeu jeu(grille);
	char mode;
	cout << "\nEn quel mode voulez-vous lancer le jeu ?" << endl << 		"C : Mode console\n"
		"G : Mode graphique\n"
		"T : Test unitaire\n"
		"Saisir C, G ou T : ";
	cin >> mode;
	int iterations;
	if (mode == 'C') {
		cout << "Combien de generations voulez-vous ? ";
		cin >> iterations;
		cout << "Mode console lance !" << endl;
		jeu.modeConsole(iterations, nomfichier);
		cout << "Jeu terminé ! Retrouvez les générations du jeu dans le dossier :" << nomfichier << "_out" << endl;
	}
	else if (mode == 'G') {
		double periode;
		cout << "Combien de generations voulez-vous ? Saisir 999 pour infini : ";
		cin >> iterations;
		cout << "Periode d'evolution en second (ex: 0.5, 1, 3..) ? ";
		cin >> periode;
		cout << "Mode graphique lance !" << endl;
		jeu.modeGraphique(iterations, periode);
		
	}
	else if (mode == 'T') {
		string nomFichInitial, nomFichAttendu;
		nomFichInitial = nomfichier + ".txt";
		cout << "Saisissez le chemin du fichier attendu (ex : fich_attendu) : ";
		cin >> nomFichAttendu;
		nomFichAttendu += ".txt";
		cout << "Combien de générations voulez-vous pour le test unitaire ? ";
		cin >> iterations;
		jeu.testUnitaire(nomFichInitial, nomFichAttendu, iterations);
	}
	else cout << "Commande introuvable! Veuillez réssayer.";

	return 0;
}
