/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEAKZ_AKZFIL               2
 #define L_DEAKZ_AKZPZN               7
 #define L_DEAKZ_AKZBEST              7
 #define L_DEAKZ_AKZBUE               3
 #define L_DEAKZ_AKZMINM              3
 #define L_DEAKZ_AKZLGNR              1
 #define L_DEAKZ_AKZLGFNR             8
 #define L_DEAKZ_AKZSTAT              2
 #define L_DEAKZ_AKZET1               16
 #define L_DEAKZ_AKZET2               16
 #define L_DEAKZ_AKZET3               16
 #define L_DEAKZ_AKZET4               16
 #define L_DEAKZ_AKZAANR              7
 #define L_DEAKZ_AKZA3                1
 #define L_DEAKZ_AKZORPA              1
 #define L_DEAKZ_AKZAAA               1
 #define L_DEAKZ_AKZDAA               1
 #define L_DEAKZ_AKZTFG               1
 #define L_DEAKZ_AKZFEUKL             2
 #define L_DEAKZ_AKZNEKZ              1
 #define L_DEAKZ_AKZGEGU              1
 #define L_DEAKZ_AKZEKS               1
 #define L_DEAKZ_AKZZYTO              1
 #define L_DEAKZ_AKZBSSG              1
 #define L_DEAKZ_AKZVRIS              1
 #define L_DEAKZ_AKZMIDAS             1
 #define L_DEAKZ_AKZSHSTAT            1
 #define L_DEAKZ_AKZCHARGE            1
 #define L_DEAKZ_AKZCBL               1
 #define L_DEAKZ_AKZAUSL              1
 #define L_DEAKZ_AKZRESP              1
 #define L_DEAKZ_AKZFILL1             6
 #define L_DEAKZ_AKZVB                1
 #define L_DEAKZ_AKZZUZA              1
 #define L_DEAKZ_AKZKRAB              2
 #define L_DEAKZ_AKZNRTI              3
 #define L_DEAKZ_AKZPRISO             1
 #define L_DEAKZ_AKZSPERR             1
 #define L_DEAKZ_AKZLOESCH            1
 #define L_DEAKZ_AKZVERF              4
 #define L_DEAKZ_AKZMAM               3
 #define L_DEAKZ_AKZNRHR              1
 #define L_DEAKZ_AKZKEYTXT            2
 #define L_DEAKZ_AKZNALI              1

 #define L_DEAKZ_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEAKZ_ANZ ( sizeof(DEAKZ_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEAKZ sizeof(struct DEAKZ)


 #define DEAKZ_H

 #define DEAKZ_LISTE \
 			DEAKZ.AKZFIL, \
 			DEAKZ.AKZPZN, \
 			DEAKZ.AKZBEST, \
 			DEAKZ.AKZBUE, \
 			DEAKZ.AKZMINM, \
 			DEAKZ.AKZLGNR, \
 			DEAKZ.AKZLGFNR, \
 			DEAKZ.AKZSTAT, \
 			DEAKZ.AKZET1, \
 			DEAKZ.AKZET2, \
 			DEAKZ.AKZET3, \
 			DEAKZ.AKZET4, \
 			DEAKZ.AKZAANR, \
			DEAKZ.AKZA3, \
			DEAKZ.AKZORPA, \
			DEAKZ.AKZAAA, \
			DEAKZ.AKZDAA, \
			DEAKZ.AKZTFG, \
			DEAKZ.AKZFEUKL, \
			DEAKZ.AKZNEKZ, \
			DEAKZ.AKZGEGU, \
			DEAKZ.AKZEKS, \
			DEAKZ.AKZZYTO, \
			DEAKZ.AKZBSSG, \
			DEAKZ.AKZVRIS, \
			DEAKZ.AKZMIDAS, \
			DEAKZ.AKTSHSTAT, \
			DEAKZ.AKZCHARGE, \
			DEAKZ.AKZCBL, \
			DEAKZ.AKZAUSL, \
			DEAKZ.AKZRESP, \
			DEAKZ.AKZFILL1, \
 			DEAKZ.AKZVB, \
 			DEAKZ.AKZZUZA, \
 			DEAKZ.AKZKRAB, \
 			DEAKZ.AKZNRTI, \
 			DEAKZ.AKZPRISO, \
 			DEAKZ.AKZSPERR, \
 			DEAKZ.AKZLOESCH, \
 			DEAKZ.AKZVERF, \
 			DEAKZ.AKZMAM, \
 			DEAKZ.AKZNRHR, \
 			DEAKZ.AKZKEYTXT, \
 			DEAKZ.AKZNALI
 #define DEAKZ_PLISTE \
 			"DEAKZ.AKZFIL," \
 			"DEAKZ.AKZPZN," \
 			"DEAKZ.AKZBEST," \
 			"DEAKZ.AKZBUE," \
 			"DEAKZ.AKZMINM," \
 			"DEAKZ.AKZLGNR," \
 			"DEAKZ.AKZLGFNR," \
 			"DEAKZ.AKZSTAT," \
 			"DEAKZ.AKZET1," \
 			"DEAKZ.AKZET2," \
 			"DEAKZ.AKZET3," \
 			"DEAKZ.AKZET4," \
 			"DEAKZ.AKZAANR," \
			"DEAKZ.AKZA3," \
			"DEAKZ.AKZORPA," \
			"DEAKZ.AKZAAA," \
			"DEAKZ.AKZDAA," \
			"DEAKZ.AKZTFG," \
			"DEAKZ.AKZFEUKL," \
			"DEAKZ.AKZNEKZ," \
			"DEAKZ.AKZGEGU," \
			"DEAKZ.AKZEKS," \
			"DEAKZ.AKZZYTO," \
			"DEAKZ.AKZBSSG," \
			"DEAKZ.AKZVRIS," \
			"DEAKZ.AKZMIDAS," \
			"DEAKZ.AKZSHSTAT," \
			"DEAKZ.AKZCHARGE," \
			"DEAKZ.AKZCBL," \
			"DEAKZ.AKZAUSL," \
			"DEAKZ.AKZRESP," \
			"DEAKZ.AKZFILL1," \
 			"DEAKZ.AKZVB," \
 			"DEAKZ.AKZZUZA," \
 			"DEAKZ.AKZKRAB," \
 			"DEAKZ.AKZNRTI," \
 			"DEAKZ.AKZPRISO," \
 			"DEAKZ.AKZSPERR," \
 			"DEAKZ.AKZLOESCH," \
 			"DEAKZ.AKZVERF," \
 			"DEAKZ.AKZMAM," \
 			"DEAKZ.AKZNRHR," \
 			"DEAKZ.AKZKEYTXT," \
 			"DEAKZ.AKZNALI " 

 #define DEAKZ_PELISTE \
 			"AKZFIL," \
 			"AKZPZN," \
 			"AKZBEST," \
 			"AKZBUE," \
 			"AKZMINM," \
 			"AKZLGNR," \
 			"AKZLGFNR," \
 			"AKZSTAT," \
 			"AKZET1," \
 			"AKZET2," \
 			"AKZET3," \
 			"AKZET4," \
 			"AKZAANR," \
			"AKZA3," \
			"AKZORPA," \
			"AKZAAA," \
			"AKZDAA," \
			"AKZTFG," \
			"AKZFEUKL," \
			"AKZNEKZ," \
			"AKZGEGU," \
			"AKZEKS," \
			"AKZZYTO," \
			"AKZBSSG," \
			"AKZVRIS," \
			"AKZMIDAS," \
			"AKZSHSTAT," \
			"AKZCHARGE," \
			"AKZCBL," \
			"AKZAUSL," \
			"AKZRESP," \
			"AKZFILL1," \
 			"AKZVB," \
 			"AKZZUZA," \
 			"AKZKRAB," \
 			"AKZNRTI," \
 			"AKZPRISO," \
 			"AKZSPERR," \
 			"AKZLOESCH," \
 			"AKZVERF," \
 			"AKZMAM," \
 			"AKZNRHR," \
 			"AKZKEYTXT," \
 			"AKZNALI " 

 #define DEAKZ_UPDLISTE \
 			"AKZFIL=?," \
 			"AKZPZN=?," \
 			"AKZBEST=?," \
 			"AKZBUE=?," \
 			"AKZMINM=?," \
 			"AKZLGNR=?," \
 			"AKZLGFNR=?," \
 			"AKZSTAT=?," \
 			"AKZET1=?," \
 			"AKZET2=?," \
 			"AKZET3=?," \
 			"AKZET4=?," \
 			"AKZAANR=?," \
			"AKZA3=?," \
			"AKZORPA=?," \
			"AKZAAA=?," \
			"AKZDAA=?," \
			"AKZTFG=?," \
			"AKZFEUKL=?," \
			"AKZNEKZ=?," \
			"AKZGEGU=?," \
			"AKZEKS=?," \
			"AKZZYTO=?," \
			"AKZBSSG=?," \
			"AKZVRIS=?," \
			"AKZMIDAS=?," \
			"AKZSHSTAT=?," \
			"AKZCHARGE=?," \
			"AKZCBL=?," \
			"AKZAUSL=?," \
			"AKZRESP=?," \
 			"AKZFILL1=?," \
 			"AKZVB=?," \
 			"AKZZUZA=?," \
 			"AKZKRAB=?," \
 			"AKZNRTI=?," \
 			"AKZPRISO=?," \
 			"AKZSPERR=?," \
 			"AKZLOESCH=?," \
 			"AKZVERF=?," \
 			"AKZMAM=?," \
 			"AKZNRHR=?," \
 			"AKZKEYTXT=?," \
 			"AKZNALI=? " 

 #define DEAKZAKZFIL                        0
 #define DEAKZAKZPZN                        1
 #define DEAKZAKZBEST                       2
 #define DEAKZAKZBUE                        3
 #define DEAKZAKZMINM                       4
 #define DEAKZAKZLGNR                       5
 #define DEAKZAKZLGFNR                      6
 #define DEAKZAKZSTAT                       7
 #define DEAKZAKZET1                        8
 #define DEAKZAKZET2                        9
 #define DEAKZAKZET3                        10
 #define DEAKZAKZET4                        11
 #define DEAKZAKZAANR                       12
 #define DEAKZAKZA3                         13
 #define DEAKZAKZORPA                       14
 #define DEAKZAKZAAA                        15
 #define DEAKZAKZDAA                        16
 #define DEAKZAKZTFG                        17
 #define DEAKZAKZFEUKL                      18
 #define DEAKZAKZNEKZ                       19
 #define DEAKZAKZGEGU                       20
 #define DEAKZAKZEKS                        21
 #define DEAKZAKZZYTO                       22
 #define DEAKZAKZBSSG                       23
 #define DEAKZAKZVRIS                       24
 #define DEAKZAKZMIDAS                      25
 #define DEAKZAKZSHSTAT                     26
 #define DEAKZAKZCHARGE                     27
 #define DEAKZAKZCBL                        28
 #define DEAKZAKZAUSL                       29
 #define DEAKZAKRESP                        30
 #define DEAKZAKZFILL1                      31
 #define DEAKZAKZVB                         32
 #define DEAKZAKZZUZA                       33
 #define DEAKZAKZKRAB                       34
 #define DEAKZAKZNRTI                       35
 #define DEAKZAKZPRISO                      36
 #define DEAKZAKZSPERR                      37
 #define DEAKZAKZLOESCH                     38
 #define DEAKZAKZVERF                       39
 #define DEAKZAKZMAM                        40
 #define DEAKZAKZNRHR                       41
 #define DEAKZAKZKEYTXT                     42
 #define DEAKZAKZNALI                       43

 #define DEAKZ_ZEIGER(xxx) \
 			:xxx->AKZFIL,\
 			:xxx->AKZPZN,\
 			:xxx->AKZBEST,\
 			:xxx->AKZBUE,\
 			:xxx->AKZMINM,\
 			:xxx->AKZLGNR,\
 			:xxx->AKZLGFNR,\
 			:xxx->AKZSTAT,\
 			:xxx->AKZET1,\
 			:xxx->AKZET2,\
 			:xxx->AKZET3,\
 			:xxx->AKZET4,\
 			:xxx->AKZAANR,\
			:xxx->AKZA3,\
			:xxx->AKZORPA,\
			:xxx->AKZAAA,\
			:xxx->AKZDAA,\
			:xxx->AKZTFG,\
			:xxx->AKZFEUKL,\
			:xxx->AKZNEKZ,\
			:xxx->AKZGEGU,\
			:xxx->AKZEKS,\
			:xxx->AKZZYTO,\
			:xxx->AKZBSSG,\
			:xxx->AKZVRIS,\
			:xxx->AKZMIDAS,\
			:xxx->AKZSHSTAT,\
			:xxx->AKZCHARGE,\
			:xxx->AKZCBL,\
			:xxx->AKZAUSL,\
			:xxx->AKZRESP,\
 			:xxx->AKZFILL1,\
 			:xxx->AKZVB,\
 			:xxx->AKZZUZA,\
 			:xxx->AKZKRAB,\
 			:xxx->AKZNRTI,\
 			:xxx->AKZPRISO,\
 			:xxx->AKZSPERR,\
 			:xxx->AKZLOESCH,\
 			:xxx->AKZVERF,\
 			:xxx->AKZMAM,\
 			:xxx->AKZNRHR,\
 			:xxx->AKZKEYTXT,\
 			:xxx->AKZNALI

 #define DEAKZ_UPDATE(xxx) \
 			AKZFIL = :xxx->AKZFIL,\
 			AKZPZN = :xxx->AKZPZN,\
 			AKZBEST = :xxx->AKZBEST,\
 			AKZBUE = :xxx->AKZBUE,\
 			AKZMINM = :xxx->AKZMINM,\
 			AKZLGNR = :xxx->AKZLGNR,\
 			AKZLGFNR = :xxx->AKZLGFNR,\
 			AKZSTAT = :xxx->AKZSTAT,\
 			AKZET1 = :xxx->AKZET1,\
 			AKZET2 = :xxx->AKZET2,\
 			AKZET3 = :xxx->AKZET3,\
 			AKZET4 = :xxx->AKZET4,\
 			AKZAANR = :xxx->AKZAANR,\
			AKZA3 = :xxx->AKZA3,\
			AKZORPA = :xxx->AKZORPA,\
			AKZAAA = :xxx->AKZAAA,\
			AKZDAA = :xxx->AKZDAA,\
			AKZTFG = :xxx->AKZTFG,\
			AKZFEUKL = :xxx->AKZFEUKL,\
			AKZNEKZ = :xxx->AKZNEKZ,\
			AKZGEGU = :xxx->AKZGEGU,\
			AKZEKS = :xxx->AKZEKS,\
			AKZZYTO = :xxx->AKZZYTO,\
			AKZBSSG = :xxx->AKZBSSG,\
			AKZVRIS = :xxx->AKZVRIS,\
			AKZMIDAS = :xxx->AKZMIDAS,\
			AKZSHSTAT = :xxx->AKZSHSTAT,\
			AKZCHARGE = :xxx->AKZCHARGE,\
			AKZCBL = :xxx->AKZCBL,\
			AKZAUSL = :xxx->AKZAUSL,\
			AKZRESP = :xxx->AKZRESP,\
 			AKZFILL1 = :xxx->AKZFILL1,\
 			AKZVB = :xxx->AKZVB,\
 			AKZZUZA = :xxx->AKZZUZA,\
 			AKZKRAB = :xxx->AKZKRAB,\
 			AKZNRTI = :xxx->AKZNRTI,\
 			AKZPRISO = :xxx->AKZPRISO,\
 			AKZSPERR = :xxx->AKZSPERR,\
 			AKZLOESCH = :xxx->AKZLOESCH,\
 			AKZVERF = :xxx->AKZVERF,\
 			AKZMAM = :xxx->AKZMAM,\
 			AKZNRHR = :xxx->AKZNRHR,\
 			AKZKEYTXT = :xxx->AKZKEYTXT,\
 			AKZNALI = :xxx->AKZNALI

 #define LS_DEAKZ_AKZFIL               3
 #define LS_DEAKZ_AKZPZN               8
 #define LS_DEAKZ_AKZBEST              8
 #define LS_DEAKZ_AKZBUE               4
 #define LS_DEAKZ_AKZMINM              4
 #define LS_DEAKZ_AKZLGNR              2
 #define LS_DEAKZ_AKZLGFNR             9
 #define LS_DEAKZ_AKZSTAT              3
 #define LS_DEAKZ_AKZET1               17
 #define LS_DEAKZ_AKZET2               17
 #define LS_DEAKZ_AKZET3               17
 #define LS_DEAKZ_AKZET4               17
 #define LS_DEAKZ_AKZAANR              8
 #define LS_DEAKZ_AKZA3                2
 #define LS_DEAKZ_AKZORPA              2
 #define LS_DEAKZ_AKZAAA               2
 #define LS_DEAKZ_AKZDAA               2
 #define LS_DEAKZ_AKZTFG               2
 #define LS_DEAKZ_AKZFEUKL             3
 #define LS_DEAKZ_AKZNEKZ              2
 #define LS_DEAKZ_AKZGEGU              2
 #define LS_DEAKZ_AKZEKS               2
 #define LS_DEAKZ_AKZZYTO              2
 #define LS_DEAKZ_AKZBSSG              2
 #define LS_DEAKZ_AKZVRIS              2
 #define LS_DEAKZ_AKZMIDAS             2
 #define LS_DEAKZ_AKZSHSTAT            2
 #define LS_DEAKZ_AKZCHARGE            2
 #define LS_DEAKZ_AKZCBL               2
 #define LS_DEAKZ_AKZAUSL              2
 #define LS_DEAKZ_AKZRESP              2
 #define LS_DEAKZ_AKZFILL1             7
 #define LS_DEAKZ_AKZVB                2
 #define LS_DEAKZ_AKZZUZA              2
 #define LS_DEAKZ_AKZKRAB              3
 #define LS_DEAKZ_AKZNRTI              4
 #define LS_DEAKZ_AKZPRISO             2
 #define LS_DEAKZ_AKZSPERR             2
 #define LS_DEAKZ_AKZLOESCH            2
 #define LS_DEAKZ_AKZVERF              5
 #define LS_DEAKZ_AKZMAM               4
 #define LS_DEAKZ_AKZNRHR              2
 #define LS_DEAKZ_AKZKEYTXT            3
 #define LS_DEAKZ_AKZNALI              2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DEAKZ {
		 char    AKZFIL[2 + 1];
		 char    AKZPZN[7 + 1];
		 char    AKZBEST[7 + 1];
		 char    AKZBUE[3 + 1];
		 char    AKZMINM[3 + 1];
		 char    AKZLGNR[1 + 1];
		 char    AKZLGFNR[8 + 1];
		 char    AKZSTAT[2 + 1];
		 char    AKZET1[16 + 1];
		 char    AKZET2[16 + 1];
		 char    AKZET3[16 + 1];
		 char    AKZET4[16 + 1];
		 char    AKZAANR[7 + 1];
		 char    AKZA3[1 + 1];
		 char    AKZORPA[1 + 1];
		 char    AKZAAA[1 + 1];
		 char    AKZDAA[1 + 1];
		 char    AKZTFG[1 + 1];
		 char    AKZFEUKL[2 + 1];
		 char    AKZNEKZ[1 + 1];
		 char    AKZGEGU[1 + 1];
		 char    AKZEKS[1 + 1];
		 char    AKZZYTO[1 + 1];
		 char    AKZBSSG[1 + 1];
		 char    AKZVRIS[1 + 1];
		 char    AKZMIDAS[1 + 1];
		 char    AKZSHSTAT[1 + 1];
		 char    AKZCHARGE[1 + 1];
		 char    AKZCBL[1 + 1];
		 char    AKZAUSL[1 + 1];
		 char    AKZRESP[1 + 1];
		 char    AKZFILL1[6 + 1];
		 char    AKZVB[1 + 1];
		 char    AKZZUZA[1 + 1];
		 char    AKZKRAB[2 + 1];
		 char    AKZNRTI[3 + 1];
		 char    AKZPRISO[1 + 1];
		 char    AKZSPERR[1 + 1];
		 char    AKZLOESCH[1 + 1];
		 char    AKZVERF[4 + 1];
		 char    AKZMAM[3 + 1];
		 char    AKZNRHR[1 + 1];
		 char    AKZKEYTXT[2 + 1];
		 char    AKZNALI[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DEAKZ {
		 char    AKZFIL[2 + 1];
		 char    AKZPZN[7 + 1];
		 char    AKZBEST[7 + 1];
		 char    AKZBUE[3 + 1];
		 char    AKZMINM[3 + 1];
		 char    AKZLGNR;
		 char    AKZLGFNR[8 + 1];
		 char    AKZSTAT[2 + 1];
		 char    AKZET1[16 + 1];
		 char    AKZET2[16 + 1];
		 char    AKZET3[16 + 1];
		 char    AKZET4[16 + 1];
		 char    AKZAANR[7 + 1];
		 char    AKZA3;
		 char    AKZORPA;
		 char    AKZAAA;
		 char    AKZDAA;
		 char    AKZTFG;
		 char    AKZFEUKL[2 + 1];
		 char    AKZNEKZ;
		 char    AKZGEGU;
		 char    AKZEKS;
		 char    AKZZYTO;
		 char    AKZBSSG;
		 char    AKZVRIS;
		 char    AKZMIDAS;
		 char    AKZSHSTAT;
		 char    AKZCHARGE;
		 char    AKZCBL;
		 char    AKZAUSL;
		 char    AKZRESP;
		 char    AKZFILL1[6 + 1];
		 char    AKZVB;
		 char    AKZZUZA;
		 char    AKZKRAB[2 + 1];
		 char    AKZNRTI[3 + 1];
		 char    AKZPRISO;
		 char    AKZSPERR;
		 char    AKZLOESCH;
		 char    AKZVERF[4 + 1];
		 char    AKZMAM[3 + 1];
		 char    AKZNRHR;
		 char    AKZKEYTXT[2 + 1];
		 char    AKZNALI;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DEAKZ {
		 short  AKZFIL;
		 short  AKZPZN;
		 short  AKZBEST;
		 short  AKZBUE;
		 short  AKZMINM;
		 short  AKZLGNR;
		 short  AKZLGFNR;
		 short  AKZSTAT;
		 short  AKZET1;
		 short  AKZET2;
		 short  AKZET3;
		 short  AKZET4;
		 short  AKZAANR;
		 short  AKZA3;
		 short  AKZORPA;
		 short  AKZAAA;
		 short  AKZDAA;
		 short  AKZTFG;
		 short  AKZFEUKL;
		 short  AKZNEKZ;
		 short  AKZGEGU;
		 short  AKZEKS;
		 short  AKZZYTO;
		 short  AKZBSSG;
		 short  AKZVRIS;
		 short  AKZMIDAS;
		 short  AKZSHSTAT;
		 short  AKZCHARGE;
		 short  AKZCBL;
		 short  AKZAUSL;
		 short  AKZRESP;
		 short  AKZFILL1;
		 short  AKZVB;
		 short  AKZZUZA;
		 short  AKZKRAB;
		 short  AKZNRTI;
		 short  AKZPRISO;
		 short  AKZSPERR;
		 short  AKZLOESCH;
		 short  AKZVERF;
		 short  AKZMAM;
		 short  AKZNRHR;
		 short  AKZKEYTXT;
		 short  AKZNALI;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DEAKZ {
		 char    AKZFIL[2 + 1];
		 char    AKZPZN[7 + 1];
		 char    AKZBEST[7 + 1];
		 char    AKZBUE[3 + 1];
		 char    AKZMINM[3 + 1];
		 char    AKZLGNR[1 + 1];
		 char    AKZLGFNR[8 + 1];
		 char    AKZSTAT[2 + 1];
		 char    AKZET1[16 + 1];
		 char    AKZET2[16 + 1];
		 char    AKZET3[16 + 1];
		 char    AKZET4[16 + 1];
		 char    AKZAANR[7 + 1];
		 char    AKZA3[1 + 1];
		 char    AKZORPA[1 + 1];
		 char    AKZAAA[1 + 1];
		 char    AKZDAA[1 + 1];
		 char    AKZTFG[1 + 1];
		 char    AKZFEUKL[2 + 1];
		 char    AKZNEKZ[1 + 1];
		 char    AKZGEGU[1 + 1];
		 char    AKZEKS[1 + 1];
		 char    AKZZYTO[1 + 1];
		 char    AKZBSSG[1 + 1];
		 char    AKZVRIS[1 + 1];
		 char    AKZMIDAS[1 + 1];
		 char    AKZSHSTAT[1 + 1];
		 char    AKZCHARGE[1 + 1];
		 char    AKZCBL[1 + 1];
		 char    AKZAUSL[1 + 1];
		 char    AKZRESP[1 + 1];
		 char    AKZFILL1[6 + 1];
		 char    AKZVB[1 + 1];
		 char    AKZZUZA[1 + 1];
		 char    AKZKRAB[2 + 1];
		 char    AKZNRTI[3 + 1];
		 char    AKZPRISO[1 + 1];
		 char    AKZSPERR[1 + 1];
		 char    AKZLOESCH[1 + 1];
		 char    AKZVERF[4 + 1];
		 char    AKZMAM[3 + 1];
		 char    AKZNRHR[1 + 1];
		 char    AKZKEYTXT[2 + 1];
		 char    AKZNALI[1 + 1];
       };

 struct O_DEAKZ {
		 char    AKZFIL[2];
		 char    AKZPZN[7];
		 char    AKZBEST[7];
		 char    AKZBUE[3];
		 char    AKZMINM[3];
		 char    AKZLGNR[1];
		 char    AKZLGFNR[8];
		 char    AKZSTAT[2];
		 char    AKZET1[16];
		 char    AKZET2[16];
		 char    AKZET3[16];
		 char    AKZET4[16];
		 char    AKZAANR[7];
		 char    AKZA3[1];
		 char    AKZORPA[1];
		 char    AKZAAA[1];
		 char    AKZDAA[1];
		 char    AKZTFG[1];
		 char    AKZFEUKL[2];
		 char    AKZNEKZ[1];
		 char    AKZGEGU[1];
		 char    AKZEKS[1];
		 char    AKZZYTO[1];
		 char    AKZBSSG[1];
		 char    AKZVRIS[1];
		 char    AKZMIDAS[1];
		 char    AKZSHSTAT[1];
		 char    AKZCHARGE[1];
		 char    AKZCBL[1];
		 char    AKZAUSL[1];
		 char    AKZRESP[1];
		 char    AKZFILL1[6];
		 char    AKZVB[1];
		 char    AKZZUZA[1];
		 char    AKZKRAB[2];
		 char    AKZNRTI[3];
		 char    AKZPRISO[1];
		 char    AKZSPERR[1];
		 char    AKZLOESCH[1];
		 char    AKZVERF[4];
		 char    AKZMAM[3];
		 char    AKZNRHR[1];
		 char    AKZKEYTXT[2];
		 char    AKZNALI[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEAKZ_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEAKZ_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEAKZ
 {
  public:

  DEAKZ s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEAKZ_BES, DEAKZ_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEAKZ_BES, DEAKZ_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEAKZ_BES, DEAKZ_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEAKZ()
  {
   ::buf_default((void *)&s, DEAKZ_BES, DEAKZ_ANZ);
  }
 };
#endif

#define DEAKZ_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 AKZFIL             CHAR(2)         default " " NOT NULL,\
		 AKZPZN             CHAR(7)         default " " NOT NULL,\
		 AKZBEST            CHAR(7)         default " " NOT NULL,\
		 AKZBUE             CHAR(3)         default " " NOT NULL,\
		 AKZMINM            CHAR(3)         default " " NOT NULL,\
		 AKZLGNR            CHAR(1)         default " " NOT NULL,\
		 AKZLGFNR           CHAR(8)         default " " NOT NULL,\
		 AKZSTAT            CHAR(2)         default " " NOT NULL,\
		 AKZET1             CHAR(16)        default " " NOT NULL,\
		 AKZET2             CHAR(16)        default " " NOT NULL,\
		 AKZET3             CHAR(16)        default " " NOT NULL,\
		 AKZET4             CHAR(16)        default " " NOT NULL,\
		 AKZAANR            CHAR(7)         default " " NOT NULL,\
		 AKZA3              CHAR(1)         default " " NOT NULL,\
		 AKZORPA            CHAR(1)         default " " NOT NULL,\
		 AKZAAA             CHAR(1)         default " " NOT NULL,\
		 AKZDAA             CHAR(1)         default " " NOT NULL,\
		 AKZTFG             CHAR(1)         default " " NOT NULL,\
		 AKZFEUKL           CHAR(2)         default " " NOT NULL,\
		 AKZNEKZ            CHAR(1)         default " " NOT NULL,\
		 AKZGEGU            CHAR(1)         default " " NOT NULL,\
		 AKZEKS             CHAR(1)         default " " NOT NULL,\
		 AKZZYTO            CHAR(1)         default " " NOT NULL,\
		 AKZBSSG            CHAR(1)         default " " NOT NULL,\
		 AKZVRIS            CHAR(1)         default " " NOT NULL,\
		 AKZMIDAS           CHAR(1)         default " " NOT NULL,\
		 AKZSHSTAT          CHAR(1)         default " " NOT NULL,\
		 AKZCHARGE          CHAR(1)         default " " NOT NULL,\
		 AKZCBL             CHAR(1)         default " " NOT NULL,\
		 AKZAUSL            CHAR(1)         default " " NOT NULL,\
		 AKZRESP            CHAR(1)         default " " NOT NULL,\
		 AKZFILL1           CHAR(8)         default " " NOT NULL,\
		 AKZVB              CHAR(1)         default " " NOT NULL,\
		 AKZZUZA            CHAR(1)         default " " NOT NULL,\
		 AKZKRAB            CHAR(2)         default " " NOT NULL,\
		 AKZNRTI            CHAR(3)         default " " NOT NULL,\
		 AKZPRISO           CHAR(1)         default " " NOT NULL,\
		 AKZSPERR           CHAR(1)         default " " NOT NULL,\
		 AKZLOESCH          CHAR(1)         default " " NOT NULL,\
		 AKZVERF            CHAR(4)         default " " NOT NULL,\
		 AKZMAM             CHAR(3)         default " " NOT NULL,\
		 AKZNRHR            CHAR(1)         default " " NOT NULL,\
		 AKZKEYTXT          CHAR(2)         default " " NOT NULL,\
		 AKZNALI            CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 9 LOCK MODE ROW;

#define DEAKZ_CREATE_INDEX(yyy,xxx) \

#define DEAKZ_DELETE_INDEX(xxx) \

