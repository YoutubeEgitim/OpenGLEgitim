#include "Mesh.hpp"
#include "VertexArrayObject.hpp"
#include<glad/glad.h>

void Mesh::draw()
{
    m_Vao->activate();

    glDrawElements(GL_TRIANGLES,m_IndexCount,GL_UNSIGNED_INT,0);

    m_Vao->deactivate();
}