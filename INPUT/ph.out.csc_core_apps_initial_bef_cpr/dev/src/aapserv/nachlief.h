/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_NACHLIEF_KDAUFTRAGNR          11
 #define L_NACHLIEF_POSNR                11
 #define L_NACHLIEF_DATUM                11
 #define L_NACHLIEF_POSTYP               6
 #define L_NACHLIEF_IDFNR                11
 #define L_NACHLIEF_ARTIKEL_NR           11
 #define L_NACHLIEF_MENGE                11
 #define L_NACHLIEF_FILIALNR1            6
 #define L_NACHLIEF_FILIALNR2            6
 #define L_NACHLIEF_FILIALNR3            6
 #define L_NACHLIEF_STATUS               6
 #define L_NACHLIEF_MATCHCODE            12
 #define L_NACHLIEF_KZKDKLASSE           3
 #define L_NACHLIEF_KUNDENNR		     11
 #define L_NACHLIEF_VERTRIEBSZENTRUMNR   6
 #define L_NACHLIEF_REGIONNR		     6
 #define L_NACHLIEF_EINHEIT              9
 #define L_NACHLIEF_ARTIKEL_NAME         30
 #define L_NACHLIEF_KDAUFTRAGART         2
 #define L_NACHLIEF_BEMERKUNGEN          240
 #define L_NACHLIEF_BESTAND              11

 #define L_NACHLIEF_PKEY 39

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define NACHLIEF_ANZ ( sizeof(NACHLIEF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_NACHLIEF sizeof(struct NACHLIEF)


 #define NACHLIEF_H

 #define NACHLIEF_LISTE \
 			NACHLIEFERPOS.KDAUFTRAGNR, \
 			NACHLIEFERPOS.POSNR, \
 			NACHLIEFERPOS.DATUM, \
 			NACHLIEFERPOS.POSTYP, \
 			NACHLIEFERPOS.IDFNR, \
 			NACHLIEFERPOS.ARTIKEL_NR, \
 			NACHLIEFERPOS.MENGE, \
 			NACHLIEFERPOS.FILIALNR1, \
 			NACHLIEFERPOS.FILIALNR2, \
 			NACHLIEFERPOS.FILIALNR3, \
 			NACHLIEFERPOS.STATUS, \
 			KUNDE.MATCHCODE, \
 			KUNDE.KZKDKLASSE, \
			NACHLIEFERPOS.KUNDENNR, \
			NACHLIEFERPOS.VERTRIEBSZENTRUMNR, \
			NACHLIEFERPOS.VERTRIEBSZENTRUMNR, \
			ARTIKELZENTRAL.EINHEIT, \
			ARTIKELZENTRAL.ARTIKEL_NAME, \
			NACHLIEFERPOS.KDAUFTRAGART, \
			NACHLIEFERPOS.BEMERKUNGEN, \
			ARTIKELLOKAL.BESTAND
 #define NACHLIEF_PLISTE \
 			"NACHLIEFERPOS.KDAUFTRAGNR," \
 			"NACHLIEFERPOS.POSNR," \
 			"NACHLIEFERPOS.DATUM," \
 			"NACHLIEFERPOS.POSTYP," \
 			"NACHLIEFERPOS.IDFNR," \
 			"NACHLIEFERPOS.ARTIKEL_NR," \
 			"NACHLIEFERPOS.MENGE," \
 			"NACHLIEFERPOS.FILIALNR1," \
 			"NACHLIEFERPOS.FILIALNR2," \
 			"NACHLIEFERPOS.FILIALNR3," \
 			"NACHLIEFERPOS.STATUS," \
 			"KUNDE.MATCHCODE," \
 			"KUNDE.KZKDKLASSE," \
			"NACHLIEFERPOS.KUNDENNR," \
			"NACHLIEFERPOS.VERTRIEBSZENTRUMNR," \
			"NACHLIEFERPOS.VERTRIEBSZENTRUMNR," \
			"ARTIKELZENTRAL.EINHEIT," \
			"ARTIKELZENTRAL.ARTIKEL_NAME," \
 			"NACHLIEFERPOS.KDAUFTRAGART," \
 			"NACHLIEFERPOS.BEMERKUNGEN," \
			"ARTIKELLOKAL.BESTAND "

 #define NACHLIEF_PELISTE \
 			"KDAUFTRAGNR," \
 			"POSNR," \
 			"DATUM," \
 			"POSTYP," \
 			"IDFNR," \
 			"ARTIKEL_NR," \
 			"MENGE," \
 			"FILIALNR1," \
 			"FILIALNR2," \
 			"FILIALNR3," \
 			"STATUS," \
 			"MATCHCODE," \
 			"KZKDKLASSE," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR," \
			"REGIONNR," \
			"EINHEIT," \
			"ARTIKEL_NAME," \
 			"KDAUFTRAGART," \
 			"BEMERKUNGEN," \
			"BESTAND "

 #define NACHLIEF_UPDLISTE \
 			"KDAUFTRAGNR=?," \
 			"POSNR=?," \
 			"DATUM=?," \
 			"POSTYP=?," \
 			"IDFNR=?," \
 			"ARTIKEL_NR=?," \
 			"MENGE=?," \
 			"FILIALNR1=?," \
 			"FILIALNR2=?," \
 			"FILIALNR3=?," \
 			"STATUS=?," \
 			"MATCHCODE=?," \
 			"KZKDKLASSE=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=?," \
			"REGIONNR=?," \
			"EINHEIT=?," \
			"ARTIKEL_NAME=?," \
 			"KDAUFTRAGART=?," \
 			"BEMERKUNGEN=?," \
			"BESTAND=? "

 #define NACHLIEFKDAUFTRAGNR                   0
 #define NACHLIEFPOSNR                         1
 #define NACHLIEFDATUM                         2
 #define NACHLIEFPOSTYP                        3
 #define NACHLIEFIDFNR                         4
 #define NACHLIEFARTIKEL_NR                    5
 #define NACHLIEFMENGE                         6
 #define NACHLIEFFILIALNR1                     7
 #define NACHLIEFFILIALNR2                     8
 #define NACHLIEFFILIALNR3                     9
 #define NACHLIEFSTATUS                        10
 #define NACHLIEFMATCHCODE                     11
 #define NACHLIEFKZKDKLASSE                    12
 #define NACHLIEFREGIONNR                      13
 #define NACHLIEFEINHEIT                       14
 #define NACHLIEFARTIKEL_NAME                  15
 #define NACHLIEFKDAUFTRAGART                  16
 #define NACHLIEFBEMERKUNGEN                   17

 #define NACHLIEF_ZEIGER(xxx) \
 			:xxx->KDAUFTRAGNR,\
 			:xxx->POSNR,\
 			:xxx->DATUM,\
 			:xxx->POSTYP,\
 			:xxx->IDFNR,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->MENGE,\
 			:xxx->FILIALNR1,\
 			:xxx->FILIALNR2,\
 			:xxx->FILIALNR3,\
 			:xxx->STATUS,\
 			:xxx->MATCHCODE,\
 			:xxx->KZKDKLASSE,\
			:xxx->KUNDENNR,\
			:xxx->VERTRIEBSZENTRUMNR,\
			:xxx->REGIONNR,\
			:xxx->EINHEIT,\
			:xxx->ARTIKEL_NAME,\
			:xxx->KDAUFTRAGART,\
			:xxx->BEMERKUNGEN,\
			:xxx->BESTAND

 #define NACHLIEF_UPDATE(xxx) \
 			KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
 			POSNR = :xxx->POSNR,\
 			DATUM = :xxx->DATUM,\
 			POSTYP = :xxx->POSTYP,\
 			IDFNR = :xxx->IDFNR,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			MENGE = :xxx->MENGE,\
 			FILIALNR1 = :xxx->FILIALNR1,\
 			FILIALNR2 = :xxx->FILIALNR2,\
 			FILIALNR3 = :xxx->FILIALNR3,\
 			STATUS = :xxx->STATUS,\
 			MATCHCODE = :xxx->MATCHCODE,\
 			KZKDKLASSE = :xxx->KZKDKLASSE,\
			KUNDENNR = :xxx->KUNDENNR,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
			REGIONNR = :xxx->REGIONNR,\
			EINHEIT = :xxx->EINHEIT,\
			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
			BESTAND = :xxx->BESTAND

 #define LS_NACHLIEF_KDAUFTRAGNR          11
 #define LS_NACHLIEF_POSNR                11
 #define LS_NACHLIEF_DATUM                11
 #define LS_NACHLIEF_POSTYP               7
 #define LS_NACHLIEF_IDFNR                11
 #define LS_NACHLIEF_ARTIKEL_NR           11
 #define LS_NACHLIEF_MENGE                11
 #define LS_NACHLIEF_FILIALNR1            7
 #define LS_NACHLIEF_FILIALNR2            7
 #define LS_NACHLIEF_FILIALNR3            7
 #define LS_NACHLIEF_STATUS               7
 #define LS_NACHLIEF_MATCHCODE            13
 #define LS_NACHLIEF_KZKDKLASSE           4
 #define LS_NACHLIEF_KUNDENNR		      11
 #define LS_NACHLIEF_VERTRIEBSZENTRUMNR   7
 #define LS_NACHLIEF_REGIONNR			  7
 #define LS_NACHLIEF_EINHEIT			  10
 #define LS_NACHLIEF_ARTIKEL_NAME		  31
 #define LS_NACHLIEF_KDAUFTRAGART		  3
 #define LS_NACHLIEF_BEMERKUNGEN          241
 #define LS_NACHLIEF_BESTAND              11
 #define LS_NACHLIEF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct NACHLIEF {
		 long    KDAUFTRAGNR;
		 long    POSNR;
		 long    DATUM;
		 short   POSTYP;
		 long    IDFNR;
		 long    ARTIKEL_NR;
		 long    MENGE;
		 short   FILIALNR1;
		 short   FILIALNR2;
		 short   FILIALNR3;
		 short   STATUS;
		 char    MATCHCODE[12 + 1];
		 char    KZKDKLASSE[3 + 1];
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 short	 REGIONNR;
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 long    BESTAND;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_NACHLIEF {
		 long    KDAUFTRAGNR;
		 long    POSNR;
		 long    DATUM;
		 short   POSTYP;
		 long    IDFNR;
		 long    ARTIKEL_NR;
		 long    MENGE;
		 short   FILIALNR1;
		 short   FILIALNR2;
		 short   FILIALNR3;
		 short   STATUS;
		 char    MATCHCODE[12 + 1];
		 char    KZKDKLASSE[3 + 1];
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 short	 REGIONNR;
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 long    BESTAND;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_NACHLIEF {
		 short  KDAUFTRAGNR;
		 short  POSNR;
		 short  DATUM;
		 short  POSTYP;
		 short  IDFNR;
		 short  ARTIKEL_NR;
		 short  MENGE;
		 short  FILIALNR1;
		 short  FILIALNR2;
		 short  FILIALNR3;
		 short  STATUS;
		 short  MATCHCODE;
		 short  KZKDKLASSE;
		 short	KUNDENNR;
		 short	VERTRIEBSZENTRUMNR;
		 short	REGIONNR;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  KDAUFTRAGART;
		 short  BEMERKUNGEN;
		 short  BESTAND;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_NACHLIEF {
		 char    KDAUFTRAGNR[11];
		 char    POSNR[11];
		 char    DATUM[11];
		 char    POSTYP[7];
		 char    IDFNR[11];
		 char    ARTIKEL_NR[11];
		 char    MENGE[11];
		 char    FILIALNR1[7];
		 char    FILIALNR2[7];
		 char    FILIALNR3[7];
		 char    STATUS[7];
		 char    MATCHCODE[12 + 1];
		 char    KZKDKLASSE[3 + 1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 REGIONNR[6 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 char    BESTAND[11];
		 char    FETCH_REL[11];
       };

 struct O_NACHLIEF {
		 char    KDAUFTRAGNR[11];
		 char    POSNR[11];
		 char    DATUM[11];
		 char    POSTYP[7];
		 char    IDFNR[11];
		 char    ARTIKEL_NR[11];
		 char    MENGE[11];
		 char    FILIALNR1[7];
		 char    FILIALNR2[7];
		 char    FILIALNR3[7];
		 char    STATUS[7];
		 char    MATCHCODE[12];
		 char    KZKDKLASSE[3];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[6];
		 char	 REGIONNR[6];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    KDAUFTRAGART[2];
		 char    BEMERKUNGEN[240];
		 char    BESTAND[11];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc NACHLIEF_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NACHLIEF_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C ,   9 ,   0 },
	 { TYP_C ,  30 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C , 240 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CNACHLIEF
 {
  public:

  NACHLIEF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, NACHLIEF_BES, NACHLIEF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,NACHLIEF_BES, NACHLIEF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,NACHLIEF_BES, NACHLIEF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CNACHLIEF()
  {
   ::buf_default((void *)&s, NACHLIEF_BES, NACHLIEF_ANZ);
  }
 };
#endif

#define NACHLIEF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 KDAUFTRAGNR INTEGER           ,\
		 POSNR INTEGER           ,\
		 DATUM INTEGER           ,\
		 POSTYP SMALLINT          ,\
		 IDFNR INTEGER           ,\
		 ARTIKEL_NR INTEGER           ,\
		 MENGE INTEGER           ,\
		 FILIALNR1 SMALLINT          ,\
		 FILIALNR2 SMALLINT          ,\
		 FILIALNR3 SMALLINT          ,\
		 STATUS SMALLINT          ,\
		 MATCHCODE CHAR(12)          ,\
		 KZKDKLASSE CHAR(3)          ,\
		 KUNDENNR INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 REGIONNR SMALLINT          ,\
		 EINHEIT CHAR(9)          ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 KDAUFTRAGART CHAR(2)          ,\
		 BEMERKUNGEN CHAR(240)          ,\
		 BESTAND INTEGER           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 245 LOCK MODE ROW;

#define NACHLIEF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_NACHLIEFERPOS_3  on yyy( KDAUFTRAGNR, POSNR, DATUM, POSTYP );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_VERBUNDLIEFERP_2 on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define NACHLIEF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_NACHLIEFERPOS_3 ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_VERBUNDLIEFERP_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

