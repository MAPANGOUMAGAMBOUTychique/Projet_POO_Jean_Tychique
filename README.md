> ⚠️ **Note importante sur les contributions GitHub :**  
> En raison d'un problème technique sur mon ordinateur durant la période de réalisation du projet, mon binôme a dû effectuer l'ensemble des *commits* et *pushes* depuis sa propre machine. Bien que je n'apparaisse pas directement dans l'historique des contributeurs de ce dépôt, le projet a été entièrement conçu, développé et testé en **binôme équitable**.

---

# Jeu de la Vie de John Conway (C++ / SFML)

## À propos du projet
Ce projet académique a été réalisé en **binôme** entre **novembre et décembre 2025**. Il consiste en l'implémentation en **C++** du **Jeu de la Vie de John Conway**, un automate cellulaire célèbre simulant l'évolution d'une population de cellules au fil des générations selon des règles déterministes simples.

L'objectif principal était d'appliquer les principes fondamentaux de la **Programmation Orientée Objet (POO)** avancée et de garantir une **gestion rigoureuse de la mémoire**.

---

## Règles du Jeu

L'évolution de la grille s'effectue étape par étape selon les trois règles canoniques suivantes:

1. **Naissance :** Une cellule morte entourée d'exactement **3 voisines vivantes** devient vivante à la génération suivante.
2. **Survie :** Une cellule vivante entourée de **2 ou 3 voisines vivantes** reste vivante.
3. **Mise en valeur / Mort :** Dans tous les autres cas (sous-population ou surpopulation), la cellule meurt ou reste morte.

---

## Fonctionnalités Clés

* 🎮 **Mode Console :** Génération automatique de fichiers texte traçant chaque itération de la grille.
* 🖥️ **Mode Graphique (SFML) :** Visualisation en temps réel et rendu fluide de l'évolution des cellules grâce à la bibliothèque SFML.
* 🔄 **Grille Torique :** Les bords de la grille sont interconnectés (le haut communique avec le bas, la gauche avec la droite).
* 🧪 **Mode Test Unitaire :** Validation automatique des résultats et calculs des générations.
* 🧱 **Gestion des Obstacles :** Intégration de cellules obstacles spéciales qui restent inaltérées par les règles d'évolution.

---

## Architecture & Concepts POO

Le cœur de l'application repose sur une conception orientée objet modulaire et flexible:

* 🔒 **Encapsulation :** Attributs privés et accès strictly contrôlé via des *getters* et *setters*.
* 🏛️ **Héritage :** Définition d'une classe抽象/abstraite `Cellule`, dont dérivent :
  * `CelluleVivante`
  * `CelluleMorte`
  * `CelluleObstacle`
* ⚡ **Polymorphisme :** Utilisation de `dynamic_cast` pour un traitement uniforme et dynamique des différents types de cellules.

---

## Gestion de la Mémoire

Afin de garantir la stabilité et la performance du programme :
* **Allocation Dynamique :** La taille de la grille est définie à l'exécution pour une flexibilité maximale.
* **Libération Sécurisée :** Association explicite de chaque allocation `new` avec son `delete` correspondant via les destructeurs.
* **Prévention des Fuites Mémoire :** Implémentation d'un constructeur de copie profonde et gestion explicite lors de la méthode `incrementerGeneration()`.

---

## Stack Technique

* **Langage principal :** C++ (C++17 ou supérieur) orienté objet
* **Langages complémentaires :** C / C++
* **Bibliothèque graphique :** SFML 2.x pour l'affichage interactif
* **Gestion de versions :** Git & GitHub
* **Compilateur :** Compatible GCC / Clang / MSVC (C++17+)

---

👥 *Projet réalisé en binôme dans le cadre du cursus académique (Nov - Déc 2025).*
