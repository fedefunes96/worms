#ifndef COMMONPARSER_H
#define COMMONPARSER_H

#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <commonarchivo.h>
#include "mapeditor.h"
#include <vector>

class Parser
{
public:
    Parser();
    ~Parser(){}

    //Guarda la configuracion del mapa en el cual se esta trabajando
    static void save(std::string &nombre,std::map<int,editorUsables> &usables,
                        std::map<int, editorWorm> &worms,
                        std::map<int, editorViga> &vigas,unsigned int cant,
                        std::string &backgrund);

    //Carga la configuracion del mapa en el Editor
    static void load(MapEditor *editor, std::string& file);

private:

};

#endif
