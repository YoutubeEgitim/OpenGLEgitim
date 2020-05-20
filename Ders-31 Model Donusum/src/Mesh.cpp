#include "Mesh.hpp"
#include "VertexArrayObject.hpp"
#include <glad/glad.h>
Mesh::Mesh(unsigned int primitiveType)
{
    m_PrimitiveType = primitiveType;
}
void Mesh::draw()
{

    m_Vao->activate();
    glDrawElements(m_PrimitiveType, m_IndexCount, GL_UNSIGNED_INT, 0);
    m_Vao->deactivate();
}