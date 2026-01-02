#ifndef __PP_AEPWD_H_
#define __PP_AEPWD_H_
/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AEPWD_FILIALNR             6
 #define L_AEPWD_USERNAME             8
 #define L_AEPWD_PASSWORD             8
 #define L_AEPWD_UID                  11
 #define L_AEPWD_UID_ANLAGE           11
 #define L_AEPWD_DAT_LOESCH           11
 #define L_AEPWD_DAT_ANLAGE           11
 #define L_AEPWD_ALLG_RECHTE          20
 #define L_AEPWD_AA                   50
 #define L_AEPWD_TERMID               4
 #define L_AEPWD_AGENTID              6
 #define L_AEPWD_AA2                  100
 #define L_AEPWD_POOLID               6


 #define L_AEPWD_PKEY 14

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AEPWD_ANZ ( sizeof(AEPWD_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AEPWD sizeof(struct AEPWD)


 #define AEPWD_H

 #define AEPWD_LISTE \
 			PASSWD.FILIALNR, \
 			PASSWD.USERNAME, \
 			PASSWD.PASSWORD, \
 			PASSWD.UID, \
 			PASSWD.UID_ANLAGE, \
 			PASSWD.DAT_LOESCH, \
 			PASSWD.DAT_ANLAGE, \
 			PASSWD.ALLG_RECHTE, \
 			PASSWD.AA, \
 			PASSWD.TERMID, \
 			PASSWD.AGENTID, \
 			PASSWD.AA2, \
			PASSWD.POOLID
 #define AEPWD_PLISTE \
 			"PASSWD.FILIALNR," \
 			"PASSWD.USERNAME," \
 			"PASSWD.PASSWORD," \
 			"PASSWD.UID," \
 			"PASSWD.UID_ANLAGE," \
 			"PASSWD.DAT_LOESCH," \
 			"PASSWD.DAT_ANLAGE," \
 			"PASSWD.ALLG_RECHTE," \
 			"PASSWD.AA," \
 			"PASSWD.TERMID," \
 			"PASSWD.AGENTID," \
 			"PASSWD.AA2," \
			"PASSWD.POOLID "

 #define AEPWD_PELISTE \
 			"FILIALNR," \
 			"USERNAME," \
 			"PASSWORD," \
 			"UID," \
 			"UID_ANLAGE," \
 			"DAT_LOESCH," \
 			"DAT_ANLAGE," \
 			"ALLG_RECHTE," \
 			"AA," \
 			"TERMID," \
 			"AGENTID," \
 			"AA2," \
			"POOLID "

 #define AEPWD_UPDLISTE \
 			"FILIALNR=?," \
 			"USERNAME=?," \
 			"PASSWORD=?," \
 			"UID=?," \
 			"UID_ANLAGE=?," \
 			"DAT_LOESCH=?," \
 			"DAT_ANLAGE=?," \
 			"ALLG_RECHTE=?," \
 			"AA=?," \
 			"TERMID=?," \
 			"AGENTID=?," \
 			"AA2=?," \
			"POOLID=? "

 #define AEPWDFILIALNR                      0
 #define AEPWDUSERNAME                      1
 #define AEPWDPASSWORD                      2
 #define AEPWDUID                           3
 #define AEPWDUID_ANLAGE                    4
 #define AEPWDDAT_LOESCH                    5
 #define AEPWDDAT_ANLAGE                    6
 #define AEPWDALLG_RECHTE                   7
 #define AEPWDAA                            8
 #define AEPWDTERMID                        9
 #define AEPWDAGENTID                      10
 #define AEPWDAA2                          11
 #define AEPWDPOOLID                       12

 #define AEPWD_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->USERNAME,\
 			:xxx->PASSWORD,\
 			:xxx->UID,\
 			:xxx->UID_ANLAGE,\
 			:xxx->DAT_LOESCH,\
 			:xxx->DAT_ANLAGE,\
 			:xxx->ALLG_RECHTE,\
 			:xxx->AA,\
 			:xxx->TERMID,\
 			:xxx->AGENTID,\
 			:xxx->AA2,\
 			:xxx->POOLID

 #define AEPWD_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			USERNAME = :xxx->USERNAME,\
 			PASSWORD = :xxx->PASSWORD,\
 			UID = :xxx->UID,\
 			UID_ANLAGE = :xxx->UID_ANLAGE,\
 			DAT_LOESCH = :xxx->DAT_LOESCH,\
 			DAT_ANLAGE = :xxx->DAT_ANLAGE,\
 			ALLG_RECHTE = :xxx->ALLG_RECHTE,\
 			AA = :xxx->AA,\
 			TERMID = :xxx->TERMID,\
 			AGENTID = :xxx->AGENTID,\
 			AA2 = :xxx->AA2,\
 			POOLID = :xxx->POOLID

 #define LS_AEPWD_FILIALNR             7
 #define LS_AEPWD_USERNAME             9
 #define LS_AEPWD_PASSWORD             9
 #define LS_AEPWD_UID                  11
 #define LS_AEPWD_UID_ANLAGE           11
 #define LS_AEPWD_DAT_LOESCH           11
 #define LS_AEPWD_DAT_ANLAGE           11
 #define LS_AEPWD_ALLG_RECHTE          21
 #define LS_AEPWD_AA                   51
 #define LS_AEPWD_TERMID               5
 #define LS_AEPWD_AGENTID              7
 #define LS_AEPWD_AA2                  101
 #define LS_AEPWD_POOLID               7
 #define LS_AEPWD_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AEPWD {
		 short   FILIALNR;
		 char    USERNAME[8 + 1];
		 char    PASSWORD[8 + 1];
		 long    UID;
		 long    UID_ANLAGE;
		 long    DAT_LOESCH;
		 long    DAT_ANLAGE;
		 char    ALLG_RECHTE[20 + 1];
		 char    AA[50 + 1];
		 char    TERMID[4 + 1];
		 char    AGENTID[6 + 1];
		 char    AA2[100 + 1];
		 short   POOLID;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AEPWD {
		 short   FILIALNR;
		 char    USERNAME[8 + 1];
		 char    PASSWORD[8 + 1];
		 long    UID;
		 long    UID_ANLAGE;
		 long    DAT_LOESCH;
		 long    DAT_ANLAGE;
		 char    ALLG_RECHTE[20 + 1];
		 char    AA[50 + 1];
		 char    TERMID[4 + 1];
		 char    AGENTID[6 + 1];
		 char    AA2[100 + 1];
		 short   POOLID;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AEPWD {
		 short  FILIALNR;
		 short  USERNAME;
		 short  PASSWORD;
		 short  UID;
		 short  UID_ANLAGE;
		 short  DAT_LOESCH;
		 short  DAT_ANLAGE;
		 short  ALLG_RECHTE;
		 short  AA;
		 short  TERMID;
		 short  AGENTID;
		 short  AA2;
		 short   POOLID;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AEPWD {
		 char    FILIALNR[7];
		 char    USERNAME[8 + 1];
		 char    PASSWORD[8 + 1];
		 char    UID[11];
		 char    UID_ANLAGE[11];
		 char    DAT_LOESCH[11];
		 char    DAT_ANLAGE[11];
		 char    ALLG_RECHTE[20 + 1];
		 char    AA[50 + 1];
		 char    TERMID[4 + 1];
		 char    AGENTID[6 + 1];
		 char    AA2[100 + 1];
		 char    POOLID[7];
		 char    FETCH_REL[11];
       };

 struct O_AEPWD {
		 char    FILIALNR[7];
		 char    USERNAME[8];
		 char    PASSWORD[8];
		 char    UID[11];
		 char    UID_ANLAGE[11];
		 char    DAT_LOESCH[11];
		 char    DAT_ANLAGE[11];
		 char    ALLG_RECHTE[20];
		 char    AA[50];
		 char    TERMID[4];
		 char    AGENTID[4];
		 char    AA2[100];
		 char    POOLID[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AEPWD_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,  100 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AEPWD_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   50 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_C,  100 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAEPWD
 {
  public:

  AEPWD s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AEPWD_BES, AEPWD_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AEPWD_BES, AEPWD_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AEPWD_BES, AEPWD_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAEPWD()
  {
   ::buf_default((void *)&s, AEPWD_BES, AEPWD_ANZ);
  }
 };
#endif

#define AEPWD_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR SMALLINT          ,\
		 USERNAME CHAR(8)           ,\
		 PASSWORD CHAR(8)           ,\
		 UID INTEGER           ,\
		 UID_ANLAGE INTEGER           ,\
		 DAT_LOESCH INTEGER           ,\
		 DAT_ANLAGE INTEGER           ,\
		 ALLG_RECHTE CHAR(20)          ,\
		 AA CHAR(50)          ,\
		 TERMID CHAR(4)           ,\
		 AGENTID CHAR(6)           ,\
		 AA2 CHAR(100)          ,\
		 POOLID SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 157 LOCK MODE ROW;

#define AEPWD_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_PASSWD_1         on yyy( FILIALNR, USERNAME );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_PASSWD_2         on yyy( FILIALNR, UID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AEPWD_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_PASSWD_1        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_PASSWD_2        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#endif

