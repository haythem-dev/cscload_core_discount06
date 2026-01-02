#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPLIMITCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPLIMITCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "isapcollectionreader.h"

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
    class SAPLimitCollectionDM : public ISAPCollectionReader
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        SAPLimitCollectionDM();
        ~SAPLimitCollectionDM();

        void injectSAPLimitCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;

        void                                                        readCollection();
        void                                                        backup()  const;

    private:
        // forbidden
        SAPLimitCollectionDM( const SAPLimitCollectionDM& );
        SAPLimitCollectionDM& operator = ( const SAPLimitCollectionDM& );

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

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPLIMITCOLLECTIONDM_H
