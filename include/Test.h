#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <vector>
#include <functional>
#include <iostream>
#include <array>


namespace test
{
static float m_PI  = 3.1415926535897932384626433832795028842;

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoordinates;
    glm::vec3 normal;
    glm::vec3 color;
    bool enabled;
};

class Test
{
    public:
        Test(  ) {}
        virtual ~Test(  ) {}

        virtual void OnUpdate( ) {}
        virtual void OnRender(  ) {}
        virtual void OnImGuiRender(  ) {}
        virtual void OnImGuiPlot(  ) {}

        virtual bool hasPlot() {return false; };
};

class TestMenu : public Test
{
    public:
        TestMenu( Test*& currentTestPointer );
        ~TestMenu(  ) {};

        void OnImGuiRender(  ) override;

        template<typename T>
        void RegisterTest(const std::string& name){
            std::cout << "[ Registering Test ] " << name << std::endl;

            m_Tests.push_back(std::make_pair( name, []() { return new T; }  ) );
        }

    private:
        Test*& m_CurrentTest;
        std::vector< std::pair< std::string, std::function<Test*(  ) > > > m_Tests;
};
}
