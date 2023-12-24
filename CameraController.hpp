#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

class CameraController{
    private:
        static double sensitivity;
        static double lastXPos;
        static double lastYPos;
        static glm::vec3 movement;
        static Camera *camera;
    public:
        static void setCamera(Camera* _camera);
        static Camera* getCamera();
        static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
        static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void update();
        // glm::mat4 getView(){return camera->getView(); }
};

#endif
