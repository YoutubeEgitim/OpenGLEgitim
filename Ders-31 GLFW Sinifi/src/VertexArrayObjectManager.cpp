#include "VertexArrayObjectManager.hpp"
#include "VertexArrayObject.hpp"

VertexArrayObjectManager::VertexArrayObjectManager()
{

}
void VertexArrayObjectManager::addNewObject(std::string name,VertexArrayObject* vao)
{
    if(!m_VaoMap.count(name))
    {
        m_VaoMap[name] = vao;
    }
}
VertexArrayObject* VertexArrayObjectManager::getVao(std::string name)
{
    if(m_VaoMap.count(name))
    {
        return m_VaoMap[name];
    }
    return nullptr;
}