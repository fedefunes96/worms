#include "commonparser.h"
#include "commonarchivo.h"
#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <iostream>
#include <yaml-cpp/yaml.h>

#define angle_rad 0
#define longitudW 1
#define alto 1
#define densidad 1
#define restitucion 0
#define velocidad 0.2
#define velocidadSaltoAX 1
#define velocidadSaltoAY 0.5
#define velocidadSaltoRX 0.2
#define velocidadSaltoRY 1.2
#define alturaSinDanio 2
#define alturaGirder 0.8
#define pi 3.141592
#define velVMin 0.2
#define velVMax 10
#define dmgXM 1
#define dmgMax 25

commonParser::commonParser()
{

}

void commonParser::saveConfig()
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out <<YAML::Key<<"Water";
    out<<0;

    out <<YAML::Key<<"Wind";
    out << YAML::BeginSeq;
    out<<velVMin;
    out<<velVMax;
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Worm";
    out <<YAML::BeginSeq;
    out << angle_rad;
    //total health
    out << longitudW;
    out << alto;
    out <<restitucion;
    out<<velocidad;
    out << velocidadSaltoAX;
    out <<velocidadSaltoAY;
    out << velocidadSaltoRX;
    out <<velocidadSaltoRY;
    out<<alturaSinDanio;
    out<<dmgXM;
    out <<dmgMax;
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Girder";
    out << YAML::BeginSeq;
    out<<alturaGirder;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Bazooka";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<50;//max dmg
    out<<2;//pusback
    out<<2;//exp rad
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Mortar";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<50;//max dmg
    out<<2;//pusback
    out<<2;//exp rad
    out<<6;//cant frag
    out<<5;//V frag
    out<<1;//rad frag
    out<<10;//max dm frag
    out <<YAML::EndSeq;

    out<<YAML::Key<<"GreenGrenade";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<0.5;//restitution
    out<<30;//max dmg
    out<<2;//pusback
    out<<2;//exp rad
    out <<YAML::EndSeq;


    out<<YAML::Key<<"RedGrenade";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<0.5;//restitution
    out<<30;//max dmg
    out<<2;//pusback
    out<<2;//exp rad
    out<<6;//cant frag
    out<<5;//V frag
    out<<1;//rad frag
    out<<10;//max dm frag
    out <<YAML::EndSeq;


    out<<YAML::Key<<"Banana";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<1;//restitution
    out<<70;//max dmg
    out<<2;//pusback
    out<<4;//exp rad
    out <<YAML::EndSeq;

    out<<YAML::Key<<"HolyGrenade";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<0.5;//restitution
    out<<110;//max dmg
    out<<2;//pusback
    out<<8;//exp rad
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Dynimite";
    out<<YAML::BeginSeq;
    out<<1;//rad
    out<<0;//restitution
    out<<50;//max dmg
    out<<2;//pusback
    out<<4;//exp rad
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Bate";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<10;//dmg
    out <<YAML::EndSeq;

    out<<YAML::Key<<"AirAttack";
    out<<YAML::BeginSeq;
    out<<10;//V
    out<<2;//rad
    out<<40;//max dmg
    out<<420;//from create
    out<<2;//pusback
    out<<2;//exp rad
    out <<YAML::EndSeq;

    out <<YAML::EndMap;


    std::string nombre = "config.yaml";
    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void commonParser::save(std::string &nombre, std::map<int, editorUsables> &usables,
                        std::map<int, editorWorm> &worms, std::map<int, editorViga> &vigas,
                        unsigned int cant, std::string &backgrund)
{
    YAML::Emitter out;
    out << YAML::BeginMap; 
    out<<YAML::Key<<"Cantidad";
    out<<cant;
    out <<YAML::Key<<"Worm";
    out <<YAML::BeginSeq;
    for (auto &worm : worms){
        out <<YAML::Flow;
        out << YAML::BeginSeq;
        out << worm.second.getX()*6/144;
        out << worm.second.getY()*6/144;
        out << worm.second.getVida();
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Small Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
                int tam = viga.second.get_tam();
        float x = viga.second.getX()*6/144 + tam/2;
        float y = viga.second.getY()*6/144;
        if (tam == 3){
            out<<YAML::Flow;
            out<<YAML::BeginSeq;
            out<<x;
            out<<y;
            out<<viga.second.get_angulo();
            out<<tam;
            out<<YAML::EndSeq;
        }
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Big Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
        int tam = viga.second.get_tam();
        float x = viga.second.getX()*6/144 + tam/2;
        float y = viga.second.getY()*6/144;
        if (tam == 6){
            out<<YAML::Flow;
            out<<YAML::BeginSeq;
            out<<x;
            out<<y;
            out<<viga.second.get_angulo();
            out<<tam;
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

    out <<YAML::EndMap;
    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void commonParser::load(EditorPantalla *editor, std::string &file)
{
    try{
        YAML::Node config = YAML::LoadFile(file);
        if (config["Small Girder"]){
            for (YAML::iterator it = config["Small Girder"].begin(); it != config["Small Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = girder[0].as<int>();
                int y = girder[1].as<int>()*144/6;
                y = -y;
                float angulo = girder[2].as<float>();
                int longitud = girder[3].as<int>();
                x -= longitud/2 +0.5;
                x = x *144/6;
                int id;
                id = editor->agregar_viga_chica(x,y);
                float anguloActual = 0;
                while (anguloActual < angulo) {
                    editor->aumetar_angulo(id);
                    anguloActual += 5*pi/180;
                }
            }
        }
        if (config["Big Girder"]){
            for (YAML::iterator it = config["Big Girder"].begin(); it != config["Big Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = girder[0].as<int>();
                int y = girder[1].as<int>()*144/6;
                y = -y;
                float angulo = girder[2].as<float>();
                int longitud = girder[3].as<int>();
                x -= longitud/2 +0.5;
                x = x *144/6;
                int id;
                id = editor->agregar_viga_grande(x,y);
                float anguloActual = 0;
                while (anguloActual < angulo) {
                    editor->aumetar_angulo(id);
                    anguloActual += 5*pi/180;
                }
            }
        }
        if (config["Worm"]){
            for (YAML::iterator it = config["Worm"].begin(); it != config["Worm"].end(); ++it){
                const YAML::Node& worm = *it;
                int x = worm[0].as<int>()*144/6;
                int y = worm[1].as<int>()*144/6;
                y = -y;
                int id = editor->agregar_gusano(x,y);
                int vida = worm[2].as<int>();
                editor->setVIdaWorm(id,vida);
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
        if (config["Background"]){
            std::string background = config["Background"].as<std::string>();
            editor->setBacGround(background);
        }
    } catch(std::exception &e){
        std::cout<<e.what()<<"\n";
    }

}
