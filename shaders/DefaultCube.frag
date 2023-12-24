#version 330

out vec4 outColor;
in vec3 outPos;

float dist;

void main(){
    outColor = vec4(outPos, 1.0);
}