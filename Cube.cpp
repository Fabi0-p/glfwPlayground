#ifndef CUBE_C 
#define CUBE_C

#include "Cube.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader Cube::defaultShader;
GLuint Cube::vao;

void Cube::init(){
    defaultShader.create("shaders/DefaultCube.vert", "shaders/DefaultCube.frag", "outColor");
        float vertices[] = {
        1, 1, 1,
        1, 1, -1,
        1, -1, -1,
        1, -1, 1,
        -1, 1, 1,
        -1, 1, -1,
        -1, -1, -1,
        -1, -1, 1
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 3, 2, // Cara derecha
        0, 1, 5, 0, 4, 5, // Cara superior
        0, 3, 7, 0, 4, 7, // Cara trasera
        5, 4, 6, 4, 6, 7, // Cara izquierda
        1, 2, 5, 2, 5, 6, // Cara frontal
        2, 3, 6, 3, 6, 7 // Cara inferior
    };

    glGenVertexArrays(1, &vao);

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);


    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}

Cube::Cube(): Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)){}

Cube::Cube(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation){
    pos = _pos;
    scale = _scale;
    rotation = _rotation;    

    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.f, 1.f));
}

void Cube::draw(glm::mat4 view, glm::mat4 projection, Shader *shader){
    glBindVertexArray(vao);
    shader->use();

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::draw(glm::mat4 view, glm::mat4 projection){
    draw(view, projection, &defaultShader);
}

void Cube::move(glm::vec3 vec){
    pos += vec;
    updateModelView();
}

void Cube::rotate(glm::vec3 _rotation){
    rotation += _rotation;
    updateModelView();
}

void Cube::setPos(glm::vec3 _pos){
    pos = _pos;
    updateModelView();
}

void Cube::setScale(glm::vec3 _scale){
    scale = _scale;
    updateModelView();
}

void Cube::setRotation(glm::vec3 _rotation){
    rotation = _rotation;
    updateModelView();
}

void Cube::updateModelView(){
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.f, 1.f));
}

#endif