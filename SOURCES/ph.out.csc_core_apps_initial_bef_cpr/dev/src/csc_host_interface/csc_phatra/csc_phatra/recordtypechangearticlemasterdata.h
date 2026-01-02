//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeArticleMasterData
 *  \author Frank Naumann
 *  \date   26.01.2015
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEMASTERDATA_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEMASTERDATA_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h> 
#include "recordtypebase.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace processing {

//----------------------------------------------------------------------------//

static basar::ConstString FIELDNAME_VERTRIEBSSPERRE = "NAHRUNGSERGAENZUNG";

class RecordTypeChangeArticleMasterData : public core::RecordTypeBase
{
public:
	enum BookingType
	{
		BOOKINGTYPE_UNKNOWN = 0,
		BOOKINGTYPE_VERTRIEBSSPERRE = 1
	};

	RecordTypeChangeArticleMasterData();
	~RecordTypeChangeArticleMasterData();             
		
	virtual void					process( const core::TransactionRecordBasePtr record ) const;		

private:
	RecordTypeChangeArticleMasterData( const RecordTypeChangeArticleMasterData& );
	RecordTypeChangeArticleMasterData& operator= ( const RecordTypeChangeArticleMasterData& );


	virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

	void							processVertriebsSperre(const core::TransactionRecordBasePtr record) const;
};

//----------------------------------------------------------------------------//

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

//----------------------------------------------------------------------------//

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEMASTERDATA_H

