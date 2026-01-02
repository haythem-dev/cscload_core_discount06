#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idebtlimitcollection.h"

#include "componentmanager/idebtlimitdisconnectedfactoryptr.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>
#include <map>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{
    class DebtLimitCollectionDM : public IDebtLimitCollection
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        DebtLimitCollectionDM();
        ~DebtLimitCollectionDM();

        void                                                        injectDebtLimitCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void                                                        injectDebtLimitDisconnectedFactory( componentManager::IDebtLimitDisconnectedFactoryPtr );

        // from IDebtLimitCollectionDM interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        IDebtLimitPtr                                               getDebtLimit( basar::Int32 partnerNo );

        bool                                                        isEmpty() const;

        void                                                        load();

        IDebtLimitPtr                                               appendEmptyItem( basar::Int32 partnerNo );
        basar::db::aspect::AccessorPropertyTable_YIterator          erase( IDebtLimitPtr );

    private:
        // forbidden
        DebtLimitCollectionDM( const DebtLimitCollectionDM& );
        DebtLimitCollectionDM& operator = ( const DebtLimitCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        componentManager::IDebtLimitDisconnectedFactoryPtr          getDebtLimitDisconnectedFactory();
        
        const log4cplus::Logger&                                    getLogger() const;
        void                                                        createIndex();

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
        componentManager::IDebtLimitDisconnectedFactoryPtr          m_DebtLimitDisconnectedFactory;

        // index
        typedef std::map< basar::Int32, basar::db::aspect::AccessorPropertyTable_YIterator > IndexPartnerNo;
        IndexPartnerNo                                              m_IndexPartnerNo;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDM_H
