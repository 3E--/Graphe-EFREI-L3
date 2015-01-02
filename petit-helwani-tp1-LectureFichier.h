#ifndef GRAPHEFILEREADER_H
#define GRAPHEFILEREADER_H
#include "petit-helwani-tp1-GrapheOriente.h"
#include "petit-helwani-tp1-Exeption.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

/**
  *
  */
namespace  LireFichier {
/**
      * @brief graphe : LECTURE DU FICHIER GRAPHE PASSE EN ARGUMENT
      * @param path : LE CHEMIN DU FICHIER GRAPHE A PARSER
      *
      *               EXEMPLE -------------------
      *               SOMMETS:[
      *                          1,
      *                          2       // (!) atention : il n'y a pas de virgule apres la declaration du nom du dernier sommet
      *               ]
      *               ARCS:{
      *                      [1, 10, 2],
      *                      [2, 44, 1]  // (!) atention : il n'y a pas de virgule apres la declaration du dernier arc
      *               }
      *               ---------------------------
      *
      * @return UN GRAPHEORIENTE A L'IMAGE DU FICHIER GRAPHE EN ARGUMENT
      * @exception ERREUR DANS LE FICHIER GRAPHE EN ARGUMENT
      */
static  inline GrapheOriente  graphe(string &path){
    
    ifstream graphFile(path.c_str(), ios::binary );
    
    // TEST SI LE FICHIER DU GRAPH EST CORRECTEMENT OUVERT
    if(!graphFile.is_open()) THROW_EXEPTION( "Erreur imposible d'ouvrir le fichier '" + path+"', verifier si il n'est pas deja utilisee dans un autre programme.");
    
    string graphText((std::istreambuf_iterator<char>(graphFile)),std::istreambuf_iterator<char>());
    
    // RETIRE TOUS LES ESPACES, LES RETOURS CHAIRIOT, AINSI QUE LES TABULATIONS
    char chars[]=" \r\n\t";
    for(char oneChar : chars)
        graphText.erase (std::remove(graphText.begin(), graphText.end(), oneChar), graphText.end());
    
    // CHERCHE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
    //                                  ^^^^^^^^^
    size_t posBeginSommet=graphText.find("SOMMETS:[");
    if(posBeginSommet==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);
    
    // CHERCHE LA POSITION DU MARQEUR "SOMMETS:[ 1,2 ]", A PARTIR DE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
    //                                               ^                                        ^^^^^^^^^
    size_t posEndSommet=graphText.find(']',posBeginSommet);
    if(posEndSommet==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);
    
    //; EXTRAIT LES SOMMETS  :"[ 1,2 ]"
    //                          ^^^
    string sommetsText(graphText.substr(posBeginSommet+9,posEndSommet-(posBeginSommet+9)));
    
    // SUPRIME "SOMMETS:[ 1,2 ]ARCS:{[1, 10, 2],[2, 44, 1]} A PARTIR DU MARQUEUR SOMMETS:[ 1,2 ] JUSQU'AU MARQUEUR SOMMETS:[ 1,2 ]
    //          ^^^^^^^^^^^^^^^                                                  ^^^^^^^^^                                       ^
    graphText.erase(posBeginSommet,posEndSommet-posBeginSommet+1);
    
    GrapheOriente graphe;
    
    size_t posSplitVirguleSommets = 0;
    
    // BOUCLE PARCOUR SPLITER LES SOMMET A PARTIR DU MARQUEUR "1,2"
    //                                                          ^
    while (( posSplitVirguleSommets = sommetsText.find(",")) != std::string::npos) {
        graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));
        sommetsText.erase(0, posSplitVirguleSommets + 1); // +1 : longeur du delimiteur
    }
    // AJOUTE LE DERNIER SOMMET
    graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));
    
    // CHERCHE LE MARQUEUR "ARCS:["
    size_t posBeginArcs=graphText.find("ARCS:{");
    if(posBeginArcs==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur 'ARC:[' n'a pas ete trouve dans le fichier : "+path);
    
    // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "ARC:["
    size_t posEndArcs=graphText.find('}',posBeginArcs);
    if(posEndArcs==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'ARC:[' n'a pas ete trouve dans le fichier : "+path);
    
    // EXTRAIT LES ARCS
    string arcsText(graphText.substr(posBeginArcs+6,posEndArcs-(posBeginArcs+5)));
    
    // PARCOUR LES ARCS
    size_t posSplitArcs = 0;
    while (( posSplitArcs = arcsText.find("],[")) != std::string::npos) {
        
        // CHERCHE LE MARQUEUR "["
        size_t posBeginArc=arcsText.find("[");
        if(posBeginArc==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur '[', debut d'un arc, n'a pas ete trouve dans le fichier : "+path);
        
        // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "SOMMETS:["
        size_t posEndArc=arcsText.find(']',posBeginArc);
        if(posEndArc==(size_t)-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin d'un n'a pas ete trouve dans le fichier : "+path);
        
        // EXTRAIT UN ARC
        string arcText(arcsText.substr(posBeginArc+1,posEndArc-(posBeginArc+1)));
        
        size_t posSplitArc = 0;
        vector<string> vStringArc;
        while (( posSplitArc = arcText.find(",")) != std::string::npos) {
            vStringArc.push_back(arcText.substr(0,posSplitArc));
            arcText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
        }
        
        // AJOUTE LE SOMMET TERMINAL D'UN ARC
        vStringArc.push_back(arcText);
        
        // VERIFIE SI LA DECLARARION DE L'ARC A BIEN 3 ELEMENTS
        if(vStringArc.size()!=3)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne cntien pas 3 elements dans sa declarartion.");
        
        graphe.ajouterArc(vStringArc[0],atof(vStringArc[1].c_str()),vStringArc[2]);
        
        arcsText.erase(0, posSplitArcs + 2); // +3 : longeur du delimiteur pour chaque arc
    }
    
    // SUPRIME "]}"
    arcsText.erase(arcsText.end()-2,arcsText.end());
    arcsText.erase(arcsText.begin(),arcsText.begin()+1);
    // AJOUTE LE DERNIER ARC
    size_t posSplitArc = 0;
    vector<string> vStringArc;
    while (( posSplitArc = arcsText.find(",")) != std::string::npos) {
        vStringArc.push_back(arcsText.substr(0,posSplitArc));
        arcsText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
    }
    
    // AJOUTE LE SOMMET TERMINAL DU DERNIER ARC
    vStringArc.push_back(arcsText);
    
    // VERIFIE SI LA DECLARARIONT DU DERNIER ARC A BIEN 3 ELEMENTS
    if(vStringArc.size()!=3)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne contien pas 3 elements dans sa declarartion, verifier la syntaxe au niveau de ',,' ou [,,] .");
    
    graphe.ajouterArc(vStringArc[0],atof(vStringArc[1].c_str()),vStringArc[2]);
    
    graphFile.close();
    
    return graphe;
}
/**
 * @brief contrainte
 * @param path
 *
    *
    *               DEBUT EXEMPLE -------------------
    *
    *               SOMMETS:[
    *                          1,
    *                          2,
    *                          3,
    *                          4       // (!) atention : il n'y a pas de virgule apres la declaration du nom du dernier sommet
    *               ]
    *               ARCS_DE_CONTRAINTE:{
    *                      [1, 10, 2],
    *                      [2, 20, 3],
    *                      [3, 20],
    *                      [4, 40, 1, 2, 3]
    *               }
    *
    *               FIN EXAMPLE ----------------------
    *
    *  !!! NOTE : la fonction vas automatiquement ajouter les sommet « début des travaux » et sommet « fin des travaux » qui sont restpectivement 0 et 5 dans l'example ci dessus
    *
 *
 * @return
 */
static inline GrapheOriente contrainte(string &path){
    
     ifstream graphFile(path.c_str(), ios::binary );
      
            // TEST SI LE FICHIER DU GRAPH EST CORRECTEMENT OUVERT
            if(!graphFile.is_open()) THROW_EXEPTION( "Erreur imposible d'ouvrir le fichier '" + path+"', verifier si il n'est pas deja utilisee dans un autre programme.");
            
            string graphText((std::istreambuf_iterator<char>(graphFile)),std::istreambuf_iterator<char>());
            
            // RETIRE TOUS LES ESPACES, LES RETOURS CHAIRIOT, AINSI QUE LES TABULATIONS
            char chars[]=" \r\n\t";
            for(char oneChar : chars)
                graphText.erase (std::remove(graphText.begin(), graphText.end(), oneChar), graphText.end());

            /// //////////////////////////////////////////////////////////
            /// TRAITEMENTS DE LA LISTE DES SOMMET DU FICHIER CONTRAINTE
            /// //////////////////////////////////////////////////////////
            // CHERCHE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
            //                                  ^^^^^^^^^
            size_t posBeginSommet=graphText.find("SOMMETS:[");
            if(posBeginSommet==-1)THROW_EXEPTION( "Erreur le marqueur 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);
            
            // CHERCHE LA POSITION DU MARQEUR "SOMMETS:[ 1,2 ]", A PARTIR DE LA POSITION DU MARQUEUR "SOMMETS:[ 1,2 ]"
            //                                               ^                                        ^^^^^^^^^
            size_t posEndSommet=graphText.find(']',posBeginSommet);
            if(posEndSommet==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'SOMMETS:[' n'a pas ete trouve dans le fichier : "+path);
            
            // EXTRAIT LES SOMMETS  :"[ 1,2 ]"
            //                          ^^^
            string sommetsText(graphText.substr(posBeginSommet+9,posEndSommet-(posBeginSommet+9)));
            
            // SUPRIME "SOMMETS:[ 1,2 ]ARCS:{[1, 10, 2],[2, 44, 1]} A PARTIR DU MARQUEUR SOMMETS:[ 1,2 ] JUSQU'AU MARQUEUR SOMMETS:[ 1,2 ]
            //          ^^^^^^^^^^^^^^^                                                  ^^^^^^^^^                                       ^
            graphText.erase(posBeginSommet,posEndSommet-posBeginSommet+1);
            
            GrapheOriente graphe;

            ///////////////////////////////////////////////
            /// SOMMET « début des travaux »
            ///////////////////////////////////////////////

            /// AJOUTE LE SOMMET 0 : sommet « début des travaux »
            graphe.ajouterSommet("0");
            size_t posSplitVirguleSommets = 0;
            
            // BOUCLE PARCOUR SPLITER LES SOMMET A PARTIR DU MARQUEUR "1,2"
            //                                                          ^
            while (( posSplitVirguleSommets = sommetsText.find(",")) != std::string::npos) {

                // AJOUTE LES SOMMET DE LA LISTE DES SOMMET SAUF LE DERNIER SOMMET (celui qui n'a pas de virgule sa declaration dans le fichier texte)
                graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));

                sommetsText.erase(0, posSplitVirguleSommets + 1); // +1 : longeur du delimiteur
            }

            // AJOUTE LE DERNIER SOMMET DE LA LISTE DES SOMMETS
             graphe.ajouterSommet(sommetsText.substr(0, posSplitVirguleSommets));

             /////////////////////////////////////////////////
             /// TRAITEMENT DES ARCS DU FICHIER DE CONTRAINTE
             /// /////////////////////////////////////////////
             /*
              * graphText:

                   ARCS_DE_CONTRAINTE:{
                          [1, 10, <2>],
                          [2, 20, <3>],
                          [3, 20],
                          [4, 40, <1,2,3>]
                   }
              */
             // CHERCHE LE MARQUEUR "ARCS_DE_CONTRAINTE:["
             size_t posBeginArcs=graphText.find("ARCS_DE_CONTRAINTE:{");
             if(posBeginArcs==-1)THROW_EXEPTION( "Erreur le marqueur 'ARCS_DE_CONTRAINTE:[' n'a pas ete trouve dans le fichier : "+path);
             
             // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "ARCS_DE_CONTRAINTE:["
             size_t posEndArcs=graphText.find('}',posBeginArcs);
             if(posEndArcs==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin de 'ARCS_DE_CONTRAINTE:[' n'a pas ete trouve dans le fichier : "+path);
             
             // EXTRAIT LES ARCS
             string arcsText(graphText.substr(posBeginArcs+6,posEndArcs-(posBeginArcs+5)));
             /*
              * arcsText :

                          [1, 10, 2],
                          [2, 20, 3],
                          [3, 20],
                          [4, 40, <1,2,3>]
              */

             map <string,double>dureeDExecutiondesSommets ;

            // PARCOUR LES ARCS
            size_t posSplitArcs = 0;
            while (( posSplitArcs = arcsText.find("],[")) != std::string::npos) {
            
                // CHERCHE LE MARQUEUR "["
                size_t posBeginArc=arcsText.find("[");
                if(posBeginArc==-1)THROW_EXEPTION( "Erreur le marqueur '[', debut d'un arc, n'a pas ete trouve dans le fichier : "+path);
                
                // CHERCHE LE MARQUEUR "]", LA FIN DU MARQUEUR "ARCS_DE_CONTRAINTE:["
                size_t posEndArc=arcsText.find(']',posBeginArc);
                if(posEndArc==-1)THROW_EXEPTION( "Erreur le marqueur ']' de fin d'un n'a pas ete trouve dans le fichier : "+path);
                
                // EXTRAIT UN ARC
                string arcText(arcsText.substr(posBeginArc+1,posEndArc-(posBeginArc+1)));
                /*
                 * arcText : 1, 10, 2
                 * arcText : 2, 20, 3
                 * arcText : 3, 20
                 * arcText : 4, 40, 1,2,3
                 */
                size_t posSplitArc = 0;
                vector<string> vStringArc;
                while (( posSplitArc = arcText.find(",")) != std::string::npos) {
                    vStringArc.push_back(arcText.substr(0,posSplitArc));
                    arcText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
                }
                
                // AJOUTE L'ARC TERMINAL D'UN ARC
                vStringArc.push_back(arcText);
                
                // VERIFIE SI LA DECLARARION DE L'ARC A BIEN plus de 2 element ELEMENTS
                if(vStringArc.size()>=2)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne contien pas au moins 2 elements dans sa declarartion.");
                
                // arcText : 4, 40, 1,2,3
                //           ^  ^^
                cout<<endl<<"FICHIER DE CONTRAINTRE : La tâche "+vStringArc[0]+" a pour durée d’exécution ‘"+vStringArc[1]+"’.";

                dureeDExecutiondesSommets[vStringArc[0]]=atof(vStringArc[1].c_str());

                if(vStringArc.size()==2){
                    cout<<" Aucune contrainte, elle sera relié au sommet 0.";

                    /// AJOUTE UN ARC ENTRE LE SOMMET  0  : sommet « début des travaux » ET LE SOMMET QUI N'A PAS DE CONTRAINTE
                    graphe.ajouterArc(toString(atoi(graphe.getListeDesSommets().front().getNom().c_str())-1),0,vStringArc[0]);

                }
                else{
                    cout<<" Elle ne peut s’exécuter que lorsque la tâche ";
                    // BOUCLE POUR PARCOURIR LES SOMMETS  arcText : 4, 40, 1,2,3
                    //                                                     ^^^^^
                    for(unsigned int i=3;i<vStringArc.size();i++){
                        if(i=3) cout<<vStringArc[i];
                        else if(i>3 && i<vStringArc.size()-1) cout<<", "+vStringArc[i];
                        else cout<<" et "+vStringArc[i];

                        // AJOUT DE L'ARC :
                        // 1 -40-> 4, 1 -40-> 4, 1 -40-> 4,
                        graphe.ajouterArc(vStringArc[i],0,vStringArc[0]);
                    }

                    cout<<" est terminée.";
                }

                
                graphe.ajouterArc(vStringArc[0],atof(vStringArc[1].c_str()),vStringArc[2]);
                
                arcsText.erase(0, posSplitArcs + 2); // +3 : longeur du delimiteur pour chaque arc
            }
            
            // SUPRIME "]}"
            arcsText.erase(arcsText.end()-2,arcsText.end());
            arcsText.erase(arcsText.begin(),arcsText.begin()+1);

            /** ***************************
            // AJOUTE LE DERNIER ARC
            *******************************/
            size_t posSplitArc = 0;
            vector<string> vStringArc;
            while (( posSplitArc = arcsText.find(",")) != std::string::npos) {
                vStringArc.push_back(arcsText.substr(0,posSplitArc));
                arcsText.erase(0, posSplitArc + 1); // +1 : longeur du delimiteur pour chaque element d'un arc
            }
            
            // AJOUTE L'ARC TERMINAL D'UN ARC
            vStringArc.push_back(arcsText);

            // VERIFIE SI LA DECLARARION DE L'ARC A BIEN plus de 2 element ELEMENTS
            if(vStringArc.size()>=2)THROW_EXEPTION( "Erreur l'arc '"+arcsText+"' ne contien pas au moins 2 elements dans sa declarartion.");

            // arcText : 4, 40, 1,2,3
            //           ^  ^^
            cout<<endl<<"FICHIER DE CONTRAINTRE : La tâche "+vStringArc[0]+" a pour durée d’exécution ‘"+vStringArc[1]+"’.";

            dureeDExecutiondesSommets[vStringArc[0]]=atof(vStringArc[1].c_str());

            if(vStringArc.size()==2){
                cout<<" Aucune contrainte, elle sera relié au sommet 0.";

                /// AJOUTE UN ARC ENTRE LE SOMMET  0  : sommet « début des travaux » ET LE SOMMET QUI N'A PAS DE CONTRAINTE
                graphe.ajouterArc(toString(atoi(graphe.getListeDesSommets().front().getNom().c_str())-1),0,vStringArc[0]);
            }
            else{
                cout<<" Elle ne peut s’exécuter que lorsque la tâche ";
                // BOUCLE POUR PARCOURIR LES SOMMETS  arcText : 4, 40, 1,2,3
                //                                                     ^^^^^
                for(unsigned int i=3;i<vStringArc.size();i++){
                    if(i=3) cout<<vStringArc[i];
                    else if(i>3 && i<vStringArc.size()-1) cout<<", "+vStringArc[i];
                    else cout<<" et "+vStringArc[i];

                    // AJOUT DE L'ARC :
                    // 1 -40-> 4, 1 -40-> 4, 1 -40-> 4,
                    graphe.ajouterArc(vStringArc[i],0,vStringArc[0]);
                }

                cout<<" est terminée.";
            }

            ///////////////////////////////////////////////
            /// SOMMET « fin des travaux »
            ///////////////////////////////////////////////

            /// AJOUTE LE DERNIER SOMMET:  « fin des travaux », son nom c'est : (le numero de la derniére tache) + 1
            graphe.ajouterSommet(toString(atoi(graphe.getListeDesSommets().back().getNom().c_str())+1));

            /// AJOUT DE L'ARC QUI RELIE LA DERNIERE TACHE AVEC LE SOMMET « fin des travaux »
            graphe.ajouterArc(graphe.getListeDesSommets().back().getNom(), 0, toString(atoi(graphe.getListeDesSommets().back().getNom().c_str())+1));

            ///////////////////////////////////////////////
            /// AJOUTE LES CONTRAINTES DE TEMPS DES ARC
            ///////////////////////////////////////////////
            for (pair<string,double>  keyAndValueMap : dureeDExecutiondesSommets)
                graphe.modifierLaValeurDUnArcParRapportASontSommetInitiale(keyAndValueMap.first, keyAndValueMap.second);

            return graphe;
    
}
/**
 * @brief toString
 * @param number
 * @return
 */
static inline string toString(const double &number){ostringstream s;s << number;return s.str();}
}

#endif // GRAPHEFILEREADER_H
