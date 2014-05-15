#version 430

layout (location = 1) in vec3 position;
layout (location = 2) in vec3 normal;

out vec3 g_normal;

void main()
{
    g_normal = normal;
    gl_Position = vec4(position,1);
}
