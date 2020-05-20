#ifndef VertexTypes_hpp
#define VertexTypes_hpp
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<glm/vec4.hpp>

#include<vector>

class Vertex3Color
{
public:
    glm::vec3 pos;
    glm::vec4 color;
};
class Vertex3Tex
{
public:
    glm::vec3 pos;
    glm::vec2 tex;
};



typedef std::vector<unsigned int>   IndexList;
typedef std::vector<glm::vec3>      PositionList;
typedef std::vector<glm::vec2>      TexCoordList;
typedef std::vector<Vertex3Tex>     Vertex3TexList;
typedef std::vector<Vertex3Color>   Vertex3ColorList;
#endif