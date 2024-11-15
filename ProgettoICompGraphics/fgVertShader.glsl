#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec2 uv;
out vec2 worldPos;

uniform float invAspectRatio;
uniform vec2 playerPos;

void main() {
	uv = aPos;
	uv.y *= invAspectRatio;
	uv = (uv + 1.0) / 2.0;
	worldPos = aPos + playerPos;
	gl_Position = vec4(aPos, 0.0, 1.0);
}