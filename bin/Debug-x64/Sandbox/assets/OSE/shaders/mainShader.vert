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
    vec4 transPos = inMatModel * inPos;

    //mat4 wProj;
    //wProj[0][0] = 1 / (uFWProjection - transPos.w);
    //wProj[1][1] = wProj[0][0];
    //wProj[2][2] = wProj[0][0];
    //vec3 projPos = (wProj * transPos).xyz;
    vec3 projPos = transPos.xyz;
    resultPos = projPos;
    resultNorm = mat3(inMatModel) * inNorm.xyz;
    gl_Position = uMatProjection * inverse(uMatView) * vec4(projPos, transPos.w - uFWProjection);
}