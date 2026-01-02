#ifndef GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDM_H
#define GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_resultsetref.h>

//-----------------------------------------------------------------------------------------

namespace loadcontractshr {
namespace domMod {
namespace loadcontractshrdm {

class ILoadContractsHrDM
{
public:
	virtual ~ILoadContractsHrDM() {}
	enum ResultGrp
	{
		NONE = -1,
		BADFORMAT = 0,
		OUTOFDATE = 1,
		DOES_NOT_EXIST = 2,
		MATCHING_EXISTS = 3,
		SIMILAR_EXISTS = 4,
		UPDATED = 5,
		NO_MATCHING_FOUND = 6,
		INSERTED = 7
	};
	virtual bool												next				( ) = 0;
	virtual void                                                run					( ) = 0;
	virtual basar::VarString									getPath				( ) = 0;
	virtual basar::VarString									getMode				( ) = 0;
	
	virtual basar::Int32										getCounterRebatesUpdated    ( ) = 0;
	virtual basar::Int32										getCounterRebatesAdded		( ) = 0;
	virtual basar::Int32										getCounterContractsAdded() = 0;
	virtual basar::Int32										getCounterRebatesUnchanged	( ) = 0;
	virtual basar::Int32										getCounterRebatesUnchangedOutOfDate ( ) = 0;
	virtual basar::Int32										getCounterRebatesUnchangedSimilar() = 0;
	virtual basar::Int32										getCounter() = 0;
	virtual basar::Int32										getCounterBadFormat() = 0;
	virtual std::stringstream*									getResult(ResultGrp grp) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDM_H
