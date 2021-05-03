#ifndef VertexArrayObjectManager_hpp
#define VertexArrayObjectManager_hpp
#include<map>
class VertexArrayObject;
class VertexArrayObjectManager
{
public:
    VertexArrayObjectManager();
    void addNewObject(std::string name, VertexArrayObject* vao);
    VertexArrayObject* getVao(std::string name);
private:
    std::map<std::string,VertexArrayObject* > m_VaoMap;
};


#endif