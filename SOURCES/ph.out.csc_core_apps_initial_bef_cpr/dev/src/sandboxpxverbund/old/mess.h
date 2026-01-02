#ifndef __MESS_H__
#define __MESS_H__

#include <memory>

//----------------------------------------------------------------------
class TimeMeasure
{
public:
				TimeMeasure	(const char * const pMsg);
			   ~TimeMeasure	();


	void		start		();
	double		stop		(bool silent = false);

	static void	wait		(unsigned int milliSec);

private:

	const TimeMeasure &		operator = (const TimeMeasure &);
	class TimeSave;

	typedef std::auto_ptr < TimeSave >	smptrTimeSave;

	const char * const	m_pMsg;
	smptrTimeSave		m_pTimeSave;
};

//----------------------------------------------------------------------
#endif
