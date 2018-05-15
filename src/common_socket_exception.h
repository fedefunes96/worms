#include <iostream>
#include <exception>

class SocketException : public std::runtime_error {
    public:
    	explicit SocketException(const char* msg) 
    	: std::runtime_error(msg) {}      
};
