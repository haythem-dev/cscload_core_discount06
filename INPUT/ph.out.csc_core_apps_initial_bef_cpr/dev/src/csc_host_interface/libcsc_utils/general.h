//-------------------------------------------------------------------------------------------------------------------//
/*! \file		general.h
*  \brief		representation of config general
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_GENERAL_H
#define GUARD_LIBCSC_UTILS_CONFIG_GENERAL_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_utils
{
	namespace config
	{
		//-------------------------------------------------------------------------------------------------------------------//
		/*! \brief representation of config general
		*/
		//-------------------------------------------------------------------------------------------------------------------//
		class General
		{
		public:
			General(void);
			General(basar::Int32 pollInterval, basar::VarString const& logLevel, bool test);

			virtual ~General(void);


			// Setter
			void				setPollInterval		(basar::Int32 value);
			void				setLogLevel			(basar::VarString const& value);
			void				setTest				(bool value);
			void				setCountry			(basar::VarString const& value);
			void				setMaxSelectOrders	(basar::Int32 maxSelect);
			void				setBulkInsert		(bool value);

			// Getter
			bool				getTest				(void) const;
			basar::VarString	getLogLevel			(void) const;
			int					getPollInterval		(void) const;
			basar::VarString	getCountry			(void) const;
			basar::Int32		getMaxSelectOrders	(void) const;
			bool				getBulkInsert		(void) const;

			bool				isSetTest			(void) const;
			bool				isSetLogLevel		(void) const;
			bool				isSetPollInterval	(void) const;
			bool				isSetCountry		(void) const;
			bool				isSetMaxSelectOrders(void) const;
			bool				isSetBulkInsert		(void) const;

		private:
			basar::Int32		m_PollInterval;
			basar::VarString	m_LogLevel;
			bool				m_Test;
			basar::VarString	m_Country;
			basar::Int32		m_MaxSelectOrders;
			bool				m_BulkInsert;

			bool				m_IsSetTest;
			bool				m_IsSetLogLevel;
			bool				m_IsSetPollInterval;
			bool				m_IsSetCountry;
			bool				m_IsSetMaxSelectOrders;
			bool				m_IsSetBulkInsert;
		};
	}
}

#endif  // GUARD_LIBCSC_UTILS_CONFIG_GENERAL_H

