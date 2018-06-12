#ifndef COMMONPARSER_H
#define COMMONPARSER_H

#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <commonarchivo.h>
#include "editorpantalla.h"
#include <vector>

class commonParser
{
public:
    commonParser();
    ~commonParser(){}

    static void saveConfig();

    static void save(std::string &nombre,std::map<int,editorUsables> &usables,
                        std::map<int, editorWorm> &worms,
                        std::map<int, editorViga> &vigas,unsigned int cant,std::string &backgrund);

    static void load(EditorPantalla *editor, std::string& file);

private:

};

#endif
