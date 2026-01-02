#ifndef SQL_ZPUTIL_INCLUDED
#define SQL_ZPUTIL_INCLUDED

#include "g_util.h"
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/artve.h>
#include <voodoo_table_header/cdiscount.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/zartfrance.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/zartserbia.h>
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/cdiscgrp.h>
#include <voodoo_table_header/ccpvalidityperiod.h>
#include <voodoo_table_header/carticleext.h>
#include <voodoo_table_header/zchargenrueckruf.h>
#include <voodoo_table_header/cimexblock.h>
#include <voodoo_table_header/cibt.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/csubsequentdeliverybrancharticleconfig.h>
#include <voodoo_table_header/protokol.h>
#include <voodoo_table_header/cgibatchentry.h>
#include <voodoo_table_header/cdiscgrpmem.h>
#include <voodoo_table_header/zchargenrueckruf.h>
#include <voodoo_table_header/cartcompack.h>
#include <voodoo_table_header/zaneuhei.h>
#include <voodoo_table_header/cartmedactor.h>
#include <voodoo_table_header/cmedicalactor.h>
#include "sql_baselist_articles.h"

int sel_zartikel(const int *Fd_ZArtikel, char* art_nr, char* errmld);
int sel_carticleext(const int *Fd_CArticleExt, char* art_nr, char* errmld);
int sel_zartpreis(const int *Fd_ZArtPreis, char* art_nr, char* datgueltab, char* errmld);
int sel_zartpreis_current(const int *Fd_ZArtPreis, char* art_nr, char* datgueltab, char* errmld);
int sel_zartwg(const int *Fd_ZArtWg, char* art_nr, char* art, char* errmld);
int sel_artve(const int *Fd_ArtVe, char* art_nr, char* errmld);
int sel_cdiscount(int *Fd_CDiscount, struct CDISCOUNT *cdisc, char* errmld);
int sel_count_cdiscount_to_stop(long * count, char* errmld);
int sel_count_cdiscgrp(long * count, char* errmld);
int sel_count_ccpvalperiod(long * count, char* errmld);
int sel_carticlecodes(const int *Fd_CArticleCodes, char* art_nr, char* code_type, char* errmld);
int sel_zchargenrr(const int *Fd_ZChargenRR, char* art_nr, char* batch, char* errmld);
int sel_zartfrance(const int *Fd_ZArtFrance, char* art_nr, char* errmld);
int sel_zartswitzerland(const int *Fd_ZArtSwitzerland, char* art_nr, char* errmld);
int sel_zartserbia(const int *Fd_ZArtSerbia, char* art_nr, char* errmld);
int sel_zartaustria(const int *Fd_ZArtAustria, char* art_nr, char* errmld);
int sel_cimexblock(const int *Fd_Cimexblock, char* art_nr, char* country, char* imex_mode, char* errmld);
int sel_cibt(const int *Fd_Cibt, char* art_nr, char* errmld);
int sel_ean(const int *Fd_Ean, char* art_nr, char* errmld);
int sel_csubsequentdeliverybrancharticleconfig(const int* Fd_Csubsequentdeliverybrancharticleconfig, char* art_nr, char* branch, char* errmld);
int sel_zartwg_5ag(const int* Fd_ZArtWg, char* art_nr, char* art, char* errmld);
int sel_bliesort_direkt(const int* Fd_Bliesort, char *art_nr, char *besla_nr, char* errmld);
int sel_cartmedactor(const int* Fd_Cartmedactor, char* art_nr, char* medicalactor_type, char* errmld);
int sel_cmedicalactor(const int* Fd_Cmedicalactor, char* medicalactor_id, char* errmld);

int upd_zartikel(const int *Fd_ZArtikel, char* errmld);
//int upd_zartpreis(const int *Fd_ZArtPreis, char* errmld);
int upd_zartwg(const int *Fd_ZArtWg, char* errmld);
int upd_artve(const int *Fd_ArtVe, char* errmld);
int upd_carticlecodes(const int *Fd_CArticleCodes, char* errmld);
int upd_zchargenrr(const int *Fd_ZChargenRR, char* errmld);
int upd_carticleext(const int *Fd_CArticleExt, char* errmld);
int upd_zartfrance(const int *Fd_ZArtFrance, char* errmld);
int upd_zartswitzerland(const int *Fd_ZArtSwitzerland, char* errmld);
int upd_zartserbia(const int *Fd_ZArtSerbia, char* errmld);
int upd_zartaustria(const int *Fd_ZArtAustria, char* errmld);
int upd_cibt(const int *Fd_Cibt, char* errmld);
int upd_csubsequentdeliverybrancharticleconfig(const int* Fd_Csubsequentdeliverybrancharticleconfig, char* errmld);
int upd_zartwg_5ag(const int* Fd_ZArtWg_5ag, char* errmld);
int upd_bliesort_direkt(const int* Fd_Bliesort, const int* Fd_ZANeuheit, char* errmld);

int ins_zartpreis(const int *Fd_ZArtPreis, char* errmld);
int ins_zartwg(const int *Fd_ZArtWg, char* errmld);
int ins_cimexblock(const int *Fd_Cimexblock, char* errmld);
int ins_artve(const int *Fd_ArtVe, char* errmld);
int ins_cdiscount(const int *Fd_CDiscount, struct CDISCOUNT *cdisc, char* errmld);
int ins_cdiscount_flexible(const int *Fd_CDiscount, char* errmld);
int ins_cdiscgrpmem(const int *Fd_CDiscGrpMem, char* errmld);
int ins_cdiscgrp(const int *Fd_CDiscGrp, char* errmld);
int ins_carticlecodes(const int *Fd_CArticleCodes, char* errmld);
int ins_zchargenrr(const int *Fd_ZChargenRR, char* errmld);
int ins_carticleext(const int *Fd_CArticleExt, char* errmld);
int ins_ccpvalperiod(const int *Fd_CcpValPeriod, const int *Fd_ZArtikel, char* errmld);
int ins_cartcompack(const int *Fd_CArtComPack, const int *Fd_ZArtikel, char* errmld);
int ins_cgibatchentry(const int *Fd_CGiBatchEntry, char* errmld);
int ins_cartrefundfrance(char* errmld);
int ins_cibt(const int *Fd_Cibt, char* errmld);
int ins_ean(const int *Fd_Ean, char* errmld);
int ins_csubsequentdeliverybrancharticleconfig(const int* Fd_Ean, char* errmld);
int ins_zartwg_5ag(const int* Fd_ZArtWg_5ag, char* errmld);
int ins_bliesort_direkt(const int* Fd_Bliesort, const int* Fd_ZANeuheit, char* errmld);
int ins_cartmedactor(const int* Fd_Cartmedactor, char* errmld);
int ins_cmedicalactor(const int* Fd_Cmedicalactor, char* errmld);

int del_zartwg(const int *Fd_ZArtWg, char* art_nr, char* art, char* errmld);
int del_cimexblock(const int *Fd_Cimexblock, char* art_nr, char* country, char* imex_mode, char* errmld);
int del_cdiscount(const int *Fd_CDiscount, char* errmld);
int del_cdiscgrpmem(const int *Fd_CDiscGrpMem, char* errmld);
int del_cartcompack(const int *Fd_CArtComPack, const int *Fd_ZArtikel, char* errmld);
int del_zartpreis_future(const int *Fd_ZArtPreis, char* errmld);
int del_ean(const int *Fd_Ean, char* art_nr, char* errmld);
int del_zaneuheit( const int* Fd_ZANeuheit, long artikelnr, char* errmld );

int upd_negval_zartikel(const int *Fd_ZArtikel, char* errmld);
int upd_cdiscount(const int *Fd_CDiscount, char* errmld);
int upd_negval_zartfrance(const int *Fd_ZArtFrance, char* errmld);
int upd_negval_zartserbia(const int *Fd_ZArtSerbia, char* errmld);
int upd_negval_zartaustria(const int *Fd_ZArtAustria, char* errmld);
int upd_cartmedactor(const int* Fd_Cartmedactor, char* errmld);
int upd_cmedicalactor(const int* Fd_Cmedicalactor, char* errmld);

int stop_cdiscount(const int *Fd_CDiscount, char* errmld);

// utils
int fill_upd_section(char* upd_section);
int fill_ins_section(char* ins_section_fields, char* ins_section_values);
int fill_ins_section_uni(int pkCount, char* ins_section_fields, char* ins_section_values);
int upd_negval(const char* table_name, const char* col_name, const int* fd, char* errmld);
int exists_in_cmedicalactor(const char* medicalactor_id, const char* medicalactor_type, char* errmld);
int exists_in_cartmedactor(const char* medicalactor_id, char* errmld);

struct ZARTIKEL			m_BufOldZArt;
struct ZARTPREIS		m_BufOldZPreis;
struct ZARTWG			m_BufOldZArtWg;
struct CDISCOUNT		m_BufOldCDiscount;
struct CDISCOUNT		m_BufOldCDiscountUnchanged;
struct ARTVE			m_BufOldArtVe;
struct ZARTFRANCE		m_BufOldZArtFrance;
struct ZARTSWITZERLAND  m_BufOldZArtSwitzerland;
struct ZARTSERBIA		m_BufOldZArtSerbia;
struct ZARTAUSTRIA		m_BufOldZArtAustria;
struct CARTICLECODES	m_BufOldCArticleCodes;
struct CARTICLEEXT		m_BufOldCArticleExt;
struct ZCHARGENRUECKRUF	m_BufOldZChargenRR;
struct CIMEXBLOCK		m_BufOldCimexblock;
struct CIBT				m_BufOldCibt;
struct EAN				m_BufOldEan;
struct CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG		m_BufOldCsubsequentdeliverybrancharticleconfig;
struct CMEDICALACTOR	m_BufOldCMedicalactor;
struct CARTMEDACTOR		m_BufOldCArtmedactor;

struct ZARTIKEL			BufZArtUpd;
struct ZARTWG			BufZArtWgUpd;
struct ARTVE			BufArtVe;
struct ZARTPREIS		BufZPreisIns;	
struct ZARTFRANCE		BufZArtFrance;
struct ZARTSWITZERLAND	BufZArtSwitzerland;
struct ZARTSERBIA		BufZArtSerbia;
struct ZARTAUSTRIA		BufZArtAustria;
struct CARTICLECODES	BufCArticleCodes;
struct CARTICLEEXT		BufCArticleExt;
struct ZCHARGENRUECKRUF	BufZChargenRR;
struct CDISCGRP			BufCDiscGrp;
struct CCPVALIDITYPERIOD BufCcpValPeriod;
struct CIBT				BufCibt;
struct CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG		BufCSubSeqDelUpd;
struct CMEDICALACTOR	BufCMedicalactor;
struct CARTMEDACTOR		BufCArtmedactor;

int sel_artnrbl		( const int *Fd_ArtnrBl,  const long art_nr, const long her_nr, struct ARTNRBL *artbl, char* errmld);
int upd_artnrbl		( const int *Fd_ArtnrBl,  struct ARTNRBL *artbl, char *errmld);
int ins_artnrbl		( const int *Fd_ArtnrBl,  struct ARTNRBL *artbl, char *errmld);
int del_artnrbl		( const int *Fd_ArtnrBl,  char *errmld);
struct ARTNRBL			m_BufOldArtBl;
struct ARTNRBL			artbl;

int sel_bliesort		( const int *Fd_Bliesort,  const long art_nr, const long her_nr, struct BLIESORT *bliesort, char* errmld);
int upd_bliesort		( const int *Fd_Bliesort,  struct BLIESORT *bliesort, const long beslaOld, char *errmld);
int ins_bliesort		( const int *Fd_Bliesort,  struct BLIESORT *bliesort, char *errmld);
struct BLIESORT			m_BufOldBLieSort;
struct BLIESORT			bliesort;
long InitPflegeTab( char *errmld );
void ClosePflegeTab( );

int sel_artnrbl_loop	( const int *Fd_ArtnrBl,  const long art_nr, char* artnrherst, char* errmld);
int upd_artnrbl_loop	( const int *Fd_ArtnrBl,  char *errmld);
int m_nNrOfArtnrbl;
int m_nNrOfArtnrblToUpdate;
struct ARTNRBL m_ArtnrblBuf[20];
struct ARTNRBL m_ArtnrblBufOld[20];

#endif
