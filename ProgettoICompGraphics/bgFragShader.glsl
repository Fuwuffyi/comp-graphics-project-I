#version 330 core

out vec4 fragColor;

in vec2 uv;
in vec2 worldPos;

uniform float worldSize;
uniform float timer;
uniform vec2 cameraPos;

// ----- STAR BACKGROUND -----
uniform uint starVolumetricSteps;
uniform uint starIterations;

#define FORMUPARAM 0.53

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
	for (uint r = 0u; r < starVolumetricSteps; ++r) {
		vec3 p = from + s * dir * 0.5;
		p = abs(tileVec - mod(p, tileVec2)); // tiling fold
        float pa;
        float a = pa = 0.0;
        for (uint i = 0u; i < starIterations; ++i) {
            float lenP = length(p);
            a += abs(lenP - pa); // Sum of the change in length
            pa = lenP;
            p = abs(p) / (dot(p, p) + 1e-6) - FORMUPARAM;
        }
		float dm = max(0.0, DARKMATTER - a * a * 0.001); //dark matter
		a *= a * a; // add contrast
		if (r > 6u) {
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
uniform uint rayStepCount;
uniform float rayMinDist;
uniform float rayMaxDist;

float sphereDst(vec3 ray, vec3 pos, float size) {
    return length(ray - pos) - size;
}

float scene(vec3 ray) {
    vec3 sunPos = vec3(0, 0, 100.);
    float sun = sphereDst(ray, sunPos, 15.);
    vec3 planet1Pos = sunPos + vec3(
        cos(timer * 0.6),
        sin(timer * 0.6),
        0.0) * 45.0;
    float planet1 = sphereDst(ray, planet1Pos, 5.);
    vec3 planet2Pos = sunPos + vec3(
        cos(timer * 1.0 + 0.4),
        sin(timer * 1.0 + 0.4),
        0.0) * 75.0;
    float planet2 = sphereDst(ray, planet2Pos, 4.);
    return min(sun, min(planet1, planet2));
}

float rayMarch(vec3 rayOrigin, vec3 rayDir) {
    float dO = 0.;
    for(uint i = 0u; i < rayStepCount; ++i) {
    	vec3 p = rayOrigin + rayDir * dO;
        float dS = scene(p);
        dO += dS;
        if(dO > rayMaxDist || abs(dS) < rayMinDist) break;
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

uniform float distortionRadiusPerc;

void main() {
    vec2 trueUv = uv * 2. - 1.;
    vec3 ro = vec3(cameraPos, 0.) * 10.0;
    vec3 rd = normalize(vec3(trueUv, 1.0));
    vec3 col = vec3(0.0);

    float dstFromCenter = length(worldPos);
    float distortionRadius = worldSize * distortionRadiusPerc;
    float dstFactor = smoothstep(distortionRadius, -distortionRadius, dstFromCenter - worldSize);
    // Add black hole distortion at the edge of the map
    if (dstFromCenter >= worldSize - distortionRadius) {
        if (dstFromCenter > worldSize) {
            rd *= 1 - dstFactor;
            ro = -ro;
        } else {
            rd *= dstFactor;
        }
    }

    // Raymarch
    float d = rayMarch(ro, rd);
    if (d < rayMaxDist) {
        // Add the planets if the ray hit them
        vec3 p = ro + rd * d;
        vec3 n = calculateNormal(p);
        float dif = dot(n, normalize(vec3(0, .2, -1))) * .5 + .5;
        col = vec3(dif);
        col.rgb = pow(col.rgb, vec3(.4545));
    } else {
        // Add the stars to everything else
        col = vec3(backgroundStars((ro / 100.) + vec3(1., .5, 0.5), rd));
    }
    fragColor = vec4(col, 1.0);
}