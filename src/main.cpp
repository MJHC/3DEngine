#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexArray.h"
#include "ObjectBuffer.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include "wtypes.h"
#include "Camera.h"
#include "Mesh.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Camera &camera);
void mouseCallback(GLFWwindow *window, double x, double y);

void getDesktopResolution(int& x, int& y);
void errorCallback(int error, const char* description);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera = Camera();
float lastX = 400;
float lastY = 300;
bool firstMouse = true;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    int y;
    int x;

    getDesktopResolution(x, y);
    int windowHeight = 600;
    int windowWidth = 800;
    int centerX = (x / 2) - (windowWidth / 2);
    int centerY = (y / 2) - (windowHeight / 2);

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetErrorCallback(errorCallback);

    // this loads adress of openGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetWindowPos(window, centerX, centerY);

    Shader myShader = Shader("../res/shader/shader.vs", "../res/shader/shader.fs");

    glEnable(GL_DEPTH_TEST);


    std::vector<Texture> textures = {
            Texture("../res/img/block.png", "image", true, GL_RGBA),
            };
    Mesh myCube = Mesh::cube(textures);
    Mesh mySphere = Mesh::sphere(1.f, 10, 10);

    std::vector<glm::vec3> cubePos = {};
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            cubePos.push_back(glm::vec3(i, 0, j));
        }
    }

    while(!glfwWindowShouldClose(window)){
        processInput(window, camera);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);


        glm::mat4 view = camera.viewMatrix();

        myShader.setMatrix("view", view);
        myShader.setMatrix("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3 (0.f, 0.f, 0.f));
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.f, .0f, 0.0f));
        //myShader.setMatrix("model", model);

        for (glm::vec3 &pos : cubePos){
            glm::mat4 cubeModel = glm::translate(model, pos);
            myShader.setMatrix("model", glm::rotate(cubeModel, (float)glfwGetTime(), glm::vec3(1.f, 1.f, 1.f)));
            myCube.draw(myShader);
        }

        myShader.setMatrix("model", glm::translate(model, glm::vec3 (0.f, 5.f, 0.f)));
        mySphere.draw(myShader);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(window);
        // polls io and other events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Camera &camera){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
        camera.processKeyboard(CameraMovement::DOWN, deltaTime);
}

void mouseCallback(GLFWwindow *window, double x, double y){
    auto xpos = static_cast<float>(x);
    auto ypos = static_cast<float>(y);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;
    camera.processMouse(xoffset, yoffset);
}

void getDesktopResolution(int& x, int& y)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    x = desktop.right;
    y = desktop.bottom;
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}