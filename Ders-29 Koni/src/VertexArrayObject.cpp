#include "VertexArrayObject.hpp"
#include<glad/glad.h>
VertexArrayObject::VertexArrayObject()
{
    m_VboId =  0;
    m_IboId =  0;
    m_VaoId =  0;
}
VertexArrayObject::~VertexArrayObject()
{
    if(m_VboId)
        glDeleteBuffers(1,&m_VboId);
    if(m_VaoId)
        glDeleteBuffers(1,&m_VaoId);
    if(m_IboId) 
        glDeleteBuffers(1,&m_IboId);
}
void VertexArrayObject::build(  const Vertex3TexList& vertices,
                                const IndexList& indices
                            )
{
    glGenVertexArrays(1, &m_VaoId); 

    glGenBuffers(1,&m_VboId);

    glGenBuffers(1, &m_IboId);
   
    glBindVertexArray(m_VaoId);
    
    glBindBuffer(GL_ARRAY_BUFFER,m_VaoId);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3Tex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
       
    glEnableVertexAttribArray(0); 
    //kaplama bilgileri belirtiliyor.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);    
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 

    m_AttribList.push_back(0);
    m_AttribList.push_back(1);
}
void VertexArrayObject::build(  const Vertex3ColorList& vertices,
                                const IndexList& indices)
{
    glGenVertexArrays(1, &m_VaoId); 

    glGenBuffers(1,&m_VboId);

    glGenBuffers(1, &m_IboId);
   
    glBindVertexArray(m_VaoId);
    
    glBindBuffer(GL_ARRAY_BUFFER,m_VaoId);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3Color)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
       
    glEnableVertexAttribArray(0); 
    //kaplama bilgileri belirtiliyor.
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);    
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 

    m_AttribList.push_back(0);
    m_AttribList.push_back(1);
}
void VertexArrayObject::activate()
{
    for(auto siradaki:m_AttribList )
        glEnableVertexAttribArray(siradaki);
}
void VertexArrayObject::deactivate()
{
    for(auto siradaki:m_AttribList )
        glDisableVertexAttribArray(siradaki);
}