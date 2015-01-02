
#include <petit-helwani-tp1-LectureFichier.h>
#include <petit-helwani-tp1-Exeption.h>
#include <vector>
#include "petit-helwani-tp1-AlgorithmesGraphe.h"
#include "FermetureTransitive.h"
#include <chrono>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace std::chrono;

int main(){
    typedef duration<long long, nano> nanoSecondes;

       //std::ofstream out("out.txt");
       //std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


    string pathFichierGraphe1="petit-helwani-tp1-g1.txt";
    string pathFichierGraphe2="petit-helwani-tp1-g2.txt";


    try {
        /*
         * CETTE PARTIE DU CODE EST SUCEPTIBLE DE GENERER DES ERREUR NOTAMENT LORS DE 'PARSAGE' DU FICHIER GRAPH
         * */

        /** ***************************
          * TRAITEMENT DU FICHIER 1
          * **************************/

        cout << "LECTURE DU FICHIER " <<pathFichierGraphe1 <<endl;
        const auto t1 = high_resolution_clock::now();

        // CREATION D'UN OBJECT QUI REPRESENTE UN GRAPHE ORIENTE EN MEMOIRE A PARTIR D'UN FICHIER REPRESENTANT UN GRAPHE
        GrapheOriente grapheOriente1 = LireFichier::graphe(pathFichierGraphe1);



        // AFFICHAGE SUR LA CONSOLE DE LA MATRICE ADJACENTE DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::matriceAdjacente(grapheOriente1);
        cout<<endl<<endl;

        // AFFICHAGE SUR LA CONSOLE LES ARCS DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::listeDesArcs(grapheOriente1);
        cout<<endl<<endl;

        // DETECTION DE CIRCUIT DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        GrapheOriente circuit1 = AlgorithmesGraphe::DetectionDeCircuit::eliminationSuccessiveDesPointsDEntree(grapheOriente1);
        cout<<endl<<endl;

        // TESTE SI IL Y A AU MOINS UN CIRCUIT DANS LE GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        if(circuit1.getListeDesSommets().empty()){

            // AFFICHAGE SUR LA CONSOLE LES SOMMETS AVANT LE CALCUL DE RANG DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
            AlgorithmesGraphe::Affichage::listeDesSommets(grapheOriente1);
            cout<<endl<<endl;

            // CALCUL DU RANG DE CHAQUE SOMMET DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
            AlgorithmesGraphe::calculDuRang(grapheOriente1);
            cout<<endl<<endl;
        }


        // AFFICHAGE SUR LA CONSOLE LES SOMMETS APRES LE CALCUL DE RANG (SI LE GRAPHE N'A PAS DE CIRCUIT) DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::listeDesSommets(grapheOriente1);



            GrapheOriente grapheOriente3 = AlgorithmesGraphe::FermetureTransitive(grapheOriente1);
            cout <<endl<< " le resultat de la fermeture transitive :"<<endl;

             // AFFICHAGE SUR LA CONSOLE DE LA MATRICE ADJACENTE DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
             AlgorithmesGraphe::Affichage::matriceAdjacente(grapheOriente3);
             cout<<endl<<endl;

             // AFFICHAGE SUR LA CONSOLE LES ARCS DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
             AlgorithmesGraphe::Affichage::listeDesArcs(grapheOriente3);
             cout<<endl<<endl;



        cout<<endl<<endl;
        /** ***************************
          * TRAITEMENT DU FICHIER 2
          * **************************/


        cout << "LECTURE DU FICHIER " <<pathFichierGraphe2 <<endl;

        /// ETAPE 2 : lecture a partir du fichier
        // CREATION D'UN OBJECT QUI REPRESENTE UN GRAPHE ORIENTE EN MEMOIRE A PARTIR D'UN FICHIER REPRESENTANT UN GRAPHE
        GrapheOriente grapheOriente2 = LireFichier::graphe(pathFichierGraphe2);

        /// ETAPE 3 : affichage
        // AFFICHAGE SUR LA CONSOLE DE LA MATRICE ADJACENTE DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::matriceAdjacente(grapheOriente2);
        cout<<endl<<endl;

        // AFFICHAGE SUR LA CONSOLE LES ARCS DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::listeDesArcs(grapheOriente2);
        cout<<endl<<endl;

        /// ETAPE 4 : Détection de circuit
        // DETECTION DE CIRCUIT DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        GrapheOriente circuit2 = AlgorithmesGraphe::DetectionDeCircuit::eliminationSuccessiveDesPointsDEntree(grapheOriente2);
        cout<<endl<<endl;

        // TESTE SI IL Y A AU MOINS UN CIRCUIT DANS LE GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        if(circuit2.getListeDesArcs().empty()){

            // AFFICHAGE SUR LA CONSOLE LES SOMMETS AVANT LE CALCUL DE RANG DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
            AlgorithmesGraphe::Affichage::listeDesSommets(grapheOriente2);
            cout<<endl<<endl;

            /// ETAPE 5 : Calcul de rang
            // CALCUL DU RANG DE CHAQUE SOMMET DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
            AlgorithmesGraphe::calculDuRang(grapheOriente2);
            cout<<endl<<endl;
        }

        // AFFICHAGE SUR LA CONSOLE LES SOMMETS APRES LE CALCUL DE RANG (SI LE GRAPHE N'A PAS DE CIRCUIT) DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
        AlgorithmesGraphe::Affichage::listeDesSommets(grapheOriente2);

        /// ETAPE 6

        if(!circuit2.getListeDesSommets().empty()) {

            GrapheOriente grapheOriente3 = AlgorithmesGraphe::FermetureTransitive(grapheOriente2);
            cout <<endl<< " le résultat de lafermeture transitive :"<<endl;

             // AFFICHAGE SUR LA CONSOLE DE LA MATRICE ADJACENTE DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
             AlgorithmesGraphe::Affichage::matriceAdjacente(grapheOriente3);
             cout<<endl<<endl;

             // AFFICHAGE SUR LA CONSOLE LES ARCS DU GRAPHE ORIENTE GENERER A PARTIR DU FICHIER
             AlgorithmesGraphe::Affichage::listeDesArcs(grapheOriente3);
             cout<<endl<<endl;

        }

        const auto t2 = high_resolution_clock::now();
        cout << duration_cast<nanoSecondes>(t2 - t1).count() << " nanosecondes\n";

    }
    catch (Exception e) {
        /*
         * AFFICHE LES EXEPTIONS AVEC LE NOM DU FICHIER SOURCE ET LA LIGNE DE L'INSTRUCTION QUI A GENERER L'EXEPTION
         * */
        cout << e.getFile() << "@" << e.getFunction() << "() :" << e.getLine() << " " <<e.what();
        return -1;
    }

    return 0;
}

