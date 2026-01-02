/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPMASTER_FILIALNR             6
 #define L_RUFPMASTER_IDFNR                11
 #define L_RUFPMASTER_RUFZEIT              11
 #define L_RUFPMASTER_AKTIVMONTAG          1
 #define L_RUFPMASTER_AKTIVDIENSTAG        1
 #define L_RUFPMASTER_AKTIVMITTWOCH        1
 #define L_RUFPMASTER_AKTIVDONNERSTAG      1
 #define L_RUFPMASTER_AKTIVFREITAG         1
 #define L_RUFPMASTER_AKTIVSAMSTAG         1
 #define L_RUFPMASTER_AKTIVSONNTAG         1
 #define L_RUFPMASTER_PROTOKOLLART         1
 #define L_RUFPMASTER_VERARBEITUNGART      1
 #define L_RUFPMASTER_PRIORITAET           6
 #define L_RUFPMASTER_SPERRKZ              1
 #define L_RUFPMASTER_LOESCHKZ             1
 #define L_RUFPMASTER_POOLNR               6
 #define L_RUFPMASTER_RUECKRUFKZ           1
 #define L_RUFPMASTER_KZ_HOST              1


 #define L_RUFPMASTER_PKEY 28

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPMASTER_ANZ (int) ( sizeof(RUFPMASTER_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPMASTER sizeof(struct RUFPMASTER)


 #define RUFPMASTER_H

 #define RUFPMASTER_LISTE \
 			MASTERPLAN.FILIALNR, \
 			MASTERPLAN.IDFNR, \
 			MASTERPLAN.RUFZEIT, \
 			MASTERPLAN.AKTIVMONTAG, \
 			MASTERPLAN.AKTIVDIENSTAG, \
 			MASTERPLAN.AKTIVMITTWOCH, \
 			MASTERPLAN.AKTIVDONNERSTAG, \
 			MASTERPLAN.AKTIVFREITAG, \
 			MASTERPLAN.AKTIVSAMSTAG, \
 			MASTERPLAN.AKTIVSONNTAG, \
 			MASTERPLAN.PROTOKOLLART, \
 			MASTERPLAN.VERARBEITUNGART, \
 			MASTERPLAN.PRIORITAET, \
 			MASTERPLAN.SPERRKZ, \
 			MASTERPLAN.LOESCHKZ, \
 			MASTERPLAN.POOLNR, \
 			MASTERPLAN.RUECKRUFKZ, \
 			MASTERPLAN.KZ_HOST, \
 			MASTERPLAN.TOURID
 #define RUFPMASTER_PLISTE \
 			"MASTERPLAN.FILIALNR," \
 			"MASTERPLAN.IDFNR," \
 			"MASTERPLAN.RUFZEIT," \
 			"MASTERPLAN.AKTIVMONTAG," \
 			"MASTERPLAN.AKTIVDIENSTAG," \
 			"MASTERPLAN.AKTIVMITTWOCH," \
 			"MASTERPLAN.AKTIVDONNERSTAG," \
 			"MASTERPLAN.AKTIVFREITAG," \
 			"MASTERPLAN.AKTIVSAMSTAG," \
 			"MASTERPLAN.AKTIVSONNTAG," \
 			"MASTERPLAN.PROTOKOLLART," \
 			"MASTERPLAN.VERARBEITUNGART," \
 			"MASTERPLAN.PRIORITAET," \
 			"MASTERPLAN.SPERRKZ," \
 			"MASTERPLAN.LOESCHKZ," \
 			"MASTERPLAN.POOLNR," \
 			"MASTERPLAN.RUECKRUFKZ," \
 			"MASTERPLAN.KZ_HOST," \
 			"MASTERPLAN.TOURID " 

 #define RUFPMASTER_PELISTE \
 			"FILIALNR," \
 			"IDFNR," \
 			"RUFZEIT," \
 			"AKTIVMONTAG," \
 			"AKTIVDIENSTAG," \
 			"AKTIVMITTWOCH," \
 			"AKTIVDONNERSTAG," \
 			"AKTIVFREITAG," \
 			"AKTIVSAMSTAG," \
 			"AKTIVSONNTAG," \
 			"PROTOKOLLART," \
 			"VERARBEITUNGART," \
 			"PRIORITAET," \
 			"SPERRKZ," \
 			"LOESCHKZ," \
 			"POOLNR," \
 			"RUECKRUFKZ," \
 			"KZ_HOST," \
 			"TOURID " 

 #define RUFPMASTER_UPDLISTE \
 			"FILIALNR=?," \
 			"IDFNR=?," \
 			"RUFZEIT=?," \
 			"AKTIVMONTAG=?," \
 			"AKTIVDIENSTAG=?," \
 			"AKTIVMITTWOCH=?," \
 			"AKTIVDONNERSTAG=?," \
 			"AKTIVFREITAG=?," \
 			"AKTIVSAMSTAG=?," \
 			"AKTIVSONNTAG=?," \
 			"PROTOKOLLART=?," \
 			"VERARBEITUNGART=?," \
 			"PRIORITAET=?," \
 			"SPERRKZ=?," \
 			"LOESCHKZ=?," \
 			"POOLNR=?," \
 			"RUECKRUFKZ=?," \
 			"KZ_HOST=?," \
 			"TOURID=? " 

 #define RUFPMASTERFILIALNR                      0
 #define RUFPMASTERIDFNR                         1
 #define RUFPMASTERRUFZEIT                       2
 #define RUFPMASTERAKTIVMONTAG                   3
 #define RUFPMASTERAKTIVDIENSTAG                 4
 #define RUFPMASTERAKTIVMITTWOCH                 5
 #define RUFPMASTERAKTIVDONNERSTAG               6
 #define RUFPMASTERAKTIVFREITAG                  7
 #define RUFPMASTERAKTIVSAMSTAG                  8
 #define RUFPMASTERAKTIVSONNTAG                  9
 #define RUFPMASTERPROTOKOLLART                  10
 #define RUFPMASTERVERARBEITUNGART               11
 #define RUFPMASTERPRIORITAET                    12
 #define RUFPMASTERSPERRKZ                       13
 #define RUFPMASTERLOESCHKZ                      14
 #define RUFPMASTERPOOLNR                        15
 #define RUFPMASTERRUECKRUFKZ                    16
 #define RUFPMASTERKZ_HOST                       17
 #define RUFPMASTERTOURID                        18

 #define RUFPMASTER_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->IDFNR,\
 			:xxx->RUFZEIT,\
 			:xxx->AKTIVMONTAG,\
 			:xxx->AKTIVDIENSTAG,\
 			:xxx->AKTIVMITTWOCH,\
 			:xxx->AKTIVDONNERSTAG,\
 			:xxx->AKTIVFREITAG,\
 			:xxx->AKTIVSAMSTAG,\
 			:xxx->AKTIVSONNTAG,\
 			:xxx->PROTOKOLLART,\
 			:xxx->VERARBEITUNGART,\
 			:xxx->PRIORITAET,\
 			:xxx->SPERRKZ,\
 			:xxx->LOESCHKZ,\
 			:xxx->POOLNR,\
 			:xxx->RUECKRUFKZ,\
 			:xxx->KZ_HOST,\
 			:xxx->TOURID

 #define RUFPMASTER_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			IDFNR = :xxx->IDFNR,\
 			RUFZEIT = :xxx->RUFZEIT,\
 			AKTIVMONTAG = :xxx->AKTIVMONTAG,\
 			AKTIVDIENSTAG = :xxx->AKTIVDIENSTAG,\
 			AKTIVMITTWOCH = :xxx->AKTIVMITTWOCH,\
 			AKTIVDONNERSTAG = :xxx->AKTIVDONNERSTAG,\
 			AKTIVFREITAG = :xxx->AKTIVFREITAG,\
 			AKTIVSAMSTAG = :xxx->AKTIVSAMSTAG,\
 			AKTIVSONNTAG = :xxx->AKTIVSONNTAG,\
 			PROTOKOLLART = :xxx->PROTOKOLLART,\
 			VERARBEITUNGART = :xxx->VERARBEITUNGART,\
 			PRIORITAET = :xxx->PRIORITAET,\
 			SPERRKZ = :xxx->SPERRKZ,\
 			LOESCHKZ = :xxx->LOESCHKZ,\
 			POOLNR = :xxx->POOLNR,\
 			RUECKRUFKZ = :xxx->RUECKRUFKZ,\
 			KZ_HOST = :xxx->KZ_HOST,\
 			TOURID = :xxx->TOURID

 #define LS_RUFPMASTER_FILIALNR             7
 #define LS_RUFPMASTER_IDFNR                11
 #define LS_RUFPMASTER_RUFZEIT              11
 #define LS_RUFPMASTER_AKTIVMONTAG          2
 #define LS_RUFPMASTER_AKTIVDIENSTAG        2
 #define LS_RUFPMASTER_AKTIVMITTWOCH        2
 #define LS_RUFPMASTER_AKTIVDONNERSTAG      2
 #define LS_RUFPMASTER_AKTIVFREITAG         2
 #define LS_RUFPMASTER_AKTIVSAMSTAG         2
 #define LS_RUFPMASTER_AKTIVSONNTAG         2
 #define LS_RUFPMASTER_PROTOKOLLART         2
 #define LS_RUFPMASTER_VERARBEITUNGART      2
 #define LS_RUFPMASTER_PRIORITAET           7
 #define LS_RUFPMASTER_SPERRKZ              2
 #define LS_RUFPMASTER_LOESCHKZ             2
 #define LS_RUFPMASTER_POOLNR               7
 #define LS_RUFPMASTER_RUECKRUFKZ           2
 #define LS_RUFPMASTER_KZ_HOST              2
 #define LS_RUFPMASTER_TOURID               7
 #define LS_RUFPMASTER_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPMASTER {
		 short   FILIALNR;
		 long    IDFNR;
		 long    RUFZEIT;
		 char    AKTIVMONTAG[1 + 1];
		 char    AKTIVDIENSTAG[1 + 1];
		 char    AKTIVMITTWOCH[1 + 1];
		 char    AKTIVDONNERSTAG[1 + 1];
		 char    AKTIVFREITAG[1 + 1];
		 char    AKTIVSAMSTAG[1 + 1];
		 char    AKTIVSONNTAG[1 + 1];
		 char    PROTOKOLLART[1 + 1];
		 char    VERARBEITUNGART[1 + 1];
		 short   PRIORITAET;
		 char    SPERRKZ[1 + 1];
		 char    LOESCHKZ[1 + 1];
		 short   POOLNR;
		 char    RUECKRUFKZ[1 + 1];
		 char    KZ_HOST[1 + 1];
		 char    TOURID[6 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPMASTER {
		 short   FILIALNR;
		 long    IDFNR;
		 long    RUFZEIT;
		 char    AKTIVMONTAG;
		 char    AKTIVDIENSTAG;
		 char    AKTIVMITTWOCH;
		 char    AKTIVDONNERSTAG;
		 char    AKTIVFREITAG;
		 char    AKTIVSAMSTAG;
		 char    AKTIVSONNTAG;
		 char    PROTOKOLLART;
		 char    VERARBEITUNGART;
		 short   PRIORITAET;
		 char    SPERRKZ;
		 char    LOESCHKZ;
		 short   POOLNR;
		 char    RUECKRUFKZ;
		 char    KZ_HOST;
		 char    TOURID[6 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPMASTER {
		 short  FILIALNR;
		 short  IDFNR;
		 short  RUFZEIT;
		 short  AKTIVMONTAG;
		 short  AKTIVDIENSTAG;
		 short  AKTIVMITTWOCH;
		 short  AKTIVDONNERSTAG;
		 short  AKTIVFREITAG;
		 short  AKTIVSAMSTAG;
		 short  AKTIVSONNTAG;
		 short  PROTOKOLLART;
		 short  VERARBEITUNGART;
		 short  PRIORITAET;
		 short  SPERRKZ;
		 short  LOESCHKZ;
		 short  POOLNR;
		 short  RUECKRUFKZ;
		 short  KZ_HOST;
		 short  TOURID;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPMASTER {
		 char    FILIALNR[7];
		 char    IDFNR[11];
		 char    RUFZEIT[11];
		 char    AKTIVMONTAG[1 + 1];
		 char    AKTIVDIENSTAG[1 + 1];
		 char    AKTIVMITTWOCH[1 + 1];
		 char    AKTIVDONNERSTAG[1 + 1];
		 char    AKTIVFREITAG[1 + 1];
		 char    AKTIVSAMSTAG[1 + 1];
		 char    AKTIVSONNTAG[1 + 1];
		 char    PROTOKOLLART[1 + 1];
		 char    VERARBEITUNGART[1 + 1];
		 char    PRIORITAET[7];
		 char    SPERRKZ[1 + 1];
		 char    LOESCHKZ[1 + 1];
		 char    POOLNR[7];
		 char    RUECKRUFKZ[1 + 1];
		 char    KZ_HOST[1 + 1];
		 char    TOURID[6 + 1];
		 char    FETCH_REL[11];
       };

 struct O_RUFPMASTER {
		 char    FILIALNR[7];
		 char    IDFNR[11];
		 char    RUFZEIT[11];
		 char    AKTIVMONTAG[1];
		 char    AKTIVDIENSTAG[1];
		 char    AKTIVMITTWOCH[1];
		 char    AKTIVDONNERSTAG[1];
		 char    AKTIVFREITAG[1];
		 char    AKTIVSAMSTAG[1];
		 char    AKTIVSONNTAG[1];
		 char    PROTOKOLLART[1];
		 char    VERARBEITUNGART[1];
		 char    PRIORITAET[7];
		 char    SPERRKZ[1];
		 char    LOESCHKZ[1];
		 char    POOLNR[7];
		 char    RUECKRUFKZ[1];
		 char    KZ_HOST[1];
		 char    TOURID[6];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPMASTER_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPMASTER_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPMASTER
 {
  public:

  RUFPMASTER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPMASTER_BES, RUFPMASTER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPMASTER_BES, RUFPMASTER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPMASTER_BES, RUFPMASTER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPMASTER()
  {
   ::buf_default((void *)&s, RUFPMASTER_BES, RUFPMASTER_ANZ);
  }
 };
#endif

#define RUFPMASTER_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR SMALLINT          ,\
		 IDFNR INTEGER           ,\
		 RUFZEIT INTEGER           ,\
		 AKTIVMONTAG CHAR(1)           ,\
		 AKTIVDIENSTAG CHAR(1)           ,\
		 AKTIVMITTWOCH CHAR(1)           ,\
		 AKTIVDONNERSTAG CHAR(1)           ,\
		 AKTIVFREITAG CHAR(1)           ,\
		 AKTIVSAMSTAG CHAR(1)           ,\
		 AKTIVSONNTAG CHAR(1)           ,\
		 PROTOKOLLART CHAR(1)           ,\
		 VERARBEITUNGART CHAR(1)           ,\
		 PRIORITAET SMALLINT          ,\
		 SPERRKZ CHAR(1)           ,\
		 LOESCHKZ CHAR(1)           ,\
		 POOLNR SMALLINT          ,\
		 RUECKRUFKZ CHAR(1)           ,\
		 KZ_HOST CHAR(1)           ,\
		 TOURID CHAR(6)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 9 LOCK MODE ROW;

#define RUFPMASTER_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_MASTERPLAN_3     on yyy( FILIALNR, IDFNR, RUFZEIT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_MASTERPLAN_2     on yyy( FILIALNR, IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define RUFPMASTER_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_MASTERPLAN_3    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_MASTERPLAN_2    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPTAG_FILIALNR             6
 #define L_RUFPTAG_IDFNR                11
 #define L_RUFPTAG_DATUM                11
 #define L_RUFPTAG_LFDAKTION            6
 #define L_RUFPTAG_PRIORITAET           6
 #define L_RUFPTAG_WOCHENTAG            2
 #define L_RUFPTAG_POOLID               6
 #define L_RUFPTAG_ANRUFART             2
 #define L_RUFPTAG_MANUELL              1
 #define L_RUFPTAG_STAGRUECKRUF         1
 #define L_RUFPTAG_TELRUECKRUFNR        15
 #define L_RUFPTAG_STATUS               6
 #define L_RUFPTAG_RUFZEITGEAENDERT     11
 #define L_RUFPTAG_BEMERKUNG            240
 #define L_RUFPTAG_NAMEAPO              40
 #define L_RUFPTAG_NAMEINHABER          30
 #define L_RUFPTAG_ORT                  30
 #define L_RUFPTAG_POSTLEITZAHL         7
 #define L_RUFPTAG_TELNR                20
 #define L_RUFPTAG_TELKURZWAHL          4
 #define L_RUFPTAG_LOESCHGRUND          6
 #define L_RUFPTAG_UID                  11
 #define L_RUFPTAG_STATUSVERBINDUNG     6
 #define L_RUFPTAG_RUFZEIT              11
 #define L_RUFPTAG_REGIONNR             6
 #define L_RUFPTAG_CALLINFO             240


 #define L_RUFPTAG_PKEY 39

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPTAG_ANZ (int) ( sizeof(RUFPTAG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPTAG sizeof(struct RUFPTAG)


 #define RUFPTAG_H

 #define RUFPTAG_LISTE \
 			TAGPLAN.FILIALNR, \
 			TAGPLAN.IDFNR, \
 			TAGPLAN.DATUM, \
 			TAGPLAN.LFDAKTION, \
 			TAGPLAN.PRIORITAET, \
 			TAGPLAN.WOCHENTAG, \
 			TAGPLAN.POOLID, \
 			TAGPLAN.ANRUFART, \
 			TAGPLAN.MANUELL, \
 			TAGPLAN.STAGRUECKRUF, \
 			TAGPLAN.TELRUECKRUFNR, \
 			TAGPLANEREIGNIS.STATUS, \
 			TAGPLANEREIGNIS.RUFZEITGEAENDERT, \
 			TAGPLANEREIGNIS.BEMERKUNG, \
 			KUNDE.NAMEAPO, \
 			KUNDE.NAMEINHABER, \
 			KUNDE.ORT, \
 			KUNDE.POSTLEITZAHL, \
 			KUNDE.TELNR, \
 			KUNDE.TELKURZWAHL, \
 			TAGPLANEREIGNIS.LOESCHGRUND, \
 			TAGPLANEREIGNIS.UID, \
 			TAGPLANEREIGNIS.STATUSVERBINDUNG, \
 			TAGPLANEREIGNIS.RUFZEIT, \
 			TAGPLANEREIGNIS.RUFZEIT, \
 			TAGPLAN.CALLINFO, \
 			REGIONARTEN.REGIONNR
 #define RUFPTAG_PLISTE \
 			"TAGPLAN.FILIALNR," \
 			"TAGPLAN.IDFNR," \
 			"TAGPLAN.DATUM," \
 			"TAGPLAN.LFDAKTION," \
 			"TAGPLAN.PRIORITAET," \
 			"TAGPLAN.WOCHENTAG," \
 			"TAGPLAN.POOLID," \
 			"TAGPLAN.ANRUFART," \
 			"TAGPLAN.MANUELL," \
 			"TAGPLAN.STAGRUECKRUF," \
 			"TAGPLAN.TELRUECKRUFNR," \
 			"TAGPLANEREIGNIS.STATUS," \
 			"TAGPLANEREIGNIS.RUFZEITGEAENDERT," \
 			"TAGPLANEREIGNIS.BEMERKUNG," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.NAMEINHABER," \
 			"KUNDE.ORT," \
 			"KUNDE.POSTLEITZAHL," \
 			"KUNDE.TELNR," \
 			"KUNDE.TELKURZWAHL," \
 			"TAGPLANEREIGNIS.LOESCHGRUND," \
 			"TAGPLANEREIGNIS.UID," \
 			"TAGPLANEREIGNIS.STATUSVERBINDUNG," \
 			"TAGPLANEREIGNIS.RUFZEIT," \
 			"TAGPLAN.CALLINFO "

 #define RUFPTAG_PELISTE \
 			"FILIALNR," \
 			"IDFNR," \
 			"DATUM," \
 			"LFDAKTION," \
 			"PRIORITAET," \
 			"WOCHENTAG," \
 			"POOLID," \
 			"ANRUFART," \
 			"MANUELL," \
 			"STAGRUECKRUF," \
 			"TELRUECKRUFNR," \
 			"STATUS," \
 			"RUFZEITGEAENDERT," \
 			"BEMERKUNG," \
 			"NAMEAPO," \
 			"NAMEINHABER," \
 			"ORT," \
 			"POSTLEITZAHL," \
 			"TELNR," \
 			"TELKURZWAHL," \
 			"LOESCHGRUND," \
 			"UID," \
 			"STATUSVERBINDUNG," \
 			"RUFZEIT," \
 			"REGIONNR," \
 			"CALLINFO "

 #define RUFPTAG_UPDLISTE \
 			"FILIALNR=?," \
 			"IDFNR=?," \
 			"DATUM=?," \
 			"LFDAKTION=?," \
 			"PRIORITAET=?," \
 			"WOCHENTAG=?," \
 			"POOLID=?," \
 			"ANRUFART=?," \
 			"MANUELL=?," \
 			"STAGRUECKRUF=?," \
 			"TELRUECKRUFNR=?," \
 			"STATUS=?," \
 			"RUFZEITGEAENDERT=?," \
 			"BEMERKUNG=?," \
 			"NAMEAPO=?," \
 			"NAMEINHABER=?," \
 			"ORT=?," \
 			"POSTLEITZAHL=?," \
 			"TELNR=?," \
 			"TELKURZWAHL=?," \
 			"LOESCHGRUND=?," \
 			"UID=?," \
 			"STATUSVERBINDUNG=?," \
 			"RUFZEIT=?," \
 			"REGIONNR," \
 			"CALLINFO=? "

 #define RUFPTAGFILIALNR                      0
 #define RUFPTAGIDFNR                         1
 #define RUFPTAGDATUM                         2
 #define RUFPTAGLFDAKTION                     3
 #define RUFPTAGPRIORITAET                    4
 #define RUFPTAGWOCHENTAG                     5
 #define RUFPTAGPOOLID                        6
 #define RUFPTAGANRUFART                      7
 #define RUFPTAGMANUELL                       8
 #define RUFPTAGSTAGRUECKRUF                  9
 #define RUFPTAGTELRUECKRUFNR                 10
 #define RUFPTAGSTATUS                        11
 #define RUFPTAGRUFZEITGEAENDERT              12
 #define RUFPTAGBEMERKUNG                     13
 #define RUFPTAGNAMEAPO                       14
 #define RUFPTAGNAMEINHABER                   15
 #define RUFPTAGORT                           16
 #define RUFPTAGPOSTLEITZAHL                  17
 #define RUFPTAGTELNR                         18
 #define RUFPTAGTELKURZWAHL                   19
 #define RUFPTAGLOESCHGRUND                   20
 #define RUFPTAGUID                           21
 #define RUFPTAGSTATUSVERBINDUNG              22
 #define RUFPTAGRUFZEIT                       23
 #define RUFPTAGREGIONNR                      24
 #define RUFPTAGCALLINFO                      25

 #define RUFPTAG_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->IDFNR,\
 			:xxx->DATUM,\
 			:xxx->LFDAKTION,\
 			:xxx->PRIORITAET,\
 			:xxx->WOCHENTAG,\
 			:xxx->POOLID,\
 			:xxx->ANRUFART,\
 			:xxx->MANUELL,\
 			:xxx->STAGRUECKRUF,\
 			:xxx->TELRUECKRUFNR,\
 			:xxx->STATUS,\
 			:xxx->RUFZEITGEAENDERT,\
 			:xxx->BEMERKUNG,\
 			:xxx->NAMEAPO,\
 			:xxx->NAMEINHABER,\
 			:xxx->ORT,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->TELNR,\
 			:xxx->TELKURZWAHL,\
 			:xxx->LOESCHGRUND,\
 			:xxx->UID,\
 			:xxx->STATUSVERBINDUNG,\
 			:xxx->RUFZEIT,\
 			:xxx->CALLINFO

 #define RUFPTAG_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			IDFNR = :xxx->IDFNR,\
 			DATUM = :xxx->DATUM,\
 			LFDAKTION = :xxx->LFDAKTION,\
 			PRIORITAET = :xxx->PRIORITAET,\
 			WOCHENTAG = :xxx->WOCHENTAG,\
 			POOLID = :xxx->POOLID,\
 			ANRUFART = :xxx->ANRUFART,\
 			MANUELL = :xxx->MANUELL,\
 			STAGRUECKRUF = :xxx->STAGRUECKRUF,\
 			TELRUECKRUFNR = :xxx->TELRUECKRUFNR,\
 			STATUS = :xxx->STATUS,\
 			RUFZEITGEAENDERT = :xxx->RUFZEITGEAENDERT,\
 			BEMERKUNG = :xxx->BEMERKUNG,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			NAMEINHABER = :xxx->NAMEINHABER,\
 			ORT = :xxx->ORT,\
 			POSTLEITZAHL = :xxx->POSTLEITZAHL,\
 			TELNR = :xxx->TELNR,\
 			TELKURZWAHL = :xxx->TELKURZWAHL,\
 			LOESCHGRUND = :xxx->LOESCHGRUND,\
 			UID = :xxx->UID,\
 			STATUSVERBINDUNG = :xxx->STATUSVERBINDUNG,\
 			RUFZEIT = :xxx->RUFZEIT,\
 			REGIONNR = :xxx->REGIONNR,\
 			CALLINFO = :xxx->CALLINFO

 #define LS_RUFPTAG_FILIALNR             7
 #define LS_RUFPTAG_IDFNR                11
 #define LS_RUFPTAG_DATUM                11
 #define LS_RUFPTAG_LFDAKTION            7
 #define LS_RUFPTAG_PRIORITAET           7
 #define LS_RUFPTAG_WOCHENTAG            3
 #define LS_RUFPTAG_POOLID               7
 #define LS_RUFPTAG_ANRUFART             3
 #define LS_RUFPTAG_MANUELL              2
 #define LS_RUFPTAG_STAGRUECKRUF         2
 #define LS_RUFPTAG_TELRUECKRUFNR        16
 #define LS_RUFPTAG_STATUS               7
 #define LS_RUFPTAG_RUFZEITGEAENDERT     11
 #define LS_RUFPTAG_BEMERKUNG            241
 #define LS_RUFPTAG_NAMEAPO              41
 #define LS_RUFPTAG_NAMEINHABER          31
 #define LS_RUFPTAG_ORT                  31
 #define LS_RUFPTAG_POSTLEITZAHL         8
 #define LS_RUFPTAG_TELNR                21
 #define LS_RUFPTAG_TELKURZWAHL          5
 #define LS_RUFPTAG_LOESCHGRUND          7
 #define LS_RUFPTAG_UID                  11
 #define LS_RUFPTAG_STATUSVERBINDUNG     7
 #define LS_RUFPTAG_RUFZEIT              11
 #define LS_RUFPTAG_REGIONNR             7
 #define LS_RUFPTAG_CALLINFO             241
 #define LS_RUFPTAG_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPTAG {
		 short   FILIALNR;
		 long    IDFNR;
		 long    DATUM;
		 short   LFDAKTION;
		 short   PRIORITAET;
		 char    WOCHENTAG[2 + 1];
		 short   POOLID;
		 char    ANRUFART[2 + 1];
		 char    MANUELL[1 + 1];
		 char    STAGRUECKRUF[1 + 1];
		 char    TELRUECKRUFNR[15 + 1];
		 short   STATUS;
		 long    RUFZEITGEAENDERT;
		 char    BEMERKUNG[240 + 1];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 short   LOESCHGRUND;
		 long    UID;
		 short   STATUSVERBINDUNG;
		 long    RUFZEIT;
		 short   REGIONNR;
		 char    CALLINFO[240 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPTAG {
		 short   FILIALNR;
		 long    IDFNR;
		 long    DATUM;
		 short   LFDAKTION;
		 short   PRIORITAET;
		 char    WOCHENTAG[2 + 1];
		 short   POOLID;
		 char    ANRUFART[2 + 1];
		 char    MANUELL;
		 char    STAGRUECKRUF;
		 char    TELRUECKRUFNR[15 + 1];
		 short   STATUS;
		 long    RUFZEITGEAENDERT;
		 char    BEMERKUNG[240 + 1];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 short   LOESCHGRUND;
		 long    UID;
		 short   STATUSVERBINDUNG;
		 long    RUFZEIT;
		 short   REGIONNR;
		 char    CALLINFO[240 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPTAG {
		 short  FILIALNR;
		 short  IDFNR;
		 short  DATUM;
		 short  LFDAKTION;
		 short  PRIORITAET;
		 short  WOCHENTAG;
		 short  POOLID;
		 short  ANRUFART;
		 short  MANUELL;
		 short  STAGRUECKRUF;
		 short  TELRUECKRUFNR;
		 short  STATUS;
		 short  RUFZEITGEAENDERT;
		 short  BEMERKUNG;
		 short  NAMEAPO;
		 short  NAMEINHABER;
		 short  ORT;
		 short  POSTLEITZAHL;
		 short  TELNR;
		 short  TELKURZWAHL;
		 short  LOESCHGRUND;
		 short  UID;
		 short  STATUSVERBINDUNG;
		 short  RUFZEIT;
		 short  REGIONNR;
		 short  CALLINFO;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPTAG {
		 char    FILIALNR[7];
		 char    IDFNR[11];
		 char    DATUM[11];
		 char    LFDAKTION[7];
		 char    PRIORITAET[7];
		 char    WOCHENTAG[2 + 1];
		 char    POOLID[7];
		 char    ANRUFART[2 + 1];
		 char    MANUELL[1 + 1];
		 char    STAGRUECKRUF[1 + 1];
		 char    TELRUECKRUFNR[15 + 1];
		 char    STATUS[7];
		 char    RUFZEITGEAENDERT[11];
		 char    BEMERKUNG[240 + 1];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    LOESCHGRUND[7];
		 char    UID[11];
		 char    STATUSVERBINDUNG[7];
		 char    RUFZEIT[11];
		 char    REGIONNR[7];
		 char    CALLINFO[240 + 1];
		 char    FETCH_REL[11];
       };

 struct O_RUFPTAG {
		 char    FILIALNR[7];
		 char    IDFNR[11];
		 char    DATUM[11];
		 char    LFDAKTION[7];
		 char    PRIORITAET[7];
		 char    WOCHENTAG[2];
		 char    POOLID[7];
		 char    ANRUFART[2];
		 char    MANUELL[1];
		 char    STAGRUECKRUF[1];
		 char    TELRUECKRUFNR[15];
		 char    STATUS[7];
		 char    RUFZEITGEAENDERT[11];
		 char    BEMERKUNG[240];
		 char    NAMEAPO[40];
		 char    NAMEINHABER[30];
		 char    ORT[30];
		 char    POSTLEITZAHL[7];
		 char    TELNR[20];
		 char    TELKURZWAHL[4];
		 char    LOESCHGRUND[7];
		 char    UID[11];
		 char    STATUSVERBINDUNG[7];
		 char    RUFZEIT[11];
		 char    REGIONNR[7];
		 char    CALLINFO[240];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPTAG_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPTAG_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   15 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPTAG
 {
  public:

  RUFPTAG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPTAG_BES, RUFPTAG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPTAG_BES, RUFPTAG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPTAG_BES, RUFPTAG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPTAG()
  {
   ::buf_default((void *)&s, RUFPTAG_BES, RUFPTAG_ANZ);
  }
 };
#endif

#define RUFPTAG_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR SMALLINT          ,\
		 IDFNR INTEGER           ,\
		 DATUM INTEGER           ,\
		 LFDAKTION SMALLINT          ,\
		 PRIORITAET SMALLINT          ,\
		 WOCHENTAG CHAR(2)           ,\
		 POOLID SMALLINT          ,\
		 ANRUFART CHAR(2)           ,\
		 MANUELL CHAR(1)           ,\
		 STAGRUECKRUF CHAR(1)           ,\
		 TELRUECKRUFNR CHAR(15)          ,\
		 STATUS SMALLINT          ,\
		 RUFZEITGEAENDERT INTEGER           ,\
		 BEMERKUNG VARCHAR(240,0)    ,\
		 NAMEAPO CHAR(40)          ,\
		 NAMEINHABER CHAR(30)          ,\
		 ORT CHAR(30)          ,\
		 POSTLEITZAHL CHAR(7)           ,\
		 TELNR CHAR(20)          ,\
		 TELKURZWAHL CHAR(4)           ,\
		 LOESCHGRUND SMALLINT          ,\
		 UID INTEGER           ,\
		 STATUSVERBINDUNG SMALLINT          ,\
		 RUFZEIT INTEGER           ,\
		 REGIONNR SMALLINT          ,\
		 CALLINFO VARCHAR(240,0)    ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 342 LOCK MODE ROW;

#define RUFPTAG_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_TAGPLAN_1        on yyy( FILIALNR, IDFNR, DATUM, RUFZEIT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define RUFPTAG_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_TAGPLAN_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPTAGINF_DATUM                11
 #define L_RUFPTAGINF_RUFZEIT              11
 #define L_RUFPTAGINF_IDFNR                11
 #define L_RUFPTAGINF_STATUS               6
 #define L_RUFPTAGINF_STATUSANRUFSATZ      6
 #define L_RUFPTAGINF_STATUSVERBINDUNG     6
 #define L_RUFPTAGINF_LOESCHGRUND          6
 #define L_RUFPTAGINF_RUFZEITGEAENDERT     11
 #define L_RUFPTAGINF_ZEIT                 11
 #define L_RUFPTAGINF_BEMERKUNG            240
 #define L_RUFPTAGINF_USERNAME             8
 #define L_RUFPTAGINF_FILIALNR             6


 #define L_RUFPTAGINF_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPTAGINF_ANZ (int) ( sizeof(RUFPTAGINF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPTAGINF sizeof(struct RUFPTAGINF)


 #define RUFPTAGINF_H

 #define RUFPTAGINF_LISTE \
 			TAGPLANEREIGNIS.DATUM, \
 			TAGPLANEREIGNIS.RUFZEIT, \
 			TAGPLANEREIGNIS.IDFNR, \
 			TAGPLANEREIGNIS.STATUS, \
 			TAGPLANEREIGNIS.STATUSANRUFSATZ, \
 			TAGPLANEREIGNIS.STATUSVERBINDUNG, \
 			TAGPLANEREIGNIS.LOESCHGRUND, \
 			TAGPLANEREIGNIS.RUFZEITGEAENDERT, \
 			TAGPLANEREIGNIS.ZEIT, \
 			TAGPLANEREIGNIS.BEMERKUNG, \
 			PASSWD.USERNAME, \
			TAGPLANEREIGNIS.FILIALNR
 #define RUFPTAGINF_PLISTE \
 			"TAGPLANEREIGNIS.DATUM," \
 			"TAGPLANEREIGNIS.RUFZEIT," \
 			"TAGPLANEREIGNIS.IDFNR," \
 			"TAGPLANEREIGNIS.STATUS," \
 			"TAGPLANEREIGNIS.STATUSANRUFSATZ," \
 			"TAGPLANEREIGNIS.STATUSVERBINDUNG," \
 			"TAGPLANEREIGNIS.LOESCHGRUND," \
 			"TAGPLANEREIGNIS.RUFZEITGEAENDERT," \
 			"TAGPLANEREIGNIS.ZEIT," \
 			"TAGPLANEREIGNIS.BEMERKUNG," \
 			"PASSWD.USERNAME," \
			"TAGPLANEREIGNIS.FILIALNR "

 #define RUFPTAGINF_PELISTE \
 			"DATUM," \
 			"RUFZEIT," \
 			"IDFNR," \
 			"STATUS," \
 			"STATUSANRUFSATZ," \
 			"STATUSVERBINDUNG," \
 			"LOESCHGRUND," \
 			"RUFZEITGEAENDERT," \
 			"ZEIT," \
 			"BEMERKUNG," \
 			"USERNAME," \
			"FILIALNR "

 #define RUFPTAGINF_UPDLISTE \
 			"DATUM=?," \
 			"RUFZEIT=?," \
 			"IDFNR=?," \
 			"STATUS=?," \
 			"STATUSANRUFSATZ=?," \
 			"STATUSVERBINDUNG=?," \
 			"LOESCHGRUND=?," \
 			"RUFZEITGEAENDERT=?," \
 			"ZEIT=?," \
 			"BEMERKUNG=?," \
 			"USERNAME=?," \
			"FILIALNR=? "

 #define RUFPTAGINFDATUM                         0
 #define RUFPTAGINFRUFZEIT                       1
 #define RUFPTAGINFIDFNR                         2
 #define RUFPTAGINFSTATUS                        3
 #define RUFPTAGINFSTATUSANRUFSATZ               4
 #define RUFPTAGINFSTATUSVERBINDUNG              5
 #define RUFPTAGINFLOESCHGRUND                   6
 #define RUFPTAGINFRUFZEITGEAENDERT              7
 #define RUFPTAGINFZEIT                          8
 #define RUFPTAGINFBEMERKUNG                     9
 #define RUFPTAGINFUSERNAME                      10
 #define RUFPTAGINFFILIALNR						 11

 #define RUFPTAGINF_ZEIGER(xxx) \
 			:xxx->DATUM,\
 			:xxx->RUFZEIT,\
 			:xxx->IDFNR,\
 			:xxx->STATUS,\
 			:xxx->STATUSANRUFSATZ,\
 			:xxx->STATUSVERBINDUNG,\
 			:xxx->LOESCHGRUND,\
 			:xxx->RUFZEITGEAENDERT,\
 			:xxx->ZEIT,\
 			:xxx->BEMERKUNG,\
 			:xxx->USERNAME,\
			:xxx->FILIALNR

 #define RUFPTAGINF_UPDATE(xxx) \
 			DATUM = :xxx->DATUM,\
 			RUFZEIT = :xxx->RUFZEIT,\
 			IDFNR = :xxx->IDFNR,\
 			STATUS = :xxx->STATUS,\
 			STATUSANRUFSATZ = :xxx->STATUSANRUFSATZ,\
 			STATUSVERBINDUNG = :xxx->STATUSVERBINDUNG,\
 			LOESCHGRUND = :xxx->LOESCHGRUND,\
 			RUFZEITGEAENDERT = :xxx->RUFZEITGEAENDERT,\
 			ZEIT = :xxx->ZEIT,\
 			BEMERKUNG = :xxx->BEMERKUNG,\
 			USERNAME = :xxx->USERNAME,\
			FILIALNR = :xxx->FILIALNR

 #define LS_RUFPTAGINF_DATUM                11
 #define LS_RUFPTAGINF_RUFZEIT              11
 #define LS_RUFPTAGINF_IDFNR                11
 #define LS_RUFPTAGINF_STATUS               7
 #define LS_RUFPTAGINF_STATUSANRUFSATZ      7
 #define LS_RUFPTAGINF_STATUSVERBINDUNG     7
 #define LS_RUFPTAGINF_LOESCHGRUND          7
 #define LS_RUFPTAGINF_RUFZEITGEAENDERT     11
 #define LS_RUFPTAGINF_ZEIT                 11
 #define LS_RUFPTAGINF_BEMERKUNG            241
 #define LS_RUFPTAGINF_USERNAME             9
 #define LS_RUFPTAGINF_FILIALNR				7
 #define LS_RUFPTAGINF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPTAGINF {
		 long    DATUM;
		 long    RUFZEIT;
		 long    IDFNR;
		 short   STATUS;
		 short   STATUSANRUFSATZ;
		 short   STATUSVERBINDUNG;
		 short   LOESCHGRUND;
		 long    RUFZEITGEAENDERT;
		 long    ZEIT;
		 char    BEMERKUNG[240 + 1];
		 char    USERNAME[8 + 1];
		 short	 FILIALNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPTAGINF {
		 long    DATUM;
		 long    RUFZEIT;
		 long    IDFNR;
		 short   STATUS;
		 short   STATUSANRUFSATZ;
		 short   STATUSVERBINDUNG;
		 short   LOESCHGRUND;
		 long    RUFZEITGEAENDERT;
		 long    ZEIT;
		 char    BEMERKUNG[240 + 1];
		 char    USERNAME[8 + 1];
		 short	 FILIALNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPTAGINF {
		 short  DATUM;
		 short  RUFZEIT;
		 short  IDFNR;
		 short  STATUS;
		 short  STATUSANRUFSATZ;
		 short  STATUSVERBINDUNG;
		 short  LOESCHGRUND;
		 short  RUFZEITGEAENDERT;
		 short  ZEIT;
		 short  BEMERKUNG;
		 short  USERNAME;
		 short	FILIALNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPTAGINF {
		 char    DATUM[11];
		 char    RUFZEIT[11];
		 char    IDFNR[11];
		 char    STATUS[7];
		 char    STATUSANRUFSATZ[7];
		 char    STATUSVERBINDUNG[7];
		 char    LOESCHGRUND[7];
		 char    RUFZEITGEAENDERT[11];
		 char    ZEIT[11];
		 char    BEMERKUNG[240 + 1];
		 char    USERNAME[8 + 1];
		 char	 FILIALNR[7];
		 char    FETCH_REL[11];
       };

 struct O_RUFPTAGINF {
		 char    DATUM[11];
		 char    RUFZEIT[11];
		 char    IDFNR[11];
		 char    STATUS[7];
		 char    STATUSANRUFSATZ[7];
		 char    STATUSVERBINDUNG[7];
		 char    LOESCHGRUND[7];
		 char    RUFZEITGEAENDERT[11];
		 char    ZEIT[11];
		 char    BEMERKUNG[240];
		 char    USERNAME[8];
		 char	 FILIALNR[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPTAGINF_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPTAGINF_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPTAGINF
 {
  public:

  RUFPTAGINF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPTAGINF_BES, RUFPTAGINF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPTAGINF_BES, RUFPTAGINF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPTAGINF_BES, RUFPTAGINF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPTAGINF()
  {
   ::buf_default((void *)&s, RUFPTAGINF_BES, RUFPTAGINF_ANZ);
  }
 };
#endif

#define RUFPTAGINF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 DATUM INTEGER           ,\
		 RUFZEIT INTEGER           ,\
		 IDFNR INTEGER           ,\
		 STATUS SMALLINT          ,\
		 STATUSANRUFSATZ SMALLINT          ,\
		 STATUSVERBINDUNG SMALLINT          ,\
		 LOESCHGRUND SMALLINT          ,\
		 RUFZEITGEAENDERT INTEGER           ,\
		 ZEIT INTEGER           ,\
		 BEMERKUNG VARCHAR(240,0)    ,\
		 USERNAME CHAR(8)           ,\
		 FILIALNR SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 388 LOCK MODE ROW;

#define RUFPTAGINF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_TAGPLANEREIGNI_1 on yyy( DATUM, RUFZEIT, IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define RUFPTAGINF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_TAGPLANEREIGNI_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPTAGSUM_DATUM                11
 #define L_RUFPTAGSUM_SUMMEOFFEN           11
 #define L_RUFPTAGSUM_SUMMEERLEDIGT        11
 #define L_RUFPTAGSUM_SUMMEGELOESCHT       11
 #define L_RUFPTAGSUM_FILIALNR		       6


 #define L_RUFPTAGSUM_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPTAGSUM_ANZ (int) ( sizeof(RUFPTAGSUM_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPTAGSUM sizeof(struct RUFPTAGSUM)


 #define RUFPTAGSUM_H

 #define RUFPTAGSUM_LISTE \
 			AADUMMY.DATUM, \
 			AADUMMY.SUMMEOFFEN, \
 			AADUMMY.SUMMEERLEDIGT, \
 			AADUMMY.SUMMEGELOESCHT, \
			TAGPLANEREIGNIS.FILIALNR
 #define RUFPTAGSUM_PLISTE \
 			"AADUMMY.DATUM," \
 			"AADUMMY.SUMMEOFFEN," \
 			"AADUMMY.SUMMEERLEDIGT," \
 			"AADUMMY.SUMMEGELOESCHT," \
			"TAGPLANEREIGNIS.FILIALNR "

 #define RUFPTAGSUM_PELISTE \
 			"DATUM," \
 			"SUMMEOFFEN," \
 			"SUMMEERLEDIGT," \
 			"SUMMEGELOESCHT," \
			"TAGPLANEREIGNIS.FILIALNR "

 #define RUFPTAGSUM_UPDLISTE \
 			"DATUM=?," \
 			"SUMMEOFFEN=?," \
 			"SUMMEERLEDIGT=?," \
 			"SUMMEGELOESCHT=?," \
			"FILIALNR=? "

 #define RUFPTAGSUMDATUM                         0
 #define RUFPTAGSUMSUMMEOFFEN                    1
 #define RUFPTAGSUMSUMMEERLEDIGT                 2
 #define RUFPTAGSUMSUMMEGELOESCHT                3
 #define RUFPTAGSUMFILIALNR						 4

 #define RUFPTAGSUM_ZEIGER(xxx) \
 			:xxx->DATUM,\
 			:xxx->SUMMEOFFEN,\
 			:xxx->SUMMEERLEDIGT,\
 			:xxx->SUMMEGELOESCHT,\
 			:xxx->FILIALNR

 #define RUFPTAGSUM_UPDATE(xxx) \
 			DATUM = :xxx->DATUM,\
 			SUMMEOFFEN = :xxx->SUMMEOFFEN,\
 			SUMMEERLEDIGT = :xxx->SUMMEERLEDIGT,\
 			SUMMEGELOESCHT = :xxx->SUMMEGELOESCHT,\
 			FILIALNR = :xxx->FILIALNR

 #define LS_RUFPTAGSUM_DATUM                11
 #define LS_RUFPTAGSUM_SUMMEOFFEN           11
 #define LS_RUFPTAGSUM_SUMMEERLEDIGT        11
 #define LS_RUFPTAGSUM_SUMMEGELOESCHT       11
 #define LS_RUFPTAGSUM_FILIALNR		        7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPTAGSUM {
		 long    DATUM;
		 long    SUMMEOFFEN;
		 long    SUMMEERLEDIGT;
		 long    SUMMEGELOESCHT;
 		 short	 FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPTAGSUM {
		 long    DATUM;
		 long    SUMMEOFFEN;
		 long    SUMMEERLEDIGT;
		 long    SUMMEGELOESCHT;
 		 short	 FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPTAGSUM {
		 short  DATUM;
		 short  SUMMEOFFEN;
		 short  SUMMEERLEDIGT;
		 short  SUMMEGELOESCHT;
 		 short	FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPTAGSUM {
		 char    DATUM[11];
		 char    SUMMEOFFEN[11];
		 char    SUMMEERLEDIGT[11];
		 char    SUMMEGELOESCHT[11];
 		 char	 FILIALNR[7];
       };

 struct O_RUFPTAGSUM {
		 char    DATUM[11];
		 char    SUMMEOFFEN[11];
		 char    SUMMEERLEDIGT[11];
		 char    SUMMEGELOESCHT[11];
 		 char	 FILIALNR[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPTAGSUM_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPTAGSUM_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPTAGSUM
 {
  public:

  RUFPTAGSUM s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPTAGSUM_BES, RUFPTAGSUM_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPTAGSUM_BES, RUFPTAGSUM_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPTAGSUM_BES, RUFPTAGSUM_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPTAGSUM()
  {
   ::buf_default((void *)&s, RUFPTAGSUM_BES, RUFPTAGSUM_ANZ);
  }
 };
#endif

#define RUFPTAGSUM_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 DATUM INTEGER           ,\
		 SUMMEOFFEN INTEGER           ,\
		 SUMMEERLEDIGT INTEGER           ,\
		 SUMMEGELOESCHT INTEGER            ,\
		 FILIALNR SMALLINT             ) EXTENT SIZE 316 LOCK MODE ROW;

#define RUFPTAGSUM_CREATE_INDEX(yyy,xxx) \

#define RUFPTAGSUM_DELETE_INDEX(xxx) \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPTAGTOUR_IDFNR                11
 #define L_RUFPTAGTOUR_DATUMKOMMI           11
 #define L_RUFPTAGTOUR_TOURID               6
 #define L_RUFPTAGTOUR_VERTRIEBSZENTRUMNR   6


 #define L_RUFPTAGTOUR_PKEY 28

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPTAGTOUR_ANZ (int) ( sizeof(RUFPTAGTOUR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPTAGTOUR sizeof(struct RUFPTAGTOUR)


 #define RUFPTAGTOUR_H

 #define RUFPTAGTOUR_LISTE \
 			TOURPLANTAG.IDFNR, \
 			TOURPLANTAG.DATUMKOMMI, \
 			TOURPLANTAG.TOURID, \
 			TOURPLANTAG.VERTRIEBSZENTRUMNR
 #define RUFPTAGTOUR_PLISTE \
 			"TOURPLANTAG.IDFNR," \
 			"TOURPLANTAG.DATUMKOMMI," \
 			"TOURPLANTAG.TOURID," \
 			"TOURPLANTAG.VERTRIEBSZENTRUMNR "

 #define RUFPTAGTOUR_PELISTE \
 			"IDFNR," \
 			"DATUMKOMMI," \
 			"TOURID," \
 			"VERTRIEBSZENTRUMNR "

 #define RUFPTAGTOUR_UPDLISTE \
 			"IDFNR=?," \
 			"DATUMKOMMI=?," \
 			"TOURID=?," \
 			"VERTRIEBSZENTRUMNR=? "

 #define RUFPTAGTOURIDFNR                         0
 #define RUFPTAGTOURDATUMKOMMI                    1
 #define RUFPTAGTOURTOURID                        2
 #define RUFPTAGTOURVERTRIEBSZENTRUMNR			  3

 #define RUFPTAGTOUR_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->DATUMKOMMI,\
 			:xxx->TOURID,\
 			:xxx->VERTRIEBSZENTRUMNR

 #define RUFPTAGTOUR_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			DATUMKOMMI = :xxx->DATUMKOMMI,\
 			TOURID = :xxx->TOURID,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR

 #define LS_RUFPTAGTOUR_IDFNR                11
 #define LS_RUFPTAGTOUR_DATUMKOMMI           11
 #define LS_RUFPTAGTOUR_TOURID               7
 #define LS_RUFPTAGTOUR_VERTRIEBSZENTRUMNR   7
 #define LS_RUFPTAGTOUR_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPTAGTOUR {
		 long    IDFNR;
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 short	 VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPTAGTOUR {
		 long    IDFNR;
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 short	 VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPTAGTOUR {
		 short  IDFNR;
		 short  DATUMKOMMI;
		 short  TOURID;
		 short	VERTRIEBSZENTRUMNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPTAGTOUR {
		 char    IDFNR[11];
		 char    DATUMKOMMI[11];
		 char    TOURID[6 + 1];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

 struct O_RUFPTAGTOUR {
		 char    IDFNR[11];
		 char    DATUMKOMMI[11];
		 char    TOURID[6];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPTAGTOUR_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPTAGTOUR_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPTAGTOUR
 {
  public:

  RUFPTAGTOUR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPTAGTOUR_BES, RUFPTAGTOUR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPTAGTOUR_BES, RUFPTAGTOUR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPTAGTOUR_BES, RUFPTAGTOUR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPTAGTOUR()
  {
   ::buf_default((void *)&s, RUFPTAGTOUR_BES, RUFPTAGTOUR_ANZ);
  }
 };
#endif

#define RUFPTAGTOUR_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 DATUMKOMMI INTEGER           ,\
		 TOURID CHAR(6)           ,\
		 VERTRIEBSZENTRUMNR SMALLINT           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 224 LOCK MODE ROW;

#define RUFPTAGTOUR_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX TOURPLANTAGX       on yyy( IDFNR, DATUMKOMMI, TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define RUFPTAGTOUR_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX TOURPLANTAGX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_RUFPTAGVOR_NUMMERTYP            6
 #define L_RUFPTAGVOR_NUMMERWERT           11
 #define L_RUFPTAGVOR_NUMMERMINDEST        11
 #define L_RUFPTAGVOR_NUMMERHOECHST        11


 #define L_RUFPTAGVOR_PKEY 6

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define RUFPTAGVOR_ANZ (int) ( sizeof(RUFPTAGVOR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_RUFPTAGVOR sizeof(struct RUFPTAGVOR)


 #define RUFPTAGVOR_H

 #define RUFPTAGVOR_LISTE \
 			NUMMER.NUMMERTYP, \
 			NUMMER.NUMMERWERT, \
 			NUMMER.NUMMERMINDEST, \
 			NUMMER.NUMMERHOECHST
 #define RUFPTAGVOR_PLISTE \
 			"NUMMER.NUMMERTYP," \
 			"NUMMER.NUMMERWERT," \
 			"NUMMER.NUMMERMINDEST," \
 			"NUMMER.NUMMERHOECHST " 

 #define RUFPTAGVOR_PELISTE \
 			"NUMMERTYP," \
 			"NUMMERWERT," \
 			"NUMMERMINDEST," \
 			"NUMMERHOECHST " 

 #define RUFPTAGVOR_UPDLISTE \
 			"NUMMERTYP=?," \
 			"NUMMERWERT=?," \
 			"NUMMERMINDEST=?," \
 			"NUMMERHOECHST=? " 

 #define RUFPTAGVORNUMMERTYP                     0
 #define RUFPTAGVORNUMMERWERT                    1
 #define RUFPTAGVORNUMMERMINDEST                 2
 #define RUFPTAGVORNUMMERHOECHST                 3

 #define RUFPTAGVOR_ZEIGER(xxx) \
 			:xxx->NUMMERTYP,\
 			:xxx->NUMMERWERT,\
 			:xxx->NUMMERMINDEST,\
 			:xxx->NUMMERHOECHST

 #define RUFPTAGVOR_UPDATE(xxx) \
 			NUMMERTYP = :xxx->NUMMERTYP,\
 			NUMMERWERT = :xxx->NUMMERWERT,\
 			NUMMERMINDEST = :xxx->NUMMERMINDEST,\
 			NUMMERHOECHST = :xxx->NUMMERHOECHST

 #define LS_RUFPTAGVOR_NUMMERTYP            7
 #define LS_RUFPTAGVOR_NUMMERWERT           11
 #define LS_RUFPTAGVOR_NUMMERMINDEST        11
 #define LS_RUFPTAGVOR_NUMMERHOECHST        11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct RUFPTAGVOR {
		 short   NUMMERTYP;
		 long    NUMMERWERT;
		 long    NUMMERMINDEST;
		 long    NUMMERHOECHST;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_RUFPTAGVOR {
		 short   NUMMERTYP;
		 long    NUMMERWERT;
		 long    NUMMERMINDEST;
		 long    NUMMERHOECHST;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_RUFPTAGVOR {
		 short  NUMMERTYP;
		 short  NUMMERWERT;
		 short  NUMMERMINDEST;
		 short  NUMMERHOECHST;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_RUFPTAGVOR {
		 char    NUMMERTYP[7];
		 char    NUMMERWERT[11];
		 char    NUMMERMINDEST[11];
		 char    NUMMERHOECHST[11];
       };

 struct O_RUFPTAGVOR {
		 char    NUMMERTYP[7];
		 char    NUMMERWERT[11];
		 char    NUMMERMINDEST[11];
		 char    NUMMERHOECHST[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc RUFPTAGVOR_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RUFPTAGVOR_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CRUFPTAGVOR
 {
  public:

  RUFPTAGVOR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFPTAGVOR_BES, RUFPTAGVOR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFPTAGVOR_BES, RUFPTAGVOR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFPTAGVOR_BES, RUFPTAGVOR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFPTAGVOR()
  {
   ::buf_default((void *)&s, RUFPTAGVOR_BES, RUFPTAGVOR_ANZ);
  }
 };
#endif

#define RUFPTAGVOR_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 NUMMERTYP SMALLINT          ,\
		 NUMMERWERT INTEGER           ,\
		 NUMMERMINDEST INTEGER           ,\
		 NUMMERHOECHST INTEGER             ) EXTENT SIZE 10 LOCK MODE ROW;

#define RUFPTAGVOR_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX IDXNUMMER          on yyy( NUMMERTYP );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define RUFPTAGVOR_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX IDXNUMMER         ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

