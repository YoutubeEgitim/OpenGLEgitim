#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include<string>
#include<map>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
   
    void attachShader(const char* fileName,unsigned int shaderType);

    void link();

    void use();

    void addVariable(const std::string& varName);

    void setFloat(const std::string& varName,float value);

private:
    std::string getShaderFromFile(const char* fileName);
    
    std::map<std::string,unsigned int>        m_UniformMap;
    
    unsigned int    m_ProgramId;
  
};


#endif
