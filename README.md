Rapport du projet CY-FESt :
Membres de l’équipe : Maxime Esnoult,Diego de la Fuente,Ninjbaatar 
Année d’étude :2023-2024
Classe :Pre-Ing 1 Supméca
Introduction :
          Le projet CY'FEST a pour but de créer un programme permettant la gestion des différentes scènes d’un festival où les participants doivent réserver et payer leurs places pour les concerts. Le système est conçu pour être utilisé tant par les gestionnaires (mode manager) que par les festivaliers (mode festivalier).
Objets Techniques :
		Gestion efficace des fichiers pour la sauvegarde des données entre les exécutions.
		Utilisation intensive de l’allocation dynamique pour gérer les données en mémoire.
		Conception d’une interface utilisateur claire pour faciliter les réservations et la gestion.
Problèmes Rencontrés et Solutions Apportées
Problème 1 : Gestion de la mémoire dynamique pour éviter les fuites de mémoire.
		Solution : Utilisation de fonctions pour allouer et libérer systématiquement la mémoire allouée dynamiquement pour les artistes et les concerts.
Problème 2 : Gestion de l'interface utilisateur pour faciliter la navigation entre les différents modes sans stopper le programme.
		Solution : Implémentation d'une boucle principale avec un menu permettant de basculer entre les modes sans quitter le programme.
Problème 3 : Sauvegarde et chargement des configurations des salles entre les exécutions.
		Solution : Écriture et lecture des données des salles dans des fichiers textes pour persister l'état entre les sessions.
Problème 4 :Les couleurs et le caractère lors de l’affichage de réservation.
		Solution : D’après de nombreux efforts nous n’avons pas pu palier à ce problème.  Comme solution une légende à été implémenté pour indiquer les catégories des différents rangées.
Problème 5 : Création de fosses
		Solution : À cause de nombreux problèmes techniques et afin de ne pas sacrifier la robustesse du code ni son fonctionnement nous avons décidé de ne pas implémenter la fonction fosse.
Répartition des taches:
Nous avons divisé le projet en deux groupes, celui du mode manager composé par Diego et Maxime, et le groupe du mode festivalier composé par Ninjibaatar. Pour ensuite faire la composition du code final tous ensemble.  Nous nous sommes organisés de cette manière car le mode manager prend plus de temps. 

Conclusion et Perspectives d'Avenir
Le projet a réussi à fournir une solution robuste pour la gestion d'un festival, avec une interface claire et une bonne gestion de la mémoire. Pour l'avenir, nous envisageons d'intégrer une visualisation graphique des salles pour améliorer encore l'expérience utilisateur et peut-être étendre notre système pour gérer plusieurs types d'événements.
