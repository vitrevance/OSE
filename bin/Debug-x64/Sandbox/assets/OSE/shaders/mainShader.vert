#version 410 core

layout (location = 0) in vec4 inVertex;
layout (location = 1) in vec4 inBase1;
layout (location = 2) in vec4 inBase2;
layout (location = 3) in vec4 inBase3;
layout (location = 4) in mat4 inMatModel;

out vec4 outVertex;
out vec4 outBase1;
out vec4 outBase2;
out vec4 outBase3;

void main() {
    outVertex = inMatModel * inVertex;
    outBase1 = inMatModel * inBase1;
    outBase2 = inMatModel * inBase2;
    outBase3 = inMatModel * inBase3;
    gl_Position = vec4(0);
}