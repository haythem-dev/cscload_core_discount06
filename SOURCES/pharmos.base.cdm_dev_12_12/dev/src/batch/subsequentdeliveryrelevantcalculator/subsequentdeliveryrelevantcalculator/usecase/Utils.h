#ifndef GUARD_UTILS_H
#define GUARD_UTILS_H

#include <string>
#include <hdatum/phodate.h>

namespace subsequentdeliveryrelevantcalculator
{
	namespace useCase
	{

		/// <summary>
		/// 
		/// </summary>
		class Utils
		{
		public:
			static PHODATE today();
			static const std::string utc_date();

		private:
			static int today_utc();
		};

	}
}

#endif
