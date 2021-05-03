#ifndef TextureManager_hpp
#define TextureManager_hpp
#include<string>
#include<map>
class TextureManager
{
public:
    static TextureManager* getInstance();

    unsigned int loadTexture(std::string fileName);

    void activateTexture(unsigned int level,unsigned int id);
    
private:
    TextureManager();


    std::map<std::string,unsigned int>  m_TextureMap;

    static TextureManager* m_Instance;
};
#endif