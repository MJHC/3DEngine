//
// Created by Magnus on 30-11-2023.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "utils.h"

std::string loadFile(const char* path){
    std::string content;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        content = stream.str();
    }
    catch (std::ifstream::failure e){
        std::cout << "ERROR::FILE_LOAD\n" << path << std::endl;
    }
    return std::move(content);
}