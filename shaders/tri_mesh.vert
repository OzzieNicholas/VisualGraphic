// tri_mesh.vert
// 顶点着色器，支持位置、法线、颜色属性，应用 MVP 变换

#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

uniform mat4 mvp;

out vec3 fragColor;

void main() {
    gl_Position = mvp * vec4(inPosition, 1.0);
    fragColor = inColor;
}
