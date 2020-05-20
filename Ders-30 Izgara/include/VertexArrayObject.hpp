#ifndef VertexArrayObject_hpp
#define VertexArrayObject_hpp
#include "VertexTypes.hpp"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void build( const Vertex3TexList& vertices,
                const IndexList& indices
                );
    void build(const Vertex3ColorList& vertices,
                const IndexList& indices);
    void activate();
    void deactivate();
private:
    unsigned int m_VboId;
    unsigned int m_IboId;
    unsigned int m_VaoId;
    std::vector<unsigned int> m_AttribList;
};

#endif
