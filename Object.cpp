#ifndef OBJECT_C
#define OBJECT_C

#include "Object.hpp"
#include <glm/ext/matrix_transform.hpp>

Object::Object(): Object(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)){}

Object::Object(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation){
    pos = _pos;
    scale = _scale;
    rotation = _rotation;    

    calculateVectors();
    updateModelView();
}

void Object::updateModelView(){
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.f, 1.f));

    normalModel = glm::transpose(glm::inverse(model));
}

void Object::move(glm::vec3 vec){
    pos += vec;
    updateModelView();
}

void Object::rotate(glm::vec3 _rotation){
    rotation += _rotation;
    calculateVectors();
    updateModelView();
}

void Object::setPos(glm::vec3 _pos){
    pos = _pos;
    updateModelView();
}

void Object::setScale(glm::vec3 _scale){
    scale = _scale;
    updateModelView();
}

void Object::setRotation(glm::vec3 _rotation){
    rotation = _rotation;
    updateModelView();
    calculateVectors();
}

void Object::moveForward(float dist){
    pos += forward * dist;
}

void Object::calculateVectors(){
    if(rotation.y > 89) rotation.y = 89;
    if(rotation.y < -89) rotation.y = -89;
    glm::vec3 _angles = glm::radians(rotation);
    forward.x = cos(_angles.x) * cos(_angles.y);
    forward.y = sin(_angles.y);
    forward.z = sin(_angles.x) * cos(_angles.y);

    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));
    up = glm::cross(forward, right);
}

#endif