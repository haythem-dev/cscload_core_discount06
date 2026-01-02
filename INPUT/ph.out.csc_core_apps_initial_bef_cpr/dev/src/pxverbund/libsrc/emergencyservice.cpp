#include "emergencyservice.h"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "tourutil.hpp"

/*----------------------------------------------------------------------------*/
EmergencyService::EmergencyService( pxSession* session, short branchno, long customerno )
	: pxDBRecord( session ), BranchNo( branchno ), CustomerNo( customerno )
{
	Init();
}

/*----------------------------------------------------------------------------*/
EmergencyService::~EmergencyService()
{
}

/*----------------------------------------------------------------------------*/
void EmergencyService::Init()
{
    tEMERGENCYSERVICEPLAN record;
    memset( &record, 0, sizeof(tEMERGENCYSERVICEPLAN) );
    Assign( *this, record );
}

/*----------------------------------------------------------------------------*/
EmergencyService& EmergencyService::operator=( const EmergencyService& src )
{
	tEMERGENCYSERVICEPLAN record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------*/
EmergencyService& EmergencyService::operator=( const tEMERGENCYSERVICEPLAN& src )
{
	return Assign( *this, src );
}


/*----------------------------------------------------------------------------*/
bool EmergencyService::Get(long date /*= 0*/)
{
	bool retval = false;
    tEMERGENCYSERVICEPLAN record;
	memset( &record, 0, sizeof(tEMERGENCYSERVICEPLAN) );

	record.BranchNo = this->BranchNo;
	record.CustomerNo = this->CustomerNo;
	record.EmergencyServiceDate = date;

    int rc = nDBRead( &record );
    if( 0 == rc )
	{
		this->m_Values = record;
		retval = true;
	}
    return retval;
}

/*----------------------------------------------------------------------------*/
int EmergencyService::Read( const void* record )
{
    return pxCustomerEmergencyServicePlanRead( (tEMERGENCYSERVICEPLAN*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
EmergencyService& EmergencyService::Assign( EmergencyService& dest, const tEMERGENCYSERVICEPLAN& src )
{
	dest.m_Values.BranchNo = src.BranchNo;
	dest.m_Values.CustomerNo = src.CustomerNo;
	dest.m_Values.DelayedDeliveryForCoolBelow20 = src.DelayedDeliveryForCoolBelow20;
	dest.m_Values.DelayedDeliveryForCoolBelow8 = src.DelayedDeliveryForCoolBelow8;
	dest.m_Values.DelayedDeliveryForCoolChain = src.DelayedDeliveryForCoolChain;
	dest.m_Values.DelayedDeliveryForNarcotics = src.DelayedDeliveryForNarcotics;
	dest.m_Values.EmergencyServiceDate = src.EmergencyServiceDate;
	dest.m_Values.EmergencyServiceTimeFrom = src.EmergencyServiceTimeFrom;
	dest.m_Values.EmergencyServiceTimeTo = src.EmergencyServiceTimeTo;
    return dest;
}

/*----------------------------------------------------------------------------*/
tEMERGENCYSERVICEPLAN& EmergencyService::Assign( tEMERGENCYSERVICEPLAN& dest, const EmergencyService& src )
{
	dest.BranchNo = src.m_Values.BranchNo;
	dest.CustomerNo = src.m_Values.CustomerNo;
	dest.DelayedDeliveryForCoolBelow20 = src.m_Values.DelayedDeliveryForCoolBelow20;
	dest.DelayedDeliveryForCoolBelow8 = src.m_Values.DelayedDeliveryForCoolBelow8;
	dest.DelayedDeliveryForCoolChain = src.m_Values.DelayedDeliveryForCoolChain;
	dest.DelayedDeliveryForNarcotics = src.m_Values.DelayedDeliveryForNarcotics;
	dest.EmergencyServiceDate = src.m_Values.EmergencyServiceDate;
	dest.EmergencyServiceTimeFrom = src.m_Values.EmergencyServiceTimeFrom;
	dest.EmergencyServiceTimeTo = src.m_Values.EmergencyServiceTimeTo;
    return dest;
}

/*----------------------------------------------------------------------------*/
short EmergencyService::getBranchNo() const
{
	return m_Values.BranchNo;
}

/*----------------------------------------------------------------------------*/
long EmergencyService::getCustomerNo() const
{
	return m_Values.CustomerNo;
}

/*----------------------------------------------------------------------------*/
long EmergencyService::getEmergencyServiceDate() const
{
	return m_Values.EmergencyServiceDate;
}

/*----------------------------------------------------------------------------*/
long EmergencyService::getEmergencyServiceTimeTo() const
{
	return m_Values.EmergencyServiceTimeTo;
}

/*----------------------------------------------------------------------------*/
long EmergencyService::getEmergencyServiceTimeFrom() const
{
	return m_Values.EmergencyServiceTimeFrom;
}

/*----------------------------------------------------------------------------*/
basar::VarString EmergencyService::getRemarks() const
{
	return (basar::VarString)m_Values.Remarks;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::delayDeliveryForNarcotics() const
{
	if(0 == m_Values.DelayedDeliveryForNarcotics) return true;
	return false;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::delayDeliveryForCoolChain() const
{
	if(0 == m_Values.DelayedDeliveryForCoolChain) return true;
	return false;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::delayDeliveryForCoolBelow8() const
{
	if(0 == m_Values.DelayedDeliveryForCoolBelow8) return true;
	return false;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::delayDeliveryForCoolBelow20() const
{
	if(0 == m_Values.DelayedDeliveryForCoolBelow20) return true;
	return false;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::delayDeliveryForArticle(pxArtBase* article) const
{
	if( this->delayDeliveryForNarcotics() && article->ArtClass().IsOpiat() ) return true;
	if( this->delayDeliveryForCoolChain() && article->ArtFlags().IsKuehlKette() ) return true;
	if( this->delayDeliveryForCoolBelow8() && article->ArtFlags().IsGekuehlt08() ) return true;
	if( this->delayDeliveryForCoolBelow20() && article->ArtFlags().IsGekuehlt20() ) return true;
	return false;
}

/*----------------------------------------------------------------------------*/
bool EmergencyService::isRelevantForTour( const nString& tourid ) const
{
	long tourtime = TourUtil::getTourIdAsHHMM(tourid) * 100; // 272900
	if( tourtime >= this->getEmergencyServiceTimeFrom() && tourtime <= this->getEmergencyServiceTimeTo() )
	{
		return true;
	}

	// in Abstimmung mit Anja Lohmar: Notdienst muss auch für >2359-Touren gelten! SR-17101355
	if (235900 == this->getEmergencyServiceTimeTo() && tourtime >= 240000)
	{
		return true;
	}

	return false;
}
