/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDAUFART_IDFNR                11
 #define L_KNDAUFART_KDAUFTRAGART         2
 #define L_KNDAUFART_VALUTAMONATE         6
 #define L_KNDAUFART_SKDAUFTRAGARTNATRA   1
 #define L_KNDAUFART_SKDAUFTRAGARTNETTO   1
 #define L_KNDAUFART_SKDAUFTRAGARTBANR    1
 #define L_KNDAUFART_SKDAUFTRAGARTMONAT   1
 #define L_KNDAUFART_SKDAUFTRAGVERBUND    1
 #define L_KNDAUFART_SKDAUFTRAGARTVALS    1
 #define L_KNDAUFART_VALUTAMONAUTO        6
 #define L_KNDAUFART_KUNDENNR		      11
 #define L_KNDAUFART_VERTRIEBSZENTRUMNR   6


 #define L_KNDAUFART_PKEY 13

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDAUFART_ANZ ( sizeof(KNDAUFART_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDAUFART sizeof(struct KNDAUFART)


 #define KNDAUFART_H

 #define KNDAUFART_LISTE \
 			AUFTRAGARTKD.IDFNR, \
 			AUFTRAGARTKD.KDAUFTRAGART, \
 			AUFTRAGARTKD.VALUTAMONATE, \
 			AUFTRAGARTKD.SKDAUFTRAGARTNATRA, \
 			AUFTRAGARTKD.SKDAUFTRAGARTNETTO, \
 			AUFTRAGARTKD.SKDAUFTRAGARTBANR, \
 			AUFTRAGARTKD.SKDAUFTRAGARTMONAT, \
 			AUFTRAGARTKD.SKDAUFTRAGVERBUND, \
 			AUFTRAGARTKD.SKDAUFTRAGARTVALS, \
 			AUFTRAGARTKD.VALUTAMONAUTO, \
			AUFTRAGARTKD.KUNDENNR, \
			AUFTRAGARTKD.VERTRIEBSZENTRUMNR
 #define KNDAUFART_PLISTE \
 			"AUFTRAGARTKD.IDFNR," \
 			"AUFTRAGARTKD.KDAUFTRAGART," \
 			"AUFTRAGARTKD.VALUTAMONATE," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTNATRA," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTNETTO," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTBANR," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTMONAT," \
 			"AUFTRAGARTKD.SKDAUFTRAGVERBUND," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTVALS," \
 			"AUFTRAGARTKD.VALUTAMONAUTO," \
			"AUFTRAGARTKD.KUNDENNR," \
			"AUFTRAGARTKD.VERTRIEBSZENTRUMNR "

 #define KNDAUFART_PELISTE \
 			"IDFNR," \
 			"KDAUFTRAGART," \
 			"VALUTAMONATE," \
 			"SKDAUFTRAGARTNATRA," \
 			"SKDAUFTRAGARTNETTO," \
 			"SKDAUFTRAGARTBANR," \
 			"SKDAUFTRAGARTMONAT," \
 			"SKDAUFTRAGVERBUND," \
 			"SKDAUFTRAGARTVALS," \
 			"VALUTAMONAUTO," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR "

 #define KNDAUFART_UPDLISTE \
 			"IDFNR=?," \
 			"KDAUFTRAGART=?," \
 			"VALUTAMONATE=?," \
 			"SKDAUFTRAGARTNATRA=?," \
 			"SKDAUFTRAGARTNETTO=?," \
 			"SKDAUFTRAGARTBANR=?," \
 			"SKDAUFTRAGARTMONAT=?," \
 			"SKDAUFTRAGVERBUND=?," \
 			"SKDAUFTRAGARTVALS=?," \
 			"VALUTAMONAUTO=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=? "

 #define KNDAUFARTIDFNR                         0
 #define KNDAUFARTKDAUFTRAGART                  1
 #define KNDAUFARTVALUTAMONATE                  2
 #define KNDAUFARTSKDAUFTRAGARTNATRA            3
 #define KNDAUFARTSKDAUFTRAGARTNETTO            4
 #define KNDAUFARTSKDAUFTRAGARTBANR             5
 #define KNDAUFARTSKDAUFTRAGARTMONAT            6
 #define KNDAUFARTSKDAUFTRAGVERBUND             7
 #define KNDAUFARTSKDAUFTRAGARTVALS             8
 #define KNDAUFARTVALUTAMONAUTO                 9
 #define KNDAUFARTKUNDENNR						10
 #define KNDAUFARTVERTRIEBSZENTRUMNR			11

 #define KNDAUFART_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->KDAUFTRAGART,\
 			:xxx->VALUTAMONATE,\
 			:xxx->SKDAUFTRAGARTNATRA,\
 			:xxx->SKDAUFTRAGARTNETTO,\
 			:xxx->SKDAUFTRAGARTBANR,\
 			:xxx->SKDAUFTRAGARTMONAT,\
 			:xxx->SKDAUFTRAGVERBUND,\
 			:xxx->SKDAUFTRAGARTVALS,\
 			:xxx->VALUTAMONAUTO,\
			:xxx->KUNDENNR,\
			:xxx->VERTRIEBSZENTRUMNR
 #define KNDAUFART_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
 			VALUTAMONATE = :xxx->VALUTAMONATE,\
 			SKDAUFTRAGARTNATRA = :xxx->SKDAUFTRAGARTNATRA,\
 			SKDAUFTRAGARTNETTO = :xxx->SKDAUFTRAGARTNETTO,\
 			SKDAUFTRAGARTBANR = :xxx->SKDAUFTRAGARTBANR,\
 			SKDAUFTRAGARTMONAT = :xxx->SKDAUFTRAGARTMONAT,\
 			SKDAUFTRAGVERBUND = :xxx->SKDAUFTRAGVERBUND,\
 			SKDAUFTRAGARTVALS = :xxx->SKDAUFTRAGARTVALS,\
 			VALUTAMONAUTO = :xxx->VALUTAMONAUTO,\
			KUNDENNR = :xxx->KUNDENNR,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR

 #define LS_KNDAUFART_IDFNR                11
 #define LS_KNDAUFART_KDAUFTRAGART         3
 #define LS_KNDAUFART_VALUTAMONATE         7
 #define LS_KNDAUFART_SKDAUFTRAGARTNATRA   2
 #define LS_KNDAUFART_SKDAUFTRAGARTNETTO   2
 #define LS_KNDAUFART_SKDAUFTRAGARTBANR    2
 #define LS_KNDAUFART_SKDAUFTRAGARTMONAT   2
 #define LS_KNDAUFART_SKDAUFTRAGVERBUND    2
 #define LS_KNDAUFART_SKDAUFTRAGARTVALS    2
 #define LS_KNDAUFART_VALUTAMONAUTO        7
 #define LS_KNDAUFART_KUNDENNR		       11
 #define LS_KNDAUFART_VERTRIEBSZENTRUMNR   7
 #define LS_KNDAUFART_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDAUFART {
		 long    IDFNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   VALUTAMONATE;
		 char    SKDAUFTRAGARTNATRA[1 + 1];
		 char    SKDAUFTRAGARTNETTO[1 + 1];
		 char    SKDAUFTRAGARTBANR[1 + 1];
		 char    SKDAUFTRAGARTMONAT[1 + 1];
		 char    SKDAUFTRAGVERBUND[1 + 1];
		 char    SKDAUFTRAGARTVALS[1 + 1];
		 short   VALUTAMONAUTO;
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDAUFART {
		 long    IDFNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   VALUTAMONATE;
		 char    SKDAUFTRAGARTNATRA;
		 char    SKDAUFTRAGARTNETTO;
		 char    SKDAUFTRAGARTBANR;
		 char    SKDAUFTRAGARTMONAT;
		 char    SKDAUFTRAGVERBUND;
		 char    SKDAUFTRAGARTVALS;
		 short   VALUTAMONAUTO;
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDAUFART {
		 short  IDFNR;
		 short  KDAUFTRAGART;
		 short  VALUTAMONATE;
		 short  SKDAUFTRAGARTNATRA;
		 short  SKDAUFTRAGARTNETTO;
		 short  SKDAUFTRAGARTBANR;
		 short  SKDAUFTRAGARTMONAT;
		 short  SKDAUFTRAGVERBUND;
		 short  SKDAUFTRAGARTVALS;
		 short  VALUTAMONAUTO;
		 short  KUNDENNR;
		 short  VERTRIEBSZENTRUMNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDAUFART {
		 char    IDFNR[11];
		 char    KDAUFTRAGART[2 + 1];
		 char    VALUTAMONATE[7];
		 char    SKDAUFTRAGARTNATRA[1 + 1];
		 char    SKDAUFTRAGARTNETTO[1 + 1];
		 char    SKDAUFTRAGARTBANR[1 + 1];
		 char    SKDAUFTRAGARTMONAT[1 + 1];
		 char    SKDAUFTRAGVERBUND[1 + 1];
		 char    SKDAUFTRAGARTVALS[1 + 1];
		 char    VALUTAMONAUTO[7];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

 struct O_KNDAUFART {
		 char    IDFNR[11];
		 char    KDAUFTRAGART[2];
		 char    VALUTAMONATE[7];
		 char    SKDAUFTRAGARTNATRA[1];
		 char    SKDAUFTRAGARTNETTO[1];
		 char    SKDAUFTRAGARTBANR[1];
		 char    SKDAUFTRAGARTMONAT[1];
		 char    SKDAUFTRAGVERBUND[1];
		 char    SKDAUFTRAGARTVALS[1];
		 char    VALUTAMONAUTO[7];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDAUFART_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDAUFART_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDAUFART
 {
  public:

  KNDAUFART s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDAUFART_BES, KNDAUFART_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDAUFART_BES, KNDAUFART_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDAUFART_BES, KNDAUFART_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDAUFART()
  {
   ::buf_default((void *)&s, KNDAUFART_BES, KNDAUFART_ANZ);
  }
 };
#endif

#define KNDAUFART_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 KDAUFTRAGART CHAR(2)           ,\
		 VALUTAMONATE SMALLINT          ,\
		 SKDAUFTRAGARTNATRA CHAR(1)           ,\
		 SKDAUFTRAGARTNETTO CHAR(1)           ,\
		 SKDAUFTRAGARTBANR CHAR(1)           ,\
		 SKDAUFTRAGARTMONAT CHAR(1)           ,\
		 SKDAUFTRAGVERBUND CHAR(1)           ,\
		 SKDAUFTRAGARTVALS CHAR(1)           ,\
		 VALUTAMONAUTO SMALLINT          ,\
		 KUNDENNR INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 9 LOCK MODE ROW;

#define KNDAUFART_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX AUFTRAGARTKDX      on yyy( IDFNR, KDAUFTRAGART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDAUFART_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX AUFTRAGARTKDX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDAUSKU_EILBOTENZUSCHLAG     5
 #define N_KNDAUSKU_EILBOTENZUSCHLAG     2
 #define L_KNDAUSKU_MONATSUMSATZ         9
 #define N_KNDAUSKU_MONATSUMSATZ         2
 #define L_KNDAUSKU_MALUSFREI_PROZ       5
 #define N_KNDAUSKU_MALUSFREI_PROZ       2
 #define L_KNDAUSKU_VERTRETER_2          6
 #define L_KNDAUSKU_IDFNR                11
 #define L_KNDAUSKU_MATCHCODE            12
 #define L_KNDAUSKU_FILIALNR             6
 #define L_KNDAUSKU_ETARTKLASSE1         5
 #define L_KNDAUSKU_ETARTKLASSE2         5
 #define L_KNDAUSKU_ETKDMERKMAL1         5
 #define L_KNDAUSKU_ETKDMERKMAL2         5
 #define L_KNDAUSKU_NAMEAPO              40
 #define L_KNDAUSKU_NAMEINHABER          30
 #define L_KNDAUSKU_STRASSE              40
 #define L_KNDAUSKU_ORT                  30
 #define L_KNDAUSKU_POSTLEITZAHL         7
 #define L_KNDAUSKU_TELNR                20
 #define L_KNDAUSKU_TELNRDAFUE           20
 #define L_KNDAUSKU_FAXNR                20
 #define L_KNDAUSKU_TELKURZWAHL          4
 #define L_KNDAUSKU_IMSBEZIRKNR          11
 #define L_KNDAUSKU_PERSONALNRVERTR      11
 #define L_KNDAUSKU_SKDSCHWERPUNKT1      1
 #define L_KNDAUSKU_SKDSCHWERPUNKT2      1
 #define L_KNDAUSKU_SKDSCHWERPUNKT3      1
 #define L_KNDAUSKU_SKDSCHWERPUNKT4      1
 #define L_KNDAUSKU_SKDSCHWERPUNKT5      1
 #define L_KNDAUSKU_SKDKDKRITISCH        1
 #define L_KNDAUSKU_MENGENATRABASIS      11
 #define L_KNDAUSKU_MENGENATRA           11
 #define L_KNDAUSKU_KUNDE_SEIT           11
 #define L_KNDAUSKU_URLAUB_VON           11
 #define L_KNDAUSKU_URLAUB_BIS           11
 #define L_KNDAUSKU_VERSAND_KOSTEN       5
 #define N_KNDAUSKU_VERSAND_KOSTEN       2
 #define L_KNDAUSKU_SKDEILSPERRE         1
 #define L_KNDAUSKU_SKDVIPKUNDE          1
 #define L_KNDAUSKU_KUNDENNR             11
 #define L_KNDAUSKU_VERTRIEBSZENTRUMNR   6
 #define L_KNDAUSKU_IMS3000              11
 #define L_KNDAUSKU_LOGISTIKAUFSCHLAG    5
 #define N_KNDAUSKU_LOGISTIKAUFSCHLAG    2


 #define L_KNDAUSKU_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDAUSKU_ANZ ( sizeof(KNDAUSKU_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDAUSKU sizeof(struct KNDAUSKU)


 #define KNDAUSKU_H

 #define KNDAUSKU_LISTE \
 			KNDAUSKU.EILBOTENZUSCHLAG, \
 			KNDAUSKU.MONATSUMSATZ, \
 			KNDAUSKU.MALUSFREI_PROZ, \
 			KNDAUSKU.VERTRETER_2, \
 			KUNDE.IDFNR, \
 			KUNDE.MATCHCODE, \
 			KUNDE.FILIALNR, \
 			KUNDE.ETARTKLASSE1, \
 			KUNDE.ETARTKLASSE2, \
 			KUNDE.ETKDMERKMAL1, \
 			KUNDE.ETKDMERKMAL2, \
 			KUNDE.NAMEAPO, \
 			KUNDE.NAMEINHABER, \
 			KUNDE.STRASSE, \
 			KUNDE.ORT, \
 			KUNDE.POSTLEITZAHL, \
 			KUNDE.TELNR, \
 			KUNDE.TELNRDAFUE, \
 			KUNDE.FAXNR, \
 			KUNDE.TELKURZWAHL, \
 			KUNDE.IMSBEZIRKNR, \
 			KUNDE.PERSONALNRVERTR, \
 			KUNDESCHALTER.SKDSCHWERPUNKT1, \
 			KUNDESCHALTER.SKDSCHWERPUNKT2, \
 			KUNDESCHALTER.SKDSCHWERPUNKT3, \
 			KUNDESCHALTER.SKDSCHWERPUNKT4, \
 			KUNDESCHALTER.SKDSCHWERPUNKT5, \
 			KUNDESCHALTER.SKDKDKRITISCH, \
 			KUNDEKONDI.MENGENATRABASIS, \
 			KUNDEKONDI.MENGENATRA, \
 			KNDAUSKU.KUNDE_SEIT, \
 			KNDAUSKU.URLAUB_VON, \
 			KNDAUSKU.URLAUB_BIS, \
 			KNDAUSKU.VERSAND_KOSTEN, \
 			KUNDESCHALTER.SKDEILSPERRE, \
 			KUNDESCHALTER.SKDVIPKUNDE, \
			KNDAUSKU.KUNDENNR, \
			KNDAUSKU.VERTRIEBSZENTRUMNR, \
			KUNDE.IMS3000, \
 			KNDAUSKU.LOGISTIKAUFSCHLAG
 #define KNDAUSKU_PLISTE \
 			"KNDAUSKU.EILBOTENZUSCHLAG," \
 			"KNDAUSKU.MONATSUMSATZ," \
 			"KNDAUSKU.MALUSFREI_PROZ," \
 			"KNDAUSKU.VERTRETER_2," \
 			"KUNDE.IDFNR," \
 			"KUNDE.MATCHCODE," \
 			"KUNDE.FILIALNR," \
 			"KUNDE.ETARTKLASSE1," \
 			"KUNDE.ETARTKLASSE2," \
 			"KUNDE.ETKDMERKMAL1," \
 			"KUNDE.ETKDMERKMAL2," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.NAMEINHABER," \
 			"KUNDE.STRASSE," \
 			"KUNDE.ORT," \
 			"KUNDE.POSTLEITZAHL," \
 			"KUNDE.TELNR," \
 			"KUNDE.TELNRDAFUE," \
 			"KUNDE.FAXNR," \
 			"KUNDE.TELKURZWAHL," \
 			"KUNDE.IMSBEZIRKNR," \
 			"KUNDE.PERSONALNRVERTR," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT1," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT2," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT3," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT4," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT5," \
 			"KUNDESCHALTER.SKDKDKRITISCH," \
 			"KUNDEKONDI.MENGENATRABASIS," \
 			"KUNDEKONDI.MENGENATRA," \
 			"KNDAUSKU.KUNDE_SEIT," \
 			"KNDAUSKU.URLAUB_VON," \
 			"KNDAUSKU.URLAUB_BIS," \
 			"KNDAUSKU.VERSAND_KOSTEN," \
 			"KUNDESCHALTER.SKDEILSPERRE," \
 			"KUNDESCHALTER.SKDVIPKUNDE," \
			"KNDAUSKU.KUNDENNR," \
			"KNDAUSKU.VERTRIEBSZENTRUMNR," \
			"KUNDE.IMS3000," \
 			"KNDAUSKU.LOGISTIKAUFSCHLAG "

 #define KNDAUSKU_PELISTE \
 			"EILBOTENZUSCHLAG," \
 			"MONATSUMSATZ," \
 			"MALUSFREI_PROZ," \
 			"VERTRETER_2," \
 			"IDFNR," \
 			"MATCHCODE," \
 			"FILIALNR," \
 			"ETARTKLASSE1," \
 			"ETARTKLASSE2," \
 			"ETKDMERKMAL1," \
 			"ETKDMERKMAL2," \
 			"NAMEAPO," \
 			"NAMEINHABER," \
 			"STRASSE," \
 			"ORT," \
 			"POSTLEITZAHL," \
 			"TELNR," \
 			"TELNRDAFUE," \
 			"FAXNR," \
 			"TELKURZWAHL," \
 			"IMSBEZIRKNR," \
 			"PERSONALNRVERTR," \
 			"SKDSCHWERPUNKT1," \
 			"SKDSCHWERPUNKT2," \
 			"SKDSCHWERPUNKT3," \
 			"SKDSCHWERPUNKT4," \
 			"SKDSCHWERPUNKT5," \
 			"SKDKDKRITISCH," \
 			"MENGENATRABASIS," \
 			"MENGENATRA," \
 			"KUNDE_SEIT," \
 			"URLAUB_VON," \
 			"URLAUB_BIS," \
 			"VERSAND_KOSTEN," \
 			"SKDEILSPERRE," \
 			"SKDVIPKUNDE," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR," \
			"IMS3000," \
 			"LOGISTIKAUFSCHLAG "

 #define KNDAUSKU_UPDLISTE \
 			"EILBOTENZUSCHLAG=?," \
 			"MONATSUMSATZ=?," \
 			"MALUSFREI_PROZ=?," \
 			"VERTRETER_2=?," \
 			"IDFNR=?," \
 			"MATCHCODE=?," \
 			"FILIALNR=?," \
 			"ETARTKLASSE1=?," \
 			"ETARTKLASSE2=?," \
 			"ETKDMERKMAL1=?," \
 			"ETKDMERKMAL2=?," \
 			"NAMEAPO=?," \
 			"NAMEINHABER=?," \
 			"STRASSE=?," \
 			"ORT=?," \
 			"POSTLEITZAHL=?," \
 			"TELNR=?," \
 			"TELNRDAFUE=?," \
 			"FAXNR=?," \
 			"TELKURZWAHL=?," \
 			"IMSBEZIRKNR=?," \
 			"PERSONALNRVERTR=?," \
 			"SKDSCHWERPUNKT1=?," \
 			"SKDSCHWERPUNKT2=?," \
 			"SKDSCHWERPUNKT3=?," \
 			"SKDSCHWERPUNKT4=?," \
 			"SKDSCHWERPUNKT5=?," \
 			"SKDKDKRITISCH=?," \
 			"MENGENATRABASIS=?," \
 			"MENGENATRA=?," \
 			"KUNDE_SEIT=?," \
 			"URLAUB_VON=?," \
 			"URLAUB_BIS=?," \
 			"VERSAND_KOSTEN=?," \
 			"SKDEILSPERRE=?," \
 			"SKDVIPKUNDE=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=?," \
			"IMS3000=?," \
 			"LOGISTIKAUFSCHLAG=? "

 #define KNDAUSKUEILBOTENZUSCHLAG              0
 #define KNDAUSKUMONATSUMSATZ                  1
 #define KNDAUSKUMALUSFREI_PROZ                2
 #define KNDAUSKUVERTRETER_2                   3
 #define KNDAUSKUIDFNR                         4
 #define KNDAUSKUMATCHCODE                     5
 #define KNDAUSKUFILIALNR                      6
 #define KNDAUSKUETARTKLASSE1                  7
 #define KNDAUSKUETARTKLASSE2                  8
 #define KNDAUSKUETKDMERKMAL1                  9
 #define KNDAUSKUETKDMERKMAL2                  10
 #define KNDAUSKUNAMEAPO                       11
 #define KNDAUSKUNAMEINHABER                   12
 #define KNDAUSKUSTRASSE                       13
 #define KNDAUSKUORT                           14
 #define KNDAUSKUPOSTLEITZAHL                  15
 #define KNDAUSKUTELNR                         16
 #define KNDAUSKUTELNRDAFUE                    17
 #define KNDAUSKUFAXNR                         18
 #define KNDAUSKUTELKURZWAHL                   19
 #define KNDAUSKUIMSBEZIRKNR                   20
 #define KNDAUSKUPERSONALNRVERTR               21
 #define KNDAUSKUSKDSCHWERPUNKT1               22
 #define KNDAUSKUSKDSCHWERPUNKT2               23
 #define KNDAUSKUSKDSCHWERPUNKT3               24
 #define KNDAUSKUSKDSCHWERPUNKT4               25
 #define KNDAUSKUSKDSCHWERPUNKT5               26
 #define KNDAUSKUSKDKDKRITISCH                 27
 #define KNDAUSKUMENGENATRABASIS               28
 #define KNDAUSKUMENGENATRA                    29
 #define KNDAUSKUKUNDE_SEIT                    30
 #define KNDAUSKUURLAUB_VON                    31
 #define KNDAUSKUURLAUB_BIS                    32
 #define KNDAUSKUVERSAND_KOSTEN                33
 #define KNDAUSKUSKDEILSPERRE                  34
 #define KNDAUSKUSKDVIPKUNDE                   35
 #define KNDAUSKUKUNDENNR					   36
 #define KNDAUSKUIMS3000					   37
 #define KNDAUSKULOGISTIKAUFSCHLAG			   38

 #define KNDAUSKU_ZEIGER(xxx) \
 			:xxx->EILBOTENZUSCHLAG,\
 			:xxx->MONATSUMSATZ,\
 			:xxx->MALUSFREI_PROZ,\
 			:xxx->VERTRETER_2,\
 			:xxx->IDFNR,\
 			:xxx->MATCHCODE,\
 			:xxx->FILIALNR,\
 			:xxx->ETARTKLASSE1,\
 			:xxx->ETARTKLASSE2,\
 			:xxx->ETKDMERKMAL1,\
 			:xxx->ETKDMERKMAL2,\
 			:xxx->NAMEAPO,\
 			:xxx->NAMEINHABER,\
 			:xxx->STRASSE,\
 			:xxx->ORT,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->TELNR,\
 			:xxx->TELNRDAFUE,\
 			:xxx->FAXNR,\
 			:xxx->TELKURZWAHL,\
 			:xxx->IMSBEZIRKNR,\
 			:xxx->PERSONALNRVERTR,\
 			:xxx->SKDSCHWERPUNKT1,\
 			:xxx->SKDSCHWERPUNKT2,\
 			:xxx->SKDSCHWERPUNKT3,\
 			:xxx->SKDSCHWERPUNKT4,\
 			:xxx->SKDSCHWERPUNKT5,\
 			:xxx->SKDKDKRITISCH,\
 			:xxx->MENGENATRABASIS,\
 			:xxx->MENGENATRA,\
 			:xxx->KUNDE_SEIT,\
 			:xxx->URLAUB_VON,\
 			:xxx->URLAUB_BIS,\
 			:xxx->VERSAND_KOSTEN,\
 			:xxx->SKDEILSPERRE,\
 			:xxx->SKDVIPKUNDE,\
 			:xxx->KUNDENNR,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->IMS3000,\
 			:xxx->LOGISTIKAUFSCHLAG

 #define KNDAUSKU_UPDATE(xxx) \
 			EILBOTENZUSCHLAG = :xxx->EILBOTENZUSCHLAG,\
 			MONATSUMSATZ = :xxx->MONATSUMSATZ,\
 			MALUSFREI_PROZ = :xxx->MALUSFREI_PROZ,\
 			VERTRETER_2 = :xxx->VERTRETER_2,\
 			IDFNR = :xxx->IDFNR,\
 			MATCHCODE = :xxx->MATCHCODE,\
 			FILIALNR = :xxx->FILIALNR,\
 			ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
 			ETARTKLASSE2 = :xxx->ETARTKLASSE2,\
 			ETKDMERKMAL1 = :xxx->ETKDMERKMAL1,\
 			ETKDMERKMAL2 = :xxx->ETKDMERKMAL2,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			NAMEINHABER = :xxx->NAMEINHABER,\
 			STRASSE = :xxx->STRASSE,\
 			ORT = :xxx->ORT,\
 			POSTLEITZAHL = :xxx->POSTLEITZAHL,\
 			TELNR = :xxx->TELNR,\
 			TELNRDAFUE = :xxx->TELNRDAFUE,\
 			FAXNR = :xxx->FAXNR,\
 			TELKURZWAHL = :xxx->TELKURZWAHL,\
 			IMSBEZIRKNR = :xxx->IMSBEZIRKNR,\
 			PERSONALNRVERTR = :xxx->PERSONALNRVERTR,\
 			SKDSCHWERPUNKT1 = :xxx->SKDSCHWERPUNKT1,\
 			SKDSCHWERPUNKT2 = :xxx->SKDSCHWERPUNKT2,\
 			SKDSCHWERPUNKT3 = :xxx->SKDSCHWERPUNKT3,\
 			SKDSCHWERPUNKT4 = :xxx->SKDSCHWERPUNKT4,\
 			SKDSCHWERPUNKT5 = :xxx->SKDSCHWERPUNKT5,\
 			SKDKDKRITISCH = :xxx->SKDKDKRITISCH,\
 			MENGENATRABASIS = :xxx->MENGENATRABASIS,\
 			MENGENATRA = :xxx->MENGENATRA,\
 			KUNDE_SEIT = :xxx->KUNDE_SEIT,\
 			URLAUB_VON = :xxx->URLAUB_VON,\
 			URLAUB_BIS = :xxx->URLAUB_BIS,\
 			VERSAND_KOSTEN = :xxx->VERSAND_KOSTEN,\
 			SKDEILSPERRE = :xxx->SKDEILSPERRE,\
 			SKDVIPKUNDE = :xxx->SKDVIPKUNDE,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			IMS3000 = :xxx->IMS3000,\
 			LOGISTIKAUFSCHLAG = :xxx->LOGISTIKAUFSCHLAG

 #define LS_KNDAUSKU_EILBOTENZUSCHLAG     7
 #define LS_KNDAUSKU_MONATSUMSATZ         11
 #define LS_KNDAUSKU_MALUSFREI_PROZ       7
 #define LS_KNDAUSKU_VERTRETER_2          7
 #define LS_KNDAUSKU_IDFNR                11
 #define LS_KNDAUSKU_MATCHCODE            13
 #define LS_KNDAUSKU_FILIALNR             7
 #define LS_KNDAUSKU_ETARTKLASSE1         6
 #define LS_KNDAUSKU_ETARTKLASSE2         6
 #define LS_KNDAUSKU_ETKDMERKMAL1         6
 #define LS_KNDAUSKU_ETKDMERKMAL2         6
 #define LS_KNDAUSKU_NAMEAPO              41
 #define LS_KNDAUSKU_NAMEINHABER          31
 #define LS_KNDAUSKU_STRASSE              41
 #define LS_KNDAUSKU_ORT                  31
 #define LS_KNDAUSKU_POSTLEITZAHL         8
 #define LS_KNDAUSKU_TELNR                21
 #define LS_KNDAUSKU_TELNRDAFUE           21
 #define LS_KNDAUSKU_FAXNR                21
 #define LS_KNDAUSKU_TELKURZWAHL          5
 #define LS_KNDAUSKU_IMSBEZIRKNR          11
 #define LS_KNDAUSKU_PERSONALNRVERTR      11
 #define LS_KNDAUSKU_SKDSCHWERPUNKT1      2
 #define LS_KNDAUSKU_SKDSCHWERPUNKT2      2
 #define LS_KNDAUSKU_SKDSCHWERPUNKT3      2
 #define LS_KNDAUSKU_SKDSCHWERPUNKT4      2
 #define LS_KNDAUSKU_SKDSCHWERPUNKT5      2
 #define LS_KNDAUSKU_SKDKDKRITISCH        2
 #define LS_KNDAUSKU_MENGENATRABASIS      11
 #define LS_KNDAUSKU_MENGENATRA           11
 #define LS_KNDAUSKU_KUNDE_SEIT           11
 #define LS_KNDAUSKU_URLAUB_VON           11
 #define LS_KNDAUSKU_URLAUB_BIS           11
 #define LS_KNDAUSKU_VERSAND_KOSTEN       7
 #define LS_KNDAUSKU_SKDEILSPERRE         2
 #define LS_KNDAUSKU_SKDVIPKUNDE          2
 #define LS_KNDAUSKU_KUNDENNR             11
 #define LS_KNDAUSKU_VERTRIEBSZENTRUMNR   7
 #define LS_KNDAUSKU_IMS3000			  11
 #define LS_KNDAUSKU_LOGISTIKAUFSCHLAG    7
 #define LS_KNDAUSKU_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDAUSKU {
		 double  EILBOTENZUSCHLAG;
		 double  MONATSUMSATZ;
		 double  MALUSFREI_PROZ;
		 short   VERTRETER_2;
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 long    PERSONALNRVERTR;
		 char    SKDSCHWERPUNKT1[1 + 1];
		 char    SKDSCHWERPUNKT2[1 + 1];
		 char    SKDSCHWERPUNKT3[1 + 1];
		 char    SKDSCHWERPUNKT4[1 + 1];
		 char    SKDSCHWERPUNKT5[1 + 1];
		 char    SKDKDKRITISCH[1 + 1];
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 long    KUNDE_SEIT;
		 long    URLAUB_VON;
		 long    URLAUB_BIS;
		 double  VERSAND_KOSTEN;
		 char    SKDEILSPERRE[1 + 1];
		 char    SKDVIPKUNDE[1 + 1];
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    IMS3000;
		 double  LOGISTIKAUFSCHLAG;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDAUSKU {
		 double  EILBOTENZUSCHLAG;
		 double  MONATSUMSATZ;
		 double  MALUSFREI_PROZ;
		 short   VERTRETER_2;
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 long    PERSONALNRVERTR;
		 char    SKDSCHWERPUNKT1;
		 char    SKDSCHWERPUNKT2;
		 char    SKDSCHWERPUNKT3;
		 char    SKDSCHWERPUNKT4;
		 char    SKDSCHWERPUNKT5;
		 char    SKDKDKRITISCH;
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 long    KUNDE_SEIT;
		 long    URLAUB_VON;
		 long    URLAUB_BIS;
		 double  VERSAND_KOSTEN;
		 char    SKDEILSPERRE;
		 char    SKDVIPKUNDE;
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    IMS3000;
		 double  LOGISTIKAUFSCHLAG;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDAUSKU {
		 short  EILBOTENZUSCHLAG;
		 short  MONATSUMSATZ;
		 short  MALUSFREI_PROZ;
		 short  VERTRETER_2;
		 short  IDFNR;
		 short  MATCHCODE;
		 short  FILIALNR;
		 short  ETARTKLASSE1;
		 short  ETARTKLASSE2;
		 short  ETKDMERKMAL1;
		 short  ETKDMERKMAL2;
		 short  NAMEAPO;
		 short  NAMEINHABER;
		 short  STRASSE;
		 short  ORT;
		 short  POSTLEITZAHL;
		 short  TELNR;
		 short  TELNRDAFUE;
		 short  FAXNR;
		 short  TELKURZWAHL;
		 short  IMSBEZIRKNR;
		 short  PERSONALNRVERTR;
		 short  SKDSCHWERPUNKT1;
		 short  SKDSCHWERPUNKT2;
		 short  SKDSCHWERPUNKT3;
		 short  SKDSCHWERPUNKT4;
		 short  SKDSCHWERPUNKT5;
		 short  SKDKDKRITISCH;
		 short  MENGENATRABASIS;
		 short  MENGENATRA;
		 short  KUNDE_SEIT;
		 short  URLAUB_VON;
		 short  URLAUB_BIS;
		 short  VERSAND_KOSTEN;
		 short  SKDEILSPERRE;
		 short  SKDVIPKUNDE;
		 short  KUNDENNR;
		 short  VERTRIEBSZENTRUMNR;
		 short  IMS3000;
		 short  LOGISTIKAUFSCHLAG;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDAUSKU {
		 char    EILBOTENZUSCHLAG[5 + 2];
		 char    MONATSUMSATZ[9 + 2];
		 char    MALUSFREI_PROZ[5 + 2];
		 char    VERTRETER_2[7];
		 char    IDFNR[11];
		 char    MATCHCODE[12 + 1];
		 char    FILIALNR[7];
		 char    ETARTKLASSE1[5 + 1];
		 char    ETARTKLASSE2[5 + 1];
		 char    ETKDMERKMAL1[5 + 1];
		 char    ETKDMERKMAL2[5 + 1];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    IMSBEZIRKNR[11];
		 char    PERSONALNRVERTR[11];
		 char    SKDSCHWERPUNKT1[1 + 1];
		 char    SKDSCHWERPUNKT2[1 + 1];
		 char    SKDSCHWERPUNKT3[1 + 1];
		 char    SKDSCHWERPUNKT4[1 + 1];
		 char    SKDSCHWERPUNKT5[1 + 1];
		 char    SKDKDKRITISCH[1 + 1];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    KUNDE_SEIT[11];
		 char    URLAUB_VON[11];
		 char    URLAUB_BIS[11];
		 char    VERSAND_KOSTEN[5 + 2];
		 char    SKDEILSPERRE[1 + 1];
		 char    SKDVIPKUNDE[1 + 1];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    IMS3000[11];
		 char    LOGISTIKAUFSCHLAG[5 + 2];
		 char    FETCH_REL[11];
       };

 struct O_KNDAUSKU {
		 char    EILBOTENZUSCHLAG[5];
		 char    MONATSUMSATZ[9];
		 char    MALUSFREI_PROZ[5];
		 char    VERTRETER_2[7];
		 char    IDFNR[11];
		 char    MATCHCODE[12];
		 char    FILIALNR[7];
		 char    ETARTKLASSE1[5];
		 char    ETARTKLASSE2[5];
		 char    ETKDMERKMAL1[5];
		 char    ETKDMERKMAL2[5];
		 char    NAMEAPO[40];
		 char    NAMEINHABER[30];
		 char    STRASSE[40];
		 char    ORT[30];
		 char    POSTLEITZAHL[7];
		 char    TELNR[20];
		 char    TELNRDAFUE[20];
		 char    FAXNR[20];
		 char    TELKURZWAHL[4];
		 char    IMSBEZIRKNR[11];
		 char    PERSONALNRVERTR[11];
		 char    SKDSCHWERPUNKT1[1];
		 char    SKDSCHWERPUNKT2[1];
		 char    SKDSCHWERPUNKT3[1];
		 char    SKDSCHWERPUNKT4[1];
		 char    SKDSCHWERPUNKT5[1];
		 char    SKDKDKRITISCH[1];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    KUNDE_SEIT[11];
		 char    URLAUB_VON[11];
		 char    URLAUB_BIS[11];
		 char    VERSAND_KOSTEN[5];
		 char    SKDEILSPERRE[1];
		 char    SKDVIPKUNDE[1];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    IMS3000[11];
		 char    LOGISTIKAUFSCHLAG[5];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDAUSKU
 {
  public:

  KNDAUSKU s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDAUSKU_BES, KNDAUSKU_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDAUSKU_BES, KNDAUSKU_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDAUSKU_BES, KNDAUSKU_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDAUSKU()
  {
   ::buf_default((void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ);
  }
 };
#endif

#define KNDAUSKU_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 EILBOTENZUSCHLAG DECIMAL(5,2)      ,\
		 MONATSUMSATZ DECIMAL(9,2)      ,\
		 MALUSFREI_PROZ DECIMAL(5,2)      ,\
		 VERTRETER_2 SMALLINT          ,\
		 IDFNR INTEGER           ,\
		 MATCHCODE CHAR(12)          ,\
		 FILIALNR SMALLINT          ,\
		 ETARTKLASSE1 INTEGER,\
		 ETARTKLASSE2 INTEGER,\
		 ETKDMERKMAL1 INTEGER,\
		 ETKDMERKMAL2 INTEGER,\
		 NAMEAPO CHAR(40)          ,\
		 NAMEINHABER CHAR(30)          ,\
		 STRASSE CHAR(40)          ,\
		 ORT CHAR(30)          ,\
		 POSTLEITZAHL CHAR(7)           ,\
		 TELNR CHAR(20)          ,\
		 TELNRDAFUE CHAR(20)          ,\
		 FAXNR CHAR(20)          ,\
		 TELKURZWAHL CHAR(4)           ,\
		 IMSBEZIRKNR INTEGER           ,\
		 PERSONALNRVERTR INTEGER           ,\
		 SKDSCHWERPUNKT1 CHAR(1)           ,\
		 SKDSCHWERPUNKT2 CHAR(1)           ,\
		 SKDSCHWERPUNKT3 CHAR(1)           ,\
		 SKDSCHWERPUNKT4 CHAR(1)           ,\
		 SKDSCHWERPUNKT5 CHAR(1)           ,\
		 SKDKDKRITISCH CHAR(1)           ,\
		 MENGENATRABASIS INTEGER           ,\
		 MENGENATRA INTEGER           ,\
		 KUNDE_SEIT INTEGER           ,\
		 URLAUB_VON INTEGER           ,\
		 URLAUB_BIS INTEGER           ,\
		 VERSAND_KOSTEN DECIMAL(5,2)      ,\
		 SKDEILSPERRE CHAR(1)           ,\
		 SKDVIPKUNDE CHAR(1)           ,\
		 KUNDENNR INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 IMS3000 INTEGER           ,\
		 LOGISTIKAUFSCHLAG DECIMAL(5,2)      ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 1863 LOCK MODE ROW;

#define KNDAUSKU_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEX             on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDMATCHCODEX       on yyy( MATCHCODE );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDAUSKU_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEX            ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDMATCHCODEX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDINF_IDFNR                11
 #define L_KNDINF_MATCHCODE            12
 #define L_KNDINF_FILIALNR             6
 #define L_KNDINF_KDNR                 11
 #define L_KNDINF_ETARTKLASSE1         5
 #define L_KNDINF_ETARTKLASSE2         5
 #define L_KNDINF_ETKDMERKMAL1         5
 #define L_KNDINF_ETKDMERKMAL2         5
 #define L_KNDINF_ANREDEKZ             6
 #define L_KNDINF_NAMEAPO              40
 #define L_KNDINF_NAMEINHABER          30
 #define L_KNDINF_STRASSE              40
 #define L_KNDINF_ORT                  30
 #define L_KNDINF_POSTLEITZAHL         7
 #define L_KNDINF_TELNR                20
 #define L_KNDINF_TELNRDAFUE           20
 #define L_KNDINF_FAXNR                20
 #define L_KNDINF_TELKURZWAHL          4
 #define L_KNDINF_IMSBEZIRKNR          11
 #define L_KNDINF_KDGRUPPE             2
 #define L_KNDINF_PERSONALNRVERTR      11
 #define L_KNDINF_DAFUESYSTEM          2
 #define L_KNDINF_KZKDDOPPELKONTR      1
 #define L_KNDINF_LAGERFACHNRRGBEI     4
 #define L_KNDINF_ANZPOSLS_RG          6
 #define L_KNDINF_ANZPOSSORTBEHAELT    6
 #define L_KNDINF_KZKDKLASSE           3
 #define L_KNDINF_ORIGINALFILIALNR     6
 #define L_KNDINF_NOTFILIALNR          6
 #define L_KNDINF_BEMERKUNGEN          240
 #define L_KNDINF_KUNDETEXT            240
 #define L_KNDINF_STDAUFKOBUART        4
 #define L_KNDINF_VERBUNDKUNDE         1
 #define L_KNDINF_KUNDENNR             11
 #define L_KNDINF_VERTRIEBSZENTRUMNR   6
 #define L_KNDINF_SKDGIVEPRODQUOTA     1
 #define L_KNDINF_EMAILADRESSE	       60
 #define L_KNDINF_SKDSCHWERPUNKT2      1
 #define L_KNDINF_LINEFEE			   5
 #define N_KNDINF_LINEFEE		       2
 #define L_KNDINF_PACKAGEFEE		   5
 #define N_KNDINF_PACKAGEFEE	       2
 #define L_KNDINF_SENDCOLLECTIVINVOICE 1


 #define L_KNDINF_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDINF_ANZ ( sizeof(KNDINF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDINF sizeof(struct KNDINF)


 #define KNDINF_H

 #define KNDINF_LISTE \
 			KUNDE.IDFNR, \
 			KUNDE.MATCHCODE, \
 			KUNDE.FILIALNR, \
 			KUNDE.KDNR, \
 			KUNDE.ETARTKLASSE1, \
 			KUNDE.ETARTKLASSE2, \
 			KUNDE.ETKDMERKMAL1, \
 			KUNDE.ETKDMERKMAL2, \
 			KUNDE.ANREDEKZ, \
 			KUNDE.NAMEAPO, \
 			KUNDE.NAMEINHABER, \
 			KUNDE.STRASSE, \
 			KUNDE.ORT, \
 			KUNDE.POSTLEITZAHL, \
 			KUNDE.TELNR, \
 			KUNDE.TELNRDAFUE, \
 			KUNDE.FAXNR, \
 			KUNDE.TELKURZWAHL, \
 			KUNDE.IMSBEZIRKNR, \
 			KUNDE.KDGRUPPE, \
 			KUNDE.PERSONALNRVERTR, \
 			KUNDE.DAFUESYSTEM, \
 			KUNDE.KZKDDOPPELKONTR, \
 			KUNDE.LAGERFACHNRRGBEI, \
 			KUNDE.ANZPOSLS_RG, \
 			KUNDE.ANZPOSSORTBEHAELT, \
 			KUNDE.KZKDKLASSE, \
 			KUNDE.ORIGINALFILIALNR, \
 			KUNDE.NOTFILIALNR, \
 			KUNDE.BEMERKUNGEN, \
 			KUNDE.KUNDETEXT, \
 			KUNDE.STDAUFKOBUART, \
 			KUNDE.VERBUNDKUNDE, \
 			KUNDE.KUNDENNR, \
 			KUNDE.VERTRIEBSZENTRUMNR, \
 			KUNDESCHALTER.SKDGIVEPRODQUOTA, \
 			KUNDE.EMAILADRESSE, \
			KUNDESCHALTER.SKDSCHWERPUNKT2, \
			KUNDE.LINEFEE, \
			KUNDE.PACKAGEFEE, \
			KUNDE.SENDCOLLECTIVINVOICE

#define KNDINF_PLISTE \
 			"KUNDE.IDFNR," \
 			"KUNDE.MATCHCODE," \
 			"KUNDE.FILIALNR," \
 			"KUNDE.KDNR," \
 			"KUNDE.ETARTKLASSE1," \
 			"KUNDE.ETARTKLASSE2," \
 			"KUNDE.ETKDMERKMAL1," \
 			"KUNDE.ETKDMERKMAL2," \
 			"KUNDE.ANREDEKZ," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.NAMEINHABER," \
 			"KUNDE.STRASSE," \
 			"KUNDE.ORT," \
 			"KUNDE.POSTLEITZAHL," \
 			"KUNDE.TELNR," \
 			"KUNDE.TELNRDAFUE," \
 			"KUNDE.FAXNR," \
 			"KUNDE.TELKURZWAHL," \
 			"KUNDE.IMSBEZIRKNR," \
 			"KUNDE.KDGRUPPE," \
 			"KUNDE.PERSONALNRVERTR," \
 			"KUNDE.DAFUESYSTEM," \
 			"KUNDE.KZKDDOPPELKONTR," \
 			"KUNDE.LAGERFACHNRRGBEI," \
 			"KUNDE.ANZPOSLS_RG," \
 			"KUNDE.ANZPOSSORTBEHAELT," \
 			"KUNDE.KZKDKLASSE," \
 			"KUNDE.ORIGINALFILIALNR," \
 			"KUNDE.NOTFILIALNR," \
 			"KUNDE.BEMERKUNGEN," \
 			"KUNDE.KUNDETEXT," \
 			"KUNDE.STDAUFKOBUART," \
 			"KUNDE.VERBUNDKUNDE," \
 			"KUNDE.KUNDENNR," \
 			"KUNDE.VERTRIEBSZENTRUMNR," \
 			"KUNDESCHALTER.SKDGIVEPRODQUOTA," \
 			"KUNDE.EMAILADRESSE," \
			"KUNDESCHALTER.SKDSCHWERPUNKT2," \
			"KUNDE.LINEFEE," \
			"KUNDE.PACKAGEFEE," \
			"KUNDE.SENDCOLLECTIVINVOICE "

 #define KNDINF_PELISTE \
 			"IDFNR," \
 			"MATCHCODE," \
 			"FILIALNR," \
 			"KDNR," \
 			"ETARTKLASSE1," \
 			"ETARTKLASSE2," \
 			"ETKDMERKMAL1," \
 			"ETKDMERKMAL2," \
 			"ANREDEKZ," \
 			"NAMEAPO," \
 			"NAMEINHABER," \
 			"STRASSE," \
 			"ORT," \
 			"POSTLEITZAHL," \
 			"TELNR," \
 			"TELNRDAFUE," \
 			"FAXNR," \
 			"TELKURZWAHL," \
 			"IMSBEZIRKNR," \
 			"KDGRUPPE," \
 			"PERSONALNRVERTR," \
 			"DAFUESYSTEM," \
 			"KZKDDOPPELKONTR," \
 			"LAGERFACHNRRGBEI," \
 			"ANZPOSLS_RG," \
 			"ANZPOSSORTBEHAELT," \
 			"KZKDKLASSE," \
 			"ORIGINALFILIALNR," \
 			"NOTFILIALNR," \
 			"BEMERKUNGEN," \
 			"KUNDETEXT," \
 			"STDAUFKOBUART," \
 			"VERBUNDKUNDE," \
 			"KUNDENNR," \
 			"VERTRIEBSZENTRUMNR," \
 			"SKDGIVEPRODQUOTA," \
 			"EMAILADRESSE," \
			"SKDSCHWERPUNKT2," \
			"LINEFEE," \
			"PACKAGEFEE," \
			"SENDCOLLECTIVINVOICE "

 #define KNDINF_UPDLISTE \
 			"IDFNR=?," \
 			"MATCHCODE=?," \
 			"FILIALNR=?," \
 			"KDNR=?," \
 			"ETARTKLASSE1=?," \
 			"ETARTKLASSE2=?," \
 			"ETKDMERKMAL1=?," \
 			"ETKDMERKMAL2=?," \
 			"ANREDEKZ=?," \
 			"NAMEAPO=?," \
 			"NAMEINHABER=?," \
 			"STRASSE=?," \
 			"ORT=?," \
 			"POSTLEITZAHL=?," \
 			"TELNR=?," \
 			"TELNRDAFUE=?," \
 			"FAXNR=?," \
 			"TELKURZWAHL=?," \
 			"IMSBEZIRKNR=?," \
 			"KDGRUPPE=?," \
 			"PERSONALNRVERTR=?," \
 			"DAFUESYSTEM=?," \
 			"KZKDDOPPELKONTR=?," \
 			"LAGERFACHNRRGBEI=?," \
 			"ANZPOSLS_RG=?," \
 			"ANZPOSSORTBEHAELT=?," \
 			"KZKDKLASSE=?," \
 			"ORIGINALFILIALNR=?," \
 			"NOTFILIALNR=?," \
 			"BEMERKUNGEN=?," \
 			"KUNDETEXT=?," \
 			"STDAUFKOBUART=?," \
 			"VERBUNDKUNDE=?," \
 			"KUNDENNR=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"SKDGIVEPRODQUOTA=?," \
 			"EMAILADRESSE=?," \
			"SKDSCHWERPUNKT2=?," \
			"LINEFEE=?," \
			"PACKAGEFEE=?," \
			"SENDCOLLECTIVINVOICE=? "

 #define KNDINFIDFNR                         0
 #define KNDINFMATCHCODE                     1
 #define KNDINFFILIALNR                      2
 #define KNDINFKDNR                          3
 #define KNDINFETARTKLASSE1                  4
 #define KNDINFETARTKLASSE2                  5
 #define KNDINFETKDMERKMAL1                  6
 #define KNDINFETKDMERKMAL2                  7
 #define KNDINFANREDEKZ                      8
 #define KNDINFNAMEAPO                       9
 #define KNDINFNAMEINHABER                   10
 #define KNDINFSTRASSE                       11
 #define KNDINFORT                           12
 #define KNDINFPOSTLEITZAHL                  13
 #define KNDINFTELNR                         14
 #define KNDINFTELNRDAFUE                    15
 #define KNDINFFAXNR                         16
 #define KNDINFTELKURZWAHL                   17
 #define KNDINFIMSBEZIRKNR                   18
 #define KNDINFKDGRUPPE                      19
 #define KNDINFPERSONALNRVERTR               20
 #define KNDINFDAFUESYSTEM                   21
 #define KNDINFKZKDDOPPELKONTR               22
 #define KNDINFLAGERFACHNRRGBEI              23
 #define KNDINFANZPOSLS_RG                   24
 #define KNDINFANZPOSSORTBEHAELT             25
 #define KNDINFKZKDKLASSE                    26
 #define KNDINFORIGINALFILIALNR              27
 #define KNDINFNOTFILIALNR                   28
 #define KNDINFBEMERKUNGEN                   29
 #define KNDINFKUNDETEXT                     30
 #define KNDINFSTDAUFKOBUART                 31
 #define KNDINFVERBUNDKUNDE                  32
 #define KNDINFKUNDENNR						 33
 #define KNDINFVERTRIEBSZENTRUMNR			 34
 #define KNDINFSKDGIVEPRODQUOTA				 35
 #define KNDINFEMAILADRESSE					 36
 #define KNDINFSKDSCHWERPUNKT2				 37
 #define KNDINFLINEFEE						 38
 #define KNDINFPACKAGEFEE					 39
 #define KNDINFSENDCOLLECTIVINVOICE			 40

 #define KNDINF_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->MATCHCODE,\
 			:xxx->FILIALNR,\
 			:xxx->KDNR,\
 			:xxx->ETARTKLASSE1,\
 			:xxx->ETARTKLASSE2,\
 			:xxx->ETKDMERKMAL1,\
 			:xxx->ETKDMERKMAL2,\
 			:xxx->ANREDEKZ,\
 			:xxx->NAMEAPO,\
 			:xxx->NAMEINHABER,\
 			:xxx->STRASSE,\
 			:xxx->ORT,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->TELNR,\
 			:xxx->TELNRDAFUE,\
 			:xxx->FAXNR,\
 			:xxx->TELKURZWAHL,\
 			:xxx->IMSBEZIRKNR,\
 			:xxx->KDGRUPPE,\
 			:xxx->PERSONALNRVERTR,\
 			:xxx->DAFUESYSTEM,\
 			:xxx->KZKDDOPPELKONTR,\
 			:xxx->LAGERFACHNRRGBEI,\
 			:xxx->ANZPOSLS_RG,\
 			:xxx->ANZPOSSORTBEHAELT,\
 			:xxx->KZKDKLASSE,\
 			:xxx->ORIGINALFILIALNR,\
 			:xxx->NOTFILIALNR,\
 			:xxx->BEMERKUNGEN,\
 			:xxx->KUNDETEXT,\
 			:xxx->STDAUFKOBUART,\
 			:xxx->VERBUNDKUNDE,\
 			:xxx->KUNDENNR,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->SKDGIVEPRODQUOTA,\
 			:xxx->EMAILADRESSE,\
			:xxx->SKDSCHWERPUNKT2,\
			:xxx->LINEFEE,\
			:xxx->PACKAGEFEE,\
			:xxx->SENDCOLLECTIVINVOICE

 #define KNDINF_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			MATCHCODE = :xxx->MATCHCODE,\
 			FILIALNR = :xxx->FILIALNR,\
 			KDNR = :xxx->KDNR,\
 			ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
 			ETARTKLASSE2 = :xxx->ETARTKLASSE2,\
 			ETKDMERKMAL1 = :xxx->ETKDMERKMAL1,\
 			ETKDMERKMAL2 = :xxx->ETKDMERKMAL2,\
 			ANREDEKZ = :xxx->ANREDEKZ,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			NAMEINHABER = :xxx->NAMEINHABER,\
 			STRASSE = :xxx->STRASSE,\
 			ORT = :xxx->ORT,\
 			POSTLEITZAHL = :xxx->POSTLEITZAHL,\
 			TELNR = :xxx->TELNR,\
 			TELNRDAFUE = :xxx->TELNRDAFUE,\
 			FAXNR = :xxx->FAXNR,\
 			TELKURZWAHL = :xxx->TELKURZWAHL,\
 			IMSBEZIRKNR = :xxx->IMSBEZIRKNR,\
 			KDGRUPPE = :xxx->KDGRUPPE,\
 			PERSONALNRVERTR = :xxx->PERSONALNRVERTR,\
 			DAFUESYSTEM = :xxx->DAFUESYSTEM,\
 			KZKDDOPPELKONTR = :xxx->KZKDDOPPELKONTR,\
 			LAGERFACHNRRGBEI = :xxx->LAGERFACHNRRGBEI,\
 			ANZPOSLS_RG = :xxx->ANZPOSLS_RG,\
 			ANZPOSSORTBEHAELT = :xxx->ANZPOSSORTBEHAELT,\
 			KZKDKLASSE = :xxx->KZKDKLASSE,\
 			ORIGINALFILIALNR = :xxx->ORIGINALFILIALNR,\
 			NOTFILIALNR = :xxx->NOTFILIALNR,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
 			KUNDETEXT = :xxx->KUNDETEXT,\
 			STDAUFKOBUART = :xxx->STDAUFKOBUART,\
 			VERBUNDKUNDE = :xxx->VERBUNDKUNDE,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			SKDGIVEPRODQUOTA = :xxx->SKDGIVEPRODQUOTA,\
 			EMAILADRESSE = :xxx->EMAILADRESSE,\
			SKDSCHWERPUNKT2 = :xxx->SKDSCHWERPUNKT2,\
			LINEFEE = :xxx->LINEFEE, \
			PACKAGEFEE = :xxx->PACKAGEFEE, \
			SENDCOLLECTIVINVOICE = :xxx->SENDCOLLECTIVINVOICE

 #define LS_KNDINF_IDFNR                11
 #define LS_KNDINF_MATCHCODE            13
 #define LS_KNDINF_FILIALNR             7
 #define LS_KNDINF_KDNR                 11
 #define LS_KNDINF_ETARTKLASSE1         6
 #define LS_KNDINF_ETARTKLASSE2         6
 #define LS_KNDINF_ETKDMERKMAL1         6
 #define LS_KNDINF_ETKDMERKMAL2         6
 #define LS_KNDINF_ANREDEKZ             7
 #define LS_KNDINF_NAMEAPO              41
 #define LS_KNDINF_NAMEINHABER          31
 #define LS_KNDINF_STRASSE              41
 #define LS_KNDINF_ORT                  31
 #define LS_KNDINF_POSTLEITZAHL         8
 #define LS_KNDINF_TELNR                21
 #define LS_KNDINF_TELNRDAFUE           21
 #define LS_KNDINF_FAXNR                21
 #define LS_KNDINF_TELKURZWAHL          5
 #define LS_KNDINF_IMSBEZIRKNR          11
 #define LS_KNDINF_KDGRUPPE             3
 #define LS_KNDINF_PERSONALNRVERTR      11
 #define LS_KNDINF_DAFUESYSTEM          3
 #define LS_KNDINF_KZKDDOPPELKONTR      2
 #define LS_KNDINF_LAGERFACHNRRGBEI     5
 #define LS_KNDINF_ANZPOSLS_RG          7
 #define LS_KNDINF_ANZPOSSORTBEHAELT    7
 #define LS_KNDINF_KZKDKLASSE           4
 #define LS_KNDINF_ORIGINALFILIALNR     7
 #define LS_KNDINF_NOTFILIALNR          7
 #define LS_KNDINF_BEMERKUNGEN          241
 #define LS_KNDINF_KUNDETEXT            241
 #define LS_KNDINF_STDAUFKOBUART        5
 #define LS_KNDINF_VERBUNDKUNDE         2
 #define LS_KNDINF_KUNDENNR             11
 #define LS_KNDINF_VERTRIEBSZENTRUMNR   7
 #define LS_KNDINF_SKDGIVEPRODQUOTA     2
 #define LS_KNDINF_EMAILADRESSE		    61
 #define LS_KNDINF_SKDSCHWERPUNKT2      2
 #define LS_KNDINF_LINEFEE              7
 #define LS_KNDINF_PACKAGEFEE           7
 #define LS_KNDINF_SENDCOLLECTIVINVOICE 2
 #define LS_KNDINF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDINF {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    KDNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 short   ANREDEKZ;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 char    KDGRUPPE[2 + 1];
		 long    PERSONALNRVERTR;
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR[1 + 1];
		 char    LAGERFACHNRRGBEI[4 + 1];
		 short   ANZPOSLS_RG;
		 short   ANZPOSSORTBEHAELT;
		 char    KZKDKLASSE[3 + 1];
		 short   ORIGINALFILIALNR;
		 short   NOTFILIALNR;
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    STDAUFKOBUART[4 + 1];
		 char    VERBUNDKUNDE[1 + 1];
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 char	 SKDGIVEPRODQUOTA[1 + 1];
		 char	 EMAILADRESSE[60 + 1];
		 char	 SKDSCHWERPUNKT2[1 + 1];
		 double  LINEFEE;
		 double  PACKAGEFEE;
		 char	 SENDCOLLECTIVINVOICE[1 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDINF {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    KDNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 short   ANREDEKZ;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 char    KDGRUPPE[2 + 1];
		 long    PERSONALNRVERTR;
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR;
		 char    LAGERFACHNRRGBEI[4 + 1];
		 short   ANZPOSLS_RG;
		 short   ANZPOSSORTBEHAELT;
		 char    KZKDKLASSE[3 + 1];
		 short   ORIGINALFILIALNR;
		 short   NOTFILIALNR;
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    STDAUFKOBUART[4 + 1];
		 char    VERBUNDKUNDE;
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 char	 SKDGIVEPRODQUOTA;
		 char	 EMAILADRESSE[60 + 1];
		 char	 SKDSCHWERPUNKT2;
		 double  LINEFEE;
		 double  PACKAGEFEE;
		 char	 SENDCOLLECTIVINVOICE;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDINF {
		 short  IDFNR;
		 short  MATCHCODE;
		 short  FILIALNR;
		 short  KDNR;
		 short  ETARTKLASSE1;
		 short  ETARTKLASSE2;
		 short  ETKDMERKMAL1;
		 short  ETKDMERKMAL2;
		 short  ANREDEKZ;
		 short  NAMEAPO;
		 short  NAMEINHABER;
		 short  STRASSE;
		 short  ORT;
		 short  POSTLEITZAHL;
		 short  TELNR;
		 short  TELNRDAFUE;
		 short  FAXNR;
		 short  TELKURZWAHL;
		 short  IMSBEZIRKNR;
		 short  KDGRUPPE;
		 short  PERSONALNRVERTR;
		 short  DAFUESYSTEM;
		 short  KZKDDOPPELKONTR;
		 short  LAGERFACHNRRGBEI;
		 short  ANZPOSLS_RG;
		 short  ANZPOSSORTBEHAELT;
		 short  KZKDKLASSE;
		 short  ORIGINALFILIALNR;
		 short  NOTFILIALNR;
		 short  BEMERKUNGEN;
		 short  KUNDETEXT;
		 short  STDAUFKOBUART;
		 short  VERBUNDKUNDE;
		 short	KUNDENNR;
		 short	VERTRIEBSZENTRUMNR;
		 short	SKDGIVEPRODQUOTA;
		 short  EMAILADRESSE;
		 short  SKDSCHWERPUNKT2;
		 short  LINEFEE;
		 short  PACKAGEFEE;
		 short  SENDCOLLECTIVINVOICE;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDINF {
		 char    IDFNR[11];
		 char    MATCHCODE[12 + 1];
		 char    FILIALNR[7];
		 char    KDNR[11];
		 char    ETARTKLASSE1[5 + 1];
		 char    ETARTKLASSE2[5 + 1];
		 char    ETKDMERKMAL1[5 + 1];
		 char    ETKDMERKMAL2[5 + 1];
		 char    ANREDEKZ[7];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    IMSBEZIRKNR[11];
		 char    KDGRUPPE[2 + 1];
		 char    PERSONALNRVERTR[11];
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR[1 + 1];
		 char    LAGERFACHNRRGBEI[4 + 1];
		 char    ANZPOSLS_RG[7];
		 char    ANZPOSSORTBEHAELT[7];
		 char    KZKDKLASSE[3 + 1];
		 char    ORIGINALFILIALNR[7];
		 char    NOTFILIALNR[7];
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    STDAUFKOBUART[4 + 1];
		 char    VERBUNDKUNDE[1 + 1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 SKDGIVEPRODQUOTA[1 + 1];
		 char	 EMAILADRESSE[60 + 1];
		 char	 SKDSCHWERPUNKT2[1 + 1];
		 char    LINEFEE[5 + 2];
		 char    PACKAGEFEE[5 + 2];
		 char	 SENDCOLLECTIVINVOICE[1 + 1];
		 char    FETCH_REL[11];
       };

 struct O_KNDINF {
		 char    IDFNR[11];
		 char    MATCHCODE[12];
		 char    FILIALNR[7];
		 char    KDNR[11];
		 char    ETARTKLASSE1[5];
		 char    ETARTKLASSE2[5];
		 char    ETKDMERKMAL1[5];
		 char    ETKDMERKMAL2[5];
		 char    ANREDEKZ[7];
		 char    NAMEAPO[40];
		 char    NAMEINHABER[30];
		 char    STRASSE[40];
		 char    ORT[30];
		 char    POSTLEITZAHL[7];
		 char    TELNR[20];
		 char    TELNRDAFUE[20];
		 char    FAXNR[20];
		 char    TELKURZWAHL[4];
		 char    IMSBEZIRKNR[11];
		 char    KDGRUPPE[2];
		 char    PERSONALNRVERTR[11];
		 char    DAFUESYSTEM[2];
		 char    KZKDDOPPELKONTR[1];
		 char    LAGERFACHNRRGBEI[4];
		 char    ANZPOSLS_RG[7];
		 char    ANZPOSSORTBEHAELT[7];
		 char    KZKDKLASSE[3];
		 char    ORIGINALFILIALNR[7];
		 char    NOTFILIALNR[7];
		 char    BEMERKUNGEN[240];
		 char    KUNDETEXT[240];
		 char    STDAUFKOBUART[4];
		 char    VERBUNDKUNDE[1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 SKDGIVEPRODQUOTA[1];
		 char	 EMAILADRESSE[60];
		 char	 SKDSCHWERPUNKT2[1];
		 char    LINEFEE[5];
		 char    PACKAGEFEE[5];
		 char	 SENDCOLLECTIVINVOICE[1];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDINF_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   60 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDINF_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   60 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDINF
 {
  public:

  KNDINF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDINF_BES, KNDINF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDINF_BES, KNDINF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDINF_BES, KNDINF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDINF()
  {
   ::buf_default((void *)&s, KNDINF_BES, KNDINF_ANZ);
  }
 };
#endif

#define KNDINF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 MATCHCODE CHAR(12)          ,\
		 FILIALNR SMALLINT          ,\
		 KDNR INTEGER           ,\
		 ETARTKLASSE1 INTEGER,\
		 ETARTKLASSE2 INTEGER,\
		 ETKDMERKMAL1 INTEGER,\
		 ETKDMERKMAL2 INTEGER,\
		 ANREDEKZ SMALLINT          ,\
		 NAMEAPO CHAR(40)          ,\
		 NAMEINHABER CHAR(30)          ,\
		 STRASSE CHAR(40)          ,\
		 ORT CHAR(30)          ,\
		 POSTLEITZAHL CHAR(7)           ,\
		 TELNR CHAR(20)          ,\
		 TELNRDAFUE CHAR(20)          ,\
		 FAXNR CHAR(20)          ,\
		 TELKURZWAHL CHAR(4)           ,\
		 IMSBEZIRKNR INTEGER           ,\
		 KDGRUPPE CHAR(2)           ,\
		 PERSONALNRVERTR INTEGER           ,\
		 DAFUESYSTEM CHAR(2)           ,\
		 KZKDDOPPELKONTR CHAR(1)           ,\
		 LAGERFACHNRRGBEI CHAR(4)           ,\
		 ANZPOSLS_RG SMALLINT          ,\
		 ANZPOSSORTBEHAELT SMALLINT          ,\
		 KZKDKLASSE CHAR(3)           ,\
		 ORIGINALFILIALNR SMALLINT          ,\
		 NOTFILIALNR SMALLINT          ,\
		 BEMERKUNGEN VARCHAR(240,0)    ,\
		 KUNDETEXT VARCHAR(240,0)    ,\
		 STDAUFKOBUART CHAR(4)           ,\
		 VERBUNDKUNDE CHAR(1)           ,\
		 KUNDENNR INTEGER			,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 SKDGIVEPRODQUOTA CHAR(1)           ,\
		 EMAILADRESSE CHAR(60)           ,\
		 SKDSCHWERPUNKT2 CHAR(1)           ,\
		 LINEFEE DECIMAL(5,2)      ,\
		 PACKAGEFEE DECIMAL(5,2)      ,\
		 SENDCOLLECTIVINVOICE CHAR(1)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 1936 LOCK MODE ROW;

#define KNDINF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEX             on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDMATCHCODEX       on yyy( MATCHCODE );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KUNDE_315        on yyy( KDNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDINF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEX            ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDMATCHCODEX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KUNDE_315       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDMONUMS_IDFNR                11
 #define L_KNDMONUMS_JAHR                 6
 #define L_KNDMONUMS_MONAT                6
 #define L_KNDMONUMS_ANZFAKTURTAGE        6
 #define L_KNDMONUMS_BRUTTOUMS_AEP        9
 #define N_KNDMONUMS_BRUTTOUMS_AEP        2
 #define L_KNDMONUMS_BRUTTOUMS_GEP        9
 #define N_KNDMONUMS_BRUTTOUMS_GEP        2
 #define L_KNDMONUMS_UMSNN_NNAEP          9
 #define N_KNDMONUMS_UMSNN_NNAEP          2
 #define L_KNDMONUMS_UMSNN_NORMAEP        9
 #define N_KNDMONUMS_UMSNN_NORMAEP        2
 #define L_KNDMONUMS_RABATT               9
 #define N_KNDMONUMS_RABATT               2
 #define L_KNDMONUMS_HANDELSPANNE         9
 #define N_KNDMONUMS_HANDELSPANNE         2
 #define L_KNDMONUMS_ANZAUFTRAG           6
 #define L_KNDMONUMS_ANZZEILEN            11
 #define L_KNDMONUMS_ANZPOS               11
 #define L_KNDMONUMS_ANZPACK              11
 #define L_KNDMONUMS_BEDINGTRABFAEHIG     9
 #define N_KNDMONUMS_BEDINGTRABFAEHIG     2
 #define L_KNDMONUMS_NRABFAEHIG           9
 #define N_KNDMONUMS_NRABFAEHIG           2
 #define L_KNDMONUMS_RABATTIERT           9
 #define N_KNDMONUMS_RABATTIERT           2
 #define L_KNDMONUMS_UMSSKONTOMIND        9
 #define N_KNDMONUMS_UMSSKONTOMIND        2
 #define L_KNDMONUMS_UMSBONUSFAEHIG       9
 #define N_KNDMONUMS_UMSBONUSFAEHIG       2
 #define L_KNDMONUMS_WERTBONUSEINST       9
 #define N_KNDMONUMS_WERTBONUSEINST       2
 #define L_KNDMONUMS_WERTZEILULIMIT       9
 #define N_KNDMONUMS_WERTZEILULIMIT       2
 #define L_KNDMONUMS_WERTTEXT             9
 #define N_KNDMONUMS_WERTTEXT             2
 #define L_KNDMONUMS_KUNDENNR             11
 #define L_KNDMONUMS_VERTRIEBSZENTRUMNR   6


 #define L_KNDMONUMS_PKEY 23

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDMONUMS_ANZ ( sizeof(KNDMONUMS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDMONUMS sizeof(struct KNDMONUMS)


 #define KNDMONUMS_H

 #define KNDMONUMS_LISTE \
 			KUNDEMONUMS.IDFNR, \
 			KUNDEMONUMS.JAHR, \
 			KUNDEMONUMS.MONAT, \
 			KUNDEMONUMS.ANZFAKTURTAGE, \
 			KUNDEMONUMS.BRUTTOUMS_AEP, \
 			KUNDEMONUMS.BRUTTOUMS_GEP, \
 			KUNDEMONUMS.UMSNN_NNAEP, \
 			KUNDEMONUMS.UMSNN_NORMAEP, \
 			KUNDEMONUMS.RABATT, \
 			KUNDEMONUMS.HANDELSPANNE, \
 			KUNDEMONUMS.ANZAUFTRAG, \
 			KUNDEMONUMS.ANZZEILEN, \
 			KUNDEMONUMS.ANZPOS, \
 			KUNDEMONUMS.ANZPACK, \
 			KUNDEMONUMS.BEDINGTRABFAEHIG, \
 			KUNDEMONUMS.NRABFAEHIG, \
 			KUNDEMONUMS.RABATTIERT, \
 			KUNDEMONUMS.UMSSKONTOMIND, \
 			KUNDEMONUMS.UMSBONUSFAEHIG, \
 			KUNDEMONUMS.WERTBONUSEINST, \
 			KUNDEMONUMS.WERTZEILULIMIT, \
 			KUNDEMONUMS.WERTTEXT, \
			KUNDEMONUMS.KUNDENNR, \
			KUNDEMONUMS.VERTRIEBSZENTRUMNR
 #define KNDMONUMS_PLISTE \
 			"KUNDEMONUMS.IDFNR," \
 			"KUNDEMONUMS.JAHR," \
 			"KUNDEMONUMS.MONAT," \
 			"KUNDEMONUMS.ANZFAKTURTAGE," \
 			"KUNDEMONUMS.BRUTTOUMS_AEP," \
 			"KUNDEMONUMS.BRUTTOUMS_GEP," \
 			"KUNDEMONUMS.UMSNN_NNAEP," \
 			"KUNDEMONUMS.UMSNN_NORMAEP," \
 			"KUNDEMONUMS.RABATT," \
 			"KUNDEMONUMS.HANDELSPANNE," \
 			"KUNDEMONUMS.ANZAUFTRAG," \
 			"KUNDEMONUMS.ANZZEILEN," \
 			"KUNDEMONUMS.ANZPOS," \
 			"KUNDEMONUMS.ANZPACK," \
 			"KUNDEMONUMS.BEDINGTRABFAEHIG," \
 			"KUNDEMONUMS.NRABFAEHIG," \
 			"KUNDEMONUMS.RABATTIERT," \
 			"KUNDEMONUMS.UMSSKONTOMIND," \
 			"KUNDEMONUMS.UMSBONUSFAEHIG," \
 			"KUNDEMONUMS.WERTBONUSEINST," \
 			"KUNDEMONUMS.WERTZEILULIMIT," \
 			"KUNDEMONUMS.WERTTEXT," \
			"KUNDEMONUMS.KUNDENNR," \
			"KUNDEMONUMS.VERTRIEBSZENTRUMNR "

 #define KNDMONUMS_PELISTE \
 			"IDFNR," \
 			"JAHR," \
 			"MONAT," \
 			"ANZFAKTURTAGE," \
 			"BRUTTOUMS_AEP," \
 			"BRUTTOUMS_GEP," \
 			"UMSNN_NNAEP," \
 			"UMSNN_NORMAEP," \
 			"RABATT," \
 			"HANDELSPANNE," \
 			"ANZAUFTRAG," \
 			"ANZZEILEN," \
 			"ANZPOS," \
 			"ANZPACK," \
 			"BEDINGTRABFAEHIG," \
 			"NRABFAEHIG," \
 			"RABATTIERT," \
 			"UMSSKONTOMIND," \
 			"UMSBONUSFAEHIG," \
 			"WERTBONUSEINST," \
 			"WERTZEILULIMIT," \
 			"WERTTEXT," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR "

 #define KNDMONUMS_UPDLISTE \
 			"IDFNR=?," \
 			"JAHR=?," \
 			"MONAT=?," \
 			"ANZFAKTURTAGE=?," \
 			"BRUTTOUMS_AEP=?," \
 			"BRUTTOUMS_GEP=?," \
 			"UMSNN_NNAEP=?," \
 			"UMSNN_NORMAEP=?," \
 			"RABATT=?," \
 			"HANDELSPANNE=?," \
 			"ANZAUFTRAG=?," \
 			"ANZZEILEN=?," \
 			"ANZPOS=?," \
 			"ANZPACK=?," \
 			"BEDINGTRABFAEHIG=?," \
 			"NRABFAEHIG=?," \
 			"RABATTIERT=?," \
 			"UMSSKONTOMIND=?," \
 			"UMSBONUSFAEHIG=?," \
 			"WERTBONUSEINST=?," \
 			"WERTZEILULIMIT=?," \
 			"WERTTEXT=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=? "

 #define KNDMONUMSIDFNR                         0
 #define KNDMONUMSJAHR                          1
 #define KNDMONUMSMONAT                         2
 #define KNDMONUMSANZFAKTURTAGE                 3
 #define KNDMONUMSBRUTTOUMS_AEP                 4
 #define KNDMONUMSBRUTTOUMS_GEP                 5
 #define KNDMONUMSUMSNN_NNAEP                   6
 #define KNDMONUMSUMSNN_NORMAEP                 7
 #define KNDMONUMSRABATT                        8
 #define KNDMONUMSHANDELSPANNE                  9
 #define KNDMONUMSANZAUFTRAG                    10
 #define KNDMONUMSANZZEILEN                     11
 #define KNDMONUMSANZPOS                        12
 #define KNDMONUMSANZPACK                       13
 #define KNDMONUMSBEDINGTRABFAEHIG              14
 #define KNDMONUMSNRABFAEHIG                    15
 #define KNDMONUMSRABATTIERT                    16
 #define KNDMONUMSUMSSKONTOMIND                 17
 #define KNDMONUMSUMSBONUSFAEHIG                18
 #define KNDMONUMSWERTBONUSEINST                19
 #define KNDMONUMSWERTZEILULIMIT                20
 #define KNDMONUMSWERTTEXT                      21
 #define KNDMONUMSKUNDENNR						22
 #define KNDMONUMSVERTRIEBSZENTRUMNR			23

 #define KNDMONUMS_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->JAHR,\
 			:xxx->MONAT,\
 			:xxx->ANZFAKTURTAGE,\
 			:xxx->BRUTTOUMS_AEP,\
 			:xxx->BRUTTOUMS_GEP,\
 			:xxx->UMSNN_NNAEP,\
 			:xxx->UMSNN_NORMAEP,\
 			:xxx->RABATT,\
 			:xxx->HANDELSPANNE,\
 			:xxx->ANZAUFTRAG,\
 			:xxx->ANZZEILEN,\
 			:xxx->ANZPOS,\
 			:xxx->ANZPACK,\
 			:xxx->BEDINGTRABFAEHIG,\
 			:xxx->NRABFAEHIG,\
 			:xxx->RABATTIERT,\
 			:xxx->UMSSKONTOMIND,\
 			:xxx->UMSBONUSFAEHIG,\
 			:xxx->WERTBONUSEINST,\
 			:xxx->WERTZEILULIMIT,\
 			:xxx->WERTTEXT,\
			:xxx->KUNDENNR,\
			:xxx->VERTRIEBSZENTRUMNR

 #define KNDMONUMS_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			JAHR = :xxx->JAHR,\
 			MONAT = :xxx->MONAT,\
 			ANZFAKTURTAGE = :xxx->ANZFAKTURTAGE,\
 			BRUTTOUMS_AEP = :xxx->BRUTTOUMS_AEP,\
 			BRUTTOUMS_GEP = :xxx->BRUTTOUMS_GEP,\
 			UMSNN_NNAEP = :xxx->UMSNN_NNAEP,\
 			UMSNN_NORMAEP = :xxx->UMSNN_NORMAEP,\
 			RABATT = :xxx->RABATT,\
 			HANDELSPANNE = :xxx->HANDELSPANNE,\
 			ANZAUFTRAG = :xxx->ANZAUFTRAG,\
 			ANZZEILEN = :xxx->ANZZEILEN,\
 			ANZPOS = :xxx->ANZPOS,\
 			ANZPACK = :xxx->ANZPACK,\
 			BEDINGTRABFAEHIG = :xxx->BEDINGTRABFAEHIG,\
 			NRABFAEHIG = :xxx->NRABFAEHIG,\
 			RABATTIERT = :xxx->RABATTIERT,\
 			UMSSKONTOMIND = :xxx->UMSSKONTOMIND,\
 			UMSBONUSFAEHIG = :xxx->UMSBONUSFAEHIG,\
 			WERTBONUSEINST = :xxx->WERTBONUSEINST,\
 			WERTZEILULIMIT = :xxx->WERTZEILULIMIT,\
 			WERTTEXT = :xxx->WERTTEXT,\
			KUNDENNR = :xxx->KUNDENNR,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR

 #define LS_KNDMONUMS_IDFNR                11
 #define LS_KNDMONUMS_JAHR                 7
 #define LS_KNDMONUMS_MONAT                7
 #define LS_KNDMONUMS_ANZFAKTURTAGE        7
 #define LS_KNDMONUMS_BRUTTOUMS_AEP        11
 #define LS_KNDMONUMS_BRUTTOUMS_GEP        11
 #define LS_KNDMONUMS_UMSNN_NNAEP          11
 #define LS_KNDMONUMS_UMSNN_NORMAEP        11
 #define LS_KNDMONUMS_RABATT               11
 #define LS_KNDMONUMS_HANDELSPANNE         11
 #define LS_KNDMONUMS_ANZAUFTRAG           7
 #define LS_KNDMONUMS_ANZZEILEN            11
 #define LS_KNDMONUMS_ANZPOS               11
 #define LS_KNDMONUMS_ANZPACK              11
 #define LS_KNDMONUMS_BEDINGTRABFAEHIG     11
 #define LS_KNDMONUMS_NRABFAEHIG           11
 #define LS_KNDMONUMS_RABATTIERT           11
 #define LS_KNDMONUMS_UMSSKONTOMIND        11
 #define LS_KNDMONUMS_UMSBONUSFAEHIG       11
 #define LS_KNDMONUMS_WERTBONUSEINST       11
 #define LS_KNDMONUMS_WERTZEILULIMIT       11
 #define LS_KNDMONUMS_WERTTEXT             11
 #define LS_KNDMONUMS_KUNDENNR             11
 #define LS_KNDMONUMS_VERTRIEBSZENTRUMNR   7
 #define LS_KNDMONUMS_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDMONUMS {
		 long    IDFNR;
		 short   JAHR;
		 short   MONAT;
		 short   ANZFAKTURTAGE;
		 double  BRUTTOUMS_AEP;
		 double  BRUTTOUMS_GEP;
		 double  UMSNN_NNAEP;
		 double  UMSNN_NORMAEP;
		 double  RABATT;
		 double  HANDELSPANNE;
		 short   ANZAUFTRAG;
		 long    ANZZEILEN;
		 long    ANZPOS;
		 long    ANZPACK;
		 double  BEDINGTRABFAEHIG;
		 double  NRABFAEHIG;
		 double  RABATTIERT;
		 double  UMSSKONTOMIND;
		 double  UMSBONUSFAEHIG;
		 double  WERTBONUSEINST;
		 double  WERTZEILULIMIT;
		 double  WERTTEXT;
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDMONUMS {
		 long    IDFNR;
		 short   JAHR;
		 short   MONAT;
		 short   ANZFAKTURTAGE;
		 double  BRUTTOUMS_AEP;
		 double  BRUTTOUMS_GEP;
		 double  UMSNN_NNAEP;
		 double  UMSNN_NORMAEP;
		 double  RABATT;
		 double  HANDELSPANNE;
		 short   ANZAUFTRAG;
		 long    ANZZEILEN;
		 long    ANZPOS;
		 long    ANZPACK;
		 double  BEDINGTRABFAEHIG;
		 double  NRABFAEHIG;
		 double  RABATTIERT;
		 double  UMSSKONTOMIND;
		 double  UMSBONUSFAEHIG;
		 double  WERTBONUSEINST;
		 double  WERTZEILULIMIT;
		 double  WERTTEXT;
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDMONUMS {
		 short  IDFNR;
		 short  JAHR;
		 short  MONAT;
		 short  ANZFAKTURTAGE;
		 short  BRUTTOUMS_AEP;
		 short  BRUTTOUMS_GEP;
		 short  UMSNN_NNAEP;
		 short  UMSNN_NORMAEP;
		 short  RABATT;
		 short  HANDELSPANNE;
		 short  ANZAUFTRAG;
		 short  ANZZEILEN;
		 short  ANZPOS;
		 short  ANZPACK;
		 short  BEDINGTRABFAEHIG;
		 short  NRABFAEHIG;
		 short  RABATTIERT;
		 short  UMSSKONTOMIND;
		 short  UMSBONUSFAEHIG;
		 short  WERTBONUSEINST;
		 short  WERTZEILULIMIT;
		 short  WERTTEXT;
		 short	KUNDENNR;
		 short	VERTRIEBSZENTRUMNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDMONUMS {
		 char    IDFNR[11];
		 char    JAHR[7];
		 char    MONAT[7];
		 char    ANZFAKTURTAGE[7];
		 char    BRUTTOUMS_AEP[9 + 2];
		 char    BRUTTOUMS_GEP[9 + 2];
		 char    UMSNN_NNAEP[9 + 2];
		 char    UMSNN_NORMAEP[9 + 2];
		 char    RABATT[9 + 2];
		 char    HANDELSPANNE[9 + 2];
		 char    ANZAUFTRAG[7];
		 char    ANZZEILEN[11];
		 char    ANZPOS[11];
		 char    ANZPACK[11];
		 char    BEDINGTRABFAEHIG[9 + 2];
		 char    NRABFAEHIG[9 + 2];
		 char    RABATTIERT[9 + 2];
		 char    UMSSKONTOMIND[9 + 2];
		 char    UMSBONUSFAEHIG[9 + 2];
		 char    WERTBONUSEINST[9 + 2];
		 char    WERTZEILULIMIT[9 + 2];
		 char    WERTTEXT[9 + 2];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

 struct O_KNDMONUMS {
		 char    IDFNR[11];
		 char    JAHR[7];
		 char    MONAT[7];
		 char    ANZFAKTURTAGE[7];
		 char    BRUTTOUMS_AEP[9];
		 char    BRUTTOUMS_GEP[9];
		 char    UMSNN_NNAEP[9];
		 char    UMSNN_NORMAEP[9];
		 char    RABATT[9];
		 char    HANDELSPANNE[9];
		 char    ANZAUFTRAG[7];
		 char    ANZZEILEN[11];
		 char    ANZPOS[11];
		 char    ANZPACK[11];
		 char    BEDINGTRABFAEHIG[9];
		 char    NRABFAEHIG[9];
		 char    RABATTIERT[9];
		 char    UMSSKONTOMIND[9];
		 char    UMSBONUSFAEHIG[9];
		 char    WERTBONUSEINST[9];
		 char    WERTZEILULIMIT[9];
		 char    WERTTEXT[9];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDMONUMS_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDMONUMS_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDMONUMS
 {
  public:

  KNDMONUMS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDMONUMS_BES, KNDMONUMS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDMONUMS_BES, KNDMONUMS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDMONUMS_BES, KNDMONUMS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDMONUMS()
  {
   ::buf_default((void *)&s, KNDMONUMS_BES, KNDMONUMS_ANZ);
  }
 };
#endif

#define KNDMONUMS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 JAHR SMALLINT          ,\
		 MONAT SMALLINT          ,\
		 ANZFAKTURTAGE SMALLINT          ,\
		 BRUTTOUMS_AEP DECIMAL(9,2)      ,\
		 BRUTTOUMS_GEP DECIMAL(9,2)      ,\
		 UMSNN_NNAEP DECIMAL(9,2)      ,\
		 UMSNN_NORMAEP DECIMAL(9,2)      ,\
		 RABATT DECIMAL(9,2)      ,\
		 HANDELSPANNE DECIMAL(9,2)      ,\
		 ANZAUFTRAG SMALLINT          ,\
		 ANZZEILEN INTEGER           ,\
		 ANZPOS INTEGER           ,\
		 ANZPACK INTEGER           ,\
		 BEDINGTRABFAEHIG DECIMAL(9,2)      ,\
		 NRABFAEHIG DECIMAL(9,2)      ,\
		 RABATTIERT DECIMAL(9,2)      ,\
		 UMSSKONTOMIND DECIMAL(9,2)      ,\
		 UMSBONUSFAEHIG DECIMAL(9,2)      ,\
		 WERTBONUSEINST DECIMAL(9,2)      ,\
		 WERTZEILULIMIT DECIMAL(9,2)      ,\
		 WERTTEXT DECIMAL(9,2)      ,\
		 KUNDENNR INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 653 LOCK MODE ROW;

#define KNDMONUMS_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_KUNDEMONUMS_1    on yyy( IDFNR, JAHR, MONAT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDMONUMS_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KUNDEMONUMS_1   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDOFFEN_TAGESTYP             6
 #define L_KNDOFFEN_ZEITBEGINAM          11
 #define L_KNDOFFEN_ZEITENDEAM           11
 #define L_KNDOFFEN_ZEITBEGINPM          11
 #define L_KNDOFFEN_ZEITENDEPM           11
 #define L_KNDOFFEN_IDFNR                11
 #define L_KNDOFFEN_KUNDENNR             11
 #define L_KNDOFFEN_VERTRIEBSZENTRUMNR   6


 #define L_KNDOFFEN_PKEY 17

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDOFFEN_ANZ ( sizeof(KNDOFFEN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDOFFEN sizeof(struct KNDOFFEN)


 #define KNDOFFEN_H

 #define KNDOFFEN_LISTE \
 			KDBETRIEBSENDE.TAGESTYP, \
 			KDBETRIEBSENDE.ZEITBEGINAM, \
 			KDBETRIEBSENDE.ZEITENDEAM, \
 			KDBETRIEBSENDE.ZEITBEGINPM, \
 			KDBETRIEBSENDE.ZEITENDEPM, \
 			KDBETRIEBSENDE.IDFNR, \
			KDBETRIEBSENDE.KUNDENNR, \
			KDBETRIEBSENDE.VERTRIEBSZENTRUMNR
 #define KNDOFFEN_PLISTE \
 			"KDBETRIEBSENDE.TAGESTYP," \
 			"KDBETRIEBSENDE.ZEITBEGINAM," \
 			"KDBETRIEBSENDE.ZEITENDEAM," \
 			"KDBETRIEBSENDE.ZEITBEGINPM," \
 			"KDBETRIEBSENDE.ZEITENDEPM," \
 			"KDBETRIEBSENDE.IDFNR," \
			"KDBETRIEBSENDE.KUNDENNR," \
			"KDBETRIEBSENDE.VERTRIEBSZENTRUMNR "

 #define KNDOFFEN_PELISTE \
 			"TAGESTYP," \
 			"ZEITBEGINAM," \
 			"ZEITENDEAM," \
 			"ZEITBEGINPM," \
 			"ZEITENDEPM," \
 			"IDFNR," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR "

 #define KNDOFFEN_UPDLISTE \
 			"TAGESTYP=?," \
 			"ZEITBEGINAM=?," \
 			"ZEITENDEAM=?," \
 			"ZEITBEGINPM=?," \
 			"ZEITENDEPM=?," \
 			"IDFNR=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=? "

 #define KNDOFFENTAGESTYP                      0
 #define KNDOFFENZEITBEGINAM                   1
 #define KNDOFFENZEITENDEAM                    2
 #define KNDOFFENZEITBEGINPM                   3
 #define KNDOFFENZEITENDEPM                    4
 #define KNDOFFENIDFNR                         5
 #define KNDOFFENKUNDENNR					   6
 #define KNDOFFENVERTRIEBSZENTRUMNR			   7

 #define KNDOFFEN_ZEIGER(xxx) \
 			:xxx->TAGESTYP,\
 			:xxx->ZEITBEGINAM,\
 			:xxx->ZEITENDEAM,\
 			:xxx->ZEITBEGINPM,\
 			:xxx->ZEITENDEPM,\
 			:xxx->IDFNR,\
 			:xxx->KUNDENNR,\
 			:xxx->VERTRIEBSZENTRUMNR
 #define KNDOFFEN_UPDATE(xxx) \
 			TAGESTYP = :xxx->TAGESTYP,\
 			ZEITBEGINAM = :xxx->ZEITBEGINAM,\
 			ZEITENDEAM = :xxx->ZEITENDEAM,\
 			ZEITBEGINPM = :xxx->ZEITBEGINPM,\
 			ZEITENDEPM = :xxx->ZEITENDEPM,\
 			IDFNR = :xxx->IDFNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR

 #define LS_KNDOFFEN_TAGESTYP             7
 #define LS_KNDOFFEN_ZEITBEGINAM          11
 #define LS_KNDOFFEN_ZEITENDEAM           11
 #define LS_KNDOFFEN_ZEITBEGINPM          11
 #define LS_KNDOFFEN_ZEITENDEPM           11
 #define LS_KNDOFFEN_IDFNR                11
 #define LS_KNDOFFEN_KUNDENNR             11
 #define LS_KNDOFFEN_VERTRIEBSZENTRUMNR   7
 #define LS_KNDOFFEN_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDOFFEN {
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGINAM;
		 long    ZEITENDEAM;
		 long    ZEITBEGINPM;
		 long    ZEITENDEPM;
		 long    IDFNR;
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDOFFEN {
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGINAM;
		 long    ZEITENDEAM;
		 long    ZEITBEGINPM;
		 long    ZEITENDEPM;
		 long    IDFNR;
		 long    KUNDENNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDOFFEN {
		 short  TAGESTYP;
		 short  ZEITBEGINAM;
		 short  ZEITENDEAM;
		 short  ZEITBEGINPM;
		 short  ZEITENDEPM;
		 short  IDFNR;
		 short  KUNDENNR;
		 short  VERTRIEBSZENTRUMNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDOFFEN {
		 char    TAGESTYP[6 + 1];
		 char    ZEITBEGINAM[11];
		 char    ZEITENDEAM[11];
		 char    ZEITBEGINPM[11];
		 char    ZEITENDEPM[11];
		 char    IDFNR[11];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

 struct O_KNDOFFEN {
		 char    TAGESTYP[6];
		 char    ZEITBEGINAM[11];
		 char    ZEITENDEAM[11];
		 char    ZEITBEGINPM[11];
		 char    ZEITENDEPM[11];
		 char    IDFNR[11];
		 char    KUNDENNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDOFFEN_BES [] =
 {
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDOFFEN_BES [] =
 {
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDOFFEN
 {
  public:

  KNDOFFEN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDOFFEN_BES, KNDOFFEN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDOFFEN_BES, KNDOFFEN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDOFFEN_BES, KNDOFFEN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDOFFEN()
  {
   ::buf_default((void *)&s, KNDOFFEN_BES, KNDOFFEN_ANZ);
  }
 };
#endif

#define KNDOFFEN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 TAGESTYP CHAR(6)           ,\
		 ZEITBEGINAM INTEGER           ,\
		 ZEITENDEAM INTEGER           ,\
		 ZEITBEGINPM INTEGER           ,\
		 ZEITENDEPM INTEGER           ,\
		 IDFNR INTEGER           ,\
		 KUNDENNR INTEGER           ,\
		 VERTIEBSZENTRUMNR SMALLINT           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 519 LOCK MODE ROW;

#define KNDOFFEN_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDBETRIEBSENDEX    on yyy( IDFNR, TAGESTYP );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDOFFEN_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDBETRIEBSENDEX   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

 /******************************************************************************/
 /* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
 /******************************************************************************/


#define L_KNDSCHALTER_SKDSCHWERPUNKT1      1
#define L_KNDSCHALTER_SKDSCHWERPUNKT2      1
#define L_KNDSCHALTER_SKDSCHWERPUNKT3      1
#define L_KNDSCHALTER_SKDSCHWERPUNKT4      1
#define L_KNDSCHALTER_SKDSCHWERPUNKT5      1
#define L_KNDSCHALTER_IDFNR                11
#define L_KNDSCHALTER_SKDMUSSKOPF          1
#define L_KNDSCHALTER_SKDVERBUNDGANZ       1
#define L_KNDSCHALTER_SKDREIMPORT	        1
#define L_KNDSCHALTER_KUNDENNR             11
#define L_KNDSCHALTER_VERTRIEBSZENTRUMNR   6
#define L_KNDSCHALTER_SKDANRUFGENERELL     1
#define L_KNDSCHALTER_SKDAUFTRAGZUSAMMEN   1
#define L_KNDSCHALTER_SKDMIDAS				1
#define L_KNDSCHALTER_SKDRETAILPERMIT		1
#define L_KNDSCHALTER_SKDHALFMARGIN		1
#define L_KNDSCHALTER_SKDDISCOUNTEXCEPT	1
#define L_KNDSCHALTER_SKDGIVEPRODQUOTA		1
#define L_KNDSCHALTER_SKDMAILINVOICE		6
#define L_KNDSCHALTER_SKDMAILBATCHCHANGEADVICE		6


#define L_KNDSCHALTER_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

#define KNDSCHALTER_ANZ ( sizeof(KNDSCHALTER_BES) / sizeof(struct buf_desc) )
#endif
#define G_KNDSCHALTER sizeof(struct KNDSCHALTER)


#define KNDSCHALTER_H

#define KNDSCHALTER_LISTE \
 			KUNDESCHALTER.SKDSCHWERPUNKT1, \
 			KUNDESCHALTER.SKDSCHWERPUNKT2, \
 			KUNDESCHALTER.SKDSCHWERPUNKT3, \
 			KUNDESCHALTER.SKDSCHWERPUNKT4, \
 			KUNDESCHALTER.SKDSCHWERPUNKT5, \
 			KUNDESCHALTER.IDFNR, \
 			KUNDESCHALTER.SKDMUSSKOPF, \
 			KUNDESCHALTER.SKDVERBUNDGANZ, \
			KUNDESCHALTER.SKDREIMPORT, \
 			KUNDESCHALTER.KUNDENNR, \
 			KUNDESCHALTER.VERTRIEBSZENTRUMNR, \
			KUNDESCHALTER.SKDANRUFGENERELL, \
			KUNDESCHALTER.SKDAUFTRAGZUSAMMEN, \
			KUNDESCHALTER.SKDMIDAS, \
			KUNDESCHALTER.SKDRETAILPERMIT, \
			KUNDESCHALTER.SKDHALFMARGIN, \
			KUNDESCHALTER.SKDDISCOUNTEXCEPT, \
			KUNDESCHALTER.SKDGIVEPRODQUOTA, \
			KUNDESCHALTER.SKDMAILINVOICE, \
			KUNDESCHALTER.SKDMAILBATCHCHANGEADVICE
#define KNDSCHALTER_PLISTE \
 			"KUNDESCHALTER.SKDSCHWERPUNKT1," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT2," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT3," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT4," \
 			"KUNDESCHALTER.SKDSCHWERPUNKT5," \
 			"KUNDESCHALTER.IDFNR," \
 			"KUNDESCHALTER.SKDMUSSKOPF," \
 			"KUNDESCHALTER.SKDVERBUNDGANZ," \
			"KUNDESCHALTER.SKDREIMPORT," \
 			"KUNDESCHALTER.KUNDENNR," \
 			"KUNDESCHALTER.VERTRIEBSZENTRUMNR," \
			"KUNDESCHALTER.SKDANRUFGENERELL," \
			"KUNDESCHALTER.SKDAUFTRAGZUSAMMEN," \
			"KUNDESCHALTER.SKDMIDAS," \
			"KUNDESCHALTER.SKDRETAILPERMIT," \
			"KUNDESCHALTER.SKDHALFMARGIN," \
			"KUNDESCHALTER.SKDDISCOUNTEXCEPT," \
			"KUNDESCHALTER.SKDGIVEPRODQUOTA," \
			"KUNDESCHALTER.SKDMAILINVOICE," \
			"KUNDESCHALTER.SKDMAILBATCHCHANGEADVICE "

 #define KNDSCHALTER_PELISTE \
 			"SKDSCHWERPUNKT1," \
 			"SKDSCHWERPUNKT2," \
 			"SKDSCHWERPUNKT3," \
 			"SKDSCHWERPUNKT4," \
 			"SKDSCHWERPUNKT5," \
 			"IDFNR," \
 			"SKDMUSSKOPF," \
 			"SKDVERBUNDGANZ," \
			"SKDREIMPORT," \
 			"KUNDENNR," \
 			"VERTRIEBSZENTRUMNR," \
			"SKDANRUFGENERELL," \
			"SKDAUFTRAGZUSAMMEN," \
			"SKDMIDAS," \
			"SKDRETAILPERMIT," \
			"SKDHALFMARGIN," \
			"SKDDISCOUNTEXCEPT," \
			"SKDGIVEPRODQUOTA," \
			"SKDMAILINVOICE," \
			"SKDMAILBATCHCHANGEADVICE "

 #define KNDSCHALTER_UPDLISTE \
 			"SKDSCHWERPUNKT1=?," \
 			"SKDSCHWERPUNKT2=?," \
 			"SKDSCHWERPUNKT3=?," \
 			"SKDSCHWERPUNKT4=?," \
 			"SKDSCHWERPUNKT5=?," \
 			"IDFNR=?," \
 			"SKDMUSSKOPF=?," \
 			"SKDVERBUNDGANZ=?," \
			"SKDREIMPORT=?," \
 			"KUNDENNR=?," \
 			"VERTRIEBSZENTRUMNR=?," \
			"SKDANRUFGENERELL=?," \
			"SKDAUFTRAGZUSAMMEN=?," \
			"SKDMIDAS=?," \
			"SKDRETAILPERMIT=?," \
			"SKDHALFMARGIN=?," \
			"SKDDISCOUNTEXCEPT=?," \
			"SKDGIVEPRODQUOTA=?," \
			"SKDMAILINVOICE=?," \
			"SKDMAILBATCHCHANGEADVICE=? "

 #define KNDSCHALTERSKDSCHWERPUNKT1               0
 #define KNDSCHALTERSKDSCHWERPUNKT2               1
 #define KNDSCHALTERSKDSCHWERPUNKT3               2
 #define KNDSCHALTERSKDSCHWERPUNKT4               3
 #define KNDSCHALTERSKDSCHWERPUNKT5               4
 #define KNDSCHALTERIDFNR                         5
 #define KNDSCHALTERSKDMUSSKOPF                   6
 #define KNDSCHALTERSKDVERBUNDGANZ                7
 #define KNDSCHALTERSKDREIMPORT                   8
 #define KNDSCHALTERKUNDENNR					  9
 #define KNDSCHALTERVERTRIEBSZENTRUMNR			 10
 #define KNDSCHALTERSKDANRUFGENERELL			 11
 #define KNDSCHALTERSKDAUFTRAGZUSAMMEN			 12
 #define KNDSCHALTERSKDMIDAS					 13
 #define KNDSCHALTERSKDRETAILPERMIT				 14
 #define KNDSCHALTERSKDHALFMARGIN				 15
 #define KNDSCHALTERSKDDISCOUNTEXCEPT			 16
 #define KNDSCHALTERSKDGIVEPRODQUOTA			 17
 #define KNDSCHALTERSKDMAILINVOICE				 18
 #define KNDSCHALTERSKDMAILBATCHCHANGEADVICE	 19

 #define KNDSCHALTER_ZEIGER(xxx) \
 			:xxx->SKDSCHWERPUNKT1,\
 			:xxx->SKDSCHWERPUNKT2,\
 			:xxx->SKDSCHWERPUNKT3,\
 			:xxx->SKDSCHWERPUNKT4,\
 			:xxx->SKDSCHWERPUNKT5,\
 			:xxx->IDFNR,\
 			:xxx->SKDMUSSKOPF,\
 			:xxx->SKDVERBUNDGANZ,\
 			:xxx->SKDREIMPORT,\
 			:xxx->KUNDENNR,\
 			:xxx->VERTRIEBSZENTRUMNR,\
			:xxx->SKDANRUFGENERELL,\
			:xxx->SKDAUFTRAGZUSAMMEN,\
			:xxx->SKDMIDAS,\
			:xxx->SKDRETAILPERMIT,\
			:xxx->SKDHALFMARGIN,\
			:xxx->SKDDISCOUNTEXCEPT,\
			:xxx->SKDGIVEPRODQUOTA,\
			:xxx->SKDMAILINVOICE,\
			:xxx->SKDMAILBATCHCHANGEADVICE

 #define KNDSCHALTER_UPDATE(xxx) \
 			SKDSCHWERPUNKT1 = :xxx->SKDSCHWERPUNKT1,\
 			SKDSCHWERPUNKT2 = :xxx->SKDSCHWERPUNKT2,\
 			SKDSCHWERPUNKT3 = :xxx->SKDSCHWERPUNKT3,\
 			SKDSCHWERPUNKT4 = :xxx->SKDSCHWERPUNKT4,\
 			SKDSCHWERPUNKT5 = :xxx->SKDSCHWERPUNKT5,\
 			IDFNR = :xxx->IDFNR,\
 			SKDMUSSKOPF = :xxx->SKDMUSSKOPF,\
 			SKDVERBUNDGANZ = :xxx->SKDVERBUNDGANZ,\
 			SKDREIMPORT = :xxx->SKDREIMPORT,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
			SKDANRUFGENERELL = :xxx->SKDANRUFGENERELL,\
			SKDAUFTRAGZUSAMMEN = :xxx->SKDAUFTRAGZUSAMMEN,\
			SKDMIDAS = :xxx->SKDMIDAS,\
			SKDRETAILPERMIT = :xxx->SKDRETAILPERMIT,\
			SKDHALFMARGIN = :xxx->SKDHALFMARGIN,\
			SKDDISCOUNTEXCEPT = :xxx->SKDDISCOUNTEXCEPT,\
			SKDGIVEPRODQUOTA = :xxx->SKDGIVEPRODQUOTA,\
			SKDMAILINVOICE = :xxx->SKDMAILINVOICE,\
			SKDMAILBATCHCHANGEADVICE = :xxx->SKDMAILBATCHCHANGEADVICE

 #define LS_KNDSCHALTER_SKDSCHWERPUNKT1      2
 #define LS_KNDSCHALTER_SKDSCHWERPUNKT2      2
 #define LS_KNDSCHALTER_SKDSCHWERPUNKT3      2
 #define LS_KNDSCHALTER_SKDSCHWERPUNKT4      2
 #define LS_KNDSCHALTER_SKDSCHWERPUNKT5      2
 #define LS_KNDSCHALTER_IDFNR                11
 #define LS_KNDSCHALTER_SKDMUSSKOPF          2
 #define LS_KNDSCHALTER_SKDVERBUNDGANZ       2
 #define LS_KNDSCHALTER_SKDREIMPORT          2
 #define LS_KNDSCHALTER_KUNDENNR             11
 #define LS_KNDSCHALTER_VERTRIEBSZENTRUMNR   7
 #define LS_KNDSCHALTER_FETCH_REL            11
 #define LS_KNDSCHALTER_SKDANRUFGENERELL	 2
 #define LS_KNDSCHALTER_SKDAUFTRAGZUSAMMEN	 2
 #define LS_KNDSCHALTER_SKDMIDAS			 2
 #define LS_KNDSCHALTER_SKDRETAILPERMIT		 2
 #define LS_KNDSCHALTER_SKDHALFMARGIN		 2
 #define LS_KNDSCHALTER_SKDDISCOUNTEXCEPT	 2
 #define LS_KNDSCHALTER_SKDGIVEPRODQUOTA	 2
 #define LS_KNDSCHALTER_SKDMAILINVOICE		 7
 #define LS_KNDSCHALTER_SKDMAILBATCHCHANGEADVICE   7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDSCHALTER {
		 char    SKDSCHWERPUNKT1[1 + 1];
		 char    SKDSCHWERPUNKT2[1 + 1];
		 char    SKDSCHWERPUNKT3[1 + 1];
		 char    SKDSCHWERPUNKT4[1 + 1];
		 char    SKDSCHWERPUNKT5[1 + 1];
		 long    IDFNR;
		 char    SKDMUSSKOPF[1 + 1];
		 char    SKDVERBUNDGANZ[1 + 1];
		 char    SKDREIMPORT[1 + 1];
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 char	 SKDANRUFGENERELL[1+1];
		 char	 SKDAUFTRAGZUSAMMEN[1+1];
		 char	 SKDMIDAS[1+1];
		 char	 SKDRETAILPERMIT[1+1];
		 char	 SKDHALFMARGIN[1+1];
		 char	 SKDDISCOUNTEXCEPT[1+1];
		 char	 SKDGIVEPRODQUOTA[1+1];
		 short	 SKDMAILINVOICE;
		 short	 SKDMAILBATCHCHANGEADVICE;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDSCHALTER {
		 char    SKDSCHWERPUNKT1;
		 char    SKDSCHWERPUNKT2;
		 char    SKDSCHWERPUNKT3;
		 char    SKDSCHWERPUNKT4;
		 char    SKDSCHWERPUNKT5;
		 long    IDFNR;
		 char    SKDMUSSKOPF;
		 char    SKDVERBUNDGANZ;
		 char    SKDREIMPORT;
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 char	 SKDANRUFGENERELL;
		 char	 SKDAUFTRAGZUSAMMEN;
		 char	 SKDMIDAS;
		 char	 SKDRETAILPERMIT;
		 char	 SKDHALFMARGIN;
		 char	 SKDDISCOUNTEXCEPT;
		 char	 SKDGIVEPRODQUOTA;
		 short	 SKDMAILINVOICE;
		 short	 SKDMAILBATCHCHANGEADVICE;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDSCHALTER {
		 short  SKDSCHWERPUNKT1;
		 short  SKDSCHWERPUNKT2;
		 short  SKDSCHWERPUNKT3;
		 short  SKDSCHWERPUNKT4;
		 short  SKDSCHWERPUNKT5;
		 short  IDFNR;
		 short  SKDMUSSKOPF;
		 short  SKDVERBUNDGANZ;
		 short  SKDREIMPORT;
		 short	KUNDENNR;
		 short	VERTRIEBSZENTRUMNR;
		 short	SKDANRUFGENERELL;
		 short	SKDAUFTRAGZUSAMMEN;
		 short	SKDMIDAS;
		 short  SKDRETAILPERMIT;
		 short  SKDHALFMARGIN;
		 short  SKDDISCOUNTEXCEPT;
		 short  SKDGIVEPRODQUOTA;
		 short	SKDMAILINVOICE;
		 short	SKDMAILBATCHCHANGEADVICE;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDSCHALTER {
		 char    SKDSCHWERPUNKT1[1 + 1];
		 char    SKDSCHWERPUNKT2[1 + 1];
		 char    SKDSCHWERPUNKT3[1 + 1];
		 char    SKDSCHWERPUNKT4[1 + 1];
		 char    SKDSCHWERPUNKT5[1 + 1];
		 char    IDFNR[11];
		 char    SKDMUSSKOPF[1 + 1];
		 char    SKDVERBUNDGANZ[1 + 1];
		 char    SKDREIMPORT[1 + 1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 SKDANRUFGENERELL[1 + 1];
		 char	 SKDAUFTRAGZUSAMMEN[1+1];
		 char	 SKDMIDAS[1+1];
		 char	 SKDRETAILPERMIT[1+1];
		 char	 SKDHALFMARGIN[1+1];
		 char	 SKDDISCOUNTEXCEPT[1+1];
		 char	 SKDGIVEPRODQUOTA[1+1];
		 char	 SKDMAILINVOICE[7];
		 char	 SKDMAILBATCHCHANGEADVICE[7];
		 char    FETCH_REL[11];
       };

 struct O_KNDSCHALTER {
		 char    SKDSCHWERPUNKT1[1];
		 char    SKDSCHWERPUNKT2[1];
		 char    SKDSCHWERPUNKT3[1];
		 char    SKDSCHWERPUNKT4[1];
		 char    SKDSCHWERPUNKT5[1];
		 char    IDFNR[11];
		 char    SKDMUSSKOPF[1];
		 char    SKDVERBUNDGANZ[1];
		 char    SKDREIMPORT[1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 SKDANRUFGENERELL[1];
		 char	 SKDAUFTRAGZUSAMMEN[1+1];
		 char	 SKDMIDAS[1+1];
		 char	 SKDRETAILPERMIT[1+1];
		 char	 SKDHALFMARGIN[1+1];
		 char	 SKDDISCOUNTEXCEPT[1+1];
		 char	 SKDGIVEPRODQUOTA[1+1];
		 char	 SKDMAILINVOICE[7];
		 char	 SKDMAILBATCHCHANGEADVICE[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDSCHALTER_BES [] =
 {
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDSCHALTER_BES [] =
 {
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDSCHALTER
 {
  public:

  KNDSCHALTER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDSCHALTER_BES, KNDSCHALTER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDSCHALTER_BES, KNDSCHALTER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDSCHALTER_BES, KNDSCHALTER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDSCHALTER()
  {
   ::buf_default((void *)&s, KNDSCHALTER_BES, KNDSCHALTER_ANZ);
  }
 };
#endif

#define KNDSCHALTER_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 SKDSCHWERPUNKT1 CHAR(1)           ,\
		 SKDSCHWERPUNKT2 CHAR(1)           ,\
		 SKDSCHWERPUNKT3 CHAR(1)           ,\
		 SKDSCHWERPUNKT4 CHAR(1)           ,\
		 SKDSCHWERPUNKT5 CHAR(1)           ,\
		 IDFNR INTEGER           ,\
		 SKDMUSSKOPF CHAR(1)           ,\
		 SKDVERBUNDGANZ CHAR(1)           ,\
		 SKDREIMPORT CHAR(1)           ,\
		 KUNDENNR INTEGER           ,\
		 VERTRIEBSZENTRUMNR SMALLINT           ,\
		 SKDANRUFGENERELL CHAR(1)           ,\
		 SKDAUFTRAGZUSAMMEN CHAR(1)           ,\
		 SKDMIDAS CHAR(1)           ,\
		 SKDRETAILPERMIT CHAR(1)           ,\
		 SKDHALFMARGIN CHAR(1)           ,\
		 SKDDISCOUNTEXCEPT CHAR(1)           ,\
		 SKDGIVEPRODQUOTA CHAR(1)           ,\
		 SKDMAILINVOICE SMALLINT           ,\
		 SKDMAILBATCHCHANGEADVICE SMALLINT           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 149 LOCK MODE ROW;

#define KNDSCHALTER_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_KUNDESCHALTER_1  on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDSCHALTER_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KUNDESCHALTER_1 ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDSEL_IDFNR                11
 #define L_KNDSEL_MATCHCODE            12
 #define L_KNDSEL_FILIALNR             6
 #define L_KNDSEL_NAMEAPO              40
 #define L_KNDSEL_NAMEINHABER          30
 #define L_KNDSEL_STRASSE              40
 #define L_KNDSEL_ORT                  30
 #define L_KNDSEL_KZKDKLASSE           3
 #define L_KNDSEL_TELKURZWAHL          4
 #define L_KNDSEL_VERTRIEBSZENTRUMNR   6
 #define L_KNDSEL_KUNDENNR             11
 #define L_KNDSEL_SKDKUNDEAEGESPERRT   1
 #define L_KNDSEL_REGIONNR			   6
 #define L_KNDSEL_ORIGINALFILIALNR	   6


 #define L_KNDSEL_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDSEL_ANZ ( sizeof(KNDSEL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDSEL sizeof(struct KNDSEL)


 #define KNDSEL_H

 #define KNDSEL_LISTE \
 			KUNDE.IDFNR, \
 			KUNDE.MATCHCODE, \
 			KUNDE.FILIALNR, \
 			KUNDE.NAMEAPO, \
 			KUNDE.NAMEINHABER, \
 			KUNDE.STRASSE, \
 			KUNDE.ORT, \
 			KUNDE.KZKDKLASSE, \
 			KUNDE.TELKURZWAHL, \
			KUNDE.VERTRIEBSZENTRUMNR, \
			KUNDE.KUNDENNR, \
			KUNDESCHALTER.SKDKUNDEAEGESPERRT, \
			KUNDE.ORIGINALFILIALNR
 #define KNDSEL_PLISTE \
 			"KUNDE.IDFNR," \
 			"KUNDE.MATCHCODE," \
 			"KUNDE.FILIALNR," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.NAMEINHABER," \
 			"KUNDE.STRASSE," \
 			"KUNDE.ORT," \
 			"KUNDE.KZKDKLASSE," \
 			"KUNDE.TELKURZWAHL," \
			"KUNDE.VERTRIEBSZENTRUMNR," \
			"KUNDE.KUNDENNR," \
			"KUNDESCHALTER.SKDKUNDEAEGESPERRT," \
			"KUNDE.ORIGINALFILIALNR "

 #define KNDSEL_PELISTE \
 			"IDFNR," \
 			"MATCHCODE," \
 			"FILIALNR," \
 			"NAMEAPO," \
 			"NAMEINHABER," \
 			"STRASSE," \
 			"ORT," \
 			"KZKDKLASSE," \
 			"TELKURZWAHL," \
			"VERTRIEBSZENTRUMNR," \
			"KUNDENNR," \
			"SKDKUNDEAEGESPERRT," \
			"ORIGINALFILIALNR "

 #define KNDSEL_UPDLISTE \
 			"IDFNR=?," \
 			"MATCHCODE=?," \
 			"FILIALNR=?," \
 			"NAMEAPO=?," \
 			"NAMEINHABER=?," \
 			"STRASSE=?," \
 			"ORT=?," \
 			"KZKDKLASSE=?," \
 			"TELKURZWAHL=?," \
			"VERTRIEBSZENTRUMNR=?," \
			"KUNDENNR=?," \
			"SKDKUNDEAEGESPERRT=?," \
			"ORIGINALFILIALNR=? "

 #define KNDSELIDFNR                         0
 #define KNDSELMATCHCODE                     1
 #define KNDSELFILIALNR                      2
 #define KNDSELNAMEAPO                       3
 #define KNDSELNAMEINHABER                   4
 #define KNDSELSTRASSE                       5
 #define KNDSELORT                           6
 #define KNDSELKZKDKLASSE                    7
 #define KNDSELTELKURZWAHL                   8
 #define KNDSELVERTRIEBSZENTRUMNR			 9
 #define KNDSELKUNDENNR						10
 #define KNDSELSKDKUNDEAEGESPERRT			11
 #define KNDSELSKDREGIONNR					12
 #define KNDSELORIGINALFILIALNR				13

 #define KNDSEL_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->MATCHCODE,\
 			:xxx->FILIALNR,\
 			:xxx->NAMEAPO,\
 			:xxx->NAMEINHABER,\
 			:xxx->STRASSE,\
 			:xxx->ORT,\
 			:xxx->KZKDKLASSE,\
 			:xxx->TELKURZWAHL,\
			:xxx->VERTRIEBSZENTRUMNR,\
			:xxx->KUNDENNR,\
			:xxx->SKDKUNDEAEGESPERRT,\
			:xxx->ORIGINALFILIALNR

 #define KNDSEL_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			MATCHCODE = :xxx->MATCHCODE,\
 			FILIALNR = :xxx->FILIALNR,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			NAMEINHABER = :xxx->NAMEINHABER,\
 			STRASSE = :xxx->STRASSE,\
 			ORT = :xxx->ORT,\
 			KZKDKLASSE = :xxx->KZKDKLASSE,\
 			TELKURZWAHL = :xxx->TELKURZWAHL,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
			KUNDENNR = :xxx->KUNDENNR,\
			SKDKUNDEAEGESPERRT = :xxx->SKDKUNDEAEGESPERRT,\
			ORIGINALFILIALNR = :xxx->ORIGINALFILIALNR

 #define LS_KNDSEL_IDFNR                11
 #define LS_KNDSEL_MATCHCODE            13
 #define LS_KNDSEL_FILIALNR             7
 #define LS_KNDSEL_NAMEAPO              41
 #define LS_KNDSEL_NAMEINHABER          31
 #define LS_KNDSEL_STRASSE              41
 #define LS_KNDSEL_ORT                  31
 #define LS_KNDSEL_KZKDKLASSE           4
 #define LS_KNDSEL_TELKURZWAHL          5
 #define LS_KNDSEL_VERTRIEBSZENTRUMNR   7
 #define LS_KNDSEL_KUNDENNR             11
 #define LS_KNDSEL_SKDKUNDEAEGESPERRT   2
 #define LS_KNDSEL_REGIONNR             7
 #define LS_KNDSEL_ORIGINALFILIALNR     7
 #define LS_KNDSEL_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDSEL {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    KZKDKLASSE[3 + 1];
		 char    TELKURZWAHL[4 + 1];
		 short	 VERTRIEBSZENTRUMNR;
		 long	 KUNDENNR;
		 char    SKDKUNDEAEGESPERRT[1 + 1];
		 short	 REGIONNR;
		 short	 ORIGINALFILIALNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KNDSEL {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    KZKDKLASSE[3 + 1];
		 char    TELKURZWAHL[4 + 1];
		 short	 VERTRIEBSZENTRUMNR;
		 long	 KUNDENNR;
		 char    SKDKUNDEAEGESPERRT[1 + 1];
		 short	 REGIONNR;
		 short	 ORIGINALFILIALNR;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KNDSEL {
		 short  IDFNR;
		 short  MATCHCODE;
		 short  FILIALNR;
		 short  NAMEAPO;
		 short  NAMEINHABER;
		 short  STRASSE;
		 short  ORT;
		 short  KZKDKLASSE;
		 short  TELKURZWAHL;
		 short	VERTRIEBSZENTRUMNR;
		 short	KUNDENNR;
		 short  SKDKUNDEAEGESPERRT;
		 short	REGIONNR;
		 short	ORIGINALFILIALNR;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KNDSEL {
		 char    IDFNR[11];
		 char    MATCHCODE[12 + 1];
		 char    FILIALNR[7];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    KZKDKLASSE[3 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char	 KUNDENNR[11];
		 char    SKDKUNDEAEGESPERRT[1 + 1];
		 char    REGIONNR[6 + 1];
		 char    ORIGINALFILIALNR[6 + 1];
		 char    FETCH_REL[11];
       };

 struct O_KNDSEL {
		 char    IDFNR[11];
		 char    MATCHCODE[12];
		 char    FILIALNR[7];
		 char    NAMEAPO[40];
		 char    NAMEINHABER[30];
		 char    STRASSE[40];
		 char    ORT[30];
		 char    KZKDKLASSE[3];
		 char    TELKURZWAHL[4];
		 char	 VERTRIEBSZENTRUMNR[6];
		 char	 KUNDENNR[11];
		 char    SKDKUNDEAEGESPERRT[1];
		 char    REGIONNR[6];
		 char    ORIGINALFILIALNR[6];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDSEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDSEL_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKNDSEL
 {
  public:

  KNDSEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KNDSEL_BES, KNDSEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KNDSEL_BES, KNDSEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KNDSEL_BES, KNDSEL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKNDSEL()
  {
   ::buf_default((void *)&s, KNDSEL_BES, KNDSEL_ANZ);
  }
 };
#endif

#define KNDSEL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 MATCHCODE CHAR(12)          ,\
		 FILIALNR SMALLINT          ,\
		 NAMEAPO CHAR(40)          ,\
		 NAMEINHABER CHAR(30)          ,\
		 STRASSE CHAR(40)          ,\
		 ORT CHAR(30)          ,\
		 KZKDKLASSE CHAR(3)           ,\
		 TELKURZWAHL CHAR(4)           ,\
		 VERTRIEBSZENTRUMNR SMALLINT		,\
		 KUNDENNR INTEGER			,\
		 SKDKUNDEAEGESPERRT CHAR(2)           ,\
		 REGIONNR SMALLINT          ,\
		 ORIGINALFILIALNR SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 1105 LOCK MODE ROW;

#define KNDSEL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEX             on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDMATCHCODEX       on yyy( MATCHCODE );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDSEL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEX            ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDMATCHCODEX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

#define L_KNDTOUREN_IDFNR 11
#define L_KNDTOUREN_TOURID 6
#define L_KNDTOUREN_REIHENFOLGENR 11
#define L_KNDTOUREN_DATUMVERSAND 11
#define L_KNDTOUREN_ZEITVERSAND 11
#define L_KNDTOUREN_FAHRTZEIT 11
#define L_KNDTOUREN_BAHNHOFVERSAND 6
#define L_KNDTOUREN_ISTVERBUNDTOUR 1
#define L_KNDTOUREN_VERTRIEBSZENTRUMNR 6
#define L_KNDTOUREN_KUNDENNR 11
#define L_KNDTOUREN_PHARMACYLOCKACCESS 6
#define L_KNDTOUREN_REMARKLACKITEMPROCESSING 40
#define L_KNDTOUREN_REMARKLACKCALLBACK 40
#define L_KNDTOUREN_KOART 1
#define L_KNDTOUREN_LAGRECHTOUR 11
#define L_KNDTOUREN_KIPPZEIT 6
#define L_KNDTOUREN_KZAUTOZUORD 1
#define L_KNDTOUREN_KDAUFTRAGART 2
#define L_KNDTOUREN_ISBTM 6
#define L_KNDTOUREN_ISKK 6
#define L_KNDTOUREN_ISK08 6
#define L_KNDTOUREN_ISK20 6
#define L_KNDTOUREN_RETURNSTOUR 6
#define L_KNDTOUREN_TRANSPEXCLPSYCHO 6
#define L_KNDTOUREN_TRANSPEXCLCOOLED 6
#define L_KNDTOUREN_TRANSPEXCLEXPENSIVE 6
#define L_KNDTOUREN_PRIO1_KIPPZ_KTOUR 6
#define L_KNDTOUREN_PRIO2_KIPPZ_FTOUR 6
#define L_KNDTOUREN_PRIO3_KIPPZ_KUNDE 11
#define L_KNDTOUREN_PRIO4_KIPPZ_FILIALE 11
#define L_KNDTOUREN_WEEKDAY 6

/* Length/Count-Define of KNDTOUREN *******************************************/

#define LS_KNDTOUREN_IDFNR 10 + 1
#define LS_KNDTOUREN_TOURID 6 + 1
#define LS_KNDTOUREN_REIHENFOLGENR 10 + 1
#define LS_KNDTOUREN_DATUMVERSAND 10 + 1
#define LS_KNDTOUREN_ZEITVERSAND 10 + 1
#define LS_KNDTOUREN_FAHRTZEIT 10 + 1
#define LS_KNDTOUREN_BAHNHOFVERSAND 5 + 1
#define LS_KNDTOUREN_ISTVERBUNDTOUR 1 + 1
#define LS_KNDTOUREN_VERTRIEBSZENTRUMNR 5 + 1
#define LS_KNDTOUREN_KUNDENNR 10 + 1
#define LS_KNDTOUREN_PHARMACYLOCKACCESS 5 + 1
#define LS_KNDTOUREN_REMARKLACKITEMPROCESSING 40 + 1
#define LS_KNDTOUREN_REMARKLACKCALLBACK 40 + 1
#define LS_KNDTOUREN_KOART 1 + 1
#define LS_KNDTOUREN_LAGRECHTOUR 10 + 1
#define LS_KNDTOUREN_KIPPZEIT 5 + 1
#define LS_KNDTOUREN_KZAUTOZUORD 1 + 1
#define LS_KNDTOUREN_KDAUFTRAGART 2 + 1
#define LS_KNDTOUREN_ISBTM 5 + 1
#define LS_KNDTOUREN_ISKK 5 + 1
#define LS_KNDTOUREN_ISK08 5 + 1
#define LS_KNDTOUREN_ISK20 5 + 1
#define LS_KNDTOUREN_RETURNSTOUR 5 + 1
#define LS_KNDTOUREN_TRANSPEXCLPSYCHO 5 + 1
#define LS_KNDTOUREN_TRANSPEXCLCOOLED 5 + 1
#define LS_KNDTOUREN_TRANSPEXCLEXPENSIVE 5 + 1
#define LS_KNDTOUREN_PRIO1_KIPPZ_KTOUR 5 + 1
#define LS_KNDTOUREN_PRIO2_KIPPZ_FTOUR 5 + 1
#define LS_KNDTOUREN_PRIO3_KIPPZ_KUNDE 10 + 1
#define LS_KNDTOUREN_PRIO4_KIPPZ_FILIALE 10 + 1
#define LS_KNDTOUREN_WEEKDAY 5 + 1

#define KNDTOURENIDFNR 0
#define KNDTOURENTOURID 1
#define KNDTOURENREIHENFOLGENR 2
#define KNDTOURENDATUMVERSAND 3
#define KNDTOURENZEITVERSAND 4
#define KNDTOURENFAHRTZEIT 5
#define KNDTOURENBAHNHOFVERSAND 6
#define KNDTOURENISTVERBUNDTOUR 7
#define KNDTOURENVERTRIEBSZENTRUMNR 8
#define KNDTOURENKUNDENNR 9
#define KNDTOURENPHARMACYLOCKACCESS 10
#define KNDTOURENREMARKLACKITEMPROCESSING 11
#define KNDTOURENREMARKLACKCALLBACK 12
#define KNDTOURENKOART 13
#define KNDTOURENLAGRECHTOUR 14
#define KNDTOURENKIPPZEIT 15
#define KNDTOURENKZAUTOZUORD 16
#define KNDTOURENKDAUFTRAGART 17
#define KNDTOURENISBTM 18
#define KNDTOURENISKK 19
#define KNDTOURENISK08 20
#define KNDTOURENISK20 21
#define KNDTOURENRETURNSTOUR 22
#define KNDTOURENTRANSPEXCLPSYCHO 23
#define KNDTOURENTRANSPEXCLCOOLED 24
#define KNDTOURENTRANSPEXCLEXPENSIVE 25
#define KNDTOURENPRIO1_KIPPZ_KTOUR 26
#define KNDTOURENPRIO2_KIPPZ_FTOUR 27
#define KNDTOURENPRIO3_KIPPZ_KUNDE 28
#define KNDTOURENPRIO4_KIPPZ_FILIALE 29
#define KNDTOURENWEEKDAY 30

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KNDTOUREN_H
#define KNDTOUREN_ANZ ( sizeof(KNDTOUREN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KNDTOUREN *****************************************************/

#define KNDTOUREN_LISTE \
        TOURPLANTAG.IDFNR,\
        TOURPLANTAG.TOURID,\
        TOURPLANTAG.REIHENFOLGENR,\
        TOUR.DATUMVERSAND,\
        TOUR.ZEITVERSAND,\
        TOURPLANTAG.FAHRTZEIT,\
        TOUR.BAHNHOFVERSAND,\
        TOURPLANTAG.ISTVERBUNDTOUR,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR,\
        CUSTOMERTOURDETAILS.PHARMACYLOCKACCESS,\
        CUSTOMERTOURDETAILS.REMARKLACKITEMPROCESSING,\
        CUSTOMERTOURDETAILS.REMARKLACKCALLBACK,\
        TOURPLANTAG.KOART,\
        TOUR.LAGRECHTOUR,\
        TOURPLANTAG.KIPPZEIT,\
        TOURPLANTAG.KZAUTOZUORD,\
        TOURPLANTAG.KDAUFTRAGART,\
        TOURPLANTAG.ISBTM,\
        TOURPLANTAG.ISKK,\
        TOURPLANTAG.ISK08,\
        TOURPLANTAG.ISK20,\
        TOURPLANTAG.RETURNSTOUR,\
        TOURPLANTAG.TRANSPEXCLPSYCHO,\
        TOURPLANTAG.TRANSPEXCLCOOLED,\
        TOURPLANTAG.TRANSPEXCLEXPENSIVE,\
        AADUMMY.PRIO1_KIPPZ_KTOUR,\
        AADUMMY.PRIO2_KIPPZ_FTOUR,\
        AADUMMY.PRIO3_KIPPZ_KUNDE,\
        AADUMMY.PRIO4_KIPPZ_FILIALE,\
        AADUMMY.WEEKDAY
#define KNDTOUREN_LISTE_390 \
        IDFNR,\
        TOURID,\
        REIHENFOLGENR,\
        DATUMVERSAND,\
        ZEITVERSAND,\
        FAHRTZEIT,\
        BAHNHOFVERSAND,\
        ISTVERBUNDTOUR,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        PHARMACYLOCKACCESS,\
        REMARKLACKITEMPROCESSING,\
        REMARKLACKCALLBACK,\
        KOART,\
        LAGRECHTOUR,\
        KIPPZEIT,\
        KZAUTOZUORD,\
        KDAUFTRAGART,\
        ISBTM,\
        ISKK,\
        ISK08,\
        ISK20,\
        RETURNSTOUR,\
        TRANSPEXCLPSYCHO,\
        TRANSPEXCLCOOLED,\
        TRANSPEXCLEXPENSIVE,\
        PRIO1_KIPPZ_KTOUR,\
        PRIO2_KIPPZ_FTOUR,\
        PRIO3_KIPPZ_KUNDE,\
        PRIO4_KIPPZ_FILIALE,\
        WEEKDAY
#define KNDTOUREN_PLISTE \
        "TOURPLANTAG.IDFNR,"\
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.REIHENFOLGENR,"\
        "TOUR.DATUMVERSAND,"\
        "TOUR.ZEITVERSAND,"\
        "TOURPLANTAG.FAHRTZEIT,"\
        "TOUR.BAHNHOFVERSAND,"\
        "TOURPLANTAG.ISTVERBUNDTOUR,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "CUSTOMERTOURDETAILS.PHARMACYLOCKACCESS,"\
        "CUSTOMERTOURDETAILS.REMARKLACKITEMPROCESSING,"\
        "CUSTOMERTOURDETAILS.REMARKLACKCALLBACK,"\
        "TOURPLANTAG.KOART,"\
        "TOUR.LAGRECHTOUR,"\
        "TOURPLANTAG.KIPPZEIT,"\
        "TOURPLANTAG.KZAUTOZUORD,"\
        "TOURPLANTAG.KDAUFTRAGART,"\
        "TOURPLANTAG.ISBTM,"\
        "TOURPLANTAG.ISKK,"\
        "TOURPLANTAG.ISK08,"\
        "TOURPLANTAG.ISK20,"\
        "TOURPLANTAG.RETURNSTOUR,"\
        "TOURPLANTAG.TRANSPEXCLPSYCHO,"\
        "TOURPLANTAG.TRANSPEXCLCOOLED,"\
        "TOURPLANTAG.TRANSPEXCLEXPENSIVE,"\
        "AADUMMY.PRIO1_KIPPZ_KTOUR,"\
        "AADUMMY.PRIO2_KIPPZ_FTOUR,"\
        "AADUMMY.PRIO3_KIPPZ_KUNDE,"\
        "AADUMMY.PRIO4_KIPPZ_FILIALE,"\
        "AADUMMY.WEEKDAY"
#define KNDTOUREN_PELISTE \
        "IDFNR,"\
        "TOURID,"\
        "REIHENFOLGENR,"\
        "DATUMVERSAND,"\
        "ZEITVERSAND,"\
        "FAHRTZEIT,"\
        "BAHNHOFVERSAND,"\
        "ISTVERBUNDTOUR,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "PHARMACYLOCKACCESS,"\
        "REMARKLACKITEMPROCESSING,"\
        "REMARKLACKCALLBACK,"\
        "KOART,"\
        "LAGRECHTOUR,"\
        "KIPPZEIT,"\
        "KZAUTOZUORD,"\
        "KDAUFTRAGART,"\
        "ISBTM,"\
        "ISKK,"\
        "ISK08,"\
        "ISK20,"\
        "RETURNSTOUR,"\
        "TRANSPEXCLPSYCHO,"\
        "TRANSPEXCLCOOLED,"\
        "TRANSPEXCLEXPENSIVE,"\
        "PRIO1_KIPPZ_KTOUR,"\
        "PRIO2_KIPPZ_FTOUR,"\
        "PRIO3_KIPPZ_KUNDE,"\
        "PRIO4_KIPPZ_FILIALE,"\
        "WEEKDAY"
#define KNDTOUREN_UPDLISTE \
        "IDFNR=?,"\
        "TOURID=?,"\
        "REIHENFOLGENR=?,"\
        "DATUMVERSAND=?,"\
        "ZEITVERSAND=?,"\
        "FAHRTZEIT=?,"\
        "BAHNHOFVERSAND=?,"\
        "ISTVERBUNDTOUR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "PHARMACYLOCKACCESS=?,"\
        "REMARKLACKITEMPROCESSING=?,"\
        "REMARKLACKCALLBACK=?,"\
        "KOART=?,"\
        "LAGRECHTOUR=?,"\
        "KIPPZEIT=?,"\
        "KZAUTOZUORD=?,"\
        "KDAUFTRAGART=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?,"\
        "RETURNSTOUR=?,"\
        "TRANSPEXCLPSYCHO=?,"\
        "TRANSPEXCLCOOLED=?,"\
        "TRANSPEXCLEXPENSIVE=?,"\
        "PRIO1_KIPPZ_KTOUR=?,"\
        "PRIO2_KIPPZ_FTOUR=?,"\
        "PRIO3_KIPPZ_KUNDE=?,"\
        "PRIO4_KIPPZ_FILIALE=?,"\
        "WEEKDAY=?"
/* SqlMacros-Define of KNDTOUREN **********************************************/

#define KNDTOUREN_ZEIGER(x) \
        :x->IDFNR,\
        :x->TOURID,\
        :x->REIHENFOLGENR,\
        :x->DATUMVERSAND,\
        :x->ZEITVERSAND,\
        :x->FAHRTZEIT,\
        :x->BAHNHOFVERSAND,\
        :x->ISTVERBUNDTOUR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->PHARMACYLOCKACCESS,\
        :x->REMARKLACKITEMPROCESSING,\
        :x->REMARKLACKCALLBACK,\
        :x->KOART,\
        :x->LAGRECHTOUR,\
        :x->KIPPZEIT,\
        :x->KZAUTOZUORD,\
        :x->KDAUFTRAGART,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->PRIO1_KIPPZ_KTOUR,\
        :x->PRIO2_KIPPZ_FTOUR,\
        :x->PRIO3_KIPPZ_KUNDE,\
        :x->PRIO4_KIPPZ_FILIALE,\
        :x->WEEKDAY
#define KNDTOUREN_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->TOURID,\
        :x->REIHENFOLGENR,\
        :x->DATUMVERSAND,\
        :x->ZEITVERSAND,\
        :x->FAHRTZEIT,\
        :x->BAHNHOFVERSAND,\
        :x->ISTVERBUNDTOUR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->PHARMACYLOCKACCESS,\
        :x->REMARKLACKITEMPROCESSING,\
        :x->REMARKLACKCALLBACK,\
        :x->KOART,\
        :x->LAGRECHTOUR,\
        :x->KIPPZEIT,\
        :x->KZAUTOZUORD,\
        :x->KDAUFTRAGART,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->PRIO1_KIPPZ_KTOUR,\
        :x->PRIO2_KIPPZ_FTOUR,\
        :x->PRIO3_KIPPZ_KUNDE,\
        :x->PRIO4_KIPPZ_FILIALE,\
        :x->WEEKDAY
#define KNDTOUREN_UPDATE(x) \
        TOURPLANTAG.IDFNR=:x->IDFNR,\
        TOURPLANTAG.TOURID=:x->TOURID,\
        TOURPLANTAG.REIHENFOLGENR=:x->REIHENFOLGENR,\
        TOUR.DATUMVERSAND=:x->DATUMVERSAND,\
        TOUR.ZEITVERSAND=:x->ZEITVERSAND,\
        TOURPLANTAG.FAHRTZEIT=:x->FAHRTZEIT,\
        TOUR.BAHNHOFVERSAND=:x->BAHNHOFVERSAND,\
        TOURPLANTAG.ISTVERBUNDTOUR=:x->ISTVERBUNDTOUR,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR=:x->KUNDENNR,\
        CUSTOMERTOURDETAILS.PHARMACYLOCKACCESS=:x->PHARMACYLOCKACCESS,\
        CUSTOMERTOURDETAILS.REMARKLACKITEMPROCESSING=:x->REMARKLACKITEMPROCESSING,\
        CUSTOMERTOURDETAILS.REMARKLACKCALLBACK=:x->REMARKLACKCALLBACK,\
        TOURPLANTAG.KOART=:x->KOART,\
        TOUR.LAGRECHTOUR=:x->LAGRECHTOUR,\
        TOURPLANTAG.KIPPZEIT=:x->KIPPZEIT,\
        TOURPLANTAG.KZAUTOZUORD=:x->KZAUTOZUORD,\
        TOURPLANTAG.KDAUFTRAGART=:x->KDAUFTRAGART,\
        TOURPLANTAG.ISBTM=:x->ISBTM,\
        TOURPLANTAG.ISKK=:x->ISKK,\
        TOURPLANTAG.ISK08=:x->ISK08,\
        TOURPLANTAG.ISK20=:x->ISK20,\
        TOURPLANTAG.RETURNSTOUR=:x->RETURNSTOUR,\
        TOURPLANTAG.TRANSPEXCLPSYCHO=:x->TRANSPEXCLPSYCHO,\
        TOURPLANTAG.TRANSPEXCLCOOLED=:x->TRANSPEXCLCOOLED,\
        TOURPLANTAG.TRANSPEXCLEXPENSIVE=:x->TRANSPEXCLEXPENSIVE,\
        AADUMMY.PRIO1_KIPPZ_KTOUR=:x->PRIO1_KIPPZ_KTOUR,\
        AADUMMY.PRIO2_KIPPZ_FTOUR=:x->PRIO2_KIPPZ_FTOUR,\
        AADUMMY.PRIO3_KIPPZ_KUNDE=:x->PRIO3_KIPPZ_KUNDE,\
        AADUMMY.PRIO4_KIPPZ_FILIALE=:x->PRIO4_KIPPZ_FILIALE,\
        AADUMMY.WEEKDAY=:x->WEEKDAY
/* SqlMacros390-Define of KNDTOUREN *******************************************/

#define KNDTOUREN_ZEIGER_390 \
        :IDFNR,\
        :TOURID,\
        :REIHENFOLGENR,\
        :DATUMVERSAND,\
        :ZEITVERSAND,\
        :FAHRTZEIT,\
        :BAHNHOFVERSAND,\
        :ISTVERBUNDTOUR,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :PHARMACYLOCKACCESS,\
        :REMARKLACKITEMPROCESSING,\
        :REMARKLACKCALLBACK,\
        :KOART,\
        :LAGRECHTOUR,\
        :KIPPZEIT,\
        :KZAUTOZUORD,\
        :KDAUFTRAGART,\
        :ISBTM,\
        :ISKK,\
        :ISK08,\
        :ISK20,\
        :RETURNSTOUR,\
        :TRANSPEXCLPSYCHO,\
        :TRANSPEXCLCOOLED,\
        :TRANSPEXCLEXPENSIVE,\
        :PRIO1_KIPPZ_KTOUR,\
        :PRIO2_KIPPZ_FTOUR,\
        :PRIO3_KIPPZ_KUNDE,\
        :PRIO4_KIPPZ_FILIALE,\
        :WEEKDAY
#define KNDTOUREN_UPDATE_390 \
        IDFNR=:IDFNR,\
        TOURID=:TOURID,\
        REIHENFOLGENR=:REIHENFOLGENR,\
        DATUMVERSAND=:DATUMVERSAND,\
        ZEITVERSAND=:ZEITVERSAND,\
        FAHRTZEIT=:FAHRTZEIT,\
        BAHNHOFVERSAND=:BAHNHOFVERSAND,\
        ISTVERBUNDTOUR=:ISTVERBUNDTOUR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        PHARMACYLOCKACCESS=:PHARMACYLOCKACCESS,\
        REMARKLACKITEMPROCESSING=:REMARKLACKITEMPROCESSING,\
        REMARKLACKCALLBACK=:REMARKLACKCALLBACK,\
        KOART=:KOART,\
        LAGRECHTOUR=:LAGRECHTOUR,\
        KIPPZEIT=:KIPPZEIT,\
        KZAUTOZUORD=:KZAUTOZUORD,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        ISBTM=:ISBTM,\
        ISKK=:ISKK,\
        ISK08=:ISK08,\
        ISK20=:ISK20,\
        RETURNSTOUR=:RETURNSTOUR,\
        TRANSPEXCLPSYCHO=:TRANSPEXCLPSYCHO,\
        TRANSPEXCLCOOLED=:TRANSPEXCLCOOLED,\
        TRANSPEXCLEXPENSIVE=:TRANSPEXCLEXPENSIVE,\
        PRIO1_KIPPZ_KTOUR=:PRIO1_KIPPZ_KTOUR,\
        PRIO2_KIPPZ_FTOUR=:PRIO2_KIPPZ_FTOUR,\
        PRIO3_KIPPZ_KUNDE=:PRIO3_KIPPZ_KUNDE,\
        PRIO4_KIPPZ_FILIALE=:PRIO4_KIPPZ_FILIALE,\
        WEEKDAY=:WEEKDAY
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 /* original struct of KNDTOUREN ***********************************************/

#ifndef TRANSCLASS
 typedef struct N_KNDTOUREN {
     long IDFNR;
     char TOURID[7];
     long REIHENFOLGENR;
     long DATUMVERSAND;
     long ZEITVERSAND;
     long FAHRTZEIT;
     short BAHNHOFVERSAND;
     char ISTVERBUNDTOUR[2];
     short VERTRIEBSZENTRUMNR;
     long KUNDENNR;
     short PHARMACYLOCKACCESS;
     char REMARKLACKITEMPROCESSING[41];
     char REMARKLACKCALLBACK[41];
     char KOART[2];
     long LAGRECHTOUR;
     short KIPPZEIT;
     char KZAUTOZUORD[2];
     char KDAUFTRAGART[3];
     short ISBTM;
     short ISKK;
     short ISK08;
     short ISK20;
     short RETURNSTOUR;
     short TRANSPEXCLPSYCHO;
     short TRANSPEXCLCOOLED;
     short TRANSPEXCLEXPENSIVE;
     short PRIO1_KIPPZ_KTOUR;
     short PRIO2_KIPPZ_FTOUR;
     long PRIO3_KIPPZ_KUNDE;
     long PRIO4_KIPPZ_FILIALE;
     short WEEKDAY;
     long FETCH_REL;
 } kndtourenS;
#else /* TRANSCLASS */
 typedef struct N_KNDTOUREN {
     long IDFNR;
     char TOURID[7];
     long REIHENFOLGENR;
     long DATUMVERSAND;
     long ZEITVERSAND;
     long FAHRTZEIT;
     short BAHNHOFVERSAND;
     char ISTVERBUNDTOUR[2];
     short VERTRIEBSZENTRUMNR;
     long KUNDENNR;
     short PHARMACYLOCKACCESS;
     char REMARKLACKITEMPROCESSING[41];
     char REMARKLACKCALLBACK[41];
     char KOART[2];
     long LAGRECHTOUR;
     short KIPPZEIT;
     char KZAUTOZUORD[2];
     char KDAUFTRAGART[3];
     short ISBTM;
     short ISKK;
     short ISK08;
     short ISK20;
     short RETURNSTOUR;
     short TRANSPEXCLPSYCHO;
     short TRANSPEXCLCOOLED;
     short TRANSPEXCLEXPENSIVE;
     short PRIO1_KIPPZ_KTOUR;
     short PRIO2_KIPPZ_FTOUR;
     long PRIO3_KIPPZ_KUNDE;
     long PRIO4_KIPPZ_FILIALE;
     short WEEKDAY;
     long FETCH_REL;
     bool operator == (const N_KNDTOUREN& right) const {
         return (
             IDFNR == right.IDFNR &&
             !strcmp(TOURID, right.TOURID) &&
             REIHENFOLGENR == right.REIHENFOLGENR &&
             DATUMVERSAND == right.DATUMVERSAND &&
             ZEITVERSAND == right.ZEITVERSAND &&
             FAHRTZEIT == right.FAHRTZEIT &&
             BAHNHOFVERSAND == right.BAHNHOFVERSAND &&
             !strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
             VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
             KUNDENNR == right.KUNDENNR &&
             PHARMACYLOCKACCESS == right.PHARMACYLOCKACCESS &&
             !strcmp(REMARKLACKITEMPROCESSING, right.REMARKLACKITEMPROCESSING) &&
             !strcmp(REMARKLACKCALLBACK, right.REMARKLACKCALLBACK) &&
             !strcmp(KOART, right.KOART) &&
             LAGRECHTOUR == right.LAGRECHTOUR &&
             KIPPZEIT == right.KIPPZEIT &&
             !strcmp(KZAUTOZUORD, right.KZAUTOZUORD) &&
             !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
             ISBTM == right.ISBTM &&
             ISKK == right.ISKK &&
             ISK08 == right.ISK08 &&
             ISK20 == right.ISK20 &&
             RETURNSTOUR == right.RETURNSTOUR &&
             TRANSPEXCLPSYCHO == right.TRANSPEXCLPSYCHO &&
             TRANSPEXCLCOOLED == right.TRANSPEXCLCOOLED &&
             TRANSPEXCLEXPENSIVE == right.TRANSPEXCLEXPENSIVE &&
             PRIO1_KIPPZ_KTOUR == right.PRIO1_KIPPZ_KTOUR &&
             PRIO2_KIPPZ_FTOUR == right.PRIO2_KIPPZ_FTOUR &&
             PRIO3_KIPPZ_KUNDE == right.PRIO3_KIPPZ_KUNDE &&
             PRIO4_KIPPZ_FILIALE == right.PRIO4_KIPPZ_FILIALE &&
             WEEKDAY == right.WEEKDAY
             );
     }
     void clear() {
#ifdef WIN32
         memset((char*)this, 0, sizeof(*this));
#else
         IDFNR = 0;
         strcpy(TOURID, " ");
         REIHENFOLGENR = 0;
         DATUMVERSAND = 0;
         ZEITVERSAND = 0;
         FAHRTZEIT = 0;
         BAHNHOFVERSAND = 0;
         strcpy(ISTVERBUNDTOUR, " ");
         VERTRIEBSZENTRUMNR = 0;
         KUNDENNR = 0;
         PHARMACYLOCKACCESS = 0;
         strcpy(REMARKLACKITEMPROCESSING, " ");
         strcpy(REMARKLACKCALLBACK, " ");
         strcpy(KOART, " ");
         LAGRECHTOUR = 0;
         KIPPZEIT = 0;
         strcpy(KZAUTOZUORD, " ");
         strcpy(KDAUFTRAGART, " ");
         ISBTM = 0;
         ISKK = 0;
         ISK08 = 0;
         ISK20 = 0;
         RETURNSTOUR = 0;
         TRANSPEXCLPSYCHO = 0;
         TRANSPEXCLCOOLED = 0;
         TRANSPEXCLEXPENSIVE = 0;
         PRIO1_KIPPZ_KTOUR = 0;
         PRIO2_KIPPZ_FTOUR = 0;
         PRIO3_KIPPZ_KUNDE = 0;
         PRIO4_KIPPZ_FILIALE = 0;
         WEEKDAY = 0;
#endif
     }
 } kndtourenS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 /* Stringbuffer Structur of KNDTOUREN *****************************************/

 struct S_KNDTOUREN {
     char IDFNR[11];
     char TOURID[6 + 1];
     char REIHENFOLGENR[11];
     char DATUMVERSAND[11];
     char ZEITVERSAND[11];
     char FAHRTZEIT[11];
     char BAHNHOFVERSAND[7];
     char ISTVERBUNDTOUR[1 + 1];
     char VERTRIEBSZENTRUMNR[7];
     char KUNDENNR[11];
     char PHARMACYLOCKACCESS[7];
     char REMARKLACKITEMPROCESSING[40 + 1];
     char REMARKLACKCALLBACK[40 + 1];
     char KOART[1 + 1];
     char LAGRECHTOUR[11];
     char KIPPZEIT[7];
     char KZAUTOZUORD[1 + 1];
     char KDAUFTRAGART[2 + 1];
     char ISBTM[7];
     char ISKK[7];
     char ISK08[7];
     char ISK20[7];
     char RETURNSTOUR[7];
     char TRANSPEXCLPSYCHO[7];
     char TRANSPEXCLCOOLED[7];
     char TRANSPEXCLEXPENSIVE[7];
     char PRIO1_KIPPZ_KTOUR[7];
     char PRIO2_KIPPZ_FTOUR[7];
     char PRIO3_KIPPZ_KUNDE[11];
     char PRIO4_KIPPZ_FILIALE[11];
     char WEEKDAY[7];
     char FETCH_REL[11];
 };
#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 /* Stringbuffer (without strend) Structur of KNDTOUREN ************************/

 struct O_KNDTOUREN {
     char IDFNR[11];
     char TOURID[6];
     char REIHENFOLGENR[11];
     char DATUMVERSAND[11];
     char ZEITVERSAND[11];
     char FAHRTZEIT[11];
     char BAHNHOFVERSAND[7];
     char ISTVERBUNDTOUR[1];
     char VERTRIEBSZENTRUMNR[7];
     char KUNDENNR[11];
     char PHARMACYLOCKACCESS[7];
     char REMARKLACKITEMPROCESSING[40];
     char REMARKLACKCALLBACK[40];
     char KOART[1];
     char LAGRECHTOUR[11];
     char KIPPZEIT[7];
     char KZAUTOZUORD[1];
     char KDAUFTRAGART[2];
     char ISBTM[7];
     char ISKK[7];
     char ISK08[7];
     char ISK20[7];
     char RETURNSTOUR[7];
     char TRANSPEXCLPSYCHO[7];
     char TRANSPEXCLCOOLED[7];
     char TRANSPEXCLEXPENSIVE[7];
     char PRIO1_KIPPZ_KTOUR[7];
     char PRIO2_KIPPZ_FTOUR[7];
     char PRIO3_KIPPZ_KUNDE[11];
     char PRIO4_KIPPZ_FILIALE[11];
     char WEEKDAY[7];
     char FETCH_REL[11];
 };
#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 /* Structur with real chartype of KNDTOUREN ***********************************/

 struct C_KNDTOUREN {
     long IDFNR;
     char TOURID[7];
     long REIHENFOLGENR;
     long DATUMVERSAND;
     long ZEITVERSAND;
     long FAHRTZEIT;
     short BAHNHOFVERSAND;
     char ISTVERBUNDTOUR;
     short VERTRIEBSZENTRUMNR;
     long KUNDENNR;
     short PHARMACYLOCKACCESS;
     char REMARKLACKITEMPROCESSING[41];
     char REMARKLACKCALLBACK[41];
     char KOART;
     long LAGRECHTOUR;
     short KIPPZEIT;
     char KZAUTOZUORD;
     char KDAUFTRAGART[3];
     short ISBTM;
     short ISKK;
     short ISK08;
     short ISK20;
     short RETURNSTOUR;
     short TRANSPEXCLPSYCHO;
     short TRANSPEXCLCOOLED;
     short TRANSPEXCLEXPENSIVE;
     short PRIO1_KIPPZ_KTOUR;
     short PRIO2_KIPPZ_FTOUR;
     long PRIO3_KIPPZ_KUNDE;
     long PRIO4_KIPPZ_FILIALE;
     short WEEKDAY;
     long FETCH_REL;
 };
#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 /* Sizetype  Structur (buf_desc) of KNDTOUREN *********************************/

 struct I_KNDTOUREN {
     short IDFNR;
     short TOURID;
     short REIHENFOLGENR;
     short DATUMVERSAND;
     short ZEITVERSAND;
     short FAHRTZEIT;
     short BAHNHOFVERSAND;
     short ISTVERBUNDTOUR;
     short VERTRIEBSZENTRUMNR;
     short KUNDENNR;
     short PHARMACYLOCKACCESS;
     short REMARKLACKITEMPROCESSING;
     short REMARKLACKCALLBACK;
     short KOART;
     short LAGRECHTOUR;
     short KIPPZEIT;
     short KZAUTOZUORD;
     short KDAUFTRAGART;
     short ISBTM;
     short ISKK;
     short ISK08;
     short ISK20;
     short RETURNSTOUR;
     short TRANSPEXCLPSYCHO;
     short TRANSPEXCLCOOLED;
     short TRANSPEXCLEXPENSIVE;
     short PRIO1_KIPPZ_KTOUR;
     short PRIO2_KIPPZ_FTOUR;
     short PRIO3_KIPPZ_KUNDE;
     short PRIO4_KIPPZ_FILIALE;
     short WEEKDAY;
     short FETCH_REL;
 };
#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

 /* structures of Buf_Desc *****************************************************/

 /* Structur (buf_desc) of KNDTOUREN *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc KNDTOUREN_BES[] = {
    { TYP_L , 11, 0 },
    { TYP_C, 6, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 1, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 40, 0 },
    { TYP_C, 40, 0 },
    { TYP_C, 1, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 1, 0 },
    { TYP_C, 2, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDTOUREN_BES[] = {
    { TYP_L , 11, 0 },
    { TYP_C, 6, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 1, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 40, 0 },
    { TYP_C, 40, 0 },
    { TYP_C, 1, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_C, 1, 0 },
    { TYP_C, 2, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
    { TYP_L , 11, 0 },
    { TYP_S ,  6, 0 },
    { TYP_L , 11, 0 },
 };
#endif

 /* description for datatypes of KNDTOUREN *************************************/

#define KNDTOUREN_S390 \
         long IDFNR; \
         char TOURID[7]; \
         long REIHENFOLGENR; \
         long DATUMVERSAND; \
         long ZEITVERSAND; \
         long FAHRTZEIT; \
         short BAHNHOFVERSAND; \
         char ISTVERBUNDTOUR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short PHARMACYLOCKACCESS; \
         char REMARKLACKITEMPROCESSING[41]; \
         char REMARKLACKCALLBACK[41]; \
         char KOART; \
         long LAGRECHTOUR; \
         short KIPPZEIT; \
         char KZAUTOZUORD; \
         char KDAUFTRAGART[3]; \
         short ISBTM; \
         short ISKK; \
         short ISK08; \
         short ISK20; \
         short RETURNSTOUR; \
         short TRANSPEXCLPSYCHO; \
         short TRANSPEXCLCOOLED; \
         short TRANSPEXCLEXPENSIVE; \
         short PRIO1_KIPPZ_KTOUR; \
         short PRIO2_KIPPZ_FTOUR; \
         long PRIO3_KIPPZ_KUNDE; \
         long PRIO4_KIPPZ_FILIALE; \
         short WEEKDAY; \
         long FETCH_REL;



/* Copy-Function Struct to single Data KNDTOUREN ******************************/

#define KNDTOUREN_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
          strcpy(TOURID,_x_->TOURID);\
         REIHENFOLGENR=_x_->REIHENFOLGENR;\
         DATUMVERSAND=_x_->DATUMVERSAND;\
         ZEITVERSAND=_x_->ZEITVERSAND;\
         FAHRTZEIT=_x_->FAHRTZEIT;\
         BAHNHOFVERSAND=_x_->BAHNHOFVERSAND;\
         ISTVERBUNDTOUR=_x_->ISTVERBUNDTOUR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         PHARMACYLOCKACCESS=_x_->PHARMACYLOCKACCESS;\
          strcpy(REMARKLACKITEMPROCESSING,_x_->REMARKLACKITEMPROCESSING);\
          strcpy(REMARKLACKCALLBACK,_x_->REMARKLACKCALLBACK);\
         KOART=_x_->KOART;\
         LAGRECHTOUR=_x_->LAGRECHTOUR;\
         KIPPZEIT=_x_->KIPPZEIT;\
         KZAUTOZUORD=_x_->KZAUTOZUORD;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         ISBTM=_x_->ISBTM;\
         ISKK=_x_->ISKK;\
         ISK08=_x_->ISK08;\
         ISK20=_x_->ISK20;\
         RETURNSTOUR=_x_->RETURNSTOUR;\
         TRANSPEXCLPSYCHO=_x_->TRANSPEXCLPSYCHO;\
         TRANSPEXCLCOOLED=_x_->TRANSPEXCLCOOLED;\
         TRANSPEXCLEXPENSIVE=_x_->TRANSPEXCLEXPENSIVE;\
         PRIO1_KIPPZ_KTOUR=_x_->PRIO1_KIPPZ_KTOUR;\
         PRIO2_KIPPZ_FTOUR=_x_->PRIO2_KIPPZ_FTOUR;\
         PRIO3_KIPPZ_KUNDE=_x_->PRIO3_KIPPZ_KUNDE;\
         PRIO4_KIPPZ_FILIALE=_x_->PRIO4_KIPPZ_FILIALE;\
         WEEKDAY=_x_->WEEKDAY;\
          FETCH_REL=_x_->FETCH_REL;\

#define KNDTOUREN_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->REIHENFOLGENR=REIHENFOLGENR;\
          _x_->DATUMVERSAND=DATUMVERSAND;\
          _x_->ZEITVERSAND=ZEITVERSAND;\
          _x_->FAHRTZEIT=FAHRTZEIT;\
          _x_->BAHNHOFVERSAND=BAHNHOFVERSAND;\
          _x_->ISTVERBUNDTOUR=ISTVERBUNDTOUR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->PHARMACYLOCKACCESS=PHARMACYLOCKACCESS;\
          strcpy(_x_->REMARKLACKITEMPROCESSING,REMARKLACKITEMPROCESSING);\
          strcpy(_x_->REMARKLACKCALLBACK,REMARKLACKCALLBACK);\
          _x_->KOART=KOART;\
          _x_->LAGRECHTOUR=LAGRECHTOUR;\
          _x_->KIPPZEIT=KIPPZEIT;\
          _x_->KZAUTOZUORD=KZAUTOZUORD;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->ISBTM=ISBTM;\
          _x_->ISKK=ISKK;\
          _x_->ISK08=ISK08;\
          _x_->ISK20=ISK20;\
          _x_->RETURNSTOUR=RETURNSTOUR;\
          _x_->TRANSPEXCLPSYCHO=TRANSPEXCLPSYCHO;\
          _x_->TRANSPEXCLCOOLED=TRANSPEXCLCOOLED;\
          _x_->TRANSPEXCLEXPENSIVE=TRANSPEXCLEXPENSIVE;\
          _x_->PRIO1_KIPPZ_KTOUR=PRIO1_KIPPZ_KTOUR;\
          _x_->PRIO2_KIPPZ_FTOUR=PRIO2_KIPPZ_FTOUR;\
          _x_->PRIO3_KIPPZ_KUNDE=PRIO3_KIPPZ_KUNDE;\
          _x_->PRIO4_KIPPZ_FILIALE=PRIO4_KIPPZ_FILIALE;\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of KNDTOUREN *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of KNDTOUREN *************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
 using namespace std;

 /* ppunixc */
#include <sockclient.h>
#include <ppstring.h>
#include <ppgeneric.h>

/* must be implemented */
 void FehlerBehandlung(int rc, const char* const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

 class ppDadeVirtual {
 public:
     virtual    ~ppDadeVirtual() {};
     virtual int SelList(int FetchRel = 1, int pos = 0) = 0;
     virtual int SelListHist(int FetchRel = 1, int pos = 0) = 0;
     virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
     virtual int Load(int pos = 0) = 0;
     virtual int Delete(int pos = 0) = 0;
     virtual int Save(int pos = 0) = 0;
 };
#endif

 class CKNDTOUREN : public ppDadeVirtual {
 public:
     kndtourenS s;
     int  rc;
     char error_msg[81];
 private:
     bool bOpenCursor;
     bool bEndOfSelect;
     int  FncNumber;
     int  CursorPos;
     int  AnzPos;
     vector<kndtourenS> lst; // class list

 public:
     unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
     void         ClearStruct() { s.clear(); }
     bool         SetData(unsigned int i) {
         if (GetSize() <= i)
             return false;
         s = lst.at(i);
         return true;
     }
     bool         SetList(const unsigned int i) {
         if (GetSize() <= i)
             return false;
         vector< kndtourenS >::iterator it = lst.begin() + i;
         *it = s;
         return true;
     }
     bool         InsList() {
         Strip(s);
         kndtourenS c = s;
         lst.insert(lst.end(), c);
         AnzPos++;
         return true;
     }
     bool         DelList(const unsigned int i) {
         if (GetSize() <= i)
             return false;
         vector< kndtourenS >::iterator it = lst.begin() + i;
         if (it != lst.end())
             lst.erase(it);
         if (--AnzPos < 0)
             AnzPos = 0;
         return true;
     }

     vector<kndtourenS>::iterator
         beginList() { return lst.begin(); }
     vector<kndtourenS>::iterator
         endList() { return lst.end(); }

     long         GetIdfnr() const { return s.IDFNR; }
     const char* GetTourid(ppString& t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
     long         GetReihenfolgenr() const { return s.REIHENFOLGENR; }
     long         GetDatumversand() const { return s.DATUMVERSAND; }
     long         GetZeitversand() const { return s.ZEITVERSAND; }
     long         GetFahrtzeit() const { return s.FAHRTZEIT; }
     short        GetBahnhofversand() const { return s.BAHNHOFVERSAND; }
     char         GetIstverbundtour() const { return s.ISTVERBUNDTOUR[0]; }
     short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
     long         GetKundennr() const { return s.KUNDENNR; }
     short        GetPharmacylockaccess() const { return s.PHARMACYLOCKACCESS; }
     const char* GetRemarklackitemprocessing(ppString& t) const { t = s.REMARKLACKITEMPROCESSING; t.erasespace(ppString::END); return t.c_str(); }
     const char* GetRemarklackcallback(ppString& t) const { t = s.REMARKLACKCALLBACK; t.erasespace(ppString::END); return t.c_str(); }
     char         GetKoart() const { return s.KOART[0]; }
     long         GetLagrechtour() const { return s.LAGRECHTOUR; }
     short        GetKippzeit() const { return s.KIPPZEIT; }
     char         GetKzautozuord() const { return s.KZAUTOZUORD[0]; }
     const char* GetKdauftragart(ppString& t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
     short        GetIsbtm() const { return s.ISBTM; }
     short        GetIskk() const { return s.ISKK; }
     short        GetIsk08() const { return s.ISK08; }
     short        GetIsk20() const { return s.ISK20; }
     short        GetReturnstour() const { return s.RETURNSTOUR; }
     short        GetTranspexclpsycho() const { return s.TRANSPEXCLPSYCHO; }
     short        GetTranspexclcooled() const { return s.TRANSPEXCLCOOLED; }
     short        GetTranspexclexpensive() const { return s.TRANSPEXCLEXPENSIVE; }
     short        GetPrio1_kippz_ktour() const { return s.PRIO1_KIPPZ_KTOUR; }
     short        GetPrio2_kippz_ftour() const { return s.PRIO2_KIPPZ_FTOUR; }
     long         GetPrio3_kippz_kunde() const { return s.PRIO3_KIPPZ_KUNDE; }
     long         GetPrio4_kippz_filiale() const { return s.PRIO4_KIPPZ_FILIALE; }
     short        GetWeekday() const { return s.WEEKDAY; }

     const kndtourenS&
         GetStruct() const { return s; }
     long         GetFetch_rel() const { return s.FETCH_REL; }

     void         SetIdfnr(long t) { s.IDFNR = t; }
     void         SetTourid(const ppString& t) { ppGStrCopy(s.TOURID, t.c_str(), L_KNDTOUREN_TOURID); }
     void         SetReihenfolgenr(long t) { s.REIHENFOLGENR = t; }
     void         SetDatumversand(long t) { s.DATUMVERSAND = t; }
     void         SetZeitversand(long t) { s.ZEITVERSAND = t; }
     void         SetFahrtzeit(long t) { s.FAHRTZEIT = t; }
     void         SetBahnhofversand(short t) { s.BAHNHOFVERSAND = t; }
     void         SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0'; }
     void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
     void         SetKundennr(long t) { s.KUNDENNR = t; }
     void         SetPharmacylockaccess(short t) { s.PHARMACYLOCKACCESS = t; }
     void         SetRemarklackitemprocessing(const ppString& t) { ppGStrCopy(s.REMARKLACKITEMPROCESSING, t.c_str(), L_KNDTOUREN_REMARKLACKITEMPROCESSING); }
     void         SetRemarklackcallback(const ppString& t) { ppGStrCopy(s.REMARKLACKCALLBACK, t.c_str(), L_KNDTOUREN_REMARKLACKCALLBACK); }
     void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0'; }
     void         SetLagrechtour(long t) { s.LAGRECHTOUR = t; }
     void         SetKippzeit(short t) { s.KIPPZEIT = t; }
     void         SetKzautozuord(char t) { s.KZAUTOZUORD[0] = t; s.KZAUTOZUORD[1] = '\0'; }
     void         SetKdauftragart(const ppString& t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_KNDTOUREN_KDAUFTRAGART); }
     void         SetIsbtm(short t) { s.ISBTM = t; }
     void         SetIskk(short t) { s.ISKK = t; }
     void         SetIsk08(short t) { s.ISK08 = t; }
     void         SetIsk20(short t) { s.ISK20 = t; }
     void         SetReturnstour(short t) { s.RETURNSTOUR = t; }
     void         SetTranspexclpsycho(short t) { s.TRANSPEXCLPSYCHO = t; }
     void         SetTranspexclcooled(short t) { s.TRANSPEXCLCOOLED = t; }
     void         SetTranspexclexpensive(short t) { s.TRANSPEXCLEXPENSIVE = t; }
     void         SetPrio1_kippz_ktour(short t) { s.PRIO1_KIPPZ_KTOUR = t; }
     void         SetPrio2_kippz_ftour(short t) { s.PRIO2_KIPPZ_FTOUR = t; }
     void         SetPrio3_kippz_kunde(long t) { s.PRIO3_KIPPZ_KUNDE = t; }
     void         SetPrio4_kippz_filiale(long t) { s.PRIO4_KIPPZ_FILIALE = t; }
     void         SetWeekday(short t) { s.WEEKDAY = t; }

     void         SetStruct(const kndtourenS& t) { s = t; }
     void         SetFetch_rel(const long t) { s.FETCH_REL = t; }


     // virtual functions
 public:
     int          Load(int pos = 0) { pos = pos; return 1; }
     int          Save(int pos = 0) { pos = pos; return 1; }
     int          Delete(int pos = 0) { pos = pos; return 1; }
     int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
     int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
     int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

     // constructor
     CKNDTOUREN() {
         ::buf_default((void*)&s, KNDTOUREN_BES, KNDTOUREN_ANZ);
         bOpenCursor = false;
         bEndOfSelect = false;
         FncNumber = 0;
         CursorPos = 0;
         AnzPos = 0;
         rc = 0;
         s.clear();
     }

     // destructor
     virtual ~CKNDTOUREN() {
         CloseCursor();
     }

     // buffer init
     void buf_default() {
         ::buf_default((void*)&s, KNDTOUREN_BES, KNDTOUREN_ANZ);
     }

     // close db cursor
     int CloseCursor(int pos = 0) {
         if (!bOpenCursor)
             return 0;
         s.FETCH_REL = 0;
#ifndef __DADE_LOAD__
         rc = ::ServerNr(pos, FncNumber, (void*)&s, KNDTOUREN_BES, (int)KNDTOUREN_ANZ, error_msg);
#else
         pos = pos;
         rc = DistributorFunSelect(FncNumber, (void*)&s, error_msg, &rc);
#endif
         bOpenCursor = false;
         bEndOfSelect = false;
         FncNumber = 0;
         CursorPos = 0;
         AnzPos = 0;
         if (rc < 0)
             FehlerBehandlung(rc, error_msg);
         return rc;
     }

     // socket server call
     int Server(int fkt_nr, int pos = 0) {
#ifdef WIN32
         rc = ::ServerNr(pos, fkt_nr, (void*)&s, KNDTOUREN_BES, (int)KNDTOUREN_ANZ, error_msg);
#else
         rc = ::Server(fkt_nr, (void*)&s, KNDTOUREN_BES, (int)KNDTOUREN_ANZ, error_msg);
#endif
         if (rc < 0)
             FehlerBehandlung(rc, error_msg);
         return rc;
     }

 private:
     void Strip(N_KNDTOUREN& d) {
         d = d;
#ifdef WIN32
         ppGStripLast(d.TOURID);
         ppGStripLast(d.REMARKLACKITEMPROCESSING);
         ppGStripLast(d.REMARKLACKCALLBACK);
         ppGStripLast(d.KDAUFTRAGART);
#endif
     }

     int UniqueServerCall(int FncNr, int pos = 0) {
#ifndef __DADE_LOAD__
         rc = ::ServerNr(pos, FncNr, (void*)&s, KNDTOUREN_BES, (int)KNDTOUREN_ANZ, error_msg);
#else
         pos = pos;
         rc = DistributorFunSelect(FncNr, (void*)&s, error_msg, &rc);
#endif
         if (rc < 0)
             FehlerBehandlung(rc, error_msg);
         return rc;
     }

     int CursorServerCall(int FncNr, int FetchRel = 1, int pos = 0) {
         if (FetchRel == 0) return CloseCursor(pos);
         else if (FetchRel == 1) return GetNext(pos, FncNr);
         else if (FetchRel < 0) return ChangeCursor(FetchRel);
         else {
             FehlerBehandlung(-1, "False cursor position!");
             return -1;
         }
     }

     int GetNext(int pos, int FncNr) {
         CKNDTOUREN c;
         if (bOpenCursor && FncNumber != FncNr)
             CloseCursor(pos);
         if (bOpenCursor)
             s.FETCH_REL = 1;
         else {
             s.FETCH_REL = 2;
             bOpenCursor = true;
             FncNumber = FncNr;
             AnzPos = 0;
             lst.clear();
         }
         if ((CursorPos == AnzPos) && bEndOfSelect) {
             rc = 1;
             return 1;
         }
         else if (CursorPos < AnzPos) {
             s = lst.at(CursorPos);
             CursorPos++;
             return 0;
         }
#ifndef __DADE_LOAD__
         rc = ::ServerNr(pos, FncNumber, (void*)&s, KNDTOUREN_BES, (int)KNDTOUREN_ANZ, error_msg);
#else
         rc = DistributorFunSelect(FncNumber, (void*)&s, error_msg, &rc);
#endif
         if (rc == 0) {
             Strip(s);
             c.s = s;
             lst.insert(lst.end(), c.s);
             bEndOfSelect = false;
             CursorPos++;
             AnzPos++;
         }
         else if (rc == 1)
             bEndOfSelect = true;
         else if (rc < 0)
             FehlerBehandlung(rc, error_msg);
         return rc;
     }

     // FetchRel is a negative value
     int ChangeCursor(int FetchRel) {
         CursorPos = (CursorPos + FetchRel) < 0 ?
             0 :
             CursorPos + FetchRel - 1;
         if (CursorPos >= AnzPos) {
             FehlerBehandlung(-1, "False cursor position!");
             return -1;
         }
         s = lst.at(CursorPos);
         CursorPos++;
         rc = 0;
         return 0;
     }
 };
#endif    // TRANSCLASS
 /* CreateSqlStatement of KNDTOUREN ********************************************/

#define KNDTOUREN_CREATE(x) EXEC SQL create table x (\
         IDFNR integer default 0 not null,\
         TOURID char(6) default " " not null,\
         REIHENFOLGENR integer default 0 not null,\
         DATUMVERSAND integer default 0 not null,\
         ZEITVERSAND integer default 0 not null,\
         FAHRTZEIT integer default 0 not null,\
         BAHNHOFVERSAND smallint default 0 not null,\
         ISTVERBUNDTOUR char(1) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         PHARMACYLOCKACCESS smallint default 0 not null,\
         REMARKLACKITEMPROCESSING char(40) default " " not null,\
         REMARKLACKCALLBACK char(40) default " " not null,\
         KOART char(1) default " " not null,\
         LAGRECHTOUR integer default 0 not null,\
         KIPPZEIT smallint default 0 not null,\
         KZAUTOZUORD char(1) default " " not null,\
         KDAUFTRAGART char(2) default " " not null,\
         ISBTM smallint default 0 not null,\
         ISKK smallint default 0 not null,\
         ISK08 smallint default 0 not null,\
         ISK20 smallint default 0 not null,\
         RETURNSTOUR smallint default 0 not null,\
         TRANSPEXCLPSYCHO smallint default 0 not null,\
         TRANSPEXCLCOOLED smallint default 0 not null,\
         TRANSPEXCLEXPENSIVE smallint default 0 not null,\
         PRIO1_KIPPZ_KTOUR smallint default 0 not null,\
         PRIO2_KIPPZ_FTOUR smallint default 0 not null,\
         PRIO3_KIPPZ_KUNDE integer default 0 not null,\
         PRIO4_KIPPZ_FILIALE integer default 0 not null,\
         WEEKDAY smallint default 0 not null) extent size 1020 next size 104 lock mode row;



/* CreateIndexStatement of KNDTOUREN ******************************************/

#define KNDTOUREN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tourplantag_2 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              datumkommi,\
              tourid );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index tourplantagx on _X_(\
              idfnr,\
              datumkommi,\
              tourid );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KNDTOUREN ******************************************/

#define KNDTOUREN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tourplantag_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index tourplantagx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
