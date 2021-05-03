#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
#include<glm/vec4.hpp>
class Mesh;
class VertexArrayObject;

class MeshManager
{
public:
    static MeshManager* getInstance();
    Mesh*   createCube();
    Mesh*   createCylinder(float length,float radius,int detail=1,
                           const glm::vec4& topColor=glm::vec4(1.0f,0.0f,0.0f,1.0),
                           const glm::vec4& surfaceColor=glm::vec4(0.0f,1.0f,0.0f,1.0));
private:
    MeshManager();
    static MeshManager * m_pInstance;
    std::map<std::string,VertexArrayObject*> m_VaoMap;
};


#endif 