//
// Created by Magnus on 01-12-2023.
//

#ifndef INC_3DENGINE_OBJECTBUFFER_H
#define INC_3DENGINE_OBJECTBUFFER_H


class ObjectBuffer {
private:
    unsigned int ID;
    unsigned int type;
    bool dynamic;
public:
    ObjectBuffer(unsigned int type, bool dynamic);
    ~ObjectBuffer();
    void setData(void *data, unsigned int size);
    void bind();
    void unbind();
};


#endif //INC_3DENGINE_OBJECTBUFFER_H
