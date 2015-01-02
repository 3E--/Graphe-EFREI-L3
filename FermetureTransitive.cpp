#include "FermetureTransitive.h"

FermetureTransitive::FermetureTransitive(){
}

FermetureTransitive::~FermetureTransitive(){
}
/**
 * @brief FermetureTransitive::operator ()
 * @param grapheOriente
 * @return
 */
GrapheOriente &FermetureTransitive::faire(GrapheOriente& grapheOriente){

    // COPIE DU GRAPHE ORIENTE
    GrapheOriente &copyGrapheOriente=grapheOriente;

    // BOUCLE POUR PARCOURIR TOUT LES SOMMETS DU GRAPHE
    for (Sommet & sommetDeLaCopyDuGraphe : copyGrapheOriente.getListeDesSommets() ){

        // CREATION D'UN VECTOR POUR RANGER TOUT LES SOMMET SUCCESSEUR DU SOMMET DU GRAPHE DE L'ITERATION COURANTE
        vector<Sommet*> v_pSommetsDejaParcouruDuSommet;

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
            if(find(sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().begin(), sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().end(), v_pSommetsDejaParcouruDuSommet.front()) == sommetDeLaCopyDuGraphe.getListePSommetsSuccesseurDirect().end())

                // CREATION D'UN ARC QUI RELIE LE SOMMET AVEC LES AUTRES SOMMET DU VECTEUR DES SOMMET SUCCESEUR
                copyGrapheOriente.ajouterArc( sommetDeLaCopyDuGraphe.getNom(), 0, v_pSommetsDejaParcouruDuSommet.front()->getNom() );

            // pop front
            v_pSommetsDejaParcouruDuSommet.erase(v_pSommetsDejaParcouruDuSommet.begin());
        }
    }

    return copyGrapheOriente;

}
