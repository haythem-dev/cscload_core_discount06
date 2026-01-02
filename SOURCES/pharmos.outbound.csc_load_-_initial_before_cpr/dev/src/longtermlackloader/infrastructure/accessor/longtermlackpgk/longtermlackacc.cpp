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
#include <libutil/accessor.h>
#include <libutil/util.h>

#include <libbasardbaspect_exceptions.h>

#include <infrastructure/accessor/properties_definitions.h>
#include <infrastructure/accessor/tables_definitions.h>
#include "infrastructure/accessor/longtermlackpgk/longtermlackacc.h"
#include "infrastructure/accessor/longtermlackpgk/longtermlackacc_definitions.h"

#include "loggerpool/longtermlackloader_loggerpool.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace longtermlack
            {
                //---------------------------------------------------------------------------------------------//
                // accessor definition
                //---------------------------------------------------------------------------------------------//
                BEGIN_ACCESSOR_DEFINITION( lit::LONG_TERM_LACK_ACC )
                    BEGIN_PROPERTY_DESCRIPTION_LIST
                        PROPERTY_DESCRIPTION_LIST_ADD( properties::ARTICLE_NO )
                    END_PROPERTY_DESCRIPTION_LIST

                    ACCESS_METHOD( lit::PREPARE_ARTICLES_WITHOUT_STOCK )
                        SQL_BUILDER_CREATE   ( ArticlesWithoutStockPreparer )
                        SQL_BUILDER_PUSH_BACK( ArticlesWithoutStockPreparer )

                    ACCESS_METHOD(lit::PREPARE_SUBSTITUTION_ARTICLES_WITH_STOCK)
                        SQL_BUILDER_CREATE   ( SubstitutionArticlesWithStockPreparer )
                        SQL_BUILDER_PUSH_BACK( SubstitutionArticlesWithStockPreparer )

                    ACCESS_METHOD(lit::PREPARE_PSEUDO_ARTICLES)
                        SQL_BUILDER_CREATE   ( PseudoArticlesPreparer )
                        SQL_BUILDER_PUSH_BACK( PseudoArticlesPreparer )

                    ACCESS_METHOD(lit::PREPARE_ARTICLES_WITH_ACTIVATION_TAG)
                        SQL_BUILDER_CREATE   ( ArticlesWithActivationTagPreparer )
                        SQL_BUILDER_PUSH_BACK( ArticlesWithActivationTagPreparer )

                    ACCESS_METHOD(lit::PREPARE_ARTICLES_WITHOUT_STOCK_BOOKING)
                        SQL_BUILDER_CREATE   ( ArticlesWithoutStockBookingPreparer )
                        SQL_BUILDER_PUSH_BACK( ArticlesWithoutStockBookingPreparer )

                    ACCESS_METHOD( lit::PREPARE_RESERVED_ARTICLES )
                        SQL_BUILDER_CREATE   ( ReservedArticlesPreparer )
                        SQL_BUILDER_PUSH_BACK( ReservedArticlesPreparer )

                    ACCESS_METHOD( lit::PREPARE_SPECIAL_PZNS )
                        SQL_BUILDER_CREATE   ( SpecialPZNsPreparer )
                        SQL_BUILDER_PUSH_BACK( SpecialPZNsPreparer )

                    ACCESS_METHOD(lit::PREPARE_ARTICLES_REIMPORT)
                        SQL_BUILDER_CREATE	 (ArticlesReImportPreparer)
                        SQL_BUILDER_PUSH_BACK(ArticlesReImportPreparer)

                    ACCESS_METHOD( lit::SUBSTRACT_ARTICLES_FROM_ARTICLES_BASE )
                        SQL_BUILDER_CREATE( ArticeFromArticleBaseSubstractor )
                        SQL_BUILDER_PUSH_BACK( ArticeFromArticleBaseSubstractor )

                    ACCESS_METHOD(lit::DISCARD_DB_TEMP_TABLE)
                        SQL_BUILDER_CREATE   ( DBTempTableDiscarder )
                        SQL_BUILDER_PUSH_BACK( DBTempTableDiscarder )

                    ACCESS_METHOD(lit::COUNT_DB_ROWS)
                        SQL_BUILDER_CREATE   ( DBTempTableRowsCounter )
                        SQL_BUILDER_PUSH_BACK( DBTempTableRowsCounter )

                    ACCESS_METHOD(lit::SAVE_LONG_TERM_LACK)
                        SQL_BUILDER_CREATE(LongTermLackEraser)
                        SQL_BUILDER_PUSH_BACK(LongTermLackEraser)
                        SQL_BUILDER_CREATE(LongTermLackInserter)
                        SQL_BUILDER_PUSH_BACK(LongTermLackInserter)
                    
                END_ACCESSOR_DEFINITION

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( LongTermLackEraser )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(LongTermLackEraser)
                bool LongTermLackEraser::isExecutable() const
                {
                    return arePropertiesSet(properties::TARGET_TABLE_NAME.toPropertyString() +
                                            properties::PERSISTENCE_STRATEGY.toPropertyString());
                }
                void LongTermLackEraser::buildSQLString()
                {
                    if (libutil::flag::INT_FLAG_ON == getPropertyList().getInt16(properties::PERSISTENCE_STRATEGY.getName()))
                    {
                        static const basar::VarString constSQL(
                            "TRUNCATE TABLE " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + "; "
                        );
                        resolve(constSQL);
                        return;
                    }

                    // delete from longtermlack where articleno not in(select artikel_nr from t_allZero);

                    static const basar::VarString constSQL(
                        "DELETE FROM " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + " "
                        "WHERE articleno NOT IN "
                        "( SELECT artikel_nr "
                        "  FROM " + properties::SOURCE_TABLE_NAME.toSQLReplacementString() +
                        " );"
                    );
                    
                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( LongTermLackInserter)
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(LongTermLackInserter)
                bool LongTermLackInserter::isExecutable() const
                {
                    return arePropertiesSet(properties::TARGET_TABLE_NAME.toPropertyString() +
                                            properties::SOURCE_TABLE_NAME.toPropertyString());
                }
                void LongTermLackInserter::buildSQLString()
                {
                    static const basar::VarString constSQL(
                        "INSERT INTO " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + " (articleno, messagecode, enabled) "
                        "   SELECT artikel_nr, 0, 1 "
                        "   FROM " + properties::SOURCE_TABLE_NAME.toSQLReplacementString()
                    );

                    if (libutil::flag::INT_FLAG_ON == getPropertyList().getInt16(properties::PERSISTENCE_STRATEGY.getName()))
                    {
                        resolve( constSQL + ";" );
                        return;
                    }
                    
                    resolve( constSQL + (" WHERE artikel_nr NOT IN( SELECT articleno FROM " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ");") );
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ArticeFromArticleBaseSubstractor )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION( ArticeFromArticleBaseSubstractor )
                bool ArticeFromArticleBaseSubstractor::isExecutable() const
                {
                    return arePropertiesSet( properties::TARGET_TABLE_NAME.toPropertyString() +
                                             properties::SOURCE_TABLE_NAME.toPropertyString());
                }
                void ArticeFromArticleBaseSubstractor::buildSQLString()
                {
                    //METHODNAME_DEF(ArticeFromArticleBaseSubstractor, buildSQLString);

                    if( isContainedAndSet(properties::DIFFERENCE_TYPE.getName()) )
                    {
                        if (libutil::flag::INT_FLAG_ON == getPropertyList().getInt16(properties::DIFFERENCE_TYPE.getName()))
                        {
                            static const basar::VarString constSQL(
                                "DELETE FROM " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + " "
                                "WHERE artikel_nr not in "
                                "( SELECT artikel_nr "
                                "  FROM " + properties::SOURCE_TABLE_NAME.toSQLReplacementString() +
                                ")"
                            );
                            resolve(constSQL);
                            return;
                        }
                    } 

                    static const basar::VarString constSQL(
                        "DELETE FROM " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + " "
                        "WHERE artikel_nr in "
                        "( SELECT artikel_nr "
                        "  FROM " + properties::SOURCE_TABLE_NAME.toSQLReplacementString() +
                        ")"
                    );
                    resolve(constSQL);

                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( SpecialPZNsPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION( SpecialPZNsPreparer )
                bool SpecialPZNsPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void SpecialPZNsPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(SpecialPZNsPreparer, buildSQLString);

                    static const basar::VarString constSQL(
                        "SELECT DISTINCT artikel_nr FROM "
                        "( "
                            "SELECT pznkuehlbox1 as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznkuehlbox2 as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznbtmschein as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznwerbefach2 as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznzytostatika as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznaddoncharge as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznfranko as artikel_nr FROM " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                            "UNION "
                            "SELECT pznfreightage as artikel_nr FROM  " + tables::PARA_AUFTRAG_BEARBEITUNG + " "
                        ") WHERE artikel_nr != 0 "
                        "INTO TEMP " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ";"
                    );

                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ReservedArticlesPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(ReservedArticlesPreparer)
                bool ReservedArticlesPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void ReservedArticlesPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(ReservedArticlesPreparer, buildSQLString);

                    ///////////////////////////////////////////////////////////////////////////////////
                    // const attributes
                    ///////////////////////////////////////////////////////////////////////////////////
                    static const basar::VarString constSelectSQL(
                        "SELECT DISTINCT articleno as artikel_nr "
                        "FROM  " + tables::ARTICLE_RESERVATION + " "
                        "WHERE " 
                    );
                    
                    /////////////////////////////////////////////////////////////////////////////////////////////////
                    // variable attributes
                    /////////////////////////////////////////////////////////////////////////////////////////////////
                    basar::VarString whereClauseSQL("reservedqty > 0 ");
                    basar::VarString variableSQL;
                    if (isContainedAndSet(properties::WITH_ARTICLE_RESERVATION_TYPE.getName()))
                    {
                        if (1 == getPropertyList().getInt16(properties::WITH_ARTICLE_RESERVATION_TYPE.getName()))
                        {
                            whereClauseSQL = "   ( reservtype = 0 AND reservepct = 100 AND " + whereClauseSQL + ") " + 
                                             "OR ( reservtype = 2 AND " + whereClauseSQL + ") ";
                        }
                    }
                    
                    static const basar::VarString constIntoSQL( "INTO TEMP " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ";" );

                    resolve( constSelectSQL + whereClauseSQL + constIntoSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ArticlesWithoutStockBookingPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION( ArticlesWithoutStockBookingPreparer )
                bool ArticlesWithoutStockBookingPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void ArticlesWithoutStockBookingPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(ArticlesWithoutStockBookingPreparer, buildSQLString);

                    static const basar::VarString constSQL(
                        "SELECT distinct artikel_nr "
                        "FROM " + tables::ARTIKEL_LOKAL + " "
                        "WHERE bitand(etartschalter2, 1024) != 1024 "
                        "INTO TEMP " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ";"
                    );

                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ArticlesReImport )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(ArticlesReImportPreparer)
                bool ArticlesReImportPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }

                void ArticlesReImportPreparer::buildSQLString()
                {
                    static const basar::VarString constSQL(
                        "SELECT distinct artikel_nr "
                        "FROM " + tables::ARTIKEL_REIMPORT + " "
                        "WHERE kzaktivpassiv = 1 "
                        "INTO TEMP " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ";"
                    );

                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }
                
                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ArticlesWithActivationTagPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(ArticlesWithActivationTagPreparer)
                bool ArticlesWithActivationTagPreparer::isExecutable() const
                {
                    return arePropertiesSet( properties::TARGET_TABLE_NAME.toPropertyString() +
                                             properties::ARTICLE_ACTIVE_TAG.toPropertyString());
                }
                void ArticlesWithActivationTagPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(ArticlesWithActivationTagPreparer, buildSQLString);

                    static const basar::VarString constSQL(
                        "SELECT DISTINCT artikel_nr "
                        "FROM " + tables::ARTIKEL_LOKAL + " "
                        "WHERE artikelaktiv = " + properties::ARTICLE_ACTIVE_TAG.toSQLReplacementString() + " "
                        "INTO TEMP " + properties::TARGET_TABLE_NAME.toSQLReplacementString() + ";"
                    );

                    resolve( constSQL );
                    BLOG_TRACE( longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString() );
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( PseudoArticlesPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(PseudoArticlesPreparer)
                bool PseudoArticlesPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void PseudoArticlesPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(PseudoArticlesPreparer, buildSQLString);

                    static const basar::VarString constSQL(
                        "SELECT DISTINCT artikel_nr "
                        "FROM " + tables::ARTIKEL_LOKAL + " "
                        "WHERE lagerfachnr in( '99999999', '09999999', '98000000', '99000000', '32000000' ) "
                        "AND filialnr != 27 "
                        "INTO TEMP " + getPropertyList().getString(properties::TARGET_TABLE_NAME.getName()) + ";"
                    );

                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( SubstitutionArticlesWithStockPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(SubstitutionArticlesWithStockPreparer)
                bool SubstitutionArticlesWithStockPreparer::isExecutable() const
                {
                    return arePropertiesSet( properties::TARGET_TABLE_NAME.toPropertyString() +
                                             properties::SOURCE_TABLE_NAME.toPropertyString());
                }
                void SubstitutionArticlesWithStockPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(SubstitutionArticlesWithStockPreparer, buildSQLString);

                    static const basar::VarString constSQL(
                        "SELECT DISTINCT aa.artikel_nr, sum(al.bestand) as sumBestand "
                        "FROM " + tables::ARTIKEL_ALTERNATIVE + " aa "
                        "INNER JOIN " + tables::ARTIKEL_LOKAL + " al ON al.artikel_nr = aa.artikel_nr_altern "
                        "WHERE aa.artikel_nr IN "
                        "( SELECT d.artikel_nr FROM " + getPropertyList().getString(properties::SOURCE_TABLE_NAME.getName()) + " d ) "
                        "GROUP BY aa.artikel_nr "
                        "HAVING sum(al.bestand) > 0 "
                        "INTO TEMP " + getPropertyList().getString(properties::TARGET_TABLE_NAME.getName()) + ";"
                    );

                    resolve(constSQL);
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( ArticlesWithoutStockPreparer )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(ArticlesWithoutStockPreparer)

                bool ArticlesWithoutStockPreparer::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }

                void ArticlesWithoutStockPreparer::buildSQLString()
                {
                    //METHODNAME_DEF(ArticlesWithoutStockPreparer, buildSQLString );

                    static const basar::VarString constSQL(
                        "SELECT artikel_nr, sum(bestand) as sumBestand, sum(nachfrage) as sumNachfrage "
                        "FROM " + tables::ARTIKEL_LOKAL + " "
                        "GROUP BY artikel_nr "
                        "HAVING sum(bestand) = 0 "
                        "ORDER BY 3 desc "
                        "INTO TEMP " + getPropertyList().getString(properties::TARGET_TABLE_NAME.getName()) + ";"
                    );

                    resolve( constSQL );
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( DBTempTableRowsCounter )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(DBTempTableRowsCounter)
                bool DBTempTableRowsCounter::isExecutable() const
                {
                    //METHODNAME_DEF(DBTempTableRowsCounter, isExecutable);
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void DBTempTableRowsCounter::buildSQLString()
                {
                    //METHODNAME_DEF(DBTempTableRowsCounter, buildSQLString);

                    static const basar::VarString constSQL("SELECT count(*) from ");

                    resolve(constSQL + getPropertyList().getString(properties::TARGET_TABLE_NAME.getName()) + ";");
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

                //////////////////////////////////////////////////////////////////////////////////////////
                // BUILDER_DEFINITION( DBTempTableDiscarder )
                //////////////////////////////////////////////////////////////////////////////////////////
                BUILDER_DEFINITION(DBTempTableDiscarder)
                    bool DBTempTableDiscarder::isExecutable() const
                {
                    return isContainedAndSet(properties::TARGET_TABLE_NAME.getName());
                }
                void DBTempTableDiscarder::buildSQLString()
                {
                    //METHODNAME_DEF(DBTempTableDiscarder, buildSQLString);

                    static const basar::VarString constSQL("DROP TABLE IF EXISTS ");

                    resolve(constSQL + getPropertyList().getString(properties::TARGET_TABLE_NAME.getName()) + ";");
                    BLOG_TRACE(longtermlackloader::infrastructure::LoggerPool::getLoggerDebugOutput(), getSQLString());
                }

            }
        }
    }
} 
