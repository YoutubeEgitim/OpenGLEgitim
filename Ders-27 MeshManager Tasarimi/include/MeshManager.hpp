#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
class Mesh;
class VertexArrayObject;

class MeshManager
{
public:
    static MeshManager* getInstance();
    Mesh*   createCube();
private:
    MeshManager();
    static MeshManager * m_pInstance;
    std::map<std::string,VertexArrayObject*> m_VaoMap;
};


#endif 