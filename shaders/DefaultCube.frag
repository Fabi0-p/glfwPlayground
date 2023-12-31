#version 330

in vec3 normal;
in vec3 fragPos;
out vec4 outColor;

uniform vec3 color;
uniform vec3 lightSource;

void main(){
    float bright = 0.1;
    bright += max(dot(normalize(normal), normalize(lightSource - fragPos)), 0);
    bright = min(bright, 1.);
    outColor = vec4(color, 1.0) * bright;
}