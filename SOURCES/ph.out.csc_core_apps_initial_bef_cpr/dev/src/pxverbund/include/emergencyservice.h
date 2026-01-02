#ifndef EMERGENCYSERVICE_H
#define EMERGENCYSERVICE_H

#include "pxbase/pxrecord.hpp"
#include "pxrecord.h"
#include "pxartbas.hpp"
#include <libbasarcmnutil_bstring.h>

struct tEMERGENCYSERVICEPLAN;

// --------------------------------------------------------------------------------------------------- //
class EmergencyService : public pxDBRecord
{
	public:
												EmergencyService( pxSession* session, short branchno, long customerno );
		virtual									~EmergencyService();

		EmergencyService&						operator=( const EmergencyService& src );
		EmergencyService&						operator=( const tEMERGENCYSERVICEPLAN& src );

		bool 									Get(long date = 0);

		short									getBranchNo() const;
		long									getCustomerNo() const;
		long									getEmergencyServiceDate() const;
		long									getEmergencyServiceTimeFrom() const;
		long									getEmergencyServiceTimeTo() const;
		basar::VarString						getRemarks() const;

		bool									delayDeliveryForNarcotics() const;
		bool									delayDeliveryForCoolChain() const;
		bool									delayDeliveryForCoolBelow8() const;
		bool									delayDeliveryForCoolBelow20() const;
		bool									delayDeliveryForArticle( pxArtBase* article ) const;

		bool									isRelevantForTour( const nString& tourid ) const;

	protected:
		void									Init();

	private:
		short									BranchNo;
		long									CustomerNo;

		tEMERGENCYSERVICEPLAN					m_Values;

		virtual  int							Read( const void *record );
		EmergencyService&						Assign( EmergencyService& dest, const tEMERGENCYSERVICEPLAN& src );
		tEMERGENCYSERVICEPLAN&					Assign( tEMERGENCYSERVICEPLAN& dest, const EmergencyService& src);
};

#endif // EMERGENCYSERVICE_H
