/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ZEITARTV_LFDNR                11
 #define L_ZEITARTV_ZEITART              11
 #define L_ZEITARTV_ZEITSCHLUESSEL       16
 #define L_ZEITARTV_TAGESTYP             6
 #define L_ZEITARTV_ZEITBEGIN            11
 #define L_ZEITARTV_ZEITENDE             11
 #define L_ZEITARTV_ZEITZUSATZ           1
 #define L_ZEITARTV_VERTRIEBSZENTRUMNR   6
 #define L_ZEITARTV_WEEKDAY				 6


 #define L_ZEITARTV_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ZEITARTV_ANZ ( sizeof(ZEITARTV_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ZEITARTV sizeof(struct ZEITARTV)


 #define ZEITARTV_H

 #define ZEITARTV_LISTE \
 			ZEITARTEN.LFDNR, \
 			ZEITARTEN.ZEITART, \
 			ZEITARTEN.ZEITSCHLUESSEL, \
 			ZEITARTEN.TAGESTYP, \
 			ZEITARTEN.ZEITBEGIN, \
 			ZEITARTEN.ZEITENDE, \
 			ZEITARTEN.ZEITZUSATZ, \
			ZEITARTEN.VERTRIEBSZENTRUMNR, \
			ZEITARTEN.WEEKDAY
 #define ZEITARTV_PLISTE \
 			"ZEITARTEN.LFDNR," \
 			"ZEITARTEN.ZEITART," \
 			"ZEITARTEN.ZEITSCHLUESSEL," \
 			"ZEITARTEN.TAGESTYP," \
 			"ZEITARTEN.ZEITBEGIN," \
 			"ZEITARTEN.ZEITENDE," \
 			"ZEITARTEN.ZEITZUSATZ," \
			"ZEITARTEN.VERTRIEBSZENTRUMNR," \
			"ZEITARTEN.WEEKDAY "

 #define ZEITARTV_PELISTE \
 			"LFDNR," \
 			"ZEITART," \
 			"ZEITSCHLUESSEL," \
 			"TAGESTYP," \
 			"ZEITBEGIN," \
 			"ZEITENDE," \
 			"ZEITZUSATZ," \
			"VERTRIEBSZENTRUMNR," \
			"WEEKDAY "

 #define ZEITARTV_UPDLISTE \
 			"LFDNR=?," \
 			"ZEITART=?," \
 			"ZEITSCHLUESSEL=?," \
 			"TAGESTYP=?," \
 			"ZEITBEGIN=?," \
 			"ZEITENDE=?," \
 			"ZEITZUSATZ=?," \
			"VERTRIEBSZENTRUMNR=?," \
			"WEEKDAY=? "

 #define ZEITARTVLFDNR                         0
 #define ZEITARTVZEITART                       1
 #define ZEITARTVZEITSCHLUESSEL                2
 #define ZEITARTVTAGESTYP                      3
 #define ZEITARTVZEITBEGIN                     4
 #define ZEITARTVZEITENDE                      5
 #define ZEITARTVZEITZUSATZ                    6
 #define ZEITARTVVERTRIEBSZENTRUMNR			   7
 #define ZEITARTVWEEKDAY					   8

 #define ZEITARTV_ZEIGER(xxx) \
 			:xxx->LFDNR,\
 			:xxx->ZEITART,\
 			:xxx->ZEITSCHLUESSEL,\
 			:xxx->TAGESTYP,\
 			:xxx->ZEITBEGIN,\
 			:xxx->ZEITENDE,\
 			:xxx->ZEITZUSATZ,\
			:xxx->VERTRIEBSZENTRUMNR,\
			:xxx->WEEKDAY

 #define ZEITARTV_UPDATE(xxx) \
 			LFDNR = :xxx->LFDNR,\
 			ZEITART = :xxx->ZEITART,\
 			ZEITSCHLUESSEL = :xxx->ZEITSCHLUESSEL,\
 			TAGESTYP = :xxx->TAGESTYP,\
 			ZEITBEGIN = :xxx->ZEITBEGIN,\
 			ZEITENDE = :xxx->ZEITENDE,\
 			ZEITZUSATZ = :xxx->ZEITZUSATZ,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
			WEEKDAY = :xxx->WEEKDAY

 #define LS_ZEITARTV_LFDNR                11
 #define LS_ZEITARTV_ZEITART              11
 #define LS_ZEITARTV_ZEITSCHLUESSEL       17
 #define LS_ZEITARTV_TAGESTYP             7
 #define LS_ZEITARTV_ZEITBEGIN            11
 #define LS_ZEITARTV_ZEITENDE             11
 #define LS_ZEITARTV_ZEITZUSATZ           2
 #define LS_ZEITARTV_VERTRIEBSZENTRUMNR   7
 #define LS_ZEITARTV_WEEKDAY			  7
 #define LS_ZEITARTV_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ZEITARTV {
		 long    LFDNR;
		 long    ZEITART;
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGIN;
		 long    ZEITENDE;
		 char    ZEITZUSATZ[1 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 short   WEEKDAY;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ZEITARTV {
		 long    LFDNR;
		 long    ZEITART;
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGIN;
		 long    ZEITENDE;
		 char    ZEITZUSATZ;
		 short   VERTRIEBSZENTRUMNR;
		 short   WEEKDAY;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ZEITARTV {
		 short  LFDNR;
		 short  ZEITART;
		 short  ZEITSCHLUESSEL;
		 short  TAGESTYP;
		 short  ZEITBEGIN;
		 short  ZEITENDE;
		 short  ZEITZUSATZ;
		 short  VERTRIEBSZENTRUMNR;
		 short  WEEKDAY;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ZEITARTV {
		 char    LFDNR[11];
		 char    ZEITART[11];
		 char    ZEITSCHLUESSEL[16 + 1];
		 char    TAGESTYP[6 + 1];
		 char    ZEITBEGIN[11];
		 char    ZEITENDE[11];
		 char    ZEITZUSATZ[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    WEEKDAY[7];
		 char    FETCH_REL[11];
       };

 struct O_ZEITARTV {
		 char    LFDNR[11];
		 char    ZEITART[11];
		 char    ZEITSCHLUESSEL[16];
		 char    TAGESTYP[6];
		 char    ZEITBEGIN[11];
		 char    ZEITENDE[11];
		 char    ZEITZUSATZ[1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    WEEKDAY[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ZEITARTV_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZEITARTV_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CZEITARTV
 {
  public:

  ZEITARTV s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ZEITARTV_BES, ZEITARTV_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ZEITARTV_BES, ZEITARTV_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ZEITARTV_BES, ZEITARTV_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CZEITARTV()
  {
   ::buf_default((void *)&s, ZEITARTV_BES, ZEITARTV_ANZ);
  }
 };
#endif

#define ZEITARTV_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 LFDNR SERIAL            ,\
		 ZEITART INTEGER           ,\
		 ZEITSCHLUESSEL CHAR(16)          ,\
		 TAGESTYP CHAR(6)           ,\
		 ZEITBEGIN INTEGER           ,\
		 ZEITENDE INTEGER           ,\
		 ZEITZUSATZ CHAR(1)           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 WEEKDAY SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 185 LOCK MODE ROW;

#define ZEITARTV_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ZEITARTEN_2      on yyy( LFDNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ZEITARTEN_1      on yyy( ZEITART, ZEITSCHLUESSEL );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ZEITARTV_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ZEITARTEN_2     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ZEITARTEN_1     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

