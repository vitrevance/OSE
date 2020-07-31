#version 410 core

out vec4 frag_color;

in vec4 resultPos;

void main() {
    frag_color = resultPos;
}