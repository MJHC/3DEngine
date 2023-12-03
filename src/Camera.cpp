//
// Created by Magnus on 02-12-2023.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 worldUp, float speed, float sensitivity) {
    _pos = pos;
    _front = front;
    _worldUp = worldUp;
    _speed = speed;
    _sensitivity = sensitivity;
}

glm::mat4 Camera::viewMatrix() {
    return glm::lookAt(_pos, _pos + _front, _up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    const float speed = _speed * deltaTime;
    if (direction == FORWARD)
        _pos += speed * glm::vec3(_front.x, 0, _front.z);
    if (direction == BACKWARD)
        _pos -= speed * glm::vec3(_front.x, 0, _front.z);;
    if (direction == LEFT)
        _pos -= glm::normalize(glm::cross(_front, _up)) * speed;
    if (direction == RIGHT)
        _pos += glm::normalize(glm::cross(_front, _up)) * speed;
    if(direction == UP)
        _pos += glm::normalize(_worldUp) * speed;
    if(direction == DOWN)
        _pos -= glm::normalize(_worldUp) * speed;
}

void Camera::processMouse(float x, float y) {

    x *= _sensitivity;
    y *= _sensitivity;

    _yaw   += x;
    _pitch += y;

    if(_pitch > 89.0f)
        _pitch = 89.0f;
    if(_pitch < -89.0f)
        _pitch = -89.0f;
    this->update();
}

void Camera::update() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up    = glm::normalize(glm::cross(_right, _front));
}