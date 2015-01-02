#ifndef LECTUREDEFICHIERDECONTRAINTE_H
#define LECTUREDEFICHIERDECONTRAINTE_H
#include "petit-helwani-tp1-GrapheOriente.h"
#include "petit-helwani-tp1-Exeption.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LectureDeFichierDeContrainte
{
public:
    LectureDeFichierDeContrainte();
    ~LectureDeFichierDeContrainte();
    static inline GrapheOriente readFile(string path);
private:
    static inline void stripString(string &str, char chars[]);
};

#endif // LECTUREDEFICHIERDECONTRAINTE_H
