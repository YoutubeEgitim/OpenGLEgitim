#include "VertexArrayObjectManager.hpp"
#include "vertexarrayobject.hpp"
VertexArrayObjectManager::VertexArrayObjectManager()
{

}
void VertexArrayObjectManager::activateVertexArray(unsigned int index)
{
    if(index<m_vaoList.size())
    {
        
    }
}
VertexArrayObjectManager* VertexArrayObjectManager::getInstance()
{
    if(!m_Instance)
        m_Instance = new VertexArrayObjectManager();

    return m_Instance;
}