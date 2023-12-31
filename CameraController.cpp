#ifndef CAMERA_CONTROLLER_C
#define CAMERA_CONTROLLER_C

#include "CameraController.hpp"
#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

Camera* CameraController::camera = NULL;
double CameraController::sensitivity = 0.1;
double CameraController::lastXPos = 0;
double CameraController::lastYPos = 0;
glm::vec3 CameraController::movement(0.f);

void CameraController::setCamera(Camera* _camera){
    camera = _camera;
}

Camera* CameraController::getCamera(){
    return camera;
}

void CameraController::mouseCallback(GLFWwindow* window, double xPos, double yPos){
    double offsetX = xPos - lastXPos;
    double offsetY = lastYPos - yPos;

    lastXPos = xPos;
    lastYPos = yPos;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    if(camera != NULL) camera->rotate(glm::vec3(offsetX, offsetY, 0.0));
}

void CameraController::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    
    if(key == GLFW_KEY_W && action == GLFW_PRESS) movement += glm::vec3(1.f, 0.f, 0.f);
    if(key == GLFW_KEY_A && action == GLFW_PRESS) movement += glm::vec3(0.f, 0.f, -1.f);
    if(key == GLFW_KEY_S && action == GLFW_PRESS) movement += glm::vec3(-1.f, 0.f, 0.f);
    if(key == GLFW_KEY_D && action == GLFW_PRESS) movement += glm::vec3(0.f, 0.f, 1.f);
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) movement += glm::vec3(0.f, 1.f, 0.f);
    if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) movement += glm::vec3(0.f, -1.f, 0.f);

    if(key == GLFW_KEY_W && action == GLFW_RELEASE) movement -= glm::vec3(1.f, 0.f, 0.f);
    if(key == GLFW_KEY_A && action == GLFW_RELEASE) movement -= glm::vec3(0.f, 0.f, -1.f);
    if(key == GLFW_KEY_S && action == GLFW_RELEASE) movement -= glm::vec3(-1.f, 0.f, 0.f);
    if(key == GLFW_KEY_D && action == GLFW_RELEASE) movement -= glm::vec3(0.f, 0.f, 1.f);
    if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE) movement -= glm::vec3(0.f, 1.f, 0.f);
    if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) movement -= glm::vec3(0.f, -1.f, 0.f);
}

void CameraController::update(){
    float angle = glm::radians(camera->getRotation().x);
    float posX = movement.x * cos(angle) - movement.z * sin(angle);
    float posY = movement.y;
    float posZ = movement.x * sin(angle) + movement.z * cos(angle);
    if(movement != glm::vec3(0.f)) camera->move(glm::normalize(glm::vec3(posX, posY, posZ)) * 0.5f);
}

#endif