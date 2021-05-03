#include "MeshManager.hpp"
#include "VertexTypes.hpp"
#include "VertexArrayObject.hpp"
#include "Mesh.hpp"
#include<iostream>
MeshManager* MeshManager::m_Instance = nullptr;

MeshManager::MeshManager()
{

}
Mesh* MeshManager::createCube()
{

    
    if(!m_VaoMap.count("cubeTex"))
    {
        std::vector<Vertex3Tex>     vertices;
        std::vector<unsigned int>   indices;
        float length = 1.0f;
        glm::vec3 v[8];
        v[0] = glm::vec3(-length/2,-length/2,-length/2);
        v[1] = glm::vec3(length/2,-length/2,-length/2);
        v[2] = glm::vec3(length/2,-length/2,length/2);
        v[3] = glm::vec3(-length/2,-length/2,length/2);

        v[4] = glm::vec3(-length/2,length/2,-length/2);
        v[5] = glm::vec3(length/2,length/2,-length/2);
        v[6] = glm::vec3(length/2,length/2,length/2);
        v[7] = glm::vec3(-length/2,length/2,length/2);
        //Ust Yuzey
        Vertex3Tex tempVertices[24];
        tempVertices[0].pos = v[7];
        tempVertices[1].pos = v[3];
        tempVertices[2].pos = v[2];
        tempVertices[3].pos = v[6];
        tempVertices[0].tex = glm::vec2(0.0f,1.0f);
        tempVertices[1].tex = glm::vec2(0.0f,0.0f);
        tempVertices[2].tex = glm::vec2(1.0f,0.0f);
        tempVertices[3].tex = glm::vec2(1.0f,1.0f);
        //Sag Yuzey
        tempVertices[4].pos = v[6];
        tempVertices[5].pos = v[2];
        tempVertices[6].pos = v[1];
        tempVertices[7].pos = v[5];
        tempVertices[4].tex = glm::vec2(0.0f,1.0f);
        tempVertices[5].tex = glm::vec2(0.0f,0.0f);
        tempVertices[6].tex = glm::vec2(1.0f,0.0f);
        tempVertices[7].tex = glm::vec2(1.0f,1.0f);
    //    //Ust Yuzey
        tempVertices[8 ].pos = v[4];
        tempVertices[9 ].pos = v[7];
        tempVertices[10].pos = v[6];
        tempVertices[11].pos = v[5];
        tempVertices[8 ].tex = glm::vec2(0.0f,1.0f);
        tempVertices[9 ].tex = glm::vec2(0.0f,0.0f);
        tempVertices[10].tex = glm::vec2(1.0f,0.0f);
        tempVertices[11].tex = glm::vec2(1.0f,1.0f);

        //Sol Yüzey
        tempVertices[12].pos = v[0];
        tempVertices[13].pos = v[3];
        tempVertices[14].pos = v[2];
        tempVertices[15].pos = v[1];
        tempVertices[12].tex = glm::vec2(0.0f,1.0f);
        tempVertices[13].tex = glm::vec2(0.0f,0.0f);
        tempVertices[14].tex = glm::vec2(1.0f,0.0f);
        tempVertices[15].tex = glm::vec2(1.0f,1.0f);
        //Sag Yuzey
        tempVertices[16].pos = v[4];
        tempVertices[17].pos = v[0];
        tempVertices[18].pos = v[1];
        tempVertices[19].pos = v[5];
        tempVertices[16].tex = glm::vec2(0.0f,1.0f);
        tempVertices[17].tex = glm::vec2(0.0f,0.0f);
        tempVertices[18].tex = glm::vec2(1.0f,0.0f);
        tempVertices[19].tex = glm::vec2(1.0f,1.0f);
    //    //Alt Yuzey
        tempVertices[20].pos = v[7];
        tempVertices[21].pos = v[3];
        tempVertices[22].pos = v[0];
        tempVertices[23].pos = v[4];
        tempVertices[20].tex = glm::vec2(0.0f,1.0f);
        tempVertices[21].tex = glm::vec2(0.0f,0.0f);
        tempVertices[22].tex = glm::vec2(1.0f,0.0f);
        tempVertices[23].tex = glm::vec2(1.0f,1.0f);


        for(int i=0;i<24;i++)
            vertices.push_back(tempVertices[i]);

        for(int i=0;i<6;i++)
        {
            int startIndex = 4*i;
            indices.push_back(startIndex);
            indices.push_back(startIndex+1);
            indices.push_back(startIndex+2);
            
            indices.push_back(startIndex);
            indices.push_back(startIndex+2);
            indices.push_back(startIndex+3);
        }    
   
   

        VertexArrayObject* vao = new VertexArrayObject();
        vao->build(vertices,indices);
        m_VaoMap["cubeTex"]= vao;
    }
    


    Mesh* mesh = new Mesh();
    mesh->m_Vao = m_VaoMap["cubeTex"];
    mesh->m_IndexCount = m_VaoMap["cubeTex"]->getIndexCount();
    mesh->m_VertexCount = m_VaoMap["cubeTex"]->getVertexCount();

    return mesh;
}
MeshManager* MeshManager::getInstance()
{
    if(m_Instance==nullptr)
    {
        m_Instance = new MeshManager();
    }

    return m_Instance;
}