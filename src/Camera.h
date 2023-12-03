//
// Created by Magnus on 02-12-2023.
//

#ifndef INC_3DENGINE_CAMERA_H
#define INC_3DENGINE_CAMERA_H


#include "glm/vec3.hpp"
#include "glm/fwd.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
private:
    glm::vec3 _pos;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _worldUp;
    glm::vec3 _right;

    float _speed;
    float _sensitivity;

    float _yaw = -90.f;
    float _pitch = 0.f;

    void update();
public:
    explicit Camera(
            glm::vec3 pos = glm::vec3(0.0f, 0.0f,  3.f),
            glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
            float speed=2.5f,
            float sensitivity=0.1f);
    glm::mat4 viewMatrix();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouse(float x, float y);

};


#endif //INC_3DENGINE_CAMERA_H
