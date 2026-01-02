#ifndef GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDM_H
#define GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_resultsetref.h>

//-----------------------------------------------------------------------------------------

namespace exportarticlecalculator {
namespace domMod {
namespace exportarticle {

class IExportArticleDM
{
public:
	virtual ~IExportArticleDM() {}

	virtual void                                                find				( ) = 0;
	virtual bool												next				( ) = 0;
	virtual void												save				( const basar::Int32 articleNo, const bool isExportExcluded ) = 0;
	virtual void                                                markChangedArticles	( ) = 0;
	
	virtual const basar::db::sql::ResultsetRef					getArticleData		( ) = 0;
	virtual basar::Int32										getCounterUpdate	( ) = 0;
	virtual basar::Int32										getCounterInsert	( ) = 0;
	virtual basar::Int32										getCounterUnchanged	( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDM_H
