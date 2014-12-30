#pragma once

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>

class FileHelper {
public:
    static unsigned char *readBinary( std::string filepath, int *p_filesize ) {
        std::ifstream file( filepath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
        if(!file.is_open()) {
            throw std::runtime_error(filepath);
        }
        *p_filesize = (int)file.tellg();
        char *data = new char[*p_filesize];
        file.seekg(0, std::ios::beg);
        if(!file.read( data, *p_filesize )) {
            throw std::runtime_error("failed to read from " + filepath );
        }
        file.close();
        return (unsigned char *)data;
    }

    static void writeBinary( std::string filepath, unsigned char*data, int filesize ) {
        std::ofstream file( filepath.c_str(), std::ios::out | std::ios::binary );
        if(!file.is_open()) {
             throw std::runtime_error("cannot open file " + filepath );
        }
        if( !file.write( (char *)data, filesize ) ) {
            throw std::runtime_error("failed to write to " + filepath );
        }
        file.close();
    }

    static bool exists( const std::string filepath ) {
       std::ifstream testifstream(filepath.c_str() );
       bool exists = testifstream.good();
       testifstream.close();
       return exists;
    }
};

