#ifndef EDITORUSABLES_H
#define EDITORUSABLES_H

#include <string>

class editorUsables
{
private:

    int municiones;
public:
    editorUsables(int municiones);
    ~editorUsables(){}

    //Retorna la municion del Usable
    int getAmmo();
};

#endif 
