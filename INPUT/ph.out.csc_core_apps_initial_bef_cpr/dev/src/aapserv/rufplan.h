/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define RUFSEL_LISTE \
 			RUFPLAN.FILIAL_NR, \
 			RUFPLAN.IDF_NR, \
 			RUFPLAN.RUF_ZEIT, \
 			RUFPLAN.AKTIV_MONTAG, \
 			RUFPLAN.AKTIV_DIENSTAG, \
 			RUFPLAN.AKTIV_MITTWOCH, \
 			RUFPLAN.AKTIV_DONNERSTAG, \
 			RUFPLAN.AKTIV_FREITAG, \
 			RUFPLAN.AKTIV_SAMSTAG, \
 			RUFPLAN.AKTIV_SONNTAG, \
 			RUFPLAN.AKTIV_DATUM, \
 			RUFPLAN.ANRUF_ART, \
 			RUFPLAN.ANRUF_STEUERUNG, \
 			RUFPLAN.PRIORITAET, \
 			RUFPLAN.ANLAGE_DATUM, \
 			RUFPLAN.AENDER_DATUM, \
 			RUFPLAN.SPERR_KZ, \
 			RUFPLAN.LOESCH_KZ, \
 			RUFPLAN.POOL_NR, \
 			RUFPLAN.RUECKRUF_KZ, \
 			RUFPLAN.TOUR_NR, \
 			RUFPLAN.UID_LETZTE_AEND

 #define RUFSEL_ZEIGER(xxx) \
 			:xxx->FILIAL_NR,\
 			:xxx->IDF_NR,\
 			:xxx->RUF_ZEIT,\
 			:xxx->AKTIV_MONTAG,\
 			:xxx->AKTIV_DIENSTAG,\
 			:xxx->AKTIV_MITTWOCH,\
 			:xxx->AKTIV_DONNERSTAG,\
 			:xxx->AKTIV_FREITAG,\
 			:xxx->AKTIV_SAMSTAG,\
 			:xxx->AKTIV_SONNTAG,\
 			:xxx->AKTIV_DATUM,\
 			:xxx->ANRUF_ART,\
 			:xxx->ANRUF_STEUERUNG,\
 			:xxx->PRIORITAET,\
 			:xxx->ANLAGE_DATUM,\
 			:xxx->AENDER_DATUM,\
 			:xxx->SPERR_KZ,\
 			:xxx->LOESCH_KZ,\
 			:xxx->POOL_NR,\
 			:xxx->RUECKRUF_KZ,\
 			:xxx->TOUR_NR,\
 			:xxx->UID_LETZTE_AEND

 #define L_RUFSEL_FILIAL_NR            11
 #define L_RUFSEL_IDF_NR               11
 #define L_RUFSEL_RUF_ZEIT             11
 #define L_RUFSEL_AKTIV_MONTAG         1
 #define L_RUFSEL_AKTIV_DIENSTAG       1
 #define L_RUFSEL_AKTIV_MITTWOCH       1
 #define L_RUFSEL_AKTIV_DONNERSTAG     1
 #define L_RUFSEL_AKTIV_FREITAG        1
 #define L_RUFSEL_AKTIV_SAMSTAG        1
 #define L_RUFSEL_AKTIV_SONNTAG        1
 #define L_RUFSEL_AKTIV_DATUM          11
 #define L_RUFSEL_ANRUF_ART            2
 #define L_RUFSEL_ANRUF_STEUERUNG      1
 #define L_RUFSEL_PRIORITAET           11
 #define L_RUFSEL_ANLAGE_DATUM         11
 #define L_RUFSEL_AENDER_DATUM         11
 #define L_RUFSEL_SPERR_KZ             1
 #define L_RUFSEL_LOESCH_KZ            1
 #define L_RUFSEL_POOL_NR              11
 #define L_RUFSEL_RUECKRUF_KZ          1
 #define L_RUFSEL_TOUR_NR              6
 #define L_RUFSEL_UID_LETZTE_AEND      11
 #define L_RUFSEL_FETCH_REL            11


 #define RUFSEL_ANZ (int) ( sizeof(RUFSEL_BES) / sizeof(struct buf_desc) )
 #define G_RUFSEL sizeof(struct RUFSEL)


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct RUFSEL {
		 long    FILIAL_NR;
		 long    IDF_NR;
		 long    RUF_ZEIT;
		 char    AKTIV_MONTAG[1 + 1];
		 char    AKTIV_DIENSTAG[1 + 1];
		 char    AKTIV_MITTWOCH[1 + 1];
		 char    AKTIV_DONNERSTAG[1 + 1];
		 char    AKTIV_FREITAG[1 + 1];
		 char    AKTIV_SAMSTAG[1 + 1];
		 char    AKTIV_SONNTAG[1 + 1];
		 long    AKTIV_DATUM;
		 char    ANRUF_ART[2 + 1];
		 char    ANRUF_STEUERUNG[1 + 1];
		 long    PRIORITAET;
		 long    ANLAGE_DATUM;
		 long    AENDER_DATUM;
		 char    SPERR_KZ[1 + 1];
		 char    LOESCH_KZ[1 + 1];
		 long    POOL_NR;
		 char    RUECKRUF_KZ[1 + 1];
		 char    TOUR_NR[6 + 1];
		 long    UID_LETZTE_AEND;
		 long    FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct I_RUFSEL {
		 short  FILIAL_NR;
		 short  IDF_NR;
		 short  RUF_ZEIT;
		 short  AKTIV_MONTAG;
		 short  AKTIV_DIENSTAG;
		 short  AKTIV_MITTWOCH;
		 short  AKTIV_DONNERSTAG;
		 short  AKTIV_FREITAG;
		 short  AKTIV_SAMSTAG;
		 short  AKTIV_SONNTAG;
		 short  AKTIV_DATUM;
		 short  ANRUF_ART;
		 short  ANRUF_STEUERUNG;
		 short  PRIORITAET;
		 short  ANLAGE_DATUM;
		 short  AENDER_DATUM;
		 short  SPERR_KZ;
		 short  LOESCH_KZ;
		 short  POOL_NR;
		 short  RUECKRUF_KZ;
		 short  TOUR_NR;
		 short  UID_LETZTE_AEND;
		 short  FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 static struct buf_desc RUFSEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };

 #ifdef __cplusplus

 class CRUFSEL
 {
  public:

  RUFSEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, RUFSEL_BES, RUFSEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
   #ifdef Win32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,RUFSEL_BES, RUFSEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,RUFSEL_BES, RUFSEL_ANZ, error_msg);
   #endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CRUFSEL()
  {
   ::buf_default((void *)&s, RUFSEL_BES, RUFSEL_ANZ);
  }
 };
 #endif

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define TAGSEL_LISTE \
 			TAGPLAN.FILIAL_NR, \
 			TAGPLAN.RUF_ZEIT, \
 			TAGPLAN.PRIORITAET, \
 			TAGPLAN.IDF_NR, \
 			TAGPLAN.TOUR_NR, \
 			TAGPLAN.MATCH_CODE, \
 			TAGPLAN.NAME_APO, \
 			TAGPLAN.NAME_INHABER, \
 			TAGPLAN.POSTLEITZAHL, \
 			TAGPLAN.ORT, \
 			TAGPLAN.KUNDEN_PRIORITAE, \
 			TAGPLAN.TELEFON_LANG, \
 			TAGPLAN.TELEFON_KURZ, \
 			TAGPLAN.RUFZEIT_UR, \
 			TAGPLAN.RUFZEIT_NEU, \
 			TAGPLAN.RUFZEIT_ALT, \
 			TAGPLAN.ZEIT_GESTARTET, \
 			TAGPLAN.ZEIT_ERLEDIGT, \
 			TAGPLAN.ZEIT_ERSTELLT, \
 			TAGPLAN.RUF_ZAEHLER, \
 			TAGPLAN.TERMINAL_ID, \
 			TAGPLAN.ANRUF_STATUS, \
 			TAGPLAN.ANRUF_ART, \
 			TAGPLAN.VERBINDUNG_STATU, \
 			TAGPLAN.VERARBEITUNG_ART, \
 			TAGPLAN.LOESCH_GRUND, \
 			TAGPLAN.WOCHEN_TAG, \
 			TAGPLAN.PLAN_DATUM, \
 			TAGPLAN.POOL_NR, \
 			TAGPLAN.RUECKRUF_KZ, \
 			TAGPLAN.TELEFON_RUECKRUF, \
 			TAGPLAN.ZEILEN_DAFUE, \
 			TAGPLAN.ANZAHL_BELEGT, \
 			TAGPLAN.NICHT_ABGEHOBEN, \
 			TAGPLAN.ANNAHME_BELEGT, \
 			TAGPLAN.ANNAHME_N_ABGEHO, \
 			TAGPLAN.ANZAHL_AUTO_RUFE

 #define TAGSEL_ZEIGER(xxx) \
 			:xxx->FILIAL_NR,\
 			:xxx->RUF_ZEIT,\
 			:xxx->PRIORITAET,\
 			:xxx->IDF_NR,\
 			:xxx->TOUR_NR,\
 			:xxx->MATCH_CODE,\
 			:xxx->NAME_APO,\
 			:xxx->NAME_INHABER,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->ORT,\
 			:xxx->KUNDEN_PRIORITAE,\
 			:xxx->TELEFON_LANG,\
 			:xxx->TELEFON_KURZ,\
 			:xxx->RUFZEIT_UR,\
 			:xxx->RUFZEIT_NEU,\
 			:xxx->RUFZEIT_ALT,\
 			:xxx->ZEIT_GESTARTET,\
 			:xxx->ZEIT_ERLEDIGT,\
 			:xxx->ZEIT_ERSTELLT,\
 			:xxx->RUF_ZAEHLER,\
 			:xxx->TERMINAL_ID,\
 			:xxx->ANRUF_STATUS,\
 			:xxx->ANRUF_ART,\
 			:xxx->VERBINDUNG_STATU,\
 			:xxx->VERARBEITUNG_ART,\
 			:xxx->LOESCH_GRUND,\
 			:xxx->WOCHEN_TAG,\
 			:xxx->PLAN_DATUM,\
 			:xxx->POOL_NR,\
 			:xxx->RUECKRUF_KZ,\
 			:xxx->TELEFON_RUECKRUF,\
 			:xxx->ZEILEN_DAFUE,\
 			:xxx->ANZAHL_BELEGT,\
 			:xxx->NICHT_ABGEHOBEN,\
 			:xxx->ANNAHME_BELEGT,\
 			:xxx->ANNAHME_N_ABGEHO,\
 			:xxx->ANZAHL_AUTO_RUFE

 #define L_TAGSEL_FILIAL_NR            11
 #define L_TAGSEL_RUF_ZEIT             11
 #define L_TAGSEL_PRIORITAET           2
 #define L_TAGSEL_IDF_NR               11
 #define L_TAGSEL_TOUR_NR              6
 #define L_TAGSEL_MATCH_CODE           30
 #define L_TAGSEL_NAME_APO             30
 #define L_TAGSEL_NAME_INHABER         30
 #define L_TAGSEL_POSTLEITZAHL         7
 #define L_TAGSEL_ORT                  30
 #define L_TAGSEL_KUNDEN_PRIORITAE     1
 #define L_TAGSEL_TELEFON_LANG         15
 #define L_TAGSEL_TELEFON_KURZ         4
 #define L_TAGSEL_RUFZEIT_UR           11
 #define L_TAGSEL_RUFZEIT_NEU          11
 #define L_TAGSEL_RUFZEIT_ALT          11
 #define L_TAGSEL_ZEIT_GESTARTET       11
 #define L_TAGSEL_ZEIT_ERLEDIGT        11
 #define L_TAGSEL_ZEIT_ERSTELLT        11
 #define L_TAGSEL_RUF_ZAEHLER          11
 #define L_TAGSEL_TERMINAL_ID          4
 #define L_TAGSEL_ANRUF_STATUS         2
 #define L_TAGSEL_ANRUF_ART            2
 #define L_TAGSEL_VERBINDUNG_STATU     2
 #define L_TAGSEL_VERARBEITUNG_ART     1
 #define L_TAGSEL_LOESCH_GRUND         2
 #define L_TAGSEL_WOCHEN_TAG           2
 #define L_TAGSEL_PLAN_DATUM           11
 #define L_TAGSEL_POOL_NR              11
 #define L_TAGSEL_RUECKRUF_KZ          1
 #define L_TAGSEL_TELEFON_RUECKRUF     15
 #define L_TAGSEL_ZEILEN_DAFUE         11
 #define L_TAGSEL_ANZAHL_BELEGT        11
 #define L_TAGSEL_NICHT_ABGEHOBEN      11
 #define L_TAGSEL_ANNAHME_BELEGT       11
 #define L_TAGSEL_ANNAHME_N_ABGEHO     11
 #define L_TAGSEL_ANZAHL_AUTO_RUFE     11
 #define L_TAGSEL_FETCH_REL            11


 #define TAGSEL_ANZ (int) ( sizeof(TAGSEL_BES) / sizeof(struct buf_desc) )
 #define G_TAGSEL sizeof(struct TAGSEL)


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct TAGSEL {
		 long    FILIAL_NR;
		 long    RUF_ZEIT;
		 char    PRIORITAET[2 + 1];
		 long    IDF_NR;
		 char    TOUR_NR[6 + 1];
		 char    MATCH_CODE[30 + 1];
		 char    NAME_APO[30 + 1];
		 char    NAME_INHABER[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    ORT[30 + 1];
		 char    KUNDEN_PRIORITAE[1 + 1];
		 char    TELEFON_LANG[15 + 1];
		 char    TELEFON_KURZ[4 + 1];
		 long    RUFZEIT_UR;
		 long    RUFZEIT_NEU;
		 long    RUFZEIT_ALT;
		 long    ZEIT_GESTARTET;
		 long    ZEIT_ERLEDIGT;
		 long    ZEIT_ERSTELLT;
		 long    RUF_ZAEHLER;
		 char    TERMINAL_ID[4 + 1];
		 char    ANRUF_STATUS[2 + 1];
		 char    ANRUF_ART[2 + 1];
		 char    VERBINDUNG_STATU[2 + 1];
		 char    VERARBEITUNG_ART[1 + 1];
		 char    LOESCH_GRUND[2 + 1];
		 char    WOCHEN_TAG[2 + 1];
		 long    PLAN_DATUM;
		 long    POOL_NR;
		 char    RUECKRUF_KZ[1 + 1];
		 char    TELEFON_RUECKRUF[15 + 1];
		 long    ZEILEN_DAFUE;
		 long    ANZAHL_BELEGT;
		 long    NICHT_ABGEHOBEN;
		 long    ANNAHME_BELEGT;
		 long    ANNAHME_N_ABGEHO;
		 long    ANZAHL_AUTO_RUFE;
		 long    FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct I_TAGSEL {
		 short  FILIAL_NR;
		 short  RUF_ZEIT;
		 short  PRIORITAET;
		 short  IDF_NR;
		 short  TOUR_NR;
		 short  MATCH_CODE;
		 short  NAME_APO;
		 short  NAME_INHABER;
		 short  POSTLEITZAHL;
		 short  ORT;
		 short  KUNDEN_PRIORITAE;
		 short  TELEFON_LANG;
		 short  TELEFON_KURZ;
		 short  RUFZEIT_UR;
		 short  RUFZEIT_NEU;
		 short  RUFZEIT_ALT;
		 short  ZEIT_GESTARTET;
		 short  ZEIT_ERLEDIGT;
		 short  ZEIT_ERSTELLT;
		 short  RUF_ZAEHLER;
		 short  TERMINAL_ID;
		 short  ANRUF_STATUS;
		 short  ANRUF_ART;
		 short  VERBINDUNG_STATU;
		 short  VERARBEITUNG_ART;
		 short  LOESCH_GRUND;
		 short  WOCHEN_TAG;
		 short  PLAN_DATUM;
		 short  POOL_NR;
		 short  RUECKRUF_KZ;
		 short  TELEFON_RUECKRUF;
		 short  ZEILEN_DAFUE;
		 short  ANZAHL_BELEGT;
		 short  NICHT_ABGEHOBEN;
		 short  ANNAHME_BELEGT;
		 short  ANNAHME_N_ABGEHO;
		 short  ANZAHL_AUTO_RUFE;
		 short  FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 static struct buf_desc TAGSEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };

 #ifdef __cplusplus

 class CTAGSEL
 {
  public:

  TAGSEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TAGSEL_BES, TAGSEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
   #ifdef Win32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TAGSEL_BES, TAGSEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TAGSEL_BES, TAGSEL_ANZ, error_msg);
   #endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTAGSEL()
  {
   ::buf_default((void *)&s, TAGSEL_BES, TAGSEL_ANZ);
  }
 };
 #endif

