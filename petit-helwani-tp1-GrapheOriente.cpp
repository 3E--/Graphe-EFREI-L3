#include "petit-helwani-tp1-GrapheOriente.h"


GrapheOriente::GrapheOriente(){

}

GrapheOriente::~GrapheOriente(){

}
/**
 * @brief GrapheOriente::ajouterSommet : PERMET D4AJOUTER UN NOUVEAU SOMMET DANS LE GRAPHE
 * @param nomSommet NOM DU NOUVEAU SOMMET A AJOUTER
 */
void GrapheOriente::ajouterSommet(string nomSommet){

    // VERIFIER SI SOMMET EXISTE DEJA
    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for(Sommet &sommet : listeDesSommets)
        // SI ON TROUVE LE SOMMET AVEC LE NOM QUI CORRESPONDS ON RETOURNE UNE EXEPTION
        if(sommet.getNom()==nomSommet)
            return;//THROW_EXEPTION( " Erreur imposible d'ajouter' le sommet : '"+nomSommet+"', car il est deja present dan le graphe");

    Sommet sommet(nomSommet);

    listeDesSommets.push_back(sommet);
}


/**
 * @brief GrapheOriente::ajouterArc : PERMET D'AJOUTER UN NOUVEAU ARC AU GRAPHE
 * @param nomSommetInitial
 * @param value
 * @param nomSommetTerminal
 */
void GrapheOriente::ajouterArc(string nomSommetInitial,double value, string nomSommetTerminal){

    // VERIFIE SI L'ARC QUE L'ON VEUT AJOUTER BOUCLE SUR LE MEME SOMMET
    if(nomSommetInitial==nomSommetTerminal)
        THROW_EXEPTION("Erreur imposible d'ajouter l'arc, ("+nomSommetInitial+","+toString(value)+","+nomSommetTerminal+"), car il bouble sur l'etat '"+nomSommetTerminal+"'.");

    // VERIFIER SI L'ARC EXISTE DEJA
    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (Arc &arc : listeDesArcs)

        // SI ON TROUVE LE SOMMET AVEC LE NOM QUI CORRESPONDS ON RETOURNE UNE EXEPTION
        if(arc.getSommetExtremiteInitiale()->getNom()==nomSommetInitial && arc.getSommetExtremiteTerminale()->getNom()==nomSommetTerminal)
            THROW_EXEPTION( " Erreur imposible d'ajouter' l'arc' : ("+nomSommetInitial+","+toString(value)+","+nomSommetTerminal+"), car il est deja present dan le graphe.");

    // CREATION D'UN OBJECT ARC
    //Arc arc(&getSommetByName(nomSommetInitial),value,&getSommetByName(nomSommetTerminal));
    // obliger de prendre listeDesArcs.back() sinon l'adresse de l'arc n'est pas la même, c'est une copie
    listeDesArcs.push_back(Arc (&getSommetByName(nomSommetInitial),value,&getSommetByName(nomSommetTerminal)));

    listeDesArcs.back().getSommetExtremiteInitiale()->ajouterArc(&listeDesArcs.back()); // Ajoute automatiquement le sommet successeur direct

    listeDesArcs.back().getSommetExtremiteTerminale()->ajouterSommetPredecesseurDirect(listeDesArcs.back().getSommetExtremiteInitiale());



}

/**
 * @brief GrapheOriente::getSommetByName PERME DE RETOUVER L'OBJET SOMMET QUI APARTIEN AU NOM
 * @param nomSommet : NOM DU SOMMET A TROUVER DANS LE GRAPHE
 * @return UNE REFECRENCE SUR L'OBJECT SOMMET QUI CORRESMONT AU NOM EN ARGMENT
 */
Sommet &GrapheOriente::getSommetByName(string nomSommet){

    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (Sommet &sommet : listeDesSommets)

        // SI ON TROUVE LE SOMMET AVEC LE NOM QUI CORRESPOND ON LE RETOURNE
        if(sommet.getNom()==nomSommet)
            return sommet;

    THROW_EXEPTION("Le sommet avec le nom : '"+nomSommet+"', n'a pas été trouvé dans le vector de sommets du graphe.");

}
/**
 * @brief GrapheOriente::genererLaMatriceAdjacente PERMET DE GENETRER UN VECTOR 2D DE LA MATRICE ADJACENTE DU GRAPHE
 * @return UNE REFERENCE SUR LE VECTOR 2D DE LA MATRICE ADJACENTE DU GRAPHE
 */
vector< vector<string> > GrapheOriente::genererLaMatriceAdjacente() const{

    // LIGNE DE L'ENTETE DE LA MATRICE
    vector<string> ligneHeader;
    ligneHeader.push_back(" ");

    vector< vector<string> > matriceAdjacente;

    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (const Sommet &sommet : listeDesSommets)
        // AJOUTE LE NOM DE CHAQUE SOMMET DU GRAPHE DANS LA PREMIERE LIGGNE DE LA MATRICE
        ligneHeader.push_back(sommet.getNom());



    // AJOUTE LA PREMIERE LIGNE DE LA MATRICE
    matriceAdjacente.push_back(ligneHeader);

    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
    for (const Sommet &sommet : listeDesSommets){

        // ON CREE UNE LIGNE POUR CHAQUE SOMMET
        vector<string> ligneDuSommet;

        // ON AJOUTE LE NOM DU SOMMET DE LA LIGNE A LA PREMIERE COLONE DE LA LIGNE DU SOMMET
        ligneDuSommet.push_back(sommet.getNom());

        // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMET DU GRAPHE
        for (const Sommet &sommet2 : listeDesSommets){
            // SI C'EST UNE BOUCLE ON AFFICHE RIEN DANS LA COLOGNE DE LA LIGNE DU SOMMET
            if(sommet2.getNom() == sommet.getNom())
                ligneDuSommet.push_back(" ");
            else {


                const Arc *pArc = trouverArc(sommet2.getNom(),sommet.getNom());
                // SINON SI IL Y A UN ARC QUI RELIE LE SOMMET DE LA LIGNE AVEC LE SOMMET DE L'ENNTETE ON AFICHE LA VALEUR DE L'ARC
                if (pArc!=NULL)
                    ligneDuSommet.push_back(toString(pArc->getValue()));
                // SINON
                else ligneDuSommet.push_back(" ");
            }

        }
        matriceAdjacente.push_back(ligneDuSommet);

    }
    return matriceAdjacente;
}


void GrapheOriente::afficherLaListeDesArcs(){

}

void GrapheOriente::supprimerUnSommet(string nomSommet){


    if(trouverSommet(nomSommet)==NULL)THROW_EXEPTION("Erreur impossible de suprimer le sommet '"+nomSommet+"', il n'existe pas.");

    // ON CHERCHE LE SOMMETS A PARTIR DE SONT NOM

    // BOUCLE POUR PARCOURIR LE VECTOR DES SOMMETS DU GRAPHE
    for (Sommet &sommet : listeDesSommets) // >>> (!C++11)

        if(sommet.getNom()!=nomSommet){

            //SUPRIMME LE SOMMET EN MEMOIRE DANS LA LISTE DES SOMMETS PREDECESSEURS DE CHAQUE SOMMETS
            for (list<Sommet*>::iterator it = sommet.getListePSommetsPredecesseurDirect().begin(); it != sommet.getListePSommetsPredecesseurDirect().end(); )
                if ((*it)->getNom()==nomSommet)
                    it=sommet.getListePSommetsPredecesseurDirect().erase(it);
                else ++it;


            //SUPRIMME LE SOMMET EN MEMOIRE DANS LA LISTE DES SOMMETS PREDECESSEURS DE CHAQUE SOMMETS
            for (std::list<Sommet*>::iterator it = sommet.getListePSommetsSuccesseurDirect().begin(); it != sommet.getListePSommetsSuccesseurDirect().end(); )
                if ((*it)->getNom()==nomSommet)
                    it=sommet.getListePSommetsPredecesseurDirect().erase(it);
                else ++it;
        }


    //SUPRIMME LES ARCS DU SOMMET EN MEMOIRE
    for (std::list<Arc>::iterator it = listeDesArcs.begin(); it != listeDesArcs.end(); )
        if (it->getSommetExtremiteInitiale()->getNom()==nomSommet)
            it=listeDesArcs.erase(it);
        else ++it;

    //SUPRIMME LE SOMMET EN MEMOIRE
    for (std::list<Sommet>::iterator it = listeDesSommets.begin(); it != listeDesSommets.end(); )
        if (it->getNom()==nomSommet)
            it=listeDesSommets.erase(it);
        else ++it;


}
void GrapheOriente::suprimerUnArc(Arc &arc){


    arc.getSommetExtremiteInitiale()->suprimerArc(&arc); // quand on suprime un arc qui apartien a un sommet, on suprimme automatiquement le sommet dans la liste des sommets predecesseurs direct du sommet a l'extremite terminal de l'arc que l'on supprime

    // SUPPRIME L'ARC DANS LE VECTOR DES ARCS DU GRAPHE COURANT
    listeDesArcs.erase(
                remove_if(listeDesArcs.begin(), listeDesArcs.end(),
                          /*** FONCTION LAMBDA (!C++11) >>> ***/[&arc](const Arc &o)->bool{
        return &o==&arc;
    }),
                listeDesArcs.end());


}

/**
 * @brief trouverArc
 * @param nomSommetInitial
 * @param nomSommetTerminal
 * @return
 */
Arc *GrapheOriente::trouverArc(const string &nomSommetInitial,const string &nomSommetTerminal) const{

    // BOUCLE POUR PARCOURIR LE VECTOR DES ARCS DU GRAPHE
    for(const Arc &arc : listeDesArcs)

        // SI ON TROUVE UN ARC QUI A POUR SOMMET INITIAL OU SOMMET TERMINAL LE SOMMET SUPRIMER ALORS ON SUPRIME AUSSI L'ARC
        if(const_cast<Arc&>(arc).getSommetExtremiteInitiale()->getNom()== nomSommetInitial && const_cast<Arc&>(arc).getSommetExtremiteTerminale()->getNom() == nomSommetTerminal)
            return &const_cast<Arc&>(arc);

    // RETOURNE UN POINTEUR NULL SI ON A PAS TROUVER L'ARC
    return NULL;
}
Sommet * GrapheOriente::trouverSommet(string nomSommet){

    // BOUCLE POUR PARCOURIR LE VECTOR DES ARCS DU GRAPHE
    for(Sommet &sommet: listeDesSommets) // >>> (!C++11)

        // SI ON TROUVE UN ARC QUI A POUR SOMMET INITIAL OU SOMMET TERMINAL LE SOMMET SUPRIMER ALORS ON SUPRIME AUSSI L'ARC
        if(sommet.getNom()==nomSommet)
            return &sommet;

    // RETOURNE UN POINTEUR NULL SI ON A PAS TROUVER L'ARC
    return NULL;
}
GrapheOriente::GrapheOriente(const GrapheOriente &grapheOrienteACopier){

    // BOUCLE POUR COPIER LES SOMMETS
    for(Sommet &sommet : const_cast<GrapheOriente&>(grapheOrienteACopier).getListeDesSommets())
        this->ajouterSommet(sommet.getNom());

    // BOUCLE POUR COPIER LES ARCS
    for(Arc &arc : const_cast<GrapheOriente&>(grapheOrienteACopier).getListeDesArcs())
        this->ajouterArc(arc.getSommetExtremiteInitiale()->getNom(), arc.getValue(), arc.getSommetExtremiteTerminale()->getNom());
}
