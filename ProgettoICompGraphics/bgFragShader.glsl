#version 330 core

out vec4 fragColor;

in vec2 uv;
in vec2 worldPos;

uniform float worldSize;
uniform float timer;
uniform vec2 cameraPos;

// ----- STAR BACKGROUND -----
#define ITERATIONS 12
#define FORMUPARAM 0.53

#define VOLSTEPS 12
#define STEPSIZE 0.1

#define TILE 0.850

#define BRIGHTNESS 0.0015
#define DARKMATTER 0.300
#define DISTFADING 0.730
#define SATURATION 0.850

vec3 backgroundStars(vec3 from, vec3 dir) {
    // Volumetric star rendering
    const vec3 tileVec = vec3(TILE);
    const vec3 tileVec2 = vec3(TILE * 2.0);
    float s = 0.1;
    float fade = 1.0;
	vec3 v = vec3(0.0);
	for (int r = 0; r < VOLSTEPS; ++r) {
		vec3 p = from + s * dir * 0.5;
		p = abs(tileVec - mod(p, tileVec2)); // tiling fold
        float pa;
        float a = pa = 0.0;
        for (int i = 0; i < ITERATIONS; ++i) {
            float lenP = length(p);
            a += abs(lenP - pa); // Sum of the change in length
            pa = lenP;
            p = abs(p) / (dot(p, p) + 1e-6) - FORMUPARAM;
        }
		float dm = max(0.0, DARKMATTER - a * a * 0.001); //dark matter
		a *= a * a; // add contrast
		if (r > 6) {
            fade *= 1.0 - dm; // dark matter, don't render near
        }
		v += fade;
		v += vec3(s, s * s, s * s * s * s) * a * BRIGHTNESS * fade; // coloring based on distance
		fade *= DISTFADING; // distance fading
		s += STEPSIZE;
	}
    // Color adjust
	v = mix(vec3(length(v)), v, SATURATION);
    return v * 0.01;
}

// ----- RAYMARCHED PLANETS -----

#define STEP_COUNT 30
#define MIN_DST .01
#define MAX_DST 250.

float sphereDst(vec3 ray, vec3 pos, float size) {
    return length(ray - pos) - size;
}

float scene(vec3 ray) {
    // Create a sun
    vec3 sunPos = vec3(0, 0, 100.);
    float sun = sphereDst(ray, sunPos, 15.);
    
    // Create a first planet to orbit the sun
    float planet1Speed = 0.6;
    float planet1Phase = 0.0;
    float planet1RotDist = 45.;
    vec3 planet1Pos = sunPos + planet1RotDist * vec3(
        cos((timer + planet1Phase) * planet1Speed), 
        sin((timer + planet1Phase) * planet1Speed), 
    0.0);
    float planet1 = sphereDst(ray, planet1Pos, 5.);
    
    // Create a second planet to orbit the sun
    float planet2Speed = 1.;
    float planet2Phase = 0.4;
    float planet2RotDist = 75.;
    vec3 planet2Pos = sunPos + planet2RotDist * vec3(
        cos((timer + planet2Phase) * planet2Speed), 
        sin((timer + planet2Phase) * planet2Speed), 
    0.0);
    float planet2 = sphereDst(ray, planet2Pos, 4.);
    
    // Return the entire scene
    return min(sun, min(planet1, planet2));
}

float rayMarch(vec3 rayOrigin, vec3 rayDir) {
    float dO = 0.;
    for(int i = 0; i < STEP_COUNT; ++i) {
    	vec3 p = rayOrigin + rayDir * dO;
        float dS = scene(p);
        dO += dS;
        if(dO > MAX_DST || abs(dS) < MIN_DST) break;
    }
    return dO;
}

vec3 calculateNormal(vec3 p) {
	float d = scene(p);
    vec2 e = vec2(.001, 0);
    vec3 n = d - vec3(
        scene(p-e.xyy),
        scene(p-e.yxy),
        scene(p-e.yyx));
    return normalize(n);
}

// ----- MAIN -----

#define DISTORTION_RADIUS 1.0

void main() {
    vec2 trueUv = uv * 2. - 1.;
    // Initialization
    vec3 ro = vec3(cameraPos, 0.) * 10.0; // Camera position
    vec3 rd = normalize(vec3(trueUv, 1.0));
    vec3 col = vec3(0.0);

    // Black hole distortion
    float dstFromCenter = length(worldPos);
    vec3 distortionColor = vec3(1.0);
    if (dstFromCenter > worldSize - DISTORTION_RADIUS) {
        float dstFactor = smoothstep(DISTORTION_RADIUS / 2.0, -DISTORTION_RADIUS / 2.0, dstFromCenter - worldSize);
        if (dstFactor <= DISTORTION_RADIUS / 2.0) {
            rd *= 1 - dstFactor;
            ro = -ro;
        } else {
            rd *= dstFactor;
        }
    }
    
    // Raymarch
    float d = rayMarch(ro, rd);
    if(d < MAX_DST) {
        vec3 p = ro + rd * d;
        vec3 n = calculateNormal(p);
        float dif = dot(n, normalize(vec3(0, .2, -1))) * .5 + .5;
        col = vec3(dif);
        col.rgb = pow(col.rgb, vec3(.4545));
    } else {
        col = vec3(backgroundStars((ro / 100.) + vec3(1., .5 , 0.5), rd));
    }
    fragColor = vec4(col * distortionColor, 1.0);
}