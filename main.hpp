#include "Object.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

int controlledObject = 0;
// 0: camera
// 1: cubo1

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

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);