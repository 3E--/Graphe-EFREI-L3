# Théorie des graphe(EFREI L3) #

## A faire : ##

- **6) Fermeture Transitive :**
>     Il s’agit tout simplement de calculer le graphe correspondant à la fermeture transitive de celui chargé par votre programme à l’étape 2.
>     Le résultat doit être stocké dans une structure de données similaire à celle utilisée pour le premier graphe.
>     En fin de traitement, vous devez reprendre votre code fait pour l’étape 3 pour afficher le résultat de la fermeture transitive.


- **7) Lecture d’un tableau de contraintes :** 
>     Il est question ici de lire en entrée un fichier contenant des contraintes d’ordonnancement telles que vues en cours ou TD.
>     Le fichier peut avoir la structure suivante :
>     
>     4              //Nombre de tâches
>     1 10 2 -1      //La tâche 1 a pour durée d’exécution ‘10’. Elle ne peut s’exécuter que lorsque la tâche 2 est terminée
>     2 20 3 -1      //Tâche 2 de durée ’20 ; la tâche 3 doit être terminée
>     3 30 -1        //Tâche 3 de durée ‘30 ‘ ; aucune contrainte
>     4 40 1 2 3 -1  //Tâche 4 de durée ‘40’ ; contraintes 1, 2 et 3
>     -1 
>     
>     Les tâches sont numérotées à partir de 1.
>     Lors de la lecture des contraintes, vous devez construire le graphe d’ordonnancement correspondant. Vous noterez dans l’exemple que les tâches sont numérotées à partir de 1, sans rupture de séquence. Le sommet « début des travaux » peut donc être le sommet ‘0’, et dans l’exemple ci-dessus la « fin des travaux » sera représentée par le sommet ‘5’. Ceci est en ligne avec les graphes que vous devez prendre en compte (voir point 1).
>     Au fur et à mesure de la lecture du fichier de contraintes, vous les afficherez à l’écran (pour vérifier que les bonnes informations sont lues.
>     En fin de lecture, vous devez afficher le graphe construit en reprenant votre code du point 3).


