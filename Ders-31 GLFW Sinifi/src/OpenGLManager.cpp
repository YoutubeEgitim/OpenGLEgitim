#include "OpenGLManager.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>

OpenGLManager::OpenGLManager()
{

    m_Window = nullptr;   
}
GLFWwindow* OpenGLManager::getWindowPtr()
{
    return m_Window;
}
bool OpenGLManager::build(int width,int height)
{
    if(!glfwInit())
        return 0;
    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    

    m_Window = glfwCreateWindow(width,height,"İLk Programım",NULL,NULL);

    if(m_Window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;

        glfwTerminate();

        return false;
    }  

    glfwSetWindowUserPointer(m_Window,this);
    glfwSetKeyCallback(m_Window, OpenGLManager::key_callback);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    } 
    return true;
}

void OpenGLManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    OpenGLManager* manager=static_cast<OpenGLManager*> (glfwGetWindowUserPointer(window));
    
    for(auto& siradaki:manager->m_KeyboardFunctions)
        siradaki(window,key,scancode,action,mods);
    
}

void OpenGLManager::addRenderFunction(RenderFunction function)
{
    m_RenderFunctions.push_back(function);
}

void OpenGLManager::addKeyboardFunction(KeyboardFunction function)
{
    m_KeyboardFunctions.push_back(function);
}
void OpenGLManager::beginRenderLoop()
{
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(m_Window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       


        for(auto& nextFunction:m_RenderFunctions)
            nextFunction();


        glfwSwapBuffers(m_Window);

        glfwPollEvents();
       
    }
}