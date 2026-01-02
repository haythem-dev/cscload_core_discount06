//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "assignmentparametercollectiondm.h"

#include "infrastructure/accessor/assignmentparameter/assignmentparameteracc_definitions.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

#include <boost/make_shared.hpp>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace assignmentParameter
{

    const libutil::misc::ClassInfo& AssignmentParameterCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "AssignmentParameterCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    AssignmentParameterCollectionDM::AssignmentParameterCollectionDM()
    : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( AssignmentParameterCollectionDM, AssignmentParameterCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    AssignmentParameterCollectionDM::~AssignmentParameterCollectionDM()
    {
        METHODNAME_DEF( AssignmentParameterCollectionDM, ~AssignmentParameterCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void AssignmentParameterCollectionDM::injectAssignmentParameterCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr AssignmentParameterCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef AssignmentParameterCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool AssignmentParameterCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void AssignmentParameterCollectionDM::findByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF( AssignmentParameterCollectionDM, findByBranchNo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::assignmentParameter::lit::SELECT_ASSIGNMENT_PARAMETER_BY_BRANCH;

		std::ostringstream oss;
		oss << "loading all pumainwarehouseassignmentrules/params for branch=" << branchNo << " ...";
		BLOG_INFO( getLogger(), oss.str() );

		basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
			libutil::domMod::SearchYIteratorPtr searchYit = getSearchYIterator();
			searchYit->get().setInt16( properties::BRANCH_NO, branchNo );

            executeResultInfo = getAccessor()->execute( SELECT_ASSIGNMENT_PARAMETER_BY_BRANCH, searchYit->get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_ASSIGNMENT_PARAMETER_BY_BRANCH,
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_ASSIGNMENT_PARAMETER_BY_BRANCH, executeResultInfo )
        }

        createIndex();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator AssignmentParameterCollectionDM::getFirstParameterByName( const basar::VarString& name ) const
    {
        basar::db::aspect::AccessorPropertyTable_YIterator yit = get().end();
        ParameterIndex::const_iterator it = m_ParameterIndex.find( name );
        if( it != m_ParameterIndex.end() )
        {
            yit = it->second;
        }

        return yit;
    }

    libutil::domMod::SearchYIteratorPtr AssignmentParameterCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = boost::make_shared< libutil::domMod::SearchYIterator >(
                properties::BRANCH_NO.toDescriptionString()
            );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& AssignmentParameterCollectionDM::getLogger() const
    {
        return m_Logger;
    }

    void AssignmentParameterCollectionDM::createIndex()
    {
        m_ParameterIndex.clear();

        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = get().begin(); ! yit.isEnd(); ++yit )
        {
            const basar::VarString paramName = yit.getString( properties::CONTEXT_NAME );
            if( m_ParameterIndex.find( paramName ) == m_ParameterIndex.end() )
            {
                m_ParameterIndex[ paramName ] = yit;
            }
        }
    }
} // end namespace assignmentParameter
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

