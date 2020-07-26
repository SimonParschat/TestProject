#include <iostream>
#include <thread>

#include "LogFunc.h"
#include "PrintFunction.h" 
#include "Test.h"
#include "TestMesh.h"

glm::vec3 cameraPosition = glm::vec3(0.0f);
glm::vec2 cameraRotation = glm::vec2(0.0f);

int SCREEN_WIDTH = 960;
int SCREEN_HEIGHT = 600;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
        cameraPosition.z = (cameraPosition.z == 0.0f) ?  1.0f : 0.0f;
    if ((key == GLFW_KEY_A) && (action == GLFW_PRESS))
        cameraPosition.x = (cameraPosition.x == 0.0f) ? -1.0f : 0.0f;
    if ((key == GLFW_KEY_D) && (action == GLFW_PRESS))
        cameraPosition.x = (cameraPosition.x == 0.0f) ?  1.0f : 0.0f;
    if ((key == GLFW_KEY_S) && (action == GLFW_PRESS))
        cameraPosition.z = (cameraPosition.z == 0.0f) ? -1.0f : 0.0f;
    if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS))
        cameraPosition.y = (cameraPosition.y == 0.0f) ?  1.0f : 0.0f;
    if ((key == GLFW_KEY_LEFT_SHIFT) && (action == GLFW_PRESS))
        cameraPosition.y = (cameraPosition.y == 0.0f) ?  -1.0f : 0.0f;
    
    if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS))
        cameraRotation.x = (cameraRotation.x == 0.0f) ? 1.0f : 0.0f;
    if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS))
        cameraRotation.x = (cameraRotation.x == 0.0f) ? -1.0f : 0.0f;
    if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS))
        cameraRotation.y = (cameraRotation.y == 0.0f) ? -1.0f : 0.0f;
    if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS))
        cameraRotation.y = (cameraRotation.y == 0.0f) ? 1.0f : 0.0f;
    

    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        cameraPosition.z = cameraPosition.z ==  1.0f ?  0.0f :-1.0f;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        cameraPosition.x = cameraPosition.x == -1.0f ?  0.0f : 1.0f;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        cameraPosition.x = cameraPosition.x ==  1.0f ?  0.0f :-1.0f;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        cameraPosition.z = cameraPosition.z == -1.0f ?  0.0f : 1.0f;
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        cameraPosition.y = cameraPosition.y ==  1.0f ?  0.0f :-1.0f;
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        cameraPosition.y = cameraPosition.y == -1.0f ?  0.0f : 1.0f;
    
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        cameraRotation.x = cameraRotation.x == 1.0f ?  0.0f : -1.0f;
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        cameraRotation.x = cameraRotation.x == -1.0f ?  0.0f : 1.0f;
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        cameraRotation.y = cameraRotation.y == -1.0f ?  0.0f : 1.0f;
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        cameraRotation.y = cameraRotation.y == 1.0f ?  0.0f : -1.0f;
}

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

    glfwSetKeyCallback(window, KeyCallback);

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

        // ImGui::ShowDemoWindow();

        glClearColor( 0.3f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        if ( currentTest )
        {
            currentTest->OnUpdate( cameraPosition, cameraRotation );
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
    delete currentTest;
    if ( currentTest != testMenu )
        delete testMenu;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}