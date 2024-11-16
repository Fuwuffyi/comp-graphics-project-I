#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec4 color;	
out vec2 pos;

uniform mat4 objMatrix;
uniform mat4 camMatrix;
uniform uint uuid;

float random(vec2 st) {
    return fract(sin(dot(st + vec2(float(int(uuid) % 1024), 0.0), vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    if (length(aPos) == 0.0) {
        pos = vec2(0.0);
    } else {
        pos = normalize(aPos);
        pos *= (random(pos) + 1.0) / 2.0;
    }
    gl_Position = camMatrix * objMatrix * vec4(pos, 0.0, 1.0);
    color = aCol;
}