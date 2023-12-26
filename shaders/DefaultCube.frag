#version 330

in vec3 normal;
out vec4 outColor;

uniform vec3 color;
uniform vec3 cubePos;

void main(){
    float bright = dot(normalize(normal), normalize(vec3(0., 5., 0) - cubePos));
    outColor = vec4(color, 1.0) * bright;
}