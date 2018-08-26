#version 330 core
layout (location = 0) in vec3 inPosition; 

  
    uniform float uMoveX;

    void main()
    {      
        gl_Position = vec4(inPosition+vec3(uMoveX,0.0,0.0), 1.0);
    }

    