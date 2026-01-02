#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVERCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVERCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerturnovercollectionloader.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{
    class CustomerTurnoverCollectionDM : public ICustomerTurnoverCollectionLoader
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerTurnoverCollectionDM();
        ~CustomerTurnoverCollectionDM();

        void injectCustomerTurnoverCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from ICustomerTurnoverCollectionLoader interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;

        void                                                        load();

    private:
        // forbidden
        CustomerTurnoverCollectionDM( const CustomerTurnoverCollectionDM& );
        CustomerTurnoverCollectionDM& operator = ( const CustomerTurnoverCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        //libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();

        //void                                                        resetSearchYit();
        //basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        //libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVERCOLLECTIONDM_H
