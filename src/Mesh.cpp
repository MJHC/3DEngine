//
// Created by Magnus on 02-12-2023.
//

#include <iostream>
#include <utility>
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures) {
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    _textures = std::move(textures);

    _VAO.bind();

    _VBO.bind();
    _VBO.setData(&_vertices[0], _vertices.size() * sizeof(Vertex));

    _EBO.bind();
    _EBO.setData(&_indices[0], _indices.size() * sizeof(unsigned int));


    GLsizei stride = sizeof(Vertex);

    _VAO.attrib(0, 3, GL_FLOAT, stride, 0);
    _VAO.attrib(1, 3, GL_FLOAT, stride, offsetof(Vertex, Normal));
    _VAO.attrib(2, 2, GL_FLOAT, stride, offsetof(Vertex, TexCoords));

    _VAO.unbind();
}

void Mesh::draw(Shader &shader) {
    shader.use();

    for (int i = 0; i < _textures.size(); i++) {
        Texture &texture = _textures[i];
        glActiveTexture(GL_TEXTURE0 + i);
        shader.setInt(texture.name(), i);
        texture.bind();
    }
    //std::exit(EXIT_SUCCESS);

    _VAO.bind();
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    VertexArray::unbind();
    glActiveTexture(GL_TEXTURE0);
}

Mesh Mesh::cube(std::vector<Texture> &textures) {
    std::vector<Vertex> vertices = {
            // Front face
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f)},
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.5f)},
            {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)},

            // Back face
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 0.5f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.5f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.5f, 1.0f)},

            // Right face
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.5f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f)},

            // Left face
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.5f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f)},

            // Top face
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.5f)},
            {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.5f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2 (0.5f, 1.0f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2  (0.0f, 1.0f)},

            // Bottom face
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(.5f, 0.0f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(.5f, .5f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(.0f, .5f)}
    };

    std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0,   // Front face
            4, 5, 6, 6, 7, 4,   // Back face
            8, 9, 10, 10, 11, 8,   // Right face
            12, 13, 14, 14, 15, 12,   // Left face
            16, 17, 18, 18, 19, 16,   // Top face
            20, 21, 22, 22, 23, 20    // Bottom face
    };
    return Mesh(vertices, indices, textures);
}

Mesh Mesh::sphere(float radius, int numStacks, int numSlices){
    std::vector<Vertex> vertices;
    float phi, theta;
    float phiIncrement = M_PI / numStacks;
    float thetaIncrement = 2.0f * M_PI / numSlices;

    for (int i = 0; i <= numStacks; ++i) {
        phi = i * phiIncrement;

        for (int j = 0; j <= numSlices; ++j) {
            theta = j * thetaIncrement;

            Vertex vertex;
            vertex.Position.x = radius * sin(phi) * cos(theta);
            vertex.Position.y = radius * sin(phi) * sin(theta);
            vertex.Position.z = radius * cos(phi);

            // Calculate the normal vector as the normalized position vector
            vertex.Normal = glm::normalize(vertex.Position);

            // Texture coordinates can be set as per your requirements
            vertex.TexCoords.x = static_cast<float>(j) / numSlices;
            vertex.TexCoords.y = static_cast<float>(i) / numStacks;

            vertices.push_back(vertex);
        }
    }
    std::vector<unsigned int> indices;

    for (int i = 0; i < numStacks; ++i) {
        for (int j = 0; j < numSlices; ++j) {
            int index0 = i * (numSlices + 1) + j;
            int index1 = index0 + 1;
            int index2 = (i + 1) * (numSlices + 1) + j;
            int index3 = index2 + 1;

            // First triangle of the quad
            indices.push_back(index0);
            indices.push_back(index1);
            indices.push_back(index2);

            // Second triangle of the quad
            indices.push_back(index2);
            indices.push_back(index1);
            indices.push_back(index3);
        }
    }
    std::vector<Texture> tt = {};
    return Mesh(vertices, indices, tt);
}

Mesh::~Mesh() {
    for (Texture &texture : _textures){
        glDeleteTextures(1, &texture.id);
    }
}