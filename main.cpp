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
#include "CameraController.hpp"
#include "Cube.hpp"

#define CUBE_COUNT 300

void GLAPIENTRY MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message);
}

const char* vertexGroundShaderSrc = R"glsl(
    #version 330
    
    layout (location = 0) in vec3 pos;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;


    void main(){
        gl_Position = projection * view * model * vec4(pos, 1.0);
    }
)glsl";

const char* fragmentGroundShaderSrc = R"glsl(
    #version 330

    out vec4 outColor;

    float dist;

    void main(){
        outColor = vec4(0.2, 0.2, 0.2, 1.0);
    }
)glsl";

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

    Camera camera(glm::vec3(0.0f, 5.0f, -17.0f), glm::vec3(90.f, -5.f, 0.f));
    CameraController::setCamera(&camera);
    glfwSetCursorPosCallback(window, CameraController::mouseCallback);
    glfwSetKeyCallback(window, CameraController::keyboardCallback);
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
        // std::cout << "Pos[" << i << "]: randX: " << randX << "- randY: " randY

        randX = (rand() % 100) / 50. + 0.2; 
        cubo[i].setScale(glm::vec3(randX, randX, randX));

        randX = (rand() % 360);    
        randY = (rand() % 360);    
        randZ = (rand() % 360);    
        cubo[i].setRotation(glm::vec3(randX, randY, randZ));

        randX = (float)rand() / float(RAND_MAX);    
        randY = (float)rand() / float(RAND_MAX);    
        randZ = (float)rand() / float(RAND_MAX);    
        std::cout << randX << std::endl;
        cubo[i].setColor(glm::vec3(randX, randY, randZ));
    }

    Cube cubo1(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    Cube cubo2(glm::vec3(0.0f, 15.0f, -17.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    Cube suelo(glm::vec3(0.f, 0.f, 0.f), glm::vec3(50.f, 1.0f, 50.f), glm::vec3(0.f, 0.f, 0.f));
    suelo.setColor(glm::vec3(.2f, .2f, .2f));
    cubo1.setColor(glm::vec3(1.f, 1.f, 1.f));

    while(running){
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            running = false;
        
        glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        cubo1.rotate(glm::vec3(0.05f, 0.05f, 0.05f));
        CameraController::update();
        view = camera.getView();

        for(int i = 0; i < CUBE_COUNT; i++){
            cubo[i].draw(view, projection);
        }

        cubo1.draw(view, projection);
        cubo2.draw(view, projection);
        suelo.draw(view, projection);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
