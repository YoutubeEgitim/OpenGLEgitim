#include "OpenGLManager.hpp"
#include "Timer.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>

OpenGLManager::OpenGLManager()
{

    m_FrameTime = 0.0;
    m_Timer = new Timer();
    m_Window = nullptr;   
}
GLFWwindow* OpenGLManager::getWindowPtr()
{
    return m_Window;
}
void OpenGLManager::setFPS(int frameCount)
{
    m_Fps =(frameCount);
    m_FrameTime = 1/static_cast<double>(m_Fps);
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
    glfwSwapInterval(0);
    
    double passedTime = 0.0;
    m_Timer->start();
    while(!glfwWindowShouldClose(m_Window))
    {

        if(passedTime>=m_FrameTime)
        {
            glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        


            for(auto& nextFunction:m_RenderFunctions)
                nextFunction();


            glfwSwapBuffers(m_Window);

            glfwPollEvents();

            passedTime=0.0;
        }
        else
        {
            passedTime+=m_Timer->elapsedSeconds();
        }
        //oluşturulacak resim başlangıç rengine boyanıyor

       
    }
}