#include <iostream>

#include<glad/glad.h>

#include<GLFW/glfw3.h>
//vertex shader kaynak kodu
char* vssource =
"#version 330 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main()                                            \    
 {                                                      \
    gl_Position = vec4(inPosition, 1.0);                \
 }";
//fragment shader kaynak kodu
char* fssource =
"#version 330 core\n                                    \
 out vec4 fragColor;                                    \
 void main()                                            \    
 {                                                      \
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);           \
 }";

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler
unsigned int fragmentShader;
unsigned int vertexShader;
unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;

int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
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

    //vertex shader oluşsturuluyor
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vssource, NULL);
    glCompileShader(vertexShader);
       
    //Fragment Shader Oluşturuluyor
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fssource, NULL);
    glCompileShader(fragmentShader);
    
    //Program nesnesi oluşturuluyor ve shader nesneleri yükleniyor    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

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
        glUseProgram(shaderProgram);
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}