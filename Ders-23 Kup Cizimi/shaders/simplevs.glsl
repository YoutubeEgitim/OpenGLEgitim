#version 330 core
layout (location = 0) in vec3 inPosition; 
layout (location = 1) in vec4 inColor; 

uniform mat4 uMtxTransform;

out vec4 color;

void main()
{      
     gl_Position = uMtxTransform*vec4(inPosition, 1.0);
    color = inColor;
}

    