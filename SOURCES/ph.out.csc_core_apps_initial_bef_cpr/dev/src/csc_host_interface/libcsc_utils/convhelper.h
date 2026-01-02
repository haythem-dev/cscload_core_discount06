//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  ConvHelper
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_CONVHELPER_H
#define GUARD_LIBCSC_UTILS_CONVHELPER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_datetime.h> 
#include <libbasarcmnutil.h> 

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//

namespace libcsc_utils
{
	static const basar::Int32	CENTURY( 2000 );

	struct TimeParts
	{	
		basar::Int32 m_Hour;
		basar::Int32 m_Minute;
		basar::Int32 m_Second;
	};

	class ConvHelper
	{
		public:					
			typedef basar::Int32 timeType;

			static libcsc_utils::TimeParts				getTimeParts4NumericTime( basar::Int32 val /* Format: HHMMSS */ );
			//static util::TimeParts				convertFromHHMMSS( const timeType );

			static basar::Date					getDateFor4DigitsDateMMYY( basar::Int32 val /* Format: MMYY, e.g. 515 = 05/2015 */ );
			static basar::Date					getDateFor4DigitsDateYYMM( basar::Int32 val /* Format: YYMM, e.g. 1309 = 09/2013 */ );
			static basar::Date					getDateFor6DigitsDate( basar::Int32 val /* Format: YYMMDD, e.g. 120704 */ );
			static basar::Date					getDateFor8DigitsDate( basar::Int32 val /* Format: YYYYMMDD, e.g. 20120704 */ );
            static basar::Int32                   get4DigitsDateYYMMFromDate( basar::Date date);

		private:
			ConvHelper( const ConvHelper& );
			ConvHelper& operator= ( const ConvHelper& );

			ConvHelper();
			~ConvHelper();             				
			
	};
}// end namespace libcsc_utils

#endif // GUARD_LIBCSC_UTILS_CONVHELPER_H
