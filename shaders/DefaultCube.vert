#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 _normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;

void main(){
    gl_Position = projection * view * model * vec4(pos, 1.0);
    normal = mat3(transpose(inverse(model))) * _normal;
}