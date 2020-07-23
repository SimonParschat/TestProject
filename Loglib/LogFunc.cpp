#include "LogFunc.h"

namespace testLog {

std::unique_ptr< testLog::Logger > Log::s_Logger;

Log::Log(const std::chrono::system_clock::duration startTime)
    :   m_SystemStartTime( startTime )
{
    s_Logger = std::make_unique< testLog::Logger >( m_SystemStartTime );

    std::string timeFormat = testLog::TimeDifference( m_SystemStartTime );

    std::cout << timeFormat << " [LOG : INIT] " << "Initialized" << std::endl;
}

}