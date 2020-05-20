#ifndef Transform_hpp
#define Transform_hpp

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
class Transform
{
public:
    Transform();
    void	    rotateX(float angle);
    void	    rotateY(float angle);
    void	    rotateZ(float angle);
    void        translate(float x,float y,float z);
    void        translate(const glm::vec3& pos);
    void        setPosition(const glm::vec3& pos);

    glm::vec3   getPosition()       const;
    glm::mat4   getWorldMatrix()    const;
private:
    void    update();
    
    
    float m_AngleX;
    float m_AngleY;
    float m_AngleZ;
    glm::vec3   m_Position;
    glm::mat4   m_WorldMatrix;

};

#endif