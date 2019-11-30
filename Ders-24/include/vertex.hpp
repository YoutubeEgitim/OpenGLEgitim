#ifndef vertex_hpp
#define vertex_hpp
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<vector>
struct Vertex3
{
    glm::vec3 pos;
    glm::vec2 tex;
};

typedef std::vector<Vertex3> VertexList; 
typedef std::vector<unsigned int> IndexList;

#endif