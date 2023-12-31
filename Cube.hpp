#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.hpp"
#include "Object.hpp"

class Cube : public Object{
    private:

        glm::vec3 color = glm::vec3(1.f, 0.5f, 1.f);

        static GLuint vao;
        static Shader defaultShader;
        static glm::vec3 lightSource;

    public:
        Cube();
        Cube(
            glm::vec3 _pos,
            glm::vec3 _scale,
            glm::vec3 _rotation
        );

        static void init();

        static glm::vec3 getLightSource();
        static void setLightSource(glm::vec3 _lightSource);

        void setColor(glm::vec3 _color){color = _color;}
        glm::vec3 getColor(){return color;}

        void draw(glm::mat4 view, glm::mat4 projection);
        void draw(glm::mat4 view, glm::mat4 projection, Shader* shader);
};

#endif