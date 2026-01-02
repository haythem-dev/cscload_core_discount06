#ifndef G_UTIL_INCLUDED
#define G_UTIL_INCLUDED

long GenUtil( char *db, char *ili_direc, char *errmld, int iMode, int iTestRun );

long tages_datum;
int  anz_columns;

int  Fd_ZArtikel;
int  Fd_ArtnrBl;
int  Fd_Bliesort;
int  Fd_ZANeuheit;
int  Fd_ZArtPreis;
int  Fd_ZArtWg;
int  Fd_CDiscount;
int  Fd_ArtVe;
int  Fd_CDiscGrpMem;
int	 Fd_CDiscGrp;
int  Fd_CArticleCodes;
int  Fd_CArticleExt;
int	 Fd_CGiBatchEntry;
int  Fd_ZArtFrance;
int  Fd_ZArtSwitzerland;
int  Fd_ZArtSerbia;
int  Fd_ZArtAustria;
int  Fd_CArtComPack;
int  Fd_CcpValPeriod;
int  Fd_ZChargenRR;
int  Fd_Cimexblock;
int  Fd_Cibt;
int	 Fd_Ean;
int	 Fd_Csubsequentdeliverybrancharticleconfig;
int  Fd_ZArtWg_5ag;
int  Fd_CBaseListArticles;
int  Fd_Cartmedactor;
int  Fd_Cmedicalactor;

enum EUpdTable
{
	UPD_ZARTIKEL = 1,
	UPD_ZARTPREIS = 2,
	UPD_ZARTWG = 3,
	UPD_CDISCOUNT = 4,
	UPD_CDISCOUNT_FLEXIBLE = 5,
	UPD_CDISCOUNT_STOP = 6,
	UPD_ARTVE = 7,
	UPD_CDISCGRPMEM = 8,
	UPD_ZARTFRANCE = 9,
	UPD_CARTICLECODES = 10,
	UPD_CARTCOMPACK = 11,
	UPD_CGIBATCHENTRY = 12,
	UPD_ZARTSWITZERLAND = 13,
	UPD_CARTICLEEXT = 14,
	UPD_ZCHARGENRR = 15,
	UPD_ZARTSERBIA = 16,
	UPD_ZARTAUSTRIA = 17,
	UPD_CIMEXBLOCK = 18,
	UPD_CIBT = 19,
	UPD_EAN = 20,
	UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG = 21,
	UPD_ZARTWG_5AG = 22,
	UPD_BLIESORT_DIREKT = 23,
	UPD_CBASELIST_ARTICLES = 24,
	UPD_CARTMEDACTOR = 25,
	UPD_CMEDICALACTOR = 26,

	MODE_END = 27
};

int m_eUpdTable;

int m_CDisc_ResetDateTo;
int m_CDisc_AlreadyExists;
int m_CDiscGrpMem_CurrentGroupNo;
int m_CArtComPack_CurrentPackNo;
int m_EanWrToProt;
int m_ZartpreisWrToProt;

enum EEanWrToProt
{
	EAN_DEL,
	EAN_NO_DEL,
	EAN_INS,
	EAN_NO_INS
};

enum EZartpreisWrToProt
{
	ZARTPREIS_INS,
	ZARTPREIS_NO_INS
};

#define ANZ_FELDER_UPD 10
#define MAX_INPUT_LENGTH 50

char upd_columns [ ANZ_FELDER_UPD + 1 ] [MAX_INPUT_LENGTH] ; /* +1 wg. Key-Spalte */
char upd_values  [ ANZ_FELDER_UPD + 1 ] [MAX_INPUT_LENGTH]  ; /* +1 wg. Key-Spalte */
char neg_values  [ ANZ_FELDER_UPD ] [MAX_INPUT_LENGTH] ; 
char table_name  [MAX_INPUT_LENGTH];

char * database;

#endif
