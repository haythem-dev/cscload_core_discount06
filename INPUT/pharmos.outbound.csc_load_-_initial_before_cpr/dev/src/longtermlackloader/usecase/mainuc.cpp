//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainuc.h"

#include "componentmanager/longtermlackloaderapplcompmgr.h"
#include "loggerpool/longtermlackloader_loggerpool.h"

#include <libutil/util.h>
#include <libutil/exception.h>

#include "infrastructure/accessor/longtermlackpgk/longtermlackacc_definitions.h"
#include <infrastructure/accessor/properties_definitions.h>
#include <infrastructure/accessor/tables_definitions.h>

#include <infrastructure/parameter/dbactionparameter.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace useCase
    {
        //-------------------------------------------------------------------------------------------------//
        // macro for registrating and deregistrating EventHandlers!
        //-------------------------------------------------------------------------------------------------//

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ArticleSearchUC::ArticleSearchUC()
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::MainUC()
        : m_Logger( infrastructure::LoggerPool::getLoggerUseCases() )
        {
            METHODNAME_DEF( MainUC, MainUC )
            BLOG_TRACE_METHOD( getLogger(), fun );
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ArticleSearchUC::~ArticleSearchUC()
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::~MainUC()
        {
            METHODNAME_DEF( MainUC, ~MainUC )
            BLOG_TRACE_METHOD( getLogger(), fun );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// ArticleSearchUC::~ArticleSearchUC()
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::injectSession( libutil::infrastructure::session::ISessionPtr session )
        {
            METHODNAME_DEF(MainUC, injectSession)
            BLOG_TRACE_METHOD(getLogger(), fun);

            m_Session = session;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // libutil::infrastructure::session::ISessionPtr MainUC::getSession() const
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::session::ISessionPtr MainUC::getSession() const
        {
            METHODNAME_DEF(MainUC, getSession)
            BLOG_TRACE_METHOD(getLogger(), fun);

            CHECK_INSTANCE_EXCEPTION(m_Session.get());
            return m_Session;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // void MainUC::injectDBSelectionParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameter )
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::injectDBSelectionParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameter )
        {
            METHODNAME_DEF(MainUC, injectDBSelectionParameterGateway)
            BLOG_TRACE_METHOD(getLogger(), fun);

            m_DBActionParameter = parameter;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // libutil::infrastructure::parameter::IParameterGatewayPtr MainUC::getDBSelectionParameter() const
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::parameter::IParameterGatewayPtr MainUC::getDBActionParameter() const
        {
            METHODNAME_DEF(MainUC, getDBActionParameter)
            BLOG_TRACE_METHOD(getLogger(), fun);
            
            CHECK_INSTANCE_EXCEPTION(m_DBActionParameter.get() );
            return m_DBActionParameter;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // void MainUC::execute(const basar::VarString& acessMethodName, basar::db::aspect::AccessorPropertyTable_YIterator yit)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::execute(const basar::VarString& acessMethodName, basar::db::aspect::AccessorPropertyTable_YIterator yit)
        {
            METHODNAME_DEF( MainUC, execute )
            BLOG_TRACE_METHOD( getLogger(), fun );

            using namespace longtermlackloader::infrastructure::accessor;

            LoadStatistic loadStatistic;
            loadStatistic.m_Table = yit.getString( properties::TARGET_TABLE_NAME.getName() );

            basar::db::aspect::ExecuteResultInfo executeResultInfo = getLongTermLackAccessor()->execute(acessMethodName, yit);
            if (executeResultInfo.hasError())
            {
                THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, acessMethodName, executeResultInfo )
            }

            std::pair< bool, basar::Decimal > result = getLongTermLackAccessor()->executeAggregate(longtermlack::lit::COUNT_DB_ROWS, yit);
            if (true == result.first)
            {
                loadStatistic.m_Hits = result.second.toInt32();
            }

            m_LoadStatisticCollection.push_back(loadStatistic);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // void MainUC::run()
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::run()
        {
            METHODNAME_DEF( MainUC, run )
            BLOG_TRACE_METHOD( getLogger(), fun );
            
            try
            {
                prepareArticlesWithoutStock();
                prepareSubstitutionArticlesWithStock();
                preparePseudoArticles();
                prepareActiveArticles();
                prepareArticlesWithoutStockBooking();
                prepareReservedArticles();
                prepareSpecialPZNs();
                prepareArticlesReImport();
                substractArticlesFromArticlesWithoutStock();

                saveLongTermLack();

                cleanUpDB();
                logLoadStatistics();
            } 
            catch( libutil::exceptions::ComponentInitializeException& e )
            {
                libutil::exceptions::ExceptionHandler::processBasarException(e, getLogger(), fun, __FILE__, __LINE__);
            }
            catch( basar::Exception& e )
            {
                libutil::exceptions::ExceptionHandler::processBasarException(e, getLogger(), fun, __FILE__, __LINE__);
                throw;
            }
        }

        void MainUC::prepareArticlesWithoutStock()
        {
            METHODNAME_DEF(MainUC, prepareArticlesWithoutStock)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if( false == isArticlesWithoutStockSelectionActive() )
            { 
                std::stringstream ss;
                ss << fun << ": Selection of articles without stock (article base) is not active. No further action possible.";
                throw libutil::exceptions::ComponentInitializeException(basar::ExceptInfo(fun, ss.str().c_str(), __FILE__, __LINE__));
            }

            using namespace longtermlackloader::infrastructure::accessor;
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::ARTICLES_WITHOUT_STOCK_TEMP);

            execute(longtermlack::lit::PREPARE_ARTICLES_WITHOUT_STOCK, getParameterizationYIterator()->get());

            m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_MINUEND, tables::ARTICLES_WITHOUT_STOCK_TEMP));
        }

        void MainUC::prepareArticlesWithoutStockBooking()
        {
            METHODNAME_DEF(MainUC, prepareArticlesWithoutStockBooking)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isArticlesWithoutStockBookingSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::ARTICLES_WITHOUT_STOCK_BOOKING_TEMP);

            execute(longtermlack::lit::PREPARE_ARTICLES_WITHOUT_STOCK_BOOKING, getParameterizationYIterator()->get());

            m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::ARTICLES_WITHOUT_STOCK_BOOKING_TEMP));
        }

        void MainUC::prepareArticlesReImport()
        {
            METHODNAME_DEF(MainUC, prepareArticlesReImport)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isArticlesReImportSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::ARTICLES_REIMPORT_TEMP);

            execute(longtermlack::lit::PREPARE_ARTICLES_REIMPORT, getParameterizationYIterator()->get());

            m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::ARTICLES_REIMPORT_TEMP));
        }
        
        void MainUC::logLoadStatistics() const
        {
            METHODNAME_DEF(MainUC, logLoadStatistics)
            BLOG_TRACE_METHOD(getLogger(), fun);

            //using namespace longtermlackloader::infrastructure::accessor;

            std::stringstream ss; ss << std::endl;
            ss << std::setw(60) << std::setfill('-') << "-" << std::endl;
            ss << "Load-Statistics: " << fun << std::endl;
            ss << std::setw(60) << std::setfill('-') << "-" << std::endl;
            /*-----------------------------------------------
            Load-Statistics: (fun)
            --------------------------------------------------
            ArtcilesWithoutStock:       312811
            T2:                         3356
            --------------------------------------------------*/

            LoadStatisticCollection::const_iterator it = m_LoadStatisticCollection.begin();
            for( ; it != m_LoadStatisticCollection.end(); ++it )
            {
                ss << std::setfill(' ') << std::left << std::setw(30) << it->m_Table << std::setw(30) << std::right << it->m_Hits << std::endl;
            }
            ss << std::setw(60) << std::setfill('-') << "-" << std::endl;

            getLogger().forcedLog( log4cplus::INFO_LOG_LEVEL, ss.str() );
        }

        void MainUC::saveLongTermLack()
        {
            METHODNAME_DEF(MainUC, saveLongTermLack)
            BLOG_TRACE_METHOD(getLogger(), fun);

            using namespace longtermlackloader::infrastructure::accessor; 

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(),   tables::LONG_TERM_LACK);
            getParameterizationYIterator()->get().setString(properties::SOURCE_TABLE_NAME.getName(),   tables::ARTICLES_WITHOUT_STOCK_TEMP);
            getParameterizationYIterator()->get().setInt16(properties::PERSISTENCE_STRATEGY.getName(), (true == isPersistenceStrategyTruncate() ? 1 : 0) );

            execute(longtermlack::lit::SAVE_LONG_TERM_LACK, getParameterizationYIterator()->get());
        }

        void MainUC::prepareSpecialPZNs()
        {
            METHODNAME_DEF(MainUC, prepareSpecialPZNs)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isSpecialPZNsSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::SPECIAL_PZNS_TEMP);
            
            execute(longtermlack::lit::PREPARE_SPECIAL_PZNS, getParameterizationYIterator()->get());

            m_TempTablesCollection.push_back( std::make_pair(DIFFERENCE_SUBTRAHENT, tables::SPECIAL_PZNS_TEMP) );
        }

        void MainUC::prepareReservedArticles()
        {
            METHODNAME_DEF( MainUC, prepareReservedArticles )
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isReservedArticlesSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            {
                getParameterizationYIterator()->reset();
                getParameterizationYIterator()->get().setInt16(properties::WITH_ARTICLE_RESERVATION_TYPE.getName(), longtermlack::SWITCH_OFF);
                getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::RESERVED_ARTICLES_TEMP);

                execute(longtermlack::lit::PREPARE_RESERVED_ARTICLES, getParameterizationYIterator()->get());

                m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::RESERVED_ARTICLES_TEMP));
            }

            {
                getParameterizationYIterator()->reset();
                getParameterizationYIterator()->get().setInt16(properties::WITH_ARTICLE_RESERVATION_TYPE.getName(), longtermlack::SWITCH_ON);
                getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::RESERVED_ARTICLES_WITH_TYPE_TEMP);

                execute(longtermlack::lit::PREPARE_RESERVED_ARTICLES, getParameterizationYIterator()->get());

                m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::RESERVED_ARTICLES_WITH_TYPE_TEMP));
            }
        }

        void MainUC::prepareActiveArticles()
        {
            METHODNAME_DEF(MainUC, prepareActiveArticles)
            BLOG_TRACE_METHOD(getLogger(), fun);
            
            if (false == isActiveArticlesSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setInt16(properties::ARTICLE_ACTIVE_TAG.getName(), longtermlack::ARTICLE_ACTIVE_TAG);
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::ACTIVE_ARTICLES_TEMP);

            execute(longtermlack::lit::PREPARE_ARTICLES_WITH_ACTIVATION_TAG, getParameterizationYIterator()->get());
            
            m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_NEGATIVE_SUBTRAHENT, tables::ACTIVE_ARTICLES_TEMP));
        }

        void MainUC::preparePseudoArticles()
        {
            METHODNAME_DEF(MainUC, preparePseudoArticles)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isPseudoArticlesSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            {
                getParameterizationYIterator()->reset();
                getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::PSEUDO_ARTICLES_TEMP);
                
                execute(longtermlack::lit::PREPARE_PSEUDO_ARTICLES, getParameterizationYIterator()->get());

                m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::PSEUDO_ARTICLES_TEMP));
            }

            //----
            {
                getParameterizationYIterator()->reset();
                getParameterizationYIterator()->get().setInt16(properties::ARTICLE_ACTIVE_TAG.getName(), longtermlack::ARTICLE_PSEUDO_TAG);
                getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::INACTIVE_ARTICLES_TEMP);

                execute(longtermlack::lit::PREPARE_ARTICLES_WITH_ACTIVATION_TAG, getParameterizationYIterator()->get());

                m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::INACTIVE_ARTICLES_TEMP));
            }
        }

        void MainUC::prepareSubstitutionArticlesWithStock()
        {
            METHODNAME_DEF(MainUC, prepareSubstitutionArticlesWithStock)
            BLOG_TRACE_METHOD(getLogger(), fun);

            if (false == isSubstitutionArticlesWithStockSelectionActive()) { return; }

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::SUBSTITUTION_ARTICLES_WITH_STOCK_TEMP);
            getParameterizationYIterator()->get().setString(properties::SOURCE_TABLE_NAME.getName(), tables::ARTICLES_WITHOUT_STOCK_TEMP);
            
            execute(longtermlack::lit::PREPARE_SUBSTITUTION_ARTICLES_WITH_STOCK, getParameterizationYIterator()->get());

            m_TempTablesCollection.push_back(std::make_pair(DIFFERENCE_SUBTRAHENT, tables::SUBSTITUTION_ARTICLES_WITH_STOCK_TEMP));
        }

        void MainUC::cleanUpDB()
        {
            METHODNAME_DEF(MainUC, cleanUpDB)
            BLOG_TRACE_METHOD(getLogger(), fun);

            using namespace longtermlackloader::infrastructure::accessor;

            TempTablesCollection::const_iterator it = m_TempTablesCollection.begin();
            for (; it != m_TempTablesCollection.end(); ++it)
            {
                getParameterizationYIterator()->reset();
                getParameterizationYIterator()->get().setString( properties::TARGET_TABLE_NAME.getName(), it->second );

                basar::db::aspect::ExecuteResultInfo executeResultInfo = getLongTermLackAccessor()->execute(longtermlack::lit::DISCARD_DB_TEMP_TABLE, getParameterizationYIterator()->get());
                if (executeResultInfo.hasError())
                {
                    THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, longtermlack::lit::DISCARD_DB_TEMP_TABLE, executeResultInfo)
                }
            }

            m_TempTablesCollection.clear();
        }

        void MainUC::substractArticlesFromArticlesWithoutStock()
        {
            METHODNAME_DEF(MainUC, substractArticlesFromArticlesWithoutStock)
            BLOG_TRACE_METHOD(getLogger(), fun);

            using namespace longtermlackloader::infrastructure::accessor;

            getParameterizationYIterator()->reset();
            getParameterizationYIterator()->get().setString(properties::TARGET_TABLE_NAME.getName(), tables::ARTICLES_WITHOUT_STOCK_TEMP);

            TempTablesCollection::const_iterator it = m_TempTablesCollection.begin();
            for (; it != m_TempTablesCollection.end(); ++it)
            {
                if (DIFFERENCE_MINUEND == it->first) { continue; }

                if (DIFFERENCE_NEGATIVE_SUBTRAHENT == it->first)
                {
                    getParameterizationYIterator()->get().setInt16(properties::DIFFERENCE_TYPE.getName(), libutil::flag::INT_FLAG_ON );
                } 
                else 
                {
                    getParameterizationYIterator()->get().setInt16(properties::DIFFERENCE_TYPE.getName(), libutil::flag::INT_FLAG_OFF);
                }
                getParameterizationYIterator()->get().setString(properties::SOURCE_TABLE_NAME.getName(), it->second);

                basar::db::aspect::ExecuteResultInfo executeResultInfo = getLongTermLackAccessor()->execute(longtermlack::lit::SUBSTRACT_ARTICLES_FROM_ARTICLES_BASE, getParameterizationYIterator()->get());
                if (executeResultInfo.hasError())
                {
                    THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, longtermlack::lit::SUBSTRACT_ARTICLES_FROM_ARTICLES_BASE, executeResultInfo)
                }
            }
        }

        void MainUC::injectLongTermLackAccesssor( libutil::infrastructure::accessor::IAccessorPtr longTermLackAccessor )
        {
            m_LongTermLackAccessor = longTermLackAccessor;
        }

        libutil::infrastructure::accessor::IAccessorPtr MainUC::getLongTermLackAccessor()
        {
            return m_LongTermLackAccessor;
        }

        libutil::domMod::ISearchYIteratorPtr MainUC::getParameterizationYIterator()
        {
            METHODNAME_DEF( MainUC, getParameterizationYIterator )
            BLOG_TRACE_METHOD( getLogger(), fun );

            if (NULL == m_ParameterizationYIterator.get())
            {
                m_ParameterizationYIterator = libutil::domMod::ISearchYIteratorPtr( 
                                                new libutil::domMod::SearchYIterator(properties::TARGET_TABLE_NAME.toDescriptionString()  + 
                                                                                     properties::SOURCE_TABLE_NAME.toDescriptionString()  +
                                                                                     properties::ARTICLE_ACTIVE_TAG.toDescriptionString() +
                                                                                     properties::WITH_ARTICLE_RESERVATION_TYPE.toDescriptionString() +
                                                                                     properties::DIFFERENCE_TYPE.toDescriptionString() +
                                                                                     properties::PERSISTENCE_STRATEGY.toDescriptionString()
                                                )
                                              );
            }

            return m_ParameterizationYIterator;
        }
        
        const log4cplus::Logger& MainUC::getLogger() const
        {
            METHODNAME_DEF( MainUC, getLogger )
            BLOG_TRACE_METHOD(m_Logger, fun );

            return m_Logger;
        }

        bool MainUC::isDBActionParameterSet( const basar::I18nString& parameterName ) const
        {
            METHODNAME_DEF(MainUC, isDBActionParameterSet)
            BLOG_TRACE_METHOD(getLogger(), fun);

            basar::I18nString value;
            if( getDBActionParameter()->getParameterValue(getSession()->getUser()->getAreaID(), parameterName, value) )
            {
                if (libutil::flag::STR_FLAG_ON == value)
                {
                    return true;
                }
            }

            return false;
        }

        bool MainUC::isArticlesWithoutStockSelectionActive() const //?????
        {
            METHODNAME_DEF( MainUC, isArticlesWithoutStockSelectionActive )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return isDBActionParameterSet( infrastructure::parameter::DBActionParameter::ART_WITHOUT_STOCK_SEL_ACTIVE );
        }

        bool MainUC::isSubstitutionArticlesWithStockSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::SUBS_ART_WITH_STOCK_SEL_ACTIVE);
        }
        
        bool MainUC::isPseudoArticlesSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::PSEUDO_ARTICLES_SEL_ACTIVE);
        }
        
        bool MainUC::isActiveArticlesSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::ACTIVE_ARTICLES_SEL_ACTIVE);
        }
        
        bool MainUC::isArticlesWithoutStockBookingSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::ART_WO_STCK_BOOKING_SEL_ACTIVE);
        }
        
        bool MainUC::isArticlesReImportSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::ART_REIMPORT_SEL_ACTIVE);
        }
        
        bool MainUC::isReservedArticlesSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::RESERVED_ARTICLES_SEL_ACTIVE);
        }
        
        bool MainUC::isSpecialPZNsSelectionActive() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::SPECIAL_PZNS_SEL_ACTIVE);
        }

        bool MainUC::isPersistenceStrategyTruncate() const
        {
            return isDBActionParameterSet(infrastructure::parameter::DBActionParameter::PERSISTENCE_STRATEGY);
        }
        
    } // namespace usecase
} // namespace longtermlackloader
