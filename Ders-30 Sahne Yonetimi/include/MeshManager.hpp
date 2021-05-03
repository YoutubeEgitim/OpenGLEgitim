#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
class Mesh;
class VertexArrayObjectManager;



class MeshManager
{
public:
    MeshManager(VertexArrayObjectManager* vaoManager);
    Mesh* createCube();
private:

    VertexArrayObjectManager* m_VaoManager;
};
#endif