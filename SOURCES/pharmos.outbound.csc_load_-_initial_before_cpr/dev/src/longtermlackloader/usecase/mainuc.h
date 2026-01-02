//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_LONGTERMLACKLOADER_USECASE_MAINUC_H
#define GUARD_LONGTERMLACKLOADER_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/longtermlackloaderapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"
//#include <libbasarappl_eventmacros.h>

#include <libutil/irunnable.h>
#include <libutil/qapplication.h>
#include <libutil/searchyiterator.h> //#include <libutil/yiterator.h>
#include <libutil/parameter.h>
#include <libutil/session.h>
#include <libutil/accessor.h>
#include <libutil/misc/timemeasure/timemeasure.h>






#include <vector>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace appl
    {
        class IEventSource;
        struct EventReturnStruct;
    }
}

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class Manager;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace useCase
    {
        struct LoadStatistic
        {
            LoadStatistic()
            : m_Table(""), m_Hits(-1)
            {}
            basar::VarString m_Table;
            basar::Int32 m_Hits;
            /*libutil::misc::TimeMeasure timeMeasure;
            timeMeasure.stop(); timeMeasure.getSeconds(); start stop */
        };
        //-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class MainUC : public libutil::useCase::IRunnable
        {
            public:
                MainUC();
                virtual ~MainUC();

                void                                                        injectLongTermLackAccesssor( libutil::infrastructure::accessor::IAccessorPtr );
                void                                                        injectDBSelectionParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr);
                void                                                        injectSession( libutil::infrastructure::session::ISessionPtr );

                virtual void                                                run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );
                
                void                                                        prepareArticlesWithoutStock();
                void                                                        prepareSubstitutionArticlesWithStock();
                void                                                        preparePseudoArticles();
                void                                                        prepareActiveArticles();
                void                                                        prepareArticlesWithoutStockBooking();
                void                                                        prepareArticlesReImport();
                void                                                        prepareReservedArticles();
                void                                                        prepareSpecialPZNs();
                void                                                        substractArticlesFromArticlesWithoutStock();
                void                                                        saveLongTermLack();
                void                                                        execute( const basar::VarString& acessMethodName,
                                                                                     basar::db::aspect::AccessorPropertyTable_YIterator yit);

                void                                                        cleanUpDB();
                void                                                        logLoadStatistics() const;

                const log4cplus::Logger&                                    getLogger() const;
                libutil::domMod::ISearchYIteratorPtr                        getParameterizationYIterator();
                libutil::infrastructure::accessor::IAccessorPtr             getLongTermLackAccessor();
                libutil::infrastructure::parameter::IParameterGatewayPtr    getDBActionParameter() const;
                libutil::infrastructure::session::ISessionPtr               getSession() const;
                
                bool                                                        isDBActionParameterSet( const basar::I18nString& parameterName ) const;
                bool                                                        isArticlesWithoutStockSelectionActive() const;
                bool                                                        isSubstitutionArticlesWithStockSelectionActive() const;
                bool                                                        isPseudoArticlesSelectionActive() const;
                bool                                                        isActiveArticlesSelectionActive() const;
                bool                                                        isArticlesWithoutStockBookingSelectionActive() const;
                bool                                                        isArticlesReImportSelectionActive() const;
                bool                                                        isReservedArticlesSelectionActive() const;
                bool                                                        isSpecialPZNsSelectionActive() const;
                bool                                                        isPersistenceStrategyTruncate() const;

                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&                                    m_Logger;
                libutil::domMod::ISearchYIteratorPtr                        m_ParameterizationYIterator;
                
                enum DifferenceEnum
                {
                    DIFFERENCE_MINUEND,
                    DIFFERENCE_SUBTRAHENT,
                    DIFFERENCE_NEGATIVE_SUBTRAHENT
                };
                typedef std::vector< std::pair< DifferenceEnum, basar::VarString> > TempTablesCollection;
                TempTablesCollection                                        m_TempTablesCollection;

                libutil::infrastructure::accessor::IAccessorPtr             m_LongTermLackAccessor;
                libutil::infrastructure::parameter::IParameterGatewayPtr    m_DBActionParameter;
                libutil::infrastructure::session::ISessionPtr               m_Session;

                typedef std::vector<LoadStatistic> LoadStatisticCollection;
                LoadStatisticCollection                                     m_LoadStatisticCollection;

        };
    } // namespace useCase
} // namespace longtermlackloader

#endif //end GUARD_LONGTERMLACKLOADER_USECASE_MAINUC_H
