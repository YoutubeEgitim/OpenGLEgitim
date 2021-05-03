#ifndef Mesh_hpp
#define Mesh_hpp

class VertexArrayObject;
class MeshManager;
class Mesh
{
public:
    void draw();
private:
    VertexArrayObject*  m_Vao;
    unsigned int m_IndexCount;
    unsigned int m_VertexCount;
    friend MeshManager;
};

#endif