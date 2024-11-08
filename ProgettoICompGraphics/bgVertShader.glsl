#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 uv;

uniform mat4 matrixProjection;

void main() {
	uv = aPos;
	gl_Position = matrixProjection * vec4(aPos, 0.0, 1.0);
}