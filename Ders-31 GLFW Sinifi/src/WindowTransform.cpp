#include "WindowTransform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<iostream>
void WindowTransform::bindAngle(float* angle)
{
    m_Angle = angle;
}
void WindowTransform::bindTransition(glm::vec3* transition)
{
    m_Transition = transition;
}
void WindowTransform::draw()
{
           ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Donusum Penceresi");
        if(ImGui::Button("Tikla!"))
        {
            std::cout<<"Tiklandi!"<<std::endl;
        }
        ImGui::SliderFloat("rotation",m_Angle,0,360);
        ImGui::SliderFloat2("transition",(float*)m_Transition,0,1);
        ImGui::End();   
        ImGui::EndFrame();

        ImGui::Render();
      
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}