#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<vector>
#include<cmath>
#include<glm/gtc/matrix_transform.hpp>
#include "shaderprogram.hpp"
#include "square.hpp"
#include "texturemanager.hpp"
#include "MeshManager.hpp"
#include "Mesh.hpp"

Mesh* mesh;

float angle;
glm::vec3 position;
float scale;

unsigned int texture;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();   
    if(action==GLFW_PRESS)
    {
       
        
        
        if(key==GLFW_KEY_LEFT)  
        {
           position.x-=0.01;
        }
        if(key==GLFW_KEY_RIGHT) 
        {
            position.x+=0.01;
        }    
        if(key==GLFW_KEY_UP)  
        {
            position.y+=0.01;
        }
        if(key==GLFW_KEY_DOWN) 
        {
            position.y-=0.01;
        }                
        
        
        if(key==GLFW_KEY_Q)
        {
            scale-=0.1;
        }    
           
        if(key==GLFW_KEY_W)
        {
            scale+=0.1;
        }            
    }  
           
}

int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;
    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800,800,"İLk Programım",NULL,NULL);

    if(window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;

        glfwTerminate();

        return -1;
    }    
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 
    
    //**********daire oluşturuluyor**************///////
    //Küp Oluşturuluyor
    mesh = MeshManager::getInstance()->createCone(3,2);

   
    glm::mat4 mtxTransform(1);

    angle=0.0f;
    position = glm::vec3(0.0f,0.0f,0.0f);
    scale = 1.0f;
    


 
    ShaderProgram program;

    program.attachShader("./shaders/colorvs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/colorfs.glsl",GL_FRAGMENT_SHADER);
    program.link();

   
    program.addUniform("uMtxTransform");
   
 
    glm::vec3 camPosition(2.0f,2.0f,2.0f);
    glm::vec3 camLookAt(0.0f,0.0f,0.0f);
    glm::vec3 camUp(0.0f,1.0f,0.0f);

    glm::mat4 mtxCam = glm::lookAt(camPosition,camLookAt,camUp);
    glm::mat4 mtxProj = glm::perspective(glm::radians(90.0f),(800.0f/800.0f),1.0f,100.0f);



    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        
        glm::mat4 mtxRotation = glm::rotate(glm::mat4(1),glm::radians(angle),glm::vec3(0.0,1.0f,0.0f));
       
 
        mtxTransform = mtxProj*mtxCam*mtxRotation;

        angle+=1.0f;
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
       
        program.setMat4("uMtxTransform",&mtxTransform);
        
        //daire index buffer kullanılarak kopyalanıyor.
        mesh->draw();
        
        std::this_thread::sleep_for (std::chrono::milliseconds(70));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}