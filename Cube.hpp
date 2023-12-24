#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.hpp"

class Cube{
    private:
        glm::vec3 pos;
        glm::vec3 scale;
        glm::vec3 rotation;

        glm::mat4 model;

        static GLuint vao;
        static Shader defaultShader;

        void updateModelView();

    public:
        Cube();
        Cube(
            glm::vec3 _pos,
            glm::vec3 _scale,
            glm::vec3 _rotation
        );

        static void init();

        void setPos(glm::vec3 _pos);
        void setScale(glm::vec3 _scale);
        void setRotation(glm::vec3 _rotation);
        glm::vec3 getPos(){return pos;}
        glm::vec3 getScale(){return scale;}
        glm::vec3 getRotation(){return rotation;}

        void move(glm::vec3 vec);
        void rotate(glm::vec3 _rotation);

        void draw(glm::mat4 view, glm::mat4 projection);
        void draw(glm::mat4 view, glm::mat4 projection, Shader* shader);
};

#endif