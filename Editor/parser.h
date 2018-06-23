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

    static void saveConfig();

    static void save(std::string &nombre,std::map<int,editorUsables> &usables,
                        std::map<int, editorWorm> &worms,
                        std::map<int, editorViga> &vigas,unsigned int cant,std::string &backgrund);

    static void load(MapEditor *editor, std::string& file);

private:

};

#endif
