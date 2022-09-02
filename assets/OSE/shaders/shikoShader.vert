#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;

uniform mat4 uMatModel;
uniform mat4 uMatRotation;
uniform mat4 uMatView;
uniform mat4 uMatProjection;

out vec3 resultPos;
out vec3 resultNorm;
out vec3 camPos;

void main() {
    resultPos = (uMatModel * uMatRotation * vec4(inPos, 1)).xyz;
    resultNorm = (uMatRotation * vec4(inNorm, 1)).xyz;
    camPos.x = uMatView[3][0];
    camPos.y = uMatView[3][1];
    camPos.z = uMatView[3][2];
    //camPos = (uMatRotation * vec4(0, 0, 1, 1)).xyz;
    //mat4 MatModel = uMatModel * uMatRotation;
    gl_Position = uMatProjection * inverse(uMatView) * uMatModel * uMatRotation * vec4(inPos, 1);
}