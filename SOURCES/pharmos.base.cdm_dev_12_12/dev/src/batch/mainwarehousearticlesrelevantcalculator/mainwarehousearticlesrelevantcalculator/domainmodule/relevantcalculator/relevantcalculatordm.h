#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_RELEVANTCALCULATORDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_RELEVANTCALCULATORDM_H

#include "irelevantcalculator.h"

#include "domainmodule/article/iarticlecollectionfinderptr.h"
#include "domainmodule/article/iarticleconfigwriterptr.h"

#include <libutil/classinfo.h>
#include <libutil/session.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantCalculator
{
    class RelevantCalculatorDM : public IRelevantCalculator
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        RelevantCalculatorDM();
        ~RelevantCalculatorDM();

        void                                         injectArticleCollectionFinder( domMod::article::IArticleCollectionFinderPtr );
        void                                         injectArticleConfigWriter    ( domMod::article::IArticleConfigWriterPtr     );

        void                                         setSession                   ( libutil::infrastructure::session::ISessionPtr );

        // from IRelevantCalculator interface
        void                                         calculate();

    private:
        // forbidden
        RelevantCalculatorDM( const RelevantCalculatorDM& );
        RelevantCalculatorDM& operator = ( const RelevantCalculatorDM& );

        const log4cplus::Logger&                      getLogger()                  const;

        domMod::article::IArticleCollectionFinderPtr  getArticleCollectionFinder() const;
        domMod::article::IArticleConfigWriterPtr      getArticleConfigWriter()     const;
        libutil::infrastructure::session::ISessionPtr getSession()                 const;

    private:
        const log4cplus::Logger&                      m_Logger;
        domMod::article::IArticleCollectionFinderPtr  m_ArticleCollectionFinder;
        domMod::article::IArticleConfigWriterPtr      m_ArticleConfigWriter;
        libutil::infrastructure::session::ISessionPtr m_Session;
    };

} // end namespace relevantCalculator
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_RELEVANTCALCULATORDM_H
