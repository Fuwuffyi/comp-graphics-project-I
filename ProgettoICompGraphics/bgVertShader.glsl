#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 uv;

uniform mat4 camProjMat;

void main() {
	uv = aPos;
	gl_Position = camProjMat * vec4(aPos, 0.0, 1.0);
}