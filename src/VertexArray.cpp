//
// Created by Magnus on 01-12-2023.
//

#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind() const {
    glBindVertexArray(ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::attrib(GLuint index, GLint size, GLenum type, GLsizei stride,
                         unsigned int offset) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(index);
}

