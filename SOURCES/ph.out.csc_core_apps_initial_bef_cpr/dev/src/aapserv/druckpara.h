/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DRUCKPARA_POSART               2
 #define L_DRUCKPARA_VERTRIEBSZENTRUMNR   6
 #define L_DRUCKPARA_DATUM                11


 #define L_DRUCKPARA_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DRUCKPARA_ANZ (int) ( sizeof(DRUCKPARA_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DRUCKPARA sizeof(struct DRUCKPARA)


 #define DRUCKPARA_H

 #define DRUCKPARA_LISTE \
 			AADUMMY.POSART,\
 			AADUMMY.VERTRIEBSZENTRUMNR,\
 			AADUMMY.DATUM
 #define DRUCKPARA_PLISTE \
 			"AADUMMY.POSART," \
 			"AADUMMY.VERTRIEBSZENTRUMNR," \
 			"AADUMMY.DATUM "

 #define DRUCKPARA_PELISTE \
 			"POSART," \
 			"VERTRIEBSZENTRUMNR," \
 			"DATUM "

 #define DRUCKPARA_UPDLISTE \
 			"POSART=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"DATUM=? "

 #define DRUCKPARAPOSART                        0
 #define DRUCKPARAVERTRIEBSZENTRUMNR            1
 #define DRUCKPARADATUM				            2

 #define DRUCKPARA_ZEIGER(xxx) \
 			:xxx->POSART,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->DATUM

 #define DRUCKPARA_UPDATE(xxx) \
 			POSART = :xxx->POSART,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			DATUM = :xxx->DATUM

 #define LS_DRUCKPARA_POSART				3
 #define LS_DRUCKPARA_VERTRIEBSZENTRUMNR	7
 #define LS_DRUCKPARA_DATUM					11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DRUCKPARA {
		 char    POSART[2 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 long    DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DRUCKPARA {
		 char    POSART[2 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 long    DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DRUCKPARA {
		 short  POSART;
		 short  VERTRIEBSZENTRUMNR;
		 short  DATUM;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DRUCKPARA {
		 char    POSART[2 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    DATUM[11];
       };

 struct O_DRUCKPARA {
		 char    POSART[2];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    DATUM[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DRUCKPARA_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DRUCKPARA_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L ,  11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDRUCKPARA
 {
  public:

  DRUCKPARA s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DRUCKPARA_BES, DRUCKPARA_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DRUCKPARA_BES, DRUCKPARA_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DRUCKPARA_BES, DRUCKPARA_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDRUCKPARA()
  {
   ::buf_default((void *)&s, DRUCKPARA_BES, DRUCKPARA_ANZ);
  }
 };
#endif

#define DRUCKPARA_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 POSART CHAR(2)             ,\
		 VERTRIEBSZENTRUMNR SMALLINT             ,\
		 DATUM INTEGER             ) EXTENT SIZE 40 LOCK MODE ROW;

#define DRUCKPARA_CREATE_INDEX(yyy,xxx) \

#define DRUCKPARA_DELETE_INDEX(xxx) \

