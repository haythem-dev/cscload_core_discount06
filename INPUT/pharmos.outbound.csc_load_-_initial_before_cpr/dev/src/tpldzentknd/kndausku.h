/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KNDAUSKU_EILBOTENZUSCHLAG     5
 #define N_KNDAUSKU_EILBOTENZUSCHLAG     2
 #define L_KNDAUSKU_MONATSUMSATZ         9
 #define N_KNDAUSKU_MONATSUMSATZ         2
 #define L_KNDAUSKU_IDFNR                11
 #define L_KNDAUSKU_MALUSFREI_PROZ       5
 #define N_KNDAUSKU_MALUSFREI_PROZ       2
 #define L_KNDAUSKU_VERTRETER_2          6
 #define L_KNDAUSKU_KUNDE_SEIT           11
 #define L_KNDAUSKU_URLAUB_VON           11
 #define L_KNDAUSKU_URLAUB_BIS           11
 #define L_KNDAUSKU_VERSAND_KOSTEN       5
 #define N_KNDAUSKU_VERSAND_KOSTEN       2
 #define L_KNDAUSKU_KZUPD                1
 #define L_KNDAUSKU_KUNDENNR             11
 #define L_KNDAUSKU_VERTRIEBSZENTRUMNR   6
 #define L_KNDAUSKU_DISPOGEBUEHR	     5
 #define N_KNDAUSKU_DISPOGEBUEHR	     2
 #define L_KNDAUSKU_BTMGEBUEHR		     5
 #define N_KNDAUSKU_BTMGEBUEHR		     2
 #define L_KNDAUSKU_DOKUGEBUEHR		     5
 #define N_KNDAUSKU_DOKUGEBUEHR		     2
 #define L_KNDAUSKU_LOGISTIKAUFSCHLAG    5
 #define N_KNDAUSKU_LOGISTIKAUFSCHLAG    2
 #define L_KNDAUSKU_LOGISTIKAUFSCHLAGMIN 5
 #define N_KNDAUSKU_LOGISTIKAUFSCHLAGMIN 2


 #define L_KNDAUSKU_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KNDAUSKU_ANZ ( sizeof(KNDAUSKU_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KNDAUSKU sizeof(struct KNDAUSKU)


 #define KNDAUSKU_H

 #define KNDAUSKU_LISTE \
 			KNDAUSKU.EILBOTENZUSCHLAG, \
 			KNDAUSKU.MONATSUMSATZ, \
 			KNDAUSKU.IDFNR, \
 			KNDAUSKU.MALUSFREI_PROZ, \
 			KNDAUSKU.VERTRETER_2, \
 			KNDAUSKU.KUNDE_SEIT, \
 			KNDAUSKU.URLAUB_VON, \
 			KNDAUSKU.URLAUB_BIS, \
 			KNDAUSKU.VERSAND_KOSTEN, \
 			KNDAUSKU.KZUPD, \
			KNDAUSKU.KUNDENNR, \
			KNDAUSKU.VERTRIEBSZENTRUMNR, \
			KNDAUSKU.DISPOGEBUEHR, \
			KNDAUSKU.BTMGEBUEHR, \
			KNDAUSKU.DOKUGEBUEHR, \
			KNDAUSKU.LOGISTIKAUFSCHLAG, \
			KNDAUSKU.LOGISTIKAUFSCHLAGMIN
 #define KNDAUSKU_PLISTE \
 			"KNDAUSKU.EILBOTENZUSCHLAG," \
 			"KNDAUSKU.MONATSUMSATZ," \
 			"KNDAUSKU.IDFNR," \
 			"KNDAUSKU.MALUSFREI_PROZ," \
 			"KNDAUSKU.VERTRETER_2," \
 			"KNDAUSKU.KUNDE_SEIT," \
 			"KNDAUSKU.URLAUB_VON," \
 			"KNDAUSKU.URLAUB_BIS," \
 			"KNDAUSKU.VERSAND_KOSTEN," \
 			"KNDAUSKU.KZUPD," \
			"KNDAUSKU.KUNDENNR," \
			"KNDAUSKU.VERTRIEBSZENTRUMNR," \
			"KNDAUSKU.DISPOGEBUEHR," \
			"KNDAUSKU.BTMGEBUEHR," \
			"KNDAUSKU.DOKUGEBUEHR," \
			"KNDAUSKU.LOGISTIKAUFSCHLAG," \
			"KNDAUSKU.LOGISTIKAUFSCHLAGMIN "

 #define KNDAUSKU_PELISTE \
 			"EILBOTENZUSCHLAG," \
 			"MONATSUMSATZ," \
 			"IDFNR," \
 			"MALUSFREI_PROZ," \
 			"VERTRETER_2," \
 			"KUNDE_SEIT," \
 			"URLAUB_VON," \
 			"URLAUB_BIS," \
 			"VERSAND_KOSTEN," \
 			"KZUPD," \
			"KUNDENNR," \
			"VERTRIEBSZENTRUMNR," \
			"DISPOGEBUEHR," \
			"BTMGEBUEHR," \
			"DOKUGEBUEHR," \
			"LOGISTIKAUFSCHLAG," \
			"LOGISTIKAUFSCHLAGMIN "

 #define KNDAUSKU_UPDLISTE \
 			"EILBOTENZUSCHLAG=?," \
 			"MONATSUMSATZ=?," \
 			"IDFNR=?," \
 			"MALUSFREI_PROZ=?," \
 			"VERTRETER_2=?," \
 			"KUNDE_SEIT=?," \
 			"URLAUB_VON=?," \
 			"URLAUB_BIS=?," \
 			"VERSAND_KOSTEN=?," \
 			"KZUPD=?," \
			"KUNDENNR=?," \
			"VERTRIEBSZENTRUMNR=?," \
			"DISPOGEBUEHR=?," \
			"BTMGEBUEHR=?," \
			"DOKUGEBUEHR=?," \
			"LOGISTIKAUFSCHLAG=?," \
			"LOGISTIKAUFSCHLAGMIN=? "

 #define KNDAUSKUEILBOTENZUSCHLAG              0
 #define KNDAUSKUMONATSUMSATZ                  1
 #define KNDAUSKUIDFNR                         2
 #define KNDAUSKUMALUSFREI_PROZ                3
 #define KNDAUSKUVERTRETER_2                   4
 #define KNDAUSKUKUNDE_SEIT                    5
 #define KNDAUSKUURLAUB_VON                    6
 #define KNDAUSKUURLAUB_BIS                    7
 #define KNDAUSKUVERSAND_KOSTEN                8
 #define KNDAUSKUKZUPD                         9
 #define KNDAUSKUKUNDENNR					   10
 #define KNDAUSKUVERTRIEBSZENTRUMNR			   11
 #define KNDAUSKUDISPOGEBUEHR				   12
 #define KNDAUSKUBTMGEBUEHR					   13
 #define KNDAUSKUDOKUGEBUEHR				   14
 #define KNDAUSKULOGISTIKAUFSCHLAG			   15
 #define KNDAUSKULOGISTIKAUFSCHLAGMIN		   16

 #define KNDAUSKU_ZEIGER(xxx) \
 			:xxx->EILBOTENZUSCHLAG,\
 			:xxx->MONATSUMSATZ,\
 			:xxx->IDFNR,\
 			:xxx->MALUSFREI_PROZ,\
 			:xxx->VERTRETER_2,\
 			:xxx->KUNDE_SEIT,\
 			:xxx->URLAUB_VON,\
 			:xxx->URLAUB_BIS,\
 			:xxx->VERSAND_KOSTEN,\
 			:xxx->KZUPD,\
			:xxx->KUNDENNR,\
			:xxx->VERTRIEBSZENTRUMNR,\
			:xxx->DISPOGEBUEHR,\
			:xxx->BTMGEBUEHR,\
			:xxx->DOKUGEBUEHR,\
			:xxx->LOGISTIKAUFSCHLAG,\
			:xxx->LOGISTIKAUFSCHLAGMIN

 #define KNDAUSKU_UPDATE(xxx) \
 			EILBOTENZUSCHLAG = :xxx->EILBOTENZUSCHLAG,\
 			MONATSUMSATZ = :xxx->MONATSUMSATZ,\
 			IDFNR = :xxx->IDFNR,\
 			MALUSFREI_PROZ = :xxx->MALUSFREI_PROZ,\
 			VERTRETER_2 = :xxx->VERTRETER_2,\
 			KUNDE_SEIT = :xxx->KUNDE_SEIT,\
 			URLAUB_VON = :xxx->URLAUB_VON,\
 			URLAUB_BIS = :xxx->URLAUB_BIS,\
 			VERSAND_KOSTEN = :xxx->VERSAND_KOSTEN,\
 			KZUPD = :xxx->KZUPD,\
			KUNDENNR = :xxx->KUNDENNR,\
			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
			DISPOGEBUEHR = :xxx->DISPOGEBUEHR,\
			BTMGEBUEHR = :xxx->BTMGEBUEHR,\
			DOKUGEBUEHR = :xxx->DOKUGEBUEHR,\
			LOGISTIKAUFSCHLAG = :xxx->LOGISTIKAUFSCHLAG,\
			LOGISTIKAUFSCHLAGMIN = :xxx->LOGISTIKAUFSCHLAGMIN

 #define LS_KNDAUSKU_EILBOTENZUSCHLAG     7
 #define LS_KNDAUSKU_MONATSUMSATZ         11
 #define LS_KNDAUSKU_IDFNR                11
 #define LS_KNDAUSKU_MALUSFREI_PROZ       7
 #define LS_KNDAUSKU_VERTRETER_2          7
 #define LS_KNDAUSKU_KUNDE_SEIT           11
 #define LS_KNDAUSKU_URLAUB_VON           11
 #define LS_KNDAUSKU_URLAUB_BIS           11
 #define LS_KNDAUSKU_VERSAND_KOSTEN       7
 #define LS_KNDAUSKU_KZUPD                2
 #define LS_KNDAUSKU_KUNDENNR             11
 #define LS_KNDAUSKU_VERTRIEBSZENTRUMNR   7
 #define LS_KNDAUSKU_DISPOGEBUEHR		  7
 #define LS_KNDAUSKU_BTMGEBUEHR			  7
 #define LS_KNDAUSKU_DOKUGEBUEHR		  7
 #define LS_KNDAUSKU_LOGISTIKAUFSCHLAG    7
 #define LS_KNDAUSKU_LOGISTIKAUFSCHLAGMIN 7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KNDAUSKU {
		 double  EILBOTENZUSCHLAG;
		 double  MONATSUMSATZ;
		 long    IDFNR;
		 double  MALUSFREI_PROZ;
		 short   VERTRETER_2;
		 long    KUNDE_SEIT;
		 long    URLAUB_VON;
		 long    URLAUB_BIS;
		 double  VERSAND_KOSTEN;
		 char    KZUPD[1 + 1];
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 double  DISPOGEBUEHR;
		 double  BTMGEBUEHR;
		 double  DOKUGEBUEHR;
		 double  LOGISTIKAUFSCHLAG;
		 double  LOGISTIKAUFSCHLAGMIN;
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
		 long    IDFNR;
		 double  MALUSFREI_PROZ;
		 short   VERTRETER_2;
		 long    KUNDE_SEIT;
		 long    URLAUB_VON;
		 long    URLAUB_BIS;
		 double  VERSAND_KOSTEN;
		 char    KZUPD;
		 long	 KUNDENNR;
		 short	 VERTRIEBSZENTRUMNR;
		 double  DISPOGEBUEHR;
		 double  BTMGEBUEHR;
		 double  DOKUGEBUEHR;
		 double  LOGISTIKAUFSCHLAG;
		 double  LOGISTIKAUFSCHLAGMIN;
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
		 short  IDFNR;
		 short  MALUSFREI_PROZ;
		 short  VERTRETER_2;
		 short  KUNDE_SEIT;
		 short  URLAUB_VON;
		 short  URLAUB_BIS;
		 short  VERSAND_KOSTEN;
		 short  KZUPD;
		 short	KUNDENNR;
		 short	VERTRIEBSZENTRUMNR;
		 short  DISPOGEBUEHR;
		 short  BTMGEBUEHR;
		 short  DOKUGEBUEHR;
		 short  LOGISTIKAUFSCHLAG;
		 short  LOGISTIKAUFSCHLAGMIN;
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
		 char    IDFNR[11];
		 char    MALUSFREI_PROZ[5 + 2];
		 char    VERTRETER_2[7];
		 char    KUNDE_SEIT[11];
		 char    URLAUB_VON[11];
		 char    URLAUB_BIS[11];
		 char    VERSAND_KOSTEN[5 + 2];
		 char    KZUPD[1 + 1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    DISPOGEBUEHR[5 + 2];
		 char    BTMGEBUEHR[5 + 2];
		 char    DOKUGEBUEHR[5 + 2];
		 char    LOGISTIKAUFSCHLAG[5 + 2];
		 char    LOGISTIKAUFSCHLAGMIN[5 + 2];
       };

 struct O_KNDAUSKU {
		 char    EILBOTENZUSCHLAG[5];
		 char    MONATSUMSATZ[9];
		 char    IDFNR[11];
		 char    MALUSFREI_PROZ[5];
		 char    VERTRETER_2[7];
		 char    KUNDE_SEIT[11];
		 char    URLAUB_VON[11];
		 char    URLAUB_BIS[11];
		 char    VERSAND_KOSTEN[5];
		 char    KZUPD[1];
		 char	 KUNDENNR[11];
		 char	 VERTRIEBSZENTRUMNR[7];
		 char    DISPOGEBUEHR[5];
		 char    BTMGEBUEHR[5];
		 char    DOKUGEBUEHR[5];
		 char    LOGISTIKAUFSCHLAG[5];
		 char    LOGISTIKAUFSCHLAGMIN[5];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L ,  11 ,   0 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    5 ,   2 },
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
		 EILBOTENZUSCHLAG   DECIMAL(5,2)    default 0 NOT NULL,\
		 MONATSUMSATZ       DECIMAL(9,2)    default 0 NOT NULL,\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 MALUSFREI_PROZ     DECIMAL(5,2)    default 0 NOT NULL,\
		 VERTRETER_2        SMALLINT        default 0 NOT NULL,\
		 KUNDE_SEIT         INTEGER         default 0 NOT NULL,\
		 URLAUB_VON         INTEGER         default 0 NOT NULL,\
		 URLAUB_BIS         INTEGER         default 0 NOT NULL,\
		 VERSAND_KOSTEN     DECIMAL(5,2)    default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 DISPOGEBUEHR	    DECIMAL(5,2)    default 0 NOT NULL,\
		 BTMGEBUEHR		    DECIMAL(5,2)    default 0 NOT NULL,\
		 DOKUGEBUEHR	    DECIMAL(5,2)    default 0 NOT NULL,\
		 LOGISTIKAUFSCHLAG	DECIMAL(5,2)    default 0 NOT NULL,\
		 LOGISTIKAUFSCHLAGMIN  DECIMAL(5,2)    default 0 NOT NULL ) EXTENT SIZE 259 LOCK MODE ROW;

#define KNDAUSKU_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_KNDAUSKU_1       on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KNDAUSKU_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KNDAUSKU_1      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

