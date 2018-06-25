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

void commonArchivo::operator<<(std::string &buf)
{
    this->fs<<buf;
}

void commonArchivo::operator<<(const char *buf)
{
    this->fs<<buf;
}
