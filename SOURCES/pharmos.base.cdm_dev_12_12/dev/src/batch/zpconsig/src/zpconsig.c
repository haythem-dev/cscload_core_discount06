/* ---------------------------------------------------------------------- *
 *   Scope          : calculate consignment partner assignment            *
 * ---------------------------------------------------------------------- *
 *   Create Date    : 07.02.2025                                          *
 *   Author         : Thomas Arnold                                       *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.0.0.0 : zpconsig 07.02.2025";

/*!
\page page6 consignmentcalculator - calculate consignment partern assignment
________________________________________________________________________________________
\version	1.0.0.0
\date		07.02.2025
\internal
- TA: CPR-240229 create consignment partner assignment based on rules for EMRA and EURIM
\endinternal

*/

/* --------- Includes -------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libscsvoodoo.h>
#include <phodate.h>
#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <zartikel.h>
#include <eklibs/sqltabs/tabsqld.h>
#include "logfile.h"

/* ----------- data structs ----------------*/
typedef struct
{
    long ARTICLE_NO;
    long MANUFACTURER_NO;
    long CONSIGNMENT_PARTNER_NO;
    char NARCOTICS_FLAG;
    char BATCH_FLAG;
    short MED_CANABIS_CATEGORY;
    long NEW_CONSIGNMENT_PARTNER_NO;
    long CHANGED_BY_RULE_ID;
} ARTICLE_S;

typedef struct
{
    long MANUFACTURER_NO;
    long CONSIGNMENT_PARTNER_NO;
    long RULE_ID;
    long RULE_SEQUENCE;
}CONSIGN_RULE_S;

const long RULE_DO_NOTHING            = 00;
const long RULE_INCLUDE_NON_NARCOTICS = 01;
const long RULE_EXCLUDE_NARCOTICS     = 02;
const long RULE_INCLUDE_BATCH         = 03;
const long RULE_EXCLUDE_NONBATCH      = 04;
const long RULE_EXCLUDE_BATCH_CANABIS = 05;

/* ------------------ delcarations ---------------------- */
long getConfiguration(CONSIGN_RULE_S* rules, int maxrules);
int executeRule(CONSIGN_RULE_S* rule, ARTICLE_S* article);
int saveArticle(ARTICLE_S* article, long changedate);
long getCurrentDate();

static char g_database[100];
static long g_currentdate;
static int  g_simulation;
/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseDatabase()
{
    SqlExecuteImm("close database");
}

/* ------------------------------------------------------------------- */
long OpenDatabase(const char* const db, char* errmld)
{
    long s;

    char base[50];
    strcpy(base, "database ");
    strcat(base, db);

    s = SqlExecuteImm(base);
    if (s != 0)
    {
        strcpy(errmld, base);
        strcat(errmld, ": ");
        strcat(errmld, DynErrmld());
        return s;
    }

    s = SqlExecuteImm("set isolation to dirty read");
    if (s == SQL_SETISOLA_ERROR) s = 0;
    if (s != 0)
    {
        strcpy(errmld, "set isolation: ");
        strcat(errmld, DynErrmld());
        CloseDatabase();
        return s;
    }

    s = SqlExecuteImm("SET LOCK MODE TO WAIT 10");
    if (s == SQL_SETISOLA_ERROR) s = 0;
    if (s != 0)
    {
        strcat(errmld, "set lock mode: ");
        strcat(errmld, DynErrmld());
        CloseDatabase();
        return s;
    }
    return 0;
}

long parseArguments(int argc, char* argv[], char* statustxt)
{
    long ret = 0;
    char data[5000];
    memset(data, 0, sizeof(data));
    // reset the global for parameters
    memset(g_database, 0, sizeof(g_database));
    g_currentdate = getCurrentDate();
    g_simulation = 0;
    strcat(data, "started with application parameters: ");
    // parse the arguments
    for (int i = 1; i < argc; i++)
    {
        strcat(data, argv[i]);
        strcat(data, " ");
        if (strcmp(argv[i], "-db") == 0)
        {
            if ((i + 1) < argc)
            {
                i++;
                sprintf(g_database, "%s", argv[i]);
                strcat(data, argv[i]);
                strcat(data, " ");
            }
        }
        else if (strcmp(argv[i], "-date") == 0)
        {
            if ((i + 1) < argc)
            {
                i++;
                g_currentdate = atol(argv[i]);
                strcat(data, argv[i]);
                strcat(data, " ");
            }
        }
        else if (strcmp(argv[i], "-sim") == 0)
        {
            if ((i + 1) < argc)
            {
                i++;
                if (strcmp(argv[i], "yes") == 0)
                {
                    g_simulation = 1;
                }
                strcat(data, argv[i]);
                strcat(data, " ");
            }
        }
    }
    write_logfile(S_INFO, "parseArguments", data);
    if (strcmp(g_database, "") == 0)
    {
        // no db set, this is mandatory
        sprintf(statustxt, "No database parameter given, application cannot be started!");
        ret = 1;
    }
    return ret;
}

/* ---------------------------------------------------------------------- */
long executeConsignmentCalculator( int argc, char *argv[], char *buf)
{
    long s = 0;
    char sql[500];
    int fd_articlecursor;
    char data[5000];

    if ((s = OpenDatabase(g_database, buf)) == 0)
    {
        CONSIGN_RULE_S rules[1000];
        long rulecount = getConfiguration(rules, 1000);
        long currule = 0;
        long lastmanufacturer = 0;
        while (currule < rulecount)
        {
            // scan valid configurations, these are ordered by manufacturer no, so run for each manufacturer
            long manufacturer = rules[currule].MANUFACTURER_NO;
            if ((manufacturer > 0) && (lastmanufacturer != manufacturer))
            {
                long articlecount = 0;
                long articlechanged = 0;
                sprintf(data,"Start checking articles with manufacturer %ld...", manufacturer);
                write_logfile(S_INFO, "executeConsignmentCalculator", data);
                // scan now all articles from this manufacturer
                sprintf(sql, "SELECT artikel_nr, hersteller_nr, konsig_partner_nr, btm, chargenartikel, med_cannabis_ges from zartikel where hersteller_nr=%ld order by artikel_nr", manufacturer);
                s = SqlOpenCsWh(&fd_articlecursor, sql);
                while (s == 0)
                {
                    ARTICLE_S articleBuf;
                    s = SqlFetch(fd_articlecursor, 1, &articleBuf.ARTICLE_NO, &articleBuf.MANUFACTURER_NO, &articleBuf.CONSIGNMENT_PARTNER_NO, 
                                                      &articleBuf.NARCOTICS_FLAG, &articleBuf.BATCH_FLAG, &articleBuf.MED_CANABIS_CATEGORY, NULL);
                    if (s == 0)
                    {
                        articlecount++;
                        // set change values to current
                        articleBuf.NEW_CONSIGNMENT_PARTNER_NO = articleBuf.CONSIGNMENT_PARTNER_NO;
                        articleBuf.CHANGED_BY_RULE_ID = RULE_DO_NOTHING;
                        // verify all rules for this manufacturer
                        int rule = currule;
                        while ((rule < rulecount) && (rules[rule].MANUFACTURER_NO == manufacturer))
                        {
                            executeRule(&rules[rule], &articleBuf);
                            rule++;
                        }
                        if ((articleBuf.NEW_CONSIGNMENT_PARTNER_NO != articleBuf.CONSIGNMENT_PARTNER_NO) && (articleBuf.CHANGED_BY_RULE_ID > RULE_DO_NOTHING))
                        {
                            sprintf(data, "Article %ld has changed consignment partner from %ld to %ld by rule %d", articleBuf.ARTICLE_NO, articleBuf.CONSIGNMENT_PARTNER_NO, articleBuf.NEW_CONSIGNMENT_PARTNER_NO, articleBuf.CHANGED_BY_RULE_ID);
                            write_logfile(S_INFO, "executeConsignmentCalculator", data);
                            if (g_simulation == 0)
                            {
                                // save article changed consignment partner
                                if (saveArticle(&articleBuf, g_currentdate) == 0)
                                {
                                    articlechanged++;
                                }
                            }
                        }
                    }
                }
                SqlCloseCs(fd_articlecursor);
                sprintf(data, "Found %ld articles and changed %ld articles for the manufacturer %ld", articlecount, articlechanged, manufacturer);
                write_logfile(S_INFO, "executeConsignmentCalculator", data);
                lastmanufacturer = manufacturer;
            }
            currule++;
        }
        CloseDatabase();
    }
    if (s == 100)
    {
        // nothing found, is also okay
        s = 0;
    }
    if (s == 0)
    {
        write_logfile(S_INFO, "executeConsignmentCalculator", "consignmentpartner verification done");
    }
    return s;
}

long getConfiguration(CONSIGN_RULE_S* rules, int maxrules)
{
    long rulecount = 0;

    int status = 0;
    char sql[500];
    char data[5000];
    char ruletext[100];
    int fd_rulecursor;
    sprintf(sql, "SELECT c.manufacturer_no, h.konsig_partner_nr, c.rule_id, c.rule_sequence FROM cconsignmentrules c, herstel h WHERE c.manufacturer_no = h.hersteller_nr ORDER BY c.manufacturer_no, c.rule_sequence");
    status = SqlOpenCs(&fd_rulecursor, sql);
    while ((status == 0) && (rulecount < maxrules))
    {
        CONSIGN_RULE_S ruleBuf;
        status = SqlFetch(fd_rulecursor, 1, &ruleBuf.MANUFACTURER_NO, &ruleBuf.CONSIGNMENT_PARTNER_NO,
                                            &ruleBuf.RULE_ID, &ruleBuf.RULE_SEQUENCE, NULL);
        if (status == 0)
        {
            memcpy(&rules[rulecount],&ruleBuf,sizeof(CONSIGN_RULE_S));
	    // map rule id to text
            sprintf(ruletext,"RULE_UNKNOWN");

            if (rules[rulecount].RULE_ID == RULE_DO_NOTHING)
            {
                sprintf(ruletext,"RULE_DO_NOTHING");
            }
            else if (rules[rulecount].RULE_ID == RULE_INCLUDE_NON_NARCOTICS)
            {
                sprintf(ruletext,"RULE_INCLUDE_NON_NARCOTICS");
            }
            else if (rules[rulecount].RULE_ID == RULE_EXCLUDE_NARCOTICS)
            {
                sprintf(ruletext,"RULE_EXCLUDE_NARCOTICS");
            }
            else if (rules[rulecount].RULE_ID == RULE_INCLUDE_BATCH)
            {
                sprintf(ruletext,"RULE_INCLUDE_BATCH");
            }
            else if (rules[rulecount].RULE_ID == RULE_EXCLUDE_NONBATCH)
            {
                sprintf(ruletext,"RULE_EXCLUDE_NONBATCH");
            }
            else if (rules[rulecount].RULE_ID == RULE_EXCLUDE_BATCH_CANABIS)
            {
                sprintf(ruletext,"RULE_EXCLUDE_BATCH_CANABIS");
            }
            sprintf(data, "Found rule for manufacturer %ld (consignment partner %ld): rule id %d(%s) with rule order sequence %d", rules[rulecount].MANUFACTURER_NO, rules[rulecount].CONSIGNMENT_PARTNER_NO, rules[rulecount].RULE_ID, ruletext, rules[rulecount].RULE_SEQUENCE);
            write_logfile(S_INFO, "getConfiguration", data);
            rulecount++;
        }
    }
    SqlCloseCs(fd_rulecursor);

    /*
    if (rules != NULL)
    {
        // simulate for now, need to be read from DB
        // EMRA excludes narcotics only
        rules[0].MANUFACTURER_NO = 7741;
        rules[0].CONSIGNMENT_PARTNER_NO = 7741;
        rules[0].RULE_ID = RULE_EXCLUDE_NARCOTICS;
        rules[0].RULE_SEQUENCE = 1;
        // so 1 rules are defined
        rulecount = 1;
    }
    */
    return rulecount;
}

int executeRule(CONSIGN_RULE_S *rule, ARTICLE_S *article)
{
    int ret = 0;
 
    if ((rule == NULL) || (article == NULL))
    {
        return ret;
    }
    if (rule->RULE_ID == RULE_EXCLUDE_NARCOTICS)
    {
        // by this rule, in case of narcotics is set, remove the consignment partner
        if (article->NARCOTICS_FLAG == '1')
        {
            if ((article->CONSIGNMENT_PARTNER_NO > 0) || (article->NEW_CONSIGNMENT_PARTNER_NO > 0))
            {
                article->NEW_CONSIGNMENT_PARTNER_NO = 0;
                article->CHANGED_BY_RULE_ID = rule->RULE_ID;
            }
        }
    }
    else if (rule->RULE_ID == RULE_INCLUDE_NON_NARCOTICS)
    {
        // by this rule, in case of narcotics is not set, add the consignment partner from the manufacturer
        if (article->NARCOTICS_FLAG != '1')
        {
            if ((article->CONSIGNMENT_PARTNER_NO != rule->CONSIGNMENT_PARTNER_NO) || (article->NEW_CONSIGNMENT_PARTNER_NO != rule->CONSIGNMENT_PARTNER_NO))
            {
                article->NEW_CONSIGNMENT_PARTNER_NO = rule->CONSIGNMENT_PARTNER_NO;
                article->CHANGED_BY_RULE_ID = rule->RULE_ID;
            }
        }
    }
    else if (rule->RULE_ID == RULE_EXCLUDE_NONBATCH)
    {
        // by this rule, in case of batch is not set, remove the consignment partner 
        if (article->BATCH_FLAG != '1')
        {
            if ((article->CONSIGNMENT_PARTNER_NO > 0) || (article->NEW_CONSIGNMENT_PARTNER_NO > 0))
            {
                article->NEW_CONSIGNMENT_PARTNER_NO = 0;
                article->CHANGED_BY_RULE_ID = rule->RULE_ID;
            }
        }
    }
    else if (rule->RULE_ID == RULE_EXCLUDE_BATCH_CANABIS)
    {
        // by this rule, in case of canabis, the batch flag is set even the article should be handled like a nonbatch, so remove the consignment partner
        if ((article->BATCH_FLAG == '1') && ((article->MED_CANABIS_CATEGORY == 1) || (article->MED_CANABIS_CATEGORY == 2)))
        {
            if ((article->CONSIGNMENT_PARTNER_NO > 0) || (article->NEW_CONSIGNMENT_PARTNER_NO > 0))
            {
                article->NEW_CONSIGNMENT_PARTNER_NO = 0;
                article->CHANGED_BY_RULE_ID = rule->RULE_ID;
            }
        }
    }
    else if (rule->RULE_ID == RULE_INCLUDE_BATCH)
    {
        // by this rule, in case of batch is set, add the consignment partner from the manufacturer
        if (article->BATCH_FLAG != '1')
        {
            article->NEW_CONSIGNMENT_PARTNER_NO = rule->CONSIGNMENT_PARTNER_NO;
            article->CHANGED_BY_RULE_ID = rule->RULE_ID;
        }
    }

    return ret;
}

int saveArticle(ARTICLE_S *article, long changedate)
{
    int status = 0, fullstatus = 0;
    char sql[500];
    long dummy;
    int fd_zartikel = -1;
    char errtxt[1000];
    char PK[100];
    sprintf(PK, "ARTIKEL_NR=%07ld", article->ARTICLE_NO);
    struct ZARTIKEL	BufZArtikelOld;
    struct ZARTIKEL	BufZArtikelAct;
    static char  zartikelTab[] = "zartikel";
    static void* zartikelDesc = NULL;

    // load original zartikel data for protocol
    if (OpenBufferDesc(&fd_zartikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errtxt) == 0)
    {
        // read full previous values from zartikel for this article
        fullstatus = FdReadRecord(fd_zartikel, PK, &BufZArtikelOld, errtxt);
        // read full description of zartikel
        fullstatus += SqlGetTabDesc(zartikelTab, &zartikelDesc, DESC_DEFAULT, errtxt);
        // done, so everything prepared for writing change protocol
        CloseOneBufferDesc(fd_zartikel);

        // save the article
        sprintf(sql, "UPDATE zartikel SET konsig_partner_nr=%ld WHERE artikel_nr=%ld", article->NEW_CONSIGNMENT_PARTNER_NO, article->ARTICLE_NO);
        status = SqlExecuteImm(sql);
        if (status == 0)
        {
            // add the trigger for updating an article
            sprintf(sql, "select datum from zapflege where artikel_nr = %ld and datum = %ld", article->ARTICLE_NO, changedate);
            status = SqlRead(sql, &dummy, NULL);

            if (status == 100)
            {
                sprintf(sql, "insert into zapflege ( artikel_nr, datum ) values ( %ld, %ld )", article->ARTICLE_NO, changedate);
                status = SqlExecuteImm(sql);
            }
            // save the change in protocol by taking over the buffers of zartikel and changing the consignment partner
            if (fullstatus == 0)
            {
                memcpy(&BufZArtikelAct, &BufZArtikelOld, sizeof(BufZArtikelOld));
                BufZArtikelAct.KONSIG_PARTNER_NR = article->NEW_CONSIGNMENT_PARTNER_NO;
                status = Insert_Protokoll(P_UPDATE, V_PROTO_VERTEIL, zartikelDesc, &BufZArtikelOld, &BufZArtikelAct, PK, "zpconsig", "", 0, errtxt);
            }
        }
    }
    return status;
}

long getCurrentDate()
{
    char datename[32];
    struct tm* to;
    time_t t;
    t = time(NULL);
    to = localtime(&t);
    strftime(datename, sizeof(datename), "%Y%m%d", to);

    return atol(datename);
}