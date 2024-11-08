#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

uniform mat4 matrixProjection;

void main() {
	gl_Position = matrixProjection * vec4(aPos, 0.0, 1.0);
}