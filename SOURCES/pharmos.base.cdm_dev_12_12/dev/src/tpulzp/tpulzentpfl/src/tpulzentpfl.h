/******************************************************************************/
/*     Hauptmodul: tpulzentpfl                                                */
/*         Source: tpulzentpfl.h                                              */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 01.04.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: typedefs aud structuren                                    */
/*                                                                            */
/******************************************************************************/

/*** TYPES ********************************************************************/

 typedef enum { be_impaired = -1, no_error = 0, read_error, write_error,
	            db_error, log_error, call_error, open_error, send_error,
				is_activ, eof } rterror;
 typedef struct S_DEZAP dezapS;
 typedef struct O_DEZAP dezapO;
 typedef struct O_DEZAPDKSOA dezapdksoaO;
 typedef struct O_DEZAPDKEAN dezapeanO;
 typedef struct O_DEZAPDKWGR dezapdkwgrO;
 typedef struct O_DEZAPDKIWG dezapdkiwgO;
 typedef struct O_DEZAPDKTGR dezapdktgrO;
/* typedef struct O_DEZAPDKBGR dezapdkbgrO; */
/* typedef struct O_DEZAPDKWIR dezapdkwirO; */
 typedef struct O_DEZAPDKLIF dezapdklifO;
 typedef struct O_DEZAPDKATX dezapdkatxO;
 typedef struct O_DEZAPDKCRR dezapdkcrrO;
 typedef struct O_DEZAPDKAFF dezapdkaffO;
 typedef struct O_DEZAPDKSTE dezapdksteO;
/* typedef struct O_DEZAPDKGAL dezapdkgalO;
   typedef struct O_DEZAPDKGAH dezapdkgahO; */
 typedef struct O_DEZAPDKLID dezapdklidO;
 typedef struct O_DEZAPCHECK dezapcheckO;
 typedef struct O_DEZAPDKRIS dezapdkrisO;
 typedef struct O_DEZAPDKEGR dezapdkegrO;
 typedef struct O_DEZAPDKRGR dezapdkrgrO;
 typedef struct O_DEZAPDKZAB dezapdkzabO;
 typedef struct O_DEZAPDKRAB dezapdkrabO;
 typedef struct O_DEZAPDKRAL dezapdkralO;
 typedef struct O_DEZAPDKSER dezapdkserO;
 typedef struct O_DEZAPDKRPG dezapdkrpgO;
 typedef struct O_DEZAPDKAZB dezapdkazbO;
/* typedef struct O_DEZAPDKGFG dezapdkgfgO; */
 typedef struct O_DEZAPDKACO dezapdkacoO;
 typedef struct O_DEZAPDRRAM dezapdrramO;
 typedef struct O_DEZAPDKMRS dezapdkmrsO;
 typedef struct O_DEZAPDKGHZ dezapdkghzO;
 typedef struct O_DEZAPDEPAU dezapdepauO;
 typedef struct O_DEZAPDKKGR dezapdkkgrO;
 typedef struct O_DEZAPDKMVS dezapdkmvsO;
/* typedef struct O_DEZAPDKLLV dezapdkllvO; */
 typedef struct O_DEZAPDKLKR dezapdklkrO;
 typedef struct O_DEZAPDKLKZ dezapdklkzO;
 typedef struct O_DEZAPDKFOK dezapdkfokO;
 typedef struct O_DEZAPDKRBF dezapdkrbfO;
 typedef struct O_DEZAPDKSPS dezapdkspsO;
 typedef struct O_DEZAPDKAUA dezapdkauaO;
 typedef struct O_DEZAPDKPRO dezapdkproO;
 typedef struct O_DEZAPDKAIN dezapdkainO;

 typedef struct { 
	 long	lDate;
	 long	lDateTo;
	 long	lDay;
	 char	spFile[128];
	 char	spDatabase[128];
	 char	Kuerzel[3];
	 short	Prewhole;
 } parameter;

typedef struct {
	const char * const Datenbank;
	const char * const Kuerzel;
	const short	Prewhole;
} country_info;

#ifdef ESQL_C
 exec sql begin declare section;
#endif

 typedef struct ZARTIKEL					dezapzartikelSTR;
 typedef struct ZARTPREIS					dezapzartpreisSTR;
 typedef struct ZARTSEKBEZ					dezapzartsekbezSTR;
 typedef struct CDEPOSITTYPES				dezapcdeposittypesSTR;
 typedef struct HERSTEL						dezapherstelSTR;
 typedef struct ZARTWG						dezapzartwgSTR;
 typedef struct CARTICLECODES				dezapcarticlecodesSTR;
 typedef struct HERSTELLERSALESCONDITION	dezaphsalescondSTR;
 typedef struct ZARTFEB2					dezapzartfeb2STR;
 typedef struct CSAFETYDATASHEET			dezapcsafetydatasheetSTR;
 typedef struct CARTICLEEXT					dezapcarticleextSTR;
 typedef struct ZAUTIDEMSPERRE				dezapzautidemsperreSTR;
/*  typedef struct CGIBATCHENTRY				dezapcgibatchentrySTR; */
 typedef struct ARTVE						dezapartveSTR;
 typedef struct EAN							dezapeanSTR;
 typedef struct ZARTAUSTRIA					dezapzartaustriaSTR;
 typedef struct ZARTCROATIA					dezapzartcroatiaSTR;
 typedef struct ZARTBULGARIA				dezapzartbulgariaSTR;
 typedef struct ZARTSERBIA					dezapzartserbiaSTR;
 typedef struct ZGRPPFLEGE					dezapzgrppflegeSTR;
 typedef struct ZPZNPFLEGE					dezapzpznpflegeSTR;
 typedef struct ZDKWGR						dezapzdkwgrSTR;
 typedef struct ARTKATG						dezapzdkiwgSTR;
 typedef struct ZDKTGR						dezapzdktgrSTR;
 typedef struct CARTICLETEXT 				dezapcarticletextSTR;
 typedef struct ZCHARGENRUECKRUF			dezapzchargenrueckrufSTR;
 typedef struct CDISCOUNT					dezapcdiscountSTR;
 typedef struct ZARTSWITZERLAND				dezapzartswitzerlandSTR;
 typedef struct CARTICLELANG 				dezapcarticlelangSTR;
 typedef struct CARTCOMPACK 				dezapcartcompackSTR;
 typedef struct CCPVALIDITYPERIOD			dezapccpvalidityperiodSTR;
 typedef struct CDISCGRP					dezapcdiscgrpSTR;
 typedef struct HERSTEL_DISPO 				dezapherstel_dispoSTR;
 typedef struct ZARTFRANCE					dezapzartfranceSTR;
 typedef struct ZARTVERK					dezapzartverkSTR;
 typedef struct CPHARMGRP					dezapcpharmgrpSTR;
 typedef struct ZRABGRP						dezapzrabgrpSTR;
 typedef struct ZZAHLBED					dezapzzahlbedSTR;
 typedef struct CDISCLIST					dezapcdisclistSTR;
 typedef struct CSERVICES					dezapcservicesSTR;
 typedef struct CDISCGRPMEM					dezapcdiscgrpmemSTR;
 typedef struct CDISCMODEL					dezapcdiscmodelSTR;
 typedef struct CMONTHDISCSORT				dezapcmonthdiscsortSTR;
 typedef struct CHIGHPAYMTARGETFEE			dezapchighpaymtargetfeeSTR;
 typedef struct CCUSTOMERGROUP				dezapccustomergroupSTR;
 typedef struct CORDERTYPE					dezapcordertypeSTR;
 typedef struct CMONTHVIRTSORT				dezapcmonthvirtsortSTR;
 typedef struct CSTORAGECRITERIA			dezapcstoragecriteriaSTR;
 typedef struct CINTRASTATCOUNTRY			dezapcintrastatcountrySTR;
 typedef struct CFORMTYPES					dezapcformtypesSTR;
 typedef struct CDISCFORM					dezapcdiscformSTR;
 typedef struct CSHIPPER					dezapcshipperSTR;
 typedef struct CPROMOTIONS					dezapcpromotionsSTR;
 typedef struct CREGISTERS					dezapcregistersSTR;
 typedef struct CBASELISTARTICLES			dezapcbaselistarticlesSTR;

/* typedef struct ZDKBTM					dezapzdkbgrSTR; */
/* typedef struct ZDKWIR					dezapzdkwirSTR; */
/* typedef struct CGALOART					dezapcgaloartSTR;
   typedef struct CGALONAM 					dezapcgalonamSTR;
   typedef struct CGALOCOM	 				dezapcgalocomSTR; */
/* typedef struct CCUSTSERVICES				dezapccustservicesSTR; */

typedef struct {
	short	customergrpflag;
	short	index_dkkgr;
} dezapccustomergrpflagSTR;

typedef struct {
	short   ordertypeflag;
	short	index_dkaua;
} dezapcordertypeflagSTR;

#ifdef ESQL_C
 exec sql end declare section;
#endif
