#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<GLFW/glfw3.h>


#include "shaderprogram.hpp"
#include "square.hpp"
float length = 0.08;
glm::vec3 position = glm::vec3(1.0f,1.0f,0.0f);
glm::vec4 color1 = glm::vec4(1.0f,0.0f,0.0f,1.0f);
glm::vec4 color2 = glm::vec4(1.0f,1.0f,0.0f,1.0f);
glm::vec4 color3 = glm::vec4(1.0f,0.0f,1.0f,1.0f);
//noktalara ait koordinat bilgileri.
float vertices[] = {
    -length/2,  length/2, 0.0f,
    -length/2, -length/2, 0.0f,
     length/2, -length/2, 0.0f,

    -length/2,  length/2, 0.0f,
     length/2, -length/2, 0.0f,  
     length/2,  length/2, 0.0f,
       
}; 

Square sq1(0.0f,0.0f,length);

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler

unsigned int VBO;
unsigned int VAO;




float deger=0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();   
    if(action==GLFW_PRESS)
    {
        if(key==GLFW_KEY_LEFT)  
        {
            sq1.setDirection(Square::DIR_LEFT);
        }
        if(key==GLFW_KEY_RIGHT) 
        {
             sq1.setDirection(Square::DIR_RIGHT);
        }    
        if(key==GLFW_KEY_UP)  
        {
             sq1.setDirection(Square::DIR_UP);
        }
        if(key==GLFW_KEY_DOWN) 
        {
             sq1.setDirection(Square::DIR_DOWN);
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

    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");

    //vertex array object oluşturuluyor
    glGenVertexArrays(1, &VAO); 
    //vertex buffer object oluşuruluyor
    glGenBuffers(1,&VBO);

    //vertex array object aktif edildi.
    glBindVertexArray(VAO);
    //vertex buffer nesnesi aktif edildi.
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //vertex buffer'a nokta bilgileri ytollanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    //gönderilen vertex'e ait özellikler etiketleniyor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //özellik  etiket i aktif ediliyor.
    glEnableVertexAttribArray(0); 

   
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
      
        

        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
         ///1.Kare
        program.setVec3("uMove",sq1.getPosition());
        program.setVec4("uColor",sq1.getColor());
        glDrawArrays(GL_TRIANGLES, 0,6);
        
        sq1.move();

        std::this_thread::sleep_for (std::chrono::milliseconds(70));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}