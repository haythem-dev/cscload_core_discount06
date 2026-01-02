/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

#ifndef __AUFTRAG_H
#define __AUFTRAG_H

 #define L_AUFALTLAGORT_FILIALNR             6
 #define L_AUFALTLAGORT_ARTIKEL_NR           11
 #define L_AUFALTLAGORT_BESTAND              11
 #define L_AUFALTLAGORT_DELIVERYDATEIBT      11
 #define L_AUFALTLAGORT_DELIVERYTIMEIBT      11
 #define L_AUFALTLAGORT_IBTTYPENAME          20


 #define L_AUFALTLAGORT_PKEY 17

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFALTLAGORT_ANZ (int) ( sizeof(AUFALTLAGORT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFALTLAGORT sizeof(struct AUFALTLAGORT)


 #define AUFALTLAGORT_H

 #define AUFALTLAGORT_LISTE \
            ARTIKELLAGERORT.FILIALNR, \
            ARTIKELLAGERORT.ARTIKEL_NR, \
            ARTIKELLAGERORT.BESTAND, \
            ARTIKELLAGERORT.DELIVERYDATEIBT, \
            ARTIKELLAGERORT.DELIVERYTIMEIBT, \
            ARTIKELLAGERORT.IBTTYPENAME
 #define AUFALTLAGORT_PLISTE \
            "ARTIKELLAGERORT.FILIALNR," \
            "ARTIKELLAGERORT.ARTIKEL_NR," \
            "ARTIKELLAGERORT.BESTAND," \
            "ARTIKELLAGERORT.DELIVERYDATEIBT," \
            "ARTIKELLAGERORT.DELIVERYTIMEIBT," \
            "ARTIKELLAGERORT.IBTTYPENAME "

 #define AUFALTLAGORT_PELISTE \
            "FILIALNR," \
            "ARTIKEL_NR," \
            "BESTAND," \
            "DELIVERYDATEIBT," \
            "DELIVERYTIMEIBT," \
            "IBTTYPENAME "

 #define AUFALTLAGORT_UPDLISTE \
            "FILIALNR=?," \
            "ARTIKEL_NR=?," \
            "BESTAND=?," \
            "DELIVERYDATEIBT=?," \
            "DELIVERYTIMEIBT=?," \
            "IBTTYPENAME=? "

 #define AUFALTLAGORTFILIALNR                      0
 #define AUFALTLAGORTARTIKEL_NR                    1
 #define AUFALTLAGORTBESTAND                       2
 #define AUFALTLAGORTDELIVERYDATEIBT               3
 #define AUFALTLAGORTDELIVERYTIMEIBT               4
 #define AUFALTLAGORTIBTTYPENAME                   5

 #define AUFALTLAGORT_ZEIGER(xxx) \
            :xxx->FILIALNR,\
            :xxx->ARTIKEL_NR,\
            :xxx->BESTAND,\
            :xxx->DELIVERYDATEIBT,\
            :xxx->DELIVERYTIMEIBT,\
            :xxx->IBTTYPENAME

 #define AUFALTLAGORT_UPDATE(xxx) \
            FILIALNR = :xxx->FILIALNR,\
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            BESTAND = :xxx->BESTAND,\
            DELIVERYDATEIBT = :xxx->DELIVERYDATEIBT,\
            DELIVERYTIMEIBT = :xxx->DELIVERYTIMEIBT,\
            IBTTYPENAME = :xxx->IBTTYPENAME

 #define LS_AUFALTLAGORT_FILIALNR             7
 #define LS_AUFALTLAGORT_ARTIKEL_NR           11
 #define LS_AUFALTLAGORT_BESTAND              11
 #define LS_AUFALTLAGORT_DELIVERYDATEIBT      11
 #define LS_AUFALTLAGORT_DELIVERYTIMEIBT      11
 #define LS_AUFALTLAGORT_IBTTYPENAME          21
 #define LS_AUFALTLAGORT_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFALTLAGORT {
         short   FILIALNR;
         long    ARTIKEL_NR;
         long    BESTAND;
         long    DELIVERYDATEIBT;
         long    DELIVERYTIMEIBT;
         char    IBTTYPENAME[20 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFALTLAGORT {
         short   FILIALNR;
         long    ARTIKEL_NR;
         long    BESTAND;
         long    DELIVERYDATEIBT;
         long    DELIVERYTIMEIBT;
         char    IBTTYPENAME[20 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFALTLAGORT {
         short  FILIALNR;
         short  ARTIKEL_NR;
         short  BESTAND;
         short  DELIVERYDATEIBT;
         short  DELIVERYTIMEIBT;
         short  IBTTYPENAME;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFALTLAGORT {
         char    FILIALNR[7];
         char    ARTIKEL_NR[11];
         char    BESTAND[11];
         char    DELIVERYDATEIBT[11];
         char    DELIVERYTIMEIBT[11];
         char    IBTTYPENAME[20 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFALTLAGORT {
         char    FILIALNR[7];
         char    ARTIKEL_NR[11];
         char    BESTAND[11];
         char    DELIVERYDATEIBT[11];
         char    DELIVERYTIMEIBT[11];
         char    IBTTYPENAME[20];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFALTLAGORT_BES [] =
 {
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   20 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFALTLAGORT_BES [] =
 {
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C ,  20 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFALTLAGORT
 {
  public:

  AUFALTLAGORT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFALTLAGORT_BES, AUFALTLAGORT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFALTLAGORT_BES, AUFALTLAGORT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFALTLAGORT()
  {
   ::buf_default((void *)&s, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
  }
 };
#endif

#define AUFALTLAGORT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         FILIALNR SMALLINT          ,\
         ARTIKEL_NR INTEGER           ,\
         BESTAND INTEGER           ,\
         DELIVERYDATEIBT INTEGER           ,\
         DELIVERYTIMEIBT INTEGER           ,\
         IBTTYPENAME CHAR(20)           ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 60176 LOCK MODE ROW;

#define AUFALTLAGORT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_5 on yyy( FILIALNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_2 on yyy( FILIALNR, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLAGERORT_ on yyy( FILIALNR, ARTIKEL_NR, LAGERBEREICHNR, STATIONNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_4 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFALTLAGORT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_5;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGERORT_;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_4;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFARTES_KDAUFTRAGART         2
 #define L_AUFARTES_IDFNR                11
 #define L_AUFARTES_BEZEICHNUNG          30
 #define L_AUFARTES_VALUTAMONATE         11
 #define L_AUFARTES_KUNDENNR             11
 #define L_AUFARTES_VERTRIEBSZENTRUMNR   6
 #define L_AUFARTES_SMUSTSUBORDER        1
 #define L_AUFARTES_SONLYEH              1


 #define L_AUFARTES_PKEY 15

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFARTES_ANZ (int) ( sizeof(AUFARTES_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFARTES sizeof(struct AUFARTES)


 #define AUFARTES_H

 #define AUFARTES_LISTE \
            KDAUFTRAGART.KDAUFTRAGART, \
            AUFTRAGARTKD.IDFNR, \
            KDAUFTRAGART.BEZEICHNUNG, \
            AADUMMY.VALUTAMONATE, \
            AUFTRAGARTKD.KUNDENNR, \
            AUFTRAGARTKD.VERTRIEBSZENTRUMNR, \
            KDAUFTRAGART.SMUSTSUBORDER, \
            KDAUFTRAGART.SONLYEH

 #define AUFARTES_PLISTE \
            "KDAUFTRAGART.KDAUFTRAGART," \
            "AUFTRAGARTKD.IDFNR," \
            "KDAUFTRAGART.BEZEICHNUNG," \
            "AADUMMY.VALUTAMONATE," \
            "AUFTRAGARTKD.KUNDENNR," \
            "AUFTRAGARTKD.VERTRIEBSZENTRUMNR," \
            "KDAUFTRAGART.SMUSTSUBORDER," \
            "KDAUFTRAGART.SONLYEH "

 #define AUFARTES_PELISTE \
            "KDAUFTRAGART," \
            "IDFNR," \
            "BEZEICHNUNG," \
            "VALUTAMONATE," \
            "KUNDENNR," \
            "VERTRIEBSZENTRUMNR," \
            "SMUSTSUBORDER," \
            "SONLYEH "

 #define AUFARTES_UPDLISTE \
            "KDAUFTRAGART=?," \
            "IDFNR=?," \
            "BEZEICHNUNG=?," \
            "VALUTAMONATE=?," \
            "KUNDENNR=?," \
            "VERTRIEBSZENTRUMNR=?," \
            "SMUSTSUBORDER=?," \
            "SONLYEH=? "

 #define AUFARTESKDAUFTRAGART                  0
 #define AUFARTESIDFNR                         1
 #define AUFARTESBEZEICHNUNG                   2
 #define AUFARTESVALUTAMONATE                  3
 #define AUFARTESKUNDENNR                       4
 #define AUFARTESVERTRIEBSZENTRUMNR             5
 #define AUFARTESSMUSTSUBORDER                  6
 #define AUFARTESSONLYEH                        7

 #define AUFARTES_ZEIGER(xxx) \
            :xxx->KDAUFTRAGART,\
            :xxx->IDFNR,\
            :xxx->BEZEICHNUNG,\
            :xxx->VALUTAMONATE,\
            :xxx->KUNDENNR,\
            :xxx->VERTRIEBSZENTRUMNR,\
            :xxx->SMUSTSUBORDER,\
            :xxx->SONLYEH

 #define AUFARTES_UPDATE(xxx) \
            KDAUFTRAGART = :xxx->KDAUFTRAGART,\
            IDFNR = :xxx->IDFNR,\
            BEZEICHNUNG = :xxx->BEZEICHNUNG,\
            VALUTAMONATE = :xxx->VALUTAMONATE,\
            KUNDENNR = :xxx->KUNDENNR,\
            VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
            SMUSTSUBORDER = :xxx->SMUSTSUBORDER,\
            SONLYEH = :xxx->SONLYEH

 #define LS_AUFARTES_KDAUFTRAGART         3
 #define LS_AUFARTES_IDFNR                11
 #define LS_AUFARTES_BEZEICHNUNG          31
 #define LS_AUFARTES_VALUTAMONATE         11
 #define LS_AUFARTES_KUNDENNR             11
 #define LS_AUFARTES_VERTRIEBSZENTRUMNR   7
 #define LS_AUFARTES_SMUSTSUBORDER        2
 #define LS_AUFARTES_SONLYEH              2
 #define LS_AUFARTES_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFARTES {
         char    KDAUFTRAGART[2 + 1];
         long    IDFNR;
         char    BEZEICHNUNG[30 + 1];
         long    VALUTAMONATE;
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         char    SMUSTSUBORDER[1 + 1];
         char    SONLYEH[1 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFARTES {
         char    KDAUFTRAGART[2 + 1];
         long    IDFNR;
         char    BEZEICHNUNG[30 + 1];
         long    VALUTAMONATE;
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         char    SMUSTSUBORDER;
         char    SONLYEH;
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFARTES {
         short  KDAUFTRAGART;
         short  IDFNR;
         short  BEZEICHNUNG;
         short  VALUTAMONATE;
         short  KUNDENNR;
         short  VERTRIEBSZENTRUMNR;
         short  SMUSTSUBORDER;
         short  SONLYEH;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFARTES {
         char    KDAUFTRAGART[2 + 1];
         char    IDFNR[11];
         char    BEZEICHNUNG[30 + 1];
         char    VALUTAMONATE[11];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7];
         char    SMUSTSUBORDER[1 + 1];
         char    SONLYEH[1 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFARTES {
         char    KDAUFTRAGART[2];
         char    IDFNR[11];
         char    BEZEICHNUNG[30];
         char    VALUTAMONATE[11];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7];
         char    SMUSTSUBORDER[1];
         char    SONLYEH[1];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFARTES_BES [] =
 {
     { TYP_C ,    2 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFARTES_BES [] =
 {
     { TYP_C,    2 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_S ,   5 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFARTES
 {
  public:

  AUFARTES s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFARTES_BES, AUFARTES_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFARTES_BES, AUFARTES_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFARTES_BES, AUFARTES_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFARTES()
  {
   ::buf_default((void *)&s, AUFARTES_BES, AUFARTES_ANZ);
  }
 };
#endif

#define AUFARTES_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         KDAUFTRAGART CHAR(2)           ,\
         IDFNR INTEGER           ,\
         BEZEICHNUNG CHAR(30)          ,\
         VALUTAMONATE INTEGER           ,\
         KUNDENNR INTEGER           ,\
         VERTRIEBSZENTRUMNR SMALLINT          ,\
         SMUSTSUBORDER CHAR(1)           ,\
         SONLYEH CHAR(1)           ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 9 LOCK MODE ROW;

#define AUFARTES_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGARTX      on yyy( KDAUFTRAGART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX AUFTRAGARTKDX      on yyy( IDFNR, KDAUFTRAGART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFARTES_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGARTX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX AUFTRAGARTKDX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFEAN_ARTIKEL_NR           11
 #define L_AUFEAN_EAN_NR               13


 #define L_AUFEAN_PKEY 24

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFEAN_ANZ (int) ( sizeof(AUFEAN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFEAN sizeof(struct AUFEAN)


 #define AUFEAN_H

 #define AUFEAN_LISTE \
            EAN.ARTIKEL_NR, \
            EAN.EAN_NR
 #define AUFEAN_PLISTE \
            "EAN.ARTIKEL_NR," \
            "EAN.EAN_NR "

 #define AUFEAN_PELISTE \
            "ARTIKEL_NR," \
            "EAN_NR "

 #define AUFEAN_UPDLISTE \
            "ARTIKEL_NR=?," \
            "EAN_NR=? "

 #define AUFEANARTIKEL_NR                    0
 #define AUFEANEAN_NR                        1

 #define AUFEAN_ZEIGER(xxx) \
            :xxx->ARTIKEL_NR,\
            :xxx->EAN_NR

 #define AUFEAN_UPDATE(xxx) \
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            EAN_NR = :xxx->EAN_NR

 #define LS_AUFEAN_ARTIKEL_NR           11
 #define LS_AUFEAN_EAN_NR               14

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFEAN {
         long    ARTIKEL_NR;
         char    EAN_NR[13 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFEAN {
         long    ARTIKEL_NR;
         char    EAN_NR[13 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFEAN {
         short  ARTIKEL_NR;
         short  EAN_NR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFEAN {
         char    ARTIKEL_NR[11];
         char    EAN_NR[13 + 1];
       };

 struct O_AUFEAN {
         char    ARTIKEL_NR[11];
         char    EAN_NR[13];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFEAN_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   13 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFEAN_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_C,   13 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFEAN
 {
  public:

  AUFEAN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFEAN_BES, AUFEAN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFEAN_BES, AUFEAN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFEAN_BES, AUFEAN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFEAN()
  {
   ::buf_default((void *)&s, AUFEAN_BES, AUFEAN_ANZ);
  }
 };
#endif

#define AUFEAN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ARTIKEL_NR INTEGER           ,\
         EAN_NR CHAR(13)            ) EXTENT SIZE 5724 LOCK MODE ROW;

#define AUFEAN_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX EAN_IDX1           on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX EAN_IDX2           on yyy( EAN_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFEAN_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX EAN_IDX1          ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX EAN_IDX2          ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFENDART_ARTIKEL_NR           11
 #define L_AUFENDART_NORMPACKUNG          2
 #define L_AUFENDART_EINHEIT              9
 #define L_AUFENDART_ARTIKEL_NAME         30
 #define L_AUFENDART_BESTAND              11
 #define L_AUFENDART_LAGERBEREICHNR       6
 #define L_AUFENDART_STATIONNR            2
 #define L_AUFENDART_LAGERFACHNR          10


 #define L_AUFENDART_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFENDART_ANZ (int) ( sizeof(AUFENDART_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFENDART sizeof(struct AUFENDART)


 #define AUFENDART_H

 #define AUFENDART_LISTE \
            ARTIKEL.ARTIKEL_NR, \
            ARTIKEL.NORMPACKUNG, \
            ARTIKEL.EINHEIT, \
            ARTIKEL.ARTIKEL_NAME, \
            ARTIKEL.BESTAND, \
            ARTIKEL.LAGERBEREICHNR, \
            ARTIKEL.STATIONNR, \
            ARTIKEL.LAGERFACHNR
 #define AUFENDART_PLISTE \
            "ARTIKEL.ARTIKEL_NR," \
            "ARTIKEL.NORMPACKUNG," \
            "ARTIKEL.EINHEIT," \
            "ARTIKEL.ARTIKEL_NAME," \
            "ARTIKEL.BESTAND," \
            "ARTIKEL.LAGERBEREICHNR," \
            "ARTIKEL.STATIONNR," \
            "ARTIKEL.LAGERFACHNR "

 #define AUFENDART_PELISTE \
            "ARTIKEL_NR," \
            "NORMPACKUNG," \
            "EINHEIT," \
            "ARTIKEL_NAME," \
            "BESTAND," \
            "LAGERBEREICHNR," \
            "STATIONNR," \
            "LAGERFACHNR "

 #define AUFENDART_UPDLISTE \
            "ARTIKEL_NR=?," \
            "NORMPACKUNG=?," \
            "EINHEIT=?," \
            "ARTIKEL_NAME=?," \
            "BESTAND=?," \
            "LAGERBEREICHNR=?," \
            "STATIONNR=?," \
            "LAGERFACHNR=? "

 #define AUFENDARTARTIKEL_NR                    0
 #define AUFENDARTNORMPACKUNG                   1
 #define AUFENDARTEINHEIT                       2
 #define AUFENDARTARTIKEL_NAME                  3
 #define AUFENDARTBESTAND                       4
 #define AUFENDARTLAGERBEREICHNR                5
 #define AUFENDARTSTATIONNR                     6
 #define AUFENDARTLAGERFACHNR                   7

 #define AUFENDART_ZEIGER(xxx) \
            :xxx->ARTIKEL_NR,\
            :xxx->NORMPACKUNG,\
            :xxx->EINHEIT,\
            :xxx->ARTIKEL_NAME,\
            :xxx->BESTAND,\
            :xxx->LAGERBEREICHNR,\
            :xxx->STATIONNR,\
            :xxx->LAGERFACHNR

 #define AUFENDART_UPDATE(xxx) \
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            NORMPACKUNG = :xxx->NORMPACKUNG,\
            EINHEIT = :xxx->EINHEIT,\
            ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
            BESTAND = :xxx->BESTAND,\
            LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
            STATIONNR = :xxx->STATIONNR,\
            LAGERFACHNR = :xxx->LAGERFACHNR

 #define LS_AUFENDART_ARTIKEL_NR           11
 #define LS_AUFENDART_NORMPACKUNG          3
 #define LS_AUFENDART_EINHEIT              10
 #define LS_AUFENDART_ARTIKEL_NAME         31
 #define LS_AUFENDART_BESTAND              11
 #define LS_AUFENDART_LAGERBEREICHNR       7
 #define LS_AUFENDART_STATIONNR            3
 #define LS_AUFENDART_LAGERFACHNR          11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFENDART {
         long    ARTIKEL_NR;
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    BESTAND;
         short   LAGERBEREICHNR;
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFENDART {
         long    ARTIKEL_NR;
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    BESTAND;
         short   LAGERBEREICHNR;
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFENDART {
         short  ARTIKEL_NR;
         short  NORMPACKUNG;
         short  EINHEIT;
         short  ARTIKEL_NAME;
         short  BESTAND;
         short  LAGERBEREICHNR;
         short  STATIONNR;
         short  LAGERFACHNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFENDART {
         char    ARTIKEL_NR[11];
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         char    BESTAND[11];
         char    LAGERBEREICHNR[7];
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
       };

 struct O_AUFENDART {
         char    ARTIKEL_NR[11];
         char    NORMPACKUNG[2];
         char    EINHEIT[9];
         char    ARTIKEL_NAME[30];
         char    BESTAND[11];
         char    LAGERBEREICHNR[7];
         char    STATIONNR[2];
         char    LAGERFACHNR[10];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFENDART_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_C ,    9 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_C ,   10 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFENDART_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_C,    9 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_C,   10 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFENDART
 {
  public:

  AUFENDART s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFENDART_BES, AUFENDART_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFENDART_BES, AUFENDART_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFENDART_BES, AUFENDART_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFENDART()
  {
   ::buf_default((void *)&s, AUFENDART_BES, AUFENDART_ANZ);
  }
 };
#endif

#define AUFENDART_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ARTIKEL_NR INTEGER           ,\
         NORMPACKUNG CHAR(2)           ,\
         EINHEIT CHAR(9)           ,\
         ARTIKEL_NAME CHAR(30)          ,\
         BESTAND INTEGER           ,\
         LAGERBEREICHNR SMALLINT          ,\
         STATIONNR CHAR(2)           ,\
         LAGERFACHNR CHAR(10)            ) EXTENT SIZE 26232 LOCK MODE ROW;

#define AUFENDART_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFENDART_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFENDKOPF_KDAUFTRAGNR          11
 #define L_AUFENDKOPF_IDFNR                11
 #define L_AUFENDKOPF_TOURID               6
 #define L_AUFENDKOPF_RECHNUNGNR           11
 #define L_AUFENDKOPF_ZEIT                 11
 #define L_AUFENDKOPF_FILIALNR             6
 #define L_AUFENDKOPF_KDNR                 11
 #define L_AUFENDKOPF_NAMEAPO              40
 #define L_AUFENDKOPF_NAMEINHABER          30
 #define L_AUFENDKOPF_STRASSE              40
 #define L_AUFENDKOPF_ORT                  30
 #define L_AUFENDKOPF_POSTLEITZAHL         7


 #define L_AUFENDKOPF_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFENDKOPF_ANZ (int) ( sizeof(AUFENDKOPF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFENDKOPF sizeof(struct AUFENDKOPF)


 #define AUFENDKOPF_H

 #define AUFENDKOPF_LISTE \
            KDAUFTRAG.KDAUFTRAGNR, \
            KDAUFTRAG.IDFNR, \
            KDAUFTRAG.TOURID, \
            KDAUFTRAG.RECHNUNGNR, \
            KDAUFTRAGEREIGNIS.ZEIT, \
            KUNDE.FILIALNR, \
            KUNDE.KDNR, \
            KUNDE.NAMEAPO, \
            KUNDE.NAMEINHABER, \
            KUNDE.STRASSE, \
            KUNDE.ORT, \
            KUNDE.POSTLEITZAHL
 #define AUFENDKOPF_PLISTE \
            "KDAUFTRAG.KDAUFTRAGNR," \
            "KDAUFTRAG.IDFNR," \
            "KDAUFTRAG.TOURID," \
            "KDAUFTRAG.RECHNUNGNR," \
            "KDAUFTRAGEREIGNIS.ZEIT," \
            "KUNDE.FILIALNR," \
            "KUNDE.KDNR," \
            "KUNDE.NAMEAPO," \
            "KUNDE.NAMEINHABER," \
            "KUNDE.STRASSE," \
            "KUNDE.ORT," \
            "KUNDE.POSTLEITZAHL "

 #define AUFENDKOPF_PELISTE \
            "KDAUFTRAGNR," \
            "IDFNR," \
            "TOURID," \
            "RECHNUNGNR," \
            "ZEIT," \
            "FILIALNR," \
            "KDNR," \
            "NAMEAPO," \
            "NAMEINHABER," \
            "STRASSE," \
            "ORT," \
            "POSTLEITZAHL "

 #define AUFENDKOPF_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "IDFNR=?," \
            "TOURID=?," \
            "RECHNUNGNR=?," \
            "ZEIT=?," \
            "FILIALNR=?," \
            "KDNR=?," \
            "NAMEAPO=?," \
            "NAMEINHABER=?," \
            "STRASSE=?," \
            "ORT=?," \
            "POSTLEITZAHL=? "

 #define AUFENDKOPFKDAUFTRAGNR                   0
 #define AUFENDKOPFIDFNR                         1
 #define AUFENDKOPFTOURID                        2
 #define AUFENDKOPFRECHNUNGNR                    3
 #define AUFENDKOPFZEIT                          4
 #define AUFENDKOPFFILIALNR                      5
 #define AUFENDKOPFKDNR                          6
 #define AUFENDKOPFNAMEAPO                       7
 #define AUFENDKOPFNAMEINHABER                   8
 #define AUFENDKOPFSTRASSE                       9
 #define AUFENDKOPFORT                           10
 #define AUFENDKOPFPOSTLEITZAHL                  11

 #define AUFENDKOPF_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR,\
            :xxx->IDFNR,\
            :xxx->TOURID,\
            :xxx->RECHNUNGNR,\
            :xxx->ZEIT,\
            :xxx->FILIALNR,\
            :xxx->KDNR,\
            :xxx->NAMEAPO,\
            :xxx->NAMEINHABER,\
            :xxx->STRASSE,\
            :xxx->ORT,\
            :xxx->POSTLEITZAHL

 #define AUFENDKOPF_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            IDFNR = :xxx->IDFNR,\
            TOURID = :xxx->TOURID,\
            RECHNUNGNR = :xxx->RECHNUNGNR,\
            ZEIT = :xxx->ZEIT,\
            FILIALNR = :xxx->FILIALNR,\
            KDNR = :xxx->KDNR,\
            NAMEAPO = :xxx->NAMEAPO,\
            NAMEINHABER = :xxx->NAMEINHABER,\
            STRASSE = :xxx->STRASSE,\
            ORT = :xxx->ORT,\
            POSTLEITZAHL = :xxx->POSTLEITZAHL

 #define LS_AUFENDKOPF_KDAUFTRAGNR          11
 #define LS_AUFENDKOPF_IDFNR                11
 #define LS_AUFENDKOPF_TOURID               7
 #define LS_AUFENDKOPF_RECHNUNGNR           11
 #define LS_AUFENDKOPF_ZEIT                 11
 #define LS_AUFENDKOPF_FILIALNR             7
 #define LS_AUFENDKOPF_KDNR                 11
 #define LS_AUFENDKOPF_NAMEAPO              41
 #define LS_AUFENDKOPF_NAMEINHABER          31
 #define LS_AUFENDKOPF_STRASSE              41
 #define LS_AUFENDKOPF_ORT                  31
 #define LS_AUFENDKOPF_POSTLEITZAHL         8

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFENDKOPF {
         long    KDAUFTRAGNR;
         long    IDFNR;
         char    TOURID[6 + 1];
         long    RECHNUNGNR;
         long    ZEIT;
         short   FILIALNR;
         long    KDNR;
         char    NAMEAPO[40 + 1];
         char    NAMEINHABER[30 + 1];
         char    STRASSE[40 + 1];
         char    ORT[30 + 1];
         char    POSTLEITZAHL[7 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFENDKOPF {
         long    KDAUFTRAGNR;
         long    IDFNR;
         char    TOURID[6 + 1];
         long    RECHNUNGNR;
         long    ZEIT;
         short   FILIALNR;
         long    KDNR;
         char    NAMEAPO[40 + 1];
         char    NAMEINHABER[30 + 1];
         char    STRASSE[40 + 1];
         char    ORT[30 + 1];
         char    POSTLEITZAHL[7 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFENDKOPF {
         short  KDAUFTRAGNR;
         short  IDFNR;
         short  TOURID;
         short  RECHNUNGNR;
         short  ZEIT;
         short  FILIALNR;
         short  KDNR;
         short  NAMEAPO;
         short  NAMEINHABER;
         short  STRASSE;
         short  ORT;
         short  POSTLEITZAHL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFENDKOPF {
         char    KDAUFTRAGNR[11];
         char    IDFNR[11];
         char    TOURID[6 + 1];
         char    RECHNUNGNR[11];
         char    ZEIT[11];
         char    FILIALNR[7];
         char    KDNR[11];
         char    NAMEAPO[40 + 1];
         char    NAMEINHABER[30 + 1];
         char    STRASSE[40 + 1];
         char    ORT[30 + 1];
         char    POSTLEITZAHL[7 + 1];
       };

 struct O_AUFENDKOPF {
         char    KDAUFTRAGNR[11];
         char    IDFNR[11];
         char    TOURID[6];
         char    RECHNUNGNR[11];
         char    ZEIT[11];
         char    FILIALNR[7];
         char    KDNR[11];
         char    NAMEAPO[40];
         char    NAMEINHABER[30];
         char    STRASSE[40];
         char    ORT[30];
         char    POSTLEITZAHL[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFENDKOPF_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   40 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_C ,   40 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_C ,    7 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFENDKOPF_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_C,    7 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFENDKOPF
 {
  public:

  AUFENDKOPF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFENDKOPF_BES, AUFENDKOPF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFENDKOPF_BES, AUFENDKOPF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFENDKOPF_BES, AUFENDKOPF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFENDKOPF()
  {
   ::buf_default((void *)&s, AUFENDKOPF_BES, AUFENDKOPF_ANZ);
  }
 };
#endif

#define AUFENDKOPF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         KDAUFTRAGNR INTEGER           ,\
         IDFNR INTEGER           ,\
         TOURID CHAR(6)           ,\
         RECHNUNGNR INTEGER           ,\
         ZEIT INTEGER           ,\
         FILIALNR SMALLINT          ,\
         KDNR INTEGER           ,\
         NAMEAPO CHAR(40)          ,\
         NAMEINHABER CHAR(30)          ,\
         STRASSE CHAR(40)          ,\
         ORT CHAR(30)          ,\
         POSTLEITZAHL CHAR(7)             ) EXTENT SIZE 1458 LOCK MODE ROW;

#define AUFENDKOPF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGX         on yyy( KDAUFTRAGNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_304    on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDAUFTRAGTOURX     on yyy( TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KUNDE_315        on yyy( KDNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFENDKOPF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGX        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_304   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDAUFTRAGTOURX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KUNDE_315       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFENDPOS_NORMPACKUNG          2
 #define L_AUFENDPOS_EINHEIT              9
 #define L_AUFENDPOS_ARTIKEL_NAME         30
 #define L_AUFENDPOS_KDAUFTRAGNR          11
 #define L_AUFENDPOS_ARTIKEL_NR           11
 #define L_AUFENDPOS_MENGEBESTELLT        11
 #define L_AUFENDPOS_MENGEGELIEFERT       11
 #define L_AUFENDPOS_KOBEHAELTNR          11
 #define L_AUFENDPOS_LAGERBEREICHNR       6
 #define L_AUFENDPOS_STATIONNR            2
 #define L_AUFENDPOS_LAGERFACHNR          10


 #define L_AUFENDPOS_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFENDPOS_ANZ (int) ( sizeof(AUFENDPOS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFENDPOS sizeof(struct AUFENDPOS)


 #define AUFENDPOS_H

 #define AUFENDPOS_LISTE \
            ARTIKEL.NORMPACKUNG, \
            ARTIKEL.EINHEIT, \
            ARTIKEL.ARTIKEL_NAME, \
            KDAUFTRAGPOS.KDAUFTRAGNR, \
            KDAUFTRAGPOS.ARTIKEL_NR, \
            KDAUFTRAGPOS.MENGEBESTELLT, \
            KDAUFTRAGPOS.MENGEGELIEFERT, \
            KDAUFTRAGPOS.KOBEHAELTNR, \
            KDAUFTRAGPOS.LAGERBEREICHNR, \
            KDAUFTRAGPOS.STATIONNR, \
            KDAUFTRAGPOS.LAGERFACHNR
 #define AUFENDPOS_PLISTE \
            "ARTIKEL.NORMPACKUNG," \
            "ARTIKEL.EINHEIT," \
            "ARTIKEL.ARTIKEL_NAME," \
            "KDAUFTRAGPOS.KDAUFTRAGNR," \
            "KDAUFTRAGPOS.ARTIKEL_NR," \
            "KDAUFTRAGPOS.MENGEBESTELLT," \
            "KDAUFTRAGPOS.MENGEGELIEFERT," \
            "KDAUFTRAGPOS.KOBEHAELTNR," \
            "KDAUFTRAGPOS.LAGERBEREICHNR," \
            "KDAUFTRAGPOS.STATIONNR," \
            "KDAUFTRAGPOS.LAGERFACHNR "

 #define AUFENDPOS_PELISTE \
            "NORMPACKUNG," \
            "EINHEIT," \
            "ARTIKEL_NAME," \
            "KDAUFTRAGNR," \
            "ARTIKEL_NR," \
            "MENGEBESTELLT," \
            "MENGEGELIEFERT," \
            "KOBEHAELTNR," \
            "LAGERBEREICHNR," \
            "STATIONNR," \
            "LAGERFACHNR "

 #define AUFENDPOS_UPDLISTE \
            "NORMPACKUNG=?," \
            "EINHEIT=?," \
            "ARTIKEL_NAME=?," \
            "KDAUFTRAGNR=?," \
            "ARTIKEL_NR=?," \
            "MENGEBESTELLT=?," \
            "MENGEGELIEFERT=?," \
            "KOBEHAELTNR=?," \
            "LAGERBEREICHNR=?," \
            "STATIONNR=?," \
            "LAGERFACHNR=? "

 #define AUFENDPOSNORMPACKUNG                   0
 #define AUFENDPOSEINHEIT                       1
 #define AUFENDPOSARTIKEL_NAME                  2
 #define AUFENDPOSKDAUFTRAGNR                   3
 #define AUFENDPOSARTIKEL_NR                    4
 #define AUFENDPOSMENGEBESTELLT                 5
 #define AUFENDPOSMENGEGELIEFERT                6
 #define AUFENDPOSKOBEHAELTNR                   7
 #define AUFENDPOSLAGERBEREICHNR                8
 #define AUFENDPOSSTATIONNR                     9
 #define AUFENDPOSLAGERFACHNR                   10

 #define AUFENDPOS_ZEIGER(xxx) \
            :xxx->NORMPACKUNG,\
            :xxx->EINHEIT,\
            :xxx->ARTIKEL_NAME,\
            :xxx->KDAUFTRAGNR,\
            :xxx->ARTIKEL_NR,\
            :xxx->MENGEBESTELLT,\
            :xxx->MENGEGELIEFERT,\
            :xxx->KOBEHAELTNR,\
            :xxx->LAGERBEREICHNR,\
            :xxx->STATIONNR,\
            :xxx->LAGERFACHNR

 #define AUFENDPOS_UPDATE(xxx) \
            NORMPACKUNG = :xxx->NORMPACKUNG,\
            EINHEIT = :xxx->EINHEIT,\
            ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            MENGEBESTELLT = :xxx->MENGEBESTELLT,\
            MENGEGELIEFERT = :xxx->MENGEGELIEFERT,\
            KOBEHAELTNR = :xxx->KOBEHAELTNR,\
            LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
            STATIONNR = :xxx->STATIONNR,\
            LAGERFACHNR = :xxx->LAGERFACHNR

 #define LS_AUFENDPOS_NORMPACKUNG          3
 #define LS_AUFENDPOS_EINHEIT              10
 #define LS_AUFENDPOS_ARTIKEL_NAME         31
 #define LS_AUFENDPOS_KDAUFTRAGNR          11
 #define LS_AUFENDPOS_ARTIKEL_NR           11
 #define LS_AUFENDPOS_MENGEBESTELLT        11
 #define LS_AUFENDPOS_MENGEGELIEFERT       11
 #define LS_AUFENDPOS_KOBEHAELTNR          11
 #define LS_AUFENDPOS_LAGERBEREICHNR       7
 #define LS_AUFENDPOS_STATIONNR            3
 #define LS_AUFENDPOS_LAGERFACHNR          11
 #define LS_AUFENDPOS_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFENDPOS {
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    KDAUFTRAGNR;
         long    ARTIKEL_NR;
         long    MENGEBESTELLT;
         long    MENGEGELIEFERT;
         long    KOBEHAELTNR;
         short   LAGERBEREICHNR;
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFENDPOS {
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    KDAUFTRAGNR;
         long    ARTIKEL_NR;
         long    MENGEBESTELLT;
         long    MENGEGELIEFERT;
         long    KOBEHAELTNR;
         short   LAGERBEREICHNR;
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFENDPOS {
         short  NORMPACKUNG;
         short  EINHEIT;
         short  ARTIKEL_NAME;
         short  KDAUFTRAGNR;
         short  ARTIKEL_NR;
         short  MENGEBESTELLT;
         short  MENGEGELIEFERT;
         short  KOBEHAELTNR;
         short  LAGERBEREICHNR;
         short  STATIONNR;
         short  LAGERFACHNR;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFENDPOS {
         char    NORMPACKUNG[2 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         char    KDAUFTRAGNR[11];
         char    ARTIKEL_NR[11];
         char    MENGEBESTELLT[11];
         char    MENGEGELIEFERT[11];
         char    KOBEHAELTNR[11];
         char    LAGERBEREICHNR[7];
         char    STATIONNR[2 + 1];
         char    LAGERFACHNR[10 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFENDPOS {
         char    NORMPACKUNG[2];
         char    EINHEIT[9];
         char    ARTIKEL_NAME[30];
         char    KDAUFTRAGNR[11];
         char    ARTIKEL_NR[11];
         char    MENGEBESTELLT[11];
         char    MENGEGELIEFERT[11];
         char    KOBEHAELTNR[11];
         char    LAGERBEREICHNR[7];
         char    STATIONNR[2];
         char    LAGERFACHNR[10];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFENDPOS_BES [] =
 {
     { TYP_C ,    2 ,   0 },
     { TYP_C ,    9 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_C ,   10 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFENDPOS_BES [] =
 {
     { TYP_C,    2 ,   0 },
     { TYP_C,    9 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFENDPOS
 {
  public:

  AUFENDPOS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFENDPOS_BES, AUFENDPOS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFENDPOS_BES, AUFENDPOS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFENDPOS_BES, AUFENDPOS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFENDPOS()
  {
   ::buf_default((void *)&s, AUFENDPOS_BES, AUFENDPOS_ANZ);
  }
 };
#endif

#define AUFENDPOS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         NORMPACKUNG CHAR(2)           ,\
         EINHEIT CHAR(9)           ,\
         ARTIKEL_NAME CHAR(30)          ,\
         KDAUFTRAGNR INTEGER           ,\
         ARTIKEL_NR INTEGER           ,\
         MENGEBESTELLT INTEGER           ,\
         MENGEGELIEFERT INTEGER           ,\
         KOBEHAELTNR INTEGER           ,\
         LAGERBEREICHNR SMALLINT          ,\
         STATIONNR CHAR(2)           ,\
         LAGERFACHNR CHAR(10)          ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 32182 LOCK MODE ROW;

#define AUFENDPOS_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGPOSX      on yyy( KDAUFTRAGNR, POSNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFENDPOS_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGPOSX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFEREIG_KDAUFTRAGNR          11
 #define L_AUFEREIG_DATUM                11
 #define L_AUFEREIG_ZEIT                 11
 #define L_AUFEREIG_EREIGNISART          6
 #define L_AUFEREIG_GERAETNAME           8
 #define L_AUFEREIG_USERNAME             8
 #define L_AUFEREIG_PERSONALNR           11
 #define L_AUFEREIG_EVENTCODE            6


 #define L_AUFEREIG_PKEY 39

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFEREIG_ANZ (int) ( sizeof(AUFEREIG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFEREIG sizeof(struct AUFEREIG)


 #define AUFEREIG_H

 #define AUFEREIG_LISTE \
            KDAUFTRAGEREIGNIS.KDAUFTRAGNR, \
            KDAUFTRAGEREIGNIS.DATUM, \
            KDAUFTRAGEREIGNIS.ZEIT, \
            KDAUFTRAGEREIGNIS.EREIGNISART, \
            KDAUFTRAGEREIGNIS.GERAETNAME, \
            PASSWD.USERNAME, \
            KDAUFTRAGEREIGNIS.PERSONALNR, \
            KDAUFTRAGEREIGNIS.EVENTCODE
 #define AUFEREIG_PLISTE \
            "KDAUFTRAGEREIGNIS.KDAUFTRAGNR," \
            "KDAUFTRAGEREIGNIS.DATUM," \
            "KDAUFTRAGEREIGNIS.ZEIT," \
            "KDAUFTRAGEREIGNIS.EREIGNISART," \
            "KDAUFTRAGEREIGNIS.GERAETNAME," \
            "PASSWD.USERNAME," \
            "KDAUFTRAGEREIGNIS.PERSONALNR," \
            "KDAUFTRAGEREIGNIS.EVENTCODE "

 #define AUFEREIG_PELISTE \
            "KDAUFTRAGNR," \
            "DATUM," \
            "ZEIT," \
            "EREIGNISART," \
            "GERAETNAME," \
            "USERNAME," \
            "PERSONALNR," \
            "EVENTCODE "

 #define AUFEREIG_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "DATUM=?," \
            "ZEIT=?," \
            "EREIGNISART=?," \
            "GERAETNAME=?," \
            "USERNAME=?," \
            "PERSONALNR=?," \
            "EVENTCODE=? "

 #define AUFEREIGKDAUFTRAGNR                   0
 #define AUFEREIGDATUM                         1
 #define AUFEREIGZEIT                          2
 #define AUFEREIGEREIGNISART                   3
 #define AUFEREIGGERAETNAME                    4
 #define AUFEREIGUSERNAME                      5
 #define AUFEREIGPERSONALNR                    6
 #define AUFEREIGEVENTCODE                     7

 #define AUFEREIG_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR,\
            :xxx->DATUM,\
            :xxx->ZEIT,\
            :xxx->EREIGNISART,\
            :xxx->GERAETNAME,\
            :xxx->USERNAME,\
            :xxx->PERSONALNR,\
            :xxx->EVENTCODE

 #define AUFEREIG_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            DATUM = :xxx->DATUM,\
            ZEIT = :xxx->ZEIT,\
            EREIGNISART = :xxx->EREIGNISART,\
            GERAETNAME = :xxx->GERAETNAME,\
            USERNAME = :xxx->USERNAME,\
            PERSONALNR = :xxx->PERSONALNR,\
            EVENTCODE = :xxx->EVENTCODE

 #define LS_AUFEREIG_KDAUFTRAGNR          11
 #define LS_AUFEREIG_DATUM                11
 #define LS_AUFEREIG_ZEIT                 11
 #define LS_AUFEREIG_EREIGNISART          7
 #define LS_AUFEREIG_GERAETNAME           9
 #define LS_AUFEREIG_USERNAME             9
 #define LS_AUFEREIG_PERSONALNR           11
 #define LS_AUFEREIG_EVENTCODE            7
 #define LS_AUFEREIG_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFEREIG {
         long    KDAUFTRAGNR;
         long    DATUM;
         long    ZEIT;
         short   EREIGNISART;
         char    GERAETNAME[8 + 1];
         char    USERNAME[8 + 1];
         long    PERSONALNR;
         short   EVENTCODE;
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFEREIG {
         long    KDAUFTRAGNR;
         long    DATUM;
         long    ZEIT;
         short   EREIGNISART;
         char    GERAETNAME[8 + 1];
         char    USERNAME[8 + 1];
         long    PERSONALNR;
         short   EVENTCODE;
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFEREIG {
         short  KDAUFTRAGNR;
         short  DATUM;
         short  ZEIT;
         short  EREIGNISART;
         short  GERAETNAME;
         short  USERNAME;
         short  PERSONALNR;
         short   EVENTCODE;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFEREIG {
         char    KDAUFTRAGNR[11];
         char    DATUM[11];
         char    ZEIT[11];
         char    EREIGNISART[7];
         char    GERAETNAME[8 + 1];
         char    USERNAME[8 + 1];
         char    PERSONALNR[11];
         char    EVENTCODE[7];
         char    FETCH_REL[11];
       };

 struct O_AUFEREIG {
         char    KDAUFTRAGNR[11];
         char    DATUM[11];
         char    ZEIT[11];
         char    EREIGNISART[7];
         char    GERAETNAME[8];
         char    USERNAME[8];
         char    PERSONALNR[11];
         char    EVENTCODE[7];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFEREIG_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    8 ,   0 },
     { TYP_C ,    8 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFEREIG_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFEREIG
 {
  public:

  AUFEREIG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFEREIG_BES, AUFEREIG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFEREIG_BES, AUFEREIG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFEREIG_BES, AUFEREIG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFEREIG()
  {
   ::buf_default((void *)&s, AUFEREIG_BES, AUFEREIG_ANZ);
  }
 };
#endif

#define AUFEREIG_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         KDAUFTRAGNR INTEGER           ,\
         DATUM INTEGER           ,\
         ZEIT INTEGER           ,\
         EREIGNISART SMALLINT          ,\
         GERAETNAME CHAR(8)           ,\
         USERNAME CHAR(8)           ,\
         PERSONALNR INTEGER           ,\
         EVENTCODE SMALLINT          ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 2308 LOCK MODE ROW;

#define AUFEREIG_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_KDAUFTRAGEREIG_1 on yyy( KDAUFTRAGNR, DATUM, ZEIT, EREIGNISART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAGEREIG_2 on yyy( KDAUFTRAGNR, EREIGNISART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFEREIG_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KDAUFTRAGEREIG_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAGEREIG_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFIE_ANZ_IE               11
 #define L_WERTE_VERTRIEBSZENTRUMNR   6


 #define L_AUFIE_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFIE_ANZ (int) ( sizeof(AUFIE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFIE sizeof(struct AUFIE)


 #define AUFIE_H

 #define AUFIE_LISTE \
            AADUMMY.ANZ_IE, \
            WERTE.VERTRIEBSZENTRUMNR
 #define AUFIE_PLISTE \
            "AADUMMY.ANZ_IE," \
            "WERTE.VERTRIEBSZENTRUMNR "

 #define AUFIE_PELISTE \
            "ANZ_IE," \
            "WERTE.VERTRIEBSZENTRUMNR "

 #define AUFIE_UPDLISTE \
            "ANZ_IE=?," \
            "WERTE.VERTRIEBSZENTRUMNR=? "

 #define AUFIEANZ_IE                        0
 #define AUFIEVERTRIEBSZENTRUMNR            1

 #define AUFIE_ZEIGER(xxx) \
            :xxx->ANZ_IE, \
            :xxx->VERTRIEBSZENTRUMNR

 #define AUFIE_UPDATE(xxx) \
            ANZ_IE = :xxx->ANZ_IE, \
            VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR

 #define LS_AUFIE_ANZ_IE               11
 #define LS_AUFIE_VERTRIEBSZENTRUMNR   7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFIE {
         long    ANZ_IE;
         short   VERTRIEBSZENTRUMNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFIE {
         long    ANZ_IE;
         short   VERTRIEBSZENTRUMNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFIE {
         short  ANZ_IE;
         short   VERTRIEBSZENTRUMNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFIE {
         char    ANZ_IE[11];
         char    VERTRIEBSZENTRUMNR[7];
       };

 struct O_AUFIE {
         char    ANZ_IE[11];
         char    VERTRIEBSZENTRUMNR[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFIE_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFIE_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_S ,   5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFIE
 {
  public:

  AUFIE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFIE_BES, AUFIE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFIE_BES, AUFIE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFIE_BES, AUFIE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFIE()
  {
   ::buf_default((void *)&s, AUFIE_BES, AUFIE_ANZ);
  }
 };
#endif

#define AUFIE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ANZ_IE INTEGER                     ,\
         VERTRIEBSZENTRUMNR SMALLINT                     ) EXTENT SIZE 80 LOCK MODE ROW;

#define AUFIE_CREATE_INDEX(yyy,xxx) \

#define AUFIE_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFLAGER_AUFTRAGNRKO          11
 #define L_AUFLAGER_KDAUFTRAGNR          11


 #define L_AUFLAGER_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFLAGER_ANZ (int) ( sizeof(AUFLAGER_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFLAGER sizeof(struct AUFLAGER)


 #define AUFLAGER_H

 #define AUFLAGER_LISTE \
            KOEINHEIT.AUFTRAGNRKO, \
            KOEINHEIT.KDAUFTRAGNR
 #define AUFLAGER_PLISTE \
            "KOEINHEIT.AUFTRAGNRKO," \
            "KOEINHEIT.KDAUFTRAGNR "

 #define AUFLAGER_PELISTE \
            "AUFTRAGNRKO," \
            "KDAUFTRAGNR "

 #define AUFLAGER_UPDLISTE \
            "AUFTRAGNRKO=?," \
            "KDAUFTRAGNR=? "

 #define AUFLAGERAUFTRAGNRKO                   0
 #define AUFLAGERKDAUFTRAGNR                   1

 #define AUFLAGER_ZEIGER(xxx) \
            :xxx->AUFTRAGNRKO,\
            :xxx->KDAUFTRAGNR

 #define AUFLAGER_UPDATE(xxx) \
            AUFTRAGNRKO = :xxx->AUFTRAGNRKO,\
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR

 #define LS_AUFLAGER_AUFTRAGNRKO          11
 #define LS_AUFLAGER_KDAUFTRAGNR          11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFLAGER {
         long    AUFTRAGNRKO;
         long    KDAUFTRAGNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFLAGER {
         long    AUFTRAGNRKO;
         long    KDAUFTRAGNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFLAGER {
         short  AUFTRAGNRKO;
         short  KDAUFTRAGNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFLAGER {
         char    AUFTRAGNRKO[11];
         char    KDAUFTRAGNR[11];
       };

 struct O_AUFLAGER {
         char    AUFTRAGNRKO[11];
         char    KDAUFTRAGNR[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFLAGER_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFLAGER_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFLAGER
 {
  public:

  AUFLAGER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFLAGER_BES, AUFLAGER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFLAGER_BES, AUFLAGER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFLAGER_BES, AUFLAGER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFLAGER()
  {
   ::buf_default((void *)&s, AUFLAGER_BES, AUFLAGER_ANZ);
  }
 };
#endif

#define AUFLAGER_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         AUFTRAGNRKO INTEGER           ,\
         KDAUFTRAGNR INTEGER             ) EXTENT SIZE 447 LOCK MODE ROW;

#define AUFLAGER_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KOEINHEITX         on yyy( AUFTRAGNRKO, KOBEHAELTNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KOMMIEINHEITKDX    on yyy( KDAUFTRAGNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFLAGER_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KOEINHEITX        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KOMMIEINHEITKDX   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFPOSANZ_ARTIKEL_NR           11
 #define L_AUFPOSANZ_PACKGROESSE          11
 #define L_AUFPOSANZ_DARREICHFORM         3
 #define L_AUFPOSANZ_EINHEIT              9
 #define L_AUFPOSANZ_ARTIKEL_NAME         30
 #define L_AUFPOSANZ_KDAUFTRAGNR          11
 #define L_AUFPOSANZ_POSNR                11
 #define L_AUFPOSANZ_POSTYP               6
 #define L_AUFPOSANZ_MENGEBESTELLT        11
 #define L_AUFPOSANZ_MENGEBESTAETIGT      11
 #define L_AUFPOSANZ_MENGEGELIEFERT       11
 #define L_AUFPOSANZ_MENGENATRA           11
 #define L_AUFPOSANZ_BEMERKUNGEN          240


 #define L_AUFPOSANZ_PKEY 33

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFPOSANZ_ANZ (int) ( sizeof(AUFPOSANZ_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFPOSANZ sizeof(struct AUFPOSANZ)


 #define AUFPOSANZ_H

 #define AUFPOSANZ_LISTE \
            ARTIKEL.ARTIKEL_NR, \
            ARTIKEL.PACKGROESSE, \
            ARTIKEL.DARREICHFORM, \
            ARTIKEL.EINHEIT, \
            ARTIKEL.ARTIKEL_NAME, \
            KDAUFTRAGPOS.KDAUFTRAGNR, \
            KDAUFTRAGPOS.POSNR, \
            KDAUFTRAGPOS.POSTYP, \
            KDAUFTRAGPOS.MENGEBESTELLT, \
            KDAUFTRAGPOS.MENGEBESTAETIGT, \
            KDAUFTRAGPOS.MENGEGELIEFERT, \
            KDAUFTRAGPOS.MENGENATRA, \
            KDAUFTRAGPOS.BEMERKUNGEN
 #define AUFPOSANZ_PLISTE \
            "ARTIKEL.ARTIKEL_NR," \
            "ARTIKEL.PACKGROESSE," \
            "ARTIKEL.DARREICHFORM," \
            "ARTIKEL.EINHEIT," \
            "ARTIKEL.ARTIKEL_NAME," \
            "KDAUFTRAGPOS.KDAUFTRAGNR," \
            "KDAUFTRAGPOS.POSNR," \
            "KDAUFTRAGPOS.POSTYP," \
            "KDAUFTRAGPOS.MENGEBESTELLT," \
            "KDAUFTRAGPOS.MENGEBESTAETIGT," \
            "KDAUFTRAGPOS.MENGEGELIEFERT," \
            "KDAUFTRAGPOS.MENGENATRA," \
            "KDAUFTRAGPOS.BEMERKUNGEN "

 #define AUFPOSANZ_PELISTE \
            "ARTIKEL_NR," \
            "PACKGROESSE," \
            "DARREICHFORM," \
            "EINHEIT," \
            "ARTIKEL_NAME," \
            "KDAUFTRAGNR," \
            "POSNR," \
            "POSTYP," \
            "MENGEBESTELLT," \
            "MENGEBESTAETIGT," \
            "MENGEGELIEFERT," \
            "MENGENATRA," \
            "BEMERKUNGEN "

 #define AUFPOSANZ_UPDLISTE \
            "ARTIKEL_NR=?," \
            "PACKGROESSE=?," \
            "DARREICHFORM=?," \
            "EINHEIT=?," \
            "ARTIKEL_NAME=?," \
            "KDAUFTRAGNR=?," \
            "POSNR=?," \
            "POSTYP=?," \
            "MENGEBESTELLT=?," \
            "MENGEBESTAETIGT=?," \
            "MENGEGELIEFERT=?," \
            "MENGENATRA=?," \
            "BEMERKUNGEN=? "

 #define AUFPOSANZARTIKEL_NR                    0
 #define AUFPOSANZPACKGROESSE                   1
 #define AUFPOSANZDARREICHFORM                  2
 #define AUFPOSANZEINHEIT                       3
 #define AUFPOSANZARTIKEL_NAME                  4
 #define AUFPOSANZKDAUFTRAGNR                   5
 #define AUFPOSANZPOSNR                         6
 #define AUFPOSANZPOSTYP                        7
 #define AUFPOSANZMENGEBESTELLT                 8
 #define AUFPOSANZMENGEBESTAETIGT               9
 #define AUFPOSANZMENGEGELIEFERT                10
 #define AUFPOSANZMENGENATRA                    11
 #define AUFPOSANZBEMERKUNGEN                   12

 #define AUFPOSANZ_ZEIGER(xxx) \
            :xxx->ARTIKEL_NR,\
            :xxx->PACKGROESSE,\
            :xxx->DARREICHFORM,\
            :xxx->EINHEIT,\
            :xxx->ARTIKEL_NAME,\
            :xxx->KDAUFTRAGNR,\
            :xxx->POSNR,\
            :xxx->POSTYP,\
            :xxx->MENGEBESTELLT,\
            :xxx->MENGEBESTAETIGT,\
            :xxx->MENGEGELIEFERT,\
            :xxx->MENGENATRA,\
            :xxx->BEMERKUNGEN

 #define AUFPOSANZ_UPDATE(xxx) \
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            PACKGROESSE = :xxx->PACKGROESSE,\
            DARREICHFORM = :xxx->DARREICHFORM,\
            EINHEIT = :xxx->EINHEIT,\
            ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            POSNR = :xxx->POSNR,\
            POSTYP = :xxx->POSTYP,\
            MENGEBESTELLT = :xxx->MENGEBESTELLT,\
            MENGEBESTAETIGT = :xxx->MENGEBESTAETIGT,\
            MENGEGELIEFERT = :xxx->MENGEGELIEFERT,\
            MENGENATRA = :xxx->MENGENATRA,\
            BEMERKUNGEN = :xxx->BEMERKUNGEN

 #define LS_AUFPOSANZ_ARTIKEL_NR           11
 #define LS_AUFPOSANZ_PACKGROESSE          11
 #define LS_AUFPOSANZ_DARREICHFORM         4
 #define LS_AUFPOSANZ_EINHEIT              10
 #define LS_AUFPOSANZ_ARTIKEL_NAME         31
 #define LS_AUFPOSANZ_KDAUFTRAGNR          11
 #define LS_AUFPOSANZ_POSNR                11
 #define LS_AUFPOSANZ_POSTYP               7
 #define LS_AUFPOSANZ_MENGEBESTELLT        11
 #define LS_AUFPOSANZ_MENGEBESTAETIGT      11
 #define LS_AUFPOSANZ_MENGEGELIEFERT       11
 #define LS_AUFPOSANZ_MENGENATRA           11
 #define LS_AUFPOSANZ_BEMERKUNGEN          241
 #define LS_AUFPOSANZ_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFPOSANZ {
         long    ARTIKEL_NR;
         long    PACKGROESSE;
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    KDAUFTRAGNR;
         long    POSNR;
         short   POSTYP;
         long    MENGEBESTELLT;
         long    MENGEBESTAETIGT;
         long    MENGEGELIEFERT;
         long    MENGENATRA;
         char    BEMERKUNGEN[240 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFPOSANZ {
         long    ARTIKEL_NR;
         long    PACKGROESSE;
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    KDAUFTRAGNR;
         long    POSNR;
         short   POSTYP;
         long    MENGEBESTELLT;
         long    MENGEBESTAETIGT;
         long    MENGEGELIEFERT;
         long    MENGENATRA;
         char    BEMERKUNGEN[240 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFPOSANZ {
         short  ARTIKEL_NR;
         short  PACKGROESSE;
         short  DARREICHFORM;
         short  EINHEIT;
         short  ARTIKEL_NAME;
         short  KDAUFTRAGNR;
         short  POSNR;
         short  POSTYP;
         short  MENGEBESTELLT;
         short  MENGEBESTAETIGT;
         short  MENGEGELIEFERT;
         short  MENGENATRA;
         short  BEMERKUNGEN;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFPOSANZ {
         char    ARTIKEL_NR[11];
         char    PACKGROESSE[11];
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    POSTYP[7];
         char    MENGEBESTELLT[11];
         char    MENGEBESTAETIGT[11];
         char    MENGEGELIEFERT[11];
         char    MENGENATRA[11];
         char    BEMERKUNGEN[240 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFPOSANZ {
         char    ARTIKEL_NR[11];
         char    PACKGROESSE[11];
         char    DARREICHFORM[3];
         char    EINHEIT[9];
         char    ARTIKEL_NAME[30];
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    POSTYP[7];
         char    MENGEBESTELLT[11];
         char    MENGEBESTAETIGT[11];
         char    MENGEGELIEFERT[11];
         char    MENGENATRA[11];
         char    BEMERKUNGEN[240];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFPOSANZ_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    3 ,   0 },
     { TYP_C ,    9 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,  240 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFPOSANZ_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_C,    9 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,  240 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFPOSANZ
 {
  public:

  AUFPOSANZ s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFPOSANZ_BES, AUFPOSANZ_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFPOSANZ_BES, AUFPOSANZ_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFPOSANZ_BES, AUFPOSANZ_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFPOSANZ()
  {
   ::buf_default((void *)&s, AUFPOSANZ_BES, AUFPOSANZ_ANZ);
  }
 };
#endif

#define AUFPOSANZ_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ARTIKEL_NR INTEGER           ,\
         PACKGROESSE INTEGER           ,\
         DARREICHFORM CHAR(3)           ,\
         EINHEIT CHAR(9)           ,\
         ARTIKEL_NAME CHAR(30)          ,\
         KDAUFTRAGNR INTEGER           ,\
         POSNR INTEGER           ,\
         POSTYP SMALLINT          ,\
         MENGEBESTELLT INTEGER           ,\
         MENGEBESTAETIGT INTEGER           ,\
         MENGEGELIEFERT INTEGER           ,\
         MENGENATRA INTEGER           ,\
         BEMERKUNGEN VARCHAR(240,0)    ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 38823 LOCK MODE ROW;

#define AUFPOSANZ_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGPOSX      on yyy( KDAUFTRAGNR, POSNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFPOSANZ_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDAUFTRAGPOSX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_AUFPOSBUCH_KDAUFTRAGNR          11
 #define L_AUFPOSBUCH_POSNR                11
 #define L_AUFPOSBUCH_ARTIKEL_NR           11
 #define L_AUFPOSBUCH_POSTYP               6
 #define L_AUFPOSBUCH_FEHLERMENGE          6
 #define L_AUFPOSBUCH_MENGEBESTELLT        11
 #define L_AUFPOSBUCH_MENGEBESTAETIGT      11
 #define L_AUFPOSBUCH_MENGEGELIEFERT       11
 #define L_AUFPOSBUCH_MENGENATRA           11
 #define L_AUFPOSBUCH_BEMERKUNG            240
 #define L_AUFPOSBUCH_WERTAUFTRAG          9
 #define N_AUFPOSBUCH_WERTAUFTRAG          2
 #define L_AUFPOSBUCH_WERTLIEFERUNG        9
 #define N_AUFPOSBUCH_WERTLIEFERUNG        2
 #define L_AUFPOSBUCH_WERTZEILEN           9
 #define N_AUFPOSBUCH_WERTZEILEN           2
 #define L_AUFPOSBUCH_ANZPOS               11
 #define L_AUFPOSBUCH_DARREICHFORM         3
 #define L_AUFPOSBUCH_EINHEIT              9
 #define L_AUFPOSBUCH_ARTIKEL_NAME         30
 #define L_AUFPOSBUCH_MENGEABGEBUCHT       11
 #define L_AUFPOSBUCH_BESTAND              11
 #define L_AUFPOSBUCH_STATUS               11
 #define L_AUFPOSBUCH_POSART               2
 #define L_AUFPOSBUCH_PREISEKGROSSO        9
 #define N_AUFPOSBUCH_PREISEKGROSSO        2
 #define L_AUFPOSBUCH_RABATTFESTDM         9
 #define N_AUFPOSBUCH_RABATTFESTDM         2
 #define L_AUFPOSBUCH_RABATTFEST           5
 #define N_AUFPOSBUCH_RABATTFEST           2
 #define L_AUFPOSBUCH_PREISEKAPO           9
 #define N_AUFPOSBUCH_PREISEKAPO           2
 #define L_AUFPOSBUCH_TAXPFLICHTIG         1
 #define L_AUFPOSBUCH_RABATTFAEHIG         1
 #define L_AUFPOSBUCH_MWSTSCHLUESSEL       1
 #define L_AUFPOSBUCH_DAFUEART             1
 #define L_AUFPOSBUCH_KZDEFEKT             1
 #define L_AUFPOSBUCH_KZFREITEXT           1
 #define L_AUFPOSBUCH_KZLIMITCHK           1
 #define L_AUFPOSBUCH_LAGERBEREICHNR       6
 #define L_AUFPOSBUCH_ETARTSCHALTER2       5
 #define L_AUFPOSBUCH_KURZBEZKONDI         6
 #define L_AUFPOSBUCH_MENGE                11
 #define L_AUFPOSBUCH_FILIALNR1            6
 #define L_AUFPOSBUCH_KZNACHBEARB          1
 #define L_AUFPOSBUCH_KZAPODINL            1
 #define L_AUFPOSBUCH_KZAUFGENOMMEN        1
 #define L_AUFPOSBUCH_KZINFOTEXT           1
 #define L_AUFPOSBUCH_WARENGRUPPEEIGEN     5
 #define L_AUFPOSBUCH_URSPRUNGAUFTRAGNR    11
 #define L_AUFPOSBUCH_URSPRUNGPOSNR        11
 #define L_AUFPOSBUCH_GEBUEHRBEARB         7
 #define N_AUFPOSBUCH_GEBUEHRBEARB         2
 #define L_AUFPOSBUCH_SENDESTATUS          6
 #define L_AUFPOSBUCH_PREISEKAPOFREE       9
 #define N_AUFPOSBUCH_PREISEKAPOFREE       2
 #define L_AUFPOSBUCH_PREIS_TYP            6
 #define L_AUFPOSBUCH_ARTICLE_NO_PACK      11
 #define L_AUFPOSBUCH_DISCOUNTVALUEPCT     5
 #define N_AUFPOSBUCH_DISCOUNTVALUEPCT     2
 #define L_AUFPOSBUCH_DISCOUNTVALPCTMAN    5
 #define N_AUFPOSBUCH_DISCOUNTVALPCTMAN    2
 #define L_AUFPOSBUCH_BALANCE              11
 #define N_AUFPOSBUCH_BALANCE              2
 #define L_AUFPOSBUCH_BALANCE2             11
 #define N_AUFPOSBUCH_BALANCE2             2
 #define L_AUFPOSBUCH_WERTNETTO            9
 #define N_AUFPOSBUCH_WERTNETTO            2
 #define L_AUFPOSBUCH_WERTRABATT           9
 #define N_AUFPOSBUCH_WERTRABATT           2
 #define L_AUFPOSBUCH_PREISFAKTUR          9
 #define N_AUFPOSBUCH_PREISFAKTUR          2
 #define L_AUFPOSBUCH_WERTNETTO_FV         9
 #define N_AUFPOSBUCH_WERTNETTO_FV         2
 #define L_AUFPOSBUCH_WERTTAX_FV           9
 #define N_AUFPOSBUCH_WERTTAX_FV           2
 #define L_AUFPOSBUCH_WERTNETTO_KK         9
 #define N_AUFPOSBUCH_WERTNETTO_KK         2
 #define L_AUFPOSBUCH_WERTTAX_KK           9
 #define N_AUFPOSBUCH_WERTTAX_KK           2
 #define L_AUFPOSBUCH_WERTNETTO_EH         9
 #define N_AUFPOSBUCH_WERTNETTO_EH         2
 #define L_AUFPOSBUCH_WERTTAX_EH           9
 #define N_AUFPOSBUCH_WERTTAX_EH           2
 #define L_AUFPOSBUCH_ETPOSSCHALTER2       11
 #define L_AUFPOSBUCH_WERTKL               9
 #define N_AUFPOSBUCH_WERTKL               2
 #define L_AUFPOSBUCH_TAXLEVEL             6
 #define L_AUFPOSBUCH_ARTIKEL_LANGNAME     50
 #define L_AUFPOSBUCH_CHARGENNR            25
 #define L_AUFPOSBUCH_PREISVKAPO           9
 #define N_AUFPOSBUCH_PREISVKAPO           2
 #define L_AUFPOSBUCH_PROMOTYP             6
 #define L_AUFPOSBUCH_PHARMACYGROUPID      6
 #define L_AUFPOSBUCH_PROMOTION_NO         3
 #define L_AUFPOSBUCH_DISCOUNTGRPNO        11
 #define L_AUFPOSBUCH_BASEQTY              11
 #define L_AUFPOSBUCH_BASE_VALUE           9
 #define N_AUFPOSBUCH_BASE_VALUE           2
 #define L_AUFPOSBUCH_CUSTOMERNO           11
 #define L_AUFPOSBUCH_ADDONSTDDISCOK       1
 #define L_AUFPOSBUCH_NETPRICE             11
 #define N_AUFPOSBUCH_NETPRICE             4
 #define L_AUFPOSBUCH_CODE_TYPE            6
 #define L_AUFPOSBUCH_ARTICLE_CODE         50
 #define L_AUFPOSBUCH_PROBLEMSTATE         6
 #define L_AUFPOSBUCH_WERTKL2              9
 #define N_AUFPOSBUCH_WERTKL2              2
 #define L_AUFPOSBUCH_KZPRISO              1
 #define L_AUFPOSBUCH_WERTEXCLUSIVE        9
 #define N_AUFPOSBUCH_WERTEXCLUSIVE        2
 #define L_AUFPOSBUCH_PRODUSERQUOTA        6
 #define L_AUFPOSBUCH_LINKPOSNR            11
 #define L_AUFPOSBUCH_IBTTYPE              6
 #define L_AUFPOSBUCH_HIGHERCOND           6
 #define L_AUFPOSBUCH_IBTTYPEID            6
 #define L_AUFPOSBUCH_DELIVERYDATE         11
 #define L_AUFPOSBUCH_DELIVERYTIME         11
 #define L_AUFPOSBUCH_TOURID               6
 #define L_AUFPOSBUCH_ETARTSCHALTER1       5
 #define L_AUFPOSBUCH_ETARTKLASSE1         5
 #define L_AUFPOSBUCH_MENGEBESTELLTNATRA   11
 #define L_AUFPOSBUCH_FIXBATCH             6
 #define L_AUFPOSBUCH_DISCOUNTMODE         6

 #define L_AUFPOSBUCH_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFPOSBUCH_ANZ (int) ( sizeof(AUFPOSBUCH_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFPOSBUCH sizeof(struct AUFPOSBUCH)


 #define AUFPOSBUCH_H

 #define AUFPOSBUCH_LISTE \
            KDAUFTRAGPOS.KDAUFTRAGNR, \
            KDAUFTRAGPOS.POSNR, \
            KDAUFTRAGPOS.ARTIKEL_NR, \
            KDAUFTRAGPOS.POSTYP, \
            KDAUFTRAGPOS.FEHLERMENGE, \
            KDAUFTRAGPOS.MENGEBESTELLT, \
            KDAUFTRAGPOS.MENGEBESTAETIGT, \
            KDAUFTRAGPOS.MENGEGELIEFERT, \
            KDAUFTRAGPOS.MENGENATRA, \
            KDAUFTRAGPOS.BEMERKUNG, \
            KDAUFTRAG.WERTAUFTRAG, \
            KDAUFTRAG.WERTLIEFERUNG, \
            KDAUFTRAG.WERTZEILEN, \
            KDAUFTRAG.ANZPOS, \
            ARTIKEL.DARREICHFORM, \
            ARTIKEL.EINHEIT, \
            ARTIKEL.ARTIKEL_NAME, \
            KDAUFTRAGPOS.MENGEABGEBUCHT, \
            ARTIKEL.BESTAND, \
            AADUMMY.STATUS, \
            AADUMMY.POSART, \
            DISPOARTIKEL.PREISEKGROSSO, \
            DISPOARTIKEL.RABATTFESTDM, \
            DISPOARTIKEL.RABATTFEST, \
            DISPOARTIKEL.PREISEKAPO, \
            AADUMMY.TAXPFLICHTIG, \
            AADUMMY.RABATTFAEHIG, \
            AADUMMY.MWSTSCHLUESSEL, \
            AADUMMY.DAFUEART, \
            AADUMMY.KZDEFEKT, \
            AADUMMY.KZFREITEXT, \
            AADUMMY.KZLIMITCHK, \
            KDAUFTRAGPOS.LAGERBEREICHNR, \
            KDAUFTRAGPOS.ETARTSCHALTER2, \
            AADUMMY.KURZBEZKONDI, \
            NACHLIEFERPOS.MENGE, \
            NACHLIEFERPOS.FILIALNR1, \
            AADUMMY.KZNACHBEARB, \
            AADUMMY.KZAPODINL, \
            AADUMMY.KZAUFGENOMMEN, \
            AADUMMY.KZINFOTEXT, \
            DISPOARTIKEL.WARENGRUPPEEIGEN, \
            DISPOARTIKEL.URSPRUNGAUFTRAGNR, \
            DISPOARTIKEL.URSPRUNGPOSNR, \
            DISPOARTIKEL.GEBUEHRBEARB, \
            KDAUFTRAGPOS.SENDESTATUS, \
            KDAUFTRAGPOS.PREISEKAPOFREE, \
            KDAUFTRAGPOS.PREIS_TYP, \
            KDAUFTRAGPOS.ARTICLE_NO_PACK, \
            KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT, \
            KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN, \
            CSTDISCACC.BALANCE, \
            CSTDISCACC.BALANCE2, \
            KDAUFTRAG.WERTNETTO, \
            KDAUFTRAG.WERTRABATT, \
            KDAUFTRAGPOS.PREISFAKTUR, \
            AADUMMY.WERTNETTO_FV, \
            AADUMMY.WERTTAX_FV, \
            AADUMMY.WERTNETTO_KK, \
            AADUMMY.WERTTAX_KK, \
            AADUMMY.WERTNETTO_EH, \
            AADUMMY.WERTTAX_EH, \
            KDAUFTRAGPOS.ETPOSSCHALTER2, \
            AADUMMY.WERTKL, \
            ARTIKEL.TAXLEVEL, \
            ARTIKEL.ARTIKEL_LANGNAME, \
            KDAUFTRAGPOSCHARGE.CHARGENNR, \
            KDAUFTRAGPOS.PREISVKAPO, \
            KDAUFTRAGPOS.PROMOTYP, \
            KDAUFTRAGPOSPROMO.PHARMACYGROUPID, \
            KDAUFTRAGPOS.PROMOTION_NO, \
            KDAUFTRAGPOSPROMO.DISCOUNTGRPNO, \
            KDAUFTRAGPOSPROMO.BASEQTY, \
            KDAUFTRAGPOSPROMO.BASE_VALUE, \
            KDAUFTRAGPOSPROMO.CUSTOMERNO, \
            PROMOTIONS.ADDONSTDDISCOK, \
            DISPOARTIKEL.NETPRICE, \
            KDAUFTRAGPOS.CODE_TYPE, \
            KDAUFTRAGPOS.ARTICLE_CODE, \
            KDAUFTRAGPOS.PROBLEMSTATE, \
            AADUMMY.WERTKL1, \
            KDAUFTRAGPOS.KZPRISO, \
            AADUMMY.WERTEXCLUSIVE, \
            ARTIKELZENTRAL.PRODUSERQUOTA, \
            KDAUFTRAGPOS.LINKPOSNR, \
            KDAUFTRAGPOS.IBTTYPE, \
            KDAUFTRAGPOS.HIGHERCOND, \
            KDAUFTRAGPOS.IBTTYPEID, \
            KDAUFTRAGPOSTOUR.DELIVERYDATE, \
            KDAUFTRAGPOSTOUR.DELIVERYTIME, \
            KDAUFTRAGPOSTOUR.TOURID, \
            KDAUFTRAGPOS.ETARTSCHALTER1, \
            KDAUFTRAGPOS.ETARTKLASSE1, \
            KDAUFTRAGPOS.MENGEBESTELLTNATRA, \
            KDAUFTRAGPOSCHARGE.FIXBATCH, \
            ORDERPOSITIONDISCOUNT.DISCOUNTMODE

#define AUFPOSBUCH_PLISTE \
            "KDAUFTRAGPOS.KDAUFTRAGNR," \
            "KDAUFTRAGPOS.POSNR," \
            "KDAUFTRAGPOS.ARTIKEL_NR," \
            "KDAUFTRAGPOS.POSTYP," \
            "KDAUFTRAGPOS.FEHLERMENGE," \
            "KDAUFTRAGPOS.MENGEBESTELLT," \
            "KDAUFTRAGPOS.MENGEBESTAETIGT," \
            "KDAUFTRAGPOS.MENGEGELIEFERT," \
            "KDAUFTRAGPOS.MENGENATRA," \
            "KDAUFTRAGPOS.BEMERKUNG," \
            "KDAUFTRAG.WERTAUFTRAG," \
            "KDAUFTRAG.WERTLIEFERUNG," \
            "KDAUFTRAG.WERTZEILEN," \
            "KDAUFTRAG.ANZPOS," \
            "ARTIKEL.DARREICHFORM," \
            "ARTIKEL.EINHEIT," \
            "ARTIKEL.ARTIKEL_NAME," \
            "KDAUFTRAGPOS.MENGEABGEBUCHT," \
            "ARTIKEL.BESTAND," \
            "AADUMMY.STATUS," \
            "AADUMMY.POSART," \
            "DISPOARTIKEL.PREISEKGROSSO," \
            "DISPOARTIKEL.RABATTFESTDM," \
            "DISPOARTIKEL.RABATTFEST," \
            "DISPOARTIKEL.PREISEKAPO," \
            "AADUMMY.TAXPFLICHTIG," \
            "AADUMMY.RABATTFAEHIG," \
            "AADUMMY.MWSTSCHLUESSEL," \
            "AADUMMY.DAFUEART," \
            "AADUMMY.KZDEFEKT," \
            "AADUMMY.KZFREITEXT," \
            "AADUMMY.KZLIMITCHK," \
            "KDAUFTRAGPOS.LAGERBEREICHNR," \
            "KDAUFTRAGPOS.ETARTSCHALTER2," \
            "AADUMMY.KURZBEZKONDI," \
            "NACHLIEFERPOS.MENGE," \
            "NACHLIEFERPOS.FILIALNR1," \
            "AADUMMY.KZNACHBEARB," \
            "AADUMMY.KZAPODINL," \
            "AADUMMY.KZAUFGENOMMEN," \
            "AADUMMY.KZINFOTEXT," \
            "DISPOARTIKEL.WARENGRUPPEEIGEN," \
            "DISPOARTIKEL.URSPRUNGAUFTRAGNR," \
            "DISPOARTIKEL.URSPRUNGPOSNR," \
            "DISPOARTIKEL.GEBUEHRBEARB," \
            "KDAUFTRAGPOS.SENDESTATUS," \
            "KDAUFTRAGPOS.PREISEKAPOFREE," \
            "KDAUFTRAGPOS.PREIS_TYP," \
            "KDAUFTRAGPOS.ARTICLE_NO_PACK," \
            "KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT," \
            "KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN," \
            "CSTDISCACC.BALANCE," \
            "CSTDISCACC.BALANCE2, " \
            "KDAUFTRAG.WERTNETTO, " \
            "KDAUFTRAG.WERTRABATT, " \
            "KDAUFTRAGPOS.PREISFAKTUR, " \
            "AADUMMY.WERTNETTO_FV, " \
            "AADUMMY.WERTTAX_FV, " \
            "AADUMMY.WERTNETTO_KK, " \
            "AADUMMY.WERTTAX_KK, " \
            "AADUMMY.WERTNETTO_EH, " \
            "AADUMMY.WERTTAX_EH, " \
            "KDAUFTRAGPOS.ETPOSSCHALTER2, " \
            "AADUMMY.WERTKL, " \
            "ARTIKEL.TAXLEVEL, " \
            "ARTIKEL.ARTIKEL_LANGNAME, " \
            "KDAUFTRAGPOSCHARGE.CHARGENNR, " \
            "KDAUFTRAGPOS.PREISVKAPO, " \
            "KDAUFTRAGPOS.PROMOTYP, " \
            "KDAUFTRAGPOSPROMO.PHARMACYGROUPID, " \
            "KDAUFTRAGPOS.PROMOTION_NO, " \
            "KDAUFTRAGPOSPROMO.DISCOUNTGRPNO, " \
            "KDAUFTRAGPOSPROMO.BASEQTY, " \
            "KDAUFTRAGPOSPROMO.BASE_VALUE, " \
            "KDAUFTRAGPOSPROMO.CUSTOMERNO, " \
            "PROMOTIONS.ADDONSTDDISCOK, " \
            "DISPOARTIKEL.NETPRICE, " \
            "KDAUFTRAGPOS.CODE_TYPE, " \
            "KDAUFTRAGPOS.ARTICLE_CODE, " \
            "KDAUFTRAGPOS.PROBLEMSTATE, " \
            "AADUMMY.WERTKL1, " \
            "KDAUFTRAGPOS.KZPRISO, " \
            "AADUMMY.WERTEXCLUSIVE, " \
            "ARTIKELZENTRAL.PRODUSERQUOTA, " \
            "KDAUFTRAGPOS.LINKPOSNR, " \
            "KDAUFTRAGPOS.IBTTYPE, " \
            "KDAUFTRAGPOS.HIGHERCOND, " \
            "KDAUFTRAGPOS.IBTTYPEID, " \
            "KDAUFTRAGPOSTOUR.DELIVERYDATE, " \
            "KDAUFTRAGPOSTOUR.DELIVERYTIME, " \
            "KDAUFTRAGPOSTOUR.TOURID, " \
            "KDAUFTRAGPOS.ETARTSCHALTER1, " \
            "KDAUFTRAGPOS.ETARTKLASSE1, " \
            "KDAUFTRAGPOS.MENGEBESTELLTNATRA, " \
            "KDAUFTRAGPOSCHARGE.FIXBATCH, " \
            "ORDERPOSITIONDISCOUNT.DISCOUNTMODE "

 #define AUFPOSBUCH_PELISTE \
            "KDAUFTRAGNR," \
            "POSNR," \
            "ARTIKEL_NR," \
            "POSTYP," \
            "FEHLERMENGE," \
            "MENGEBESTELLT," \
            "MENGEBESTAETIGT," \
            "MENGEGELIEFERT," \
            "MENGENATRA," \
            "BEMERKUNG," \
            "WERTAUFTRAG," \
            "WERTLIEFERUNG," \
            "WERTZEILEN," \
            "ANZPOS," \
            "DARREICHFORM," \
            "EINHEIT," \
            "ARTIKEL_NAME," \
            "MENGEABGEBUCHT," \
            "BESTAND," \
            "STATUS," \
            "POSART," \
            "PREISEKGROSSO," \
            "RABATTFESTDM," \
            "RABATTFEST," \
            "PREISEKAPO," \
            "TAXPFLICHTIG," \
            "RABATTFAEHIG," \
            "MWSTSCHLUESSEL," \
            "DAFUEART," \
            "KZDEFEKT," \
            "KZFREITEXT," \
            "KZLIMITCHK," \
            "LAGERBEREICHNR," \
            "ETARTSCHALTER2," \
            "KURZBEZKONDI," \
            "MENGE," \
            "FILIALNR1," \
            "KZNACHBEARB," \
            "KZAPODINL," \
            "KZAUFGENOMMEN," \
            "KZINFOTEXT," \
            "WARENGRUPPEEIGEN," \
            "URSPRUNGAUFTRAGNR," \
            "URSPRUNGPOSNR," \
            "GEBUEHRBEARB," \
            "SENDESTATUS," \
            "PREISEKAPOFREE," \
            "PREIS_TYP," \
            "ARTICLE_NO_PACK," \
            "DISCOUNTVALUEPCT," \
            "DISCOUNTVALPCTMAN," \
            "BALANCE," \
            "BALANCE2," \
            "WERTNETTO," \
            "WERTRABATT," \
            "PREISFAKTUR, " \
            "WERTNETTO_FV, " \
            "WERTTAX_FV, " \
            "WERTNETTO_KK, " \
            "WERTTAX_KK, " \
            "WERTNETTO_EH, " \
            "WERTTAX_EH, " \
            "ETPOSSCHALTER2, " \
            "WERTKL, " \
            "TAXLEVEL, " \
            "ARTIKEL_LANGNAME, " \
            "CHARGENNR, " \
            "PREISVKAPO, " \
            "PROMOTYP, " \
            "PHARMACYGROUPID, " \
            "PROMOTION_NO, " \
            "DISCOUNTGRPNO, " \
            "BASEQTY, " \
            "BASE_VALUE, " \
            "CUSTOMERNO, " \
            "ADDONSTDDISCOK, " \
            "NETPRICE, " \
            "CODE_TYPE, " \
            "ARTICLE_CODE, " \
            "PROBLEMSTATE, " \
            "WERTKL1, " \
            "KZPRISO, " \
            "WERTEXCLUSIVE, " \
            "PRODUSERQUOTA, " \
            "LINKPOSNR, " \
            "IBTTYPE, " \
            "HIGHERCOND, " \
            "IBTTYPEID, " \
            "DELIVERYDATE, " \
            "DELIVERYTIME, " \
            "TOURID, " \
            "ETARTSCHALTER1, " \
            "ETARTKLASSE1, " \
            "MENGEBESTELLTNATRA, " \
            "FIXBATCH, " \
            "DISCOUNTMODE "

 #define AUFPOSBUCH_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "POSNR=?," \
            "ARTIKEL_NR=?," \
            "POSTYP=?," \
            "FEHLERMENGE=?," \
            "MENGEBESTELLT=?," \
            "MENGEBESTAETIGT=?," \
            "MENGEGELIEFERT=?," \
            "MENGENATRA=?," \
            "BEMERKUNG=?," \
            "WERTAUFTRAG=?," \
            "WERTLIEFERUNG=?," \
            "WERTZEILEN=?," \
            "ANZPOS=?," \
            "DARREICHFORM=?," \
            "EINHEIT=?," \
            "ARTIKEL_NAME=?," \
            "MENGEABGEBUCHT=?," \
            "BESTAND=?," \
            "STATUS=?," \
            "POSART=?," \
            "PREISEKGROSSO=?," \
            "RABATTFESTDM=?," \
            "RABATTFEST=?," \
            "PREISEKAPO=?," \
            "TAXPFLICHTIG=?," \
            "RABATTFAEHIG=?," \
            "MWSTSCHLUESSEL=?," \
            "DAFUEART=?," \
            "KZDEFEKT=?," \
            "KZFREITEXT=?," \
            "KZLIMITCHK=?," \
            "LAGERBEREICHNR=?," \
            "ETARTSCHALTER2=?," \
            "KURZBEZKONDI=?," \
            "MENGE=?," \
            "FILIALNR1=?," \
            "KZNACHBEARB=?," \
            "KZAPODINL=?," \
            "KZAUFGENOMMEN=?," \
            "KZINFOTEXT=?," \
            "WARENGRUPPEEIGEN=?," \
            "URSPRUNGAUFTRAGNR=?," \
            "URSPRUNGPOSNR=?," \
            "GEBUEHRBEARB=?," \
            "SENDESTATUS=?," \
            "PREISEKAPOFREE=?," \
            "PREIS_TYP=?," \
            "ARTICLE_NO_PACK=?," \
            "DISCOUNTVALUEPCT=?," \
            "DISCOUNTVALPCTMAN=?," \
            "BALANCE=?," \
            "BALANCE2=?," \
            "WERTNETTO=?," \
            "WERTRABATT=?," \
            "PREISFAKTUR=?, " \
            "WERTNETTO_FV=?, " \
            "WERTTAX_FV=?, " \
            "WERTNETTO_KK=?, " \
            "WERTTAX_KK=?, " \
            "WERTNETTO_EH=?, " \
            "WERTTAX_EH=?, " \
            "ETPOSSCHALTER2=?, " \
            "WERTKL=?, " \
            "TAXLEVEL=?, " \
            "ARTIKEL_LANGNAME=?, " \
            "CHARGENNR=?, " \
            "PREISVKAPO=?, " \
            "PROMOTYP=?, " \
            "PHARMACYGROUPID=?, " \
            "PROMOTION_NO=?, " \
            "DISCOUNTGRPNO=?, " \
            "BASEQTY=?, " \
            "BASE_VALUE=?, " \
            "CUSTOMERNO=?, " \
            "ADDONSTDDISCOK=?, " \
            "NETPRICE=?, " \
            "CODE_TYPE=?, " \
            "ARTICLE_CODE=?, " \
            "PROBLEMSTATE=?, " \
            "WERTKL1=?, " \
            "KZPRISO=?, " \
            "WERTEXCLUSIVE=?, " \
            "PRODUSERQUOTA=?, " \
            "LINKPOSNR=?, " \
            "IBTTYPE=?, " \
            "HIGHERCOND=?, " \
            "IBTTYPEID=?, " \
            "DELIVERYDATE=?, " \
            "DELIVERYTIME=?, " \
            "TOURID=?, " \
            "ETARTSCHALTER1=?, " \
            "ETARTKLASSE1=?, " \
            "MENGEBESTELLTNATRA=?, " \
            "FIXBATCH=?, " \
            "DISCOUNTMODE=? "

 #define AUFPOSBUCHKDAUFTRAGNR                   0
 #define AUFPOSBUCHPOSNR                         1
 #define AUFPOSBUCHARTIKEL_NR                    2
 #define AUFPOSBUCHPOSTYP                        3
 #define AUFPOSBUCHFEHLERMENGE                   4
 #define AUFPOSBUCHMENGEBESTELLT                 5
 #define AUFPOSBUCHMENGEBESTAETIGT               6
 #define AUFPOSBUCHMENGEGELIEFERT                7
 #define AUFPOSBUCHMENGENATRA                    8
 #define AUFPOSBUCHBEMERKUNG                     9
 #define AUFPOSBUCHWERTAUFTRAG                   10
 #define AUFPOSBUCHWERTLIEFERUNG                 11
 #define AUFPOSBUCHWERTZEILEN                    12
 #define AUFPOSBUCHANZPOS                        13
 #define AUFPOSBUCHDARREICHFORM                  14
 #define AUFPOSBUCHEINHEIT                       15
 #define AUFPOSBUCHARTIKEL_NAME                  16
 #define AUFPOSBUCHMENGEABGEBUCHT                17
 #define AUFPOSBUCHBESTAND                       18
 #define AUFPOSBUCHSTATUS                        19
 #define AUFPOSBUCHPOSART                        20
 #define AUFPOSBUCHPREISEKGROSSO                 21
 #define AUFPOSBUCHRABATTFESTDM                  22
 #define AUFPOSBUCHRABATTFEST                    23
 #define AUFPOSBUCHPREISEKAPO                    24
 #define AUFPOSBUCHTAXPFLICHTIG                  25
 #define AUFPOSBUCHRABATTFAEHIG                  26
 #define AUFPOSBUCHMWSTSCHLUESSEL                27
 #define AUFPOSBUCHDAFUEART                      28
 #define AUFPOSBUCHKZDEFEKT                      29
 #define AUFPOSBUCHKZFREITEXT                    30
 #define AUFPOSBUCHKZLIMITCHK                    31
 #define AUFPOSBUCHLAGERBEREICHNR                32
 #define AUFPOSBUCHETARTSCHALTER2                33
 #define AUFPOSBUCHKURZBEZKONDI                  34
 #define AUFPOSBUCHMENGE                         35
 #define AUFPOSBUCHFILIALNR1                     36
 #define AUFPOSBUCHKZNACHBEARB                   37
 #define AUFPOSBUCHKZAPODINL                     38
 #define AUFPOSBUCHKZAUFGENOMMEN                 39
 #define AUFPOSBUCHKZINFOTEXT                    40
 #define AUFPOSBUCHWARENGRUPPEEIGEN              41
 #define AUFPOSBUCHURSPRUNGAUFTRAGNR             42
 #define AUFPOSBUCHURSPRUNGPOSNR                 43
 #define AUFPOSBUCHGEBUEHRBEARB                  44
 #define AUFPOSBUCHSENDESTATUS                   45
 #define AUFPOSBUCHPREISEKAPOFREE                46
 #define AUFPOSBUCHPREIS_TYP                     47
 #define AUFPOSBUCHARTICLE_NO_PACK               48
 #define AUFPOSBUCHDISCOUNTVALUEPCT              49
 #define AUFPOSBUCHDISCOUNTVALPCTMAN             50
 #define AUFPOSBUCHBALANCE                       51
 #define AUFPOSBUCHBALANCE2                      52
 #define AUFPOSBUCHWERTNETTO                     53
 #define AUFPOSBUCHWERTRABATT                    54
 #define AUFPOSBUCHPREISFAKTUR                   55
 #define AUFPOSBUCHWERTNETTO_FV                  56
 #define AUFPOSBUCHWERTTAX_FV                    57
 #define AUFPOSBUCHWERTNETTO_KK                  58
 #define AUFPOSBUCHWERTTAX_KK                    59
 #define AUFPOSBUCHWERTNETTO_EH                  60
 #define AUFPOSBUCHWERTTAX_EH                    61
 #define AUFPOSBUCHETPOSSCHALTER2                62
 #define AUFPOSBUCHWERTKL                        63
 #define AUFPOSBUCHTAXLEVEL                      64
 #define AUFPOSBUCHARTIKEL_LANGNAME              65
 #define AUFPOSBUCHCHARGENNR                     66
 #define AUFPOSBUCHPREISVKAPO                    67
 #define AUFPOSBUCHPROMOTYP                      68
 #define AUFPOSBUCHPHARMACYGROUPID               69
 #define AUFPOSBUCHPROMOTION_NO                  70
 #define AUFPOSBUCHDISCOUNTGRPNO                 71
 #define AUFPOSBUCHBASEQTY                       72
 #define AUFPOSBUCHBASE_VALUE                    73
 #define AUFPOSBUCHCUSTOMERNO                    74
 #define AUFPOSBUCHADDONSTDDISCOK                75
 #define AUFPOSBUCHNETPRICE                      76
 #define AUFPOSBUCHCODE_TYPE                     77
 #define AUFPOSBUCHARTICLE_CODE                  78
 #define AUFPOSBUCHPROBLEMSTATE                  79
 #define AUFPOSBUCHWERTKL1                       80
 #define AUFPOSBUCHKZPRISO                       81
 #define AUFPOSBUCHWERTEXCLUSIVE                 82
 #define AUFPOSBUCHPRODUSERQUOTA                 83
 #define AUFPOSBUCHLINKPOSNR                     84
 #define AUFPOSBUCHIBTTYPE                       85
 #define AUFPOSBUCHHIGHERCOND                    86
 #define AUFPOSBUCHIBTTYPEID                     87
 #define AUFPOSBUCHDELIVERYDATE                  88
 #define AUFPOSBUCHDELIVERYTIME                  89
 #define AUFPOSBUCHTOURID                        90
 #define AUFPOSBUCHETARTSCHALTER1                91
 #define AUFPOSBUCHETARTKLASSE1                  92
 #define AUFPOSBUCHMENGEBESTELLTNATRA            93
 #define AUFPOSBUCHFIXBATCH                      94
 #define AUFPOSBUCHDISCOUNTMODE                  95


 #define AUFPOSBUCH_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR,\
            :xxx->POSNR,\
            :xxx->ARTIKEL_NR,\
            :xxx->POSTYP,\
            :xxx->FEHLERMENGE,\
            :xxx->MENGEBESTELLT,\
            :xxx->MENGEBESTAETIGT,\
            :xxx->MENGEGELIEFERT,\
            :xxx->MENGENATRA,\
            :xxx->BEMERKUNG,\
            :xxx->WERTAUFTRAG,\
            :xxx->WERTLIEFERUNG,\
            :xxx->WERTZEILEN,\
            :xxx->ANZPOS,\
            :xxx->DARREICHFORM,\
            :xxx->EINHEIT,\
            :xxx->ARTIKEL_NAME,\
            :xxx->MENGEABGEBUCHT,\
            :xxx->BESTAND,\
            :xxx->STATUS,\
            :xxx->POSART,\
            :xxx->PREISEKGROSSO,\
            :xxx->RABATTFESTDM,\
            :xxx->RABATTFEST,\
            :xxx->PREISEKAPO,\
            :xxx->TAXPFLICHTIG,\
            :xxx->RABATTFAEHIG,\
            :xxx->MWSTSCHLUESSEL,\
            :xxx->DAFUEART,\
            :xxx->KZDEFEKT,\
            :xxx->KZFREITEXT,\
            :xxx->KZLIMITCHK,\
            :xxx->LAGERBEREICHNR,\
            :xxx->ETARTSCHALTER2,\
            :xxx->KURZBEZKONDI,\
            :xxx->MENGE,\
            :xxx->FILIALNR1,\
            :xxx->KZNACHBEARB,\
            :xxx->KZAPODINL,\
            :xxx->KZAUFGENOMMEN,\
            :xxx->KZINFOTEXT,\
            :xxx->WARENGRUPPEEIGEN,\
            :xxx->URSPRUNGAUFTRAGNR,\
            :xxx->URSPRUNGPOSNR,\
            :xxx->GEBUEHRBEARB,\
            :xxx->SENDESTATUS,\
            :xxx->PREISEKAPOFREE,\
            :xxx->PREIS_TYP,\
            :xxx->ARTICLE_NO_PACK,\
            :xxx->DISCOUNTVALUEPCT,\
            :xxx->DISCOUNTVALPCTMAN,\
            :xxx->BALANCE,\
            :xxx->BALANCE,\
            :xxx->WERTNETTO,\
            :xxx->WERTRABATT,\
            :xxx->PREISFAKTUR,\
            :xxx->WERTNETTO_FV,\
            :xxx->WERTTAX_FV,\
            :xxx->WERTNETTO_KK,\
            :xxx->WERTTAX_KK,\
            :xxx->WERTNETTO_EH,\
            :xxx->WERTTAX_EH,\
            :xxx->ETPOSSCHALTER2,\
            :xxx->WERTKL,\
            :xxx->TAXLEVEL,\
            :xxx->ARTIKEL_LANGNAME,\
            :xxx->CHARGENNR,\
            :xxx->PREISVKAPO,\
            :xxx->PROMOTYP,\
            :xxx->PHARMACYGROUPID,\
            :xxx->PROMOTION_NO,\
            :xxx->DISCOUNTGRPNO,\
            :xxx->BASEQTY,\
            :xxx->BASE_VALUE,\
            :xxx->CUSTOMERNO,\
            :xxx->ADDONSTDDISCOK,\
            :xxx->NETPRICE,\
            :xxx->CODE_TYPE,\
            :xxx->ARTICLE_CODE,\
            :xxx->PROBLEMSTATE,\
            :xxx->WERTKL1,\
            :xxx->KZPRISO,\
            :xxx->WERTEXCLUSIVE,\
            :xxx->PRODUSERQUOTA,\
            :xxx->LINKPOSNR,\
            :xxx->IBTTYPE,\
            :xxx->HIGHERCOND,\
            :xxx->IBTTYPEID,\
            :xxx->DELIVERYDATE,\
            :xxx->DELIVERYTIME,\
            :xxx->TOURID,\
            :xxx->ETARTSCHALTER1,\
            :xxx->ETARTKLASSE1,\
            :xxx->MENGEBESTELLTNATRA,\
            :xxx->FIXBATCH,\
            :xxx->DISCOUNTMODE


 #define AUFPOSBUCH_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            POSNR = :xxx->POSNR,\
            ARTIKEL_NR = :xxx->ARTIKEL_NR,\
            POSTYP = :xxx->POSTYP,\
            FEHLERMENGE = :xxx->FEHLERMENGE,\
            MENGEBESTELLT = :xxx->MENGEBESTELLT,\
            MENGEBESTAETIGT = :xxx->MENGEBESTAETIGT,\
            MENGEGELIEFERT = :xxx->MENGEGELIEFERT,\
            MENGENATRA = :xxx->MENGENATRA,\
            BEMERKUNG = :xxx->BEMERKUNG,\
            WERTAUFTRAG = :xxx->WERTAUFTRAG,\
            WERTLIEFERUNG = :xxx->WERTLIEFERUNG,\
            WERTZEILEN = :xxx->WERTZEILEN,\
            ANZPOS = :xxx->ANZPOS,\
            DARREICHFORM = :xxx->DARREICHFORM,\
            EINHEIT = :xxx->EINHEIT,\
            ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
            MENGEABGEBUCHT = :xxx->MENGEABGEBUCHT,\
            BESTAND = :xxx->BESTAND,\
            STATUS = :xxx->STATUS,\
            POSART = :xxx->POSART,\
            PREISEKGROSSO = :xxx->PREISEKGROSSO,\
            RABATTFESTDM = :xxx->RABATTFESTDM,\
            RABATTFEST = :xxx->RABATTFEST,\
            PREISEKAPO = :xxx->PREISEKAPO,\
            TAXPFLICHTIG = :xxx->TAXPFLICHTIG,\
            RABATTFAEHIG = :xxx->RABATTFAEHIG,\
            MWSTSCHLUESSEL = :xxx->MWSTSCHLUESSEL,\
            DAFUEART = :xxx->DAFUEART,\
            KZDEFEKT = :xxx->KZDEFEKT,\
            KZFREITEXT = :xxx->KZFREITEXT,\
            KZLIMITCHK = :xxx->KZLIMITCHK,\
            LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
            ETARTSCHALTER2 = :xxx->ETARTSCHALTER2,\
            KURZBEZKONDI = :xxx->KURZBEZKONDI,\
            MENGE = :xxx->MENGE,\
            FILIALNR1 = :xxx->FILIALNR1,\
            KZNACHBEARB = :xxx->KZNACHBEARB,\
            KZAPODINL = :xxx->KZAPODINL,\
            KZAUFGENOMMEN = :xxx->KZAUFGENOMMEN,\
            KZINFOTEXT = :xxx->KZINFOTEXT,\
            WARENGRUPPEEIGEN = :xxx->WARENGRUPPEEIGEN,\
            URSPRUNGAUFTRAGNR = :xxx->URSPRUNGAUFTRAGNR,\
            URSPRUNGPOSNR = :xxx->URSPRUNGPOSNR,\
            GEBUEHRBEARB = :xxx->GEBUEHRBEARB,\
            SENDESTATUS = :xxx->SENDESTATUS,\
            PREISEKAPOFREE = :xxx->PREISEKAPOFREE,\
            PREIS_TYP = :xxx->PREIS_TYP,\
            ARTICLE_NO_PACK = :xxx->ARTICLE_NO_PACK,\
            DISCOUNTVALUEPCT = :xxx->DISCOUNTVALUEPCT,\
            DISCOUNTVALPCTMAN = :xxx->DISCOUNTVALPCTMAN,\
            BALANCE = :xxx->BALANCE,\
            BALANCE2 = :xxx->BALANCE2,\
            WERTNETTO = :xxx->WERTNETTO,\
            WERTRABATT = :xxx->WERTRABATT,\
            PREISFAKTUR = :xxx->PREISFAKTUR,\
            WERTNETTO_FV = :xxx->WERTNETTO_FV,\
            WERTTAX_FV = :xxx->WERTTAX_FV,\
            WERTNETTO_KK = :xxx->WERTNETTO_KK,\
            WERTTAX_KK = :xxx->WERTTAX_KK,\
            WERTNETTO_EH = :xxx->WERTNETTO_EH,\
            WERTTAX_EH = :xxx->WERTTAX_EH,\
            ETPOSSCHALTER2 = :xxx->ETPOSSCHALTER2,\
            WERTKL = :xxx->WERTKL,\
            TAXLEVEL = :xxx->TAXLEVEL,\
            ARTIKEL_LANGNAME = :xxx->ARTIKEL_LANGNAME,\
            CHARGENNR = :xxx->CHARGENNR,\
            PREISVKAPO = :xxx->PREISVKAPO,\
            PROMOTYP = :xxx->PROMOTYP,\
            PHARMACYGROUPID = :xxx->PHARMACYGROUPID,\
            PROMOTION_NO = :xxx->PROMOTION_NO,\
            DISCOUNTGRPNO = :xxx->DISCOUNTGRPNO,\
            BASEQTY = :xxx->BASEQTY,\
            BASE_VALUE = :xxx->BASE_VALUE,\
            CUSTOMERNO = :xxx->CUSTOMERNO,\
            ADDONSTDDISCOK = :xxx->ADDONSTDDISCOK,\
            NETPRICE = :xxx->NETPRICE,\
            CODE_TYPE = :xxx->CODE_TYPE,\
            ARTICLE_CODE = :xxx->ARTICLE_CODE,\
            PROBLEMSTATE = :xxx->PROBLEMSTATE,\
            WERTKL1 = :xxx->WERTKL1,\
            KZPRISO = :xxx->KZPRISO,\
            WERTEXCLUSIVE = :xxx->WERTEXCLUSIVE,\
            PRODUSERQUOTA = :xxx->PRODUSERQUOTA,\
            LINKPOSNR = :xxx->LINKPOSNR,\
            IBTTYPE = :xxx->IBTTYPE,\
            HIGHERCOND = :xxx->HIGHERCOND,\
            IBTTYPEID = :xxx->IBTTYPEID,\
            DELIVERYDATE = :xxx->DELIVERYDATE,\
            DELIVERYTIME = :xxx->DELIVERYTIME,\
            TOURID = :xxx->TOURID,\
            ETARTSCHALTER1 = :xxx->ETARTSCHALTER1,\
            ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
            MENGEBESTELLTNATRA = :xxx->MENGEBESTELLTNATRA,\
            FIXBATCH = :xxx->FIXBATCH,\
            DISCOUNTMODE = :xxx->DISCOUNTMODE


 #define LS_AUFPOSBUCH_KDAUFTRAGNR          11
 #define LS_AUFPOSBUCH_POSNR                11
 #define LS_AUFPOSBUCH_ARTIKEL_NR           11
 #define LS_AUFPOSBUCH_POSTYP               7
 #define LS_AUFPOSBUCH_FEHLERMENGE          7
 #define LS_AUFPOSBUCH_MENGEBESTELLT        11
 #define LS_AUFPOSBUCH_MENGEBESTAETIGT      11
 #define LS_AUFPOSBUCH_MENGEGELIEFERT       11
 #define LS_AUFPOSBUCH_MENGENATRA           11
 #define LS_AUFPOSBUCH_BEMERKUNG            241
 #define LS_AUFPOSBUCH_WERTAUFTRAG          11
 #define LS_AUFPOSBUCH_WERTLIEFERUNG        11
 #define LS_AUFPOSBUCH_WERTZEILEN           11
 #define LS_AUFPOSBUCH_ANZPOS               11
 #define LS_AUFPOSBUCH_DARREICHFORM         4
 #define LS_AUFPOSBUCH_EINHEIT              10
 #define LS_AUFPOSBUCH_ARTIKEL_NAME         31
 #define LS_AUFPOSBUCH_MENGEABGEBUCHT       11
 #define LS_AUFPOSBUCH_BESTAND              11
 #define LS_AUFPOSBUCH_STATUS               11
 #define LS_AUFPOSBUCH_POSART               3
 #define LS_AUFPOSBUCH_PREISEKGROSSO        11
 #define LS_AUFPOSBUCH_RABATTFESTDM         11
 #define LS_AUFPOSBUCH_RABATTFEST           7
 #define LS_AUFPOSBUCH_PREISEKAPO           11
 #define LS_AUFPOSBUCH_TAXPFLICHTIG         2
 #define LS_AUFPOSBUCH_RABATTFAEHIG         2
 #define LS_AUFPOSBUCH_MWSTSCHLUESSEL       2
 #define LS_AUFPOSBUCH_DAFUEART             2
 #define LS_AUFPOSBUCH_KZDEFEKT             2
 #define LS_AUFPOSBUCH_KZFREITEXT           2
 #define LS_AUFPOSBUCH_KZLIMITCHK           2
 #define LS_AUFPOSBUCH_LAGERBEREICHNR       7
 #define LS_AUFPOSBUCH_ETARTSCHALTER2       6
 #define LS_AUFPOSBUCH_KURZBEZKONDI         7
 #define LS_AUFPOSBUCH_MENGE                11
 #define LS_AUFPOSBUCH_FILIALNR1            7
 #define LS_AUFPOSBUCH_KZNACHBEARB          2
 #define LS_AUFPOSBUCH_KZAPODINL            2
 #define LS_AUFPOSBUCH_KZAUFGENOMMEN        2
 #define LS_AUFPOSBUCH_KZINFOTEXT           2
 #define LS_AUFPOSBUCH_WARENGRUPPEEIGEN     6
 #define LS_AUFPOSBUCH_URSPRUNGAUFTRAGNR    11
 #define LS_AUFPOSBUCH_URSPRUNGPOSNR        11
 #define LS_AUFPOSBUCH_GEBUEHRBEARB         9
 #define LS_AUFPOSBUCH_SENDESTATUS          7
 #define LS_AUFPOSBUCH_PREISEKAPOFREE       11
 #define LS_AUFPOSBUCH_PREIS_TYP            7
 #define LS_AUFPOSBUCH_ARTICLE_NO_PACK      11
 #define LS_AUFPOSBUCH_DISCOUNTVALUEPCT     5
 #define LS_AUFPOSBUCH_DISCOUNTVALPCTMAN    5
 #define LS_AUFPOSBUCH_BALANCE              13
 #define LS_AUFPOSBUCH_BALANCE2             13
 #define LS_AUFPOSBUCH_WERTNETTO            11
 #define LS_AUFPOSBUCH_WERTRABATT           11
 #define LS_AUFPOSBUCH_PREISFAKTUR          11
 #define LS_AUFPOSBUCH_WERTNETTO_FV         11
 #define LS_AUFPOSBUCH_WERTTAX_FV           11
 #define LS_AUFPOSBUCH_WERTNETTO_KK         11
 #define LS_AUFPOSBUCH_WERTTAX_KK           11
 #define LS_AUFPOSBUCH_WERTNETTO_EH         11
 #define LS_AUFPOSBUCH_WERTTAX_EH           11
 #define LS_AUFPOSBUCH_FETCH_REL            11
 #define LS_AUFPOSBUCH_ETPOSSCHALTER2       6
 #define LS_AUFPOSBUCH_WERTKL               11
 #define LS_AUFPOSBUCH_TAXLEVEL             7
 #define LS_AUFPOSBUCH_ARTIKEL_LANGNAME     51
 #define LS_AUFPOSBUCH_CHARGENNR            26
 #define LS_AUFPOSBUCH_PREISVKAPO           11
 #define LS_AUFPOSBUCH_PROMOTYP             7
 #define LS_AUFPOSBUCH_PHARMACYGROUPID      4
 #define LS_AUFPOSBUCH_PROMOTION_NO         7
 #define LS_AUFPOSBUCH_DISCOUNTGRPNO        11
 #define LS_AUFPOSBUCH_BASEQTY              11
 #define LS_AUFPOSBUCH_BASE_VALUE           11
 #define LS_AUFPOSBUCH_CUSTOMERNO           11
 #define LS_AUFPOSBUCH_ADDONSTDDISCOK       2
 #define LS_AUFPOSBUCH_NETPRICE             11
 #define LS_AUFPOSBUCH_CODE_TYPE            7
 #define LS_AUFPOSBUCH_ARTICLE_CODE         26
 #define LS_AUFPOSBUCH_PROBLEMSTATE         7
 #define LS_AUFPOSBUCH_WERTKL1              11
 #define LS_AUFPOSBUCH_KZPRISO              2
 #define LS_AUFPOSBUCH_WERTEXCLUSIVE        11
 #define LS_AUFPOSBUCH_PRODUSERQUOTA        7
 #define LS_AUFPOSBUCH_LINKPOSNR            11
 #define LS_AUFPOSBUCH_IBTTYPE              7
 #define LS_AUFPOSBUCH_HIGHERCOND           7
 #define LS_AUFPOSBUCH_IBTTYPEID            7
 #define LS_AUFPOSBUCH_DELIVERYDATE         11
 #define LS_AUFPOSBUCH_DELIVERYTIME         11
 #define LS_AUFPOSBUCH_TOURID               7
 #define LS_AUFPOSBUCH_ETARTSCHALTER1       6
 #define LS_AUFPOSBUCH_ETARTKLASSE1         6
 #define LS_AUFPOSBUCH_MENGEBESTELLTNATRA   11
 #define LS_AUFPOSBUCH_FIXBATCH             7
 #define LS_AUFPOSBUCH_DISCOUNTMODE         7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFPOSBUCH {
         long    KDAUFTRAGNR;
         long    POSNR;
         long    ARTIKEL_NR;
         short   POSTYP;
         short   FEHLERMENGE;
         long    MENGEBESTELLT;
         long    MENGEBESTAETIGT;
         long    MENGEGELIEFERT;
         long    MENGENATRA;
         char    BEMERKUNG[240 + 1];
         double  WERTAUFTRAG;
         double  WERTLIEFERUNG;
         double  WERTZEILEN;
         long    ANZPOS;
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    MENGEABGEBUCHT;
         long    BESTAND;
         long    STATUS;
         char    POSART[2 + 1];
         double  PREISEKGROSSO;
         double  RABATTFESTDM;
         double  RABATTFEST;
         double  PREISEKAPO;
         char    TAXPFLICHTIG[1 + 1];
         char    RABATTFAEHIG[1 + 1];
         char    MWSTSCHLUESSEL[1 + 1];
         char    DAFUEART[1 + 1];
         char    KZDEFEKT[1 + 1];
         char    KZFREITEXT[1 + 1];
         char    KZLIMITCHK[1 + 1];
         short   LAGERBEREICHNR;
         long    ETARTSCHALTER2;
         char    KURZBEZKONDI[6 + 1];
         long    MENGE;
         short   FILIALNR1;
         char    KZNACHBEARB[1 + 1];
         char    KZAPODINL[1 + 1];
         char    KZAUFGENOMMEN[1 + 1];
         char    KZINFOTEXT[1 + 1];
         char    WARENGRUPPEEIGEN[5 + 1];
         long    URSPRUNGAUFTRAGNR;
         long    URSPRUNGPOSNR;
         double  GEBUEHRBEARB;
         short   SENDESTATUS;
         double  PREISEKAPOFREE;
         short   PREIS_TYP;
         long    ARTICLE_NO_PACK;
         double  DISCOUNTVALUEPCT;
         double  DISCOUNTVALPCTMAN;
         double  BALANCE;
         double  BALANCE2;
         double  WERTNETTO;
         double  WERTRABATT;
         double  PREISFAKTUR;
         double  WERTNETTO_FV;
         double  WERTTAX_FV;
         double  WERTNETTO_KK;
         double  WERTTAX_KK;
         double  WERTNETTO_EH;
         double  WERTTAX_EH;
         long    ETPOSSCHALTER2;
         double  WERTKL;
         short   TAXLEVEL;
         char    ARTIKEL_LANGNAME[50 + 1];
         char    CHARGENNR[25 + 1];
         double  PREISVKAPO;
         short   PROMOTYP;
         char    PHARMACYGROUPID[3 + 1];
         short   PROMOTION_NO;
         long    DISCOUNTGRPNO;
         long    BASEQTY;
         double  BASE_VALUE;
         long    CUSTOMERNO;
         char    ADDONSTDDISCOK[1 + 1];
         double  NETPRICE;
         short   CODE_TYPE;
         char    ARTICLE_CODE[25 + 1];
         short   PROBLEMSTATE;
         double  WERTKL1;
         char    KZPRISO[1 + 1];
         double  WERTEXCLUSIVE;
         short   PRODUSERQUOTA;
         long    LINKPOSNR;
         short   IBTTYPE;
         short   HIGHERCOND;
         short   IBTTYPEID;
         long    DELIVERYDATE;
         long    DELIVERYTIME;
         char    TOURID[6 + 1];
         long    ETARTSCHALTER1;
         long    ETARTKLASSE1;
         long    MENGEBESTELLTNATRA;
         short   FIXBATCH;
         short   DISCOUNTMODE;         
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFPOSBUCH {
         long    KDAUFTRAGNR;
         long    POSNR;
         long    ARTIKEL_NR;
         short   POSTYP;
         short   FEHLERMENGE;
         long    MENGEBESTELLT;
         long    MENGEBESTAETIGT;
         long    MENGEGELIEFERT;
         long    MENGENATRA;
         char    BEMERKUNG[240 + 1];
         double  WERTAUFTRAG;
         double  WERTLIEFERUNG;
         double  WERTZEILEN;
         long    ANZPOS;
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         long    MENGEABGEBUCHT;
         long    BESTAND;
         long    STATUS;
         char    POSART[2 + 1];
         double  PREISEKGROSSO;
         double  RABATTFESTDM;
         double  RABATTFEST;
         double  PREISEKAPO;
         char    TAXPFLICHTIG;
         char    RABATTFAEHIG;
         char    MWSTSCHLUESSEL;
         char    DAFUEART;
         char    KZDEFEKT;
         char    KZFREITEXT;
         char    KZLIMITCHK;
         short   LAGERBEREICHNR;
         long    ETARTSCHALTER2;
         char    KURZBEZKONDI[6 + 1];
         long    MENGE;
         short   FILIALNR1;
         char    KZNACHBEARB;
         char    KZAPODINL;
         char    KZAUFGENOMMEN;
         char    KZINFOTEXT;
         char    WARENGRUPPEEIGEN[5 + 1];
         long    URSPRUNGAUFTRAGNR;
         long    URSPRUNGPOSNR;
         double  GEBUEHRBEARB;
         short   SENDESTATUS;
         double  PREISEKAPOFREE;
         short   PREIS_TYP;
         long    ARTICLE_NO_PACK;
         double  DISCOUNTVALUEPCT;
         double  DISCOUNTVALPCTMAN;
         double  BALANCE;
         double  BALANCE2;
         double  WERTNETTO;
         double  WERTRABATT;
         double  PREISFAKTUR;
         double  WERTNETTO_FV;
         double  WERTTAX_FV;
         double  WERTNETTO_KK;
         double  WERTTAX_KK;
         double  WERTNETTO_EH;
         double  WERTTAX_EH;
         long    ETPOSSCHALTER2;
         double  WERTKL;
         short   TAXLEVEL;
         char    ARTIKEL_LANGNAME[50 + 1];
         char    CHARGENNR[25 + 1];
         double  PREISVKAPO;
         short   PROMOTYP;
         char    PHARMACYGROUPID[3 + 1];
         short   PROMOTION_NO;
         long    DISCOUNTGRPNO;
         long    BASEQTY;
         double  BASE_VALUE;
         long    CUSTOMERNO;
         char    ADDONSTDDISCOK;
         double  NETPRICE;
         short   CODE_TYPE;
         char    ARTICLE_CODE[25 + 1];
         short   PROBLEMSTATE;
         double  WERTKL1;
         char    KZPRISO;
         double  WERTEXCLUSIVE;
         short   PRODUSERQUOTA;
         long    LINKPOSNR;
         short   IBTTYPE;
         short   HIGHERCOND;
         short   IBTTYPEID;
         long    DELIVERYDATE;
         long    DELIVERYTIME;
         char    TOURID[6 + 1];
         long    ETARTSCHALTER1;
         long    ETARTKLASSE1;
         long    MENGEBESTELLTNATRA;
         short   FIXBATCH;
         short   DISCOUNTMODE;         
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFPOSBUCH {
         short  KDAUFTRAGNR;
         short  POSNR;
         short  ARTIKEL_NR;
         short  POSTYP;
         short  FEHLERMENGE;
         short  MENGEBESTELLT;
         short  MENGEBESTAETIGT;
         short  MENGEGELIEFERT;
         short  MENGENATRA;
         short  BEMERKUNG;
         short  WERTAUFTRAG;
         short  WERTLIEFERUNG;
         short  WERTZEILEN;
         short  ANZPOS;
         short  DARREICHFORM;
         short  EINHEIT;
         short  ARTIKEL_NAME;
         short  MENGEABGEBUCHT;
         short  BESTAND;
         short  STATUS;
         short  POSART;
         short  PREISEKGROSSO;
         short  RABATTFESTDM;
         short  RABATTFEST;
         short  PREISEKAPO;
         short  TAXPFLICHTIG;
         short  RABATTFAEHIG;
         short  MWSTSCHLUESSEL;
         short  DAFUEART;
         short  KZDEFEKT;
         short  KZFREITEXT;
         short  KZLIMITCHK;
         short  LAGERBEREICHNR;
         short  ETARTSCHALTER2;
         short  KURZBEZKONDI;
         short  MENGE;
         short  FILIALNR1;
         short  KZNACHBEARB;
         short  KZAPODINL;
         short  KZAUFGENOMMEN;
         short  KZINFOTEXT;
         short  WARENGRUPPEEIGEN;
         short  URSPRUNGAUFTRAGNR;
         short  URSPRUNGPOSNR;
         short  GEBUEHRBEARB;
         short  SENDESTATUS;
         short  PREISEKAPOFREE;
         short  PREIS_TYP;
         short  ARTICLE_NO_PACK;
         short  DISCOUNTVALUEPCT;
         short  DISCOUNTVALPCTMAN;
         short  BALANCE;
         short  BALANCE2;
         short  WERTNETTO;
         short  WERTRABATT;
         short  PREISFAKTUR;
         short  WERTNETTO_FV;
         short  WERTTAX_FV;
         short  WERTNETTO_KK;
         short  WERTTAX_KK;
         short  WERTNETTO_EH;
         short  WERTTAX_EH;
         short  ETPOSSCHALTER2;
         short  WERTKL;
         short  TAXLEVEL;
         short  ARTIKEL_LANGNAME;
         short  CHARGENNR;
         short  PREISVKAPO;
         short  PROMOTYP;
         short  PHARMACYGROUPID;
         short  PROMOTION_NO;
         short  DISCOUNTGRPNO;
         short  BASEQTY;
         short  BASE_VALUE;
         short  CUSTOMERNO;
         short  ADDONSTDDISCOK;
         short  NETPRICE;
         short  CODE_TYPE;
         short  ARTICLE_CODE;
         short  PROBLEMSTATE;
         short  WERTKL1;
         short  KZPRISO;
         short  WERTEXCLUSIVE;
         short  PRODUSERQUOTA;
         short  LINKPOSNR;
         short  IBTTYPE;
         short  HIGHERCOND;
         short  IBTTYPEID;
         short  DELIVERYDATE;
         short  DELIVERYTIME;
         short  TOURID;
         short  ETARTSCHALTER1;
         short  ETARTKLASSE1;
         short  MENGEBESTELLTNATRA;
         short  FIXBATCH;
         short  DISCOUNTMODE;         
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFPOSBUCH {
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    ARTIKEL_NR[11];
         char    POSTYP[7];
         char    FEHLERMENGE[7];
         char    MENGEBESTELLT[11];
         char    MENGEBESTAETIGT[11];
         char    MENGEGELIEFERT[11];
         char    MENGENATRA[11];
         char    BEMERKUNG[240 + 1];
         char    WERTAUFTRAG[9 + 2];
         char    WERTLIEFERUNG[9 + 2];
         char    WERTZEILEN[9 + 2];
         char    ANZPOS[11];
         char    DARREICHFORM[3 + 1];
         char    EINHEIT[9 + 1];
         char    ARTIKEL_NAME[30 + 1];
         char    MENGEABGEBUCHT[11];
         char    BESTAND[11];
         char    STATUS[11];
         char    POSART[2 + 1];
         char    PREISEKGROSSO[9 + 2];
         char    RABATTFESTDM[9 + 2];
         char    RABATTFEST[5 + 2];
         char    PREISEKAPO[9 + 2];
         char    TAXPFLICHTIG[1 + 1];
         char    RABATTFAEHIG[1 + 1];
         char    MWSTSCHLUESSEL[1 + 1];
         char    DAFUEART[1 + 1];
         char    KZDEFEKT[1 + 1];
         char    KZFREITEXT[1 + 1];
         char    KZLIMITCHK[1 + 1];
         char    LAGERBEREICHNR[7];
         char    ETARTSCHALTER2[5 + 1];
         char    KURZBEZKONDI[6 + 1];
         char    MENGE[11];
         char    FILIALNR1[7];
         char    KZNACHBEARB[1 + 1];
         char    KZAPODINL[1 + 1];
         char    KZAUFGENOMMEN[1 + 1];
         char    KZINFOTEXT[1 + 1];
         char    WARENGRUPPEEIGEN[5 + 1];
         char    URSPRUNGAUFTRAGNR[11];
         char    URSPRUNGPOSNR[11];
         char    GEBUEHRBEARB[7 + 2];
         char    SENDESTATUS[7];
         char    PREISEKAPOFREE[9 + 2];
         char    PREIS_TYP[7];
         char    ARTICLE_NO_PACK[11];
         char    DISCOUNTVALUEPCT[5 + 2];
         char    DISCOUNTVALPCTMAN[5 + 2];
         char    BALANCE[11 + 2];
         char    BALANCE2[11 + 2];
         char    WERTNETTO[9 + 2];
         char    WERTRABATT[9 + 2];
         char    PREISFAKTUR[9 + 2];
         char    WERTNETTO_FV[9 + 2];
         char    WERTTAX_FV[9 + 2];
         char    WERTNETTO_KK[9 + 2];
         char    WERTTAX_KK[9 + 2];
         char    WERTNETTO_EH[9 + 2];
         char    WERTTAX_EH[9 + 2];
         char    ETPOSSCHALTER2[5 + 1];
         char    WERTKL[9 + 2];
         char    TAXLEVEL[7];
         char    ARTIKEL_LANGNAME[50 + 1];
         char    CHARGENNR[25 + 1];
         char    PREISVKAPO[9 + 2];
         char    PROMOTYP[7];
         char    PHARMACYGROUPID[3 + 1];
         char    PROMOTION_NO[7];
         char    DISCOUNTGRPNO[11];
         char    BASEQTY[11];
         char    BASE_VALUE[9 + 2];
         char    CUSTOMERNO[11];
         char    ADDONSTDDISCOK[1 + 1];
         char    NETPRICE[11 + 4];
         char    CODE_TYPE[7];
         char    ARTICLE_CODE[25 + 1];
         char    PROBLEMSTATE[7];
         char    WERTKL1[9 + 2];
         char    KZPRISO[1 + 1];
         char    WERTEXCLUSIVE[9 + 2];
         char    PRODUSERQUOTA[7];
         char    LINKPOSNR[11];
         char    IBTTYPE[7];
         char    HIGHERCOND[7];
         char    IBTTYPEID[7];
         char    DELIVERYDATE[11];
         char    DELIVERYTIME[11];
         char    TOURID[6 + 1];
         char    ETARTSCHALTER1[5 + 1];
         char    ETARTKLASSE1[5 + 1];
         char    MENGEBESTELLTNATRA[11];
         char    FIXBATCH[7];
         char    DISCOUNTMODE[7];         
         char    FETCH_REL[11];
       };

 struct O_AUFPOSBUCH {
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    ARTIKEL_NR[11];
         char    POSTYP[7];
         char    FEHLERMENGE[7];
         char    MENGEBESTELLT[11];
         char    MENGEBESTAETIGT[11];
         char    MENGEGELIEFERT[11];
         char    MENGENATRA[11];
         char    BEMERKUNG[240];
         char    WERTAUFTRAG[9];
         char    WERTLIEFERUNG[9];
         char    WERTZEILEN[9];
         char    ANZPOS[11];
         char    DARREICHFORM[3];
         char    EINHEIT[9];
         char    ARTIKEL_NAME[30];
         char    MENGEABGEBUCHT[11];
         char    BESTAND[11];
         char    STATUS[11];
         char    POSART[2];
         char    PREISEKGROSSO[9];
         char    RABATTFESTDM[9];
         char    RABATTFEST[5];
         char    PREISEKAPO[9];
         char    TAXPFLICHTIG[1];
         char    RABATTFAEHIG[1];
         char    MWSTSCHLUESSEL[1];
         char    DAFUEART[1];
         char    KZDEFEKT[1];
         char    KZFREITEXT[1];
         char    KZLIMITCHK[1];
         char    LAGERBEREICHNR[7];
         char    ETARTSCHALTER2[5];
         char    KURZBEZKONDI[6];
         char    MENGE[11];
         char    FILIALNR1[7];
         char    KZNACHBEARB[1];
         char    KZAPODINL[1];
         char    KZAUFGENOMMEN[1];
         char    KZINFOTEXT[1];
         char    WARENGRUPPEEIGEN[5];
         char    URSPRUNGAUFTRAGNR[11];
         char    URSPRUNGPOSNR[11];
         char    GEBUEHRBEARB[7];
         char    SENDESTATUS[7];
         char    PREISEKAPOFREE[9];
         char    PREIS_TYP[7];
         char    ARTICLE_NO_PACK[11];
         char    DISCOUNTVALUEPCT[5];
         char    DISCOUNTVALPCTMAN[5];
         char    BALANCE[11];
         char    BALANCE2[11];
         char    WERTNETTO[9];
         char    WERTRABATT[9];
         char    PREISFAKTUR[9];
         char    WERTNETTO_FV[9];
         char    WERTTAX_FV[9];
         char    WERTNETTO_KK[9];
         char    WERTTAX_KK[9];
         char    WERTNETTO_EH[9];
         char    WERTTAX_EH[9];
         char    ETPOSSCHALTER2[5];
         char    WERTKL[9];
         char    TAXLEVEL[7];
         char    ARTIKEL_LANGNAME[50];
         char    CHARGENNR[25];
         char    PREISVKAPO[9];
         char    PROMOTYP[7];
         char    PHARMACYGROUPID[3];
         char    PROMOTION_NO[7];
         char    DISCOUNTGRPNO[11];
         char    BASEQTY[11];
         char    BASE_VALUE[9];
         char    CUSTOMERNO[11];
         char    ADDONSTDDISCOK[1];
         char    NETPRICE[11];
         char    CODE_TYPE[7];
         char    ARTICLE_CODE[25];
         char    PROBLEMSTATE[7];
         char    WERTKL1[9];
         char    KZPRISO[1];
         char    WERTEXCLUSIVE[9];
         char    PRODUSERQUOTA[7];
         char    LINKPOSNR[11];
         char    IBTTYPE[7];
         char    HIGHERCOND[7];
         char    IBTTYPEID[7];
         char    DELIVERYDATE[11];
         char    DELIVERYTIME[11];
         char    TOURID[6];
         char    ETARTSCHALTER1[5];
         char    ETARTKLASSE1[5];
         char    MENGEBESTELLTNATRA[11];
         char    FIXBATCH[7];
         char    DISCOUNTMODE[7];         
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFPOSBUCH_BES [] =
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
     { TYP_C ,  240 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    3 ,   0 },
     { TYP_C ,    9 ,   0 },
     { TYP_C ,   30 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    5 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    5 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_D ,    7 ,   2 },
     { TYP_S ,    6 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_D ,    5 ,   2 },
     { TYP_D ,    5 ,   2 },
     { TYP_D ,   11 ,   2 },
     { TYP_D ,   11 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,   50 ,   0 },
     { TYP_C ,   25 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,    3 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_D ,   11 ,   4 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,   25 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_C ,    1 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFPOSBUCH_BES [] =
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
     { TYP_C,  240 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_C,    9 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    5 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_C,    5 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_D ,   7 ,   2 },
     { TYP_S,    5 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_D,    5 ,   2 },
     { TYP_D,    5 ,   2 },
     { TYP_D,   11 ,   2 },
     { TYP_D,   11 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_S,    5 ,   0 },
     { TYP_C,   50 ,   0 },
     { TYP_C,   25 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_S,    5 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_D,   11 ,   4 },
     { TYP_S,    5 ,   0 },
     { TYP_C,   25 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_F,    1 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },	 
     { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFPOSBUCH
 {
  public:

  AUFPOSBUCH s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFPOSBUCH_BES, AUFPOSBUCH_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFPOSBUCH_BES, AUFPOSBUCH_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFPOSBUCH()
  {
   ::buf_default((void *)&s, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
  }
 };
#endif


#define AUFPOSBUCH_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         KDAUFTRAGNR INTEGER           ,\
         POSNR INTEGER           ,\
         ARTIKEL_NR INTEGER           ,\
         POSTYP SMALLINT          ,\
         FEHLERMENGE SMALLINT          ,\
         MENGEBESTELLT INTEGER           ,\
         MENGEBESTAETIGT INTEGER           ,\
         MENGEGELIEFERT INTEGER           ,\
         MENGENATRA INTEGER           ,\
         BEMERKUNG VARCHAR(240,0)    ,\
         WERTAUFTRAG DECIMAL(9,2)      ,\
         WERTLIEFERUNG DECIMAL(9,2)      ,\
         WERTZEILEN DECIMAL(9,2)      ,\
         ANZPOS INTEGER           ,\
         DARREICHFORM CHAR(3)           ,\
         EINHEIT CHAR(9)           ,\
         ARTIKEL_NAME CHAR(30)          ,\
         MENGEABGEBUCHT INTEGER           ,\
         BESTAND INTEGER           ,\
         STATUS INTEGER           ,\
         POSART CHAR(2)           ,\
         PREISEKGROSSO DECIMAL(9,2)      ,\
         RABATTFESTDM DECIMAL(9,2)      ,\
         RABATTFEST DECIMAL(5,2)      ,\
         PREISEKAPO DECIMAL(9,2)      ,\
         TAXPFLICHTIG CHAR(1)           ,\
         RABATTFAEHIG CHAR(1)           ,\
         MWSTSCHLUESSEL CHAR(1)           ,\
         DAFUEART CHAR(1)           ,\
         KZDEFEKT CHAR(1)           ,\
         KZFREITEXT CHAR(1)           ,\
         KZLIMITCHK CHAR(1)           ,\
         LAGERBEREICHNR SMALLINT          ,\
         ETARTSCHALTER2 INTEGER,\
         KURZBEZKONDI CHAR(6)           ,\
         MENGE INTEGER           ,\
         FILIALNR1 SMALLINT          ,\
         KZNACHBEARB CHAR(1)           ,\
         KZAPODINL CHAR(1)           ,\
         KZAUFGENOMMEN CHAR(1)           ,\
         KZINFOTEXT CHAR(1)           ,\
         WARENGRUPPEEIGEN CHAR(5)           ,\
         URSPRUNGAUFTRAGNR INTEGER           ,\
         URSPRUNGPOSNR INTEGER           ,\
         GEBUEHRBEARB DECIMAL(5,2)      ,\
         SENDESTATUS SMALLINT          ,\
         PREISEKAPOFREE DECIMAL(9,2)      ,\
         PREIS_TYP SMALLINT          ,\
         ARTICLE_NO_PACK INTEGER           ,\
         DISCOUNTVALUEPCT DECIMAL(5,2)      ,\
         DISCOUNTVALPCTMAN DECIMAL(5,2)      ,\
         BALANCE decimal(11,2) default 0 not null,\
         BALANCE2 decimal(11,2) default 0 not null,\
         WERTNETTO DECIMAL(9,2)      ,\
         WERTRABATT DECIMAL(9,2)      ,\
         PREISFAKTUR DECIMAL(9,2)      ,\
         WERTNETTO_FV DECIMAL(9,2)      ,\
         WERTTAX_FV DECIMAL(9,2)      ,\
         WERTNETTO_KK DECIMAL(9,2)      ,\
         WERTTAX_KK DECIMAL(9,2)      ,\
         WERTNETTO_EH DECIMAL(9,2)      ,\
         WERTTAX_EH DECIMAL(9,2)      ,\
         ETPOSSCHALTER2 INTEGER,\
         WERTKL DECIMAL(9,2)      ,\
         TAXLEVEL SMALLINT          ,\
         ARTIKEL_LANGNAME CHAR(50)          ,\
         CHARGENNR CHAR(25)          ,\
         PREISVKAPO DECIMAL(9,2)      ,\
         PROMOTYP SMALLINT          ,\
         PHARMACYGROUPID CHAR(3)           ,\
         PROMOTION_NO SMALLINT          ,\
         DISCOUNTGRPNO INTEGER,\
         BASEQTY INTEGER,\
         BASE_VALUE DECIMAL(9,2)      ,\
         CUSTOMERNO INTEGER,\
         ADDONSTDDISCOK CHAR(1)           ,\
         NETPRICE DECIMAL(11,4)      ,\
         CODE_TYPE SMALLINT          ,\
         ARTICLE_CODE CHAR(25)           ,\
         PROBLEMSTATE SMALLINT          ,\
         WERTKL1 DECIMAL(9,2)      ,\
         KZPRISO CHAR(1)           ,\
         WERTEXCLUSIVE DECIMAL(9,2)      ,\
         PRODUSERQUOTA SMALLINT          ,\
         LINKPOSNR INTEGER,\
         IBTTYPE SMALLINT          ,\
         HIGHERCOND SMALLINT          ,\
         IBTTYPEID SMALLINT          ,\
         DELIVERYDATE INTEGER,\
         DELIVERYTIME INTEGER,\
         KZPRISO CHAR(6)           ,\
         ETARTSCHALTER1 INTEGER,\
         ETARTKLASSE1 INTEGER,\
         MENGEBESTELLTNATRA INTEGER,\
         FIXBATCH SMALLINT          ,\
         DISCOUNTMODE SMALLINT    ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 19300 LOCK MODE ROW;

#define AUFPOSBUCH_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGPOSX      on yyy( KDAUFTRAGNR, POSNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFPOSBUCH_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGPOSX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFPOSNACH_KDAUFTRAGNR          11
 #define L_AUFPOSNACH_POSNR                11
 #define L_AUFPOSNACH_KZNACHBEARB          1
 #define L_AUFPOSNACH_KZAUFGENOMMEN        1


 #define L_AUFPOSNACH_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFPOSNACH_ANZ (int) ( sizeof(AUFPOSNACH_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFPOSNACH sizeof(struct AUFPOSNACH)


 #define AUFPOSNACH_H

 #define AUFPOSNACH_LISTE \
            KDAUFTRAGPOS.KDAUFTRAGNR, \
            KDAUFTRAGPOS.POSNR, \
            AADUMMY.KZNACHBEARB, \
            AADUMMY.KZAUFGENOMMEN
 #define AUFPOSNACH_PLISTE \
            "KDAUFTRAGPOS.KDAUFTRAGNR," \
            "KDAUFTRAGPOS.POSNR," \
            "AADUMMY.KZNACHBEARB," \
            "AADUMMY.KZAUFGENOMMEN "

 #define AUFPOSNACH_PELISTE \
            "KDAUFTRAGNR," \
            "POSNR," \
            "KZNACHBEARB," \
            "KZAUFGENOMMEN "

 #define AUFPOSNACH_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "POSNR=?," \
            "KZNACHBEARB=?," \
            "KZAUFGENOMMEN=? "

 #define AUFPOSNACHKDAUFTRAGNR                   0
 #define AUFPOSNACHPOSNR                         1
 #define AUFPOSNACHKZNACHBEARB                   2
 #define AUFPOSNACHKZAUFGENOMMEN                 3

 #define AUFPOSNACH_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR,\
            :xxx->POSNR,\
            :xxx->KZNACHBEARB,\
            :xxx->KZAUFGENOMMEN

 #define AUFPOSNACH_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            POSNR = :xxx->POSNR,\
            KZNACHBEARB = :xxx->KZNACHBEARB,\
            KZAUFGENOMMEN = :xxx->KZAUFGENOMMEN

 #define LS_AUFPOSNACH_KDAUFTRAGNR          11
 #define LS_AUFPOSNACH_POSNR                11
 #define LS_AUFPOSNACH_KZNACHBEARB          2
 #define LS_AUFPOSNACH_KZAUFGENOMMEN        2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFPOSNACH {
         long    KDAUFTRAGNR;
         long    POSNR;
         char    KZNACHBEARB[1 + 1];
         char    KZAUFGENOMMEN[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFPOSNACH {
         long    KDAUFTRAGNR;
         long    POSNR;
         char    KZNACHBEARB;
         char    KZAUFGENOMMEN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFPOSNACH {
         short  KDAUFTRAGNR;
         short  POSNR;
         short  KZNACHBEARB;
         short  KZAUFGENOMMEN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFPOSNACH {
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    KZNACHBEARB[1 + 1];
         char    KZAUFGENOMMEN[1 + 1];
       };

 struct O_AUFPOSNACH {
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    KZNACHBEARB[1];
         char    KZAUFGENOMMEN[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFPOSNACH_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFPOSNACH_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFPOSNACH
 {
  public:

  AUFPOSNACH s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFPOSNACH_BES, AUFPOSNACH_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFPOSNACH_BES, AUFPOSNACH_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFPOSNACH_BES, AUFPOSNACH_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFPOSNACH()
  {
   ::buf_default((void *)&s, AUFPOSNACH_BES, AUFPOSNACH_ANZ);
  }
 };
#endif

#define AUFPOSNACH_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         KDAUFTRAGNR INTEGER           ,\
         POSNR INTEGER           ,\
         KZNACHBEARB CHAR(1)           ,\
         KZAUFGENOMMEN CHAR(1)             ) EXTENT SIZE 2797 LOCK MODE ROW;

#define AUFPOSNACH_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGPOSX      on yyy( KDAUFTRAGNR, POSNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFPOSNACH_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGPOSX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFSESS_GERAETNAME           8


 #define L_AUFSESS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFSESS_ANZ (int) ( sizeof(AUFSESS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFSESS sizeof(struct AUFSESS)


 #define AUFSESS_H

 #define AUFSESS_LISTE \
            KDAUFTRAG.GERAETNAME
 #define AUFSESS_PLISTE \
            "KDAUFTRAG.GERAETNAME "

 #define AUFSESS_PELISTE \
            "GERAETNAME "

 #define AUFSESS_UPDLISTE \
            "GERAETNAME=? "

 #define AUFSESSGERAETNAME                    0

 #define AUFSESS_ZEIGER(xxx) \
            :xxx->GERAETNAME

 #define AUFSESS_UPDATE(xxx) \
            GERAETNAME = :xxx->GERAETNAME

 #define LS_AUFSESS_GERAETNAME           9

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFSESS {
         char    GERAETNAME[8 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFSESS {
         char    GERAETNAME[8 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFSESS {
         short  GERAETNAME;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFSESS {
         char    GERAETNAME[8 + 1];
       };

 struct O_AUFSESS {
         char    GERAETNAME[8];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFSESS_BES [] =
 {
     { TYP_C ,    8 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFSESS_BES [] =
 {
     { TYP_C,    8 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFSESS
 {
  public:

  AUFSESS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFSESS_BES, AUFSESS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFSESS_BES, AUFSESS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFSESS_BES, AUFSESS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFSESS()
  {
   ::buf_default((void *)&s, AUFSESS_BES, AUFSESS_ANZ);
  }
 };
#endif

#define AUFSESS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         GERAETNAME CHAR(8)             ) EXTENT SIZE 165 LOCK MODE ROW;

#define AUFSESS_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_305    on yyy( GERAETNAME );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFSESS_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KDAUFTRAG_305   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFSTATUS_ANZ_ER               11
 #define L_AUFSTATUS_ANZ_BF               11
 #define L_AUFSTATUS_ANZ_FA               11
 #define L_AUFSTATUS_ANZ_ZU               11
 #define L_AUFSTATUS_ANZ_IK               11
 #define L_AUFSTATUS_ANZ_GD               11
 #define L_AUFSTATUS_ANZ_ST               11
 #define L_AUFSTATUS_FAKTUR_ZEILEN        11
 #define L_AUFSTATUS_FAKTUR_WERT          11
 #define L_AUFSTATUS_WERT_AND_NL          11
 #define L_AUFSTATUS_ANZ_WANNEN           11
 #define L_AUFSTATUS_FEHLER               11
 #define L_AUFSTATUS_ANZ_IE               11
 #define L_AUFSTATUS_ANZ_IAEN             11
 #define L_AUFSTATUS_ANZ_UNBEKANNT        11
 #define L_AUFSTATUS_PHONANZ              11
 #define L_AUFSTATUS_PHONMIN              11
 #define L_AUFSTATUS_PARAANZ              11
 #define L_AUFSTATUS_PARAMIN              11
 #define L_AUFSTATUS_SERAANZ              11
 #define L_AUFSTATUS_SERAMIN              11
 #define L_AUFSTATUS_ANZ_DD               11


 #define L_AUFSTATUS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFSTATUS_ANZ (int) ( sizeof(AUFSTATUS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFSTATUS sizeof(struct AUFSTATUS)


 #define AUFSTATUS_H

 #define AUFSTATUS_LISTE \
            AADUMMY.ANZ_ER, \
            AADUMMY.ANZ_BF, \
            AADUMMY.ANZ_FA, \
            AADUMMY.ANZ_ZU, \
            AADUMMY.ANZ_IK, \
            AADUMMY.ANZ_GD, \
            AADUMMY.ANZ_ST, \
            AADUMMY.FAKTUR_ZEILEN, \
            AADUMMY.FAKTUR_WERT, \
            AADUMMY.WERT_AND_NL, \
            AADUMMY.ANZ_WANNEN, \
            AADUMMY.FEHLER, \
            AADUMMY.ANZ_IE, \
            AADUMMY.ANZ_IAEN, \
            AADUMMY.ANZ_UNBEKANNT, \
            AADUMMY.PHONANZ, \
            AADUMMY.PHONMIN, \
            AADUMMY.PARAANZ, \
            AADUMMY.PARAMIN, \
            AADUMMY.SERAANZ, \
            AADUMMY.SERAMIN, \
            AADUMMY.ANZ_DD
 #define AUFSTATUS_PLISTE \
            "AADUMMY.ANZ_ER," \
            "AADUMMY.ANZ_BF," \
            "AADUMMY.ANZ_FA," \
            "AADUMMY.ANZ_ZU," \
            "AADUMMY.ANZ_IK," \
            "AADUMMY.ANZ_GD," \
            "AADUMMY.ANZ_ST," \
            "AADUMMY.FAKTUR_ZEILEN," \
            "AADUMMY.FAKTUR_WERT," \
            "AADUMMY.WERT_AND_NL," \
            "AADUMMY.ANZ_WANNEN," \
            "AADUMMY.FEHLER," \
            "AADUMMY.ANZ_IE," \
            "AADUMMY.ANZ_IAEN," \
            "AADUMMY.ANZ_UNBEKANNT," \
            "AADUMMY.PHONANZ," \
            "AADUMMY.PHONMIN," \
            "AADUMMY.PARAANZ," \
            "AADUMMY.PARAMIN," \
            "AADUMMY.SERAANZ," \
            "AADUMMY.SERAMIN," \
            "AADUMMY.ANZ_DD "

 #define AUFSTATUS_PELISTE \
            "ANZ_ER," \
            "ANZ_BF," \
            "ANZ_FA," \
            "ANZ_ZU," \
            "ANZ_IK," \
            "ANZ_GD," \
            "ANZ_ST," \
            "FAKTUR_ZEILEN," \
            "FAKTUR_WERT," \
            "WERT_AND_NL," \
            "ANZ_WANNEN," \
            "FEHLER," \
            "ANZ_IE," \
            "ANZ_IAEN," \
            "ANZ_UNBEKANNT," \
            "PHONANZ," \
            "PHONMIN," \
            "PARAANZ," \
            "PARAMIN," \
            "SERAANZ," \
            "SERAMIN," \
            "ANZ_DD "

 #define AUFSTATUS_UPDLISTE \
            "ANZ_ER=?," \
            "ANZ_BF=?," \
            "ANZ_FA=?," \
            "ANZ_ZU=?," \
            "ANZ_IK=?," \
            "ANZ_GD=?," \
            "ANZ_ST=?," \
            "FAKTUR_ZEILEN=?," \
            "FAKTUR_WERT=?," \
            "WERT_AND_NL=?," \
            "ANZ_WANNEN=?," \
            "FEHLER=?," \
            "ANZ_IE=?," \
            "ANZ_IAEN=?," \
            "ANZ_UNBEKANNT=?," \
            "PHONANZ=?," \
            "PHONMIN=?," \
            "PARAANZ=?," \
            "PARAMIN=?," \
            "SERAANZ=?," \
            "SERAMIN=?," \
            "ANZ_DD=? "

 #define AUFSTATUSANZ_ER                        0
 #define AUFSTATUSANZ_BF                        1
 #define AUFSTATUSANZ_FA                        2
 #define AUFSTATUSANZ_ZU                        3
 #define AUFSTATUSANZ_IK                        4
 #define AUFSTATUSANZ_GD                        5
 #define AUFSTATUSANZ_ST                        6
 #define AUFSTATUSFAKTUR_ZEILEN                 7
 #define AUFSTATUSFAKTUR_WERT                   8
 #define AUFSTATUSWERT_AND_NL                   9
 #define AUFSTATUSANZ_WANNEN                    10
 #define AUFSTATUSFEHLER                        11
 #define AUFSTATUSANZ_IE                        12
 #define AUFSTATUSANZ_IAEN                      13
 #define AUFSTATUSANZ_UNBEKANNT                 14
 #define AUFSTATUSPHONANZ                       15
 #define AUFSTATUSPHONMIN                       16
 #define AUFSTATUSPARAANZ                       17
 #define AUFSTATUSPARAMIN                       18
 #define AUFSTATUSSERAANZ                       19
 #define AUFSTATUSSERAMIN                       20
 #define AUFSTATUSANZ_DD                        21

 #define AUFSTATUS_ZEIGER(xxx) \
            :xxx->ANZ_ER,\
            :xxx->ANZ_BF,\
            :xxx->ANZ_FA,\
            :xxx->ANZ_ZU,\
            :xxx->ANZ_IK,\
            :xxx->ANZ_GD,\
            :xxx->ANZ_ST,\
            :xxx->FAKTUR_ZEILEN,\
            :xxx->FAKTUR_WERT,\
            :xxx->WERT_AND_NL,\
            :xxx->ANZ_WANNEN,\
            :xxx->FEHLER,\
            :xxx->ANZ_IE,\
            :xxx->ANZ_IAEN,\
            :xxx->ANZ_UNBEKANNT,\
            :xxx->PHONANZ,\
            :xxx->PHONMIN,\
            :xxx->PARAANZ,\
            :xxx->PARAMIN,\
            :xxx->SERAANZ,\
            :xxx->SERAMIN,\
            :xxx->ANZ_DD

 #define AUFSTATUS_UPDATE(xxx) \
            ANZ_ER = :xxx->ANZ_ER,\
            ANZ_BF = :xxx->ANZ_BF,\
            ANZ_FA = :xxx->ANZ_FA,\
            ANZ_ZU = :xxx->ANZ_ZU,\
            ANZ_IK = :xxx->ANZ_IK,\
            ANZ_GD = :xxx->ANZ_GD,\
            ANZ_ST = :xxx->ANZ_ST,\
            FAKTUR_ZEILEN = :xxx->FAKTUR_ZEILEN,\
            FAKTUR_WERT = :xxx->FAKTUR_WERT,\
            WERT_AND_NL = :xxx->WERT_AND_NL,\
            ANZ_WANNEN = :xxx->ANZ_WANNEN,\
            FEHLER = :xxx->FEHLER,\
            ANZ_IE = :xxx->ANZ_IE,\
            ANZ_IAEN = :xxx->ANZ_IAEN,\
            ANZ_UNBEKANNT = :xxx->ANZ_UNBEKANNT,\
            PHONANZ = :xxx->PHONANZ,\
            PHONMIN = :xxx->PHONMIN,\
            PARAANZ = :xxx->PARAANZ,\
            PARAMIN = :xxx->PARAMIN,\
            SERAANZ = :xxx->SERAANZ,\
            SERAMIN = :xxx->SERAMIN,\
            ANZ_DD = :xxx->ANZ_DD

 #define LS_AUFSTATUS_ANZ_ER               11
 #define LS_AUFSTATUS_ANZ_BF               11
 #define LS_AUFSTATUS_ANZ_FA               11
 #define LS_AUFSTATUS_ANZ_ZU               11
 #define LS_AUFSTATUS_ANZ_IK               11
 #define LS_AUFSTATUS_ANZ_GD               11
 #define LS_AUFSTATUS_ANZ_ST               11
 #define LS_AUFSTATUS_FAKTUR_ZEILEN        11
 #define LS_AUFSTATUS_FAKTUR_WERT          11
 #define LS_AUFSTATUS_WERT_AND_NL          11
 #define LS_AUFSTATUS_ANZ_WANNEN           11
 #define LS_AUFSTATUS_FEHLER               11
 #define LS_AUFSTATUS_ANZ_IE               11
 #define LS_AUFSTATUS_ANZ_IAEN             11
 #define LS_AUFSTATUS_ANZ_UNBEKANNT        11
 #define LS_AUFSTATUS_PHONANZ              11
 #define LS_AUFSTATUS_PHONMIN              11
 #define LS_AUFSTATUS_PARAANZ              11
 #define LS_AUFSTATUS_PARAMIN              11
 #define LS_AUFSTATUS_SERAANZ              11
 #define LS_AUFSTATUS_SERAMIN              11
 #define LS_AUFSTATUS_ANZ_DD               11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFSTATUS {
         long    ANZ_ER;
         long    ANZ_BF;
         long    ANZ_FA;
         long    ANZ_ZU;
         long    ANZ_IK;
         long    ANZ_GD;
         long    ANZ_ST;
         long    FAKTUR_ZEILEN;
         long    FAKTUR_WERT;
         long    WERT_AND_NL;
         long    ANZ_WANNEN;
         long    FEHLER;
         long    ANZ_IE;
         long    ANZ_IAEN;
         long    ANZ_UNBEKANNT;
         long    PHONANZ;
         long    PHONMIN;
         long    PARAANZ;
         long    PARAMIN;
         long    SERAANZ;
         long    SERAMIN;
         long    ANZ_DD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFSTATUS {
         long    ANZ_ER;
         long    ANZ_BF;
         long    ANZ_FA;
         long    ANZ_ZU;
         long    ANZ_IK;
         long    ANZ_GD;
         long    ANZ_ST;
         long    FAKTUR_ZEILEN;
         long    FAKTUR_WERT;
         long    WERT_AND_NL;
         long    ANZ_WANNEN;
         long    FEHLER;
         long    ANZ_IE;
         long    ANZ_IAEN;
         long    ANZ_UNBEKANNT;
         long    PHONANZ;
         long    PHONMIN;
         long    PARAANZ;
         long    PARAMIN;
         long    SERAANZ;
         long    SERAMIN;
         long    ANZ_DD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFSTATUS {
         short  ANZ_ER;
         short  ANZ_BF;
         short  ANZ_FA;
         short  ANZ_ZU;
         short  ANZ_IK;
         short  ANZ_GD;
         short  ANZ_ST;
         short  FAKTUR_ZEILEN;
         short  FAKTUR_WERT;
         short  WERT_AND_NL;
         short  ANZ_WANNEN;
         short  FEHLER;
         short  ANZ_IE;
         short  ANZ_IAEN;
         short  ANZ_UNBEKANNT;
         short  PHONANZ;
         short  PHONMIN;
         short  PARAANZ;
         short  PARAMIN;
         short  SERAANZ;
         short  SERAMIN;
         short  ANZ_DD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFSTATUS {
         char    ANZ_ER[11];
         char    ANZ_BF[11];
         char    ANZ_FA[11];
         char    ANZ_ZU[11];
         char    ANZ_IK[11];
         char    ANZ_GD[11];
         char    ANZ_ST[11];
         char    FAKTUR_ZEILEN[11];
         char    FAKTUR_WERT[11];
         char    WERT_AND_NL[11];
         char    ANZ_WANNEN[11];
         char    FEHLER[11];
         char    ANZ_IE[11];
         char    ANZ_IAEN[11];
         char    ANZ_UNBEKANNT[11];
         char    PHONANZ[11];
         char    PHONMIN[11];
         char    PARAANZ[11];
         char    PARAMIN[11];
         char    SERAANZ[11];
         char    SERAMIN[11];
         char    ANZ_DD[11];
       };

 struct O_AUFSTATUS {
         char    ANZ_ER[11];
         char    ANZ_BF[11];
         char    ANZ_FA[11];
         char    ANZ_ZU[11];
         char    ANZ_IK[11];
         char    ANZ_GD[11];
         char    ANZ_ST[11];
         char    FAKTUR_ZEILEN[11];
         char    FAKTUR_WERT[11];
         char    WERT_AND_NL[11];
         char    ANZ_WANNEN[11];
         char    FEHLER[11];
         char    ANZ_IE[11];
         char    ANZ_IAEN[11];
         char    ANZ_UNBEKANNT[11];
         char    PHONANZ[11];
         char    PHONMIN[11];
         char    PARAANZ[11];
         char    PARAMIN[11];
         char    SERAANZ[11];
         char    SERAMIN[11];
         char    ANZ_DD[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFSTATUS_BES [] =
 {
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
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFSTATUS_BES [] =
 {
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
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFSTATUS
 {
  public:

  AUFSTATUS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFSTATUS_BES, AUFSTATUS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFSTATUS_BES, AUFSTATUS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFSTATUS_BES, AUFSTATUS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFSTATUS()
  {
   ::buf_default((void *)&s, AUFSTATUS_BES, AUFSTATUS_ANZ);
  }
 };
#endif

#define AUFSTATUS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ANZ_ER INTEGER           ,\
         ANZ_BF INTEGER           ,\
         ANZ_FA INTEGER           ,\
         ANZ_ZU INTEGER           ,\
         ANZ_IK INTEGER           ,\
         ANZ_GD INTEGER           ,\
         ANZ_ST INTEGER           ,\
         FAKTUR_ZEILEN INTEGER           ,\
         FAKTUR_WERT INTEGER           ,\
         WERT_AND_NL INTEGER           ,\
         ANZ_WANNEN INTEGER           ,\
         FEHLER INTEGER           ,\
         ANZ_IE INTEGER           ,\
         ANZ_IAEN INTEGER           ,\
         ANZ_UNBEKANNT INTEGER           ,\
         PHONANZ INTEGER           ,\
         PHONMIN INTEGER           ,\
         PARAANZ INTEGER           ,\
         PARAMIN INTEGER           ,\
         SERAANZ INTEGER           ,\
         SERAMIN INTEGER           ,\
         ANZ_DD INTEGER             ) EXTENT SIZE 1668 LOCK MODE ROW;

#define AUFSTATUS_CREATE_INDEX(yyy,xxx) \

#define AUFSTATUS_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFSTPLAN_ANRUFART             2
 #define L_AUFSTPLAN_IDFNR                11
 #define L_AUFSTPLAN_RUFZEITGEAENDERT     11


 #define L_AUFSTPLAN_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFSTPLAN_ANZ (int) ( sizeof(AUFSTPLAN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFSTPLAN sizeof(struct AUFSTPLAN)


 #define AUFSTPLAN_H

 #define AUFSTPLAN_LISTE \
            TAGPLAN.ANRUFART, \
            TAGPLANEREIGNIS.IDFNR, \
            TAGPLANEREIGNIS.RUFZEITGEAENDERT
 #define AUFSTPLAN_PLISTE \
            "TAGPLAN.ANRUFART," \
            "TAGPLANEREIGNIS.IDFNR," \
            "TAGPLANEREIGNIS.RUFZEITGEAENDERT "

 #define AUFSTPLAN_PELISTE \
            "ANRUFART," \
            "IDFNR," \
            "RUFZEITGEAENDERT "

 #define AUFSTPLAN_UPDLISTE \
            "ANRUFART=?," \
            "IDFNR=?," \
            "RUFZEITGEAENDERT=? "

 #define AUFSTPLANANRUFART                      0
 #define AUFSTPLANIDFNR                         1
 #define AUFSTPLANRUFZEITGEAENDERT              2

 #define AUFSTPLAN_ZEIGER(xxx) \
            :xxx->ANRUFART,\
            :xxx->IDFNR,\
            :xxx->RUFZEITGEAENDERT

 #define AUFSTPLAN_UPDATE(xxx) \
            ANRUFART = :xxx->ANRUFART,\
            IDFNR = :xxx->IDFNR,\
            RUFZEITGEAENDERT = :xxx->RUFZEITGEAENDERT

 #define LS_AUFSTPLAN_ANRUFART             3
 #define LS_AUFSTPLAN_IDFNR                11
 #define LS_AUFSTPLAN_RUFZEITGEAENDERT     11
 #define LS_AUFSTPLAN_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFSTPLAN {
         char    ANRUFART[2 + 1];
         long    IDFNR;
         long    RUFZEITGEAENDERT;
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFSTPLAN {
         char    ANRUFART[2 + 1];
         long    IDFNR;
         long    RUFZEITGEAENDERT;
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFSTPLAN {
         short  ANRUFART;
         short  IDFNR;
         short  RUFZEITGEAENDERT;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFSTPLAN {
         char    ANRUFART[2 + 1];
         char    IDFNR[11];
         char    RUFZEITGEAENDERT[11];
         char    FETCH_REL[11];
       };

 struct O_AUFSTPLAN {
         char    ANRUFART[2];
         char    IDFNR[11];
         char    RUFZEITGEAENDERT[11];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFSTPLAN_BES [] =
 {
     { TYP_C ,    2 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFSTPLAN_BES [] =
 {
     { TYP_C,    2 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFSTPLAN
 {
  public:

  AUFSTPLAN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFSTPLAN_BES, AUFSTPLAN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFSTPLAN_BES, AUFSTPLAN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFSTPLAN_BES, AUFSTPLAN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFSTPLAN()
  {
   ::buf_default((void *)&s, AUFSTPLAN_BES, AUFSTPLAN_ANZ);
  }
 };
#endif

#define AUFSTPLAN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ANRUFART CHAR(2)           ,\
         IDFNR INTEGER           ,\
         RUFZEITGEAENDERT INTEGER           ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 22 LOCK MODE ROW;

#define AUFSTPLAN_CREATE_INDEX(yyy,xxx) \

#define AUFSTPLAN_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFTEXTE_BEMERKUNGSART        6
 #define L_AUFTEXTE_BEMERKUNGSNR         6
 #define L_AUFTEXTE_BEMERKUNGEN          240


 #define L_AUFTEXTE_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFTEXTE_ANZ (int) ( sizeof(AUFTEXTE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFTEXTE sizeof(struct AUFTEXTE)


 #define AUFTEXTE_H

 #define AUFTEXTE_LISTE \
            KDAUFTRAGBEM.BEMERKUNGSART, \
            KDAUFTRAGBEM.BEMERKUNGSNR, \
            KDAUFTRAGBEM.BEMERKUNGEN
 #define AUFTEXTE_PLISTE \
            "KDAUFTRAGBEM.BEMERKUNGSART," \
            "KDAUFTRAGBEM.BEMERKUNGSNR," \
            "KDAUFTRAGBEM.BEMERKUNGEN "

 #define AUFTEXTE_PELISTE \
            "BEMERKUNGSART," \
            "BEMERKUNGSNR," \
            "BEMERKUNGEN "

 #define AUFTEXTE_UPDLISTE \
            "BEMERKUNGSART=?," \
            "BEMERKUNGSNR=?," \
            "BEMERKUNGEN=? "

 #define AUFTEXTEBEMERKUNGSART                 0
 #define AUFTEXTEBEMERKUNGSNR                  1
 #define AUFTEXTEBEMERKUNGEN                   2

 #define AUFTEXTE_ZEIGER(xxx) \
            :xxx->BEMERKUNGSART,\
            :xxx->BEMERKUNGSNR,\
            :xxx->BEMERKUNGEN

 #define AUFTEXTE_UPDATE(xxx) \
            BEMERKUNGSART = :xxx->BEMERKUNGSART,\
            BEMERKUNGSNR = :xxx->BEMERKUNGSNR,\
            BEMERKUNGEN = :xxx->BEMERKUNGEN

 #define LS_AUFTEXTE_BEMERKUNGSART        7
 #define LS_AUFTEXTE_BEMERKUNGSNR         7
 #define LS_AUFTEXTE_BEMERKUNGEN          241
 #define LS_AUFTEXTE_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFTEXTE {
         short   BEMERKUNGSART;
         short   BEMERKUNGSNR;
         char    BEMERKUNGEN[240 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFTEXTE {
         short   BEMERKUNGSART;
         short   BEMERKUNGSNR;
         char    BEMERKUNGEN[240 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFTEXTE {
         short  BEMERKUNGSART;
         short  BEMERKUNGSNR;
         short  BEMERKUNGEN;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFTEXTE {
         char    BEMERKUNGSART[7];
         char    BEMERKUNGSNR[7];
         char    BEMERKUNGEN[240 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFTEXTE {
         char    BEMERKUNGSART[7];
         char    BEMERKUNGSNR[7];
         char    BEMERKUNGEN[240];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFTEXTE_BES [] =
 {
     { TYP_S ,    6 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_C ,  240 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFTEXTE_BES [] =
 {
     { TYP_S,    5 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,  240 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFTEXTE
 {
  public:

  AUFTEXTE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFTEXTE_BES, AUFTEXTE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFTEXTE_BES, AUFTEXTE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFTEXTE_BES, AUFTEXTE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFTEXTE()
  {
   ::buf_default((void *)&s, AUFTEXTE_BES, AUFTEXTE_ANZ);
  }
 };
#endif

#define AUFTEXTE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         BEMERKUNGSART SMALLINT          ,\
         BEMERKUNGSNR SMALLINT          ,\
         BEMERKUNGEN VARCHAR(240)      ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 9 LOCK MODE ROW;

#define AUFTEXTE_CREATE_INDEX(yyy,xxx) \

#define AUFTEXTE_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFTRAG_KDAUFTRAGNR          11
 #define L_AUFTRAG_KDAUFTRAGSTAT        16
 #define L_AUFTRAG_IDFNR                11
 #define L_AUFTRAG_TOURID               6
 #define L_AUFTRAG_KDAUFTRAGART         2
 #define L_AUFTRAG_KOART                1
 #define L_AUFTRAG_BUCHART              1
 #define L_AUFTRAG_WERTAUFTRAG          9
 #define N_AUFTRAG_WERTAUFTRAG          2
 #define L_AUFTRAG_WERTLIEFERUNG        9
 #define N_AUFTRAG_WERTLIEFERUNG        2
 #define L_AUFTRAG_WERTZEILEN           9
 #define N_AUFTRAG_WERTZEILEN           2
 #define L_AUFTRAG_ANZPOS               11
 #define L_AUFTRAG_STATUS               11
 #define L_AUFTRAG_VALUTAMONATE         11
 #define L_AUFTRAG_BEMERKUNGEN          240
 #define L_AUFTRAG_NAMEAPO              40
 #define L_AUFTRAG_GERAETNAME           8
 #define L_AUFTRAG_ANZPOSOB             11
 #define L_AUFTRAG_ANZPOSDAFUE          11
 #define L_AUFTRAG_APOENDZEIT           8
 #define L_AUFTRAG_FEHLER               11
 #define L_AUFTRAG_KZKDKLASSE           3
 #define L_AUFTRAG_ANZDEFEKTUB          11
 #define L_AUFTRAG_USERNAME             8
 #define L_AUFTRAG_DAFUEART             1
 #define L_AUFTRAG_UID                  11
 #define L_AUFTRAG_RECHNUNGNR           11
 #define L_AUFTRAG_KZDEFOFLOW           1
 #define L_AUFTRAG_KUNDENNR             11
 #define L_AUFTRAG_VERTRIEBSZENTRUMNR   7
 #define L_AUFTRAG_KDAUFTRAGNRFILIALE   11
 #define L_AUFTRAG_SENDESTATUS          7
 #define L_AUFTRAG_DATUMVALUTA          11
 #define L_AUFTRAG_BATCHSCHREIBEN       11
 #define L_AUFTRAG_ZUGRUND              16
 #define L_AUFTRAG_EILSPERRE            1
 #define L_AUFTRAG_NACHLIEFERTYP        1
 #define L_AUFTRAG_DATUMAUSLIEFERUNG    11
 #define L_AUFTRAG_SUB_ORDER_TYPE       3
 #define L_AUFTRAG_KZKDKK               1
 #define L_AUFTRAG_TENDERNO             11
 #define L_AUFTRAG_BALANCE              11
 #define N_AUFTRAG_BALANCE              2
 #define L_AUFTRAG_BALANCE2             11
 #define N_AUFTRAG_BALANCE2             2
 #define L_AUFTRAG_DATUMBTM             11
 #define L_AUFTRAG_BTMFORMULARNR        10
 #define L_AUFTRAG_KZSPRACHE            3
 #define L_AUFTRAG_WERTNETTO            9
 #define N_AUFTRAG_WERTNETTO            2
 #define L_AUFTRAG_WERTRABATT           9
 #define N_AUFTRAG_WERTRABATT           2
 #define L_AUFTRAG_SKDRETAILPERMIT      1
 #define L_AUFTRAG_WERTNETTO_FV         9
 #define N_AUFTRAG_WERTNETTO_FV         2
 #define L_AUFTRAG_WERTTAX_FV           9
 #define N_AUFTRAG_WERTTAX_FV           2
 #define L_AUFTRAG_WERTNETTO_KK         9
 #define N_AUFTRAG_WERTNETTO_KK         2
 #define L_AUFTRAG_WERTTAX_KK           9
 #define N_AUFTRAG_WERTTAX_KK           2
 #define L_AUFTRAG_WERTNETTO_EH         9
 #define N_AUFTRAG_WERTNETTO_EH         2
 #define L_AUFTRAG_WERTTAX_EH           9
 #define N_AUFTRAG_WERTTAX_EH           2
 #define L_AUFTRAG_PAYMENTDATE          11
 #define L_AUFTRAG_PAYMENTTYPE          1
 #define L_AUFTRAG_NORABATTKONTO        1
 #define L_AUFTRAG_WERTEXCLUSIVE        9
 #define N_AUFTRAG_WERTEXCLUSIVE        2
 #define L_AUFTRAG_SETORDERLABEL        1
 #define L_AUFTRAG_NOMOREPOS            1
 #define L_AUFTRAG_QUOTAINHERITANCE     1
 #define L_AUFTRAG_RELATIONNO           11
 #define L_AUFTRAG_DELIVERYDATE         11
 #define L_AUFTRAG_SAP_REFERENCENO      10

 #define L_AUFTRAG_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFTRAG_ANZ (int) ( sizeof(AUFTRAG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFTRAG sizeof(struct AUFTRAG)


 #define AUFTRAG_H

 #define AUFTRAG_LISTE \
            KDAUFTRAG.KDAUFTRAGNR, \
            KDAUFTRAG.KDAUFTRAGSTAT, \
            KDAUFTRAG.IDFNR, \
            KDAUFTRAG.TOURID, \
            KDAUFTRAG.KDAUFTRAGART, \
            KDAUFTRAG.KOART, \
            KDAUFTRAG.BUCHART, \
            KDAUFTRAG.WERTAUFTRAG, \
            KDAUFTRAG.WERTLIEFERUNG, \
            KDAUFTRAG.WERTZEILEN, \
            KDAUFTRAG.ANZPOS, \
            AADUMMY.STATUS, \
            AADUMMY.VALUTAMONATE, \
            KDAUFTRAG.BEMERKUNGEN, \
            KUNDE.NAMEAPO, \
            KDAUFTRAG.GERAETNAME, \
            KDAUFTRAG.ANZPOSOB, \
            KDAUFTRAG.ANZPOSDAFUE, \
            AADUMMY.APOENDZEIT, \
            AADUMMY.FEHLER, \
            KUNDE.KZKDKLASSE, \
            AADUMMY.ANZDEFEKTUB, \
            PASSWD.USERNAME, \
            AADUMMY.DAFUEART, \
            PASSWD.UID, \
            KDAUFTRAG.RECHNUNGNR, \
            AADUMMY.KZDEFOFLOW, \
            KDAUFTRAG.KUNDENNR, \
            KDAUFTRAG.VERTRIEBSZENTRUMNR, \
            KDAUFTRAG.KDAUFTRAGNRFILIALE, \
            KDAUFTRAG.SENDESTATUS, \
            KDAUFTRAG.DATUMVALUTA, \
            KDAUFTRAG.BATCHSCHREIBEN, \
            KDAUFTRAG.ZUGRUND, \
            KUNDE.EILSPERRE, \
            KUNDE.NACHLIEFERTYP, \
            KDAUFTRAG.DATUMAUSLIEFERUNG, \
            KDAUFTRAG.SUB_ORDER_TYPE, \
            AADUMMY.KZKDKK, \
            KDAUFTRAG.TENDERNO, \
            CSTDISCACC.BALANCE, \
            CSTDISCACC.BALANCE2, \
            KDAUFTRAG.DATUMBTM, \
            KDAUFTRAG.BTMFORMULARNR, \
            KUNDE.KZSPRACHE, \
            KDAUFTRAG.WERTNETTO, \
            KDAUFTRAG.WERTRABATT, \
            KUNDESCHALTER.SKDRETAILPERMIT, \
            AADUMMY.WERTNETTO_FV, \
            AADUMMY.WERTTAX_FV, \
            AADUMMY.WERTNETTO_KK, \
            AADUMMY.WERTTAX_KK, \
            AADUMMY.WERTNETTO_EH, \
            AADUMMY.WERTTAX_EH, \
            KDAUFTRAG.PAYMENTDATE, \
            KDAUFTRAG.PAYMENTTYPE, \
            AADUMMY.NORABATTKONTO, \
            AADUMMY.WERTEXCLUSIVE, \
            AADUMMY.SETORDERLABEL, \
            AADUMMY.NOMOREPOS, \
            AADUMMY.QUOTAINHERITANCE, \
            OREDERRELATIONNO.RELATIONNO, \
            KDAUFTRAG.DELIVERYDATE, \
            AADUMMY.SAP_REFERENCENO

 #define AUFTRAG_PLISTE \
            "KDAUFTRAG.KDAUFTRAGNR," \
            "KDAUFTRAG.KDAUFTRAGSTAT," \
            "KDAUFTRAG.IDFNR," \
            "KDAUFTRAG.TOURID," \
            "KDAUFTRAG.KDAUFTRAGART," \
            "KDAUFTRAG.KOART," \
            "KDAUFTRAG.BUCHART," \
            "KDAUFTRAG.WERTAUFTRAG," \
            "KDAUFTRAG.WERTLIEFERUNG," \
            "KDAUFTRAG.WERTZEILEN," \
            "KDAUFTRAG.ANZPOS," \
            "AADUMMY.STATUS," \
            "AADUMMY.VALUTAMONATE," \
            "KDAUFTRAG.BEMERKUNGEN," \
            "KUNDE.NAMEAPO," \
            "KDAUFTRAG.GERAETNAME," \
            "KDAUFTRAG.ANZPOSOB," \
            "KDAUFTRAG.ANZPOSDAFUE," \
            "AADUMMY.APOENDZEIT," \
            "AADUMMY.FEHLER," \
            "KUNDE.KZKDKLASSE," \
            "AADUMMY.ANZDEFEKTUB," \
            "PASSWD.USERNAME," \
            "AADUMMY.DAFUEART," \
            "PASSWD.UID," \
            "KDAUFTRAG.RECHNUNGNR," \
            "AADUMMY.KZDEFOFLOW," \
            "KDAUFTRAG.KUNDENNR," \
            "KDAUFTRAG.VERTRIEBSZENTRUMNR," \
            "KDAUFTRAG.KDAUFTRAGNRFILIALE," \
            "KDAUFTRAG.SENDESTATUS," \
            "KDAUFTRAG.DATUMVALUTA," \
            "KDAUFTRAG.BATCHSCHREIBEN," \
            "KDAUFTRAG.ZUGRUND," \
            "KUNDE.EILSPERRE," \
            "KUNDE.NACHLIEFERTYP," \
            "KDAUFTRAG.DATUMAUSLIEFERUNG," \
            "KDAUFTRAG.SUB_ORDER_TYPE," \
            "AADUMMY.KZKDKK," \
            "KDAUFTRAG.TENDERNO," \
            "CSTDISCACC.BALANCE," \
            "CSTDISCACC.BALANCE2," \
            "KDAUFTRAG.DATUMBTM," \
            "KDAUFTRAG.BTMFORMULARNR," \
            "KUNDE.KZSPRACHE," \
            "KDAUFTRAG.WERTNETTO," \
            "KDAUFTRAG.WERTRABATT," \
            "KUNDESCHALTER.SKDRETAILPERMIT," \
            "AADUMMY.WERTNETTO_FV, " \
            "AADUMMY.WERTTAX_FV, " \
            "AADUMMY.WERTNETTO_KK, " \
            "AADUMMY.WERTTAX_KK, " \
            "AADUMMY.WERTNETTO_EH, " \
            "AADUMMY.WERTTAX_EH, " \
            "KDAUFTRAG.PAYMENTDATE, " \
            "KDAUFTRAG.PAYMENTTYPE, " \
            "AADUMMY.NORABATTKONTO, " \
            "AADUMMY.WERTEXCLUSIVE, " \
            "AADUMMY.SETORDERLABEL, " \
            "AADUMMY.NOMOREPOS, " \
            "AADUMMY.QUOTAINHERITANCE, " \
            "OREDERRELATIONNO.RELATIONNO, " \
            "KDAUFTRAG.DELIVERYDATE, " \
            "AADUMMY.SAP_REFERENCENO"

 #define AUFTRAG_PELISTE \
            "KDAUFTRAGNR," \
            "KDAUFTRAGSTAT," \
            "IDFNR," \
            "TOURID," \
            "KDAUFTRAGART," \
            "KOART," \
            "BUCHART," \
            "WERTAUFTRAG," \
            "WERTLIEFERUNG," \
            "WERTZEILEN," \
            "ANZPOS," \
            "STATUS," \
            "VALUTAMONATE," \
            "BEMERKUNGEN," \
            "NAMEAPO," \
            "GERAETNAME," \
            "ANZPOSOB," \
            "ANZPOSDAFUE," \
            "APOENDZEIT," \
            "FEHLER," \
            "KZKDKLASSE," \
            "ANZDEFEKTUB," \
            "USERNAME," \
            "DAFUEART," \
            "UID," \
            "RECHNUNGNR," \
            "KZDEFOFLOW," \
            "KUNDENNR," \
            "VERTRIEBSZENTRUMNR," \
            "KDAUFTRAGNRFILIALE," \
            "SENDESTATUS," \
            "DATUMVALUTA," \
            "BATCHSCHREIBEN," \
            "ZUGRUND," \
            "EILSPERRE," \
            "NACHLIEFERTYP," \
            "DATUMAUSLIEFERUNG," \
            "SUB_ORDER_TYPE," \
            "KZKDKK," \
            "TENDERNO," \
            "BALANCE," \
            "BALANCE2," \
            "DATUMBTM," \
            "BTMFORMULARNR," \
            "KZSPRACHE," \
            "WERTNETTO," \
            "WERTRABATT," \
            "SKDRETAILPERMIT," \
            "WERTNETTO_FV, " \
            "WERTTAX_FV, " \
            "WERTNETTO_KK, " \
            "WERTTAX_KK, " \
            "WERTNETTO_EH, " \
            "WERTTAX_EH, " \
            "PAYMENTDATE, " \
            "PAYMENTTYPE, " \
            "NORABATTKONTO, " \
            "WERTEXCLUSIVE, " \
            "SETORDERLABEL, " \
            "NOMOREPOS, " \
            "QUOTAINHERITANCE, " \
            "RELATIONNO, " \
            "DELIVERYDATE, " \
            "SAP_REFERENCENO"

 #define AUFTRAG_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "KDAUFTRAGSTAT=?," \
            "IDFNR=?," \
            "TOURID=?," \
            "KDAUFTRAGART=?," \
            "KOART=?," \
            "BUCHART=?," \
            "WERTAUFTRAG=?," \
            "WERTLIEFERUNG=?," \
            "WERTZEILEN=?," \
            "ANZPOS=?," \
            "STATUS=?," \
            "VALUTAMONATE=?," \
            "BEMERKUNGEN=?," \
            "NAMEAPO=?," \
            "GERAETNAME=?," \
            "ANZPOSOB=?," \
            "ANZPOSDAFUE=?," \
            "APOENDZEIT=?," \
            "FEHLER=?," \
            "KZKDKLASSE=?," \
            "ANZDEFEKTUB=?," \
            "USERNAME=?," \
            "DAFUEART=?," \
            "UID=?," \
            "RECHNUNGNR=?," \
            "KZDEFOFLOW=?," \
            "KUNDENNR=?," \
            "VERTRIEBSZENTRUMNR=?," \
            "KDAUFTRAGNRFILIALE=?," \
            "SENDESTATUS=?," \
            "DATUMVALUTA=?," \
            "BATCHSCHREIBEN=?," \
            "ZUGRUND=?," \
            "EILSPERRE=?," \
            "NACHLIEFERTYP=?," \
            "DATUMAUSLIEFERUNG=?," \
            "SUB_ORDER_TYPE=?," \
            "KZKDKK=?," \
            "TENDERNO=?," \
            "BALANCE=?," \
            "BALANCE2=?," \
            "DATUMBTM=?," \
            "BTMFORMULARNR=?," \
            "KZSPRACHE=?," \
            "WERTNETTO=?," \
            "WERTRABATT=?," \
            "SKDRETAILPERMIT=?, " \
            "WERTNETTO_FV=?, " \
            "WERTTAX_FV=?, " \
            "WERTNETTO_KK=?, " \
            "WERTTAX_KK=?, " \
            "WERTNETTO_EH=?, " \
            "WERTTAX_EH=?, " \
            "PAYMENTDATE=?, " \
            "PAYMENTTYPE=?, " \
            "NORABATTKONTO=?, " \
            "WERTEXCLUSIVE=?, " \
            "SETORDERLABEL=?, " \
            "NOMOREPOS=?," \
            "QUOTAINHERITANCE=?," \
            "RELATIONNO=?," \
            "DELIVERYDATE=?, " \
            "SAP_REFERENCENO=?"

 #define AUFTRAGKDAUFTRAGNR                   0
 #define AUFTRAGKDAUFTRAGSTAT                 1
 #define AUFTRAGIDFNR                         2
 #define AUFTRAGTOURID                        3
 #define AUFTRAGKDAUFTRAGART                  4
 #define AUFTRAGKOART                         5
 #define AUFTRAGBUCHART                       6
 #define AUFTRAGWERTAUFTRAG                   7
 #define AUFTRAGWERTLIEFERUNG                 8
 #define AUFTRAGWERTZEILEN                    9
 #define AUFTRAGANZPOS                        10
 #define AUFTRAGSTATUS                        11
 #define AUFTRAGVALUTAMONATE                  12
 #define AUFTRAGBEMERKUNGEN                   13
 #define AUFTRAGNAMEAPO                       14
 #define AUFTRAGGERAETNAME                    15
 #define AUFTRAGANZPOSOB                      16
 #define AUFTRAGANZPOSDAFUE                   17
 #define AUFTRAGAPOENDZEIT                    18
 #define AUFTRAGFEHLER                        19
 #define AUFTRAGKZKDKLASSE                    20
 #define AUFTRAGANZDEFEKTUB                   21
 #define AUFTRAGUSERNAME                      22
 #define AUFTRAGDAFUEART                      23
 #define AUFTRAGUID                           24
 #define AUFTRAGRECHNUNGNR                    25
 #define AUFTRAGKZDEFOFLOW                    26
 #define AUFTRAGKUNDENNR                      27
 #define AUFTRAGVERTRIEBSZENTRUMNR            28
 #define AUFTRAGKDAUFTRAGNRFILIALE            29
 #define AUFTRAGSENDESTATUS                   30
 #define AUFTRAGDATUMVALUTA                   31
 #define AUFTRAGBATCHSCHREIBEN                32
 #define AUFTRAGZUGRUND                       33
 #define AUFTRAGEILSPERRE                     34
 #define AUFTRAGNACHLIEFERTYP                 35
 #define AUFTRAGDATUMAUSLIEFERUNG             36
 #define AUFTRAGSUB_ORDER_TYPE                37
 #define AUFTRAGKZKDKK                        38
 #define AUFTRAGTENDERNO                      39
 #define AUFTRAGBALANCE                       40
 #define AUFTRAGBALANCE2                      41
 #define AUFTRAGDATUMBTM                      42
 #define AUFTRAGBTMFORMULARNR                 43
 #define AUFTRAGKZSPRACHE                     44
 #define AUFTRAGWERTNETTO                     45
 #define AUFTRAGWERTRABATT                    46
 #define AUFTRAGSKDRETAILPERMIT               47
 #define AUFTRAGWERTNETTO_FV                  48
 #define AUFTRAGWERTTAX_FV                    49
 #define AUFTRAGWERTNETTO_KK                  50
 #define AUFTRAGWERTTAX_KK                    51
 #define AUFTRAGWERTNETTO_EH                  52
 #define AUFTRAGWERTTAX_EH                    53
 #define AUFTRAGPAYMENTDATE                   54
 #define AUFTRAGPAYMENTTYPE                   55
 #define AUFTRAGNORABATTKONTO                 56
 #define AUFTRAGWERTEXCLUSIVE                 57
 #define AUFTRAGSETORDERLABEL                 58
 #define AUFTRAGNOMOREPOS                     59
 #define AUFTRAGQUOTAINHERITANCE              60
 #define AUFTRAGRELATIONNO                    61
 #define AUFTRAGDELIVERYDATE                  62
 #define AUFTRAGSAP_REFERENCENO               63

 #define AUFTRAG_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR, \
            :xxx->KDAUFTRAGSTAT, \
            :xxx->IDFNR, \
            :xxx->TOURID, \
            :xxx->KDAUFTRAGART, \
            :xxx->KOART, \
            :xxx->BUCHART, \
            :xxx->WERTAUFTRAG, \
            :xxx->WERTLIEFERUNG, \
            :xxx->WERTZEILEN, \
            :xxx->ANZPOS, \
            :xxx->STATUS, \
            :xxx->VALUTAMONATE, \
            :xxx->BEMERKUNGEN, \
            :xxx->NAMEAPO, \
            :xxx->GERAETNAME, \
            :xxx->ANZPOSOB, \
            :xxx->ANZPOSDAFUE, \
            :xxx->APOENDZEIT, \
            :xxx->FEHLER, \
            :xxx->KZKDKLASSE, \
            :xxx->ANZDEFEKTUB, \
            :xxx->USERNAME, \
            :xxx->DAFUEART, \
            :xxx->UID, \
            :xxx->RECHNUNGNR, \
            :xxx->KZDEFOFLOW, \
            :xxx->KUNDENNR, \
            :xxx->VERTRIEBSZENTRUMNR, \
            :xxx->KDAUFTRAGNRFILIALE, \
            :xxx->SENDESTATUS, \
            :xxx->DATUMVALUTA, \
            :xxx->BATCHSCHREIBEN, \
            :xxx->ZUGRUND, \
            :xxx->EILSPERRE, \
            :xxx->NACHLIEFERTYP, \
            :xxx->DATUMAUSLIEFERUNG, \
            :xxx->SUB_ORDER_TYPE, \
            :xxx->KZKDKK, \
            :xxx->TENDERNO, \
            :xxx->BALANCE, \
            :xxx->BALANCE2, \
            :xxx->DATUMBTM, \
            :xxx->BTMFORMULARNR, \
            :xxx->KZSPRACHE, \
            :xxx->WERTNETTO, \
            :xxx->WERTRABATT, \
            :xxx->SKDRETAILPERMIT, \
            :xxx->WERTNETTO_FV, \
            :xxx->WERTTAX_FV, \
            :xxx->WERTNETTO_KK, \
            :xxx->WERTTAX_KK, \
            :xxx->WERTNETTO_EH, \
            :xxx->WERTTAX_EH, \
            :xxx->PAYMENTDATE, \
            :xxx->PAYMENTTYPE, \
            :xxx->NORABATTKONTO, \
            :xxx->WERTEXCLUSIVE, \
            :xxx->SETORDERLABEL, \
            :xxx->NOMOREPOS, \
            :xxx->QUOTAINHERITANCE, \
            :xxx->RELATIONNO, \
            :xxx->DELIVERYDATE, \
            :xxx->SAP_REFERENCENO

 #define AUFTRAG_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR, \
            KDAUFTRAGSTAT = :xxx->KDAUFTRAGSTAT, \
            IDFNR = :xxx->IDFNR, \
            TOURID = :xxx->TOURID, \
            KDAUFTRAGART = :xxx->KDAUFTRAGART, \
            KOART = :xxx->KOART, \
            BUCHART = :xxx->BUCHART, \
            WERTAUFTRAG = :xxx->WERTAUFTRAG, \
            WERTLIEFERUNG = :xxx->WERTLIEFERUNG, \
            WERTZEILEN = :xxx->WERTZEILEN, \
            ANZPOS = :xxx->ANZPOS, \
            STATUS = :xxx->STATUS, \
            VALUTAMONATE = :xxx->VALUTAMONATE, \
            BEMERKUNGEN = :xxx->BEMERKUNGEN, \
            NAMEAPO = :xxx->NAMEAPO, \
            GERAETNAME = :xxx->GERAETNAME, \
            ANZPOSOB = :xxx->ANZPOSOB, \
            ANZPOSDAFUE = :xxx->ANZPOSDAFUE, \
            APOENDZEIT = :xxx->APOENDZEIT, \
            FEHLER = :xxx->FEHLER, \
            KZKDKLASSE = :xxx->KZKDKLASSE, \
            ANZDEFEKTUB = :xxx->ANZDEFEKTUB, \
            USERNAME = :xxx->USERNAME, \
            DAFUEART = :xxx->DAFUEART, \
            UID = :xxx->UID, \
            RECHNUNGNR = :xxx->RECHNUNGNR, \
            KZDEFOFLOW = :xxx->KZDEFOFLOW, \
            KUNDENNR = :xxx->KUNDENNR, \
            VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR, \
            KDAUFTRAGNRFILIALE = :xxx->KDAUFTRAGNRFILIALE, \
            SENDESTATUS = :xxx->SENDESTATUS, \
            DATUMVALUTA = :xxx->DATUMVALUTA, \
            BATCHSCHREIBEN = :xxx->BATCHSCHREIBEN, \
            ZUGRUND = :xxx->ZUGRUND, \
            EILSPERRE = :xxx->EILSPERRE, \
            NACHLIEFERTYP = :xxx->NACHLIEFERTYP, \
            DATUMAUSLIEFERUNG = :xxx->DATUMAUSLIEFERUNG, \
            SUB_ORDER_TYPE = :xxx->SUB_ORDER_TYPE, \
            KZKDKK = :xxx->KZKDKK, \
            TENDERNO = :xxx->TENDERNO, \
            BALANCE = :xxx->BALANCE, \
            BALANCE2 = :xxx->BALANCE2, \
            DATUMBTM = :xxx->DATUMBTM, \
            BTMFORMULARNR = :xxx->BTMFORMULARNR, \
            KZSPRACHE = :xxx->KZSPRACHE, \
            WERTNETTO = :xxx->WERTNETTO, \
            WERTRABATT = :xxx->WERTRABATT, \
            SKDRETAILPERMIT = :xxx->SKDRETAILPERMIT, \
            WERTNETTO_FV = :xxx->WERTNETTO_FV, \
            WERTTAX_FV = :xxx->WERTTAX_FV, \
            WERTNETTO_KK = :xxx->WERTNETTO_KK, \
            WERTTAX_KK = :xxx->WERTTAX_KK, \
            WERTNETTO_EH = :xxx->WERTNETTO_EH, \
            WERTTAX_EH = :xxx->WERTTAX_EH, \
            PAYMENTDATE = :xxx->PAYMENTDATE, \
            PAYMENTTYPE = :xxx->PAYMENTTYPE, \
            NORABATTKONTO = :xxx->NORABATTKONTO, \
            WERTEXCLUSIVE = :xxx->WERTEXCLUSIVE, \
            SETORDERLABEL = :xxx->SETORDERLABEL, \
            NOMOREPOS = :xxx->NOMOREPOS, \
            QUOTAINHERITANCE = :xxx->QUOTAINHERITANCE, \
            RELATIONNO = :xxx->RELATIONNO, \
            DELIVERYDATE = :xxx->DELIVERYDATE, \
            SAP_REFERENCENO =:xxx->SAP_REFERENCENO

 #define LS_AUFTRAG_KDAUFTRAGNR          11
 #define LS_AUFTRAG_KDAUFTRAGSTAT        17
 #define LS_AUFTRAG_IDFNR                11
 #define LS_AUFTRAG_TOURID               7
 #define LS_AUFTRAG_KDAUFTRAGART         3
 #define LS_AUFTRAG_KOART                2
 #define LS_AUFTRAG_BUCHART              2
 #define LS_AUFTRAG_WERTAUFTRAG          11
 #define LS_AUFTRAG_WERTLIEFERUNG        11
 #define LS_AUFTRAG_WERTZEILEN           11
 #define LS_AUFTRAG_ANZPOS               11
 #define LS_AUFTRAG_STATUS               11
 #define LS_AUFTRAG_VALUTAMONATE         11
 #define LS_AUFTRAG_BEMERKUNGEN          241
 #define LS_AUFTRAG_NAMEAPO              41
 #define LS_AUFTRAG_GERAETNAME           9
 #define LS_AUFTRAG_ANZPOSOB             11
 #define LS_AUFTRAG_ANZPOSDAFUE          11
 #define LS_AUFTRAG_APOENDZEIT           9
 #define LS_AUFTRAG_FEHLER               11
 #define LS_AUFTRAG_KZKDKLASSE           4
 #define LS_AUFTRAG_ANZDEFEKTUB          11
 #define LS_AUFTRAG_USERNAME             9
 #define LS_AUFTRAG_DAFUEART             2
 #define LS_AUFTRAG_UID                  11
 #define LS_AUFTRAG_RECHNUNGNR           11
 #define LS_AUFTRAG_KZDEFOFLOW           2
 #define LS_AUFTRAG_KUNDENNR             11
 #define LS_AUFTRAG_VERTRIEBSZENTRUMNR   7
 #define LS_AUFTRAG_KDAUFTRAGNRFILIALE   11
 #define LS_AUFTRAG_SENDESTATUS          7
 #define LS_AUFTRAG_DATUMVALUTA          11
 #define LS_AUFTRAG_BATCHSCHREIBEN       11
 #define LS_AUFTRAG_ZUGRUND              17
 #define LS_AUFTRAG_EILSPERRE            2
 #define LS_AUFTRAG_NACHLIEFERTYP        2
 #define LS_AUFTRAG_DATUMAUSLIEFERUNG    11
 #define LS_AUFTRAG_SUB_ORDER_TYPE       4
 #define LS_AUFTRAG_KZKDKK               2
 #define LS_AUFTRAG_TENDERNO             11
 #define LS_AUFTRAG_BALANCE              13
 #define LS_AUFTRAG_BALANCE2             13
 #define LS_AUFTRAG_DATUMBTM             11
 #define LS_AUFTRAG_BTMFORMULARNR        11
 #define LS_AUFTRAG_KZSPRACHE            3
 #define LS_AUFTRAG_WERTNETTO            11
 #define LS_AUFTRAG_WERTRABATT           11
 #define LS_AUFTRAG_SKDRETAILPERMIT      2
 #define LS_AUFTRAG_WERTNETTO_FV         11
 #define LS_AUFTRAG_WERTTAX_FV           11
 #define LS_AUFTRAG_WERTNETTO_KK         11
 #define LS_AUFTRAG_WERTTAX_KK           11
 #define LS_AUFTRAG_WERTNETTO_EH         11
 #define LS_AUFTRAG_WERTTAX_EH           11
 #define LS_AUFTRAG_PAYMENTDATE          11
 #define LS_AUFTRAG_PAYMENTTYPE          2
 #define LS_AUFTRAG_NORABATTKONTO        2
 #define LS_AUFTRAG_WERTEXCLUSIVE        11
 #define LS_AUFTRAG_SETORDERLABEL        2
 #define LS_AUFTRAG_NOMOREPOS            2
 #define LS_AUFTRAG_QUOTAINHERITANCE     2
 #define LS_AUFTRAG_RELATIONNO           11
 #define LS_AUFTRAG_DELIVERYDATE         11
 #define LS_AUFTRAG_SAP_REFERENCENO      11
 #define LS_AUFTRAG_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFTRAG {
         long    KDAUFTRAGNR;
         char    KDAUFTRAGSTAT[16 + 1];
         long    IDFNR;
         char    TOURID[6 + 1];
         char    KDAUFTRAGART[2 + 1];
         char    KOART[1 + 1];
         char    BUCHART[1 + 1];
         double  WERTAUFTRAG;
         double  WERTLIEFERUNG;
         double  WERTZEILEN;
         long    ANZPOS;
         long    STATUS;
         long    VALUTAMONATE;
         char    BEMERKUNGEN[240 + 1];
         char    NAMEAPO[40 + 1];
         char    GERAETNAME[8 + 1];
         long    ANZPOSOB;
         long    ANZPOSDAFUE;
         char    APOENDZEIT[8 + 1];
         long    FEHLER;
         char    KZKDKLASSE[3 + 1];
         long    ANZDEFEKTUB;
         char    USERNAME[8 + 1];
         char    DAFUEART[1 + 1];
         long    UID;
         long    RECHNUNGNR;
         char    KZDEFOFLOW[1 + 1];
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         long    KDAUFTRAGNRFILIALE;
         short   SENDESTATUS;
         long    DATUMVALUTA;
         long    BATCHSCHREIBEN;
         char    ZUGRUND[16 + 1];
         char    EILSPERRE[1 + 1];
         char    NACHLIEFERTYP[1 + 1];
         long    DATUMAUSLIEFERUNG;
         char    SUB_ORDER_TYPE[3 + 1];
         char    KZKDKK[1 + 1];
         long    TENDERNO;
         double  BALANCE;
         double  BALANCE2;
         long    DATUMBTM;
         char    BTMFORMULARNR[10 + 1];
         char    KZSPRACHE[2 + 1];
         double  WERTNETTO;
         double  WERTRABATT;
         char    SKDRETAILPERMIT[1 + 1];
         double  WERTNETTO_FV;
         double  WERTTAX_FV;
         double  WERTNETTO_KK;
         double  WERTTAX_KK;
         double  WERTNETTO_EH;
         double  WERTTAX_EH;
         long    PAYMENTDATE;
         char    PAYMENTTYPE[1 + 1];
         char    NORABATTKONTO[1 + 1];
         double  WERTEXCLUSIVE;
         char    SETORDERLABEL[1 + 1];
         char    NOMOREPOS[1 + 1];
         char    QUOTAINHERITANCE[1 + 1];
         long    RELATIONNO;
         long    DELIVERYDATE;
         char    SAP_REFERENCENO[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFTRAG {
         long    KDAUFTRAGNR;
         char    KDAUFTRAGSTAT[16 + 1];
         long    IDFNR;
         char    TOURID[6 + 1];
         char    KDAUFTRAGART[2 + 1];
         char    KOART;
         char    BUCHART;
         double  WERTAUFTRAG;
         double  WERTLIEFERUNG;
         double  WERTZEILEN;
         long    ANZPOS;
         long    STATUS;
         long    VALUTAMONATE;
         char    BEMERKUNGEN[240 + 1];
         char    NAMEAPO[40 + 1];
         char    GERAETNAME[8 + 1];
         long    ANZPOSOB;
         long    ANZPOSDAFUE;
         char    APOENDZEIT[8 + 1];
         long    FEHLER;
         char    KZKDKLASSE[3 + 1];
         long    ANZDEFEKTUB;
         char    USERNAME[8 + 1];
         char    DAFUEART;
         long    UID;
         long    RECHNUNGNR;
         char    KZDEFOFLOW;
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         long    KDAUFTRAGNRFILIALE;
         short   SENDESTATUS;
         long    DATUMVALUTA;
         long    BATCHSCHREIBEN;
         char    ZUGRUND[16 + 1];
         char    EILSPERRE;
         char    NACHLIEFERTYP;
         long    DATUMAUSLIEFERUNG;
         char    SUB_ORDER_TYPE[3 + 1];
         char    KZKDKK;
         long    TENDERNO;
         double  BALANCE;
         double  BALANCE2;
         long    DATUMBTM;
         char    BTMFORMULARNR[10 + 1];
         char    KZSPRACHE[2 + 1];
         double  WERTNETTO;
         double  WERTRABATT;
         char    SKDRETAILPERMIT;
         double  WERTNETTO_FV;
         double  WERTTAX_FV;
         double  WERTNETTO_KK;
         double  WERTTAX_KK;
         double  WERTNETTO_EH;
         double  WERTTAX_EH;
         long    PAYMENTDATE;
         char    PAYMENTTYPE;
         char    NORABATTKONTO;
         double  WERTEXCLUSIVE;
         char    SETORDERLABEL;
         char    NOMOREPOS;
         char    QUOTAINHERITANCE;
         long    RELATIONNO;
         long    DELIVERYDATE;
         char    SAP_REFERENCENO[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFTRAG {
         short  KDAUFTRAGNR;
         short  KDAUFTRAGSTAT;
         short  IDFNR;
         short  TOURID;
         short  KDAUFTRAGART;
         short  KOART;
         short  BUCHART;
         short  WERTAUFTRAG;
         short  WERTLIEFERUNG;
         short  WERTZEILEN;
         short  ANZPOS;
         short  STATUS;
         short  VALUTAMONATE;
         short  BEMERKUNGEN;
         short  NAMEAPO;
         short  GERAETNAME;
         short  ANZPOSOB;
         short  ANZPOSDAFUE;
         short  APOENDZEIT;
         short  FEHLER;
         short  KZKDKLASSE;
         short  ANZDEFEKTUB;
         short  USERNAME;
         short  DAFUEART;
         short  UID;
         short  RECHNUNGNR;
         short  KZDEFOFLOW;
         short  KUNDENNR;
         short  VERTRIEBSZENTRUMNR;
         short  KDAUFTRAGNRFILIALE;
         short  SENDESTATUS;
         short  DATUMVALUTA;
         short  BATCHSCHREIBEN;
         short  ZUGRUND;
         short  EILSPERRE;
         short  NACHLIEFERTYP;
         short  DATUMAUSLIEFERUNG;
         short  SUB_ORDER_TYPE;
         short  KZKDKK;
         short  TENDERNO;
         short  BALANCE;
         short  BALANCE2;
         short  DATUMBTM;
         short  BTMFORMULARNR;
         short  KZSPRACHE;
         short  WERTNETTO;
         short  WERTRABATT;
         short  SKDRETAILPERMIT;
         short  WERTNETTO_FV;
         short  WERTTAX_FV;
         short  WERTNETTO_KK;
         short  WERTTAX_KK;
         short  WERTNETTO_EH;
         short  WERTTAX_EH;
         short  PAYMENTDATE;
         short  PAYMENTTYPE;
         short  NORABATTKONTO;
         short  WERTEXCLUSIVE;
         short  SETORDERLABEL;
         short  NOMOREPOS;
         short  QUOTAINHERITANCE;
         short  RELATIONNO;
         short  DELIVERYDATE;
         short  SAP_REFERENCENO;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFTRAG {
         char    KDAUFTRAGNR[11];
         char    KDAUFTRAGSTAT[16 + 1];
         char    IDFNR[11];
         char    TOURID[6 + 1];
         char    KDAUFTRAGART[2 + 1];
         char    KOART[1 + 1];
         char    BUCHART[1 + 1];
         char    WERTAUFTRAG[9 + 2];
         char    WERTLIEFERUNG[9 + 2];
         char    WERTZEILEN[9 + 2];
         char    ANZPOS[11];
         char    STATUS[11];
         char    VALUTAMONATE[11];
         char    BEMERKUNGEN[240 + 1];
         char    NAMEAPO[40 + 1];
         char    GERAETNAME[8 + 1];
         char    ANZPOSOB[11];
         char    ANZPOSDAFUE[11];
         char    APOENDZEIT[8 + 1];
         char    FEHLER[11];
         char    KZKDKLASSE[3 + 1];
         char    ANZDEFEKTUB[11];
         char    USERNAME[8 + 1];
         char    DAFUEART[1 + 1];
         char    UID[11];
         char    RECHNUNGNR[11];
         char    KZDEFOFLOW[1 + 1];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7];
         char    KDAUFTRAGNRFILIALE[11];
         char    SENDESTATUS[7];
         char    DATUMVALUTA[11];
         char    BATCHSCHREIBEN[11];
         char    ZUGRUND[16 + 1];
         char    EILSPERRE[1 + 1];
         char    NACHLIEFERTYP[1 + 1];
         char    DATUMAUSLIEFERUNG[11];
         char    SUB_ORDER_TYPE[3 + 1];
         char    KZKDKK[1 + 1];
         char    TENDERNO[11];
         char    BALANCE[11 + 2];
         char    BALANCE2[11 + 2];
         char    DATUMBTM[11];
         char    BTMFORMULARNR[10 + 1];
         char    KZSPRACHE[2 + 1];
         char    WERTNETTO[9 + 2];
         char    WERTRABATT[9 + 2];
         char    SKDRETAILPERMIT[1 + 1];
         char    WERTNETTO_FV[9 + 2];
         char    WERTTAX_FV[9 + 2];
         char    WERTNETTO_KK[9 + 2];
         char    WERTTAX_KK[9 + 2];
         char    WERTNETTO_EH[9 + 2];
         char    WERTTAX_EH[9 + 2];
         char    PAYMENTDATE[11];
         char    PAYMENTTYPE[1 + 1];
         char    NORABATTKONTO[1 + 1];
         char    WERTEXCLUSIVE[9 + 2];
         char    SETORDERLABEL[1 + 1];
         char    NOMOREPOS[1 + 1];
         char    QUOTAINHERITANCE[1 + 1];
         char    RELATIONNO[11];
         char    DELIVERYDATE[11];
         char    SAP_REFERENCENO[10 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFTRAG {
         char    KDAUFTRAGNR[11];
         char    KDAUFTRAGSTAT[16];
         char    IDFNR[11];
         char    TOURID[6];
         char    KDAUFTRAGART[2];
         char    KOART[1];
         char    BUCHART[1];
         char    WERTAUFTRAG[9];
         char    WERTLIEFERUNG[9];
         char    WERTZEILEN[9];
         char    ANZPOS[11];
         char    STATUS[11];
         char    VALUTAMONATE[11];
         char    BEMERKUNGEN[240];
         char    NAMEAPO[40];
         char    GERAETNAME[8];
         char    ANZPOSOB[11];
         char    ANZPOSDAFUE[11];
         char    APOENDZEIT[8];
         char    FEHLER[11];
         char    KZKDKLASSE[3];
         char    ANZDEFEKTUB[11];
         char    USERNAME[8];
         char    DAFUEART[1];
         char    UID[11];
         char    RECHNUNGNR[11];
         char    KZDEFOFLOW[1];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7];
         char    KDAUFTRAGNRFILIALE[11];
         char    SENDESTATUS[7];
         char    DATUMVALUTA[11];
         char    BATCHSCHREIBEN[11];
         char    ZUGRUND[16];
         char    EILSPERRE[1];
         char    NACHLIEFERTYP[1];
         char    DATUMAUSLIEFERUNG[11];
         char    SUB_ORDER_TYPE[3];
         char    KZKDKK[1];
         char    TENDERNO[11];
         char    BALANCE[11];
         char    BALANCE2[11];
         char    DATUMBTM[11];
         char    BTMFORMULARNR[10 + 1];
         char    KZSPRACHE[2];
         char    WERTNETTO[9];
         char    WERTRABATT[9];
         char    SKDRETAILPERMIT[1];
         char    WERTNETTO_FV[9];
         char    WERTTAX_FV[9];
         char    WERTNETTO_KK[9];
         char    WERTTAX_KK[9];
         char    WERTNETTO_EH[9];
         char    WERTTAX_EH[9];
         char    PAYMENTDATE[11];
         char    PAYMENTTYPE[1];
         char    NORABATTKONTO[1];
         char    WERTEXCLUSIVE[9];
         char    SETORDERLABEL[1];
         char    NOMOREPOS[1];
         char    QUOTAINHERITANCE[1];
         char    RELATIONNO[11];
         char    DELIVERYDATE[11];
         char    SAP_REFERENCENO[10];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFTRAG_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   16 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    6 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,  240 ,   0 },
     { TYP_C ,   40 ,   0 },
     { TYP_C ,    8 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    8 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    3 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    8 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_S ,    6 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   16 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    3 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_D ,   11 ,   2 },
     { TYP_D ,   11 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   10 ,   0 },
     { TYP_C ,    2 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_C ,    1 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_D ,    9 ,   2 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_D ,    9 ,   2 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_C ,    1 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   10 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFTRAG_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,  240 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_S ,   5 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_S ,   5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L ,  11 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_D ,  11 ,   2 },
     { TYP_D ,  11 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_F,    1 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_D,    9 ,   2 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_D,    9 ,   2 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFTRAG
 {
  public:

  AUFTRAG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFTRAG_BES, AUFTRAG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFTRAG_BES, AUFTRAG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFTRAG_BES, AUFTRAG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFTRAG()
  {
   ::buf_default((void *)&s, AUFTRAG_BES, AUFTRAG_ANZ);
  }
 };
#endif

#define AUFTRAG_CREATE(xxx)  EXEC SQL CREATE TABLE xxx ( \
         KDAUFTRAGNR INTEGER, \
         KDAUFTRAGSTAT CHAR(16), \
         IDFNR INTEGER, \
         TOURID CHAR(6), \
         KDAUFTRAGART CHAR(2), \
         KOART CHAR(1), \
         BUCHART CHAR(1), \
         WERTAUFTRAG DECIMAL(9,2), \
         WERTLIEFERUNG DECIMAL(9,2), \
         WERTZEILEN DECIMAL(9,2), \
         ANZPOS INTEGER, \
         STATUS INTEGER, \
         VALUTAMONATE INTEGER, \
         BEMERKUNGEN VARCHAR(240,0), \
         NAMEAPO CHAR(40), \
         GERAETNAME CHAR(8), \
         ANZPOSOB INTEGER, \
         ANZPOSDAFUE INTEGER, \
         APOENDZEIT CHAR(8), \
         FEHLER INTEGER, \
         KZKDKLASSE CHAR(3), \
         ANZDEFEKTUB INTEGER, \
         USERNAME CHAR(8), \
         DAFUEART CHAR(1), \
         UID INTEGER, \
         RECHNUNGNR INTEGER, \
         KZDEFOFLOW CHAR(1), \
         KUNDENNR INTEGER, \
         VERTRIEBSZENTRUMNR SMALLINT, \
         KDAUFTRAGNRFILIALE INTEGER, \
         SENDESTATUS SMALLINT, \
         DATUMVALUTA INTEGER, \
         BATCHSCHREIBEN INTEGER, \
         ZUGRUND CHAR(16), \
         EILSPERRE CHAR(1), \
         NACHLIEFERTYP CHAR(1), \
         DATUMAUSLIEFERUNG INTEGER, \
         SUB_ORDER_TYPE CHAR(3), \
         KZKDKK CHAR(1), \
         TENDERNO INTEGER, \
         BALANCE decimal(11,2) default 0 not null, \
         BALANCE2 decimal(11,2) default 0 not null, \
         DATUMBTM INTEGER, \
         BTMFORMULARNR CHAR(10), \
         KZSPRACHE CHAR(2), \
         WERTNETTO DECIMAL(9,2), \
         WERTRABATT DECIMAL(9,2), \
         SKDRETAILPERMIT CHAR(1), \
         WERTNETTO_FV DECIMAL(9,2), \
         WERTTAX_FV DECIMAL(9,2), \
         WERTNETTO_KK DECIMAL(9,2), \
         WERTTAX_KK DECIMAL(9,2), \
         WERTNETTO_EH DECIMAL(9,2), \
         WERTTAX_EH DECIMAL(9,2), \
         PAYMENTDATE INTEGER, \
         PAYMENTTYPE CHAR(1), \
         NORABATTKONTO CHAR(1), \
         WERTEXCLUSIVE DECIMAL(9,2), \
         SETORDERLABEL CHAR(1), \
         NOMOREPOS CHAR(1), \
         QUOTAINHERITANCE CHAR(1), \
         RELATIONNO INTEGER, \
         DELIVERYDATE INTEGER, \
         SAP_REFERENCENO CHAR(10), \
         FETCH_REL INTEGER  ) EXTENT SIZE 1573 LOCK MODE ROW;

#define AUFTRAG_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGX         on yyy( KDAUFTRAGNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_303    on yyy( KDAUFTRAGSTAT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_304    on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDAUFTRAGTOURX     on yyy( TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_305    on yyy( GERAETNAME );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFTRAG_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGX        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_303   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_304   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDAUFTRAGTOURX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_305   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_AUFWANNEN_DATUM                11
 #define L_AUFWANNEN_KDAUFTRAGNR          11
 #define L_AUFWANNEN_POSNR                11
 #define L_AUFWANNEN_KOBEHAELTNR          11
 #define L_AUFWANNEN_LAGERFACHNR          10


 #define L_AUFWANNEN_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFWANNEN_ANZ (int) ( sizeof(AUFWANNEN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFWANNEN sizeof(struct AUFWANNEN)


 #define AUFWANNEN_H

 #define AUFWANNEN_LISTE \
            AADUMMY.DATUM, \
            KDAUFTRAGPOS.KDAUFTRAGNR, \
            KDAUFTRAGPOS.POSNR, \
            KDAUFTRAGPOS.KOBEHAELTNR, \
            KDAUFTRAGPOS.LAGERFACHNR
 #define AUFWANNEN_PLISTE \
            "AADUMMY.DATUM," \
            "KDAUFTRAGPOS.KDAUFTRAGNR," \
            "KDAUFTRAGPOS.POSNR," \
            "KDAUFTRAGPOS.KOBEHAELTNR," \
            "KDAUFTRAGPOS.LAGERFACHNR "

 #define AUFWANNEN_PELISTE \
            "DATUM," \
            "KDAUFTRAGNR," \
            "POSNR," \
            "KOBEHAELTNR," \
            "LAGERFACHNR "

 #define AUFWANNEN_UPDLISTE \
            "DATUM=?," \
            "KDAUFTRAGNR=?," \
            "POSNR=?," \
            "KOBEHAELTNR=?," \
            "LAGERFACHNR=? "

 #define AUFWANNENDATUM                         0
 #define AUFWANNENKDAUFTRAGNR                   1
 #define AUFWANNENPOSNR                         2
 #define AUFWANNENKOBEHAELTNR                   3
 #define AUFWANNENLAGERFACHNR                   4

 #define AUFWANNEN_ZEIGER(xxx) \
            :xxx->DATUM,\
            :xxx->KDAUFTRAGNR,\
            :xxx->POSNR,\
            :xxx->KOBEHAELTNR,\
            :xxx->LAGERFACHNR

 #define AUFWANNEN_UPDATE(xxx) \
            DATUM = :xxx->DATUM,\
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
            POSNR = :xxx->POSNR,\
            KOBEHAELTNR = :xxx->KOBEHAELTNR,\
            LAGERFACHNR = :xxx->LAGERFACHNR

 #define LS_AUFWANNEN_DATUM                11
 #define LS_AUFWANNEN_KDAUFTRAGNR          11
 #define LS_AUFWANNEN_POSNR                11
 #define LS_AUFWANNEN_KOBEHAELTNR          11
 #define LS_AUFWANNEN_LAGERFACHNR          11
 #define LS_AUFWANNEN_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFWANNEN {
         long    DATUM;
         long    KDAUFTRAGNR;
         long    POSNR;
         long    KOBEHAELTNR;
         char    LAGERFACHNR[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFWANNEN {
         long    DATUM;
         long    KDAUFTRAGNR;
         long    POSNR;
         long    KOBEHAELTNR;
         char    LAGERFACHNR[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFWANNEN {
         short  DATUM;
         short  KDAUFTRAGNR;
         short  POSNR;
         short  KOBEHAELTNR;
         short  LAGERFACHNR;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFWANNEN {
         char    DATUM[11];
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    KOBEHAELTNR[11];
         char    LAGERFACHNR[10 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUFWANNEN {
         char    DATUM[11];
         char    KDAUFTRAGNR[11];
         char    POSNR[11];
         char    KOBEHAELTNR[11];
         char    LAGERFACHNR[10];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFWANNEN_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_C ,   10 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFWANNEN_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFWANNEN
 {
  public:

  AUFWANNEN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFWANNEN_BES, AUFWANNEN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFWANNEN_BES, AUFWANNEN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFWANNEN_BES, AUFWANNEN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFWANNEN()
  {
   ::buf_default((void *)&s, AUFWANNEN_BES, AUFWANNEN_ANZ);
  }
 };
#endif

#define AUFWANNEN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         DATUM INTEGER           ,\
         KDAUFTRAGNR INTEGER           ,\
         POSNR INTEGER           ,\
         KOBEHAELTNR INTEGER           ,\
         LAGERFACHNR CHAR(10)          ,\
         FETCH_REL INTEGER  ) EXTENT SIZE 988 LOCK MODE ROW;

#define AUFWANNEN_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGPOSX      on yyy( KDAUFTRAGNR, POSNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFWANNEN_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGPOSX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFZLNSTAT_ZEIT_VON             11
 #define L_AUFZLNSTAT_ZEIT_BIS             11
 #define L_AUFZLNSTAT_ANZAHL               11
 #define L_AUFZLNSTAT_WERT                 11
 #define L_AUFZLNSTAT_ANZAHL_DAFUE         11
 #define L_AUFZLNSTAT_ANZAHL_ALPHA         11
 #define L_AUFZLNSTAT_ANZAHL_AUFTRAG       11
 #define L_AUFZLNSTAT_DATUM                11


 #define L_AUFZLNSTAT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFZLNSTAT_ANZ (int) ( sizeof(AUFZLNSTAT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFZLNSTAT sizeof(struct AUFZLNSTAT)


 #define AUFZLNSTAT_H

 #define AUFZLNSTAT_LISTE \
            AADUMMY.ZEIT_VON, \
            AADUMMY.ZEIT_BIS, \
            AADUMMY.ANZAHL, \
            AADUMMY.WERT, \
            AADUMMY.ANZAHL_DAFUE, \
            AADUMMY.ANZAHL_ALPHA, \
            AADUMMY.ANZAHL_AUFTRAG, \
            AADUMMY.DATUM
 #define AUFZLNSTAT_PLISTE \
            "AADUMMY.ZEIT_VON," \
            "AADUMMY.ZEIT_BIS," \
            "AADUMMY.ANZAHL," \
            "AADUMMY.WERT," \
            "AADUMMY.ANZAHL_DAFUE," \
            "AADUMMY.ANZAHL_ALPHA," \
            "AADUMMY.ANZAHL_AUFTRAG," \
            "AADUMMY.DATUM "

 #define AUFZLNSTAT_PELISTE \
            "ZEIT_VON," \
            "ZEIT_BIS," \
            "ANZAHL," \
            "WERT," \
            "ANZAHL_DAFUE," \
            "ANZAHL_ALPHA," \
            "ANZAHL_AUFTRAG," \
            "DATUM "

 #define AUFZLNSTAT_UPDLISTE \
            "ZEIT_VON=?," \
            "ZEIT_BIS=?," \
            "ANZAHL=?," \
            "WERT=?," \
            "ANZAHL_DAFUE=?," \
            "ANZAHL_ALPHA=?," \
            "ANZAHL_AUFTRAG=?," \
            "DATUM=? "

 #define AUFZLNSTATZEIT_VON                      0
 #define AUFZLNSTATZEIT_BIS                      1
 #define AUFZLNSTATANZAHL                        2
 #define AUFZLNSTATWERT                          3
 #define AUFZLNSTATANZAHL_DAFUE                  4
 #define AUFZLNSTATANZAHL_ALPHA                  5
 #define AUFZLNSTATANZAHL_AUFTRAG                6
 #define AUFZLNSTATDATUM                         7

 #define AUFZLNSTAT_ZEIGER(xxx) \
            :xxx->ZEIT_VON,\
            :xxx->ZEIT_BIS,\
            :xxx->ANZAHL,\
            :xxx->WERT,\
            :xxx->ANZAHL_DAFUE,\
            :xxx->ANZAHL_ALPHA,\
            :xxx->ANZAHL_AUFTRAG,\
            :xxx->DATUM

 #define AUFZLNSTAT_UPDATE(xxx) \
            ZEIT_VON = :xxx->ZEIT_VON,\
            ZEIT_BIS = :xxx->ZEIT_BIS,\
            ANZAHL = :xxx->ANZAHL,\
            WERT = :xxx->WERT,\
            ANZAHL_DAFUE = :xxx->ANZAHL_DAFUE,\
            ANZAHL_ALPHA = :xxx->ANZAHL_ALPHA,\
            ANZAHL_AUFTRAG = :xxx->ANZAHL_AUFTRAG,\
            DATUM = :xxx->DATUM

 #define LS_AUFZLNSTAT_ZEIT_VON             11
 #define LS_AUFZLNSTAT_ZEIT_BIS             11
 #define LS_AUFZLNSTAT_ANZAHL               11
 #define LS_AUFZLNSTAT_WERT                 11
 #define LS_AUFZLNSTAT_ANZAHL_DAFUE         11
 #define LS_AUFZLNSTAT_ANZAHL_ALPHA         11
 #define LS_AUFZLNSTAT_ANZAHL_AUFTRAG       11
 #define LS_AUFZLNSTAT_DATUM                11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFZLNSTAT {
         long    ZEIT_VON;
         long    ZEIT_BIS;
         long    ANZAHL;
         long    WERT;
         long    ANZAHL_DAFUE;
         long    ANZAHL_ALPHA;
         long    ANZAHL_AUFTRAG;
         long    DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFZLNSTAT {
         long    ZEIT_VON;
         long    ZEIT_BIS;
         long    ANZAHL;
         long    WERT;
         long    ANZAHL_DAFUE;
         long    ANZAHL_ALPHA;
         long    ANZAHL_AUFTRAG;
         long    DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFZLNSTAT {
         short  ZEIT_VON;
         short  ZEIT_BIS;
         short  ANZAHL;
         short  WERT;
         short  ANZAHL_DAFUE;
         short  ANZAHL_ALPHA;
         short  ANZAHL_AUFTRAG;
         short  DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFZLNSTAT {
         char    ZEIT_VON[11];
         char    ZEIT_BIS[11];
         char    ANZAHL[11];
         char    WERT[11];
         char    ANZAHL_DAFUE[11];
         char    ANZAHL_ALPHA[11];
         char    ANZAHL_AUFTRAG[11];
         char    DATUM[11];
       };

 struct O_AUFZLNSTAT {
         char    ZEIT_VON[11];
         char    ZEIT_BIS[11];
         char    ANZAHL[11];
         char    WERT[11];
         char    ANZAHL_DAFUE[11];
         char    ANZAHL_ALPHA[11];
         char    ANZAHL_AUFTRAG[11];
         char    DATUM[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFZLNSTAT_BES [] =
 {
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
     { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFZLNSTAT_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFZLNSTAT
 {
  public:

  AUFZLNSTAT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFZLNSTAT_BES, AUFZLNSTAT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFZLNSTAT_BES, AUFZLNSTAT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFZLNSTAT_BES, AUFZLNSTAT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFZLNSTAT()
  {
   ::buf_default((void *)&s, AUFZLNSTAT_BES, AUFZLNSTAT_ANZ);
  }
 };
#endif

#define AUFZLNSTAT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
         ZEIT_VON INTEGER           ,\
         ZEIT_BIS INTEGER           ,\
         ANZAHL INTEGER           ,\
         WERT INTEGER           ,\
         ANZAHL_DAFUE INTEGER           ,\
         ANZAHL_ALPHA INTEGER           ,\
         ANZAHL_AUFTRAG INTEGER           ,\
         DATUM INTEGER             ) EXTENT SIZE 636 LOCK MODE ROW;

#define AUFZLNSTAT_CREATE_INDEX(yyy,xxx) \

#define AUFZLNSTAT_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUSTINF_KDAUFTRAGNR          11
 #define L_AUSTINF_KDAUFTRAGSTAT        16
 #define L_AUSTINF_IDFNR                11
 #define L_AUSTINF_GERAETNAME           8
 #define L_AUSTINF_TOURID               6
 #define L_AUSTINF_ETAUFTRAGSCHALTER2   5
 #define L_AUSTINF_KDAUFTRAGART         2
 #define L_AUSTINF_KOART                1
 #define L_AUSTINF_BUCHART              1
 #define L_AUSTINF_ANZPOS               11
 #define L_AUSTINF_ANZPOSDAFUE          11
 #define L_AUSTINF_ZEITENDEAM           11
 #define L_AUSTINF_ZEITENDEPM           11
 #define L_AUSTINF_NAMEAPO              40
 #define L_AUSTINF_KZKDKLASSE           3
 #define L_AUSTINF_ANZPOSOB             11
 #define L_AUSTINF_ANZALPHATEXT         11
 #define L_AUSTINF_ORT                  30
 #define L_AUSTINF_ZEITERSTEGUELTIGK    11
 #define L_AUSTINF_DATUM                11
 #define L_AUSTINF_KUNDENNR             11
 #define L_AUSTINF_VERTRIEBSZENTRUMNR   7
 #define L_AUSTINF_KDAUFTRAGNRFILIALE   11
 #define L_AUSTINF_SENDESTATUS          7
 #define L_AUSTINF_ZUGRUND              16
 #define L_AUSTINF_DATUMAUSLIEFERUNG    11
 #define L_AUSTINF_RECHNUNGNR           11
 #define L_AUSTINF_SORTFIELD            20
 #define L_AUSTINF_BATCHSCHREIBEN       11
 #define L_AUSTINF_INVOICENUMBER        15
 #define L_AUSTINF_PAYMENTDATE          11
 #define L_AUSTINF_PAYMENTTYPE          1
 #define L_AUSTINF_ORDERLABEL           40
 #define L_AUSTINF_ORDERPERIODID        10
 #define L_AUSTINF_AKTUELL              1
 #define L_AUSTINF_HISTORY              1
 #define L_AUSTINF_ONLYORDER            1
 #define L_AUSTINF_ONLYORDERFILI        1
 #define L_AUSTINF_REGIONLIST           100
 #define L_AUSTINF_WAITFORIBTPICKING    7
 #define L_AUSTINF_NAMEINHABER          30
 #define L_AUSTINF_SAP_REFERENCENO      10


 #define L_AUSTINF_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUSTINF_ANZ (int) ( sizeof(AUSTINF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUSTINF sizeof(struct AUSTINF)


 #define AUSTINF_H

 #define AUSTINF_LISTE \
            KDAUFTRAG.KDAUFTRAGNR, \
            KDAUFTRAG.KDAUFTRAGSTAT, \
            KDAUFTRAG.IDFNR, \
            KDAUFTRAG.GERAETNAME, \
            KDAUFTRAG.TOURID, \
            KDAUFTRAG.ETAUFTRAGSCHALTER2, \
            KDAUFTRAG.KDAUFTRAGART, \
            KDAUFTRAG.KOART, \
            KDAUFTRAG.BUCHART, \
            KDAUFTRAG.ANZPOS, \
            KDAUFTRAG.ANZPOSDAFUE, \
            KDAUFTRAG.ZEITENDEAM, \
            KDAUFTRAG.ZEITENDEPM, \
            KUNDE.NAMEAPO, \
            KUNDE.KZKDKLASSE, \
            KDAUFTRAG.ANZPOSOB, \
            KDAUFTRAG.ANZALPHATEXT, \
            KUNDE.ORT, \
            AADUMMY.ZEITERSTEGUELTIGK, \
            KDAUFTRAGEREIGNIS.DATUM, \
            KDAUFTRAG.KUNDENNR, \
            KDAUFTRAG.VERTRIEBSZENTRUMNR, \
            KDAUFTRAG.KDAUFTRAGNRFILIALE, \
            KDAUFTRAG.SENDESTATUS, \
            KDAUFTRAG.ZUGRUND, \
            KDAUFTRAG.DATUMAUSLIEFERUNG, \
            KDAUFTRAG.RECHNUNGNR, \
            KDAUFTRAG.SORTFIELD, \
            KDAUFTRAG.BATCHSCHREIBEN, \
            KDAUFTRAG.INVOICENUMBER, \
            KDAUFTRAG.PAYMENTDATE, \
            KDAUFTRAG.PAYMENTTYPE, \
            KDAUFTRAG.ORDERLABEL, \
            KDAUFTRAG.ORDERPERIODID, \
            AADUMMY.AKTUELL, \
            AADUMMY.HISTORY, \
            AADUMMY.ONLYORDER, \
            AADUMMY.ONLYORDERFILI, \
            AADUMMY.REGIONLIST, \
            CSCORDERFLAGS.WAITFORIBTPICKING, \
            KUNDE.NAMEINHABER, \
            AADUMMY.SAP_REFERENCENO
 #define AUSTINF_PLISTE \
            "KDAUFTRAG.KDAUFTRAGNR," \
            "KDAUFTRAG.KDAUFTRAGSTAT," \
            "KDAUFTRAG.IDFNR," \
            "KDAUFTRAG.GERAETNAME," \
            "KDAUFTRAG.TOURID," \
            "KDAUFTRAG.ETAUFTRAGSCHALTER2," \
            "KDAUFTRAG.KDAUFTRAGART," \
            "KDAUFTRAG.KOART," \
            "KDAUFTRAG.BUCHART," \
            "KDAUFTRAG.ANZPOS," \
            "KDAUFTRAG.ANZPOSDAFUE," \
            "KDAUFTRAG.ZEITENDEAM," \
            "KDAUFTRAG.ZEITENDEPM," \
            "KUNDE.NAMEAPO," \
            "KUNDE.KZKDKLASSE," \
            "KDAUFTRAG.ANZPOSOB," \
            "KDAUFTRAG.ANZALPHATEXT," \
            "KUNDE.ORT," \
            "AADUMMY.ZEITERSTEGUELTIGK," \
            "KDAUFTRAGEREIGNIS.DATUM," \
            "KDAUFTRAG.KUNDENNR," \
            "KDAUFTRAG.VERTRIEBSZENTRUMNR," \
            "KDAUFTRAG.KDAUFTRAGNRFILIALE," \
            "KDAUFTRAG.SENDESTATUS," \
            "KDAUFTRAG.ZUGRUND," \
            "KDAUFTRAG.DATUMAUSLIEFERUNG," \
            "KDAUFTRAG.RECHNUNGNR," \
            "KDAUFTRAG.SORTFIELD," \
            "KDAUFTRAG.BATCHSCHREIBEN," \
            "KDAUFTRAG.INVOICENUMBER," \
            "KDAUFTRAG.PAYMENTDATE," \
            "KDAUFTRAG.PAYMENTTYPE," \
            "KDAUFTRAG.ORDERLABEL," \
            "KDAUFTRAG.ORDERPERIODID," \
            "AADUMMY.AKTUELL," \
            "AADUMMY.HISTORY," \
            "AADUMMY.ONLYORDER," \
            "AADUMMY.ONLYORDERFILI," \
            "AADUMMY.REGIONLIST," \
            "CSCORDERFLAGS.WAITFORIBTPICKING," \
            "KUNDE.NAMEINHABER," \
            "AADUMMY.SAP_REFERENCENO"
 #define AUSTINF_PELISTE \
            "KDAUFTRAGNR," \
            "KDAUFTRAGSTAT," \
            "IDFNR," \
            "GERAETNAME," \
            "TOURID," \
            "ETAUFTRAGSCHALTER2," \
            "KDAUFTRAGART," \
            "KOART," \
            "BUCHART," \
            "ANZPOS," \
            "ANZPOSDAFUE," \
            "ZEITENDEAM," \
            "ZEITENDEPM," \
            "NAMEAPO," \
            "KZKDKLASSE," \
            "ANZPOSOB," \
            "ANZALPHATEXT," \
            "ORT," \
            "ZEITERSTEGUELTIGK," \
            "DATUM," \
            "KUNDENNR," \
            "VERTRIEBSZENTRUMNR," \
            "KDAUFTRAGNRFILIALE," \
            "SENDESTATUS," \
            "ZUGRUND," \
            "DATUMAUSLIEFERUNG," \
            "RECHNUNGNR," \
            "SORTFIELD," \
            "BATCHSCHREIBEN," \
            "INVOICENUMBER," \
            "PAYMENTDATE," \
            "PAYMENTTYPE," \
            "ORDERLABEL," \
            "ORDERPERIODID," \
            "AKTUELL," \
            "HISTORY," \
            "ONLYORDER," \
            "ONLYORDERFILI," \
            "REGIONLIST," \
            "WAITFORIBTPICKING," \
            "NAMEINHABER," \
            "SAP_REFERENCENO"
 #define AUSTINF_UPDLISTE \
            "KDAUFTRAGNR=?," \
            "KDAUFTRAGSTAT=?," \
            "IDFNR=?," \
            "GERAETNAME=?," \
            "TOURID=?," \
            "ETAUFTRAGSCHALTER2=?," \
            "KDAUFTRAGART=?," \
            "KOART=?," \
            "BUCHART=?," \
            "ANZPOS=?," \
            "ANZPOSDAFUE=?," \
            "ZEITENDEAM=?," \
            "ZEITENDEPM=?," \
            "NAMEAPO=?," \
            "KZKDKLASSE=?," \
            "ANZPOSOB=?," \
            "ANZALPHATEXT=?," \
            "ORT=?," \
            "ZEITERSTEGUELTIGK=?," \
            "DATUM=?," \
            "KUNDENNR=?," \
            "VERTRIEBSZENTRUMNR=?," \
            "KDAUFTRAGNRFILIALE=?," \
            "SENDESTATUS=?," \
            "ZUGRUND=?," \
            "DATUMAUSLIEFERUNG=?," \
            "RECHNUNGNR=?," \
            "SORTFIELD=?," \
            "BATCHSCHREIBEN=?," \
            "INVOICENUMBER=?," \
            "PAYMENTDATE=?," \
            "PAYMENTTYPE=?," \
            "ORDERLABEL=?," \
            "ORDERPERIODID=?," \
            "AKTUELL=?," \
            "HISTORY=?," \
            "ONLYORDER=?," \
            "ONLYORDERFILI=?," \
            "REGIONLIST=?," \
            "WAITFORIBTPICKING=?," \
            "NAMEINHABER=?," \
            "SAP_REFERENCENO=?"
 #define AUSTINFKDAUFTRAGNR                   0
 #define AUSTINFKDAUFTRAGSTAT                 1
 #define AUSTINFIDFNR                         2
 #define AUSTINFGERAETNAME                    3
 #define AUSTINFTOURID                        4
 #define AUSTINFETAUFTRAGSCHALTER2            5
 #define AUSTINFKDAUFTRAGART                  6
 #define AUSTINFKOART                         7
 #define AUSTINFBUCHART                       8
 #define AUSTINFANZPOS                        9
 #define AUSTINFANZPOSDAFUE                   10
 #define AUSTINFZEITENDEAM                    11
 #define AUSTINFZEITENDEPM                    12
 #define AUSTINFNAMEAPO                       13
 #define AUSTINFKZKDKLASSE                    14
 #define AUSTINFANZPOSOB                      15
 #define AUSTINFANZALPHATEXT                  16
 #define AUSTINFORT                           17
 #define AUSTINFZEITERSTEGUELTIGK             18
 #define AUSTINFDATUM                         19
 #define AUSTINFKUNDENNR                      20
 #define AUSTINFVERTRIEBSZENTRUMNR            21
 #define AUSTINFKDAUFTRAGNRFILIALE            22
 #define AUSTINFSENDESTATUS                   23
 #define AUSTINFZUGRUND                       24
 #define AUSTINFDATUMAUSLIEFERUNG             25
 #define AUSTINFRECHNUNGNR                    26
 #define AUSTINFSORTFIELD                     27
 #define AUSTINFBATCHSCHREIBEN                28
 #define AUSTINFINVOICENUMBER                 29
 #define AUSTINFPAYMENTDATE                   30
 #define AUSTINFPAYMENTTYPE                   31
 #define AUSTINFORDERLABEL                    32
 #define AUSTINFORDERPERIODID                 33
 #define AUSTINFAKTUELL                       34
 #define AUSTINFHISTORY                       35
 #define AUSTINFONLYORDER                     36
 #define AUSTINFONLYORDERFILI                 37
 #define AUSTINFREGIONLIST                    38
 #define AUSTINFWAITFORIBTPICKING             39
 #define AUSTINFNAMEINHABER                   40
 #define AUSTINFSAP_REFERENCENO               41

 #define AUSTINF_ZEIGER(xxx) \
            :xxx->KDAUFTRAGNR, \
            :xxx->KDAUFTRAGSTAT, \
            :xxx->IDFNR, \
            :xxx->GERAETNAME, \
            :xxx->TOURID, \
            :xxx->ETAUFTRAGSCHALTER2, \
            :xxx->KDAUFTRAGART, \
            :xxx->KOART, \
            :xxx->BUCHART, \
            :xxx->ANZPOS, \
            :xxx->ANZPOSDAFUE, \
            :xxx->ZEITENDEAM, \
            :xxx->ZEITENDEPM, \
            :xxx->NAMEAPO, \
            :xxx->KZKDKLASSE, \
            :xxx->ANZPOSOB, \
            :xxx->ANZALPHATEXT, \
            :xxx->ORT, \
            :xxx->ZEITERSTEGUELTIGK, \
            :xxx->DATUM, \
            :xxx->KUNDENNR, \
            :xxx->VERTRIEBSZENTRUMNR, \
            :xxx->KDAUFTRAGNRFILIALE, \
            :xxx->SENDESTATUS, \
            :xxx->ZUGRUND, \
            :xxx->DATUMAUSLIEFERUNG, \
            :xxx->RECHNUNGNR, \
            :xxx->SORTFIELD, \
            :xxx->BATCHSCHREIBEN, \
            :xxx->INVOICENUMBER, \
            :xxx->PAYMENTDATE=?, \
            :xxx->PAYMENTTYPE=?, \
            :xxx->ORDERLABEL=?, \
            :xxx->ORDERPERIODID=?, \
            :xxx->AKTUELL=?, \
            :xxx->HISTORY=?, \
            :xxx->ONLYORDER=?, \
            :xxx->ONLYORDERFILI=?, \
            :xxx->REGIONLIST=?, \
            :xxx->WAITFORIBTPICKING=?, \
            :xxx->NAMEINHABER=?, \
            :xxx->SAP_REFERENCENO

 #define AUSTINF_UPDATE(xxx) \
            KDAUFTRAGNR = :xxx->KDAUFTRAGNR, \
            KDAUFTRAGSTAT = :xxx->KDAUFTRAGSTAT, \
            IDFNR = :xxx->IDFNR, \
            GERAETNAME = :xxx->GERAETNAME, \
            TOURID = :xxx->TOURID, \
            ETAUFTRAGSCHALTER2 = :xxx->ETAUFTRAGSCHALTER2, \
            KDAUFTRAGART = :xxx->KDAUFTRAGART, \
            KOART = :xxx->KOART, \
            BUCHART = :xxx->BUCHART, \
            ANZPOS = :xxx->ANZPOS, \
            ANZPOSDAFUE = :xxx->ANZPOSDAFUE, \
            ZEITENDEAM = :xxx->ZEITENDEAM, \
            ZEITENDEPM = :xxx->ZEITENDEPM, \
            NAMEAPO = :xxx->NAMEAPO, \
            KZKDKLASSE = :xxx->KZKDKLASSE, \
            ANZPOSOB = :xxx->ANZPOSOB, \
            ANZALPHATEXT = :xxx->ANZALPHATEXT, \
            ORT = :xxx->ORT, \
            ZEITERSTEGUELTIGK = :xxx->ZEITERSTEGUELTIGK, \
            DATUM = :xxx->DATUM, \
            KUNDENNR = :xxx->KUNDENNR, \
            VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR, \
            KDAUFTRAGNRFILIALE = :xxx->KDAUFTRAGNRFILIALE, \
            SENDESTATUS = :xxx->SENDESTATUS, \
            ZUGRUND = :xxx->ZUGRUND, \
            DATUMAUSLIEFERUNG = :xxx->DATUMAUSLIEFERUNG, \
            RECHNUNGNR = :xxx->RECHNUNGNR, \
            SORTFIELD = :xxx->SORTFIELD, \
            BATCHSCHREIBEN = :xxx->BATCHSCHREIBEN, \
            INVOICENUMBER = :xxx->INVOICENUMBER, \
            PAYMENTDATE = :xxx->PAYMENTDATE, \
            PAYMENTTYPE = :xxx->PAYMENTTYPE, \
            ORDERLABEL = :xxx->ORDERLABEL, \
            ORDERPERIODID = :xxx->ORDERPERIODID, \
            AKTUELL = :xxx->AKTUELL, \
            HISTORY = :xxx->HISTORY, \
            ONLYORDER = :xxx->ONLYORDER, \
            ONLYORDERFILI = :xxx->ONLYORDERFILI, \
            REGIONLIST = :xxx->REGIONLIST, \
            WAITFORIBTPICKING = :xxx->WAITFORIBTPICKING, \
            NAMEINHABER = :xxx->NAMEINHABER, \
            SAP_REFERENCENO =:xxx->SAP_REFERENCENO

 #define LS_AUSTINF_KDAUFTRAGNR          11
 #define LS_AUSTINF_KDAUFTRAGSTAT        17
 #define LS_AUSTINF_IDFNR                11
 #define LS_AUSTINF_GERAETNAME           9
 #define LS_AUSTINF_TOURID               7
 #define LS_AUSTINF_ETAUFTRAGSCHALTER2   6
 #define LS_AUSTINF_KDAUFTRAGART         3
 #define LS_AUSTINF_KOART                2
 #define LS_AUSTINF_BUCHART              2
 #define LS_AUSTINF_ANZPOS               11
 #define LS_AUSTINF_ANZPOSDAFUE          11
 #define LS_AUSTINF_ZEITENDEAM           11
 #define LS_AUSTINF_ZEITENDEPM           11
 #define LS_AUSTINF_NAMEAPO              41
 #define LS_AUSTINF_KZKDKLASSE           4
 #define LS_AUSTINF_ANZPOSOB             11
 #define LS_AUSTINF_ANZALPHATEXT         11
 #define LS_AUSTINF_ORT                  31
 #define LS_AUSTINF_ZEITERSTEGUELTIGK    11
 #define LS_AUSTINF_DATUM                11
 #define LS_AUSTINF_KUNDENNR             11
 #define LS_AUSTINF_VERTRIEBSZENTRUMNR   7
 #define LS_AUSTINF_KDAUFTRAGNRFILIALE   11
 #define LS_AUSTINF_SENDESTATUS          7
 #define LS_AUSTINF_ZUGRUND              17
 #define LS_AUSTINF_DATUMAUSLIEFERUNG    11
 #define LS_AUSTINF_RECHNUNGNR           11
 #define LS_AUSTINF_SORTFIELD            21
 #define LS_AUSTINF_BATCHSCHREIBEN       11
 #define LS_AUSTINF_INVOICENUMBER        16
 #define LS_AUSTINF_PAYMENTDATE          11
 #define LS_AUSTINF_PAYMENTTYPE          2
 #define LS_AUSTINF_ORDERLABEL           41
 #define LS_AUSTINF_ORDERPERIODID        11
 #define LS_AUSTINF_AKTUELL              2
 #define LS_AUSTINF_HISTORY              2
 #define LS_AUSTINF_ONLYORDER            2
 #define LS_AUSTINF_ONLYORDERFILI        2
 #define LS_AUSTINF_REGIONLIST           101
 #define LS_AUSTINF_WAITFORIBTPICKING    7
 #define LS_AUSTINF_NAMEINHABER          31
 #define LS_AUSTINF_SAP_REFERENCENO      11
 #define LS_AUSTINF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUSTINF {
         long    KDAUFTRAGNR;
         char    KDAUFTRAGSTAT[16 + 1];
         long    IDFNR;
         char    GERAETNAME[8 + 1];
         char    TOURID[6 + 1];
         long    ETAUFTRAGSCHALTER2;
         char    KDAUFTRAGART[2 + 1];
         char    KOART[1 + 1];
         char    BUCHART[1 + 1];
         long    ANZPOS;
         long    ANZPOSDAFUE;
         long    ZEITENDEAM;
         long    ZEITENDEPM;
         char    NAMEAPO[40 + 1];
         char    KZKDKLASSE[3 + 1];
         long    ANZPOSOB;
         long    ANZALPHATEXT;
         char    ORT[30 + 1];
         long    ZEITERSTEGUELTIGK;
         long    DATUM;
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         long    KDAUFTRAGNRFILIALE;
         short   SENDESTATUS;
         short   REGIONNR;
         char    ZUGRUND[16 + 1];
         long    DATUMAUSLIEFERUNG;
         long    RECHNUNGNR;
         char    SORTFIELD[20 + 1];
         long    BATCHSCHREIBEN;
         char    INVOICENUMBER[15 + 1];
         long    PAYMENTDATE;
         char    PAYMENTTYPE[1 + 1];
         char    ORDERLABEL[40 + 1];
         long    ORDERPERIODID;
         char    AKTUELL[1 + 1];
         char    HISTORY[1 + 1];
         char    ONLYORDER[1 + 1];
         char    ONLYORDERFILI[1 + 1];
         char    REGIONLIST[100 + 1];
         short   WAITFORIBTPICKING;
         char    NAMEINHABER[30 + 1];
         char    SAP_REFERENCENO[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUSTINF {
         long    KDAUFTRAGNR;
         char    KDAUFTRAGSTAT[16 + 1];
         long    IDFNR;
         char    GERAETNAME[8 + 1];
         char    TOURID[6 + 1];
         long    ETAUFTRAGSCHALTER2;
         char    KDAUFTRAGART[2 + 1];
         char    KOART;
         char    BUCHART;
         long    ANZPOS;
         long    ANZPOSDAFUE;
         long    ZEITENDEAM;
         long    ZEITENDEPM;
         char    NAMEAPO[40 + 1];
         char    KZKDKLASSE[3 + 1];
         long    ANZPOSOB;
         long    ANZALPHATEXT;
         char    ORT[30 + 1];
         long    ZEITERSTEGUELTIGK;
         long    DATUM;
         long    KUNDENNR;
         short   VERTRIEBSZENTRUMNR;
         long    KDAUFTRAGNRFILIALE;
         short   SENDESTATUS;
         short   REGIONNR;
         char    ZUGRUND[16 + 1];
         long    DATUMAUSLIEFERUNG;
         long    RECHNUNGNR;
         char    SORTFIELD[20 + 1];
         long    BATCHSCHREIBEN;
         char    INVOICENUMBER[15 + 1];
         long    PAYMENTDATE;
         char    PAYMENTTYPE;
         char    ORDERLABEL[40 + 1];
         long    ORDERPERIODID;
         char    AKTUELL;
         char    HISTORY;
         char    ONLYORDER;
         char    ONLYORDERFILI;
         char    REGIONLIST[100 + 1];
         short   WAITFORIBTPICKING;
         char    NAMEINHABER[30 + 1];
         char    SAP_REFERENCENO[10 + 1];
         long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUSTINF {
         short  KDAUFTRAGNR;
         short  KDAUFTRAGSTAT;
         short  IDFNR;
         short  GERAETNAME;
         short  TOURID;
         short  ETAUFTRAGSCHALTER2;
         short  KDAUFTRAGART;
         short  KOART;
         short  BUCHART;
         short  ANZPOS;
         short  ANZPOSDAFUE;
         short  ZEITENDEAM;
         short  ZEITENDEPM;
         short  NAMEAPO;
         short  KZKDKLASSE;
         short  ANZPOSOB;
         short  ANZALPHATEXT;
         short  ORT;
         short  ZEITERSTEGUELTIGK;
         short  DATUM;
         short  KUNDENNR;
         short  VERTRIEBSZENTRUMNR;
         short  KDAUFTRAGNRFILIALE;
         short  SENDESTATUS;
         short  REGIONNR;
         short  ZUGRUND;
         short  DATUMAUSLIEFERUNG;
         short  RECHNUNGNR;
         short  SORTFIELD;
         short  BATCHSCHREIBEN;
         short  INVOICENUMBER;
         short  PAYMENTDATE;
         short  PAYMENTTYPE;
         short  ORDERLABEL;
         short  ORDERPERIODID;
         short  AKTUELL;
         short  HISTORY;
         short  ONLYORDER;
         short  ONLYORDERFILI;
         short  REGIONLIST;
         short  WAITFORIBTPICKING;
         short  NAMEINHABER;
         short  SAP_REFERENCENO;
         short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUSTINF {
         char    KDAUFTRAGNR[11];
         char    KDAUFTRAGSTAT[16 + 1];
         char    IDFNR[11];
         char    GERAETNAME[8 + 1];
         char    TOURID[6 + 1];
         char    ETAUFTRAGSCHALTER2[5 + 1];
         char    KDAUFTRAGART[2 + 1];
         char    KOART[1 + 1];
         char    BUCHART[1 + 1];
         char    ANZPOS[11];
         char    ANZPOSDAFUE[11];
         char    ZEITENDEAM[11];
         char    ZEITENDEPM[11];
         char    NAMEAPO[40 + 1];
         char    KZKDKLASSE[3 + 1];
         char    ANZPOSOB[11];
         char    ANZALPHATEXT[11];
         char    ORT[30 + 1];
         char    ZEITERSTEGUELTIGK[11];
         char    DATUM[11];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7+1];
         char    KDAUFTRAGNRFILIALE[11];
         char    SENDESTATUS[7+1];
         char    REGIONNR[7+1];
         char    ZUGRUND[16 + 1];
         char    DATUMAUSLIEFERUNG[11];
         char    RECHNUNGNR[11];
         char    SORTFIELD[20 + 1];
         char    BATCHSCHREIBEN[11];
         char    INVOICENUMBER[15 + 1];
         char    PAYMENTDATE[11];
         char    PAYMENTTYPE[1 + 1];
         char    ORDERLABEL[40 + 1];
         char    ORDERPERIODID[11];
         char    AKTUELL[1 + 1];
         char    HISTORY[1 + 1];
         char    ONLYORDER[1 + 1];
         char    ONLYORDERFILI[1 + 1];
         char    REGIONLIST[100 + 1];
         char    WAITFORIBTPICKING[7 + 1];
         char    NAMEINHABER[30 + 1];
         char    SAP_REFERENCENO[10 + 1];
         char    FETCH_REL[11];
       };

 struct O_AUSTINF {
         char    KDAUFTRAGNR[11];
         char    KDAUFTRAGSTAT[16];
         char    IDFNR[11];
         char    GERAETNAME[8];
         char    TOURID[6];
         char    ETAUFTRAGSCHALTER2[5];
         char    KDAUFTRAGART[2];
         char    KOART[1];
         char    BUCHART[1];
         char    ANZPOS[11];
         char    ANZPOSDAFUE[11];
         char    ZEITENDEAM[11];
         char    ZEITENDEPM[11];
         char    NAMEAPO[40];
         char    KZKDKLASSE[3];
         char    ANZPOSOB[11];
         char    ANZALPHATEXT[11];
         char    ORT[30];
         char    ZEITERSTEGUELTIGK[11];
         char    DATUM[11];
         char    KUNDENNR[11];
         char    VERTRIEBSZENTRUMNR[7];
         char    KDAUFTRAGNRFILIALE[11];
         char    SENDESTATUS[7];
         char    REGIONNR[7];
         char    ZUGRUND[16];
         char    DATUMAUSLIEFERUNG[11];
         char    RECHNUNGNR[11];
         char    SORTFIELD[20];
         char    BATCHSCHREIBEN[11];
         char    INVOICENUMBER[15];
         char    PAYMENTDATE[11];
         char    PAYMENTTYPE[1];
         char    ORDERLABEL[40];
         char    ORDERPERIODID[11];
         char    AKTUELL[1];
         char    HISTORY[1];
         char    ONLYORDER[1];
         char    ONLYORDERFILI[1];
         char    REGIONLIST[100];
         char    WAITFORIBTPICKING[7];
         char    NAMEINHABER[30];
         char    SAP_REFERENCENO[10];
         char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUSTINF_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    6 ,   0 },
     { TYP_S,    6 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   20 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   15 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,    1 ,   0 },
     { TYP_C,  100 ,   0 },
     { TYP_S,    6 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUSTINF_BES [] =
 {
     { TYP_L,   11 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    8 ,   0 },
     { TYP_C,    6 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,    2 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_C,    3 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,   16 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   20 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_C,   15 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_C,   40 ,   0 },
     { TYP_L,   11 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_F,    1 ,   0 },
     { TYP_C,  100 ,   0 },
     { TYP_S,    5 ,   0 },
     { TYP_C,   30 ,   0 },
     { TYP_C,   10 ,   0 },
     { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUSTINF
 {
  public:

  AUSTINF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUSTINF_BES, AUSTINF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUSTINF_BES, AUSTINF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUSTINF_BES, AUSTINF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUSTINF()
  {
   ::buf_default((void *)&s, AUSTINF_BES, AUSTINF_ANZ);
  }
 };
#endif

#define AUSTINF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx ( \
         KDAUFTRAGNR INTEGER, \
         KDAUFTRAGSTAT CHAR(16), \
         IDFNR INTEGER, \
         GERAETNAME CHAR(8), \
         TOURID CHAR(6), \
         ETAUFTRAGSCHALTER2 INTEGER, \
         KDAUFTRAGART CHAR(2), \
         KOART CHAR(1), \
         BUCHART CHAR(1), \
         ANZPOS INTEGER, \
         ANZPOSDAFUE INTEGER, \
         ZEITENDEAM INTEGER, \
         ZEITENDEPM INTEGER, \
         NAMEAPO CHAR(40), \
         KZKDKLASSE CHAR(3), \
         ANZPOSOB INTEGER, \
         ANZALPHATEXT INTEGER, \
         ORT CHAR(30), \
         ZEITERSTEGUELTIGK INTEGER, \
         DATUM INTEGER, \
         KUNDENNR INTEGER, \
         VERTRIEBSZENTRUMNR SMALLINT, \
         KDAUFTRAGNRFILIALE INTEGER, \
         SENDESTATUS SMALLINT, \
         ZUGRUND CHAR(16), \
         DATUMAUSLIEFERUNG INTEGER, \
         RECHNUNGNR INTEGER, \
         SORTFIELD CHAR(20), \
         BATCHSCHREIBEN INTEGER, \
         INVOICENUMBER CHAR(15), \
         PAYMENTDATE INTEGER, \
         PAYMENTTYPE CHAR(1), \
         ORDERLABEL CHAR(40), \
         ORDERPERIODID INTEGER, \
         AKTUELL CHAR(1), \
         HISTORY CHAR(1), \
         ONLYORDER CHAR(1), \
         ONLYORDERFILI CHAR(1), \
         REGIONLIST CHAR(100), \
         WAITFORIBTPICKING SMALLINT, \
         NAMEINHABER CHAR(40), \
         SAP_REFERENCENO char(10), \
         FETCH_REL INTEGER  ) EXTENT SIZE 1573 LOCK MODE ROW;

#define AUSTINF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGX         on yyy( KDAUFTRAGNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_303    on yyy( KDAUFTRAGSTAT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_304    on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_305    on yyy( GERAETNAME );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDAUFTRAGTOURX     on yyy( TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUSTINF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGX        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_303   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_304   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_305   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDAUFTRAGTOURX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#endif // __AUFTRAG_H
