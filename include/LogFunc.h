#pragma once
#include <iostream>
#include <chrono>
#include <ctime> 

namespace test {

class Log
{
    private:
        std::chrono::system_clock::duration m_SystemStartTime;
    public:
        Log(const std::chrono::system_clock::duration);
        ~Log() {}

        inline Log* GetLogger() { return this; }

        void warn(const char*);
};

}

#define TEST_WARN(...) ::test::Log::GetLogger()->warn(__VA_ARGS_)