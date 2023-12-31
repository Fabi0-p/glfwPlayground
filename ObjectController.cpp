#ifndef OBJECT_CONTROLLER_C
#define OBJECT_CONTROLLER_C

#include "ObjectController.hpp"
#include "Object.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

Object* ObjectController::object = NULL;
double ObjectController::sensitivity = 0.1;
double ObjectController::lastXPos = 0;
double ObjectController::lastYPos = 0;
glm::vec3 ObjectController::movement(0.f);

void ObjectController::setObject(Object* _object){
    object = _object;
}

Object* ObjectController::getObject(){
    return object;
}

void ObjectController::mouseController(double xPos, double yPos){
    double offsetX = xPos - lastXPos;
    double offsetY = lastYPos - yPos;

    lastXPos = xPos;
    lastYPos = yPos;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    if(object != NULL) object->rotate(glm::vec3(offsetX, offsetY, 0.0));
}

void ObjectController::keyboardController(int key, int scancode, int action, int mods){
    
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

void ObjectController::update(){
    float angle = glm::radians(object->getRotation().x);
    float posX = movement.x * cos(angle) - movement.z * sin(angle);
    float posY = movement.y;
    float posZ = movement.x * sin(angle) + movement.z * cos(angle);
    if(movement != glm::vec3(0.f)) object->move(glm::normalize(glm::vec3(posX, posY, posZ)) * 0.5f);
}

#endif