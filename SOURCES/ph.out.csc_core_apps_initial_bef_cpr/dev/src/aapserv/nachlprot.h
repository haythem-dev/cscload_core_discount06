/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_NACHLPROT_ARTIKEL_NR           11
 #define L_NACHLPROT_IDFNR                11
 #define L_NACHLPROT_NL_MENGE_ALT         11
 #define L_NACHLPROT_AENDTYP              6
 #define L_NACHLPROT_POSTYP               6
 #define L_NACHLPROT_DATUM                11
 #define L_NACHLPROT_POSNR                11
 #define L_NACHLPROT_KDAUFTRAGNR          11
 #define L_NACHLPROT_UID                  11
 #define L_NACHLPROT_ZEIT_NEU             11
 #define L_NACHLPROT_DATUM_NEU            11
 #define L_NACHLPROT_KDAUFTRAG_NR_NEU     11
 #define L_NACHLPROT_NL_MENGE_AKTUELL     11
 #define L_NACHLPROT_NL_MENGE_GELIEFER    11
 #define L_NACHLPROT_NL_MENGE_NEU         11
 #define L_NACHLPROT_VERTRIEBSZENTRUMNR   6
 #define L_NACHLPROT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define NACHLPROT_ANZ (int) ( sizeof(NACHLPROT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_NACHLPROT sizeof(struct NACHLPROT)


 #define NACHLPROT_H

 #define NACHLPROT_LISTE \
 			NACHLIEFPROT.ARTIKEL_NR, \
 			NACHLIEFPROT.IDFNR, \
 			NACHLIEFPROT.NL_MENGE_ALT, \
 			NACHLIEFPROT.AENDTYP, \
 			NACHLIEFPROT.POSTYP, \
 			NACHLIEFPROT.DATUM, \
 			NACHLIEFPROT.POSNR, \
 			NACHLIEFPROT.KDAUFTRAGNR, \
 			NACHLIEFPROT.UID, \
 			NACHLIEFPROT.ZEIT_NEU, \
 			NACHLIEFPROT.DATUM_NEU, \
 			NACHLIEFPROT.KDAUFTRAG_NR_NEU, \
 			NACHLIEFPROT.NL_MENGE_AKTUELL, \
 			NACHLIEFPROT.NL_MENGE_GELIEFER, \
 			NACHLIEFPROT.NL_MENGE_NEU
 #define NACHLPROT_PLISTE \
 			"NACHLIEFPROT.ARTIKEL_NR," \
 			"NACHLIEFPROT.IDFNR," \
 			"NACHLIEFPROT.NL_MENGE_ALT," \
 			"NACHLIEFPROT.AENDTYP," \
 			"NACHLIEFPROT.POSTYP," \
 			"NACHLIEFPROT.DATUM," \
 			"NACHLIEFPROT.POSNR," \
 			"NACHLIEFPROT.KDAUFTRAGNR," \
 			"NACHLIEFPROT.UID," \
 			"NACHLIEFPROT.ZEIT_NEU," \
 			"NACHLIEFPROT.DATUM_NEU," \
 			"NACHLIEFPROT.KDAUFTRAG_NR_NEU," \
 			"NACHLIEFPROT.NL_MENGE_AKTUELL," \
 			"NACHLIEFPROT.NL_MENGE_GELIEFER," \
 			"NACHLIEFPROT.NL_MENGE_NEU " 

 #define NACHLPROT_PELISTE \
 			"ARTIKEL_NR," \
 			"IDFNR," \
 			"NL_MENGE_ALT," \
 			"AENDTYP," \
 			"POSTYP," \
 			"DATUM," \
 			"POSNR," \
 			"KDAUFTRAGNR," \
 			"UID," \
 			"ZEIT_NEU," \
 			"DATUM_NEU," \
 			"KDAUFTRAG_NR_NEU," \
 			"NL_MENGE_AKTUELL," \
 			"NL_MENGE_GELIEFER," \
 			"NL_MENGE_NEU " 

 #define NACHLPROT_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"IDFNR=?," \
 			"NL_MENGE_ALT=?," \
 			"AENDTYP=?," \
 			"POSTYP=?," \
 			"DATUM=?," \
 			"POSNR=?," \
 			"KDAUFTRAGNR=?," \
 			"UID=?," \
 			"ZEIT_NEU=?," \
 			"DATUM_NEU=?," \
 			"KDAUFTRAG_NR_NEU=?," \
 			"NL_MENGE_AKTUELL=?," \
 			"NL_MENGE_GELIEFER=?," \
 			"NL_MENGE_NEU=? " 

 #define NACHLPROTARTIKEL_NR                    0
 #define NACHLPROTIDFNR                         1
 #define NACHLPROTNL_MENGE_ALT                  2
 #define NACHLPROTAENDTYP                       3
 #define NACHLPROTPOSTYP                        4
 #define NACHLPROTDATUM                         5
 #define NACHLPROTPOSNR                         6
 #define NACHLPROTKDAUFTRAGNR                   7
 #define NACHLPROTUID                           8
 #define NACHLPROTZEIT_NEU                      9
 #define NACHLPROTDATUM_NEU                     10
 #define NACHLPROTKDAUFTRAG_NR_NEU              11
 #define NACHLPROTNL_MENGE_AKTUELL              12
 #define NACHLPROTNL_MENGE_GELIEFER             13
 #define NACHLPROTNL_MENGE_NEU                  14
 #define NACHLPROTVERTRIEBSZENTRUMNR			15

 #define NACHLPROT_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->IDFNR,\
 			:xxx->NL_MENGE_ALT,\
 			:xxx->AENDTYP,\
 			:xxx->POSTYP,\
 			:xxx->DATUM,\
 			:xxx->POSNR,\
 			:xxx->KDAUFTRAGNR,\
 			:xxx->UID,\
 			:xxx->ZEIT_NEU,\
 			:xxx->DATUM_NEU,\
 			:xxx->KDAUFTRAG_NR_NEU,\
 			:xxx->NL_MENGE_AKTUELL,\
 			:xxx->NL_MENGE_GELIEFER,\
 			:xxx->NL_MENGE_NEU

 #define NACHLPROT_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			IDFNR = :xxx->IDFNR,\
 			NL_MENGE_ALT = :xxx->NL_MENGE_ALT,\
 			AENDTYP = :xxx->AENDTYP,\
 			POSTYP = :xxx->POSTYP,\
 			DATUM = :xxx->DATUM,\
 			POSNR = :xxx->POSNR,\
 			KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
 			UID = :xxx->UID,\
 			ZEIT_NEU = :xxx->ZEIT_NEU,\
 			DATUM_NEU = :xxx->DATUM_NEU,\
 			KDAUFTRAG_NR_NEU = :xxx->KDAUFTRAG_NR_NEU,\
 			NL_MENGE_AKTUELL = :xxx->NL_MENGE_AKTUELL,\
 			NL_MENGE_GELIEFER = :xxx->NL_MENGE_GELIEFER,\
 			NL_MENGE_NEU = :xxx->NL_MENGE_NEU

 #define LS_NACHLPROT_ARTIKEL_NR           11
 #define LS_NACHLPROT_IDFNR                11
 #define LS_NACHLPROT_NL_MENGE_ALT         11
 #define LS_NACHLPROT_AENDTYP              7
 #define LS_NACHLPROT_POSTYP               7
 #define LS_NACHLPROT_DATUM                11
 #define LS_NACHLPROT_POSNR                11
 #define LS_NACHLPROT_KDAUFTRAGNR          11
 #define LS_NACHLPROT_UID                  11
 #define LS_NACHLPROT_ZEIT_NEU             11
 #define LS_NACHLPROT_DATUM_NEU            11
 #define LS_NACHLPROT_KDAUFTRAG_NR_NEU     11
 #define LS_NACHLPROT_NL_MENGE_AKTUELL     11
 #define LS_NACHLPROT_NL_MENGE_GELIEFER    11
 #define LS_NACHLPROT_NL_MENGE_NEU         11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct NACHLPROT {
		 long    ARTIKEL_NR;
		 long    IDFNR;
		 long    NL_MENGE_ALT;
		 short   AENDTYP;
		 short   POSTYP;
		 long    DATUM;
		 long    POSNR;
		 long    KDAUFTRAGNR;
		 long    UID;
		 long    ZEIT_NEU;
		 long    DATUM_NEU;
		 long    KDAUFTRAG_NR_NEU;
		 long    NL_MENGE_AKTUELL;
		 long    NL_MENGE_GELIEFER;
		 long    NL_MENGE_NEU;
		 short   VERTRIEBSZENTRUMNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_NACHLPROT {
		 long    ARTIKEL_NR;
		 long    IDFNR;
		 long    NL_MENGE_ALT;
		 short   AENDTYP;
		 short   POSTYP;
		 long    DATUM;
		 long    POSNR;
		 long    KDAUFTRAGNR;
		 long    UID;
		 long    ZEIT_NEU;
		 long    DATUM_NEU;
		 long    KDAUFTRAG_NR_NEU;
		 long    NL_MENGE_AKTUELL;
		 long    NL_MENGE_GELIEFER;
		 long    NL_MENGE_NEU;
 		 short   VERTRIEBSZENTRUMNR;
      };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_NACHLPROT {
		 short  ARTIKEL_NR;
		 short  IDFNR;
		 short  NL_MENGE_ALT;
		 short  AENDTYP;
		 short  POSTYP;
		 short  DATUM;
		 short  POSNR;
		 short  KDAUFTRAGNR;
		 short  UID;
		 short  ZEIT_NEU;
		 short  DATUM_NEU;
		 short  KDAUFTRAG_NR_NEU;
		 short  NL_MENGE_AKTUELL;
		 short  NL_MENGE_GELIEFER;
		 short  NL_MENGE_NEU;
		 short  VERTRIEBSZENTRUMNR;
 };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_NACHLPROT {
		 char    ARTIKEL_NR[11];
		 char    IDFNR[11];
		 char    NL_MENGE_ALT[11];
		 char    AENDTYP[7];
		 char    POSTYP[7];
		 char    DATUM[11];
		 char    POSNR[11];
		 char    KDAUFTRAGNR[11];
		 char    UID[11];
		 char    ZEIT_NEU[11];
		 char    DATUM_NEU[11];
		 char    KDAUFTRAG_NR_NEU[11];
		 char    NL_MENGE_AKTUELL[11];
		 char    NL_MENGE_GELIEFER[11];
		 char    NL_MENGE_NEU[11];
       };

 struct O_NACHLPROT {
		 char    ARTIKEL_NR[11];
		 char    IDFNR[11];
		 char    NL_MENGE_ALT[11];
		 char    AENDTYP[7];
		 char    POSTYP[7];
		 char    DATUM[11];
		 char    POSNR[11];
		 char    KDAUFTRAGNR[11];
		 char    UID[11];
		 char    ZEIT_NEU[11];
		 char    DATUM_NEU[11];
		 char    KDAUFTRAG_NR_NEU[11];
		 char    NL_MENGE_AKTUELL[11];
		 char    NL_MENGE_GELIEFER[11];
		 char    NL_MENGE_NEU[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc NACHLPROT_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NACHLPROT_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S ,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CNACHLPROT
 {
  public:

  NACHLPROT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, NACHLPROT_BES, NACHLPROT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,NACHLPROT_BES, NACHLPROT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,NACHLPROT_BES, NACHLPROT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CNACHLPROT()
  {
   ::buf_default((void *)&s, NACHLPROT_BES, NACHLPROT_ANZ);
  }
 };
#endif

#define NACHLPROT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 IDFNR INTEGER           ,\
		 NL_MENGE_ALT INTEGER           ,\
		 AENDTYP SMALLINT          ,\
		 POSTYP SMALLINT          ,\
		 DATUM INTEGER           ,\
		 POSNR INTEGER           ,\
		 KDAUFTRAGNR INTEGER           ,\
		 UID INTEGER           ,\
		 ZEIT_NEU INTEGER           ,\
		 DATUM_NEU INTEGER           ,\
		 KDAUFTRAG_NR_NEU INTEGER           ,\
		 NL_MENGE_AKTUELL INTEGER           ,\
		 NL_MENGE_GELIEFER INTEGER           ,\
		 NL_MENGE_NEU INTEGER             ) EXTENT SIZE 375 LOCK MODE ROW;

#define NACHLPROT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_NACHLIEFPROT_1   on yyy( ARTIKEL_NR, IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define NACHLPROT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_NACHLIEFPROT_1  ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_NACHLPROTV_ARTIKEL_NR           11
 #define L_NACHLPROTV_IDFNR                11
 #define L_NACHLPROTV_NL_MENGE_ALT         11
 #define L_NACHLPROTV_AENDTYP              6
 #define L_NACHLPROTV_POSTYP               6
 #define L_NACHLPROTV_DATUM                11
 #define L_NACHLPROTV_POSNR                11
 #define L_NACHLPROTV_KDAUFTRAGNR          11
 #define L_NACHLPROTV_ZEIT_NEU             11
 #define L_NACHLPROTV_DATUM_NEU            11
 #define L_NACHLPROTV_KDAUFTRAG_NR_NEU     11
 #define L_NACHLPROTV_NL_MENGE_AKTUELL     11
 #define L_NACHLPROTV_NL_MENGE_GELIEFER    11
 #define L_NACHLPROTV_NL_MENGE_NEU         11
 #define L_NACHLPROTV_USERNAME             8


 #define L_NACHLPROTV_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define NACHLPROTV_ANZ (int) ( sizeof(NACHLPROTV_BES) / sizeof(struct buf_desc) )
#endif
 #define G_NACHLPROTV sizeof(struct NACHLPROTV)


 #define NACHLPROTV_H

 #define NACHLPROTV_LISTE \
 			NACHLIEFPROT.ARTIKEL_NR, \
 			NACHLIEFPROT.IDFNR, \
 			NACHLIEFPROT.NL_MENGE_ALT, \
 			NACHLIEFPROT.AENDTYP, \
 			NACHLIEFPROT.POSTYP, \
 			NACHLIEFPROT.DATUM, \
 			NACHLIEFPROT.POSNR, \
 			NACHLIEFPROT.KDAUFTRAGNR, \
 			NACHLIEFPROT.ZEIT_NEU, \
 			NACHLIEFPROT.DATUM_NEU, \
 			NACHLIEFPROT.KDAUFTRAG_NR_NEU, \
 			NACHLIEFPROT.NL_MENGE_AKTUELL, \
 			NACHLIEFPROT.NL_MENGE_GELIEFER, \
 			NACHLIEFPROT.NL_MENGE_NEU, \
 			PASSWD.USERNAME
 #define NACHLPROTV_PLISTE \
 			"NACHLIEFPROT.ARTIKEL_NR," \
 			"NACHLIEFPROT.IDFNR," \
 			"NACHLIEFPROT.NL_MENGE_ALT," \
 			"NACHLIEFPROT.AENDTYP," \
 			"NACHLIEFPROT.POSTYP," \
 			"NACHLIEFPROT.DATUM," \
 			"NACHLIEFPROT.POSNR," \
 			"NACHLIEFPROT.KDAUFTRAGNR," \
 			"NACHLIEFPROT.ZEIT_NEU," \
 			"NACHLIEFPROT.DATUM_NEU," \
 			"NACHLIEFPROT.KDAUFTRAG_NR_NEU," \
 			"NACHLIEFPROT.NL_MENGE_AKTUELL," \
 			"NACHLIEFPROT.NL_MENGE_GELIEFER," \
 			"NACHLIEFPROT.NL_MENGE_NEU," \
 			"PASSWD.USERNAME " 

 #define NACHLPROTV_PELISTE \
 			"ARTIKEL_NR," \
 			"IDFNR," \
 			"NL_MENGE_ALT," \
 			"AENDTYP," \
 			"POSTYP," \
 			"DATUM," \
 			"POSNR," \
 			"KDAUFTRAGNR," \
 			"ZEIT_NEU," \
 			"DATUM_NEU," \
 			"KDAUFTRAG_NR_NEU," \
 			"NL_MENGE_AKTUELL," \
 			"NL_MENGE_GELIEFER," \
 			"NL_MENGE_NEU," \
 			"USERNAME " 

 #define NACHLPROTV_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"IDFNR=?," \
 			"NL_MENGE_ALT=?," \
 			"AENDTYP=?," \
 			"POSTYP=?," \
 			"DATUM=?," \
 			"POSNR=?," \
 			"KDAUFTRAGNR=?," \
 			"ZEIT_NEU=?," \
 			"DATUM_NEU=?," \
 			"KDAUFTRAG_NR_NEU=?," \
 			"NL_MENGE_AKTUELL=?," \
 			"NL_MENGE_GELIEFER=?," \
 			"NL_MENGE_NEU=?," \
 			"USERNAME=? " 

 #define NACHLPROTVARTIKEL_NR                    0
 #define NACHLPROTVIDFNR                         1
 #define NACHLPROTVNL_MENGE_ALT                  2
 #define NACHLPROTVAENDTYP                       3
 #define NACHLPROTVPOSTYP                        4
 #define NACHLPROTVDATUM                         5
 #define NACHLPROTVPOSNR                         6
 #define NACHLPROTVKDAUFTRAGNR                   7
 #define NACHLPROTVZEIT_NEU                      8
 #define NACHLPROTVDATUM_NEU                     9
 #define NACHLPROTVKDAUFTRAG_NR_NEU              10
 #define NACHLPROTVNL_MENGE_AKTUELL              11
 #define NACHLPROTVNL_MENGE_GELIEFER             12
 #define NACHLPROTVNL_MENGE_NEU                  13
 #define NACHLPROTVUSERNAME                      14

 #define NACHLPROTV_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->IDFNR,\
 			:xxx->NL_MENGE_ALT,\
 			:xxx->AENDTYP,\
 			:xxx->POSTYP,\
 			:xxx->DATUM,\
 			:xxx->POSNR,\
 			:xxx->KDAUFTRAGNR,\
 			:xxx->ZEIT_NEU,\
 			:xxx->DATUM_NEU,\
 			:xxx->KDAUFTRAG_NR_NEU,\
 			:xxx->NL_MENGE_AKTUELL,\
 			:xxx->NL_MENGE_GELIEFER,\
 			:xxx->NL_MENGE_NEU,\
 			:xxx->USERNAME

 #define NACHLPROTV_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			IDFNR = :xxx->IDFNR,\
 			NL_MENGE_ALT = :xxx->NL_MENGE_ALT,\
 			AENDTYP = :xxx->AENDTYP,\
 			POSTYP = :xxx->POSTYP,\
 			DATUM = :xxx->DATUM,\
 			POSNR = :xxx->POSNR,\
 			KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
 			ZEIT_NEU = :xxx->ZEIT_NEU,\
 			DATUM_NEU = :xxx->DATUM_NEU,\
 			KDAUFTRAG_NR_NEU = :xxx->KDAUFTRAG_NR_NEU,\
 			NL_MENGE_AKTUELL = :xxx->NL_MENGE_AKTUELL,\
 			NL_MENGE_GELIEFER = :xxx->NL_MENGE_GELIEFER,\
 			NL_MENGE_NEU = :xxx->NL_MENGE_NEU,\
 			USERNAME = :xxx->USERNAME

 #define LS_NACHLPROTV_ARTIKEL_NR           11
 #define LS_NACHLPROTV_IDFNR                11
 #define LS_NACHLPROTV_NL_MENGE_ALT         11
 #define LS_NACHLPROTV_AENDTYP              7
 #define LS_NACHLPROTV_POSTYP               7
 #define LS_NACHLPROTV_DATUM                11
 #define LS_NACHLPROTV_POSNR                11
 #define LS_NACHLPROTV_KDAUFTRAGNR          11
 #define LS_NACHLPROTV_ZEIT_NEU             11
 #define LS_NACHLPROTV_DATUM_NEU            11
 #define LS_NACHLPROTV_KDAUFTRAG_NR_NEU     11
 #define LS_NACHLPROTV_NL_MENGE_AKTUELL     11
 #define LS_NACHLPROTV_NL_MENGE_GELIEFER    11
 #define LS_NACHLPROTV_NL_MENGE_NEU         11
 #define LS_NACHLPROTV_USERNAME             9
 #define LS_NACHLPROTV_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct NACHLPROTV {
		 long    ARTIKEL_NR;
		 long    IDFNR;
		 long    NL_MENGE_ALT;
		 short   AENDTYP;
		 short   POSTYP;
		 long    DATUM;
		 long    POSNR;
		 long    KDAUFTRAGNR;
		 long    ZEIT_NEU;
		 long    DATUM_NEU;
		 long    KDAUFTRAG_NR_NEU;
		 long    NL_MENGE_AKTUELL;
		 long    NL_MENGE_GELIEFER;
		 long    NL_MENGE_NEU;
		 char    USERNAME[8 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_NACHLPROTV {
		 long    ARTIKEL_NR;
		 long    IDFNR;
		 long    NL_MENGE_ALT;
		 short   AENDTYP;
		 short   POSTYP;
		 long    DATUM;
		 long    POSNR;
		 long    KDAUFTRAGNR;
		 long    ZEIT_NEU;
		 long    DATUM_NEU;
		 long    KDAUFTRAG_NR_NEU;
		 long    NL_MENGE_AKTUELL;
		 long    NL_MENGE_GELIEFER;
		 long    NL_MENGE_NEU;
		 char    USERNAME[8 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_NACHLPROTV {
		 short  ARTIKEL_NR;
		 short  IDFNR;
		 short  NL_MENGE_ALT;
		 short  AENDTYP;
		 short  POSTYP;
		 short  DATUM;
		 short  POSNR;
		 short  KDAUFTRAGNR;
		 short  ZEIT_NEU;
		 short  DATUM_NEU;
		 short  KDAUFTRAG_NR_NEU;
		 short  NL_MENGE_AKTUELL;
		 short  NL_MENGE_GELIEFER;
		 short  NL_MENGE_NEU;
		 short  USERNAME;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_NACHLPROTV {
		 char    ARTIKEL_NR[11];
		 char    IDFNR[11];
		 char    NL_MENGE_ALT[11];
		 char    AENDTYP[7];
		 char    POSTYP[7];
		 char    DATUM[11];
		 char    POSNR[11];
		 char    KDAUFTRAGNR[11];
		 char    ZEIT_NEU[11];
		 char    DATUM_NEU[11];
		 char    KDAUFTRAG_NR_NEU[11];
		 char    NL_MENGE_AKTUELL[11];
		 char    NL_MENGE_GELIEFER[11];
		 char    NL_MENGE_NEU[11];
		 char    USERNAME[8 + 1];
		 char    FETCH_REL[11];
       };

 struct O_NACHLPROTV {
		 char    ARTIKEL_NR[11];
		 char    IDFNR[11];
		 char    NL_MENGE_ALT[11];
		 char    AENDTYP[7];
		 char    POSTYP[7];
		 char    DATUM[11];
		 char    POSNR[11];
		 char    KDAUFTRAGNR[11];
		 char    ZEIT_NEU[11];
		 char    DATUM_NEU[11];
		 char    KDAUFTRAG_NR_NEU[11];
		 char    NL_MENGE_AKTUELL[11];
		 char    NL_MENGE_GELIEFER[11];
		 char    NL_MENGE_NEU[11];
		 char    USERNAME[8];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc NACHLPROTV_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NACHLPROTV_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CNACHLPROTV
 {
  public:

  NACHLPROTV s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, NACHLPROTV_BES, NACHLPROTV_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,NACHLPROTV_BES, NACHLPROTV_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,NACHLPROTV_BES, NACHLPROTV_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CNACHLPROTV()
  {
   ::buf_default((void *)&s, NACHLPROTV_BES, NACHLPROTV_ANZ);
  }
 };
#endif

#define NACHLPROTV_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 IDFNR INTEGER           ,\
		 NL_MENGE_ALT INTEGER           ,\
		 AENDTYP SMALLINT          ,\
		 POSTYP SMALLINT          ,\
		 DATUM INTEGER           ,\
		 POSNR INTEGER           ,\
		 KDAUFTRAGNR INTEGER           ,\
		 ZEIT_NEU INTEGER           ,\
		 DATUM_NEU INTEGER           ,\
		 KDAUFTRAG_NR_NEU INTEGER           ,\
		 NL_MENGE_AKTUELL INTEGER           ,\
		 NL_MENGE_GELIEFER INTEGER           ,\
		 NL_MENGE_NEU INTEGER           ,\
		 USERNAME CHAR(8)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 421 LOCK MODE ROW;

#define NACHLPROTV_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_NACHLIEFPROT_1   on yyy( ARTIKEL_NR, IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define NACHLPROTV_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_NACHLIEFPROT_1  ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

