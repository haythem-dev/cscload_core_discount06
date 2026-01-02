/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define VTELARTAK_LISTE \
         TELARTAK.SATZNR, \
         TELARTAK.PZN, \
         TELARTAK.ARTIKEL_NAME

 #define VTELARTAK_ZEIGER(xxx) \
         :xxx->SATZNR,\
         :xxx->PZN,\
         :xxx->ARTIKEL_NAME

 #define VTELARTAK_UPDATE(xxx) \
         SATZNR = :xxx->SATZNR,\
         PZN = :xxx->PZN,\
         ARTIKEL_NAME = :xxx->ARTIKEL_NAME

 #define L_VTELARTAK_SATZNR               11
 #define L_VTELARTAK_PZN                  11
 #define L_VTELARTAK_ARTIKEL_NAME         30
 #define L_VTELARTAK_FETCH_REL            11


 #define L_VTELARTAK_PKEY 11


 #define VTELARTAK_ANZ (int) ( sizeof(VTELARTAK_BES) / sizeof(struct buf_desc) )
 #define G_VTELARTAK sizeof(struct VTELARTAK)


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct VTELARTAK {
       long    SATZNR;
       long    PZN;
       char    ARTIKEL_NAME[30 + 1];
       long    FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct I_VTELARTAK {
       short  SATZNR;
       short  PZN;
       short  ARTIKEL_NAME;
       short  FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 static struct buf_desc VTELARTAK_BES [] =
 {
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_C ,   30 ,   0 },
    { TYP_L ,   11 ,   0 },
 };

 #ifdef __cplusplus

 class CVTELARTAK
 {
  public:

  VTELARTAK s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, VTELARTAK_BES, VTELARTAK_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
   #ifdef Win32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,VTELARTAK_BES, VTELARTAK_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,VTELARTAK_BES, VTELARTAK_ANZ, error_msg);
   #endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CVTELARTAK()
  {
   ::buf_default((void *)&s, VTELARTAK_BES, VTELARTAK_ANZ);
  }
 };
 #endif

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define VTELSUCH_LISTE \
         TELARTAK.SATZNR, \
         TELARTAK.PZN, \
         TELARTAK.ARTIKEL_NAME, \
         TELARTSUCH.SUCH_BEZEICH

 #define VTELSUCH_ZEIGER(xxx) \
         :xxx->SATZNR,\
         :xxx->PZN,\
         :xxx->ARTIKEL_NAME,\
         :xxx->SUCH_BEZEICH

 #define VTELSUCH_UPDATE(xxx) \
         SATZNR = :xxx->SATZNR,\
         PZN = :xxx->PZN,\
         ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
         SUCH_BEZEICH = :xxx->SUCH_BEZEICH

 #define L_VTELSUCH_SATZNR               11
 #define L_VTELSUCH_PZN                  11
 #define L_VTELSUCH_ARTIKEL_NAME         30
 #define L_VTELSUCH_SUCH_BEZEICH         255
 #define L_VTELSUCH_FETCH_REL            11


 #define L_VTELSUCH_PKEY 11


 #define VTELSUCH_ANZ (int) ( sizeof(VTELSUCH_BES) / sizeof(struct buf_desc) )
 #define G_VTELSUCH sizeof(struct VTELSUCH)


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct VTELSUCH {
       long    SATZNR;
       long    PZN;
       char    ARTIKEL_NAME[30 + 1];
       long    FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct I_VTELSUCH {
       short  SATZNR;
       short  PZN;
       short  ARTIKEL_NAME;
       short  SUCH_BEZEICH;
       short  FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 static struct buf_desc VTELSUCH_BES [] =
 {
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_C ,   30 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
 };

 #ifdef __cplusplus

 class CVTELSUCH
 {
  public:

  VTELSUCH s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, VTELSUCH_BES, VTELSUCH_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
   #ifdef Win32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,VTELSUCH_BES, VTELSUCH_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,VTELSUCH_BES, VTELSUCH_ANZ, error_msg);
   #endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CVTELSUCH()
  {
   ::buf_default((void *)&s, VTELSUCH_BES, VTELSUCH_ANZ);
  }
 };
 #endif

