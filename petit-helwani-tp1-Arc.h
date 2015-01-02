#ifndef ARC_H
#define ARC_H

#include "petit-helwani-tp1-Sommet.h"
class Sommet;
/**
 * @brief The Arc class STRUCTURE DE DONNEES D'UN ARC EN MEMOIRE
 */
class Arc{

public:

    Arc();
    Arc(Sommet* pSommetExtremiteInitiale, double value, Sommet* pSommetExtremiteTerminale);
    ~Arc();

    inline Sommet *getSommetExtremiteInitiale()const{ return this->pSommetExtremiteInitiale;  }
    void setSommetExtremiteInitiale(Sommet* pSommetExtremiteInitiale){ this->pSommetExtremiteInitiale = pSommetExtremiteInitiale; }

    Sommet *getSommetExtremiteTerminale(){ return this->pSommetExtremiteTerminale; }
    void setSommetExtremiteTerminale(Sommet* pSommetExtremiteTerminale){ this->pSommetExtremiteTerminale = pSommetExtremiteTerminale; }

    const double &getValue()const{ return this->value; }
    void setValue(int value){ this->value = value; }
    /**
     * @brief pExtremiteInitiale ATTENTION ! : POINTEUR NON LIBERE DANS LE DESTRUCTEUR DE LA CLASS ARC
     */
    Sommet *pSommetExtremiteInitiale ;
    /**
     * @brief ExtremiteTerminale ATTENTION ! : POINTEUR NON LIBERE DANS LE DESTRUCTEUR DE LA CLASS ARC
     */
    Sommet *pSommetExtremiteTerminale ;



private:

    double value ;
};

#endif // ARC_H
