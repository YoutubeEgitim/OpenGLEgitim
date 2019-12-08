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


struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texCoord;
};



std::vector<Vertex>      vertices;
std::vector<unsigned int>   indices;

float angle;
glm::vec3 position;
float scale;


unsigned int VBO;
unsigned int VAO;
unsigned int EBO;   //index buffer'ın id değerini tutacak
unsigned int texture;


void buildSquare(float length)
{
    glm::vec3 v[8];
    v[0] = glm::vec3(-length/2,-length/2,-length/2);
    v[1] = glm::vec3(length/2,-length/2,-length/2);
    v[2] = glm::vec3(length/2,-length/2,length/2);
    v[3] = glm::vec3(-length/2,-length/2,length/2);

    v[4] = glm::vec3(-length/2,length/2,-length/2);
    v[5] = glm::vec3(length/2,length/2,-length/2);
    v[6] = glm::vec3(length/2,length/2,length/2);
    v[7] = glm::vec3(-length/2,length/2,length/2);
    //Ust Yuzey

    Vertex tempVertices[24];
    tempVertices[0].pos = v[7];
    tempVertices[1].pos = v[3];
    tempVertices[2].pos = v[2];
    tempVertices[3].pos = v[6];
    tempVertices[0].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[1].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[2].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[3].texCoord = glm::vec2(1.0f,1.0f);
    //Sag Yuzey
    tempVertices[4].pos = v[6];
    tempVertices[5].pos = v[2];
    tempVertices[6].pos = v[1];
    tempVertices[7].pos = v[5];
    tempVertices[4].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[5].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[6].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[7].texCoord = glm::vec2(1.0f,1.0f);
//    //Ust Yuzey
    tempVertices[8 ].pos = v[4];
    tempVertices[9 ].pos = v[7];
    tempVertices[10].pos = v[6];
    tempVertices[11].pos = v[5];
    tempVertices[8 ].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[9 ].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[10].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[11].texCoord = glm::vec2(1.0f,1.0f);

    //Sol Yüzey
    tempVertices[12].pos = v[0];
    tempVertices[13].pos = v[3];
    tempVertices[14].pos = v[2];
    tempVertices[15].pos = v[1];
    tempVertices[12].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[13].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[14].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[15].texCoord = glm::vec2(1.0f,1.0f);
    //Sag Yuzey
    tempVertices[16].pos = v[4];
    tempVertices[17].pos = v[0];
    tempVertices[18].pos = v[1];
    tempVertices[19].pos = v[5];
    tempVertices[16].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[17].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[18].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[19].texCoord = glm::vec2(1.0f,1.0f);
//    //Alt Yuzey
    tempVertices[20].pos = v[7];
    tempVertices[21].pos = v[3];
    tempVertices[22].pos = v[0];
    tempVertices[23].pos = v[4];
    tempVertices[20].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[21].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[22].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[23].texCoord = glm::vec2(1.0f,1.0f);


    for(int i=0;i<24;i++)
        vertices.push_back(tempVertices[i]);

    for(int i=0;i<6;i++)
    {
        int startIndex = 4*i;
        indices.push_back(startIndex);
        indices.push_back(startIndex+1);
        indices.push_back(startIndex+2);
        
        indices.push_back(startIndex);
        indices.push_back(startIndex+2);
        indices.push_back(startIndex+3);
    }
   
}



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
    buildSquare(1);
    
    texture = TextureManager::getInstance()->loadTexture("./images/container.jpg");


    glm::mat4 mtxTransform(1);

    angle=0.0f;
    position = glm::vec3(0.0f,0.0f,0.0f);
    scale = 1.0f;
    


 
    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

   
    program.addUniform("uColor");
    program.addUniform("uMtxTransform");
   
    glGenVertexArrays(1, &VAO); 

    glGenBuffers(1,&VBO);

    glGenBuffers(1, &EBO);
   
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
       
    glEnableVertexAttribArray(0); 
    //kaplama bilgileri belirtiliyor.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);    
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 
   
   
 
    glm::vec3 camPosition(0.0f,0.0f,2.0f);
    glm::vec3 camLookAt(0.0f,0.0f,0.0f);
    glm::vec3 camUp(0.0f,1.0f,0.0f);

    glm::mat4 mtxCam = glm::lookAt(camPosition,camLookAt,camUp);
    glm::mat4 mtxProj = glm::perspective(glm::radians(90.0f),(800.0f/800.0f),1.0f,100.0f);


    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glm::mat4 mtxRotation = glm::rotate(glm::mat4(1),glm::radians(angle),glm::vec3(1.0,0.0f,1.0f));
       
 
        mtxTransform = mtxProj*mtxCam*mtxRotation;

        angle+=1.0f;
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
       
        //kaplama Aktif Ediliyor.
        TextureManager::getInstance()->activateTexture(GL_TEXTURE0,texture);
        
        
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
         ///1.Kare
        
        program.setVec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat4("uMtxTransform",&mtxTransform);
        
        //daire index buffer kullanılarak kopyalanıyor.
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        std::this_thread::sleep_for (std::chrono::milliseconds(70));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}