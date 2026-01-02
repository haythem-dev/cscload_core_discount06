/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_SERALOG_DATUM				11
 #define L_SERALOG_IDF					11
 #define L_SERALOG_ZEIT					11
 #define L_SERALOG_TID					4
 #define L_SERALOG_AUFTR				10

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 static struct buf_desc SERALOGH_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
 #define SERALOGH_ANZ ( sizeof(SERALOGH_BES) / sizeof(struct buf_desc) )
#endif
 #define G_SERALOGH sizeof(struct SERALOGH)

 struct SERALOGH {
		 long    DATUM;
		 long    IDF;
		 long    ZEIT;
		 char    TID[4+1];
		 char    AUFTR[10];
		 long    FETCH_REL;
       };

#ifdef TRANSCLASS

 class CSERALOGH
 {
  public:

  SERALOGH s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, SERALOGH_BES, SERALOGH_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,SERALOGH_BES, SERALOGH_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,SERALOGH_BES, SERALOGH_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CSERALOGH()
  {
   ::buf_default((void *)&s, SERALOGH_BES, SERALOGH_ANZ);
  }
 };
#endif

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_SERALOG_DATEN				280

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 static struct buf_desc SERALOGD_BES [] =
 {
	 { TYP_C ,  280 ,   0 },
 };

 #define SERALOGD_ANZ ( sizeof(SERALOGD_BES) / sizeof(struct buf_desc) )
#endif
 #define G_SERALOGD sizeof(struct SERALOGD)

 struct SERALOGD {
		char	DATEN[280+1];
       };

#ifdef TRANSCLASS

 class CSERALOGD
 {
  public:

  SERALOGD s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, SERALOGD_BES, SERALOGD_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,SERALOGD_BES, SERALOGD_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,SERALOGD_BES, SERALOGD_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CSERALOGD()
  {
   ::buf_default((void *)&s, SERALOGD_BES, SERALOGD_ANZ);
  }
 };
#endif
