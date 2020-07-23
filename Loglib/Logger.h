#pragma once

#include <iostream>
#include <chrono>
#include <ctime> 

namespace testLog {

static std::string TimeDifference( const std::chrono::system_clock::duration& endT, const std::chrono::system_clock::duration& startT = std::chrono::system_clock::now().time_since_epoch() )
{
    auto duration = endT - startT;
    int mili = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    int hours = mili / (1000*60*60);
    std::string hourZero = "";
    if (hours < 10) hourZero = "0";

    int minutes = (mili-(hours*60*60*1000)) / (1000*60);
    std::string minZero = "";
    if (minutes < 10) minZero = "0";

    int seconds = (mili - (minutes*1000*60)) / 1000;
    std::string secZero = "";
    if (seconds < 10) secZero = "0";

    mili = mili - (seconds*1000);
    std::string miliZero = "";
    if (mili < 100) miliZero = "0";
    if (mili < 10) miliZero = "00";

    return "["+hourZero+ std::to_string(hours) + ":"+minZero + std::to_string(minutes)
            +":"+secZero+ std::to_string(seconds) +":"+miliZero+ std::to_string(mili) +"]";
}

    class Logger
    {
    private:
        std::chrono::system_clock::duration m_SystemStartTime;

    public:

        Logger(const std::chrono::system_clock::duration& startTime )
            :   m_SystemStartTime(startTime) {}

        ~Logger() {}
        
        template<typename T>
        void warn(T message, const char* optional = "")
        {
            
            std::string timeFormat =  testLog::TimeDifference( std::chrono::system_clock::now().time_since_epoch(), m_SystemStartTime );

            std::cout << timeFormat << " [LOG : WARNING] " << optional << message << std::endl;
        }

        template< typename T>
        void info(T message, const char* optional = "")
        {
            
            std::string timeFormat =  testLog::TimeDifference( std::chrono::system_clock::now().time_since_epoch(), m_SystemStartTime );

            std::cout << timeFormat << " [LOG : INFO] " << optional << message << std::endl;
        }
    };
}