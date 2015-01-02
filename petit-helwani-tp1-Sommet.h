#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <vector>
#include <list>
#include "petit-helwani-tp1-Exeption.h"
#include "petit-helwani-tp1-Arc.h"
using namespace std;

class Arc;

/**
 * @brief The Sommet class : STRUCTURE DE DONNEES D'UN SOMMET EN MEMOIRE
 */
class Sommet{

public:
    Sommet();
    Sommet(string nomSommet);
    ~Sommet();


    const string &getNom()const{return this->nom;}
    void setNom(string nom){this->nom=nom;}

     const int &getRang()const{return this->rang;}
     void setRang(int rang){this->rang=rang;}

      list <Sommet*> &getListePSommetsPredecesseurDirect(){return ListePSommetsPredecesseurDirect;}
      list <Sommet*> &getListePSommetsSuccesseurDirect(){return ListePSommetsSuccesseurDirect;}
      list <Arc*> &getListePArcs(){return ListePArcs;}

     void ajouterArc(Arc *pArc);
     void suprimerArc(Arc *pArc);
     void ajouterSommetPredecesseurDirect(Sommet *pSommet);
     void suprimerSommetPredecesseurDirect(Sommet *pSommet);
private:

    void ajouterSommetSuccesseurDirect(Sommet *pSommet);
    int rang;
    string nom;

    list <Sommet*> ListePSommetsPredecesseurDirect;
    list <Sommet*> ListePSommetsSuccesseurDirect;
    list <Arc*> ListePArcs;

};

#endif // SOMMET_H
