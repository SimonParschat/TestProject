#pragma once
#include <iostream>
#include <chrono>
#include <ctime> 

#include "Logger.h"

namespace testLog {

class Log
{
    private:
        static std::unique_ptr< testLog::Logger > s_Logger;
        std::chrono::system_clock::duration m_SystemStartTime;
    public:

        Log(const std::chrono::system_clock::duration);
        ~Log() {}

        inline static std::unique_ptr< testLog::Logger >& GetLogger() { return s_Logger; }
};

}

#define TEST_WARN(...) ::testLog::Log::GetLogger()->warn(__VA_ARGS__)
#define TEST_INFO(...) ::testLog::Log::GetLogger()->info(__VA_ARGS__)