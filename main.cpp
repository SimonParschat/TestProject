#include <iostream>
#include <thread>

#include "LogFunc.h"
#include "PrintFunction.h" 
#include "GLFW/glfw3.h"

int main() 
{
    test::Log log( std::chrono::system_clock::now().time_since_epoch() );
    PrintFunction pf( "Hello World!" );

    // std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(10));
    
    TEST_WARN("Warn");

    return 0;
}