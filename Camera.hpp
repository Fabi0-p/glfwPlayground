#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera{
    private:
        glm::vec3 pos;
        glm::vec3 angles;

        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        void calculateVectors();

    public:
        Camera();
        Camera(glm::vec3 _pos);
        Camera(glm::vec3 _pos, glm::vec3 _angles);

        void setPos(glm::vec3 _pos){pos = _pos;}
        void setAngles(glm::vec3 _angles);
        glm::vec3 getPos(){return pos;}
        glm::vec3 getAngles(){return angles;}

        void moveForward(float dist);
        void move(glm::vec3 vec);
        void rotate(glm::vec3 _angles);

        glm::vec3 getTarget();
        glm::mat4 getView();
};

#endif