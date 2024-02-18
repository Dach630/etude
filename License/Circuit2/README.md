CAI Thierry,
CHENG Daniel,
ROMELE Gaspard,
VELANGANNI Jean Paul,

Rapport de Projet : Calcul de Trajectoire

1. De quoi s’agit-il ?

L’objectif de ce projet était de réaliser un programme permettant de calculer une trajectoire optimale avec différents algorithmes pour aller d’un point A à un point B dans un circuit en respectant les bords de la piste et en régulant sa vitesse. 
Nous avons donc travaillé sur un programme qui prend un fichier au format .ppm (ou Portable Pixmap Image File, une image de couleur formatée en un format de texte stockant chaque pixel avec un nombre) pour le convertir grâce à un parser en un circuit de course afin de réaliser nos calculs dessus.

2. Instructions

Après avoir téléchargé le code depuis la branche master de git, ouvrez un terminal et déplacez-vous dans le fichier contenant le code. Ecrivez ensuite “javac *.java”, puis “java main”. Ensuite :  
    
- Suivre les instructions affichées dans la console.
- Choisir un des circuits disponibles.
- Puis l’algorithme qui le parcourra ou choisir la fonctionnalité “Voiture” qui permet à l’utilisateur de parcourir de lui-même le circuit.

3. Fonctionnalités implémentées
    
Une fois l’objectif principal de ce projet accompli, nous avons décidé de mettre en place plusieurs fonctions qui permettent d’améliorer les performances et de rendre la navigation du programme plus simple. 
Nous avons également fait en sorte qu’un utilisateur puisse piloter un véhicule sur les circuits choisis, en nous inspirant de ce jeu : http://harmmade.com/vectorracer/#grindy

4.  Contributions de chacun

Nous avons principalement travaillé ensemble en nous réunissant régulièrement pour s’aider et résoudre les problèmes rencontrés. Nous nous sommes tout de même réparti les tâches afin que nous puissions travailler sur plusieurs aspects du projet en même temps: 

- Dans un premier temps, Daniel et Gaspard ont donc travaillé sur le code permettant de traduire un fichier .ppm en un circuit pouvant être parcouru, tandis que Thierry et Jean Paul écrivaient les fonctions de parcours en largeur du circuit.
- Ensuite, Thierry et Jean Paul ont travaillé sur l’algorithme de Dijkstra, qui sert à trouver le chemin le plus court possible pour se rendre du point de départ à l’arrivée. 
- Daniel et Gaspard se sont servis de cet algorithme pour rédiger la fonction aEtoile, qui est une fonction similaire à Dijkstra mais dont la vitesse d'exécution est optimisée.
- Enfin, Daniel a fait les parties permettant de piloter un véhicule ainsi que l’interface utilisateur.   
        
        
* Difficultés rencontrées

- La compréhension du projet, on a eu du mal à cerner les tâches que nous devions effectuer.
- Étant dans des groupes différents, nos emplois du temps ne nous permettaient pas d’avoir beaucoup de temps ensemble.
- Impossible de se rencontrer, ce qui rendait certains aspects du projet plus compliqué.
- Récupérer les informations des poly et les traduire en code comme pour les algorithmes (parcours en largeur, Dijkstra, A*).

