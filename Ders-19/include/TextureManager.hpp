#ifndef TextureManager_hpp
#define TextureManager_hpp
#include <map>
#include<string>
class TextureManager
{
public:
    static TextureManager* getInstance();

    unsigned int loadTexture(std::string fileName);
private:
            TextureManager();
    void    initialize();

    static TextureManager* m_Instance;

    std::map<std::string,unsigned int>  m_TextureMap;

};

#endif