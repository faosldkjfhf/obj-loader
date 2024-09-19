#version 410 core

layout(location = 0) in vec3 pos;
out vec3 v_Pos;

void main() {
    v_Pos = vec3(pos);
    gl_Position = vec4(pos, 1.0);
}
