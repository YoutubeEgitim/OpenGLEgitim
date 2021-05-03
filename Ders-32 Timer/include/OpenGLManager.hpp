#ifndef OpenGLManager_hpp
#define OpenGLManager_hpp
#include <functional>
#include <vector>
class GLFWwindow;
class Timer;
typedef std::function<void()> RenderFunction;
typedef std::vector<RenderFunction> RenderFunctionList;

typedef std::function<void (GLFWwindow*,int,int,int,int)> KeyboardFunction;
typedef std::vector<KeyboardFunction> KeyboardFunctionList;


class OpenGLManager
{
public:
    OpenGLManager();
    bool build(int width,int height);
    void beginRenderLoop();

    void addRenderFunction(RenderFunction function);
    void addKeyboardFunction(KeyboardFunction function);

    void setFPS(int frameCount);
    
    GLFWwindow* getWindowPtr();
    
 
private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    Timer*                  m_Timer;
    RenderFunctionList      m_RenderFunctions;
    KeyboardFunctionList    m_KeyboardFunctions;
    GLFWwindow*             m_Window;
    double                  m_FrameTime;
    int                     m_Fps;
};

#endif