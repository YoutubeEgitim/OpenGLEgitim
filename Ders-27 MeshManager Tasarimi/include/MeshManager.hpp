#ifndef MeshManager_hpp
#define MeshManager_hpp

class Mesh;

class MeshManager
{
public:
    static MeshManager* getInstance();

    Mesh* createCube();
private:
    static MeshManager* m_Instance;
    MeshManager();
};
#endif