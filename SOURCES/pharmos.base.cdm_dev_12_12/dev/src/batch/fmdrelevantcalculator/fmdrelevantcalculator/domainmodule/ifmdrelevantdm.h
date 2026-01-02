#ifndef GUARD_DOMMOD_FMDRELEVANT_IFMDRELEVANTDM_H
#define GUARD_DOMMOD_FMDRELEVANT_IFMDRELEVANTDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_resultsetref.h>

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmdarticle {

class IFmdRelevantDM
{
public:
	virtual ~IFmdRelevantDM() {}

	virtual void                                                find				( ) = 0;
	virtual bool												next				( ) = 0;
	virtual void												save				( const basar::Int32 articleno, const basar::Int16 isFmdRelevant ) = 0;
	virtual basar::Int16										getBranchNo         ( ) = 0;
	
	virtual const basar::db::sql::ResultsetRef					getArticleData		( ) = 0;
	virtual basar::Int32										getCounterUpdate	( ) = 0;
	virtual basar::Int32										getCounterUnchanged	( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_FMDRELEVANT_IFMDRELEVANTDM_H
