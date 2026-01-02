/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_LIEFERINFO_BESLA_NR             11
 #define L_LIEFERINFO_BESLA_NAME           30
 #define L_LIEFERINFO_PLZ_STRASSE          7
 #define L_LIEFERINFO_ORT                  30
 #define L_LIEFERINFO_E_MAIL               120
 #define L_LIEFERINFO_EINKAUFSVERBOT       1
 #define L_LIEFERINFO_ARZNEIMITTELBEZUG    1


 #define L_LIEFERINFO_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define LIEFERINFO_ANZ (int) ( sizeof(LIEFERINFO_BES) / sizeof(struct buf_desc) )
#endif
 #define G_LIEFERINFO sizeof(struct LIEFERINFO)


 #define LIEFERINFO_H

 
 #define LIEFERINFOBESLA_NR                      0
 #define LIEFERINFOBESLA_NAME                    1
 #define LIEFERINFOPLZ_STRASSE                   2
 #define LIEFERINFOORT                           3
 #define LIEFERINFOE_MAIL                        4
 #define LIEFERINFOEINKAUFSVERBOT                5
 #define LIEFERINFOARZNEIMITTELBEZUG             6

 #define LS_LIEFERINFO_BESLA_NR             11
 #define LS_LIEFERINFO_BESLA_NAME           31
 #define LS_LIEFERINFO_PLZ_STRASSE          8
 #define LS_LIEFERINFO_ORT                  31
 #define LS_LIEFERINFO_E_MAIL               121
 #define LS_LIEFERINFO_EINKAUFSVERBOT       2
 #define LS_LIEFERINFO_ARZNEIMITTELBEZUG    2
 #define LS_LIEFERINFO_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct LIEFERINFO {
		 long    BESLA_NR;
		 char    BESLA_NAME[30 + 1];
		 char    PLZ_STRASSE[7 + 1];
		 char    ORT[30 + 1];
		 char    E_MAIL[120 + 1];
		 char    EINKAUFSVERBOT[1 + 1];
		 char    ARZNEIMITTELBEZUG[1 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_LIEFERINFO {
		 long    BESLA_NR;
		 char    BESLA_NAME[30 + 1];
		 char    PLZ_STRASSE[7 + 1];
		 char    ORT[30 + 1];
		 char    E_MAIL[120 + 1];
		 char    EINKAUFSVERBOT[1 + 1];
		 char    ARZNEIMITTELBEZUG[1 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_LIEFERINFO {
		 short BESLA_NR;
		 short BESLA_NAME;
		 short PLZ_STRASSE;
		 short ORT;
		 short E_MAIL;
		 short EINKAUFSVERBOT;
		 short ARZNEIMITTELBEZUG;
		 short FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_LIEFERINFO {
		 char    BESLA_NR[11];
		 char    BESLA_NAME[30 + 1];
		 char    PLZ_STRASSE[7 + 1];
		 char    ORT[30 + 1];
		 char    E_MAIL[120 + 1];
		 char    EINKAUFSVERBOT[1 + 1];
		 char    ARZNEIMITTELBEZUG[1 + 1];
		 char    FETCH_REL[11];
       };

 struct O_LIEFERINFO {
		 char    BESLA_NR[11];
		 char    BESLA_NAME[30];
		 char    PLZ_STRASSE[7];
		 char    ORT[30];
		 char    E_MAIL[120];
		 char    EINKAUFSVERBOT[1];
		 char    ARZNEIMITTELBEZUG[1];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc LIEFERINFO_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,  120 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc LIEFERINFO_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,  120 ,   0 },
	 { TYP_C,    1 ,   0 },
	 { TYP_C,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CLIEFERINFO
 {
  public:

  LIEFERINFO s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, LIEFERINFO_BES, LIEFERINFO_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,LIEFERINFO_BES, LIEFERINFO_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,LIEFERINFO_BES, LIEFERINFO_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CLIEFERINFO()
  {
   ::buf_default((void *)&s, LIEFERINFO_BES, LIEFERINFO_ANZ);
  }
 };
#endif
