#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include<string>
#include<map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
   
    void attachShader(const char* fileName,unsigned int shaderType);

    void link();

    void use();

    void addUniform(const std::string& varName );

    void setFloat(const std::string& varName,float value);
 
    void setVec3(const std::string& varName,const glm::vec3& value);

    void setVec4(const std::string& varName,const glm::vec4& value);

    void setMat4(const std::string& varName,const glm::mat4* mtx);
private:
    std::string getShaderFromFile(const char* fileName);
    
    std::map<std::string,unsigned int>  m_UniformVars;

    unsigned int    m_ProgramId;
  
};


#endif
