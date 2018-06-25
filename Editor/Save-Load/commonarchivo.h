#ifndef COMMONARCHIVO_H
#define COMMONARCHIVO_H

#include <string>
#include <fstream>

class commonArchivo
{
private:
    std::fstream fs;

public:
    commonArchivo(const commonArchivo& other){}

    commonArchivo(std::string &nombre, const std::ios_base::openmode mode);

    ~commonArchivo();

    void operator<<(std::string &buf);

    void operator<<(const char *buf);
};


#endif
