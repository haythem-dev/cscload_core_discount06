#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idebtlimit.h"

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
namespace debtLimit
{
    class DebtLimitDM : public IDebtLimit
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        DebtLimitDM();
        ~DebtLimitDM();

        void                                                        injectDebtLimitAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void                                                        set( basar::db::aspect::AccessorPropertyTable_YIterator );

        // from IDebtLimit interface
        basar::db::aspect::AccessorPropertyTable_YIterator          get() const;
        basar::db::aspect::AccessorPropertyTable_YIterator          get();

        bool                                                        isChanged() const;
        bool                                                        isEmpty() const;

        void                                                        erase();
        void                                                        save();

    private:
        // forbidden
        DebtLimitDM( const DebtLimitDM& );
        DebtLimitDM& operator = ( const DebtLimitDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        //libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        //libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        basar::db::aspect::AccessorPropertyTable_YIterator          m_YitDebtLimit;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITDM_H
