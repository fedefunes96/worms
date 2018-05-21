#include "commonarchivo.h"
#include <string>

commonArchivo::commonArchivo(std::string &nombre,
                             const std::ios_base::openmode mode)
{
    this->fs.open(nombre,mode);
    if (!this->fs.is_open()){
        throw -1;
    }
}

commonArchivo::~commonArchivo()
{
    this->fs.close();
}

void commonArchivo::leer_linea(std::string &buf)
{
    std::getline(this->fs,buf);
}

void commonArchivo::leer_linea(std::string &buf, char delim)
{
    std::getline(this->fs,buf,delim);
}

char commonArchivo::leer_caracter()
{
    return this->fs.get();
}

bool commonArchivo::eof()
{
    return this->fs.eof();
}

void commonArchivo::operator<<(std::string &buf)
{
    this->fs<<buf;
}
