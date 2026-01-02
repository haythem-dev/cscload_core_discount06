#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_MAINWAREHOUSEDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_MAINWAREHOUSEDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "imainwarehousefinder.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace mainwarehouse
{
    class MainwarehouseDM : public IMainwarehouseFinder
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        MainwarehouseDM();
        ~MainwarehouseDM();

        void                                                        injectMainwarehouseAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from IMainwarehouseFinder interface
        void                                                        findByBranchNo( basar::Int16 );
        basar::Int16                                                getMainwarehouseBranch() const;

    private:
        // forbidden
        MainwarehouseDM( const MainwarehouseDM& );
        MainwarehouseDM& operator = ( const MainwarehouseDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();

        basar::db::aspect::AccessorPropertyTable_YIterator          get() const;
        bool                                                        isEmpty() const;
         
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace mainwarehouse
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_MAINWAREHOUSEDM_H
