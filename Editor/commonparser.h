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

    static void saveConfig();

    static void save(std::string &nombre,std::map<int,editorUsables> &usables,
                        std::map<int, editorWorm> &worms,
                        std::map<int, editorViga> &vigas, int cant );

    static void load(EditorPantalla *editor, std::string& file);

    static void loadWorms(std::string& file, std::string &config);

    static void loadGirder(std::string& file,std::string &config);

    static void loadWeapon(std::string& file);

    static void loadWeaponCaract(std::string& file);

    static int waterLvl(std::string& file);

    static int cantidad(std::string& file);

    static float airMinSpeed(std::string& file);

    static float airMaxSpeed(std::string& file);

private:

};

#endif
