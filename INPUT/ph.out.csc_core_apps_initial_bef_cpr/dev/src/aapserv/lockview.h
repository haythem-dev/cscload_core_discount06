/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_LOCKMAN_RESOURCENAME         32
 #define L_LOCKMAN_RESOURCEKEY          32
 #define L_LOCKMAN_NAMEWORKSTATION      32
 #define L_LOCKMAN_TM_YEAR              6
 #define L_LOCKMAN_TM_MON               6
 #define L_LOCKMAN_TM_MDAY              6
 #define L_LOCKMAN_TM_HOUR              6
 #define L_LOCKMAN_TM_MIN               6
 #define L_LOCKMAN_TM_SEC               6


 #define L_LOCKMAN_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define LOCKMAN_ANZ ( sizeof(LOCKMAN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_LOCKMAN sizeof(struct LOCKMAN)


 #define LOCKMAN_H

 #define LOCKMAN_LISTE \
 			AADUMMY.RESOURCENAME, \
 			AADUMMY.RESOURCEKEY, \
 			AADUMMY.NAMEWORKSTATION, \
 			AADUMMY.TM_YEAR, \
 			AADUMMY.TM_MON, \
 			AADUMMY.TM_MDAY, \
 			AADUMMY.TM_HOUR, \
 			AADUMMY.TM_MIN, \
 			AADUMMY.TM_SEC
 #define LOCKMAN_PLISTE \
 			"AADUMMY.RESOURCENAME," \
 			"AADUMMY.RESOURCEKEY," \
 			"AADUMMY.NAMEWORKSTATION," \
 			"AADUMMY.TM_YEAR," \
 			"AADUMMY.TM_MON," \
 			"AADUMMY.TM_MDAY," \
 			"AADUMMY.TM_HOUR," \
 			"AADUMMY.TM_MIN," \
 			"AADUMMY.TM_SEC " 

 #define LOCKMAN_PELISTE \
 			"RESOURCENAME," \
 			"RESOURCEKEY," \
 			"NAMEWORKSTATION," \
 			"TM_YEAR," \
 			"TM_MON," \
 			"TM_MDAY," \
 			"TM_HOUR," \
 			"TM_MIN," \
 			"TM_SEC " 

 #define LOCKMAN_UPDLISTE \
 			"RESOURCENAME=?," \
 			"RESOURCEKEY=?," \
 			"NAMEWORKSTATION=?," \
 			"TM_YEAR=?," \
 			"TM_MON=?," \
 			"TM_MDAY=?," \
 			"TM_HOUR=?," \
 			"TM_MIN=?," \
 			"TM_SEC=? " 

 #define LOCKMANRESOURCENAME                  0
 #define LOCKMANRESOURCEKEY                   1
 #define LOCKMANNAMEWORKSTATION               2
 #define LOCKMANTM_YEAR                       3
 #define LOCKMANTM_MON                        4
 #define LOCKMANTM_MDAY                       5
 #define LOCKMANTM_HOUR                       6
 #define LOCKMANTM_MIN                        7
 #define LOCKMANTM_SEC                        8

 #define LOCKMAN_ZEIGER(xxx) \
 			:xxx->RESOURCENAME,\
 			:xxx->RESOURCEKEY,\
 			:xxx->NAMEWORKSTATION,\
 			:xxx->TM_YEAR,\
 			:xxx->TM_MON,\
 			:xxx->TM_MDAY,\
 			:xxx->TM_HOUR,\
 			:xxx->TM_MIN,\
 			:xxx->TM_SEC

 #define LOCKMAN_UPDATE(xxx) \
 			RESOURCENAME = :xxx->RESOURCENAME,\
 			RESOURCEKEY = :xxx->RESOURCEKEY,\
 			NAMEWORKSTATION = :xxx->NAMEWORKSTATION,\
 			TM_YEAR = :xxx->TM_YEAR,\
 			TM_MON = :xxx->TM_MON,\
 			TM_MDAY = :xxx->TM_MDAY,\
 			TM_HOUR = :xxx->TM_HOUR,\
 			TM_MIN = :xxx->TM_MIN,\
 			TM_SEC = :xxx->TM_SEC

 #define LS_LOCKMAN_RESOURCENAME         33
 #define LS_LOCKMAN_RESOURCEKEY          33
 #define LS_LOCKMAN_NAMEWORKSTATION      33
 #define LS_LOCKMAN_TM_YEAR              7
 #define LS_LOCKMAN_TM_MON               7
 #define LS_LOCKMAN_TM_MDAY              7
 #define LS_LOCKMAN_TM_HOUR              7
 #define LS_LOCKMAN_TM_MIN               7
 #define LS_LOCKMAN_TM_SEC               7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct LOCKMAN {
		 char    RESOURCENAME[32 + 1];
		 char    RESOURCEKEY[32 + 1];
		 char    NAMEWORKSTATION[32 + 1];
		 short   TM_YEAR;
		 short   TM_MON;
		 short   TM_MDAY;
		 short   TM_HOUR;
		 short   TM_MIN;
		 short   TM_SEC;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_LOCKMAN {
		 char    RESOURCENAME[32 + 1];
		 char    RESOURCEKEY[32 + 1];
		 char    NAMEWORKSTATION[32 + 1];
		 short   TM_YEAR;
		 short   TM_MON;
		 short   TM_MDAY;
		 short   TM_HOUR;
		 short   TM_MIN;
		 short   TM_SEC;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_LOCKMAN {
		 short  RESOURCENAME;
		 short  RESOURCEKEY;
		 short  NAMEWORKSTATION;
		 short  TM_YEAR;
		 short  TM_MON;
		 short  TM_MDAY;
		 short  TM_HOUR;
		 short  TM_MIN;
		 short  TM_SEC;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_LOCKMAN {
		 char    RESOURCENAME[32 + 1];
		 char    RESOURCEKEY[32 + 1];
		 char    NAMEWORKSTATION[32 + 1];
		 char    TM_YEAR[7];
		 char    TM_MON[7];
		 char    TM_MDAY[7];
		 char    TM_HOUR[7];
		 char    TM_MIN[7];
		 char    TM_SEC[7];
       };

 struct O_LOCKMAN {
		 char    RESOURCENAME[32];
		 char    RESOURCEKEY[32];
		 char    NAMEWORKSTATION[32];
		 char    TM_YEAR[7];
		 char    TM_MON[7];
		 char    TM_MDAY[7];
		 char    TM_HOUR[7];
		 char    TM_MIN[7];
		 char    TM_SEC[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc LOCKMAN_BES [] =
 {
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc LOCKMAN_BES [] =
 {
	 { TYP_C,   32 ,   0 },
	 { TYP_C,   32 ,   0 },
	 { TYP_C,   32 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CLOCKMAN
 {
  public:

  LOCKMAN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, LOCKMAN_BES, LOCKMAN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,LOCKMAN_BES, LOCKMAN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,LOCKMAN_BES, LOCKMAN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CLOCKMAN()
  {
   ::buf_default((void *)&s, LOCKMAN_BES, LOCKMAN_ANZ);
  }
 };
#endif

#define LOCKMAN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 RESOURCENAME CHAR(32)          ,\
		 RESOURCEKEY CHAR(32)          ,\
		 NAMEWORKSTATION CHAR(32)          ,\
		 TM_YEAR SMALLINT          ,\
		 TM_MON SMALLINT          ,\
		 TM_MDAY SMALLINT          ,\
		 TM_HOUR SMALLINT          ,\
		 TM_MIN SMALLINT          ,\
		 TM_SEC SMALLINT            ) EXTENT SIZE 2224 LOCK MODE ROW;

#define LOCKMAN_CREATE_INDEX(yyy,xxx) \

#define LOCKMAN_DELETE_INDEX(xxx) \

