//-------------------------------------------------------------------------------------------------------------------//
/*! \file		informix.h
*  \brief		representation of config informix
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_INFORMIX_H
#define GUARD_LIBCSC_UTILS_CONFIG_INFORMIX_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_utils
{
namespace config
{
	//-------------------------------------------------------------------------------------------------------------------//
	/*! \brief representation of config informix
	*/
	//-------------------------------------------------------------------------------------------------------------------//
	class Informix
	{
	public:
		Informix(void);
		Informix(basar::VarString const& ifxHost, basar::VarString const& ifxDataBase, basar::VarString const& ifxServiceName);
		~Informix(void);

		//Setter
		void						setIfxHost				(basar::VarString const& value);
		void						setIfxDataBase			(basar::VarString const& value);
		void						setIfxServiceName		(basar::VarString const& value);
		void                        setConnectionRetries    (basar::Int32 value);
		void                        setConnWaitBeforeRetry  (basar::Int32 value);
		void                        setActivate 			(bool value);

		//Getter
		basar::VarString	 	getIfxHost				    (void) const;
		basar::VarString 		getIfxDataBase			    (void) const;
		basar::VarString 		getIfxServiceName		    (void) const;
		basar::Int32			getConnectionRetries        (void) const;
		basar::Int32			getConnWaitBeforeRetry      (void) const;
		bool					getActivate 				(void) const;

		bool					isSetIfxHost			    (void) const;
		bool					isSetIfxDataBase		    (void) const;
		bool					isSetIfxServiceName		    (void) const;
		bool					isSetConnectionRetries      (void) const;
		bool					isSetConnWaitBeforeRetry    (void) const;
		bool					isSetActivate				(void) const;

	private:
		basar::VarString	m_IfxHost;
		basar::VarString	m_IfxDataBase;
		basar::VarString	m_IfxServiceName; 
		basar::Int32		m_ConnectionRetries;
		basar::Int32		m_ConnWaitBeforeRetry;
		bool				m_Activate;

		bool m_IsSetIfxHost;
		bool m_IsSetIfxDataBase;
		bool m_IsSetIfxServiceName;
		bool m_IsSetConnectionRetries;
		bool m_IsSetConnWaitBeforeRetry;
		bool m_IsSetActivate;
	};
}
}

#endif // GUARD_LIBCSC_UTILS_CONFIG_INFORMIX_H
