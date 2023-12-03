//
// Created by Magnus on 01-12-2023.
//

#include "ObjectBuffer.h"
#include "glad/glad.h"

ObjectBuffer::ObjectBuffer(unsigned int type, bool dynamic) {
    this->type = type;
    this->dynamic = dynamic;
    glGenBuffers(1, &ID);
}

ObjectBuffer::~ObjectBuffer() {
    glDeleteBuffers(1, &ID);
}

void ObjectBuffer::bind() {
    glBindBuffer(this->type, this->ID);
}

void ObjectBuffer::unbind() {
    glBindBuffer(this->type, 0);
}

void ObjectBuffer::setData(void *data, unsigned int size) {
    glBufferData(this->type, size, data, this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}