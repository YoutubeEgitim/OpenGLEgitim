#ifndef Mesh_hpp
#define Mesh_hpp
#include <glm/mat4x4.hpp>
class VertexArrayObject;
class MeshManager;

class Mesh
{
public:
    void draw();
private:

    glm::mat4   m_MtxWorld;

    VertexArrayObject* m_Vao;

    unsigned int m_VertexCount;
    unsigned int m_IndexCount;

    friend MeshManager;
};

#endif