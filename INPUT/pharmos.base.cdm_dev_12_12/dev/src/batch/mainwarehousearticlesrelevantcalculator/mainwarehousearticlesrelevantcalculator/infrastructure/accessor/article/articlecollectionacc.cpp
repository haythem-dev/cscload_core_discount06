//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/article/articlecollectionacc.h"
#include "infrastructure/accessor/article/articlecollectionacc_definitions.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
namespace article
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::ARTICLE_COLLECTION_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::ARTICLE_LOCKED_FLAG         )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::ARTICLE_NO                  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BATCH_FLAG                  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO                   )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CENTRALPURCHASE_LOCKED_FLAG )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CONSIGNMENT_PARTNER_NO      )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::COOL_ARTICLE_MODE           )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CREATION_DATE               )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::HAZARDOUS_SUBSTANCE_OLD     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::HAZARDOUS_SUBSTANCE_NEW     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::IBT_RELEVANT_COUNT          )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::MANUAL_SIGNED_ZDP           )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::NARCOTIC_FLAG               )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::OUTSALE_DATE                )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PREVIOUS_RELEVANCE_FLAG     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PROGNOSIS                   )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PURCHASING_PRICE            )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::REGISTRABLE_FLAG            )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SEASON_GROUP_1              )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SEASON_GROUP_2              )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SEASON_GROUP_3              )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SPECIAL_ARTICLE_TYPE        )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::STORAGE_LOCATION            )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::STORAGE_LOCATION_MAINWH     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::UN_NO                       )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::UNDERDELIVERYQUOTA_LIMIT	   )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::UNDERDELIVERYQUOTA_VAL	   )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::REGIONALARTICLE_FLAG		   )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::STAMMLAGER_FLAG			   )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::ADMISSION_PARAM_GROUPID     )
            END_PROPERTY_DESCRIPTION_LIST

            ACCESS_METHOD( lit::SELECT_LAST_PROGNOSIS_DATE )
                SQL_BUILDER_CREATE   ( SelectLastPrognosisDate )
                SQL_BUILDER_PUSH_BACK( SelectLastPrognosisDate )
            
            ACCESS_METHOD( lit::SELECT_ARTICLE_COLLECTION )
                SQL_BUILDER_CREATE   ( SelectArticleCollection )
                SQL_BUILDER_PUSH_BACK( SelectArticleCollection )

            ACCESS_METHOD(lit::SELECT_COUNT_ARTICLE_COLLECTION)
                SQL_BUILDER_CREATE(SelectCountArticleCollection)
                SQL_BUILDER_PUSH_BACK(SelectCountArticleCollection)

        END_ACCESSOR_DEFINITION


        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectLastPrognosisDate )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectLastPrognosisDate )

        ENSURE_PROPERTIES_ARE_SET( SelectLastPrognosisDate, properties::BRANCH_NO.toPropertyString() )

        void SelectLastPrognosisDate::buildSQLString()
        {
            static const basar::VarString sqlStatement(
                "SELECT MAX (datum) "
                "FROM artprog "
                "WHERE filialnr = "                                                  + properties::BRANCH_NO.toSQLReplacementString() +
                " AND artikel_nr = "
				"(SELECT * FROM "
                "(SELECT FIRST 1 artikel_nr FROM artikelf WHERE filialnr = "         + properties::BRANCH_NO.toSQLReplacementString() +
				" AND artikelaktiv = 1) )"
            );

            resolve( sqlStatement );
            BLOG_TRACE_SQLSTRING( LoggerPool::getLoggerAccessors() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectCountArticleCollection )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION(SelectCountArticleCollection)

        bool SelectCountArticleCollection::isExecutable() const
        {
            METHODNAME_DEF(SelectCountArticleCollection, isExecutable);
            static const log4cplus::Logger& logger = LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD(logger, fun);

            const bool executable = arePropertiesSet(properties::BRANCH_NO.toPropertyString() +
                properties::BRANCH_NO_MAINWAREHOUSE.toPropertyString()
            );

            CHECK_EXECUTABILITY(getPropertyList(), logger, fun);
            return executable;
        }

        void SelectCountArticleCollection::buildSQLString()
        {
            static const basar::VarString sqlStatement(
                "SELECT CAST(count(*) as INTEGER) "
                "FROM zartikel z "
                "JOIN artikelf f ON z.artikel_nr = f.artikel_nr "
                "LEFT JOIN artikelf f2 on z.artikel_nr = f2.artikel_nr AND f2.filialnr = " + properties::BRANCH_NO_MAINWAREHOUSE.toSQLReplacementString() + " "
                "WHERE f.filialnr = " + properties::BRANCH_NO.toSQLReplacementString() + " "
                //"AND z.artikel_nr > 5000 AND z.artikel_nr < 10000" // for testing
            );

            resolve(sqlStatement);
            BLOG_TRACE_SQLSTRING(LoggerPool::getLoggerAccessors());
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectArticleCollection )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectArticleCollection )

        bool SelectArticleCollection::isExecutable() const
        {
            METHODNAME_DEF( SelectArticleCollection, isExecutable );
            static const log4cplus::Logger& logger = LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString()               +
                                                      properties::BRANCH_NO_MAINWAREHOUSE.toPropertyString() +
                                                      properties::LAST_PROGNOSIS_DATE.toPropertyString()
                                                    );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectArticleCollection::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT distinct z.artikel_gesperrt AS "                                             + properties::ARTICLE_LOCKED_FLAG.getName()         +
                    ", z.artikel_nr AS "                                                    + properties::ARTICLE_NO.getName()                  +
                    ", z.chargenartikel AS "                                                + properties::BATCH_FLAG.getName()                  +
                    ", f.filialnr AS "                                                      + properties::BRANCH_NO.getName()                   +
                    ", z.zentr_eksperre AS "                                                + properties::CENTRALPURCHASE_LOCKED_FLAG.getName() +
                    ", z.konsig_partner_nr AS "                                             + properties::CONSIGNMENT_PARTNER_NO.getName()      +
                    ", z.kuehlartikel AS "                                                  + properties::COOL_ARTICLE_MODE.getName()           +
                    ", TO_DATE( CASE WHEN z.datum_anlage = 0 THEN '99991231'"
			               " ELSE TO_CHAR(z.datum_anlage) END, '%Y%m%d')::DATE AS "         + properties::CREATION_DATE.getName()               +
                    ", (SELECT COUNT(*) FROM puibtbrancharticleconfig ic "
                    "  WHERE ic.articleno = z.artikel_nr AND ibtroletypeid = 1)::INT AS "   + properties::IBT_RELEVANT_COUNT.getName()          +
                    ", z.btm AS "                                                           + properties::NARCOTIC_FLAG.getName()               +
                    ", TO_DATE( CASE WHEN z.datum_ah = 0 THEN '99991231'"
			               " ELSE TO_CHAR(z.datum_ah) END, '%Y%m%d')::DATE AS "             + properties::OUTSALE_DATE.getName()                +
                    ", NVL(p.aep, 0.0) AS "                                                 + properties::PURCHASING_PRICE.getName()            +
                    ", z.meldepfl AS "                                                      + properties::REGISTRABLE_FLAG.getName()            +
                    ", NVL(w1.warengruppe, '') AS "                                         + properties::SEASON_GROUP_1.getName()              +
                    ", NVL(w2.warengruppe, '') AS "                                         + properties::SEASON_GROUP_2.getName()              +
                    ", NVL(w3.warengruppe, '') AS "                                         + properties::SEASON_GROUP_3.getName()              +
                    ", NVL(w4.warengruppe, '') AS "                                         + properties::SPECIAL_ARTICLE_TYPE.getName()        +
                    ", f.lagerfachnr AS "                                                   + properties::STORAGE_LOCATION.getName()            +
                    ", f2.lagerfachnr AS "                                                  + properties::STORAGE_LOCATION_MAINWH.getName()     +
                    ", z.g_un_nr AS "                                                       + properties::UN_NO.getName()                       +
                    ", z.zentralppelist AS "                                                + properties::MANUAL_SIGNED_ZDP.getName()           +
                    ", CAST((z.gs_explosion + z.gs_hochentz + z.gs_umwelt + z.gs_reizend + "
                    "z.gs_aetzend + z.gs_sehrgiftig + z.gs_leichtentz + z.gs_giftig + "
                    "z.gs_gesundhsch + z.gs_brand) as smallint) AS "                        + properties::HAZARDOUS_SUBSTANCE_OLD.getName()     +
                    ", CAST(NVL(s.pictogram01_flag, 0) + NVL(s.pictogram02_flag, 0) + "
                    "NVL(s.pictogram03_flag, 0) + NVL(s.pictogram04_flag, 0) + "
                    "NVL(s.pictogram05_flag, 0) + NVL(s.pictogram06_flag, 0) + "
                    "NVL(s.pictogram07_flag, 0) + NVL(s.pictogram08_flag, 0) + "
                    "NVL(s.pictogram09_flag, 0) as smallint) AS "                           + properties::HAZARDOUS_SUBSTANCE_NEW.getName()     +
                    ", NVL(c.orderatmainwarehouseflag, -1)::SMALLINT AS "                   + properties::PREVIOUS_RELEVANCE_FLAG.getName()     +
                    ", NVL(ap.prog_s, 0) AS " 
				+ properties::PROGNOSIS.getName()                   +
				", CASE WHEN puc.relevanceflag = 1 and puc.ibtroletypeid = (select id from puibtroletype where levelabbreviation = 'R') THEN '1' ELSE '0' END AS "
				+ properties::REGIONALARTICLE_FLAG.getName()		+
				", NVL((SELECT comparevalue from pumainwarehouseassignmentparam where branchno=" + properties::BRANCH_NO_MAINWAREHOUSE.toSQLReplacementString()
				+ " and ruleid = (SELECT ruleid FROM pumainwarehouseassignmentrule where contextname = 'UNDERDELIVERYQUOTA')), 0) AS " + properties::UNDERDELIVERYQUOTA_LIMIT.getName() +
				", NVL(pq.undeliveryquota, 0) AS " + properties::UNDERDELIVERYQUOTA_VAL.getName() +
				", f.stammlagerkenz AS "													 + properties::STAMMLAGER_FLAG.getName() +
                ", NVL(c.admissionparamgroupid, 0)::SMALLINT AS " + properties::ADMISSION_PARAM_GROUPID.getName() +
                " FROM zartikel z"
                " JOIN artikelf f ON z.artikel_nr = f.artikel_nr"
                " LEFT JOIN artikelf f2 on z.artikel_nr = f2.artikel_nr AND f2.filialnr = " + properties::BRANCH_NO_MAINWAREHOUSE.toSQLReplacementString() +
                " LEFT JOIN zartwg w1 ON w1.artikel_nr = z.artikel_nr AND w1.art = '5'"
                " LEFT JOIN zartwg w2 ON w2.artikel_nr = z.artikel_nr AND w2.art = 'A'"
                " LEFT JOIN zartwg w3 ON w3.artikel_nr = z.artikel_nr AND w3.art = 'G'"
                " LEFT JOIN zartwg w4 ON w4.artikel_nr = z.artikel_nr AND w4.art = 'D'"
                " LEFT JOIN zartpreis p ON p.artikel_nr = z.artikel_nr AND p.datumgueltigab ="
                " (SELECT MAX(datumgueltigab) FROM zartpreis p2 WHERE p2.artikel_nr ="
                " p.artikel_nr AND datumgueltigab <= CAST(TO_CHAR(CURRENT, '%Y%m%d') AS integer))"
                " LEFT JOIN pumainwarehousebrancharticleconfig c ON c.branchno = f.filialnr AND c.articleno = f.artikel_nr"
				" LEFT JOIN puundeliveryquota pq ON pq.articleno = f.artikel_nr AND pq.branchno = " + properties::BRANCH_NO_MAINWAREHOUSE.toSQLReplacementString() +
				" LEFT JOIN csafetydatasheet s ON z.artikel_nr = s.articleno"
				" LEFT JOIN puibtbrancharticleconfig puc on puc.articleno = f.artikel_nr and puc.branchno = c.branchno"
                " LEFT JOIN artprog ap ON f.filialnr = ap.filialnr AND z.artikel_nr = ap.artikel_nr"
                " AND ap.datum = "                                                          + properties::LAST_PROGNOSIS_DATE.toSQLReplacementString() +
                " WHERE f.filialnr = "                                                      + properties::BRANCH_NO.toSQLReplacementString()
				//+ " AND z.artikel_nr > 5000 AND z.artikel_nr < 10000" // for testing
                + " "
            );

            resolve( constSQL );
            basar::VarString sql = getSQLString();
            BLOG_TRACE_SQLSTRING( LoggerPool::getLoggerAccessors() );
        }

} // end namespace article
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
