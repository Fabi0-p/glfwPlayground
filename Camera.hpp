#ifndef CAMERA_H
#define CAMERA_H

#include "Object.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera: public Object{
    public:
        Camera();
        Camera(glm::vec3 _pos);
        Camera(glm::vec3 _pos, glm::vec3 _angles);

        glm::mat4 getView();
};

#endif