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

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Camera &camera);
void mouseCallback(GLFWwindow *window, double x, double y);

void getDesktopResolution(int& x, int& y);
void errorCallback(int error, const char* description);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera = Camera(glm::vec3(.0f, 2.f, 5.0f));
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
bool firstMouse = true;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    int y;
    int x;

    getDesktopResolution(x, y);
    int windowHeight = SCREEN_HEIGHT;
    int windowWidth = SCREEN_WIDTH;
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

    Shader textureShader = Shader("../res/shader/shader.vs", "../res/shader/shader.fs");
    Shader colorShader = Shader("../res/shader/shader.vs", "../res/shader/color.fs");

    glEnable(GL_DEPTH_TEST);


    std::vector<Texture> textures = {
            Texture("../res/img/block.png", "image", true, GL_RGBA),
            };



    Mesh myCube = Mesh::cube(textures);
    Mesh sun = Mesh::sphere(1.f, 20, 20);
    glm::vec3 sunPos = glm::vec3(1.2f, 1.0f, 2.0f);

    
    std::vector<glm::vec3> plane ={glm::vec3(0.f, 1.f, 0.f)};

    for (int i=0; i < 16; i++){
        for (int j=0; j < 16; j++){
            plane.push_back(glm::vec3(i - 8, 0, j - 8));
        }
    }
    
    while(!glfwWindowShouldClose(window)){
        processInput(window, camera);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.viewMatrix();
        glm::vec3 camPos = camera.pos();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        textureShader.use();
        for (glm::vec3 &pos : plane){
            textureShader.setMat4("view", view);
            textureShader.setMat4("projection", projection);
            textureShader.setMat4("model", glm::translate(model, pos));
            textureShader.setVec3f("material.color", glm::vec3(1.f));
            textureShader.setVec3f("material.ambient", glm::vec3(1.f));
            textureShader.setVec3f("material.diffuse", glm::vec3(1.f));
            textureShader.setVec3f("material.specular", glm::vec3(1.f));
            textureShader.setFloat("material.shininess", 16.f);

            textureShader.setVec3f("light.ambient",  glm::vec3(.2f));
            textureShader.setVec3f("light.diffuse",  glm::vec3(.5f)); // darken diffuse light a bit
            textureShader.setVec3f("light.specular", glm::vec3(1.f)); 
            textureShader.setVec3f("lightPos", sunPos);
            textureShader.setVec3f("viewPos", camPos);
            myCube.draw(textureShader);
        }




        colorShader.use();

        colorShader.setMat4("view", view);
        colorShader.setMat4("projection", projection);
        

        // Rotating sun !
        const float sunRadius = 1.2f; 
        float sunAngle = glfwGetTime();  


        float sunX = sin(sunAngle) * sunRadius;
        float sunZ = cos(sunAngle) * sunRadius;
        sunPos = glm::vec3(sunX, 2.0f, sunZ);

        // Create a model matrix for the sun
        glm::mat4 sunModel = glm::translate(glm::mat4(1.0f), sunPos);
        sunModel = glm::scale(sunModel, glm::vec3(0.2f)); 
        colorShader.setMat4("model", sunModel);
        colorShader.setVec3f("objectColor", glm::vec3(1.f));
        sun.draw(colorShader);


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