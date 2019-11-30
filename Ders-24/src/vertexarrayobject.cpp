#include "vertexarrayobject.hpp"
VertexArrayObject::VertexArrayObject()
{
    m_IboId = -1;
    m_VaoId = -1;
    m_VboId = -1;
}
void VertexArrayObject::activate()
{

}
void VertexArrayObject::deactivate()
{
    
}
unsigned int VertexArrayObject::getId()const
{
    return m_VaoId;
}

unsigned int VertexArrayObject::getIndexBufferId() const
{
    return m_IboId;
}

unsigned int VertexArrayObject::getVertexBufferId()const
{
    return m_VaoId;
}