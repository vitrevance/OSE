#version 410 core

layout (location = 0) in vec4 inPos;
layout (location = 1) in vec4 inNorm;
layout (location = 2) in mat4 inMatModel;

uniform mat4 uMatView;
uniform mat4 uMatProjection;
uniform float uFWProjection;

out vec3 resultPos;
out vec3 resultNorm;

void main() {
    mat4 matView = inverse(uMatView);
    mat4 mat4DProj;
    vec4 pIn4D = vec4(inPos.xyz, 1);
    mat4DProj[0][0] = 1;
    mat4DProj[1][1] = 1;
    mat4DProj[2][2] = (inPos.w + uFWProjection) / (inPos.w - uFWProjection);
    mat4DProj[3][2] = -inPos.w * uFWProjection / (inPos.w - uFWProjection);
    mat4DProj[2][3] = 1;

    vec4 pOut3D = mat4DProj * inMatModel * pIn4D;
    pOut3D = vec4(pOut3D.xyz, 1);;
    pOut3D = uMatProjection * matView * pOut3D;
    gl_Position = pOut3D;
}