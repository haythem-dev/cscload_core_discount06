// enable use of getenv() under Windows without stupid warnings
// reading the value of an environment variable, feeding it to
// std::stoi() and catching any possibly resulting exception is 
// NOT a security problem
#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "Utils.h"


namespace subsequentdeliveryrelevantcalculator
{
	namespace useCase
	{
		inline std::string GetEnv(char const var[])
		{
			char* pVal = getenv(var);
			if (pVal != NULL)
			{
				return std::string(pVal);
			}
			else
			{
				return std::string();
			}
		}

		// --- class Utils

		const std::string Utils::utc_date()
		{
			namespace bg = boost::gregorian;

			static char const* const fmt = "%Y%m%d";
			std::ostringstream ss;
			// assumes std::cout's locale has been set appropriately for the entire app
			ss.imbue(std::locale(std::cout.getloc(), new bg::date_facet(fmt)));
			ss << bg::day_clock::universal_day();
			return ss.str();
		}

		PHODATE Utils::today()
		{
			// check if test environment
			auto testDate = GetEnv("subsequentdelivery_DATE");
			if (!testDate.empty())
			{
				try
				{
					auto res = std::stoi(testDate);
					return res;
				}
				catch (...)
				{
					return PhoToday();
				}
			}
			else
			{
				return PhoToday();
			}
		}

		int Utils::today_utc()
		{
			std::string::size_type sz;
			auto res = std::stoi(Utils::utc_date(), &sz);
			return res;
		}
	}
}