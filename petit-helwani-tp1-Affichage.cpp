#include "petit-helwani-tp1-Affichage.h"

Affichage::Affichage()
{

}

Affichage::~Affichage()
{

}
/**
 * @brief Affichage::matriceAdjacente
 * @param grapheOriente
 */
void Affichage::matriceAdjacente(GrapheOriente &grapheOriente){

    vector< vector<string> > Vector2D=grapheOriente.genererLaMatriceAdjacente();
    string b="     ";

    cout << "---------------------------------------------------" << endl;
    cout << "-               MATRICE ADJACENTE                 -" << endl;
    cout << "---------------------------------------------------" << endl;
    for (unsigned int x = 0; x < Vector2D.size(); x++) {
        for (unsigned int y = 0; y < Vector2D.at(x).size(); y++)
            cout<< Vector2D.at(x).at(y)<<b.substr(0,b.size()-Vector2D.at(x).at(y).size()+1)<<"|";
        cout<<endl<< "---------------------------------------------------" <<endl;
    }
    cout << "---------------------------------------------------" << endl;

}
/**
  * @brief Affichage::listeDesArcs
  * @param grapheOriente
  */
 void Affichage::listeDesArcs(GrapheOriente &grapheOriente){



    cout << "-----------------------------------------" << endl;
    cout << "-             LISTE DES ARCS            -" << endl;
    cout << "-----------------------------------------" << endl;
    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (Arc &arc : grapheOriente.getListeDesArcs())
        cout<<"("<<arc.getSommetExtremiteInitiale()->getNom()<<","<< arc.getSommetExtremiteTerminale()->getNom() <<","<<toString(arc.getValue())<<")"<<endl;
    //( extrémité initiale , extrémité terminale , valeur )
    cout << "-----------------------------------------" << endl;
 }
 /**
  * @brief Affichage::listeDesSommets
  * @param grapheOriente
  */
 void Affichage::listeDesSommets(GrapheOriente &grapheOriente){

 cout << "---------------------------------------------------" << endl;
 cout << "-               LISTE DES SOMMETS                 -" << endl;
 cout << "---------------------------------------------------" << endl;
 for (Sommet &sommet : grapheOriente.getListeDesSommets())
         cout<<"( NOM:'" <<sommet.getNom()<< "', RANG:" << sommet.getRang() <<  ")" <<endl;
 cout << "---------------------------------------------------" << endl;


 }
