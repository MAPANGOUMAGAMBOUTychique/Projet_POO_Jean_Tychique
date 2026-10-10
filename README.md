> ⚠️ **Note importante sur les contributions GitHub :**  
> En raison d'un problème technique sur mon ordinateur durant la période de réalisation du projet, mon binôme a dû effectuer l'ensemble des *commits* et *pushes* depuis sa propre machine. Bien que je n'apparaisse pas directement dans l'historique des contributeurs de ce dépôt, le projet a été entièrement conçu, développé et testé en **binôme équitable**.

---

# Jeu de la Vie de John Conway (C++ / SFML)

## À propos du projet
Ce projet académique a été réalisé en **binôme** entre **novembre et décembre 2025**. Il consiste en l'implémentation en **C++** du **Jeu de la Vie de John Conway**, un automate cellulaire célèbre simulant l'évolution d'une population de cellules au fil des générations selon des règles déterministes simples[cite: 1].

L'objectif principal était d'appliquer les principes fondamentaux de la **Programmation Orientée Objet (POO)** avancée et de garantir une **gestion rigoureuse de la mémoire**[cite: 4, 5].

---

## Règles du Jeu

L'évolution de la grille s'effectue étape par étape selon les trois règles canoniques suivantes[cite: 1] :

1. **Naissance :** Une cellule morte entourée d'exactement **3 voisines vivantes** devient vivante à la génération suivante[cite: 1].
2. **Survie :** Une cellule vivante entourée de **2 ou 3 voisines vivantes** reste vivante[cite: 1].
3. **Mise en valeur / Mort :** Dans tous les autres cas (sous-population ou surpopulation), la cellule meurt ou reste morte[cite: 1].

---

## Fonctionnalités Clés

* 🎮 **Mode Console :** Génération automatique de fichiers texte traçant chaque itération de la grille[cite: 2].
* 🖥️ **Mode Graphique (SFML) :** Visualisation en temps réel et rendu fluide de l'évolution des cellules grâce à la bibliothèque SFML[cite: 2, 3].
* 🔄 **Grille Torique :** Les bords de la grille sont interconnectés (le haut communique avec le bas, la gauche avec la droite)[cite: 2].
* 🧪 **Mode Test Unitaire :** Validation automatique des résultats et calculs des générations[cite: 2].
* 🧱 **Gestion des Obstacles :** Intégration de cellules obstacles spéciales qui restent inaltérées par les règles d'évolution[cite: 2, 4].

---

## Architecture & Concepts POO

Le cœur de l'application repose sur une conception orientée objet modulaire et flexible[cite: 4] :

* 🔒 **Encapsulation :** Attributs privés et accès strictly contrôlé via des *getters* et *setters*[cite: 4].
* 🏛️ **Héritage :** Définition d'une classe抽象/abstraite `Cellule`[cite: 4], dont dérivent :
  * `CelluleVivante`[cite: 4]
  * `CelluleMorte`[cite: 4]
  * `CelluleObstacle`[cite: 4]
* ⚡ **Polymorphisme :** Utilisation de `dynamic_cast` pour un traitement uniforme et dynamique des différents types de cellules[cite: 4].

---

## Gestion de la Mémoire

Afin de garantir la stabilité et la performance du programme[cite: 5] :
* **Allocation Dynamique :** La taille de la grille est définie à l'exécution pour une flexibilité maximale[cite: 5].
* **Libération Sécurisée :** Association explicite de chaque allocation `new` avec son `delete` correspondant via les destructeurs[cite: 5].
* **Prévention des Fuites Mémoire :** Implémentation d'un constructeur de copie profonde et gestion explicite lors de la méthode `incrementerGeneration()`[cite: 5].

---

## Stack Technique

* **Langage principal :** C++ (C++17 ou supérieur) orienté objet[cite: 3]
* **Langages complémentaires :** C / C++[cite: 3]
* **Bibliothèque graphique :** SFML 2.x pour l'affichage interactif[cite: 3]
* **Gestion de versions :** Git & GitHub[cite: 3]
* **Compilateur :** Compatible GCC / Clang / MSVC (C++17+)[cite: 3]

---

👥 *Projet réalisé en binôme dans le cadre du cursus académique (Nov - Déc 2025).*
