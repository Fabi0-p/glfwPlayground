#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <iterator>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Camera.hpp"
#include "ObjectController.hpp"
#include "Cube.hpp"

#include "main.hpp"

#define CUBE_COUNT 300

Camera camera(glm::vec3(0.0f, 5.0f, -17.0f), glm::vec3(90.f, -5.f, 0.f));
Cube lightCube(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f));

int main()
{
    bool running = true; 
    
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Playground", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    glewExperimental = GL_TRUE;
    glewInit();
    Cube::init();

    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, 0);

    ObjectController::setObject(&camera);
    controlledObject = 0;
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glm::mat4 projection = glm::perspective(glm::radians(45.0), 1.0, 1.0, 1000.0);
    glm::mat4 view;

    srand(0);

    Cube cubo[CUBE_COUNT];
    for(int i = 0; i < CUBE_COUNT; i++){
        float randX;
        float randY;
        float randZ;

        randX = (rand() % 100) - 50;    
        randY = (rand() % 20);    
        randZ = (rand() % 100) - 50;            
        cubo[i].setPos(glm::vec3(randX, randY, randZ));

        randX = (rand() % 100) / 50. + 0.2; 
        cubo[i].setScale(glm::vec3(randX, randX, randX));

        randX = (rand() % 360);    
        randY = (rand() % 360);    
        randZ = (rand() % 360);    
        cubo[i].setRotation(glm::vec3(randX, randY, randZ));

        randX = (float)rand() / float(RAND_MAX);    
        randY = (float)rand() / float(RAND_MAX);    
        randZ = (float)rand() / float(RAND_MAX);    
        cubo[i].setColor(glm::vec3(randX, randY, randZ));
    }

    Shader shaderLightCube("shaders/DefaultCube.vert", "shaders/FlatCube.frag", "outColor");

    Cube cubo2(glm::vec3(0.0f, 15.0f, -17.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    Cube suelo(glm::vec3(0.f, 0.f, 0.f), glm::vec3(50.f, 1.0f, 50.f), glm::vec3(0.f, 0.f, 0.f));
    suelo.setColor(glm::vec3(1.f, .5f, .5f));
    lightCube.setColor(glm::vec3(1.f, 1.f, 1.f));
    Cube::setLightSource(lightCube.getPos());

    while(running){
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            running = false;
        
        // glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        ObjectController::update();
        view = camera.getView();

        for(int i = 0; i < CUBE_COUNT; i++){
            cubo[i].draw(view, projection);
        }
        Cube::setLightSource(lightCube.getPos());
        lightCube.draw(view, projection, &shaderLightCube);
        cubo2.draw(view, projection);
        suelo.draw(view, projection);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}


void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
        if(controlledObject == 0){
            ObjectController::setObject(&lightCube);
            lightCube.setRotation(camera.getRotation());
            controlledObject = 1;
        }
        else if(controlledObject == 1){
            ObjectController::setObject(&camera);
            controlledObject = 0;
        }
    }
    ObjectController::keyboardController(key, scancode, action, mods);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos){
    if(controlledObject == 0) ObjectController::mouseController(xPos, yPos);
}