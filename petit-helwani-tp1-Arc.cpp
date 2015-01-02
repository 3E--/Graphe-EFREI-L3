#include "petit-helwani-tp1-Arc.h"

Arc::Arc(){

}
/**
 * @brief Arc::Arc : SURCHARGE DU CONSTRUCTEUR POUR CREE UN OBJECT ARC DIRECTEMENT AVEC SES ATRIBUT EN ARGUMNENT DU CONSTRUCTEUR
 * @param pExtremiteInitiale : LE SOMMET INITIAL DE L'ARC
 * @param value : LA VALEURS, OU LE POIDS DE L'ARC
 * @param ExtremiteTerminale : LE SOMMET TERMINAL DE L'ARC
 */
Arc::Arc(Sommet* pSommetExtremiteInitiale, double value, Sommet* pSommetExtremiteTerminale){
    setSommetExtremiteInitiale(pSommetExtremiteInitiale);
    setValue(value);
    setSommetExtremiteTerminale(pSommetExtremiteTerminale);
}

Arc::~Arc()
{

}


