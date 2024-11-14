#version 330 core

out vec4 fragColor;

in vec2 uv;

uniform float timer;
uniform vec2 cameraPos;

// ----- STAR BACKGROUND -----
#define iterations 12
#define formuparam 0.53

#define volsteps 12
#define stepsize 0.1

#define tile 0.850

#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.730
#define saturation 0.850

vec3 backgroundStars(vec3 from, vec3 dir) {
	//volumetric rendering
	float s = 0.1, fade = 1.;
	vec3 v = vec3(0.);
	for (int r = 0; r < volsteps; ++r) {
		vec3 p = from + s * dir * .5;
		p = abs(vec3(tile) - mod(p, vec3(tile * 2.))); // tiling fold
		float pa, a = pa = 0.;
		for (int i = 0; i < iterations; ++i) { 
			p = abs(p) / dot(p, p) - formuparam; // the magic formula
			a += abs(length(p) - pa); // absolute sum of average change
			pa = length(p);
		}
		float dm = max(0., darkmatter - a * a * .001); //dark matter
		a *= a * a; // add contrast
		if (r > 6) {
            fade *= 1. - dm; // dark matter, don't render near
        }
		v += fade;
		v += vec3(s, s * s, s * s * s * s) * a * brightness * fade; // coloring based on distance
		fade *= distfading; // distance fading
		s += stepsize;
	}
	v = mix(vec3(length(v)),v,saturation); //color adjust
    return v * .01;
}

// ----- RAYMARCHED PLANETS -----

#define STEP_COUNT 30
#define MIN_DST .001
#define MAX_DST 500.

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

vec2 rayMarch(vec3 rayOrigin, vec3 rayDir) {
    float dO = 0.;
    int i = 0;
    for(; i < STEP_COUNT; ++i) {
    	vec3 p = rayOrigin + rayDir * dO;
        float dS = scene(p);
        dO += dS;
        if(dO > MAX_DST || abs(dS) < MIN_DST) break;
    }
    return vec2(dO, float(i));
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

void main() {
    vec2 trueUv = uv * 2. - 1.;
    // Initialization
    vec3 ro = vec3(cameraPos, 0.) * 10.0; // Camera position
    vec3 rd = normalize(vec3(trueUv, 1.0));
    vec3 col = vec3(0.0);
    
    // Raymarch
    vec2 d = rayMarch(ro, rd);
    if(d.x < MAX_DST) {
        vec3 p = ro + rd * d.x;
        vec3 n = calculateNormal(p);
        float dif = dot(n, normalize(vec3(0, .2, -1))) * .5 + .5;
        col = vec3(dif);
        col.rgb = pow(col.rgb, vec3(.4545));
    } else {
        float bloomFac = d.y / STEP_COUNT;
        col = vec3(backgroundStars((ro / 100.) + vec3(1., .5 , 0.5), rd));
        if (bloomFac > 0.5) {
            col += vec3(0.0, 0.0, 1.0) * bloomFac;
        }
    }
    // Gamma correction
    fragColor = vec4(col, 1.);
}