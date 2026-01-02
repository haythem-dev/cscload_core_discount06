//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  ConvHelper
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "convhelper.h"

namespace libcsc_utils
{

	ConvHelper::ConvHelper()
	{
	}

	ConvHelper::~ConvHelper()
	{
	}

	libcsc_utils::TimeParts ConvHelper::getTimeParts4NumericTime( basar::Int32 val /* Format: HHMMSS */ )
	//util::TimeParts ConvHelper::getTimeParts4NumericTime( timeType_HHMMSS val )

	{	
		libcsc_utils::TimeParts retval;	
		retval.m_Hour = val / 10000;
		val = val - (retval.m_Hour * 10000);
		retval.m_Minute = val / 100;
		retval.m_Second = val - (retval.m_Minute * 100);	
		return retval;
	}

	basar::Date ConvHelper::getDateFor8DigitsDate( basar::Int32 val /* Format: YYYYMMDD, e.g. 20120704 */ )
	{		
		basar::Int32 year = (val / 10000);
		val = val - (year * 10000);
		basar::Int32 month = val / 100;
		basar::Int32 day = val - (month * 100);	
		return basar::Date( year, month, day );
	}

	basar::Date ConvHelper::getDateFor6DigitsDate( basar::Int32 val /* Format: YYMMDD, e.g. 120704 */ )
	{		
		basar::Int32 year = (val / 10000);
		val = val - (year * 10000);
		basar::Int32 month = val / 100;
		basar::Int32 day = val - (month * 100);
		year = year + libcsc_utils::CENTURY;
		return basar::Date( year, month, day );
	}

	basar::Date ConvHelper::getDateFor4DigitsDateMMYY( basar::Int32 val /* Format: MMYY, e.g. 1012 = 10/2012, also: 515 = 05/2015 */ )
	{	
		basar::Date retval;
		try
		{					
			if (0 == val) //handle invalid date
			{				
				retval.setInvalid();
			}
			else
			{
				basar::Int32 month = val / 100;
				basar::Int32 year = val - (month * 100);	
				year = year + libcsc_utils::CENTURY;
				basar::Int32 day = basar::Date::getDaysOfMonth(year, month);	
				retval = basar::Date( year, month, day);			
			}
		}
		catch( ... )
		{
			retval.setInvalid();			
		}
		return retval;
	}

    basar::Int32 ConvHelper::get4DigitsDateYYMMFromDate( basar::Date date )
    {
        basar::Int32 year2Digits = date.getYear();
        year2Digits = year2Digits - ((year2Digits / 100) * 100);
        basar::Int32 month = date.getMonth();
        return year2Digits * 100 + month;

    }

	basar::Date ConvHelper::getDateFor4DigitsDateYYMM( basar::Int32 val /* Format: YYMM, e.g. 1309 = 09/2013 */ )
	{
		basar::Int32 year = val / 100;
		basar::Int32 month = val - (year * 100);	
        	year = year + libcsc_utils::CENTURY;
		basar::Int32 day = basar::Date::getDaysOfMonth(year, month);
		return basar::Date(year, month, day);	
	}


} // end namespace libcsc_utils
