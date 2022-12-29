# NotStonksBank

Création d'une banque simplifié


## Répartition des taches

- Remy : Aide sur la lecture xml et Affichage Graphique
- Juliannnnnnne : Affichage graphique 
- Julien : Affichage graphique
- Romain : Communication des sockets, parsing, morteur


## Utilisation :
 Pour utiliser le projet merci de suivre la démarche suivante : 
 - Executer le Serveur TCP en executant Serveur.exe dans le dossier Bande_Centrale
 - Executer l'agence de votre choix dans l'un des dossier Agence
 - C'est tout bon ! 


### Piste D'amélioration : 

- Faire en sorte qu'une agence puisse recevoir plusieurs virement a la fois ( faut faire du parsing...) Prio 2/5
- Trier les Bdd avec une méthode de tri puissante ( Tri fusion ?) Prio 1/5
- Si tri actif => Recherche dichotomique Prio 1/5
- Faire en sorte que l'on puisse rentrer des floatant Prio 2/5 ( Double Double)
- Faire un cryptage sur les sockets pour qu'on ne puisse pas faire une attaque d'homme du milieu Prio 1/5


### Liste des commandes :
 - 0/Id_agence Envoie toutes les t sec (Automatique)
  - 1/id_client/nom/prenom/adresse/telephone/Id_compte_courant/solde_courant/Id_compte_epargne1/solde_epargne1/Id_compte_epargne2/solde_epargne2 ... Envoie la Bdd (Autoatique)
  - 2/Id_bank Renvoie l'id du prochain client
  - 3/Id_client Recherche un client et renvoie toutes les infos
  - 4/Id_client Recherche et connection
  - 5/Id_client Supprime un client
  - 6/Id_compte/argent Virement
  - 7 N'existe pas
  - 8 N'existe pas
  - 9/Id_agence Fermeture du serveur client
