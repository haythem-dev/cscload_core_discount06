#ifndef GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icremamailcleaner.h"

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
namespace cremaMail
{
    class CremaMailCleanupDM : public ICremaMailCleaner
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CremaMailCleanupDM();
        ~CremaMailCleanupDM();

        void injectCremaMailCleanupAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from ICremaMailCleanerDM interface
        void cleanup();

    private:
        // forbidden
        CremaMailCleanupDM( const CremaMailCleanupDM& );
        CremaMailCleanupDM& operator = ( const CremaMailCleanupDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        //libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        //libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace cremaMail
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDM_H