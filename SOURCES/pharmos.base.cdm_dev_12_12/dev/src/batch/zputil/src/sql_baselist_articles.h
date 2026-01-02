#ifndef _SQL_BASELIST_ARTICLES_H_
#define _SQL_BASELIST_ARTICLES_H_

#include "voodoo_table_header/cbaselist.h"
#include "voodoo_table_header/cbaselistarticles.h"

long sel_cbaselistarticles(const int* Fd_CBaseListArticles, char* baselist_id, char* articleno, char* errmld);
long upd_cbaselistarticles(const int* Fd_CBaseListArticles, char* errmld);
long ins_cbaselistarticles(const int* Fd_CBaseListArticles, char* errmld);
int  baselist_upload_requires_rollback();
void baselist_article_import_summary(char* errmld);

#endif /* _SQL_BASELIST_ARTICLES_H_ */
