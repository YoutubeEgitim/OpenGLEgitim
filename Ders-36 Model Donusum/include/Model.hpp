#ifndef Model_hpp
#define Model_hpp

class Mesh;
class Transform;

class Model
{
public:
    Model();
    Transform*  m_Transform;
    Mesh*       m_Mesh;
};

#endif