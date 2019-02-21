#include "TextureManager.hpp"
#include<glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
TextureManager* TextureManager::m_Instance(0);

TextureManager::TextureManager()
{
    initialize();
}
void TextureManager::initialize()
{

}
void TextureManager::activateTexture(std::string fileName)
{
    if(m_TextureMap.count(fileName)!=0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureMap[fileName]);
    }
}
unsigned int TextureManager::loadTexture(std::string fileName)
{
    
    unsigned int id = -1;
    if(m_TextureMap.count(fileName)!=0)
    {
        id = m_TextureMap[fileName];
    }
    else
    {
        int width, height, nrChannels;
        
        unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0); 
      
        unsigned int textureId;
        
        glGenTextures(1, &textureId);  
        
        glBindTexture(GL_TEXTURE_2D, textureId);  
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_TextureMap[fileName] = textureId;

        id= textureId;
        stbi_image_free(data);

    }
    
    return id;



}
TextureManager* TextureManager::getInstance()
{
    if(!m_Instance)
        m_Instance = new TextureManager();

    return m_Instance;
}