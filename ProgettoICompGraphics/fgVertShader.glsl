#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 uv;

void main() {
	uv = (aPos + 1.0) / 2.0;
	gl_Position = vec4(aPos, 0.0, 1.0);
}