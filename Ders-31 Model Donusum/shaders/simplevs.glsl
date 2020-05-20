#version 330 core
layout (location = 0) in vec3 inPosition; 
layout (location = 1) in vec2 inTexCoord; 

uniform mat4 uMtxTransform;

out vec2 texCoord;

void main()
{      
     gl_Position = uMtxTransform*vec4(inPosition, 1.0);
    texCoord = inTexCoord;
}

    