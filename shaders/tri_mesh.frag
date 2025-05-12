// tri_mesh.frag
// 片元着色器，使用顶点插值颜色进行填色

#version 460 core

in vec3 fragColor;
out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}
