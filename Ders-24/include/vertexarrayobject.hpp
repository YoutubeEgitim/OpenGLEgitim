#ifndef VertexArrayObject_h
#define VertexArrayObject_h
#include<vector>
class VertexArrayObject
{
public:
    VertexArrayObject();

    void activate();
    void deactivate();
    unsigned int getId()    const;
    unsigned int getVertexBufferId()    const;
    unsigned int getIndexBufferId()     const;
private:
    unsigned int m_VaoId;
    unsigned int m_VboId;
    unsigned int m_IboId;
};

#endif