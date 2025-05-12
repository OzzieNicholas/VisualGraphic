// tri_mesh.vert
// ������ɫ����֧��λ�á����ߡ���ɫ���ԣ�Ӧ�� MVP �任

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
