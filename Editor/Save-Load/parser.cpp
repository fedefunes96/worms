#include "parser.h"
#include "commonarchivo.h"
#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <math.h>

#define pi 3.141592

Parser::Parser()
{

}

void Parser::save(std::string &nombre, std::map<int, editorUsables> &usables,
                        std::map<int, editorWorm> &worms, 
                        std::map<int, editorViga> &vigas,
                        unsigned int cant, std::string &backgrund)
{
    float height = 0;
    YAML::Emitter out;
    out << YAML::BeginMap; 
    out<<YAML::Key<<"Cantidad";
    out<<cant;
    out <<YAML::Key<<"Worm";
    out <<YAML::BeginSeq;
    for (auto &worm : worms){
        out <<YAML::Flow;
        out << YAML::BeginSeq;
        float x = (worm.second.getX()*6)/140.0;
        float y = (worm.second.getY()*6)/140.0;
        out << x;
        out << y;
        out << worm.second.getVida();
        x = worm.second.getX();
        y = worm.second.getY();
        out << x;
        out << y;
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Small Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
        int tam = viga.second.get_tam();
        float x = (viga.second.getX()*6)/140.0;
        float y = (viga.second.getY()*6)/140.0;
        if (height < y){
            height = y;
        }
        if (tam == 3){
            out<<YAML::Flow;
            out<<YAML::BeginSeq;
            out<<x;
            out<<y;
            out<<viga.second.get_angulo();
            out<<tam;
            x = viga.second.getX();
            y = viga.second.getY();
            out << x;
            out << y;
            out<<YAML::EndSeq;
        }
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Big Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
        int tam = viga.second.get_tam();
        float x = (viga.second.getX()*6)/140.0;
        float y = (viga.second.getY()*6)/140.0;
        if (tam == 6){
            out<<YAML::Flow;
            out<<YAML::BeginSeq;
            out<<x;
            out<<y;
            out<<viga.second.get_angulo();
            out<<tam;
            x = viga.second.getX();
            y = viga.second.getY();
            out << x;
            out << y;
            out<<YAML::EndSeq;
        }
    }
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Usable";
    out<<YAML::BeginSeq;
    for (auto &usable : usables){
        out<<YAML::Flow;
        out<<YAML::BeginSeq;
        out<<std::to_string(usable.first);
        out<<usable.second.getAmmo();
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Background";
    out<<backgrund;

    height += 10;
    out<<YAML::Key<<"Air Strike";
    out<<height;

    out <<YAML::EndMap;
    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void Parser::load(MapEditor *editor, std::string &file)
{
    try{
        YAML::Node config = YAML::LoadFile(file);
        if (config["Small Girder"]){
            for (YAML::iterator it = config["Small Girder"].begin(); 
                it != config["Small Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = girder[4].as<int>();
                int y = girder[5].as<int>();
                y = -y;
                float angulo = girder[2].as<float>();
                int id;
                id = editor->add_small_girder(x,y);
                int angle = ceil(angulo*180/pi);
                int resto = angle %5;
                angle -= resto;
                editor->aumetar_angulo(id,angle);
            }
        }
        if (config["Big Girder"]){
            for (YAML::iterator it = config["Big Girder"].begin(); 
                it != config["Big Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = (girder[4].as<int>());
                int y = girder[5].as<int>();
                y = -y;
                float angulo = girder[2].as<float>();
                int id;
                id = editor->add_big_girder(x,y);
                int angle = ceil(angulo*180/pi);
                int resto = angle %5;
                angle -= resto;
                editor->aumetar_angulo(id,angle);
            }
        }
        if (config["Worm"]){
            for (YAML::iterator it = config["Worm"].begin(); 
                it != config["Worm"].end(); ++it){
                const YAML::Node& worm = *it;
                int x = worm[3].as<int>();
                int y = worm[4].as<int>();
                y = -y;
                int id = editor->add_worm(x,y);
                int vida = worm[2].as<int>();
                editor->setVIdaWorm(id,vida);
            }
        }
        if (config["Usable"]){
             for (YAML::iterator it = config["Usable"].begin(); 
                it != config["Usable"].end(); ++it){
                 const YAML::Node& usable = *it;
                 int id = usable[0].as<int>();
                 int ammo = usable[1].as<int>();
                 editor->agregar_arma(id,ammo);
             }
        }
        if (config["Background"]){
            std::string background = config["Background"].as<std::string>();
            editor->setBacGround(background);
        }
    } catch(std::exception &e){
        std::cout<<e.what()<<"\n";
    }

}
