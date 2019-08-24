#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<vector>
#include<cmath>
#include<glm/gtx/matrix_transform_2d.hpp>
#include "shaderprogram.hpp"
#include "square.hpp"

std::vector<glm::vec3>      vertices;
std::vector<unsigned int>   indices;

float angle;
glm::vec2 position;
float scale;


unsigned int VBO;
unsigned int VAO;
unsigned int EBO;   //index buffer'ın id değerini tutacak

//dairenin koordinatları ve index değerlerini hesaplıyan fonksiyon.
//ilk parametre yarıçap ikinci parametre dairenin detay değerini belirtmektedir.
void buildCircle(float radius,int detailValue)
{
    if(detailValue<=0)
        detailValue = 1;

    int vertexCount = 4*detailValue;
    int triCount    = vertexCount-2;
    float angle     = 360.0f/vertexCount;

    //koordinat bilgileri hesaplanıyor
    for(int i=0;i<vertexCount;i++)
    {
        glm::vec3 nextPos;
        float nextAngle = angle*i;
        nextPos.x = radius*glm::cos(glm::radians(nextAngle));
        nextPos.y = radius*glm::sin(glm::radians(nextAngle));
        nextPos.z = 1.0f;
        vertices.push_back(nextPos);

        
    }

    //index değerleri hesaplanıyor
    for(int i =0;i<triCount;i++)
    {
        int index = i;

        indices.push_back(0);
        indices.push_back(index+1);
        indices.push_back(index+2);
        
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
    buildCircle(0.2,2);
    
    glm::mat3 mtxTransform(1);

    angle=0.0f;
    position = glm::vec2(0.0f,0.0f);
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
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    
    glEnableVertexAttribArray(0); 
    
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 
   
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat3 mtxRotatiton = glm::rotate(glm::mat3(1),glm::radians(angle));
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1),position);
        glm::mat3 mtxScale =glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform = mtxTranslation*mtxRotatiton*mtxScale;

        angle+=1.0f;
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
  
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
         ///1.Kare
        
        program.setVec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat3("uMtxTransform",&mtxTransform);
        
        //daire index buffer kullanılarak kopyalanıyor.
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        std::this_thread::sleep_for (std::chrono::milliseconds(70));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}