/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_TOURPLANGEN_TAGESTYP             6
 #define L_TOURPLANGEN_TOURID               6
 #define L_TOURPLANGEN_IDFNR                11
 #define L_TOURPLANGEN_REIHENFOLGENR        11
 #define L_TOURPLANGEN_FAHRTZEIT            11
 #define L_TOURPLANGEN_BEMERKUNGEN          240


 #define L_TOURPLANGEN_PKEY 23

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TOURPLANGEN_ANZ ( sizeof(TOURPLANGEN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TOURPLANGEN sizeof(struct TOURPLANGEN)


 #define TOURPLANGEN_H

 #define TOURPLANGEN_LISTE \
         TOURPLANGEN.TAGESTYP, \
         TOURPLANGEN.TOURID, \
         TOURPLANGEN.IDFNR, \
         TOURPLANGEN.REIHENFOLGENR, \
         TOURPLANGEN.FAHRTZEIT, \
         TOURPLANGEN.BEMERKUNGEN
 #define TOURPLANGEN_PLISTE \
         "TOURPLANGEN.TAGESTYP," \
         "TOURPLANGEN.TOURID," \
         "TOURPLANGEN.IDFNR," \
         "TOURPLANGEN.REIHENFOLGENR," \
         "TOURPLANGEN.FAHRTZEIT," \
         "TOURPLANGEN.BEMERKUNGEN "

 #define TOURPLANGENTAGESTYP                      0
 #define TOURPLANGENTOURID                        1
 #define TOURPLANGENIDFNR                         2
 #define TOURPLANGENREIHENFOLGENR                 3
 #define TOURPLANGENFAHRTZEIT                     4
 #define TOURPLANGENBEMERKUNGEN                   5

 #define TOURPLANGEN_ZEIGER(xxx) \
         :xxx->TAGESTYP,\
         :xxx->TOURID,\
         :xxx->IDFNR,\
         :xxx->REIHENFOLGENR,\
         :xxx->FAHRTZEIT,\
         :xxx->BEMERKUNGEN

 #define TOURPLANGEN_UPDATE(xxx) \
         TAGESTYP = :xxx->TAGESTYP,\
         TOURID = :xxx->TOURID,\
         IDFNR = :xxx->IDFNR,\
         REIHENFOLGENR = :xxx->REIHENFOLGENR,\
         FAHRTZEIT = :xxx->FAHRTZEIT,\
         BEMERKUNGEN = :xxx->BEMERKUNGEN

 #define LS_TOURPLANGEN_TAGESTYP             7
 #define LS_TOURPLANGEN_TOURID               7
 #define LS_TOURPLANGEN_IDFNR                11
 #define LS_TOURPLANGEN_REIHENFOLGENR        11
 #define LS_TOURPLANGEN_FAHRTZEIT            11
 #define LS_TOURPLANGEN_BEMERKUNGEN          241

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TOURPLANGEN {
       char    TAGESTYP[6 + 1];
       char    TOURID[6 + 1];
       long    IDFNR;
       long    REIHENFOLGENR;
       long    FAHRTZEIT;
       char    BEMERKUNGEN[240 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TOURPLANGEN {
       char    TAGESTYP[6 + 1];
       char    TOURID[6 + 1];
       long    IDFNR;
       long    REIHENFOLGENR;
       short   FAHRTZEIT;
       char    BEMERKUNGEN[240 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TOURPLANGEN {
       short  TAGESTYP;
       short  TOURID;
       short  IDFNR;
       short  REIHENFOLGENR;
       short  FAHRTZEIT;
       short  BEMERKUNGEN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TOURPLANGEN {
       char    TAGESTYP[6 + 1];
       char    TOURID[6 + 1];
       char    IDFNR[11];
       char    REIHENFOLGENR[11];
       char    FAHRTZEIT[7];
       char    BEMERKUNGEN[240 + 1];
       };

 struct O_TOURPLANGEN {
       char    TAGESTYP[6];
       char    TOURID[6];
       char    IDFNR[11];
       char    REIHENFOLGENR[11];
       char    FAHRTZEIT[7];
       char    BEMERKUNGEN[240];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TOURPLANGEN_BES [] =
 {
    { TYP_C ,    6 ,   0 },
    { TYP_C ,    6 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_C ,  240 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURPLANGEN_BES [] =
 {
    { TYP_C ,    6 ,   0 },
    { TYP_C ,    6 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_L ,   11 ,   0 },
    { TYP_S ,    5 ,   0 },
    { TYP_C ,  240 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTOURPLANGEN
 {
  public:

  TOURPLANGEN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TOURPLANGEN_BES, TOURPLANGEN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TOURPLANGEN_BES, TOURPLANGEN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TOURPLANGEN_BES, TOURPLANGEN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTOURPLANGEN()
  {
   ::buf_default((void *)&s, TOURPLANGEN_BES, TOURPLANGEN_ANZ);
  }
 };
#endif

