#version 410 core

layout (location = 0) in vec3 inPos;

uniform mat4 uMatModel;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

out vec4 resultPos;

void main() {
    resultPos = uMatModel * vec4(inPos, 1);
    gl_Position = uMatProjection * uMatView * uMatModel * vec4(inPos, 1);;
}