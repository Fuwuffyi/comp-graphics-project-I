#version 330 core

out vec4 fragColor;

in vec2 uv;

uniform float timer;

void drawVignette(inout vec3 color, vec2 uv) {    
    float vignette = uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y);
    vignette = clamp(pow(16.0 * vignette, 0.3), 0.0, 1.0);
    color *= vignette;
}

void drawScanlines(inout vec3 color, vec2 uv) {
    float scanline = clamp(0.95 + 0.05 * cos(3.14 * (uv.y + 0.008 * timer) * 240.0 * 1.0), 0.0, 1.0);
    float grille = 0.85 + 0.15 * clamp(1.5 * cos(3.14 * uv.x * 640.0 * 1.0), 0.0, 1.0);    
    color *= scanline * grille * 1.2;
}

void main() {
    vec4 col = vec4(vec3(1.0), 0.3);
    drawVignette(col.xyz, uv);
    drawScanlines(col.xyz, uv);
	fragColor = col;
}