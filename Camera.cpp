#ifndef CAMERA_C
#define CAMERA_C

#include"Camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(): Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)){calculateVectors();}
Camera::Camera(glm::vec3 _pos): Camera(_pos, glm::vec3(0.0f, 0.0f, 0.0f)){calculateVectors();}
Camera::Camera(glm::vec3 _pos, glm::vec3 _angles): pos(_pos), angles(_angles){calculateVectors();}

glm::vec3 Camera::getTarget(){
    return forward;
}

void Camera::move(glm::vec3 vec){pos += vec;}

void Camera::rotate(glm::vec3 _angles){
    angles += _angles;
    calculateVectors();    
}


void Camera::setAngles(glm::vec3 _angles){
    angles = _angles;
    calculateVectors();
}

void Camera::moveForward(float dist){
    pos += getTarget() * dist;
}

void Camera::calculateVectors(){
    if(angles.y > 89) angles.y = 89;
    if(angles.y < -89) angles.y = -89;
    glm::vec3 _angles = glm::radians(angles);
    forward.x = cos(_angles.x) * cos(_angles.y);
    forward.y = sin(_angles.y);
    forward.z = sin(_angles.x) * cos(_angles.y);

    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));
    up = glm::cross(forward, right);
}

glm::mat4 Camera::getView(){
    // return glm::lookAt(pos, pos + forward, up);
    return glm::lookAt(pos, pos + forward, glm::vec3(0.f, 1.f, 0.f));
}

#endif