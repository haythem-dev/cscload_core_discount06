#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_FILEACCESSORBASE_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_FILEACCESSORBASE_H

#include <libutil/accessor.h>

#include "accessmethodcaller.hpp"
#include <libbasardbaspect_accessorpropertytable_yiterator.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
    class AccessorBase : public libutil::infrastructure::accessor::IAccessor
    {
    public:
        AccessorBase( const basar::VarString& accessorName );
        virtual ~AccessorBase();

        const basar::db::aspect::AccessorPropertyTableRef  getPropertyTable() const;
        basar::db::aspect::AccessorPropertyTableRef        getPropertyTable();

        virtual const basar::db::aspect::ExecuteResultInfo execute( const basar::db::aspect::AccessMethodName&, 
                                                                    const bool clearBeforeSelect = true, const bool flagExcept = true, 
                                                                    const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	    virtual const basar::db::aspect::ExecuteResultInfo execute( const basar::db::aspect::AccessMethodName&, 
                                                                    basar::db::aspect::AccessorPropertyTable_YIterator,
	                                                                const bool clearBeforeSelect = true, const bool flagExcept = true, 
	                                                                const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	    virtual const basar::db::aspect::ExecuteResultInfo execute( const basar::db::aspect::AccessMethodName&,
	                                                                basar::db::aspect::AccessorPropertyTable_YIterator yitBegin, 
                                                                    basar::db::aspect::AccessorPropertyTable_YIterator yitEnd,
	                                                                const bool clearBeforeSelect = true, const bool flagExcept = true,
	                                                                const basar::db::aspect::DatabaseHintEnum dbHint = basar::db::aspect::NO_HINT );

	    virtual const std::pair<bool, basar::Decimal>      executeAggregate( const basar::db::aspect::AccessMethodName& );
	    virtual const std::pair<bool, basar::Decimal>      executeAggregate( const basar::db::aspect::AccessMethodName&,
                                                                             basar::db::aspect::AccessorPropertyTable_YIterator );


        //-----------------------------------------------------------------------------------//
	    // Serial id methods (not overwritable 'cause not necessary)
	    //-----------------------------------------------------------------------------------//   
        basar::Int64                                       getLastInsertedSerial();
        basar::Int64                                       getInsertedSerial( const basar::Int32 );
        basar::Int32                                       getNumberOfLastInsertedSerials();
        bool                                               hasLastInsertedSerial();
        void                                               clearLastInsertedSerials();

    protected:
        typedef AccessMethodCaller< basar::db::aspect::AccessorPropertyTable_YIterator > AccMethodCaller;

        // pure virtual methods
        virtual void                                       registerAccessorMethods( AccMethodCaller& )                                       = 0;
        virtual void                                       setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const = 0;

    private:
        // forbidden
        AccessorBase();
        AccessorBase( const AccessorBase& );
        AccessorBase& operator = ( const AccessorBase& );

        void                                               init();
        bool                                               isInitialized() const;

        void                                               initAccessor() const;
        void                                               destroyAccessor();

        void                                               clear( bool );

        basar::db::aspect::AccessorInstanceRef             getAccessor() const;

    private:
        basar::VarString								   m_AccessorDefinitionName;
        mutable basar::db::aspect::AccessorInstanceRef     m_Accessor;

        AccMethodCaller                                    m_AccessMethodCaller;
    };

} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_FILEACCESSORBASE_H
