#version 410 core

out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

struct LightSource {
    vec3 position;
    mat4 rotation;
    vec3 color;
    int type;
};

uniform LightSource uLights[20];
uniform int uNumLights;

void main() {
    //for (int i = 0; i < uNumLights && i < 1; i++)
    vec3 lightDir = normalize(vec3(1, -1, 1));
    frag_color = vec4(resultPos, 1) * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}