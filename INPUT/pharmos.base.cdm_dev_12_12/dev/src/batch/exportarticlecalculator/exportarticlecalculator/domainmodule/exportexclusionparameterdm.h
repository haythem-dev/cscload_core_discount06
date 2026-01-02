#ifndef GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_EXPORTEXCLUSIONPARAMETERDM_H
#define GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_EXPORTEXCLUSIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include "iexportexclusionparameterdm.h"
#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace exportarticlecalculator {
namespace domMod {
namespace exportexclusionparameter {

//-----------------------------------------------------------------------------------------

class ExportExclusionParameterDM : public IExportExclusionParameterDM
{
public:
	ExportExclusionParameterDM(const log4cplus::Logger& logger);
	~ExportExclusionParameterDM();

	virtual void												injectAccessor		( libutil::infrastructure::accessor::IAccessorPtr );
	
	virtual void                                                find				( );
	virtual basar::db::aspect::AccessorPropertyTableRef         get();
	
	virtual void												setBranchNo			( const basar::Int16 branchNo );
	virtual void												setCountry			( const basar::VarString & country );
	virtual basar::Int16										getBranchNo			( );
	virtual basar::VarString									getCountry			( );

private:
	ExportExclusionParameterDM( const ExportExclusionParameterDM & );
	ExportExclusionParameterDM & operator = ( const ExportExclusionParameterDM & );

	const log4cplus::Logger&									getLogger() const;
	libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
	basar::db::aspect::AccessorPropertyTable_YIterator			createSearchIterator();

	const log4cplus::Logger&									m_Logger;
	basar::Int16												m_BranchNo;
	basar::VarString											m_Country ;
	libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_EXPORTEXCLUSIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

