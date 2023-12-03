//
// Created by Magnus on 01-12-2023.
//

#ifndef INC_3DENGINE_TEXTURE_H
#define INC_3DENGINE_TEXTURE_H
#include <string>

class Texture {
private:
    std::string _name;
public:
    unsigned int id;
    Texture(const char *path, std::string name, bool flip, GLenum format);
    void bind();
    std::string name();
    std::string str();
};


#endif //INC_3DENGINE_TEXTURE_H
