#ifndef VertexArrayObjectManager_hpp
#define VertexArrayObjectManager_hpp

#include<vector>

class VertexArrayObject;

class VertexArrayObjectManager
{
public:
    static VertexArrayObjectManager* getInstance();

    void activateVertexArray(unsigned int index);
private:
    VertexArrayObjectManager();
    std::vector<VertexArrayObject*>  m_vaoList;
    static VertexArrayObjectManager* m_Instance;
};

#endif