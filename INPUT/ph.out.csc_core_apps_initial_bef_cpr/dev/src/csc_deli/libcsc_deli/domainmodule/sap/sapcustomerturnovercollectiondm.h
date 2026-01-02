#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPCUSTOMERTURNOVERCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPCUSTOMERTURNOVERCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "isapcollectionwriter.h"

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
namespace sap
{
    class SAPCustomerTurnoverCollectionDM : public ISAPCollectionWriter
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        SAPCustomerTurnoverCollectionDM();
        ~SAPCustomerTurnoverCollectionDM();

        void injectSAPCustomerTurnoverCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;
        void                                                        insert( basar::db::aspect::AccessorPropertyTable_YIterator );

        void                                                        writeCollection();

    private:
        // forbidden
        SAPCustomerTurnoverCollectionDM( const SAPCustomerTurnoverCollectionDM& );
        SAPCustomerTurnoverCollectionDM& operator = ( const SAPCustomerTurnoverCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        //libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        //libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace sap
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPCUSTOMERTURNOVERCOLLECTIONDM_H
