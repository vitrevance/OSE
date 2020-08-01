#version 410 core

out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

void main() {
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = vec4(resultPos, 1) * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}