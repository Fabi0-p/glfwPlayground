#ifndef CUBE_C 
#define CUBE_C

#include "Cube.hpp"
#include "Object.hpp"
#include <glm/fwd.hpp>


Shader Cube::defaultShader;
GLuint Cube::vao;
glm::vec3 Cube::lightSource;

void Cube::init(){
    defaultShader.create("shaders/DefaultCube.vert", "shaders/DefaultCube.frag", "outColor");
    float vertices[] = {
        // Cara superior [0]
        1, 1, 1, 0, 1, 0,
        -1, 1, 1, 0, 1, 0,
        -1, 1, -1, 0, 1, 0,
        1, 1, -1, 0, 1, 0,
        // Cara inferior [4]
        1, -1, 1, 0, -1, 0,
        -1,-1, 1, 0, -1, 0,
        -1,-1, -1, 0, -1, 0,
        1, -1, -1, 0, -1, 0,
        // Cara derecha [8]
        1, 1, 1, 1, 0, 0,
        1, -1, 1, 1, 0, 0,
        1, -1, -1, 1, 0, 0,
        1, 1, -1, 1, 0, 0,
        // Cara izquierda [12]
        -1, 1, 1, -1, 0, 0,
        -1, -1, 1, -1, 0, 0,
        -1, -1, -1, -1, 0, 0,
        -1, 1, -1, -1, 0, 0,
        // Cara frontal [16] 
        1, 1, 1, 0, 0, 1,
        1, -1, 1, 0, 0, 1,
        -1, -1, 1, 0, 0, 1,
        -1, 1, 1, 0, 0, 1,
        // Cara trasera [20]
        1, 1, -1, 0, 0, -1,
        1, -1, -1, 0, 0, -1,
        -1, -1, -1, 0, 0, -1,
        -1, 1, -1, 0, 0, -1
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 3, 2, // Cara superior
        4, 5, 6, 4, 7, 6, // Cara inferior
        8, 9, 10, 8, 11, 10, // Cara derecha
        12, 13, 14, 12, 15, 14, // Cara izquierda
        16, 17, 18, 16, 19, 18, // Cara frontal
        20, 21, 22, 20, 23, 22 // Cara trasera
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Cube::setLightSource(glm::vec3 _lightSource){
    lightSource = _lightSource;
}

glm::vec3 Cube::getLightSource(){
    return lightSource;
}

Cube::Cube(): Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)){}

Cube::Cube(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation): Object(_pos, _scale, _rotation){}

void Cube::draw(glm::mat4 view, glm::mat4 projection, Shader *shader){
    glBindVertexArray(vao);
    shader->use();

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setMat4("normalModel", normalModel);
    shader->setVec3("color", color);
    shader->setVec3("lightSource", lightSource);
    shader->setVec3("cubePos", pos);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::draw(glm::mat4 view, glm::mat4 projection){
    draw(view, projection, &defaultShader);
}

#endif