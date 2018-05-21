#ifndef COMMONPARSER_H
#define COMMONPARSER_H

#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <commonarchivo.h>
#include "editorpantalla.h"

class commonParser
{
public:
    commonParser();

    void save(std::string &nombre,std::map<int,editorUsables> &usables,
                        std::map<int, editorWorm> &worms,
                        std::map<int, editorViga> &vigas );

    void load(EditorPantalla *editor, std::string& file);

private:
    void saveWorm(commonArchivo &archivo, editorWorm &worm);
    void saveViga(commonArchivo &archivo, editorViga& viga);
    void saveUsable(commonArchivo &archivo, editorUsables &usable, int id);
};


#endif
