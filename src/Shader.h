//
// Created by Magnus on 30-11-2023.
//

#ifndef INC_3DENGINE_SHADER_H
#define INC_3DENGINE_SHADER_H


#include <string>
#include "glm/glm.hpp"

class Shader {
private:
    unsigned int ID;
    void _compile(const std::string &vs, const std::string &fs);
public:
    Shader(const char* vsPath, const char* fsPath);
    ~Shader();
    void use();
    void setBool(const std::string &name, bool val);
    void setInt(const std::string &name, int val);
    void setFloat(const std::string &name, float val);

    void setBool(const std::string &name, bool x, bool y);
    void setInt(const std::string &name, int x, int y);
    void setFloat(const std::string &name, float x, float y);

    void setBool(const std::string &name, bool x, bool y, bool z);
    void setInt(const std::string &name, int x, int y, int z);
    void setFloat(const std::string &name, float x, float y, float z);

    void setBool(const std::string &name, bool x, bool y, bool z, bool w);
    void setInt(const std::string &name, int x, int y, int z, int w);
    void setFloat(const std::string &name, float x, float y, float z, float w);

    void setMatrix(const std::string &name, const glm::mat4 &mat);

};


#endif //INC_3DENGINE_SHADER_H
