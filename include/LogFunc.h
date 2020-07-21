#pragma once
#include <iostream>
#include <chrono>
#include <ctime> 

class Log
{
    private:
        std::chrono::system_clock::duration m_SystemStartTime;
    public:
        Log(const std::chrono::system_clock::duration);
        ~Log() {}

        void warn(const char*);
};