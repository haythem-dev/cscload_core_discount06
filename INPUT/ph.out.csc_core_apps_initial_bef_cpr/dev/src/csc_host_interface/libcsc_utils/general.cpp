//-------------------------------------------------------------------------------------------------------------------//
/*! \file		general.cpp
*  \brief		representation of config general
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "general.h"
namespace libcsc_utils
{
	namespace config
	{
		General::General(void)
		{
			m_LogLevel = "";
			m_Country = "";
			m_PollInterval = 0;
			m_Test = false;
			m_MaxSelectOrders = 20;
			m_BulkInsert = false;

			m_IsSetCountry = false;
			m_IsSetTest = false;
			m_IsSetLogLevel = false;
			m_IsSetPollInterval = false;
			m_IsSetMaxSelectOrders = false;
			m_IsSetBulkInsert = false;
		}

		General::General(basar::Int32 pollInterval, basar::VarString const& logLevel, bool test)
		{
			m_LogLevel = logLevel;
			m_PollInterval = pollInterval;
			m_Test = test;

			m_IsSetTest = true;
			m_IsSetLogLevel = true;
			m_IsSetPollInterval = true;
		}

		General::~General(void)
		{
		}

		void General::setCountry(basar::VarString const& value)
		{
			m_Country = value;
			m_IsSetCountry = true;
		}

		void General::setPollInterval(basar::Int32 value)
		{
			m_PollInterval = value;
			m_IsSetPollInterval = true;
		}

		void General::setLogLevel(basar::VarString const& value)
		{	
			m_LogLevel = value;
			m_IsSetLogLevel = true;
		}

		void General::setTest(bool value)
		{
			m_Test = value;
			m_IsSetTest = true;
		}

		void General::setMaxSelectOrders(basar::Int32 maxSelectOrders)
		{
			m_MaxSelectOrders = maxSelectOrders;
			m_IsSetMaxSelectOrders = true;
		}

		void General::setBulkInsert(bool value)
		{
			m_BulkInsert = value;
			m_IsSetBulkInsert = true;
		}

		int General::getPollInterval(void) const
		{
			return m_PollInterval;
		}

		basar::VarString General::getLogLevel(void) const
		{
			return m_LogLevel;
		}

		basar::VarString General::getCountry() const
		{
			return m_Country;
		}

		bool General::getTest(void) const
		{
			return m_Test;
		}

		basar::Int32 General::getMaxSelectOrders(void) const
		{
			return m_MaxSelectOrders;
		}

		bool General::getBulkInsert(void) const
		{
			return m_BulkInsert;
		}

		bool General::isSetTest(void) const
		{
			return m_IsSetTest;
		}

		bool General::isSetLogLevel(void) const
		{
			return m_IsSetLogLevel;
		}

		bool General::isSetPollInterval(void) const
		{
			return m_IsSetPollInterval;
		}

		bool General::isSetCountry() const
		{
			return m_IsSetCountry;
		}

		bool General::isSetMaxSelectOrders(void) const
		{
			return m_IsSetMaxSelectOrders;
		}

		bool General::isSetBulkInsert(void) const
		{
			return m_IsSetBulkInsert;
		}
	}
}
