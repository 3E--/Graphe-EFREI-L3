#ifndef DETECTIONDECIRCUIT_H
#define DETECTIONDECIRCUIT_H
#include "petit-helwani-tp1-GrapheOriente.h"
#include "iostream"
#include <stack>
using namespace std;

namespace AlgorithmesGraphe{

/** *****************************************************************************************************
 *  LES ALGORITHMES POUR L'AFFICHAGE DU GRAPHE
 ********************************************************************************************************/
namespace Affichage{
/**
 * @brief toString
 * @param number
 * @return
 */
static inline string toString(const double &number){ostringstream s;s << number;return s.str();}

/**
 * @brief Affichage::matriceAdjacente
 * @param grapheOriente
 */
static inline void matriceAdjacente(const GrapheOriente &grapheOriente){

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
static inline  void listeDesArcs(GrapheOriente &grapheOriente){


    cout << "-----------------------------------------" << endl;
    cout << "-             LISTE DES ARCS            -" << endl;
    cout << "-----------------------------------------" << endl << endl;
    cout << "( extrémité initiale , extrémité terminale , valeur )"<<endl;
    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (Arc &arc : grapheOriente.getListeDesArcs())
        cout<<"("<<arc.getSommetExtremiteInitiale()->getNom()<<","<< arc.getSommetExtremiteTerminale()->getNom() <<","<<toString(arc.getValue())<<")"<<endl;

    cout << "-----------------------------------------" << endl;
 }
 /**
  * @brief Affichage::listeDesSommets
  * @param grapheOriente
  */
static inline void listeDesSommets(GrapheOriente &grapheOriente){

 cout << "---------------------------------------------------" << endl;
 cout << "-               LISTE DES SOMMETS                 -" << endl;
 cout << "---------------------------------------------------" << endl;
 for (Sommet &sommet : grapheOriente.getListeDesSommets())
         cout<<"( NOM:'" <<sommet.getNom()<< "', RANG:" << sommet.getRang() <<  ")" <<endl;
 cout << "---------------------------------------------------" << endl;


 }


}

/** *****************************************************************************************************
 *  LES ALGORITHMES POUR LA DETECTION DE CIRCUIT DANS LE GRAPHE
 ********************************************************************************************************/
namespace DetectionDeCircuit{

/**
 * @brief eliminationSuccessiveDesPointsDEntree : PERMET DE DETECTER SI IL Y AU AU MOINS UN CIRCUIT DANS UN GRAPHE ORIENTE
 * @param grapheOriente : LE GRAPHE ORIENTE A TESTER
 * @return : UNE COPIE DE CE QUI RESTE DU GRAPHE ORIENTE APRES LES OPERATIONS DE SUPRESSION DE SOMMET SI CELUI CI N'A PAS DE PREDECESSEUR
 */
static inline GrapheOriente eliminationSuccessiveDesPointsDEntree(const GrapheOriente &grapheOriente){

    cout<<"----------------------------------------------"<<endl;
    cout<<"-        DETECTION DE CIRCUIT PAR :          -"<<endl;
    cout<<"- ELIMINATION SUCCESSIVE DES POINTS D'ENTREE -"<<endl;
    cout<<"----------------------------------------------"<<endl;

    GrapheOriente copieDuGrapheOriente(grapheOriente);

    // MARQUEUR POUR LE GOTO
DEBUT_BOUCLE_PARCOUR_SOMMETS :

    // BOUCLE POUR PARCOURIR LES SOMMET DE LA COPIE DU GRAPHE ORIENTE

    for(Sommet &sommet : copieDuGrapheOriente.getListeDesSommets())

        // SI LE SOMMET DE L'ITERATION COURRANTE N'A PAS AU MOINS UN PREDECESSEUR
        if(sommet.getListePSommetsPredecesseurDirect().empty()){

            cout << "SUPRESSION DU SOMMET : '"<<sommet.getNom()<<"'"<<endl;

            // ON SUPPRIME DANS LA COPIE DU GRAPHE ORIENTE LE SOMMET DE L'ITERATION COURANTE QUI NA PAS DE PREDECESSEUR
            copieDuGrapheOriente.supprimerUnSommet(sommet.getNom());

            // ON RETOURNE AU DEBUT DE LA BOUCLE QUI PARCOUR TOUTS LES SOMMETS DE LA COPIE DU GRAPHE ORIENTE
            goto DEBUT_BOUCLE_PARCOUR_SOMMETS;
        }

    // SI LA COPIE DU GRAPHE ORIENTE POSSIDE AU MOINS UN SOMMET, CELA VEUT DIRE QUE LE GRAPHE ORIENTE EN ARGUMENT POSSEDE AU MOINS UN CIRCUIT
    if(copieDuGrapheOriente.getListeDesSommets().empty())
        cout << "  >>> RESULTAT : IL N'Y A PAS DE CIRCUIT DANS CE GRAPHE."<<endl;

    // SINON IL N'Y A PAS DE CIRCUIT DANS LE GRAPHE EN ARGUMENT
    else
        cout << "  >>> RESULTAT : IL Y A AU MOINS UN CIRCUIT DANS CE GRAPHE."<<endl;

    return copieDuGrapheOriente;
}
}

/**
 * @brief CalculDeRang::calculerUnRangPourChaqueSommet : PERMET DE CALCULER LE RANG DE TOUS LES SOMMETS D'UN GRAPHE
 * @param grapheOriente : LE GRAPHE ORIENTE OU L'ON DROIS CALCULER LE RANGS DE TOUS LES SOMMETS, ON SUPOSE DEJA QUE CELUI CI N'A PAS DE CIRCUIT
 */
static inline void calculDuRang(GrapheOriente &grapheOriente){

    cout << "---------------------------------------------------" << endl;
    cout << "-   CALCUL DU RANG DE CHAQUE SOMMET DU GRAPHE     -" << endl;
    cout << "---------------------------------------------------" << endl;

    // ON EFFECTUE UNE COPIE DU GRAPHE ORIENTE POUR FAIRE NOS CALCULS
    GrapheOriente copyGrapheOriente=grapheOriente;

    unsigned int rang=0;

    stack<Sommet*> pileDePointeurDeSommetDejaParcouru;

    // MARQUEUR DU DEBUT DE LA BOUCLE QUI PARCOUR TOUTS LES SOMMETS DU GRAPHE ORIENTE POUR LE GOTO
DEBUT_BOUCLE_PARCOURS_DE_TOUS_LES_SOMMETS_DU_GRAPHE_COPIE:

    /** *************************************************************************
     * BOUCLE POUR L'ATRIBUTION DE RANG AU SOMMET QUI N'ONT PAS DE PREDECESSEUR
     * **************************************************************************/
    // BLOUCLE POUR PARCOURIR TOUT LES SOMMES DU GRAPHE ORIENTE

    for( Sommet &sommet : copyGrapheOriente.getListeDesSommets()){

        // TESTE SI LE SOMMET DE L'ITERATION COURANTE NE POSSEDE AUCUN PREDECESSEUR, ALORS LE SOMMET N'EST PAS UNE RACINE
        if(!sommet.getListePSommetsPredecesseurDirect().empty())
            // PASSE A L'ITERATION SUIVANTE DE LA BOUCLE FOR QUI PARCOUR LES SOMMETS, SI LE SOMMET DE L'ITERATION COURANTE NE POSSEDE PAS DE PREDECESSEUR
            continue;

        // TESTE SI ON A DEJA ATRIBUIE UN RANG, AU SOMMET DE L'ITERATION COURANTE
        cout << "LE SOMMET: '" <<  sommet.getNom()<<"' PREND LE RANG : "<< rang<< endl;

        // ATRIBUTION DU RANG AU SOMMET DE L'ITERATION COURANTE
        sommet.setRang(rang);

        pileDePointeurDeSommetDejaParcouru.push(&sommet);

    }

    /** *************************************************************************
     * BOUCLE POUR SUPRIMER LES SOMMETS ( DANS LA COPIE DU GRAPHE ORIENTE ) DONT ONT A DONNE UN RANG DANS LA BOUCLE FOR PRECEDENTE
     * *************************************************************************/
    while(!pileDePointeurDeSommetDejaParcouru.empty()){

        cout << "SUPRESSION DU SOMMET : '" << pileDePointeurDeSommetDejaParcouru.top()->getNom()<< "'"<<endl;

        copyGrapheOriente.supprimerUnSommet(pileDePointeurDeSommetDejaParcouru.top()->getNom());

        pileDePointeurDeSommetDejaParcouru.pop();
    }


    // TESTE SI IL RESTE DES SOMMETS DANS LA COPIE DU GRAPHE ORIENTE
    if(!copyGrapheOriente.getListeDesSommets().empty()){

        // INCREMENTATION DU RANG
        rang++;

        // ON RETOURNE AU DEBUT E LA BOUCLE QUI PARCOUR TOUTS LES SOMMETS DU GRAPHE ORIENTE
        goto DEBUT_BOUCLE_PARCOURS_DE_TOUS_LES_SOMMETS_DU_GRAPHE_COPIE;
    }
}
static inline GrapheOriente FermetureTransitive(GrapheOriente& grapheOriente){

    // COPIE DU GRAPHE ORIENTE
    GrapheOriente copyGrapheOriente(grapheOriente);

    cout << "---------------------------------------------------" << endl;
    cout << "-               FERMETURE TRANSIVE                -" << endl;
    cout << "---------------------------------------------------" << endl;

    // BOUCLE POUR PARCOURIR TOUT LES SOMMETS DU GRAPHE
    for (Sommet & sommetDeLaCopyDuGraphe : copyGrapheOriente.getListeDesSommets() ){

        // CREATION D'UN VECTOR POUR RANGER TOUT LES SOMMET SUCCESSEUR DU SOMMET DU GRAPHE DE L'ITERATION COURANTE
        list<Sommet*> v_pSommetsDejaParcouruDuSommet;

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        /// ON CHERCHE A RANGER DANS LE VECTOR, TOUTS LES SUCCESSSEUR DU SOMMET DE L'ITERATION COURANTE ///
        /// ///////////////////////////////////////////////////////////////////////////////////////////////

        // BOUCLE POUR PARCOURIR ET AJOUTER DANS LE VECTOR DES SOMMET DEJA PARCOURU TOUS LES SOMMET SUCCESSEUR DIRECT DU SOMMET
        for(Sommet *pSommetSuccesseurDirect : sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect())
            v_pSommetsDejaParcouruDuSommet.push_back(pSommetSuccesseurDirect);

        // BOUCLE POUR PARCOURIR ET AJOUTER DANS LE VECTOR DES SOMMETS DEJA PARCOURU TOUS LES SOMMETS SUCCESSEUR DIRECT DU SOMMET DE L'ITERATION COURANTE
        for(Sommet *pSommetDejaParcouru : v_pSommetsDejaParcouruDuSommet)
            for(Sommet *pSommetSuccesseurDuSommetDejaParcouru : pSommetDejaParcouru->getListePSommetsSuccesseurDirect())

                // SI LE SOMMET SUCCESEUR NE BOUCLE PAS SUR LUI MEME
                if(find(v_pSommetsDejaParcouruDuSommet.begin(), v_pSommetsDejaParcouruDuSommet.end(), pSommetSuccesseurDuSommetDejaParcouru ) == v_pSommetsDejaParcouruDuSommet.end())

                    // AJOUTE LE SOMMET DANS LA LISTE DES SOMMETS DEJA PARCOURU
                    v_pSommetsDejaParcouruDuSommet.push_back( pSommetSuccesseurDuSommetDejaParcouru );



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ON CHERCHE A AJOUTER UN NOUVELLE ARC QUI RELIE LE SOMMETS DE L'ITERATION COURANTE AVEC TOUT SES SUCESSEUR, SI IL N'Y EN A PAS DEJA AU MOINS UN ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        while(!v_pSommetsDejaParcouruDuSommet.empty()){

            // SI LA TETE N'EST PAS DEJA SUCCESEUR DU SOMMET ON AJOUTE DES ARC
            if(find(sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().begin(), sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().end(), v_pSommetsDejaParcouruDuSommet.front()) == sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().end()){

                /// [!!!] BOUCLE SUR LUI MEME
                 ///if(sommetDeLaCopyDuGraphe.getNom() != v_pSommetsDejaParcouruDuSommet.front()->getNom() )

                cout<< " > AJOUT D'UN ARC : " << sommetDeLaCopyDuGraphe.getNom() <<" -- "<< 0 <<" -> "<< v_pSommetsDejaParcouruDuSommet.front()->getNom()<< endl;

                // CREATION D'UN ARC QUI RELIE LE SOMMET AVEC LES AUTRES SOMMET DU VECTEUR DES SOMMET SUCCESEUR
                copyGrapheOriente.ajouterArc( sommetDeLaCopyDuGraphe.getNom(), 0, v_pSommetsDejaParcouruDuSommet.front()->getNom() );
            }

            // pop front
            v_pSommetsDejaParcouruDuSommet.erase(v_pSommetsDejaParcouruDuSommet.begin());
        }
    }
    cout << "---------------------------------------------------" << endl;
    return copyGrapheOriente;

}
}
#endif // DETECTIONDECIRCUIT_H
