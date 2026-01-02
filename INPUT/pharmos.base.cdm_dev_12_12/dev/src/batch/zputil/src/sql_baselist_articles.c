/* ------------------------------------------------------------- *
 * Requirement : SQL functions on base list articles mass upload *
 * ------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "libscsvoodoo/libscsvoodoo.h"
#include "voodoo_table_header/pflege.h"

#include "eklibs/wdbups/wpp_dbas.h"
#include "eklibs/wdbups/wpp_prot.h"
#include "eklibs/sqltabs/tabsqld.h"
#include "hdatum/phodate.h"
#include "hdatum/phozeit.h"
#include "util_form.h"

#include "sql_zputil.h"
#include "sql_baselist_articles.h"

struct CBASELISTARTICLES m_BufOldCBaseListArticles;
struct CBASELISTARTICLES BufCBaseListArticles;

/*
 * How much string space for details on
 * - invalid baselist IDs
 * - invalid article nos
 * ?
 */
#define DETAILS_LEN 600

/*
 * The context for the base list articles maintenance,
 * tracking any validation errors included
 */
typedef struct baselist_article_context {
  int               current_input_line;
  char              theID; /* the one and only baselist ID in the input */
  int               articles_inserted;
  int               articles_updated;
  long              current_article_no;
  int               record_is_validated; 
  int               invalid_baselist_id;
  int               invalid_pzns;          /* no valid article code */
  char*             invalid_baselist_id_details;
  char*             invalid_pzn_details;
  char*             valid_baselist_ids;    /* a subset of 'A'..'Z' w/o 'J' and 'N' */
} baselist_article_context_t;

baselist_article_context_t* bl_articles_ctx;

long allocate_baselist_article_context(char* errmld);
void release_baselist_article_context();
long fetch_baselist_ids(char* errmld);
int  validate_baselist_record(char baselist_id, long article_no, char* errmld);
void baselist_clean_id();

long allocate_baselist_article_context(char* errmld)
{
  /*
  ** pre-requisite: DB connection has been established
  */
  long answer = 0L;
  
  if(bl_articles_ctx != NULL) {
    /* has been called before => we're already good to go */
    return answer;
  }
  
  bl_articles_ctx = malloc(sizeof(baselist_article_context_t));
  memset(bl_articles_ctx, 0, sizeof(baselist_article_context_t));

  bl_articles_ctx->invalid_baselist_id_details = malloc(DETAILS_LEN * sizeof(char));
  memset(bl_articles_ctx->invalid_baselist_id_details, 0, DETAILS_LEN * sizeof(char));

  bl_articles_ctx->invalid_pzn_details = malloc(DETAILS_LEN * sizeof(char));
  memset(bl_articles_ctx->invalid_pzn_details, 0, DETAILS_LEN * sizeof(char));
  
  return fetch_baselist_ids(errmld);
}

void release_baselist_article_context()
{
  if(bl_articles_ctx) {
    if(bl_articles_ctx->valid_baselist_ids) {
      free(bl_articles_ctx->valid_baselist_ids);
    }
    
    if(bl_articles_ctx->invalid_baselist_id_details) {
      free(bl_articles_ctx->invalid_baselist_id_details);
    }
    
    if(bl_articles_ctx->invalid_pzn_details) {
      free(bl_articles_ctx->invalid_pzn_details);
    }
    
    free(bl_articles_ctx);
    bl_articles_ctx = NULL;
  }
}

/* ------------------------------------------------------------------- */
long sel_cbaselistarticles(const int *Fd_CBaseListArticles, char* baselist_id, char* articleno, char* errmld)
{
	long lStatus;
	char where_clause[100] = {0};
	
	if (*Fd_CBaseListArticles < 0 || 0L != allocate_baselist_article_context(errmld)) {
	  return -1L;
	}

	/*
	** For every upload record of base list articles, this function will be called
	** firstly and validate its entries prior to any insert/update thereafter.
	*/
	
	/* check if article base list ID have been prepared */
	if(NULL == bl_articles_ctx || NULL == bl_articles_ctx->valid_baselist_ids) {
	  strcpy(errmld, "base list article context is missing, cannot validate on update");
	  return -1L;
	}

	/* validate, and map current article no. to bl_articles_ctx->current_pzn if possible */
	bl_articles_ctx->record_is_validated = validate_baselist_record(*baselist_id, atol(articleno), errmld);
	
	if(!bl_articles_ctx->record_is_validated) {
	  /* skip article because it fails validation */
	  return 0L;
	}

	sprintf(where_clause, "baselist_id='%c' AND articleno=%ld", *baselist_id, bl_articles_ctx->current_article_no);

	lStatus = FdReadRecord(*Fd_CBaseListArticles, where_clause, &m_BufOldCBaseListArticles, errmld);
	
	if (0L != lStatus && 100L != lStatus) {
	  sprintf(errmld,
		  "cbaselistarticles (Searching baselist_id '%c', articleno: %ld): %s",
		  *baselist_id, bl_articles_ctx->current_article_no, DynErrmld());
	  
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
long upd_cbaselistarticles(const int *Fd_CBaseListArticles, char* errmld)
{
	long lStatus = 0;
	char sql[150] = {0};
	char upd_section[100] = {0};
	char current_blid=upd_values[1][0];
	
	if(!bl_articles_ctx->record_is_validated) {
	  /* this records is bad, so do not update it */
	  return 0L;
	}

	if (*Fd_CBaseListArticles < 0 || 0 != fill_upd_section(upd_section)) {
	  return -1;
	}

	sprintf(sql,
		"UPDATE cbaselistarticles %s "
		"WHERE baselist_id = '%c' AND articleno=%ld",
		upd_section, current_blid, bl_articles_ctx->current_article_no);

	lStatus = SqlExecuteImm(sql);
	
	if (lStatus != 0L)
	{
	  sprintf(errmld,
		  "cbaselistarticles (single row update ['%c', %ld]): %s",
		  current_blid, bl_articles_ctx->current_article_no, DynErrmld());
	}
	else
	{
	  char where_clause[100] = {0};
	  
	  bl_articles_ctx->articles_updated++;
	  WriteProtZeile(fd_prot);
	  
	  sprintf(where_clause, "baselist_id='%c' AND articleno=%ld", current_blid, bl_articles_ctx->current_article_no);
	  
	  FdReadRecord(*Fd_CBaseListArticles, where_clause, &BufCBaseListArticles, errmld);

	  if (memcmp(&BufCBaseListArticles, &m_BufOldCBaseListArticles, sizeof(m_BufOldCBaseListArticles)) != 0)
	    {
	      /* Insert into zpznpflege for article update */
	      lStatus = WritePznPflege(bl_articles_ctx->current_article_no, "03", tages_datum, errmld);
	    }
	}

	return lStatus;
}

void baselist_clean_id()
{
  char		sql[100] = { 0 };
  char*		errmld = NULL;
  long		lStatus = 0L;
  int		fd;
  struct	CBASELISTARTICLES article = { 0 };

  // Fetch all articles for the given baselist_id
  snprintf(sql, sizeof(sql) - 1,
	  "SELECT BASELIST_ID, ARTICLENO FROM cbaselistarticles "
	  "WHERE baselist_id='%c'",
	  bl_articles_ctx->theID);

  lStatus = SqlOpenCs(&fd, sql);
  if (0L != lStatus) {
	  strcat(errmld, DynErrmld());
	  return;
  }

  // Iterate over all articles and store all in zpznpflege
  while (0L == SqlFetch(fd, 1, &article, NULL)) {
	  WritePznPflege(article.ARTICLENO, "03", tages_datum, errmld);
  }

  SqlCloseCs(fd);
  memset(sql, 0, sizeof(sql));

  // Delete all articles for the given baselist_id
  snprintf(sql, sizeof(sql)-1,
	   "DELETE FROM cbaselistarticles "
	   "WHERE baselist_id='%c'",
	   bl_articles_ctx->theID);
  
  SqlExecuteImm(sql);
}

int validate_baselist_id(char baselist_id)
{
  /* check I: matches a character that is permitted */
  int validated = NULL != strchr(bl_articles_ctx->valid_baselist_ids, baselist_id);

  if(validated) {
    if('\0' == bl_articles_ctx->theID) {
      bl_articles_ctx->theID = baselist_id;
      /* full upload always -> clean ID */
      baselist_clean_id();
    }
    
    /* check II: there can only be one in the input */
    validated = baselist_id == bl_articles_ctx->theID;
  }
  
  return validated;
}

int validate_baselist_record(char baselist_id, long article_no, char* errmld)
{
  int  validated  = validate_baselist_id(baselist_id);
  char buf[20] = { 0 };
  
  bl_articles_ctx->current_article_no = article_no;

  /* Skip ZdpUtil header line when advancing current line no. */
  bl_articles_ctx->current_input_line += (bl_articles_ctx->current_input_line == 0 ? 2 : 1);

  if(validated && article_no < 0) {
    /*
     * ZdpUtil sends negative article numbers when the article code does not exist.
     * Put that into protocol, if there is enough room still.
     */
    if(strlen(bl_articles_ctx->invalid_pzn_details) + 18 < DETAILS_LEN) {  
      snprintf(buf, sizeof(buf)-1, "#%d:%ld ",
	       bl_articles_ctx->current_input_line,
	       article_no < 0 ? -article_no : article_no);
      strcat(bl_articles_ctx->invalid_pzn_details, buf);
    }

    bl_articles_ctx->invalid_pzns++;
  } else if(!validated) {
    /* skip article because of invalid base list id */
    bl_articles_ctx->invalid_baselist_id++;
    
    if(strlen(bl_articles_ctx->invalid_baselist_id_details) + 12 < DETAILS_LEN) {
      snprintf(buf, sizeof(buf)-1, "#%d:'%c' ", bl_articles_ctx->current_input_line, baselist_id);
      strcat(bl_articles_ctx->invalid_baselist_id_details, buf);
    }
  }
  
  return validated && article_no > 0;
}

/* ------------------------------------------------------------------- */
long ins_cbaselistarticles(const int *Fd_CBaseListArticles, char* errmld)
{
	long lStatus = 0L;
	char sql[250] = {0};
	char ins_section_fields[100] = {0};
	char ins_section_values[100] = {0};
	char current_blid=upd_values[1][0];

	if(!bl_articles_ctx->record_is_validated) {
	  /* this records is bad, so do not insert it */
	  return 0L;
	}
	
	if (*Fd_CBaseListArticles < 0) {
	  return -1L;
	}

	if (fill_ins_section(ins_section_fields, ins_section_values) != 0) {
	  return -1L;
	}

	sprintf(sql,
		"INSERT INTO cbaselistarticles (%s, articleno)"
		" VALUES ('%c', %ld) ",
		ins_section_fields, current_blid, bl_articles_ctx->current_article_no);

	lStatus = SqlExecuteImm(sql);

	if (0L != lStatus) {
	  sprintf(errmld,
		  "cbaselistarticles (single row update ['%c', %ld]): %s",
		  current_blid, bl_articles_ctx->current_article_no, DynErrmld());
	} else {
	  bl_articles_ctx->articles_inserted++;
	  WriteProtZeile(fd_prot);
	  
	  /* Insert into zpznpflege for article insert */
	  lStatus = WritePznPflege(bl_articles_ctx->current_article_no, "03", tages_datum, errmld);
	}

	return lStatus;
}

long fetch_baselist_ids(char* errmld)
{
  long             lStatus = 0L, total_ids;
  int              fd;
  /* seems that fetching into a long value requires the cast below: */
  char*            sql0 = "SELECT CAST(COUNT(*) AS INTEGER) FROM cbaselist";
  char*            sql1 = "SELECT baselist_id FROM cbaselist";
  struct CBASELIST cbl = { 0 };

  if(bl_articles_ctx->valid_baselist_ids) {
    free(bl_articles_ctx->valid_baselist_ids);
    bl_articles_ctx->valid_baselist_ids= NULL;
  }
  
  lStatus = SqlOpenCs( &fd, sql0 );
  if (0L != lStatus) {
    strcat( errmld, DynErrmld() );
    return lStatus;
  }

  lStatus = SqlFetch(fd, 1, &total_ids, NULL);
  if(0L != lStatus || 0L == total_ids) {
    return lStatus;
  }
  
  SqlCloseCs(fd);
  total_ids++; /* one more for '\0' */
  
  lStatus = SqlOpenCs( &fd, sql1 );
  if (0L != lStatus) {
    strcat( errmld, DynErrmld() );
    return lStatus;
  }

  bl_articles_ctx->valid_baselist_ids = malloc(total_ids * sizeof(char));
  memset(bl_articles_ctx->valid_baselist_ids, 0, total_ids * sizeof(char));
  
  for(char* c=bl_articles_ctx->valid_baselist_ids; 0L == lStatus; c++) {
    lStatus = SqlFetch(fd, 1, &cbl, NULL);

    /* remember next base list ID */
    if(0L == lStatus) {
      *c=cbl.BASELIST_ID[0];
    }
  }

  SqlCloseCs(fd);
  return 0L;
}

void baselist_article_import_summary(char* errmld) {

  char        buf0[DETAILS_LEN + 5] = { 0 };
  char        buf1[DETAILS_LEN + 5] = { 0 };
  const char* toBeOrNotToBe = baselist_upload_requires_rollback() ? "waeren" : "sind";

  if(bl_articles_ctx->invalid_baselist_id > 0) {
    sprintf(buf0, "( %s)\n", bl_articles_ctx->invalid_baselist_id_details);
  }
  
  if(bl_articles_ctx->invalid_pzns > 0) {
    sprintf(buf1, "\n( %s)", bl_articles_ctx->invalid_pzn_details);
  }
  
  sprintf(errmld,
	  "%d Saetze %s aktualisiert worden.\n"
	  "%d Saetze %s eingefuegt worden.\n"
	  "%d Saetze hatten eine ungueltige Basislisten-ID.\n%s"
	  "%d Saetze hatten einen ungueltigen Artikel-Code.%s",
	  bl_articles_ctx->articles_updated,
	  toBeOrNotToBe,
	  bl_articles_ctx->articles_inserted,
	  toBeOrNotToBe,
	  bl_articles_ctx->invalid_baselist_id,
	  buf0,
	  bl_articles_ctx->invalid_pzns,
	  buf1);

  /* We're done */
  if(baselist_upload_requires_rollback()) {
    SqlRollbackWork();
  } else {
    SqlCommitWork();
  }
  
  release_baselist_article_context();
}
  
int baselist_upload_requires_rollback()
{
  return bl_articles_ctx->invalid_baselist_id > 0 || bl_articles_ctx->invalid_pzns > 0;
}
