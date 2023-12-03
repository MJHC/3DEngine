//
// Created by Magnus on 01-12-2023.
//

#ifndef INC_3DENGINE_VERTEXARRAY_H
#define INC_3DENGINE_VERTEXARRAY_H


#include <vector>
#include "glad/glad.h"



class VertexArray {
private:
    unsigned int ID;



public:
    VertexArray();
    ~VertexArray();
    void attrib(GLuint index, GLint size, GLenum type, GLsizei stride, unsigned int offset);
    void bind() const;
    static void unbind();
};


#endif //INC_3DENGINE_VERTEXARRAY_H
