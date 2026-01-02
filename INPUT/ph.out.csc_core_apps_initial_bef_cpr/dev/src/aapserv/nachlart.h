/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_NACHLART_KDAUFTRAGNR          11
 #define L_NACHLART_POSNR                11
 #define L_NACHLART_DATUM                11
 #define L_NACHLART_POSTYP               6
 #define L_NACHLART_IDFNR                11
 #define L_NACHLART_ARTIKEL_NR           11
 #define L_NACHLART_MENGE                11
 #define L_NACHLART_FILIALNR1            6
 #define L_NACHLART_FILIALNR2            6
 #define L_NACHLART_FILIALNR3            6
 #define L_NACHLART_STATUS               6
 #define L_NACHLART_DARREICHFORM         3
 #define L_NACHLART_EINHEIT              9
 #define L_NACHLART_ARTIKEL_NAME         30
 #define L_NACHLART_BESTAND              11
 #define L_NACHLART_VERTRIEBSZENTRUMNR   6
 #define L_NACHLART_PREISEKAPONETTO      9
 #define N_NACHLART_PREISEKAPONETTO      2
 #define L_NACHLART_KDAUFTRAGART         2
 #define L_NACHLART_CODE_TYPE            6
 #define L_NACHLART_ARTICLE_CODE		 25
 #define L_NACHLART_DISCOUNTVALUEPCT     5
 #define N_NACHLART_DISCOUNTVALUEPCT     2
 #define L_NACHLART_MENGEBESTELLT        11
 #define L_NACHLART_PREIS_TYP            6


 #define L_NACHLART_PKEY 39

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define NACHLART_ANZ ( sizeof(NACHLART_BES) / sizeof(struct buf_desc) )
#endif
 #define G_NACHLART sizeof(struct NACHLART)


 #define NACHLART_H

 #define NACHLART_LISTE \
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
 			ARTIKEL.DARREICHFORM, \
 			ARTIKEL.EINHEIT, \
 			ARTIKEL.ARTIKEL_NAME, \
 			ARTIKEL.BESTAND, \
 			ARTIKEL.VERTRIEBSZENTRUMNR, \
 			NACHLIEFERPOS.PREISEKAPONETTO, \
 			NACHLIEFERPOS.KDAUFTRAGART, \
 			NACHLIEFERPOS.CODE_TYPE, \
 			NACHLIEFERPOS.ARTICLE_CODE, \
 			NACHLIEFERPOS.DISCOUNTVALUEPCT, \
 			NACHLIEFERPOS.MENGEBESTELLT, \
 			NACHLIEFERPOS.PREIS_TYP
 #define NACHLART_PLISTE \
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
 			"ARTIKEL.DARREICHFORM," \
 			"ARTIKEL.EINHEIT," \
 			"ARTIKEL.ARTIKEL_NAME," \
 			"ARTIKEL.BESTAND," \
 			"ARTIKEL.VERTRIEBSZENTRUMNR," \
 			"NACHLIEFERPOS.PREISEKAPONETTO," \
 			"NACHLIEFERPOS.KDAUFTRAGART," \
 			"NACHLIEFERPOS.CODE_TYPE," \
 			"NACHLIEFERPOS.ARTICLE_CODE," \
 			"NACHLIEFERPOS.DISCOUNTVALUEPCT," \
 			"NACHLIEFERPOS.MENGEBESTELLT," \
 			"NACHLIEFERPOS.PREIS_TYP "

 #define NACHLART_PELISTE \
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
 			"DARREICHFORM," \
 			"EINHEIT," \
 			"ARTIKEL_NAME," \
 			"BESTAND," \
 			"VERTRIEBSZENTRUMNR," \
 			"PREISEKAPONETTO," \
 			"KDAUFTRAGART," \
 			"CODE_TYPE," \
 			"ARTICLE_CODE," \
 			"DISCOUNTVALUEPCT," \
 			"MENGEBESTELLT," \
 			"PREIS_TYP "

 #define NACHLART_UPDLISTE \
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
 			"DARREICHFORM=?," \
 			"EINHEIT=?," \
 			"ARTIKEL_NAME=?," \
 			"BESTAND=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"PREISEKAPONETTO=?," \
 			"KDAUFTRAGART=?," \
 			"CODE_TYPE=?," \
 			"ARTICLE_CODE=?," \
 			"DISCOUNTVALUEPCT=?," \
 			"MENGEBESTELLT=?," \
 			"PREIS_TYP=? "

 #define NACHLARTKDAUFTRAGNR                   0
 #define NACHLARTPOSNR                         1
 #define NACHLARTDATUM                         2
 #define NACHLARTPOSTYP                        3
 #define NACHLARTIDFNR                         4
 #define NACHLARTARTIKEL_NR                    5
 #define NACHLARTMENGE                         6
 #define NACHLARTFILIALNR1                     7
 #define NACHLARTFILIALNR2                     8
 #define NACHLARTFILIALNR3                     9
 #define NACHLARTSTATUS                        10
 #define NACHLARTDARREICHFORM                  11
 #define NACHLARTEINHEIT                       12
 #define NACHLARTARTIKEL_NAME                  13
 #define NACHLARTBESTAND                       14
 #define NACHLARTVERTRIEBSZENTRUMNR            15
 #define NACHLARTPREISEKAPONETTO               16
 #define NACHLARTKDAUFTRAGART	               17
 #define NACHLARTCODE_TYPE		               18
 #define NACHLARTARTICLE_CODE	               19
 #define NACHLARTDISCOUNTVALUEPCT	           20
 #define NACHLARTMENGEBESTELLT	               21
 #define NACHLARTPREIS_TYP					   22

 #define NACHLART_ZEIGER(xxx) \
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
 			:xxx->DARREICHFORM,\
 			:xxx->EINHEIT,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->BESTAND,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->PREISEKAPONETTO,\
 			:xxx->KDAUFTRAGART,\
 			:xxx->CODE_TYPE,\
 			:xxx->ARTICLE_CODE,\
 			:xxx->DISCOUNTVALUEPCT,\
 			:xxx->MENGEBESTELLT,\
 			:xxx->PREIS_TYP

 #define NACHLART_UPDATE(xxx) \
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
 			DARREICHFORM = :xxx->DARREICHFORM,\
 			EINHEIT = :xxx->EINHEIT,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			BESTAND = :xxx->BESTAND,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			PREISEKAPONETTO = :xxx->PREISEKAPONETTO,\
 			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
 			CODE_TYPE = :xxx->CODE_TYPE,\
 			ARTICLE_CODE = :xxx->ARTICLE_CODE,\
 			DISCOUNTVALUEPCT = :xxx->DISCOUNTVALUEPCT,\
 			MENGEBESTELLT = :xxx->MENGEBESTELLT,\
 			PREIS_TYP = :xxx->PREIS_TYP

 #define LS_NACHLART_KDAUFTRAGNR          11
 #define LS_NACHLART_POSNR                11
 #define LS_NACHLART_DATUM                11
 #define LS_NACHLART_POSTYP               7
 #define LS_NACHLART_IDFNR                11
 #define LS_NACHLART_ARTIKEL_NR           11
 #define LS_NACHLART_MENGE                11
 #define LS_NACHLART_FILIALNR1            7
 #define LS_NACHLART_FILIALNR2            7
 #define LS_NACHLART_FILIALNR3            7
 #define LS_NACHLART_STATUS               7
 #define LS_NACHLART_DARREICHFORM         4
 #define LS_NACHLART_EINHEIT              10
 #define LS_NACHLART_ARTIKEL_NAME         31
 #define LS_NACHLART_BESTAND              11
 #define LS_NACHLART_VERTRIEBSZENTRUMNR   7
 #define LS_NACHLART_PREISEKAPONETTO      11
 #define LS_NACHLART_KDAUFTRAGART	      3
 #define LS_NACHLART_CODE_TYPE			  7
 #define LS_NACHLART_ARTICLE_CODE	      26
 #define LS_NACHLART_DISCOUNTVALUEPCT     11
 #define LS_NACHLART_MENGEBESTELLT        11
 #define LS_NACHLART_PREIS_TYP			  7
 #define LS_NACHLART_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct NACHLART {
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
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    BESTAND;
		 short   VERTRIEBSZENTRUMNR;
		 double  PREISEKAPONETTO;
		 char    KDAUFTRAGART[2 + 1];
		 short   CODE_TYPE;
		 char    ARTICLE_CODE[25 + 1];
		 double  DISCOUNTVALUEPCT;
		 long    MENGEBESTELLT;
		 short   PREIS_TYP;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_NACHLART {
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
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    BESTAND;
		 short   VERTRIEBSZENTRUMNR;
		 double  PREISEKAPONETTO;
		 char    KDAUFTRAGART[2 + 1];
		 short   CODE_TYPE;
		 char    ARTICLE_CODE[25 + 1];
		 double  DISCOUNTVALUEPCT;
		 long    MENGEBESTELLT;
		 short   PREIS_TYP;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_NACHLART {
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
		 short  DARREICHFORM;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  BESTAND;
		 short  VERTRIEBSZENTRUMNR;
		 short  PREISEKAPONETTO;
		 short  KDAUFTRAGART;
		 short  CODE_TYPE;
		 short  ARTICLE_CODE;
		 short  DISCOUNTVALUEPCT;
		 short  MENGEBESTELLT;
		 short  PREIS_TYP;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_NACHLART {
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
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    BESTAND[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    PREISEKAPONETTO[9 + 2];
		 char    KDAUFTRAGART[2 + 1];
		 char    CODE_TYPE[7];
		 char    ARTICLE_CODE[25 + 1];
		 char    DISCOUNTVALUEPCT[5 + 2];
		 char    MENGEBESTELLT[11];
		 char    PREIS_TYP[7];
		 char    FETCH_REL[11];
       };

 struct O_NACHLART {
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
		 char    DARREICHFORM[3];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    BESTAND[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    PREISEKAPONETTO[9];
		 char    KDAUFTRAGART[2];
		 char    CODE_TYPE[7];
		 char    ARTICLE_CODE[25];
		 char    DISCOUNTVALUEPCT[5];
		 char    MENGEBESTELLT[11];
		 char    PREIS_TYP[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc NACHLART_BES [] =
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
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NACHLART_BES [] =
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
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   25 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CNACHLART
 {
  public:

  NACHLART s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, NACHLART_BES, NACHLART_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,NACHLART_BES, NACHLART_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,NACHLART_BES, NACHLART_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CNACHLART()
  {
   ::buf_default((void *)&s, NACHLART_BES, NACHLART_ANZ);
  }
 };
#endif

#define NACHLART_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
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
		 DARREICHFORM CHAR(3)           ,\
		 EINHEIT CHAR(9)           ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 BESTAND INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 PREISEKAPONETTO DECIMAL(9,2)      ,\
		 KDAUFTRAGART CHAR(3)           ,\
		 CODE_TYPE SMALLINT          ,\
		 ARTICLE_CODE CHAR(25)          ,\
		 DISCOUNTVALUEPCT DECIMAL(5,2)      ,\
		 MENGEBESTELLT INTEGER           ,\
		 PREIS_TYP SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 257 LOCK MODE ROW;

#define NACHLART_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_NACHLIEFERPOS_3  on yyy( KDAUFTRAGNR, POSNR, DATUM, POSTYP );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_VERBUNDLIEFERP_2 on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define NACHLART_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_NACHLIEFERPOS_3 ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_VERBUNDLIEFERP_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

