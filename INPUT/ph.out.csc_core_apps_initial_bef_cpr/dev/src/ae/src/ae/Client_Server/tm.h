/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

#ifndef _TM_H
#define _TM_H

 #define L_TM_DATUM                11
 #define L_TM_ZEIT                 11
 #define L_TM_WTAG                 11
 #define L_TM_JTAG                 11


 #define L_TM_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TM_ANZ ( sizeof(TM_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TM sizeof(struct TM)


 #define TM_H

 #define TM_LISTE \
 			AADUMMY.DATUM, \
 			AADUMMY.ZEIT, \
 			AADUMMY.WTAG, \
 			AADUMMY.JTAG
 #define TM_PLISTE \
 			"AADUMMY.DATUM," \
 			"AADUMMY.ZEIT," \
 			"AADUMMY.WTAG," \
 			"AADUMMY.JTAG " 

 #define TMDATUM                         0
 #define TMZEIT                          1
 #define TMWTAG                          2
 #define TMJTAG                          3

 #define TM_ZEIGER(xxx) \
 			:xxx->DATUM,\
 			:xxx->ZEIT,\
 			:xxx->WTAG,\
 			:xxx->JTAG

 #define TM_UPDATE(xxx) \
 			DATUM = :xxx->DATUM,\
 			ZEIT = :xxx->ZEIT,\
 			WTAG = :xxx->WTAG,\
 			JTAG = :xxx->JTAG

 #define LS_TM_DATUM                11
 #define LS_TM_ZEIT                 11
 #define LS_TM_WTAG                 11
 #define LS_TM_JTAG                 11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TM {
		 long    DATUM;
		 long    ZEIT;
		 long    WTAG;
		 long    JTAG;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TM {
		 long    DATUM;
		 long    ZEIT;
		 long    WTAG;
		 long    JTAG;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TM {
		 short  DATUM;
		 short  ZEIT;
		 short  WTAG;
		 short  JTAG;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TM {
		 char    DATUM[11];
		 char    ZEIT[11];
		 char    WTAG[11];
		 char    JTAG[11];
       };

 struct O_TM {
		 char    DATUM[11];
		 char    ZEIT[11];
		 char    WTAG[11];
		 char    JTAG[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TM_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TM_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTM
 {
  public:

  TM s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TM_BES, TM_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TM_BES, TM_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TM_BES, TM_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTM()
  {
   ::buf_default((void *)&s, TM_BES, TM_ANZ);
  }
 };
#endif
#endif

