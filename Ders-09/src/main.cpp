#include <iostream>

#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include "shaderprogram.hpp"


//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.6f, -0.6f, 0.0f,
     0.6f, -0.6f, 0.0f,
     0.0f,  0.6f, 0.0f,
     0.0f,  0.6f, 0.0f,   
    -0.8f,  0.9f, 0.0f,
     0.8f,  0.9f, 0.0f
}; 

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler

unsigned int VBO;
unsigned int VAO;
float x =0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();

    if(key==GLFW_KEY_LEFT)
    {
        x-=0.01;
    }
    if(key==GLFW_KEY_RIGHT)
    {
        x+=0.01;
    }
}
int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800,600,"İLk Programım",NULL,NULL);
    glfwSetKeyCallback(window, key_callback);
    
    if(window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;

        glfwTerminate();

        return -1;
    }    

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
    program.addVariable("uMoveX");
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
        program.setFloat("uMoveX",x);
        
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawArrays(GL_TRIANGLES, 0,6);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}