/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ZEITARTEN_LFDNR                11
 #define L_ZEITARTEN_ZEITART              11
 #define L_ZEITARTEN_ZEITSCHLUESSEL       16
 #define L_ZEITARTEN_TAGESTYP             6
 #define L_ZEITARTEN_ZEITBEGIN            11
 #define L_ZEITARTEN_ZEITENDE             11
 #define L_ZEITARTEN_ZEITZUSATZ           1
 #define L_ZEITARTEN_KZUPD                1
 #define L_ZEITARTEN_VERTRIEBSZENTRUMNR   6
 #define L_ZEITARTEN_WEEKDAY              6


 #define L_ZEITARTEN_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ZEITARTEN_ANZ ( sizeof(ZEITARTEN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ZEITARTEN sizeof(struct ZEITARTEN)


 #define ZEITARTEN_H

 #define ZEITARTEN_LISTE \
 			ZEITARTEN.LFDNR, \
 			ZEITARTEN.ZEITART, \
 			ZEITARTEN.ZEITSCHLUESSEL, \
 			ZEITARTEN.TAGESTYP, \
 			ZEITARTEN.ZEITBEGIN, \
 			ZEITARTEN.ZEITENDE, \
 			ZEITARTEN.ZEITZUSATZ, \
 			ZEITARTEN.KZUPD, \
 			ZEITARTEN.VERTRIEBSZENTRUMNR, \
 			ZEITARTEN.WEEKDAY
 #define ZEITARTEN_PLISTE \
 			"ZEITARTEN.LFDNR," \
 			"ZEITARTEN.ZEITART," \
 			"ZEITARTEN.ZEITSCHLUESSEL," \
 			"ZEITARTEN.TAGESTYP," \
 			"ZEITARTEN.ZEITBEGIN," \
 			"ZEITARTEN.ZEITENDE," \
 			"ZEITARTEN.ZEITZUSATZ," \
 			"ZEITARTEN.KZUPD," \
 			"ZEITARTEN.VERTRIEBSZENTRUMNR," \
 			"ZEITARTEN.WEEKDAY "

 #define ZEITARTEN_PELISTE \
 			"LFDNR," \
 			"ZEITART," \
 			"ZEITSCHLUESSEL," \
 			"TAGESTYP," \
 			"ZEITBEGIN," \
 			"ZEITENDE," \
 			"ZEITZUSATZ," \
 			"KZUPD," \
 			"VERTRIEBSZENTRUMNR," \
 			"WEEKDAY "

 #define ZEITARTEN_UPDLISTE \
 			"LFDNR=?," \
 			"ZEITART=?," \
 			"ZEITSCHLUESSEL=?," \
 			"TAGESTYP=?," \
 			"ZEITBEGIN=?," \
 			"ZEITENDE=?," \
 			"ZEITZUSATZ=?," \
 			"KZUPD=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"WEEKDAY=? "

 #define ZEITARTENLFDNR                         0
 #define ZEITARTENZEITART                       1
 #define ZEITARTENZEITSCHLUESSEL                2
 #define ZEITARTENTAGESTYP                      3
 #define ZEITARTENZEITBEGIN                     4
 #define ZEITARTENZEITENDE                      5
 #define ZEITARTENZEITZUSATZ                    6
 #define ZEITARTENKZUPD                         7
 #define ZEITARTENVERTRIEBSZENTRUMNR            8
 #define ZEITARTENWEEKDAY                       9

 #define ZEITARTEN_ZEIGER(xxx) \
 			:xxx->LFDNR,\
 			:xxx->ZEITART,\
 			:xxx->ZEITSCHLUESSEL,\
 			:xxx->TAGESTYP,\
 			:xxx->ZEITBEGIN,\
 			:xxx->ZEITENDE,\
 			:xxx->ZEITZUSATZ,\
 			:xxx->KZUPD

 #define ZEITARTEN_UPDATE(xxx) \
 			LFDNR = :xxx->LFDNR,\
 			ZEITART = :xxx->ZEITART,\
 			ZEITSCHLUESSEL = :xxx->ZEITSCHLUESSEL,\
 			TAGESTYP = :xxx->TAGESTYP,\
 			ZEITBEGIN = :xxx->ZEITBEGIN,\
 			ZEITENDE = :xxx->ZEITENDE,\
 			ZEITZUSATZ = :xxx->ZEITZUSATZ,\
 			KZUPD = :xxx->KZUPD,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			WEEKDAY = :xxx->WEEKDAY

 #define LS_ZEITARTEN_LFDNR                11
 #define LS_ZEITARTEN_ZEITART              11
 #define LS_ZEITARTEN_ZEITSCHLUESSEL       17
 #define LS_ZEITARTEN_TAGESTYP             7
 #define LS_ZEITARTEN_ZEITBEGIN            11
 #define LS_ZEITARTEN_ZEITENDE             11
 #define LS_ZEITARTEN_ZEITZUSATZ           2
 #define LS_ZEITARTEN_KZUPD                2
 #define LS_ZEITARTEN_VERTRIEBSZENTRUMNR   7
 #define LS_ZEITARTEN_WEEKDAY              7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ZEITARTEN {
		 long    LFDNR;
		 long    ZEITART;
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGIN;
		 long    ZEITENDE;
		 char    ZEITZUSATZ[1 + 1];
		 char    KZUPD[1 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 short   WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ZEITARTEN {
		 long    LFDNR;
		 long    ZEITART;
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGIN;
		 long    ZEITENDE;
		 char    ZEITZUSATZ;
		 char    KZUPD;
		 short   VERTRIEBSZENTRUMNR;
		 short   WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ZEITARTEN {
		 short  LFDNR;
		 short  ZEITART;
		 short  ZEITSCHLUESSEL;
		 short  TAGESTYP;
		 short  ZEITBEGIN;
		 short  ZEITENDE;
		 short  ZEITZUSATZ;
		 short  KZUPD;
		 short   VERTRIEBSZENTRUMNR;
		 short   WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ZEITARTEN {
		 char    LFDNR[11];
		 char    ZEITART[11];
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 char    ZEITBEGIN[11];
		 char    ZEITENDE[11];
		 char    ZEITZUSATZ[1 + 1];
		 char    KZUPD[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    WEEKDAY[7];
       };

 struct O_ZEITARTEN {
		 char    LFDNR[11];
		 char    ZEITART[11];
		 char    ZEITSCHLUESSEL[16];
		 char    TAGESTYP[6];
		 char    ZEITBEGIN[11];
		 char    ZEITENDE[11];
		 char    ZEITZUSATZ[1];
		 char    KZUPD[1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    WEEKDAY[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ZEITARTEN_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZEITARTEN_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CZEITARTEN
 {
  public:

  ZEITARTEN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ZEITARTEN_BES, ZEITARTEN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ZEITARTEN_BES, ZEITARTEN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ZEITARTEN_BES, ZEITARTEN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CZEITARTEN()
  {
   ::buf_default((void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ);
  }
 };
#endif

#define ZEITARTEN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 LFDNR              SERIAL          NOT NULL,\
		 ZEITART            INTEGER         default 0 NOT NULL,\
		 ZEITSCHLUESSEL     CHAR(16)        default " " NOT NULL,\
		 TAGESTYP           CHAR(6)         default " " NOT NULL,\
		 ZEITBEGIN          INTEGER         default 0 NOT NULL,\
		 ZEITENDE           INTEGER         default 0 NOT NULL,\
		 ZEITZUSATZ         CHAR(1)         default " " NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 WEEKDAY            SMALLINT        default 0 NOT NULL  ) EXTENT SIZE 179 LOCK MODE ROW;

#define ZEITARTEN_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ZEITARTEN_2      on yyy( LFDNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ZEITARTEN_1      on yyy( ZEITART, ZEITSCHLUESSEL );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ZEITARTEN_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ZEITARTEN_2     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ZEITARTEN_1     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

