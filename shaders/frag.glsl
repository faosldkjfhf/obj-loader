#version 410 core

in vec3 v_Pos;
out vec4 fragColor;

void main() {
    fragColor = vec4(v_Pos * 2.0 + 1.0, 1.0);
}
