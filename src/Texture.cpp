//
// Created by Magnus on 01-12-2023.
//
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <sstream>
#include "stb_image.h"
#include "glad/glad.h"
#include "Texture.h"

Texture::Texture(const char *path, std::string name, bool flip, GLenum format) {
    glGenTextures(1, &id);
    _name = name;

    this->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(false);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

std::string Texture::name() {
    return _name;
}

std::string Texture::str() {
    std::ostringstream addr;
    addr << this;
    return "Texture {\nID: " + std::to_string(id) + "\nName: " + _name + "\nAddress: " + addr.str() + "\n}";
}