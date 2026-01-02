#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_ACCESSORPROXYUNIONDECORATOR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_ACCESSORPROXYUNIONDECORATOR_H

/*
    Executes all internal accessors and creates a union by appending all found datasets to default accessor
*/

#include "infrastructure/connectionpool/iconnectionpoolgetterptr.h"
#include <libutil/accessor.h>
#include <vector>

namespace log4cplus
{
    class Logger;
}

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
    class AccessorProxyUnionDecorator : public libutil::infrastructure::accessor::IAccessor
    {
        public:
            AccessorProxyUnionDecorator( const basar::VarString & accessorName, connectionPool::IConnectionPoolGetterPtr,
				                    const basar::db::aspect::CachingPolicyEnum eCachePolicy = basar::db::aspect::ON_DEMAND_CACHING,
				                    const bool storeInInstanceList = true );
            ~AccessorProxyUnionDecorator();

            const basar::db::aspect::AccessorPropertyTableRef  getPropertyTable() const;
            basar::db::aspect::AccessorPropertyTableRef        getPropertyTable();

            const basar::db::aspect::ExecuteResultInfo         execute( const basar::db::aspect::AccessMethodName&, 
                                                                        const bool clearBeforeSelect = true, const bool flagExcept = true, 
                                                                        const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	        const basar::db::aspect::ExecuteResultInfo         execute( const basar::db::aspect::AccessMethodName&, 
                                                                        basar::db::aspect::AccessorPropertyTable_YIterator,
	                                                                    const bool clearBeforeSelect = true, const bool flagExcept = true, 
	                                                                    const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	        const basar::db::aspect::ExecuteResultInfo         execute( const basar::db::aspect::AccessMethodName&,
	                                                                    basar::db::aspect::AccessorPropertyTable_YIterator yitBegin, 
                                                                        basar::db::aspect::AccessorPropertyTable_YIterator yitEnd,
	                                                                    const bool clearBeforeSelect = true, const bool flagExcept = true,
	                                                                    const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	        const std::pair<bool, basar::Decimal>              executeAggregate( const basar::db::aspect::AccessMethodName& );
	        const std::pair<bool, basar::Decimal>              executeAggregate( const basar::db::aspect::AccessMethodName&,
                                                                                 basar::db::aspect::AccessorPropertyTable_YIterator );

            basar::Int64                                       getLastInsertedSerial();
            basar::Int64                                       getInsertedSerial( const basar::Int32 );
            basar::Int32                                       getNumberOfLastInsertedSerials();
            bool                                               hasLastInsertedSerial();
            void                                               clearLastInsertedSerials();

        private:
            // forbidden
            AccessorProxyUnionDecorator();
            AccessorProxyUnionDecorator( const AccessorProxyUnionDecorator& );
            AccessorProxyUnionDecorator& operator = ( const AccessorProxyUnionDecorator& );

            const log4cplus::Logger&                           getLogger() const;
            void                                               appendToDefaultAccessor( basar::db::aspect::AccessorPropertyTableRef );

        private:
            const log4cplus::Logger&                           m_Logger;
            typedef std::vector< libutil::infrastructure::accessor::IAccessorPtr > AccessorCollection;

            libutil::infrastructure::accessor::IAccessorPtr    m_DefaultAccessor;
            AccessorCollection                                 m_Accessors;
    };

} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_ACCESSORPROXYUNIONDECORATOR_H
