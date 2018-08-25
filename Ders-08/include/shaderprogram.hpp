#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include<string>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
   
    void attachShader(const char* fileName,unsigned int shaderType);

    void link();

    void use();
private:
    std::string getShaderFromFile(const char* fileName);
    
    
    
    
    unsigned int m_ProgramId;
  
};


#endif
