#include "TestMesh.h"
#include "LogFunc.h"

namespace test {

    TestMesh::TestMesh()
    {
        plotEnabled = false;
        if( glfwGetTime() >= m_Timer+1.0f ) {
            TEST_INFO("TestMesh Constructor");
            m_Timer = glfwGetTime();
        }
    }

    void TestMesh::OnUpdate()
    {
        if( glfwGetTime() >= m_Timer+2.0f ) {
            TEST_INFO("TestMesh On Update Function");
            m_Timer = glfwGetTime();
        }
    }

    void TestMesh::OnRender()
    {
        glClearColor( 0.0f, 0.3f, 0.7f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    void TestMesh::OnImGuiRender()
    {

    }

    void TestMesh::OnImGuiPlot()
    {}

}