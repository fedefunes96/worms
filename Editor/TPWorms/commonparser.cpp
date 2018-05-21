#include "commonparser.h"
#include "commonarchivo.h"
#include <string>
#include <map>
#include <editorviga.h>
#include <editorworm.h>
#include <editorusables.h>
#include <iostream>

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
#define pi 3.141592



commonParser::commonParser()
{

}

void commonParser::save(std::string &nombre, std::map<int, editorUsables> &usables,
                        std::map<int, editorWorm> &worms, std::map<int, editorViga> &vigas)
{
    commonArchivo archivo = commonArchivo(nombre, std::fstream::out);
    for (auto &worm : worms){
        saveWorm(archivo, worm.second);
    }

    for (auto &viga : vigas){
        saveViga(archivo, viga.second);
    }

    for (auto &usable : usables){
        saveUsable(archivo,usable.second,usable.first);
    }
}

void commonParser::load(EditorPantalla *editor, std::string &file)
{
    commonArchivo archivo = commonArchivo(file, std::fstream::in);
    while (!archivo.eof()){
        std::string buf;
        char c = archivo.leer_caracter();
        archivo.leer_caracter();
        if ( c == 'W'){
           archivo.leer_linea(buf, ' ');
           buf.clear();
           archivo.leer_linea(buf, ' ');
           int x = std::stoi(buf);
           archivo.leer_linea(buf, ' ');
           buf.clear();
           archivo.leer_linea(buf, ' ');
           int y = std::stoi(buf);
           buf.clear();
           archivo.leer_linea(buf, ' ');
           buf.clear();
           archivo.leer_linea(buf, ' ');
           int vida = std::stoi(buf);
           buf.clear();
           archivo.leer_linea(buf);
           editor->agregar_gusano(x,y,vida);

        }
        if (c == 'V'){
            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            int x = std::stoi(buf);
            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            int y = std::stoi(buf);
            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            float angulo = std::stof(buf);
            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            int largo = std::stoi(buf);
            int id;
            if (largo == 3){
                id = editor->agregar_viga_chica(x,y);
            } else{
                id = editor->agregar_viga_grande(x,y);
            }
            float ang = 0;
            while (ang<angulo){
                ang += 5*pi/180;
                editor->aumetar_angulo(id);
            }
            archivo.leer_linea(buf);
        }
        if (c == 'U'){
            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            int id = std::stoi(buf);

            archivo.leer_linea(buf, ' ');
            buf.clear();
            archivo.leer_linea(buf, ' ');
            int ammo = std::stoi(buf);
            editor->agregar_arma(id,ammo);
        }
    }
}

void commonParser::saveWorm(commonArchivo &archivo, editorWorm &worm)
{
    std::string buf;
    buf = "W ";
    int x = worm.getX();
    int y = worm.getY();
    int vida = worm.getVida();
    buf += "posicionX ";
    buf += std::to_string(x);
    buf += " posicionY ";
    buf += std::to_string(y);
    buf += " vida ";
    buf += std::to_string(vida);
    buf += " angulo ";
    buf += std::to_string(angle_rad);
    buf += " longitud ";
    buf += std::to_string(longitudW);
    buf += " alto ";
    buf += std::to_string(alto);
    buf += " densidad ";
    buf += std::to_string(densidad);
    buf += " velocidad ";
    buf += std::to_string(velocidad);
    buf += " saltoAciaAdelante ";
    buf += std::to_string(velocidadSaltoAX);
    buf += ' ';
    buf += std::to_string(velocidadSaltoAY);
    buf += " saltoAciaAtras ";
    buf += std::to_string(velocidadSaltoRX);
    buf += ' ';
    buf += std::to_string(velocidadSaltoRY);
    buf += " alturaSinDaño ";
    buf += std::to_string(alturaSinDanio);
    buf += '\n';
    archivo<<buf;
}

void commonParser::saveViga(commonArchivo &archivo,editorViga& viga)
{
    std::string buf;
    buf = "V ";
    buf += "posicionX ";
    buf += std::to_string(viga.getX());
    buf += " posicionY ";
    buf += std::to_string(viga.getY());
    buf += " angulo ";
    buf += std::to_string(viga.get_angulo());
    buf += " longitud ";
    buf += std::to_string(viga.get_tam());
    buf += " alto ";
    buf += std::to_string(alto);
    buf += '\n';
    archivo<<buf;
}

void commonParser::saveUsable(commonArchivo &archivo, editorUsables &usable, int id)
{
    std::string buf;
    buf = "U ";
    buf += "id ";
    buf += std::to_string(id);
    buf += " ammo ";
    buf += std::to_string(usable.getAmmo());
    buf += '\n';
    archivo<<buf;
}
