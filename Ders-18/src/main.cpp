#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<vector>
#include<cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.hpp"
#include "square.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Vertex
{
    glm::vec3   pos;
    glm::vec2   tex;
};

std::vector<Vertex>         vertices;
std::vector<unsigned int>   indices;

glm::mat4   matTransform;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;   //index buffer'ın id değerini tutacak



void buildSquare(float length)
{
    Vertex v0,v1,v2,v3;
    v0.pos = glm::vec3(-length/2,length/2,0.0f);
    v1.pos = glm::vec3(-length/2,-length/2,0.0f);
    v2.pos = glm::vec3(length/2,-length/2,0.0f);
    v3.pos = glm::vec3(length/2,length/2,0.0f);

    v0.tex = glm::vec2(0.0f,1.0f);
    v1.tex = glm::vec2(0.0f,0.0f);
    v2.tex = glm::vec2(1.0f,0.0f);
    v3.tex = glm::vec2(1.0f,1.0f);

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);


    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();   
    if(action==GLFW_PRESS)
    {
       
        {
            
            if(key==GLFW_KEY_LEFT)  
            {
               
            }
            if(key==GLFW_KEY_RIGHT) 
            {
                
            }    
            if(key==GLFW_KEY_UP)  
            {
                
            }
            if(key==GLFW_KEY_DOWN) 
            {
                
            }                
        }
        
        if(key==GLFW_KEY_SPACE)
        {

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
    buildSquare(1);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./images/container.jpg", &width, &height, &nrChannels, 0); 

    std::cout<<width<<","<<height<<std::endl;
   
    unsigned int texture;
    
    glGenTextures(1, &texture);  
    
    glBindTexture(GL_TEXTURE_2D, texture);  
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    stbi_image_free(data);
    
    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");
    program.addUniform("uTransform");
   
    matTransform = glm::mat4(1.0f);

    matTransform = glm::rotate(matTransform,glm::radians(5.0f), glm::vec3(0.0f,0.0f,1.0f));

    glGenVertexArrays(1, &VAO); 

    glGenBuffers(1,&VBO);

    glGenBuffers(1, &EBO);
   
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
     
    glEnableVertexAttribArray(0); 
   
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 3 * sizeof(float)));
       
    glEnableVertexAttribArray(1);   
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 
   
    float aci = 1.0f;
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
         ///1.Kare
        program.setVec3("uMove",glm::vec3(0.0f,0.0f,0.0f));
        program.setVec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat4("uTransform",&matTransform);
        //daire index buffer kullanılarak kopyalanıyor.
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        std::this_thread::sleep_for (std::chrono::milliseconds(70));
    
        glm::mat4 matRotation   = glm::rotate(glm::mat4(1),glm::radians(aci), glm::vec3(0.0f,0.0f,1.0f));
        glm::mat4 matTranslate  = glm::translate(glm::mat4(1),glm::vec3(0.3,0.3,0.3));

        matTransform = matTranslate*matRotation;

        aci++;
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}