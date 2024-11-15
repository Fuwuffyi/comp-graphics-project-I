#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 uv;

uniform float invAspectRatio;

void main() {
	uv = aPos;
	uv.y *= invAspectRatio;
	uv = (uv + 1.0) / 2.0;
	gl_Position = vec4(aPos, 0.0, 1.0);
}