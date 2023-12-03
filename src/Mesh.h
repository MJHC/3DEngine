//
// Created by Magnus on 02-12-2023.
//

#ifndef INC_3DENGINE_MESH_H
#define INC_3DENGINE_MESH_H

#include "VertexArray.h"
#include "ObjectBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};



class Mesh {
private:
    VertexArray _VAO;
    ObjectBuffer _VBO = ObjectBuffer(GL_ARRAY_BUFFER, false);
    ObjectBuffer _EBO = ObjectBuffer(GL_ELEMENT_ARRAY_BUFFER, false);
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;

public:
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned  int> &indices, std::vector<Texture> &textures);
    ~Mesh();
    void draw(Shader &shader);
    static Mesh cube(std::vector<Texture> &textures);
    static Mesh sphere(float radius, int numStacks, int numSlices);
};


#endif //INC_3DENGINE_MESH_H
