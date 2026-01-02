#include <stdio.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include "mess.h"

//----------------------------------------------------------------------
static const char * const MSGFORMAT = "%-25s: %f sec\n";

//----------------------------------------------------------------------
class TimeMeasure::TimeSave
{
public:
				TimeSave	() 
                {
#ifdef WIN32
                    m_thrHnd = ::GetCurrentThread();

	                DWORD_PTR systemMask;

	                ::GetProcessAffinityMask(GetCurrentProcess(), &m_procAffMask, &systemMask);
	                ::SetThreadAffinityMask(m_thrHnd, 1);
	                ::QueryPerformanceFrequency(reinterpret_cast< LARGE_INTEGER* >(&m_Freq));
	                ::SetThreadAffinityMask(m_thrHnd, m_procAffMask);
#endif
                };

			   ~TimeSave	() {};

#ifdef WIN32
                __int64 GetTime() const
                {
	                LARGE_INTEGER curTime;
	                ::SetThreadAffinityMask(m_thrHnd, 1);
	                ::QueryPerformanceCounter(&curTime);
	                ::SetThreadAffinityMask(m_thrHnd, m_procAffMask);
	                return curTime.QuadPart;
                };

                void start()
                {
                    m_Start = GetTime();
                };

                void stop()
                {
                    m_Stop= GetTime();
                }

	__int64     m_Start;
	__int64     m_Stop;
   	__int64     m_Freq;

     void   *   m_thrHnd;

#if defined(_WIN64)
    unsigned __int64    m_procAffMask;
#else
    unsigned long       m_procAffMask;
#endif

#else

	timespec	m_Start;
	timespec	m_Stop;
#endif
};

//----------------------------------------------------------------------
TimeMeasure::TimeMeasure	( const char * const pMsg)
							: m_pMsg(pMsg),
							  m_pTimeSave(smptrTimeSave(new TimeSave))
{
}

//----------------------------------------------------------------------
TimeMeasure::~TimeMeasure	()
{
}   

//----------------------------------------------------------------------
#ifdef WIN32
//----------------------------------------------------------------------
double TimeMeasure::stop(bool silent /* = false */)
{
	 m_pTimeSave->stop();

	__int64 const elapsedTime = m_pTimeSave->m_Stop - m_pTimeSave->m_Start;

	double const seconds = double(elapsedTime) / double(m_pTimeSave->m_Freq);

	if (!silent)
		printf(MSGFORMAT, m_pMsg, seconds);
    
	return seconds;
}

//----------------------------------------------------------------------
void TimeMeasure::start()
{
    m_pTimeSave->start();
}

//----------------------------------------------------------------------
void TimeMeasure::wait(unsigned int milliSec)
{
	Sleep( milliSec );
}
 
//----------------------------------------------------------------------
#else
//----------------------------------------------------------------------
double TimeMeasure::stop(bool silent /* = false */)
{
	clock_gettime(CLOCK_REALTIME, &(m_pTimeSave->m_Stop));

	double dHRes = difftime(m_pTimeSave->m_Stop.tv_sec, m_pTimeSave->m_Start.tv_sec);
	long   lHRes = m_pTimeSave->m_Stop.tv_nsec - m_pTimeSave->m_Start.tv_nsec;

	double dDiff = ((double)lHRes)/((double)1000000000);
	dHRes += dDiff;

	if (!silent)
		printf(MSGFORMAT, m_pMsg, dHRes);
		   
	return dHRes;		  
}

//----------------------------------------------------------------------
void TimeMeasure::start()
{
	clock_gettime(CLOCK_REALTIME, &(m_pTimeSave->m_Start));
}

//----------------------------------------------------------------------
void TimeMeasure::wait(unsigned int milliSec)
{
	struct timeval waitTime;

	waitTime.tv_sec  = milliSec / 1000;
	waitTime.tv_usec = (milliSec % 1000) * 1000;

	select(0, 0, 0, 0, &waitTime);	 
}
 
//----------------------------------------------------------------------
#endif

