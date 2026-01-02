#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORY_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORY_H

#include "iarticlefactory.h"

#include "domainmodule/relevantrule/irelevantruleptr.h"

#include "infrastructure/dataprovider/idataproviderptr.h"

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    class ArticleFactory : public IArticleFactory
    {
    public:
        ArticleFactory();
        ~ArticleFactory();

        void                                                           injectRelevantRule( domMod::relevantRule::IRelevantRulePtr );

        // from IArticleFactory interface
        domMod::article::IArticlePtr                                   create( basar::db::aspect::AccessorPropertyTable_YIterator );

    private:
        // forbidden
        ArticleFactory( const ArticleFactory& );
        ArticleFactory& operator = ( const ArticleFactory& );

        const log4cplus::Logger&                                       getLogger()              const;
        domMod::relevantRule::IRelevantRulePtr                         getRelevantRule()        const;

        infrastructure::dataProvider::IDataProviderPtr                 getDataProvider( basar::db::aspect::AccessorPropertyTable_YIterator );

    private:
        const log4cplus::Logger&                                       m_Logger;
        domMod::relevantRule::IRelevantRulePtr                         m_RelevantRule;
    };

}// end namespace componentManager
}// end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORY_H
