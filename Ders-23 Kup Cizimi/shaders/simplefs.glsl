#version 330 core

out vec4 fragColor;

uniform vec4 uColor;

in vec4 color;

void main()
{
    fragColor = color;
}