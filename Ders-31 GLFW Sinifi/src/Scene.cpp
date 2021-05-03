#include "Scene.hpp"
#include "VertexArrayObjectManager.hpp"
#include "MeshManager.hpp"
#include "texturemanager.hpp"
#include "WindowTransform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
Scene::Scene()
{
    m_VaoManager = new VertexArrayObjectManager();
    m_MeshManager = new MeshManager(m_VaoManager);
    m_TextureManager = new TextureManager();
    m_WindowTransform = new WindowTransform();
}
WindowTransform* Scene::getWindowTransform()
{
    return m_WindowTransform;
}
void Scene::build(GLFWwindow* window)
{
     IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();   
}
void Scene::draw()
{
    m_WindowTransform->draw();
}
MeshManager* Scene::getMeshManager()
{
    return m_MeshManager;
}
TextureManager* Scene::getTextureManager()
{
    return m_TextureManager;
}
VertexArrayObjectManager* Scene::getVaoManager()
{
    return m_VaoManager;
}