#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in mat4 inMatModel;

uniform mat4 uMatView;
uniform mat4 uMatProjection;

out vec3 resultPos;
out vec3 resultNorm;

void main() {
    resultPos = (inMatModel * vec4(inPos, 1)).xyz;
    resultNorm = mat3(inMatModel) * inNorm;
    gl_Position = uMatProjection * inverse(uMatView) * inMatModel * vec4(inPos, 1);
}