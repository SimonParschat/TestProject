#include "LogFunc.h"

namespace test {

Log::Log(const std::chrono::system_clock::duration startTime)
    :   m_SystemStartTime(startTime)
{
    auto duration = std::chrono::system_clock::now().time_since_epoch() - m_SystemStartTime;
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
    if (mili < 10) miliZero = "0";

    std::cout << "["<<hourZero<<hours<<":"<<minZero<<minutes<<":"<<secZero<<seconds<<":"<<miliZero<<mili<<"] [LOG : INIT] " << "Initialized" << std::endl;
}

void Log::warn(const char* message)
{
    auto duration = std::chrono::system_clock::now().time_since_epoch() - m_SystemStartTime;
    auto mili = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
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
    if (mili < 10) miliZero = "0";

    std::cout << "["<<hourZero<<hours<<":"<<minZero<<minutes<<":"<<secZero<<seconds<<":"<<miliZero<<mili<<"] [LOG : WARNING] " << message << std::endl;
}

}