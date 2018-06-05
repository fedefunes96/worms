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
    out << longitudW;
    out << alto;
    out <<restitucion;
    out << velocidad;
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
    out<<2;
    out<<0;
    out<<50;
    out<<10;
    out<<5;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Mortar";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0;
    out<<50;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"MortarSub";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0;
    out<<10;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"GranadaVerde";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0.5;
    out<<30;
    out <<YAML::EndSeq;


    out<<YAML::Key<<"GranadaRoja";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0.5;
    out<<30;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"GranadaRojaSub";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0.5;
    out<<10;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Banana";
    out<<YAML::BeginSeq;
    out<<4;
    out<<1;
    out<<70;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"GranadaS";
    out<<YAML::BeginSeq;
    out<<8;
    out<<0.5;
    out<<110;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Dinamita";
    out<<YAML::BeginSeq;
    out<<4;
    out<<0.5;
    out<<50;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Bate";
    out<<YAML::BeginSeq;
    out<<0;
    out<<0;
    out<<10;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Aereo";
    out<<YAML::BeginSeq;
    out<<2;
    out<<0;
    out<<40;
    out <<YAML::EndSeq;

    out<<YAML::Key<<"Teletransportador";
    out<<YAML::BeginSeq;
    out<<0;
    out<<0;
    out<<0;
    out <<YAML::EndSeq;

    out <<YAML::EndMap;


    std::string nombre = "config.yaml";
    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void commonParser::save(std::string &nombre, std::map<int, editorUsables> &usables,
                        std::map<int, editorWorm> &worms, std::map<int, editorViga> &vigas, int cant)
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
        out << worm.second.getX();
        out << worm.second.getY();
        out << worm.second.getVida();
        out <<YAML::EndSeq;
    }
    out <<YAML::EndSeq;

    out <<YAML::Key<<"Girder";
    out <<YAML::BeginSeq;
    for (auto &viga : vigas){
        out<<YAML::Flow;
        out<<YAML::BeginSeq;
        out<<viga.second.getX();
        out<<viga.second.getY();
        out<<viga.second.get_angulo();
        out<<viga.second.get_tam();
        out<<YAML::EndSeq;
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

    out <<YAML::EndMap;
    commonArchivo archivo = commonArchivo(nombre,std::fstream::out);
    archivo<<out.c_str();
}

void commonParser::load(EditorPantalla *editor, std::string &file)
{
    try{
        YAML::Node config = YAML::LoadFile(file);
        if (config["Girder"]){
            for (YAML::iterator it = config["Girder"].begin(); it != config["Girder"].end(); ++it){
                const YAML::Node& girder = *it;
                int x = girder[0].as<int>();
                int y = girder[1].as<int>();
                y = -y;
                float angulo = girder[2].as<float>();
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
        if (config["Worm"]){
            for (YAML::iterator it = config["Worm"].begin(); it != config["Worm"].end(); ++it){
                const YAML::Node& worm = *it;
                int x = worm[0].as<int>();
                int y = worm[1].as<int>();
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
    } catch(std::exception &e){
        std::cout<<e.what()<<"\n";
    }

}

void commonParser::loadWorms(std::string &file, std::string &config)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Worm"]){
        int i= 0;
        for (YAML::iterator it = editor["Worm"].begin(); it != editor["Worm"].end(); ++it,++i){
            const YAML::Node& worm = *it;
            int x = worm[0].as<int>()*6/140;
            int y = worm[1].as<int>()*6/140;
            int health = worm[2].as<int>();
            float angl = cfg["Worm"][0].as<float>();
            int longitud = cfg["Worm"][1].as<int>();
            int height = cfg["Worm"][2].as<int>();
            int restitution = cfg["Worm"][3].as<int>();
            float speed = cfg["Worm"][4].as<float>();
            float fowJumX  = cfg["Worm"][5].as<float>();
            float fowJumy  = cfg["Worm"][6].as<float>();
            float backJumX  = cfg["Worm"][7].as<float>();
            float backJumY  = cfg["Worm"][8].as<float>();
            int alturaMax = cfg["Worm"][9].as<int>();
            int dkgPorM = cfg["Worm"][10].as<int>();
            int damgMax = cfg["Worm"][11].as<int>();
            // Crea el gusano como prefieras
            // cambia la firma de la funcion a lo que te convenga.

        }
    }
}

void commonParser::loadGirder(std::string &file, std::string &config)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Girder"]){
        for (YAML::iterator it = editor["Girder"].begin(); it != editor["Girder"].end(); ++it){
            const YAML::Node& girder = *it;
            int x = girder[0].as<int>();
            int y = girder[1].as<int>();
            float angle = girder[2].as<float>();
            int longitud = girder[3].as<int>();
            float height = cfg["Girder"][0].as<float>();
            // Crea la viga como quieras
            // cambia la firma de la funcion a lo que te convenga.
        }
    }
}

void commonParser::loadWeapon(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    if (config["Usable"]){
         for (YAML::iterator it = config["Usable"].begin(); it != config["Usable"].end(); ++it){
             const YAML::Node& usable = *it;
             int id = usable[0].as<int>();
             int ammo = usable[1].as<int>();
         }
    }
}

void commonParser::loadWeaponCaract(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);

    int radius = config["Bazooka"][0].as<int>();
    int restitution = config["Bazooka"][1].as<int>();
    int max_damg = config["Bazooka"][2].as<int>();
    int VDisparo = config["Bazooka"][3].as<int>();
    int VAngular = config["Bazooka"][4].as<int>();
    std::cout<<radius<<std::endl;

    /*for (YAML::iterator it = config["Mortar"].begin(); it != config["Mortar"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["MortarSub"].begin(); it != config["MortarSub"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["GranadaVerde"].begin(); it != config["GranadaVerde"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["GranadaRoja"].begin(); it != config["GranadaRoja"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["GranadaRojaSub"].begin(); it != config["GranadaRojaSub"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["Banana"].begin(); it != config["Banana"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["GranadaS"].begin(); it != config["GranadaS"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["Dinamita"].begin(); it != config["Dinamita"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["Bate"].begin(); it != config["Bate"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["Aereo"].begin(); it != config["Aereo"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }

    for (YAML::iterator it = config["Teletransportador"].begin(); it != config["Teletransportador"].end(); ++it){
        const YAML::Node& usable = *it;
        float radius = usable[0].as<float>();
        float restitution = usable[1].as<float>();
        float max_damg = usable[2].as<float>();
    }*/
}

int commonParser::waterLvl(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Water"].as<int>();
}

int commonParser::cantidad(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Cantidad"].as<int>();
}

float commonParser::airMinSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][0].as<int>();
}

float commonParser::airMaxSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][1].as<int>();
}


