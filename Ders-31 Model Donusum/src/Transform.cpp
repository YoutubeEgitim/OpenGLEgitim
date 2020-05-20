#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include<iostream>
Transform::Transform()
{
    m_WorldMatrix = glm::mat4(1);
    m_Position = glm::vec3(0);
}

void Transform::rotateX(float angle)
{
	if (m_AngleX >= 360)
		m_AngleX = 360 - (m_AngleX + angle);
	else
		m_AngleX += angle;
	
    
	update();
}
void Transform::rotateY(float angle)
{
	if (m_AngleY >= 360)
		m_AngleY = 360 - (m_AngleY + angle);
	else
		m_AngleY += angle;

	update();
}
void Transform::rotateZ(float angle)
{
	if (m_AngleZ >= 360)
		m_AngleZ = 360 - (m_AngleZ + angle);
	else
		m_AngleZ += angle;

	update();
}
glm::mat4 Transform::getWorldMatrix() const
{
    return m_WorldMatrix;
}
glm::vec3 Transform::getPosition() const
{
    return m_Position;
}
void Transform::setPosition(const glm::vec3& pos)
{
    m_Position = pos;
    update();
}
void Transform::translate(float x,float y,float z)
{
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;

		update();    
}
void Transform::translate(const glm::vec3& pos)
{
		m_Position += pos;
		update();    
}
void Transform::update()
{
    glm::mat4 mtxRotX,mtxRotY,mtxRotZ;

    mtxRotX = glm::rotate<float>(glm::mat4(1),glm::radians(m_AngleX),glm::vec3(1.0f,0.0f,0.0f));
    mtxRotY = glm::rotate<float>(glm::mat4(1),glm::radians(m_AngleY),glm::vec3(0.0f,1.0f,0.0f));
    mtxRotZ = glm::rotate<float>(glm::mat4(1),glm::radians(m_AngleZ),glm::vec3(0.0f,0.0f,1.0f));

    glm::mat4 mtxRot = mtxRotY*mtxRotX*mtxRotZ;
    glm::mat4 mtxTranslate;

    mtxTranslate = glm::translate<float>(glm::mat4(1),m_Position);


    m_WorldMatrix = mtxTranslate*mtxRot;
}