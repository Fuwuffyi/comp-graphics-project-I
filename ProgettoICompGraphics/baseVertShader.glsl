#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec4 color;	

uniform mat4 objMatrix;
uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * objMatrix * vec4(aPos, 0.0, 1.0);
    color = aCol;
}