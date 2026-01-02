#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXTASKCONTROL_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXTASKCONTROL_H

#include "ipxtaskcontrol.h"
#include "pxvbpxtaskcontrolptr.h"

#include <persistence/itransactionfactoryptr.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

	class PxTaskControl : public domMod::IPxTaskControl
	{	
		public:
			PxTaskControl( const log4cplus::Logger& logger );
			~PxTaskControl();								

			virtual void				setHeartBeat();	

			void						injectTransactionFactory(libcsc::persistence::ITransactionFactoryPtr transactionFactory);
			void						injectPxVbPxTaskControl(pxVbPxTaskControlPtr);

		private:
			PxTaskControl( const PxTaskControl& );
			PxTaskControl& operator= ( const PxTaskControl& );

			const log4cplus::Logger&							getLogger();
			libcsc::persistence::ITransactionFactoryPtr			getTransactionFactory();
			pxVbPxTaskControlPtr								getPxVbPxTaskControl();

			const log4cplus::Logger&							m_Logger;
			pxVbPxTaskControlPtr								m_pxVbPxTaskControl;
			libcsc::persistence::ITransactionFactoryPtr			m_TransactionFactory;
	};

} // namespace domMod
} // namespace ibtorderimport 

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXTASKCONTROL_H
