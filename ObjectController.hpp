#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

#include "Object.hpp"
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

class ObjectController{
    private:
        static double sensitivity;
        static double lastXPos;
        static double lastYPos;
        static glm::vec3 movement;
        static Object *object;
    public:
        static void setObject(Object* _object);
        static Object* getObject();
        static void mouseController(double xPos, double yPos);
        static void keyboardController(int key, int scancode, int action, int mods);
        static void update();
        // glm::mat4 getView(){return camera->getView(); }
};

#endif
