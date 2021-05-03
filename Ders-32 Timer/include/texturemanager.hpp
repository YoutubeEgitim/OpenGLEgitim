#ifndef TextureManager_hpp
#define TextureManager_hpp
#include<string>
#include<map>
class TextureManager
{
public:
   TextureManager();

    unsigned int loadTexture(std::string fileName);

    void activateTexture(unsigned int level,unsigned int id);
    
private:
 

    std::map<std::string,unsigned int>  m_TextureMap;

};
#endif