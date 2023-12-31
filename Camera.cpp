#ifndef CAMERA_C
#define CAMERA_C

#include"Camera.hpp"
#include "Object.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(): Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)){}
Camera::Camera(glm::vec3 _pos): Camera(_pos, glm::vec3(0.0f, 0.0f, 0.0f)){}
Camera::Camera(glm::vec3 _pos, glm::vec3 _rotation): Object(_pos, glm::vec3(1.f, 1.f, 1.f), _rotation){}

glm::mat4 Camera::getView(){
    // return glm::lookAt(pos, pos + forward, up);
    return glm::lookAt(pos, pos + forward, glm::vec3(0.f, 1.f, 0.f));
}

#endif