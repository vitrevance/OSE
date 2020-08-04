#version 410 core

out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

uniform mat4 uLights[20];
uniform int uNumLights;

vec3 calcDirectionalLight(int i) {
    vec3 lightDir = normalize(mat3(uLights[i]) * vec3(0, 0, 1));
    return vec3(uLights[i][0][3], uLights[i][1][3], uLights[i][2][3]) * max( -dot(resultNorm, lightDir), 0 );
}
vec3 calcPointLight(int i) {
    vec3 lightPos = vec3(uLights[i][0][0], uLights[i][0][1], uLights[i][0][2]);
    vec3 lightDir = normalize(resultPos - lightPos);
    return vec3(uLights[i][0][3], uLights[i][1][3], uLights[i][2][3]) * max( -dot(resultNorm, lightDir), 0 );
}

vec3 calcAmbientLight(int i) {
    return vec3(uLights[i][0][3], uLights[i][1][3], uLights[i][2][3]);
}

void main() {
    vec3 matColor = vec3(1);
    vec3 lightColor = vec3(0);
    vec3 ambientLight = vec3(0);
    int numLights = uNumLights;
    for (int i = 0; i < uNumLights; i++) {
        switch (int(uLights[i][3][3])) {
            case 0:
            lightColor += calcPointLight(i);
            break;
            case 1:
            lightColor += calcDirectionalLight(i);
            break;
            case 2:
            ambientLight += calcAmbientLight(i);
            numLights--;
            break;
        }
    }
    lightColor /= numLights;
    lightColor += ambientLight;
    frag_color = vec4(matColor * lightColor, 1);
}