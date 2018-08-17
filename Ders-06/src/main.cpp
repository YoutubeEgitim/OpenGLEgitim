#include <iostream>

#include<glad/glad.h>

#include<GLFW/glfw3.h>



int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800,600,"İLk Programım",NULL,NULL);
    
   
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



    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}