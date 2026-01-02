#ifndef PXSESSIONINITIALIZATION_HPP
#define PXSESSIONINITIALIZATION_HPP

#include <libbasarcmnutil_bstring.h>
#include "pxdevicetypeenum.hpp"

class pxSessionInitialization
{
	public:	
		static basar::VarString	getCountryCode( const short branchNo );

						        pxSessionInitialization();
		virtual			        ~pxSessionInitialization();

		// setter
		void			        setBranchInformation( const short branchNo, const basar::VarString& countryCode );			
        void			        setDBInformation( const basar::VarString& dbServerName, const basar::VarString& dbName );		
		void			        setDevice( const ::pxDeviceType deviceType, const basar::VarString& deviceName );
		void			        setMessageFileName( const basar::VarString& messageFileName );

		// getter
		short			        getBranchNo() const;
		const basar::VarString&	getCountryCode() const;
		const basar::VarString&	getDBServerName() const;
		const basar::VarString&	getDBName() const;
		const basar::VarString&	getDeviceName() const;
		::pxDeviceType	        getDeviceType() const;			
		const basar::VarString& getMessageFileName() const;

		const basar::VarString&	getDBConnectionString() const;

	protected:
		void			        setCountryCode( const basar::VarString& countrycode );
		void			        setDeviceName( const basar::VarString& name );
		void			        setDeviceType( const ::pxDeviceType type );
		void			        setConnectionString( const basar::VarString& connectionstring );
		bool			        isConnectionStringSet() const;
		
	private:	
		void			        init();

		short			        m_BranchNo;
		basar::VarString		m_CountryCode;						
		basar::VarString		m_DBServerName;
		basar::VarString		m_DBName;
		::pxDeviceType	        m_DeviceType;
		basar::VarString		m_DeviceName;
		basar::VarString		m_MessageFileName;				
		basar::VarString		m_ConnectionString;

		friend class pxSession;
};

#endif // PXSESSIONINITIALIZATION_HPP
