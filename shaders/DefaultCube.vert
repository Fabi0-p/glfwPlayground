#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 _normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalModel;

out vec3 normal;
out vec3 fragPos;

void main(){
    gl_Position = projection * view * model * vec4(pos, 1.0);
    fragPos = vec3(model * vec4(pos, 1.0));
    normal = mat3(normalModel) * _normal;
}