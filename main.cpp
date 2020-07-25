#include <iostream>
#include <thread>

#include "LogFunc.h"
#include "PrintFunction.h" 
#include "Test.h"
#include "TestMesh.h"

int SCREEN_WIDTH = 960;
int SCREEN_HEIGHT = 600;


int main() 
{
    testLog::Log log( std::chrono::system_clock::now().time_since_epoch() );

    GLFWwindow* window;

    if ( !glfwInit() ) return -1;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );

    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Modern OpenGL", NULL, NULL );
    
    if ( !window ) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval( 1 );
    glewExperimental = GL_TRUE;

    if ( glewInit() != GLEW_OK ) std::cout << "Well, Fuck..." << std::endl;

    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 330" );
    ImGui::StyleColorsDark();

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu( currentTest );
    currentTest = testMenu;

    testMenu->RegisterTest< test::TestMesh >( "Test Draw" );

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    while ( !glfwWindowShouldClose( window ) )
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor( 0.3f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        if ( currentTest )
        {
            currentTest->OnUpdate(  );
            currentTest->OnRender(  );
            ImGui::Begin("Test");
            if ( currentTest != testMenu && ImGui::Button( "<-" ) )
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
            
            if ( currentTest != testMenu ) {
                if ( currentTest->hasPlot() ) {
                    ImGui::Begin("Plot", NULL, window_flags);
                    currentTest->OnImGuiPlot();
                    ImGui::End();
                }
            }
        }

        ImGui::Begin(" ", NULL, window_flags);
        ImGui::Text("%.3f ms, FPS: %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 

        glfwSwapBuffers( window );
        glfwPollEvents();
        glFinish();
    }

    glfwTerminate();
    return 0;
}