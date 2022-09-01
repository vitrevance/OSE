#version 410 core

layout (location = 0) in vec4 inVertex;
layout (location = 1) in vec4 inBase1;
layout (location = 2) in vec4 inBase2;
layout (location = 3) in vec4 inBase3;
layout (location = 4) in vec2 inUVvertex, inUVbase_1;
layout (location = 5) in vec2 inUVbase_2, inUVbase_3;
layout (location = 6) in mat4 inMatModel;
layout (location = 10) in vec4 inVecModel;

out vec4 outVertex;
out vec4 outBase1;
out vec4 outBase2;
out vec4 outBase3;
out vec2 outUVVe, outUVB1, outUVB2, outUVB3;
out vec4 translate;

void main() {
    outVertex = inMatModel * inVertex + inVecModel;
    outBase1 = inMatModel * inBase1 + inVecModel;
    outBase2 = inMatModel * inBase2 + inVecModel;
    outBase3 = inMatModel * inBase3 + inVecModel;
    outUVVe = inUVvertex;
    outUVB1 = inUVbase_1;
    outUVB2 = inUVbase_2;
    outUVB3 = inUVbase_3;
    translate = inVecModel;
    gl_Position = vec4(0);
}