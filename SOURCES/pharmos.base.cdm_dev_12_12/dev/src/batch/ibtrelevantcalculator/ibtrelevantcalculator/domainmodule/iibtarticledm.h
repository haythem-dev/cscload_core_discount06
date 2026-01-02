#ifndef GUARD_DOMMOD_IBTARTICLE_IIBTARTICLEDM_H
#define GUARD_DOMMOD_IBTARTICLE_IIBTARTICLEDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_resultsetref.h>

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtArticle {

class IIbtArticleDM
{
public:
	virtual ~IIbtArticleDM() {}

	virtual void                                                find				( ) = 0;
	virtual basar::Int32										findDemand			( const basar::Int32 articleNo, basar::Int32 weeksToConsider ) = 0;
	virtual bool												next				( ) = 0;
	virtual void												saveRelevanceFlag	(const basar::Int32 articleNo, const basar::Int32 assortmentType, basar::Int16 relvanceflag) = 0;
	virtual void												save				( const basar::Int32 articleNo, const bool isIbtRelevant, const basar::Int32 assortmentType ) = 0;
	virtual void                                                deleteUnknownConfig	( ) = 0;

	virtual const basar::db::sql::ResultsetRef					getArticleData		( ) = 0;
	virtual basar::Int32										getCounterUpdate	( ) = 0;
	virtual basar::Int32										getCounterInsert	( ) = 0;
	virtual basar::Int32										getCounterUnchanged	( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_IBTARTICLE_IIBTARTICLEDM_H
