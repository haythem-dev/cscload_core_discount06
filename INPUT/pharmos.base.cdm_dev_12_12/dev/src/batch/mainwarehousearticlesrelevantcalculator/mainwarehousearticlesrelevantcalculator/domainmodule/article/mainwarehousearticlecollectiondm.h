#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_MAINWAREHOUSEARTICLECOLLECTIONDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_MAINWAREHOUSEARTICLECOLLECTIONDM_H

#include "iarticlecollectionfinder.h"

#include "componentmanager/iarticlefactoryptr.h"
#include "domainmodule/mainwarehouse/imainwarehousefinderptr.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class MainwarehouseArticleCollectionDM : public IArticleCollectionFinder
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        MainwarehouseArticleCollectionDM();
        ~MainwarehouseArticleCollectionDM();

        void                                                        injectArticleCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void                                                        injectMainwarehouseFinder      ( domMod::mainwarehouse::IMainwarehouseFinderPtr );
        void                                                        injectArticleFactory           ( componentManager::IArticleFactoryPtr );

        // from IArticleCollectionFinder interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;

        void                                                        findByBranchNo( basar::Int16 );
        IArticlePtr                                                 getArticle( basar::db::aspect::AccessorPropertyTable_YIterator ) const;
        basar::Int32                                                countByBranchNo( basar::Int16 );

    private:
        // forbidden
        MainwarehouseArticleCollectionDM( const MainwarehouseArticleCollectionDM& );
        MainwarehouseArticleCollectionDM& operator = ( const MainwarehouseArticleCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        
        const log4cplus::Logger&                                    getLogger() const;

        basar::Int32                                                findLastPrognosisDate();
        basar::Int16                                                getMainwarehouseByBranchNo( basar::Int16 branchNo );

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
        domMod::mainwarehouse::IMainwarehouseFinderPtr              m_MainwarehouseFinder;
        componentManager::IArticleFactoryPtr                        m_ArticleFactory;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_MAINWAREHOUSEARTICLECOLLECTIONDM_H
