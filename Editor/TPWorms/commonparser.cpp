#include "commonparser.h"
#include "commonarchivo.h"
#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <iostream>
#include <yaml-cpp/yaml.h>

#define angle_rad "0"
#define longitudW "1"
#define alto "1"
#define densidad "1"
#define restitucion "0"
#define velocidad "0.2"
#define velocidadSaltoAX "1"
#define velocidadSaltoAY "0.5"
#define velocidadSaltoRX "0.2"
#define velocidadSaltoRY "1.2"
#define alturaSinDanio "2"
#define alturaGirder "0.8"
#define pi 3.141592



commonParser::commonParser()
{

}

void commonParser::save(std::string &nombre, std::map<int, editorUsables> &usables,
                        std::map<int, editorWorm> &worms, std::map<int, editorViga> &vigas)
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out <<YAML::Key<<"Water";
    out<<0;
    out <<YAML::Key<<"Worm";
    out <<YAML::BeginSeq;
    for (auto &worm : worms){
        out <<YAML::Flow;
        out << YAML::BeginSeq;
        out << std::to_string(worm.second.getX());
        out << std::to_string(worm.second.getY());
        out << angle_rad;
        out << longitudW;
        out << alto;
        out <<restitucion;
        out << std::to_string(worm.second.getVida());
        out << velocidad;
        out << velocidadSaltoAX;
        out <<velocidadSaltoAY;
        out << velocidadSaltoRX;
        out <<velocidadSaltoRY;
        out<<alturaSinDanio;
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
        out<<YAML::Flow;
        out<<YAML::BeginSeq;
        out<<std::to_string(viga.second.getX());
        out<<std::to_string(viga.second.getY());
        out<<viga.second.get_angulo();
        out<<std::to_string(viga.second.get_tam());
        out<<alturaGirder;
        out<<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Usable";
    out<<YAML::BeginSeq;
    for (auto &usable : usables){
        out<<YAML::Flow;
        out<<YAML::BeginSeq;
        out<<std::to_string(usable.first);
        out<<std::to_string(usable.second.getAmmo());
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out <<YAML::EndMap;


    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void commonParser::load(EditorPantalla *editor, std::string &file)
{
    try{
        YAML::Node config = YAML::LoadFile(file);
        if (config["Worm"]){
            for (YAML::iterator it = config["Worm"].begin(); it != config["Worm"].end(); ++it){
                const YAML::Node& worm = *it;
                int x = worm[0].as<int>();
                int y = worm[1].as<int>();
                y = -y;
                int id = editor->agregar_gusano(x,y);
                int vida = worm[6].as<int>();
                editor->setVIdaWorm(id,vida);
            }
        }
        if (config["Girder"]){
            for (YAML::iterator it = config["Girder"].begin(); it != config["Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = girder[0].as<int>();
                int y = girder[1].as<int>();
                y = -y;
                float angulo = girder[2].as<float>();
                std::cout<<angulo<<std::endl;
                int longitud = girder[3].as<int>();
                int id;
                if (longitud == 3){
                    id = editor->agregar_viga_chica(x,y);
                } else {
                    id = editor->agregar_viga_grande(x,y);
                }
                float anguloActual = 0;
                while (anguloActual < angulo) {
                    editor->aumetar_angulo(id);
                    anguloActual += 5*pi/180;
                }
            }
        }
        if (config["Usable"]){
             for (YAML::iterator it = config["Usable"].begin(); it != config["Usable"].end(); ++it){
                 const YAML::Node& usable = *it;
                 int id = usable[0].as<int>();
                 int ammo = usable[1].as<int>();
                 editor->agregar_arma(id,ammo);
             }
        }
    } catch(std::exception &e){
        std::cout<<e.what()<<"\n";
    }
}

