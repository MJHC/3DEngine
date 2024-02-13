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

    void setVec2f(const std::string &name, const glm::vec2 &vec);
    void setVec3f(const std::string &name, const glm::vec3 &vec);
    void setVec4f(const std::string &name, const glm::vec4 &vec);
    void setMat4(const std::string &name, const glm::mat4 &mat);

};


#endif //INC_3DENGINE_SHADER_H
