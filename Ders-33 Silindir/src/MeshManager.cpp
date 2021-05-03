#include "MeshManager.hpp"
#include "Mesh.hpp"
#include "VertexArrayObject.hpp"
#include<glm/trigonometric.hpp>
#include<iostream>
MeshManager* MeshManager::m_pInstance = nullptr;
MeshManager::MeshManager()
{
    
}
Mesh* MeshManager::createCube()
{
    float length =1.0f;
    Vertex3TexList    vertices;
    IndexList   indices;
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
    m_VaoMap["cubeTex"] = vao;

    Mesh* mesh = new Mesh();
    mesh->m_Vao = vao;
    mesh->m_IndexCount = indices.size();
    mesh->m_VertexCount = vertices.size();

    return mesh;
}
Mesh* MeshManager::createCylinder(  float length,
                                    float radius,
                                    int detail,
                                    const glm::vec4& topColor,
                                    const glm::vec4& surfaceColor)
{
    Vertex3ColorList vertices;
    IndexList indices;
    //parametre çap alıyor yariçapa çeviriyoruz.
    float halfRadius = radius/2.0f;
    //Dairenin noktaları arasındaki açı miktarı hesaplanıyor
    int angleIncrese;
    //Detay miktarına göre noktalar arasındaki açı miktarı hesaplanıyor
    switch(detail)
    {
        case 1:
            angleIncrese=30;
            break;
        case 2:
            angleIncrese = 20;
            break;
        case 3:
            angleIncrese = 10;
            break;
        default:
            angleIncrese= 5;

    }
    //Bir daire için gerekli olan nokta sayısı hesaplanıyor
    int circleVertexCount = 360/angleIncrese;

    //vertex dizisinin boyutu başlangıçta bütün noktaları alacak kadar genişlitiliyor
    //bu sayede noktaları sıra ile eklemek zorunda kalmıyoruz.
    vertices.resize(circleVertexCount*4);

    float renkAzaltma = 0.03;
    // noktalar hesaplanıyor
    for(int i = 0;i<circleVertexCount;i++)
    {
        Vertex3Color vertex;

        //Önceclikle ön yüzdedki dairenin nokta koordinatları hesaplanıyor
        float angle =(float) i*angleIncrese;
        vertex.pos.x = glm::cos(glm::radians(angle))*halfRadius;
        vertex.pos.y = glm::sin(glm::radians(angle))*halfRadius;

        vertex.pos.z = length/2.0f;
        vertex.color = topColor;
        
        vertices[i] = vertex;

        //ön dairenin nokyaları ayrıca ara yüzeydede  kullanacağı için
        //vertex listesi içerisine aynı bir noktaya yerleştiriliyor
        //tabi renk değeri farklı veriliyor
        vertices[i+circleVertexCount*2] =vertex;
        vertices[i+circleVertexCount*2].color = surfaceColor ;

        //Alt yüzeyin koordinatındaki tek fark z eksenindeki konumudur. 
        //buna göre ayarlanıyor ve diziye yerleştiriyor
        vertex.pos.z = -length/2.0f;

        vertices[i+circleVertexCount] = vertex;

        //bir öncekinde olduğu gibi ara yüzeylerin alt koordinatları da diziye yerleştiriliyor
        vertices[i+circleVertexCount*3] = vertex;
        vertices[i+circleVertexCount*3].color = surfaceColor;
    }

    //dairelerin indeks değerleri ayarlanıyor 
    for(int i =0;i<circleVertexCount-2;i++)
    {
        //Ön Yüz 
        indices.push_back(0);
        indices.push_back(i+1);
        indices.push_back(i+2);
        //Arka yüz
        indices.push_back(circleVertexCount);
        indices.push_back(circleVertexCount+i+1);
        indices.push_back(circleVertexCount+i+2);
    }
   
    
    int startIndex = circleVertexCount*2;
    int currentIndex = startIndex;
    //ara yüzler
    for(int i =0;i<circleVertexCount-1;i++)
    {
       
      
        indices.push_back(currentIndex);
        indices.push_back(currentIndex+circleVertexCount);
        indices.push_back(currentIndex+circleVertexCount+1);

        indices.push_back(currentIndex);
        indices.push_back(currentIndex+circleVertexCount+1);
        indices.push_back(currentIndex+1);

         currentIndex++;
    }
    //Son yüzeyde indeks tekrardan başa sardığı için döngü dışına aldık
    indices.push_back(currentIndex);
    indices.push_back(currentIndex+circleVertexCount);
    indices.push_back(currentIndex+1);

    indices.push_back(currentIndex);
    indices.push_back(currentIndex+1);
    indices.push_back(startIndex);    
    
    VertexArrayObject* vao = new VertexArrayObject();
    vao->build(vertices,indices);
 
    Mesh* mesh = new Mesh();
    mesh->m_Vao = vao;
 
    mesh->m_IndexCount = indices.size();
    mesh->m_VertexCount = vertices.size();
   

    return mesh;
}
MeshManager* MeshManager::getInstance()
{
    if(!m_pInstance)
        m_pInstance = new MeshManager();
    
    return m_pInstance;
}