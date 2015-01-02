#include "petit-helwani-tp1-Sommet.h"

Sommet::Sommet(){

}
/**
 * @brief Sommet::Sommet : SURCHARGE DU CONSTRUCTEUR POUR CREE UN OBJECT SOMMET DIRECTEMENT AVE SES ATRIBUT EN ARGUMNENT DU CONSTRUCTEUR
 * @param nomSommet : LE NOM DU SOMMET
 */
 Sommet::Sommet(string nomSommet){
    setNom(nomSommet);
    setRang(-1);
}

/**
 * @brief Sommet::~Sommet
 */
Sommet::~Sommet(){

}

 void Sommet::ajouterArc(Arc *pArc){
    if(pArc->getSommetExtremiteInitiale()!=this)THROW_EXEPTION("Le sommet initiale '"+pArc->getSommetExtremiteInitiale()->getNom()+"'' de l'arc a ajouter n'est pas le même que le sommet "+this->getNom()+", que vous voulez ajouter.");

    ajouterSommetSuccesseurDirect(pArc->getSommetExtremiteTerminale());
    ListePArcs.push_back(pArc);
}

 void Sommet::suprimerArc(Arc *pArc){
    if(pArc->getSommetExtremiteInitiale()!=this)THROW_EXEPTION("Le sommet initiale '"+pArc->getSommetExtremiteInitiale()->getNom()+"'' de l'arc a supprimer n'est pas le même que le sommet "+this->getNom()+", que vous voulez ajouter.");


    // SUPPRIME L'ARC DANS LE VECTOR DES ARCS DU SOMMET COURRANT
    ListePSommetsSuccesseurDirect.erase(
                remove_if(ListePSommetsSuccesseurDirect.begin(), ListePSommetsSuccesseurDirect.end(),

                               /*** FONCTION LAMBDA (!C++11) >>> ***/[&pArc](const Sommet * o)->bool{
        if(o==pArc->getSommetExtremiteTerminale()){
            // ON DIT AU SUCCESSEUR DIRECT DE SUPPRIMER LE SOMMET COURRANT ENTANT QUE PREDECESSEUR DIRECT, PUISQUE L'ON SUPRIMME L'ARC QUI LES RELIENT
            pArc->getSommetExtremiteTerminale()->suprimerSommetPredecesseurDirect(pArc->getSommetExtremiteInitiale());
            return true;// Pour supprimer entent que successeur direct du sommet courant, le sommet qui se trouve a l'extremité terminal de l'arc? puisque l'on supprime l'arc qui les relient
        }
    }),
                ListePSommetsSuccesseurDirect.end());

    // SUPPRIME L'ARC DANS LE VECTOR DES ARCS DU SOMMET COURRANT
    ListePArcs.erase(
                remove_if(ListePArcs.begin(), ListePArcs.end(),
                               /*** FONCTION LAMBDA (!C++11) >>> ***/[&pArc](const Arc * o)->bool{ return o==pArc; }
    ),
                ListePArcs.end());


}

 void Sommet::ajouterSommetPredecesseurDirect(Sommet *pSommet){

    if(pSommet==NULL)THROW_EXEPTION("Erreur imposible d'ajouter un sommet predecesseur direct au sommet '"+this->getNom()+"' car le pointeur en argument est null.");

    ListePSommetsPredecesseurDirect.push_back(pSommet);

}

 void Sommet::suprimerSommetPredecesseurDirect(Sommet *pSommet){

    if(pSommet==NULL)THROW_EXEPTION("Erreur imposible de supprimer un sommet predecesseur direct au sommet '"+this->getNom()+"' car le pointeur en argument est null.");
    if(pSommet==this)THROW_EXEPTION("Erreur imposible de supprimer un sommet predecesseur direct au sommet '"+this->getNom()+"' car le pointeur en argument est le meme.");

    ListePSommetsPredecesseurDirect.erase(
                remove_if(ListePSommetsPredecesseurDirect.begin(), ListePSommetsPredecesseurDirect.end(),
                               /*** FONCTION LAMBDA (!C++11) >>> ***/[&pSommet](const Sommet * o)->bool{ return o==pSommet;}),
                ListePSommetsPredecesseurDirect.end());



}

 void Sommet::ajouterSommetSuccesseurDirect(Sommet *pSommet){

    if(pSommet==NULL)THROW_EXEPTION("Erreur imposible d'ajouter un sommet successeur direct au sommet '"+this->getNom()+"' car le pointeur en argument est null.");

    ListePSommetsSuccesseurDirect.push_back(pSommet);

}
