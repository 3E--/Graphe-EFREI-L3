#include "petit-helwani-tp1-CalculDeRang.h"

/**
 * @brief CalculDeRang::CalculDeRang : CONSTRUCTEUR DE LA CLASSE
 */
CalculDeRang::CalculDeRang(){
}

/**
 * @brief CalculDeRang::~CalculDeRang : DESTRUCTEUR DE LA CLASSE
 */
CalculDeRang::~CalculDeRang(){
}

/**
 * @brief CalculDeRang::calculerUnRangPourChaqueSommet : PERMET DE CALCULER LE RANG DE TOUS LES SOMMETS D'UN GRAPHE
 * @param grapheOriente : LE GRAPHE ORIENTE OU L'ON DROIS CALCULER LE RANGS DE TOUS LES SOMMETS, ON SUPOSE DEJA QUE CELUI CI N'A PAS DE CIRCUIT
 */
void CalculDeRang::calculerUnRangPourChaqueSommet(GrapheOriente &grapheOriente){

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


