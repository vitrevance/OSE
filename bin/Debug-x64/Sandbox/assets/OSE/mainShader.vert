#version 410 core

layout (location = 0) in vec3 inPos;

uniform mat4 uMatModel;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

void main() {
    //gl_Position = vec4((uMatProjection * uMatView * uMatModel * vec4(inPos, 1)).xy, 0, 1);
    gl_Position = uMatView * vec4(inPos, 1);
}