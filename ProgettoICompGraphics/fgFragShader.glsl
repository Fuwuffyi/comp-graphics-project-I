#version 330 core

out vec4 fragColor;

in vec2 uv;

uniform float timer;

uniform uint bVignette;
uniform uint bScanlines;
uniform float scanlineScale;
uniform float transparency;

// Slightly blurred borders
void drawVignette(inout vec3 color, vec2 uv) {    
    float vignette = uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y);
    vignette = clamp(pow(16.0 * vignette, 0.3), 0.0, 1.0);
    color *= vignette;
}

// Lines on screen for CRT effect
void drawScanlines(inout vec3 color, vec2 uv) {
    float scanline = clamp(0.95 + 0.05 * cos(3.14 * (uv.y + 0.008 * timer * 4.0) * 240.0 * 1.0), 0.0, 1.0);
    float grille = 0.85 + 0.15 * clamp(1.5 * cos(3.14 * uv.x * 640.0 * 1.0), 0.0, 1.0);    
    color *= scanline * grille * 1.2;
}

void main() {
    vec3 col = vec3(1.0);
    if (bVignette == 1u) {
        drawVignette(col, uv);
    }
    if (bScanlines == 1u) {
        drawScanlines(col, uv * scanlineScale);
    }
    vec4 scanlineCol = vec4(1.0 - col, transparency);
	fragColor = scanlineCol;
}