/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_VBCOUNT_ANZ_ER               11
 #define L_VBCOUNT_ANZ_GD               11
 #define L_VBCOUNT_ANZ_ST               11
 #define L_VBCOUNT_ANZ_IE               11


 #define L_VBCOUNT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define VBCOUNT_ANZ ( sizeof(VBCOUNT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_VBCOUNT sizeof(struct VBCOUNT)


 #define VBCOUNT_H

 #define VBCOUNT_LISTE \
 			AADUMMY.ANZ_ER, \
 			AADUMMY.ANZ_GD, \
 			AADUMMY.ANZ_ST, \
 			AADUMMY.ANZ_IE
 #define VBCOUNT_PLISTE \
 			"AADUMMY.ANZ_ER," \
 			"AADUMMY.ANZ_GD," \
 			"AADUMMY.ANZ_ST," \
 			"AADUMMY.ANZ_IE " 

 #define VBCOUNT_PELISTE \
 			"ANZ_ER," \
 			"ANZ_GD," \
 			"ANZ_ST," \
 			"ANZ_IE " 

 #define VBCOUNT_UPDLISTE \
 			"ANZ_ER=?," \
 			"ANZ_GD=?," \
 			"ANZ_ST=?," \
 			"ANZ_IE=? " 

 #define VBCOUNTANZ_ER                        0
 #define VBCOUNTANZ_GD                        1
 #define VBCOUNTANZ_ST                        2
 #define VBCOUNTANZ_IE                        3

 #define VBCOUNT_ZEIGER(xxx) \
 			:xxx->ANZ_ER,\
 			:xxx->ANZ_GD,\
 			:xxx->ANZ_ST,\
 			:xxx->ANZ_IE

 #define VBCOUNT_UPDATE(xxx) \
 			ANZ_ER = :xxx->ANZ_ER,\
 			ANZ_GD = :xxx->ANZ_GD,\
 			ANZ_ST = :xxx->ANZ_ST,\
 			ANZ_IE = :xxx->ANZ_IE

 #define LS_VBCOUNT_ANZ_ER               11
 #define LS_VBCOUNT_ANZ_GD               11
 #define LS_VBCOUNT_ANZ_ST               11
 #define LS_VBCOUNT_ANZ_IE               11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct VBCOUNT {
		 long    ANZ_ER;
		 long    ANZ_GD;
		 long    ANZ_ST;
		 long    ANZ_IE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_VBCOUNT {
		 long    ANZ_ER;
		 long    ANZ_GD;
		 long    ANZ_ST;
		 long    ANZ_IE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_VBCOUNT {
		 short  ANZ_ER;
		 short  ANZ_GD;
		 short  ANZ_ST;
		 short  ANZ_IE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_VBCOUNT {
		 char    ANZ_ER[11];
		 char    ANZ_GD[11];
		 char    ANZ_ST[11];
		 char    ANZ_IE[11];
       };

 struct O_VBCOUNT {
		 char    ANZ_ER[11];
		 char    ANZ_GD[11];
		 char    ANZ_ST[11];
		 char    ANZ_IE[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc VBCOUNT_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc VBCOUNT_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CVBCOUNT
 {
  public:

  VBCOUNT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, VBCOUNT_BES, VBCOUNT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,VBCOUNT_BES, VBCOUNT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,VBCOUNT_BES, VBCOUNT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CVBCOUNT()
  {
   ::buf_default((void *)&s, VBCOUNT_BES, VBCOUNT_ANZ);
  }
 };
#endif

#define VBCOUNT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ANZ_ER INTEGER           ,\
		 ANZ_GD INTEGER           ,\
		 ANZ_ST INTEGER           ,\
		 ANZ_IE INTEGER             ) EXTENT SIZE 316 LOCK MODE ROW;

#define VBCOUNT_CREATE_INDEX(yyy,xxx) \

#define VBCOUNT_DELETE_INDEX(xxx) \

