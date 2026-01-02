#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_STORAGELOCATIONDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_STORAGELOCATIONDM_H

#include "istoragelocationslotchecker.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace storageLocation
{
    class StorageLocationDM : public IStorageLocationSlotChecker
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        StorageLocationDM();
        ~StorageLocationDM();

        void                                                        injectStorageLocationSlotAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from IStorageLocationSlotChecker interface
        void                                                        findByBranchNo( basar::Int16 );
        bool                                                        hasStorageLocation( const basar::VarString& storageLocationSlot ) const;
        basar::VarString                                            getPseudoStorageLocation()                                        const;

    private:
        // forbidden
        StorageLocationDM( const StorageLocationDM& );
        StorageLocationDM& operator = ( const StorageLocationDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        
        const log4cplus::Logger&                                    getLogger() const;

        basar::db::aspect::AccessorPropertyTable_YIterator          get()     const;
        bool                                                        isEmpty() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace storageLocation
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_STORAGELOCATIONDM_H
