#ifndef Scene_hpp
#define Scene_hpp

class MeshManager;
class TextureManager;
class VertexArrayObjectManager;
class WindowTransform;
class GLFWwindow;
class Scene
{
public:
    Scene();

    void build(GLFWwindow* window);
    void draw();

    MeshManager*    getMeshManager();
    TextureManager* getTextureManager();
    VertexArrayObjectManager* getVaoManager();
    WindowTransform* getWindowTransform();
private:
    MeshManager*                m_MeshManager;
    TextureManager*             m_TextureManager;
    VertexArrayObjectManager*   m_VaoManager;
    WindowTransform*            m_WindowTransform;
};
#endif