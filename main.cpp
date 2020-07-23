#include <iostream>
#include <thread>

#include "LogFunc.h"
#include "PrintFunction.h" 

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
    
    TEST_INFO("Created Window");

    if ( !window ) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval( 1 );
    glewExperimental = GL_TRUE;

    if ( glewInit() != GLEW_OK ) std::cout << "Well, Fuck..." << std::endl;

    TEST_INFO( glGetString( GL_VERSION ), "OpenGL Version: " );

    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    TEST_WARN("Before Loop");

    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor( 0.3f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glfwSwapBuffers( window );
        glfwPollEvents();
        glFinish();
    }

    glfwTerminate();
    return 0;
}