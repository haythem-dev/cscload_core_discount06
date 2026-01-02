#ifndef __PP_AUFTRAGINFO_H_
#define __PP_AUFTRAGINFO_H_

/******************************************************************************/
/* d:\prj\aa\unix\aapserv\AuftragInfo *****************************************/
/******************************************************************************/

/* Length-Define of AUFPOSRAB *************************************************/

  #define L_AUFPOSRAB_DATUM 11
  #define L_AUFPOSRAB_KDAUFTRAGNR 11
  #define L_AUFPOSRAB_POSNR 11
  #define L_AUFPOSRAB_DISCOUNTTYPE 6
  #define L_AUFPOSRAB_DISCOUNTVALUEPCT 5
  #define N_AUFPOSRAB_DISCOUNTVALUEPCT 2
  #define L_AUFPOSRAB_PHARMACYGROUPID 3
  #define L_AUFPOSRAB_PAYMENTTARGETNO 6
  #define L_AUFPOSRAB_DISCOUNTVALPCTMAN 5
  #define N_AUFPOSRAB_DISCOUNTVALPCTMAN 2

/* Length-Define of AUFTRAGWERTE **********************************************/

  #define L_AUFTRAGWERTE_KDAUFTRAGNR 11
  #define L_AUFTRAGWERTE_ORDVALFTAXFSDISC 11
  #define N_AUFTRAGWERTE_ORDVALFTAXFSDISC 2
  #define L_AUFTRAGWERTE_ORDVALLTAXFSDISC 11
  #define N_AUFTRAGWERTE_ORDVALLTAXFSDISC 2
  #define L_AUFTRAGWERTE_ORDVALFTAXHFDISC 11
  #define N_AUFTRAGWERTE_ORDVALFTAXHFDISC 2
  #define L_AUFTRAGWERTE_ORDVALLTAXHFDISC 11
  #define N_AUFTRAGWERTE_ORDVALLTAXHFDISC 2
  #define L_AUFTRAGWERTE_ORDVALFTAXRSDISC 11
  #define N_AUFTRAGWERTE_ORDVALFTAXRSDISC 2
  #define L_AUFTRAGWERTE_ORDVALLTAXRSDISC 11
  #define N_AUFTRAGWERTE_ORDVALLTAXRSDISC 2

/* Length-Define of AUFTRAGWERTEALT *******************************************/

  #define L_AUFTRAGWERTEALT_DATUM 11
  #define L_AUFTRAGWERTEALT_KDAUFTRAGNR 11
  #define L_AUFTRAGWERTEALT_ORDVALFTAXFSDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALFTAXFSDISC 2
  #define L_AUFTRAGWERTEALT_ORDVALLTAXFSDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALLTAXFSDISC 2
  #define L_AUFTRAGWERTEALT_ORDVALFTAXHFDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALFTAXHFDISC 2
  #define L_AUFTRAGWERTEALT_ORDVALLTAXHFDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALLTAXHFDISC 2
  #define L_AUFTRAGWERTEALT_ORDVALFTAXRSDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALFTAXRSDISC 2
  #define L_AUFTRAGWERTEALT_ORDVALLTAXRSDISC 11
  #define N_AUFTRAGWERTEALT_ORDVALLTAXRSDISC 2

/* Length-Define of COLLECTIVEORDERS ******************************************/

  #define L_COLLECTIVEORDERS_KDAUFTRAGNR 11
  #define L_COLLECTIVEORDERS_KDAUFTRAGSTAT 16
  #define L_COLLECTIVEORDERS_DATUM 11
  #define L_COLLECTIVEORDERS_NAMEAPO 40
  #define L_COLLECTIVEORDERS_ORT 30
  #define L_COLLECTIVEORDERS_KDGRUPPE 2
  #define L_COLLECTIVEORDERS_ANZPOS 11
  #define L_COLLECTIVEORDERS_KZKDKLASSE 3
  #define L_COLLECTIVEORDERS_KUNDENNR 11

/* Length-Define of POSCHANGE *************************************************/

  #define L_POSCHANGE_KDAUFTRAGNR 11
  #define L_POSCHANGE_POSNR 11
  #define L_POSCHANGE_MENGEBESTELLT 11
  #define L_POSCHANGE_MENGEBESTAETIGT 11
  #define L_POSCHANGE_MENGE_ALT 11
  #define L_POSCHANGE_SWCHECKED 1
  #define L_POSCHANGE_NAMEAPO 40
  #define L_POSCHANGE_VERTRIEBSZENTRUMNR 6
  #define L_POSCHANGE_INVOICENUMBER 15
  #define L_POSCHANGE_ARTIKEL_NAME 30
  #define L_POSCHANGE_ARTIKEL_LANGNAME 50

/* Length-Define of POSCHANGEHIST *********************************************/

  #define L_POSCHANGEHIST_DATUM 11
  #define L_POSCHANGEHIST_KDAUFTRAGNR 11
  #define L_POSCHANGEHIST_POSNR 11
  #define L_POSCHANGEHIST_MENGEBESTELLT 11
  #define L_POSCHANGEHIST_MENGEBESTAETIGT 11
  #define L_POSCHANGEHIST_MENGE_ALT 11
  #define L_POSCHANGEHIST_SWCHECKED 1
  #define L_POSCHANGEHIST_NAMEAPO 40
  #define L_POSCHANGEHIST_VERTRIEBSZENTRUMNR 6
  #define L_POSCHANGEHIST_INVOICENUMBER 15
  #define L_POSCHANGEHIST_ARTIKEL_NAME 30
  #define L_POSCHANGEHIST_ARTIKEL_LANGNAME 50

/* Length-Define of PROLINK ***************************************************/

  #define L_PROLINK_DATUM 11
  #define L_PROLINK_KDAUFTRAGNR 11
  #define L_PROLINK_INVOICENUMBERPRO 15
  #define L_PROLINK_INVOICENUMBER 15
  #define L_PROLINK_DATEPROFORMA 11
  #define L_PROLINK_KDAUFTRAGNRPRO 11

/* Length-Define of PROLINKACT ************************************************/

  #define L_PROLINKACT_KDAUFTRAGNR 11
  #define L_PROLINKACT_INVOICENUMBERPRO 15
  #define L_PROLINKACT_INVOICENUMBER 15
  #define L_PROLINKACT_DATEPROFORMA 11
  #define L_PROLINKACT_KDAUFTRAGNRPRO 11

/* SqlDefine of AUFPOSRAB *****************************************************/



 #define AUFPOSRAB_PLISTE \
         "AKDAUFTRAGPOSRAB.DATUM,"\
         "AKDAUFTRAGPOSRAB.KDAUFTRAGNR,"\
         "AKDAUFTRAGPOSRAB.POSNR,"\
         "AKDAUFTRAGPOSRAB.DISCOUNTTYPE,"\
         "AKDAUFTRAGPOSRAB.DISCOUNTVALUEPCT,"\
         "AKDAUFTRAGPOSRAB.PHARMACYGROUPID,"\
         "AKDAUFTRAGPOSRAB.PAYMENTTARGETNO,"\
         "AKDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN"



/* SqlDefine of AUFTRAGWERTE **************************************************/



 #define AUFTRAGWERTE_PLISTE \
         "KDAUFTRAGWERTE.KDAUFTRAGNR,"\
         "KDAUFTRAGWERTE.ORDVALFTAXFSDISC,"\
         "KDAUFTRAGWERTE.ORDVALLTAXFSDISC,"\
         "KDAUFTRAGWERTE.ORDVALFTAXHFDISC,"\
         "KDAUFTRAGWERTE.ORDVALLTAXHFDISC,"\
         "KDAUFTRAGWERTE.ORDVALFTAXRSDISC,"\
         "KDAUFTRAGWERTE.ORDVALLTAXRSDISC"



/* SqlDefine of AUFTRAGWERTEALT ***********************************************/



 #define AUFTRAGWERTEALT_PLISTE \
         "AKDAUFTRAGWERTE.DATUM,"\
         "AKDAUFTRAGWERTE.KDAUFTRAGNR,"\
         "AKDAUFTRAGWERTE.ORDVALFTAXFSDISC,"\
         "AKDAUFTRAGWERTE.ORDVALLTAXFSDISC,"\
         "AKDAUFTRAGWERTE.ORDVALFTAXHFDISC,"\
         "AKDAUFTRAGWERTE.ORDVALLTAXHFDISC,"\
         "AKDAUFTRAGWERTE.ORDVALFTAXRSDISC,"\
         "AKDAUFTRAGWERTE.ORDVALLTAXRSDISC"



/* SqlDefine of COLLECTIVEORDERS **********************************************/



 #define COLLECTIVEORDERS_PLISTE \
         "KDAUFTRAG.KDAUFTRAGNR,"\
         "KDAUFTRAG.KDAUFTRAGSTAT,"\
         "KDAUFTRAGEREIGNIS.DATUM,"\
         "KUNDE.NAMEAPO,"\
         "KUNDE.ORT,"\
         "KUNDE.KDGRUPPE,"\
         "KDAUFTRAG.ANZPOS,"\
         "KUNDE.KZKDKLASSE,"\
         "KDAUFTRAG.KUNDENNR"



/* SqlDefine of POSCHANGE *****************************************************/



 #define POSCHANGE_PLISTE \
         "KDAUFTRAGPOSCHANGE.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSCHANGE.POSNR,"\
         "KDAUFTRAGPOSCHANGE.MENGEBESTELLT,"\
         "KDAUFTRAGPOSCHANGE.MENGEBESTAETIGT,"\
         "KDAUFTRAGPOSCHANGE.MENGE_ALT,"\
         "KDAUFTRAGPOSCHANGE.SWCHECKED,"\
         "KUNDE.NAMEAPO,"\
         "KUNDE.VERTRIEBSZENTRUMNR,"\
         "KDAUFTRAG.INVOICENUMBER,"\
         "ARTIKELZENTRAL.ARTIKEL_NAME,"\
         "ARTIKELZENTRAL.ARTIKEL_LANGNAME"



/* SqlDefine of POSCHANGEHIST *************************************************/



 #define POSCHANGEHIST_PLISTE \
         "AKDAUFTRAGPOSCHANG.DATUM,"\
         "AKDAUFTRAGPOSCHANG.KDAUFTRAGNR,"\
         "AKDAUFTRAGPOSCHANG.POSNR,"\
         "AKDAUFTRAGPOSCHANG.MENGEBESTELLT,"\
         "AKDAUFTRAGPOSCHANG.MENGEBESTAETIGT,"\
         "AKDAUFTRAGPOSCHANG.MENGE_ALT,"\
         "AKDAUFTRAGPOSCHANG.SWCHECKED,"\
         "KUNDE.NAMEAPO,"\
         "KUNDE.VERTRIEBSZENTRUMNR,"\
         "AKDAUFTRAG.INVOICENUMBER,"\
         "ARTIKELZENTRAL.ARTIKEL_NAME,"\
         "ARTIKELZENTRAL.ARTIKEL_LANGNAME"



/* SqlDefine of PROLINK *******************************************************/



 #define PROLINK_PLISTE \
         "AKDAUFTRAGPROLINK.DATUM,"\
         "AKDAUFTRAGPROLINK.KDAUFTRAGNR,"\
         "AKDAUFTRAGPROLINK.INVOICENUMBERPRO,"\
         "AKDAUFTRAGPROLINK.INVOICENUMBER,"\
         "AKDAUFTRAGPROLINK.DATEPROFORMA,"\
         "AKDAUFTRAGPROLINK.KDAUFTRAGNRPRO"



/* SqlDefine of PROLINKACT ****************************************************/



 #define PROLINKACT_PLISTE \
         "KDAUFTRAGPROLINK.KDAUFTRAGNR,"\
         "KDAUFTRAGPROLINK.INVOICENUMBERPRO,"\
         "KDAUFTRAGPROLINK.INVOICENUMBER,"\
         "KDAUFTRAGPROLINK.DATEPROFORMA,"\
         "KDAUFTRAGPROLINK.KDAUFTRAGNRPRO"



/* SqlDefine of AUFPOSRAB *****************************************************/



 #define AUFPOSRAB_UPDLISTE \
         "DATUM=?,"\
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "DISCOUNTTYPE=?,"\
         "DISCOUNTVALUEPCT=?,"\
         "PHARMACYGROUPID=?,"\
         "PAYMENTTARGETNO=?,"\
         "DISCOUNTVALPCTMAN=?"

/* SqlDefine of AUFTRAGWERTE **************************************************/



 #define AUFTRAGWERTE_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "ORDVALFTAXFSDISC=?,"\
         "ORDVALLTAXFSDISC=?,"\
         "ORDVALFTAXHFDISC=?,"\
         "ORDVALLTAXHFDISC=?,"\
         "ORDVALFTAXRSDISC=?,"\
         "ORDVALLTAXRSDISC=?"

/* SqlDefine of AUFTRAGWERTEALT ***********************************************/



 #define AUFTRAGWERTEALT_UPDLISTE \
         "DATUM=?,"\
         "KDAUFTRAGNR=?,"\
         "ORDVALFTAXFSDISC=?,"\
         "ORDVALLTAXFSDISC=?,"\
         "ORDVALFTAXHFDISC=?,"\
         "ORDVALLTAXHFDISC=?,"\
         "ORDVALFTAXRSDISC=?,"\
         "ORDVALLTAXRSDISC=?"

/* SqlDefine of COLLECTIVEORDERS **********************************************/



 #define COLLECTIVEORDERS_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "KDAUFTRAGSTAT=?,"\
         "DATUM=?,"\
         "NAMEAPO=?,"\
         "ORT=?,"\
         "KDGRUPPE=?,"\
         "ANZPOS=?,"\
         "KZKDKLASSE=?,"\
         "KUNDENNR=?"

/* SqlDefine of POSCHANGE *****************************************************/



 #define POSCHANGE_UPDLISTE \
         "SWCHECKED=?"

/* SqlDefine of POSCHANGEHIST *************************************************/



 #define POSCHANGEHIST_UPDLISTE \
         "SWCHECKED=?"

/* SqlDefine of PROLINK *******************************************************/



 #define PROLINK_UPDLISTE \
         "DATUM=?,"\
         "KDAUFTRAGNR=?,"\
         "INVOICENUMBERPRO=?,"\
         "INVOICENUMBER=?,"\
         "DATEPROFORMA=?,"\
         "KDAUFTRAGNRPRO=?"

/* SqlDefine of PROLINKACT ****************************************************/



 #define PROLINKACT_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "INVOICENUMBERPRO=?,"\
         "INVOICENUMBER=?,"\
         "DATEPROFORMA=?,"\
         "KDAUFTRAGNRPRO=?"

/* SqlMacros-Define of AUFPOSRAB **********************************************/

 #define AUFPOSRAB_ZEIGER(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTVALUEPCT,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENTTARGETNO,\
         :x->DISCOUNTVALPCTMAN

 #define AUFPOSRAB_ZEIGERSEL(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTVALUEPCT,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENTTARGETNO,\
         :x->DISCOUNTVALPCTMAN



/* SqlMacros-Define of AUFTRAGWERTE *******************************************/

 #define AUFTRAGWERTE_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->ORDVALFTAXFSDISC,\
         :x->ORDVALLTAXFSDISC,\
         :x->ORDVALFTAXHFDISC,\
         :x->ORDVALLTAXHFDISC,\
         :x->ORDVALFTAXRSDISC,\
         :x->ORDVALLTAXRSDISC

 #define AUFTRAGWERTE_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->ORDVALFTAXFSDISC,\
         :x->ORDVALLTAXFSDISC,\
         :x->ORDVALFTAXHFDISC,\
         :x->ORDVALLTAXHFDISC,\
         :x->ORDVALFTAXRSDISC,\
         :x->ORDVALLTAXRSDISC



/* SqlMacros-Define of AUFTRAGWERTEALT ****************************************/

 #define AUFTRAGWERTEALT_ZEIGER(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->ORDVALFTAXFSDISC,\
         :x->ORDVALLTAXFSDISC,\
         :x->ORDVALFTAXHFDISC,\
         :x->ORDVALLTAXHFDISC,\
         :x->ORDVALFTAXRSDISC,\
         :x->ORDVALLTAXRSDISC

 #define AUFTRAGWERTEALT_ZEIGERSEL(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->ORDVALFTAXFSDISC,\
         :x->ORDVALLTAXFSDISC,\
         :x->ORDVALFTAXHFDISC,\
         :x->ORDVALLTAXHFDISC,\
         :x->ORDVALFTAXRSDISC,\
         :x->ORDVALLTAXRSDISC



/* SqlMacros-Define of COLLECTIVEORDERS ***************************************/

 #define COLLECTIVEORDERS_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->KDAUFTRAGSTAT,\
         :x->DATUM,\
         :x->NAMEAPO,\
         :x->ORT,\
         :x->KDGRUPPE,\
         :x->ANZPOS,\
         :x->KZKDKLASSE,\
         :x->KUNDENNR

 #define COLLECTIVEORDERS_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->KDAUFTRAGSTAT,\
         :x->DATUM,\
         :x->NAMEAPO,\
         :x->ORT,\
         :x->KDGRUPPE,\
         :x->ANZPOS,\
         :x->KZKDKLASSE,\
         :x->KUNDENNR



/* SqlMacros-Define of POSCHANGE **********************************************/

 #define POSCHANGE_ZEIGER(x) \
         :x->SWCHECKED

 #define POSCHANGE_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->MENGEBESTELLT,\
         :x->MENGEBESTAETIGT,\
         :x->MENGE_ALT,\
         :x->SWCHECKED,\
         :x->NAMEAPO,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->INVOICENUMBER,\
         :x->ARTIKEL_NAME,\
         :x->ARTIKEL_LANGNAME



/* SqlMacros-Define of POSCHANGEHIST ******************************************/

 #define POSCHANGEHIST_ZEIGER(x) \
         :x->SWCHECKED

 #define POSCHANGEHIST_ZEIGERSEL(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->MENGEBESTELLT,\
         :x->MENGEBESTAETIGT,\
         :x->MENGE_ALT,\
         :x->SWCHECKED,\
         :x->NAMEAPO,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->INVOICENUMBER,\
         :x->ARTIKEL_NAME,\
         :x->ARTIKEL_LANGNAME



/* SqlMacros-Define of PROLINK ************************************************/

 #define PROLINK_ZEIGER(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO

 #define PROLINK_ZEIGERSEL(x) \
         :x->DATUM,\
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO



/* SqlMacros-Define of PROLINKACT *********************************************/

 #define PROLINKACT_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO

 #define PROLINKACT_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO



/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define AUFPOSRAB_H
 #define AUFPOSRAB_ANZ ( sizeof(AUFPOSRAB_BES) / sizeof(struct buf_desc) )
 #define AUFTRAGWERTE_H
 #define AUFTRAGWERTE_ANZ ( sizeof(AUFTRAGWERTE_BES) / sizeof(struct buf_desc) )
 #define AUFTRAGWERTEALT_H
 #define AUFTRAGWERTEALT_ANZ ( sizeof(AUFTRAGWERTEALT_BES) / sizeof(struct buf_desc) )
 #define COLLECTIVEORDERS_H
 #define COLLECTIVEORDERS_ANZ ( sizeof(COLLECTIVEORDERS_BES) / sizeof(struct buf_desc) )
 #define POSCHANGE_H
 #define POSCHANGE_ANZ ( sizeof(POSCHANGE_BES) / sizeof(struct buf_desc) )
 #define POSCHANGEHIST_H
 #define POSCHANGEHIST_ANZ ( sizeof(POSCHANGEHIST_BES) / sizeof(struct buf_desc) )
 #define PROLINK_H
 #define PROLINK_ANZ ( sizeof(PROLINK_BES) / sizeof(struct buf_desc) )
 #define PROLINKACT_H
 #define PROLINKACT_ANZ ( sizeof(PROLINKACT_BES) / sizeof(struct buf_desc) )
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of AUFPOSRAB **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_AUFPOSRAB {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;
         long FETCH_REL;
        } aufposrabS;
 #else /*TRANSCLASS*/
 typedef struct N_AUFPOSRAB {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;
         long FETCH_REL;
			bool operator==(const N_AUFPOSRAB& right) const {
			return(
				DATUM == right.DATUM &&
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				DISCOUNTTYPE == right.DISCOUNTTYPE &&
				DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
				!strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
				PAYMENTTARGETNO == right.PAYMENTTARGETNO &&
				DISCOUNTVALPCTMAN == right.DISCOUNTVALPCTMAN
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				DATUM = 0;
				KDAUFTRAGNR = 0;
				POSNR = 0;
				DISCOUNTTYPE = 0;
				DISCOUNTVALUEPCT = 0;
				strcpy(PHARMACYGROUPID, " " );
				PAYMENTTARGETNO = 0;
				DISCOUNTVALPCTMAN = 0;
#endif
			}
         } aufposrabS;
         #endif /*TRANSCLASS*/


/* original Strucur of AUFTRAGWERTE *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_AUFTRAGWERTE {
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;
        } auftragwerteS;
 #else /*TRANSCLASS*/
 typedef struct N_AUFTRAGWERTE {
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;

			bool operator==(const N_AUFTRAGWERTE& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				ORDVALFTAXFSDISC == right.ORDVALFTAXFSDISC &&
				ORDVALLTAXFSDISC == right.ORDVALLTAXFSDISC &&
				ORDVALFTAXHFDISC == right.ORDVALFTAXHFDISC &&
				ORDVALLTAXHFDISC == right.ORDVALLTAXHFDISC &&
				ORDVALFTAXRSDISC == right.ORDVALFTAXRSDISC &&
				ORDVALLTAXRSDISC == right.ORDVALLTAXRSDISC
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				ORDVALFTAXFSDISC = 0;
				ORDVALLTAXFSDISC = 0;
				ORDVALFTAXHFDISC = 0;
				ORDVALLTAXHFDISC = 0;
				ORDVALFTAXRSDISC = 0;
				ORDVALLTAXRSDISC = 0;
#endif
			}
         } auftragwerteS;
         #endif /*TRANSCLASS*/


/* original Strucur of AUFTRAGWERTEALT ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_AUFTRAGWERTEALT {
         long DATUM;
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;
        } auftragwertealtS;
 #else /*TRANSCLASS*/
 typedef struct N_AUFTRAGWERTEALT {
         long DATUM;
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;

			bool operator==(const N_AUFTRAGWERTEALT& right) const {
			return(
				DATUM == right.DATUM &&
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				ORDVALFTAXFSDISC == right.ORDVALFTAXFSDISC &&
				ORDVALLTAXFSDISC == right.ORDVALLTAXFSDISC &&
				ORDVALFTAXHFDISC == right.ORDVALFTAXHFDISC &&
				ORDVALLTAXHFDISC == right.ORDVALLTAXHFDISC &&
				ORDVALFTAXRSDISC == right.ORDVALFTAXRSDISC &&
				ORDVALLTAXRSDISC == right.ORDVALLTAXRSDISC
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				DATUM = 0;
				KDAUFTRAGNR = 0;
				ORDVALFTAXFSDISC = 0;
				ORDVALLTAXFSDISC = 0;
				ORDVALFTAXHFDISC = 0;
				ORDVALLTAXHFDISC = 0;
				ORDVALFTAXRSDISC = 0;
				ORDVALLTAXRSDISC = 0;
#endif
			}
         } auftragwertealtS;
         #endif /*TRANSCLASS*/


/* original Strucur of COLLECTIVEORDERS ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_COLLECTIVEORDERS {
         long KDAUFTRAGNR;
         char KDAUFTRAGSTAT[17];
         long DATUM;
         char NAMEAPO[41];
         char ORT[31];
         char KDGRUPPE[3];
         long ANZPOS;
         char KZKDKLASSE[4];
         long KUNDENNR;
         long FETCH_REL;
        } collectiveordersS;
 #else /*TRANSCLASS*/
 typedef struct N_COLLECTIVEORDERS {
         long KDAUFTRAGNR;
         char KDAUFTRAGSTAT[17];
         long DATUM;
         char NAMEAPO[41];
         char ORT[31];
         char KDGRUPPE[3];
         long ANZPOS;
         char KZKDKLASSE[4];
         long KUNDENNR;
         long FETCH_REL;
			bool operator==(const N_COLLECTIVEORDERS& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				!strcmp(KDAUFTRAGSTAT, right.KDAUFTRAGSTAT) &&
				DATUM == right.DATUM &&
				!strcmp(NAMEAPO, right.NAMEAPO) &&
				!strcmp(ORT, right.ORT) &&
				!strcmp(KDGRUPPE, right.KDGRUPPE) &&
				ANZPOS == right.ANZPOS &&
				!strcmp(KZKDKLASSE, right.KZKDKLASSE) &&
				KUNDENNR == right.KUNDENNR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				strcpy(KDAUFTRAGSTAT, " " );
				DATUM = 0;
				strcpy(NAMEAPO, " " );
				strcpy(ORT, " " );
				strcpy(KDGRUPPE, " " );
				ANZPOS = 0;
				strcpy(KZKDKLASSE, " " );
				KUNDENNR = 0;
#endif
			}
         } collectiveordersS;
         #endif /*TRANSCLASS*/


/* original Strucur of POSCHANGE **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_POSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
        } poschangeS;
 #else /*TRANSCLASS*/
 typedef struct N_POSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
			bool operator==(const N_POSCHANGE& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				MENGEBESTELLT == right.MENGEBESTELLT &&
				MENGEBESTAETIGT == right.MENGEBESTAETIGT &&
				MENGE_ALT == right.MENGE_ALT &&
				!strcmp(SWCHECKED, right.SWCHECKED) &&
				!strcmp(NAMEAPO, right.NAMEAPO) &&
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				!strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
				!strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
				!strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				MENGEBESTELLT = 0;
				MENGEBESTAETIGT = 0;
				MENGE_ALT = 0;
				strcpy(SWCHECKED, " " );
				strcpy(NAMEAPO, " " );
				VERTRIEBSZENTRUMNR = 0;
				strcpy(INVOICENUMBER, " " );
				strcpy(ARTIKEL_NAME, " " );
				strcpy(ARTIKEL_LANGNAME, " " );
#endif
			}
         } poschangeS;
         #endif /*TRANSCLASS*/


/* original Strucur of POSCHANGEHIST ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_POSCHANGEHIST {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
        } poschangehistS;
 #else /*TRANSCLASS*/
 typedef struct N_POSCHANGEHIST {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
			bool operator==(const N_POSCHANGEHIST& right) const {
			return(
				DATUM == right.DATUM &&
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				MENGEBESTELLT == right.MENGEBESTELLT &&
				MENGEBESTAETIGT == right.MENGEBESTAETIGT &&
				MENGE_ALT == right.MENGE_ALT &&
				!strcmp(SWCHECKED, right.SWCHECKED) &&
				!strcmp(NAMEAPO, right.NAMEAPO) &&
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				!strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
				!strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
				!strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				DATUM = 0;
				KDAUFTRAGNR = 0;
				POSNR = 0;
				MENGEBESTELLT = 0;
				MENGEBESTAETIGT = 0;
				MENGE_ALT = 0;
				strcpy(SWCHECKED, " " );
				strcpy(NAMEAPO, " " );
				VERTRIEBSZENTRUMNR = 0;
				strcpy(INVOICENUMBER, " " );
				strcpy(ARTIKEL_NAME, " " );
				strcpy(ARTIKEL_LANGNAME, " " );
#endif
			}
         } poschangehistS;
         #endif /*TRANSCLASS*/


/* original Strucur of PROLINK ************************************************/

 #ifndef TRANSCLASS
 typedef struct N_PROLINK {
         long DATUM;
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
        } prolinkS;
 #else /*TRANSCLASS*/
 typedef struct N_PROLINK {
         long DATUM;
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;

			bool operator==(const N_PROLINK& right) const {
			return(
				DATUM == right.DATUM &&
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				!strcmp(INVOICENUMBERPRO, right.INVOICENUMBERPRO) &&
				!strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
				DATEPROFORMA == right.DATEPROFORMA &&
				KDAUFTRAGNRPRO == right.KDAUFTRAGNRPRO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				DATUM = 0;
				KDAUFTRAGNR = 0;
				strcpy(INVOICENUMBERPRO, " " );
				strcpy(INVOICENUMBER, " " );
				DATEPROFORMA = 0;
				KDAUFTRAGNRPRO = 0;
#endif
			}
         } prolinkS;
         #endif /*TRANSCLASS*/


/* original Strucur of PROLINKACT *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_PROLINKACT {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
        } prolinkactS;
 #else /*TRANSCLASS*/
 typedef struct N_PROLINKACT {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;

			bool operator==(const N_PROLINKACT& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				!strcmp(INVOICENUMBERPRO, right.INVOICENUMBERPRO) &&
				!strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
				DATEPROFORMA == right.DATEPROFORMA &&
				KDAUFTRAGNRPRO == right.KDAUFTRAGNRPRO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				strcpy(INVOICENUMBERPRO, " " );
				strcpy(INVOICENUMBER, " " );
				DATEPROFORMA = 0;
				KDAUFTRAGNRPRO = 0;
#endif
			}
         } prolinkactS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of AUFPOSRAB ***********************************/

 struct C_AUFPOSRAB {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;
         long FETCH_REL;
         };

/* Structur with real chartype of AUFTRAGWERTE ********************************/

 struct C_AUFTRAGWERTE {
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;
         };

/* Structur with real chartype of AUFTRAGWERTEALT *****************************/

 struct C_AUFTRAGWERTEALT {
         long DATUM;
         long KDAUFTRAGNR;
         double ORDVALFTAXFSDISC;
         double ORDVALLTAXFSDISC;
         double ORDVALFTAXHFDISC;
         double ORDVALLTAXHFDISC;
         double ORDVALFTAXRSDISC;
         double ORDVALLTAXRSDISC;
         };

/* Structur with real chartype of COLLECTIVEORDERS ****************************/

 struct C_COLLECTIVEORDERS {
         long KDAUFTRAGNR;
         char KDAUFTRAGSTAT[17];
         long DATUM;
         char NAMEAPO[41];
         char ORT[31];
         char KDGRUPPE[3];
         long ANZPOS;
         char KZKDKLASSE[4];
         long KUNDENNR;
         long FETCH_REL;
         };

/* Structur with real chartype of POSCHANGE ***********************************/

 struct C_POSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED;
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
         };

/* Structur with real chartype of POSCHANGEHIST *******************************/

 struct C_POSCHANGEHIST {
         long DATUM;
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED;
         char NAMEAPO[41];
         short VERTRIEBSZENTRUMNR;
         char INVOICENUMBER[16];
         char ARTIKEL_NAME[31];
         char ARTIKEL_LANGNAME[51];
         long FETCH_REL;
         };

/* Structur with real chartype of PROLINK *************************************/

 struct C_PROLINK {
         long DATUM;
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
         };

/* Structur with real chartype of PROLINKACT **********************************/

 struct C_PROLINKACT {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of AUFPOSRAB *********************************/

 struct I_AUFPOSRAB {
         short DATUM;
         short KDAUFTRAGNR;
         short POSNR;
         short DISCOUNTTYPE;
         short DISCOUNTVALUEPCT;
         short PHARMACYGROUPID;
         short PAYMENTTARGETNO;
         short DISCOUNTVALPCTMAN;
         short FETCH_REL;
         };

/* Sizetype  Structur (buf_desc) of AUFTRAGWERTE ******************************/

 struct I_AUFTRAGWERTE {
         short KDAUFTRAGNR;
         short ORDVALFTAXFSDISC;
         short ORDVALLTAXFSDISC;
         short ORDVALFTAXHFDISC;
         short ORDVALLTAXHFDISC;
         short ORDVALFTAXRSDISC;
         short ORDVALLTAXRSDISC;
         };

/* Sizetype  Structur (buf_desc) of AUFTRAGWERTEALT ***************************/

 struct I_AUFTRAGWERTEALT {
         short DATUM;
         short KDAUFTRAGNR;
         short ORDVALFTAXFSDISC;
         short ORDVALLTAXFSDISC;
         short ORDVALFTAXHFDISC;
         short ORDVALLTAXHFDISC;
         short ORDVALFTAXRSDISC;
         short ORDVALLTAXRSDISC;
         };

/* Sizetype  Structur (buf_desc) of COLLECTIVEORDERS **************************/

 struct I_COLLECTIVEORDERS {
         short KDAUFTRAGNR;
         short KDAUFTRAGSTAT;
         short DATUM;
         short NAMEAPO;
         short ORT;
         short KDGRUPPE;
         short ANZPOS;
         short KZKDKLASSE;
         short KUNDENNR;
         short FETCH_REL;
         };

/* Sizetype  Structur (buf_desc) of POSCHANGE *********************************/

 struct I_POSCHANGE {
         short KDAUFTRAGNR;
         short POSNR;
         short MENGEBESTELLT;
         short MENGEBESTAETIGT;
         short MENGE_ALT;
         short SWCHECKED;
         short NAMEAPO;
         short VERTRIEBSZENTRUMNR;
         short INVOICENUMBER;
         short ARTIKEL_NAME;
         short ARTIKEL_LANGNAME;
         short FETCH_REL;
         };

/* Sizetype  Structur (buf_desc) of POSCHANGEHIST *****************************/

 struct I_POSCHANGEHIST {
         short DATUM;
         short KDAUFTRAGNR;
         short POSNR;
         short MENGEBESTELLT;
         short MENGEBESTAETIGT;
         short MENGE_ALT;
         short SWCHECKED;
         short NAMEAPO;
         short VERTRIEBSZENTRUMNR;
         short INVOICENUMBER;
         short ARTIKEL_NAME;
         short ARTIKEL_LANGNAME;
         short FETCH_REL;
         };

/* Sizetype  Structur (buf_desc) of PROLINK ***********************************/

 struct I_PROLINK {
         short DATUM;
         short KDAUFTRAGNR;
         short INVOICENUMBERPRO;
         short INVOICENUMBER;
         short DATEPROFORMA;
         short KDAUFTRAGNRPRO;
         };

/* Sizetype  Structur (buf_desc) of PROLINKACT ********************************/

 struct I_PROLINKACT {
         short KDAUFTRAGNR;
         short INVOICENUMBERPRO;
         short INVOICENUMBER;
         short DATEPROFORMA;
         short KDAUFTRAGNRPRO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of AUFPOSRAB *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc AUFPOSRAB_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFPOSRAB_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
 };
#endif

/* Structur (buf_desc) of AUFTRAGWERTE ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc AUFTRAGWERTE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFTRAGWERTE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
 };
#endif

/* Structur (buf_desc) of AUFTRAGWERTEALT *************************************/

#if defined (BUF_DESC)
 static struct buf_desc AUFTRAGWERTEALT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFTRAGWERTEALT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
 };
#endif

/* Structur (buf_desc) of COLLECTIVEORDERS ************************************/

#if defined (BUF_DESC)
 static struct buf_desc COLLECTIVEORDERS_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc COLLECTIVEORDERS_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* Structur (buf_desc) of POSCHANGE *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc POSCHANGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc POSCHANGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* Structur (buf_desc) of POSCHANGEHIST ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc POSCHANGEHIST_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc POSCHANGEHIST_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* Structur (buf_desc) of PROLINK *********************************************/

#if defined (BUF_DESC)
 static struct buf_desc PROLINK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PROLINK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* Structur (buf_desc) of PROLINKACT ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc PROLINKACT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PROLINKACT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* FunctionNumber-Define of AufPosRab *****************************************/

  #define AUFPOSRAB_SELLIST 1506

/* FunctionNumber-Define of AuftragWerte **************************************/

  #define AUFTRAGWERTE_SELWERTE 1577

/* FunctionNumber-Define of AuftragWerteAlt ***********************************/

  #define AUFTRAGWERTEALT_SELWERTE 1579

/* FunctionNumber-Define of CollectiveOrders **********************************/

  #define COLLECTIVEORDERS_SELCVORDER 1581
  #define COLLECTIVEORDERS_SELLIST 1580

/* FunctionNumber-Define of PosChange *****************************************/

  #define POSCHANGE_SELLIST 1541
  #define POSCHANGE_UPDATE 1543

/* FunctionNumber-Define of PosChangeHist *************************************/

  #define POSCHANGEHIST_SELLIST 1542
  #define POSCHANGEHIST_UPDATE 1544

/* FunctionNumber-Define of ProLink *******************************************/

  #define PROLINK_INSERT 1571
  #define PROLINK_SELPROLINK 1570

/* FunctionNumber-Define of ProLinkAct ****************************************/

  #define PROLINKACT_INSERT 1573
  #define PROLINKACT_SELPROLINK 1572

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of AufPosRab *************************************/

  #define SelList 1506

/* Old-FunctionNumber-Define of AuftragWerte **********************************/

  #define SelWerte 1577

/* Old-FunctionNumber-Define of AuftragWerteAlt *******************************/

  #define SelWerte 1579

/* Old-FunctionNumber-Define of CollectiveOrders ******************************/

  #define SelCVOrder 1581
  #define SelList 1580

/* Old-FunctionNumber-Define of PosChange *************************************/

  #define SelList 1541
  #define Update 1543

/* Old-FunctionNumber-Define of PosChangeHist *********************************/

  #define SelList 1542
  #define Update 1544

/* Old-FunctionNumber-Define of ProLink ***************************************/

  #define Insert 1571
  #define SelProLink 1570

/* Old-FunctionNumber-Define of ProLinkAct ************************************/

  #define Insert 1573
  #define SelProLink 1572

#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
	public:
		virtual    ~ppDadeVirtual() {};
		virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
		virtual int Load         (int pos = 0                  ) = 0;
 		virtual int Delete       (int pos = 0                  ) = 0;
		virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CAUFPOSRAB : public ppDadeVirtual
{
	//data members
	public:
		aufposrabS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<aufposrabS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<aufposrabS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<aufposrabS>; Strip(s); aufposrabS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<aufposrabS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<aufposrabS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<aufposrabS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetDatum() const	{ return s.DATUM; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		short		GetDiscounttype() const	{ return s.DISCOUNTTYPE; }
		double		GetDiscountvaluepct() const	{ return s.DISCOUNTVALUEPCT; }
		const char*	GetPharmacygroupid(ppString& t) const 	{ t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
		short		GetPaymenttargetno() const	{ return s.PAYMENTTARGETNO; }
		double		GetDiscountvalpctman() const	{ return s.DISCOUNTVALPCTMAN; }
		const aufposrabS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
		void 		SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
		void 		SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_AUFPOSRAB_PHARMACYGROUPID); }
		void 		SetPaymenttargetno(short t) { s.PAYMENTTARGETNO = t; }
		void 		SetDiscountvalpctman(double t) { s.DISCOUNTVALPCTMAN = t; }
		void 		SetStruct(const aufposrabS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1506,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CAUFPOSRAB()  //constructor
		{
			::buf_default((void *)&s, AUFPOSRAB_BES, AUFPOSRAB_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CAUFPOSRAB()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, AUFPOSRAB_BES, AUFPOSRAB_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,AUFPOSRAB_BES,AUFPOSRAB_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1506 ) 	return CursorServerCall(1506,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_AUFPOSRAB& d)
		{
#ifdef WIN32
			ppGStripLast(d.PHARMACYGROUPID);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, AUFPOSRAB_BES, AUFPOSRAB_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else 
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CAUFPOSRAB c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<aufposrabS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, AUFPOSRAB_BES, AUFPOSRAB_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

class CAUFTRAGWERTE : public ppDadeVirtual
{
	//data members
	public:
		auftragwerteS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<auftragwerteS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<auftragwerteS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<auftragwerteS>; Strip(s); auftragwerteS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<auftragwerteS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<auftragwerteS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<auftragwerteS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		double		GetOrdvalftaxfsdisc() const	{ return s.ORDVALFTAXFSDISC; }
		double		GetOrdvalltaxfsdisc() const	{ return s.ORDVALLTAXFSDISC; }
		double		GetOrdvalftaxhfdisc() const	{ return s.ORDVALFTAXHFDISC; }
		double		GetOrdvalltaxhfdisc() const	{ return s.ORDVALLTAXHFDISC; }
		double		GetOrdvalftaxrsdisc() const	{ return s.ORDVALFTAXRSDISC; }
		double		GetOrdvalltaxrsdisc() const	{ return s.ORDVALLTAXRSDISC; }
		const auftragwerteS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetOrdvalftaxfsdisc(double t) { s.ORDVALFTAXFSDISC = t; }
		void 		SetOrdvalltaxfsdisc(double t) { s.ORDVALLTAXFSDISC = t; }
		void 		SetOrdvalftaxhfdisc(double t) { s.ORDVALFTAXHFDISC = t; }
		void 		SetOrdvalltaxhfdisc(double t) { s.ORDVALLTAXHFDISC = t; }
		void 		SetOrdvalftaxrsdisc(double t) { s.ORDVALFTAXRSDISC = t; }
		void 		SetOrdvalltaxrsdisc(double t) { s.ORDVALLTAXRSDISC = t; }
		void 		SetStruct(const auftragwerteS& t) { s = t; }
		int 		SelWerte(int pos=0)	{ int rc = UniqueServerCall(1577,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CAUFTRAGWERTE()  //constructor
		{
			::buf_default((void *)&s, AUFTRAGWERTE_BES, AUFTRAGWERTE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CAUFTRAGWERTE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, AUFTRAGWERTE_BES, AUFTRAGWERTE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1577 ) 	return UniqueServerCall(1577,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_AUFTRAGWERTE& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, AUFTRAGWERTE_BES, AUFTRAGWERTE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

class CAUFTRAGWERTEALT : public ppDadeVirtual
{
	//data members
	public:
		auftragwertealtS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<auftragwertealtS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<auftragwertealtS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<auftragwertealtS>; Strip(s); auftragwertealtS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<auftragwertealtS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<auftragwertealtS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<auftragwertealtS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetDatum() const	{ return s.DATUM; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		double		GetOrdvalftaxfsdisc() const	{ return s.ORDVALFTAXFSDISC; }
		double		GetOrdvalltaxfsdisc() const	{ return s.ORDVALLTAXFSDISC; }
		double		GetOrdvalftaxhfdisc() const	{ return s.ORDVALFTAXHFDISC; }
		double		GetOrdvalltaxhfdisc() const	{ return s.ORDVALLTAXHFDISC; }
		double		GetOrdvalftaxrsdisc() const	{ return s.ORDVALFTAXRSDISC; }
		double		GetOrdvalltaxrsdisc() const	{ return s.ORDVALLTAXRSDISC; }
		const auftragwertealtS& GetStruct() const { return s; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetOrdvalftaxfsdisc(double t) { s.ORDVALFTAXFSDISC = t; }
		void 		SetOrdvalltaxfsdisc(double t) { s.ORDVALLTAXFSDISC = t; }
		void 		SetOrdvalftaxhfdisc(double t) { s.ORDVALFTAXHFDISC = t; }
		void 		SetOrdvalltaxhfdisc(double t) { s.ORDVALLTAXHFDISC = t; }
		void 		SetOrdvalftaxrsdisc(double t) { s.ORDVALFTAXRSDISC = t; }
		void 		SetOrdvalltaxrsdisc(double t) { s.ORDVALLTAXRSDISC = t; }
		void 		SetStruct(const auftragwertealtS& t) { s = t; }
		int 		SelWerte(int pos=0)	{ int rc = UniqueServerCall(1579,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CAUFTRAGWERTEALT()  //constructor
		{
			::buf_default((void *)&s, AUFTRAGWERTEALT_BES, AUFTRAGWERTEALT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CAUFTRAGWERTEALT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, AUFTRAGWERTEALT_BES, AUFTRAGWERTEALT_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1579 ) 	return UniqueServerCall(1579,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_AUFTRAGWERTEALT& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, AUFTRAGWERTEALT_BES, AUFTRAGWERTEALT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

class CCOLLECTIVEORDERS : public ppDadeVirtual
{
	//data members
	public:
		collectiveordersS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<collectiveordersS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<collectiveordersS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<collectiveordersS>; Strip(s); collectiveordersS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<collectiveordersS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<collectiveordersS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<collectiveordersS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const char*	GetKdauftragstat(ppString& t) const 	{ t = s.KDAUFTRAGSTAT; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDatum() const	{ return s.DATUM; }
		const char*	GetNameapo(ppString& t) const 	{ t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetOrt(ppString& t) const 	{ t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetKdgruppe(ppString& t) const 	{ t = s.KDGRUPPE; t.erasespace(ppString::END); return t.c_str(); }
		long		GetAnzpos() const	{ return s.ANZPOS; }
		const char*	GetKzkdklasse(ppString& t) const 	{ t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }
		long		GetKundennr() const	{ return s.KUNDENNR; }
		const collectiveordersS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetKdauftragstat(const ppString& t) { ppGStrCopy(s.KDAUFTRAGSTAT,t.c_str() ,L_COLLECTIVEORDERS_KDAUFTRAGSTAT); }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetNameapo(const ppString& t) { ppGStrCopy(s.NAMEAPO,t.c_str() ,L_COLLECTIVEORDERS_NAMEAPO); }
		void 		SetOrt(const ppString& t) { ppGStrCopy(s.ORT,t.c_str() ,L_COLLECTIVEORDERS_ORT); }
		void 		SetKdgruppe(const ppString& t) { ppGStrCopy(s.KDGRUPPE,t.c_str() ,L_COLLECTIVEORDERS_KDGRUPPE); }
		void 		SetAnzpos(long t) { s.ANZPOS = t; }
		void 		SetKzkdklasse(const ppString& t) { ppGStrCopy(s.KZKDKLASSE,t.c_str() ,L_COLLECTIVEORDERS_KZKDKLASSE); }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetStruct(const collectiveordersS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelCVOrder(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1581,FetchRel,pos); return rc;}
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1580,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCOLLECTIVEORDERS()  //constructor
		{
			::buf_default((void *)&s, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCOLLECTIVEORDERS()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,COLLECTIVEORDERS_BES,COLLECTIVEORDERS_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1581 ) 	return CursorServerCall(1581,s.FETCH_REL,pos);
			if( fkt_nr == 1580 ) 	return CursorServerCall(1580,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_COLLECTIVEORDERS& d)
		{
#ifdef WIN32
			ppGStripLast(d.KDAUFTRAGSTAT);
			ppGStripLast(d.NAMEAPO);
			ppGStripLast(d.ORT);
			ppGStripLast(d.KDGRUPPE);
			ppGStripLast(d.KZKDKLASSE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else 
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CCOLLECTIVEORDERS c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<collectiveordersS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

class CPOSCHANGE : public ppDadeVirtual
{
	//data members
	public:
		poschangeS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<poschangeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<poschangeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<poschangeS>; Strip(s); poschangeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<poschangeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<poschangeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<poschangeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		long		GetMengebestellt() const	{ return s.MENGEBESTELLT; }
		long		GetMengebestaetigt() const	{ return s.MENGEBESTAETIGT; }
		long		GetMenge_alt() const	{ return s.MENGE_ALT; }
		char		GetSwchecked() const	{ return s.SWCHECKED[0]; }
		const char*	GetNameapo(ppString& t) const 	{ t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		const char*	GetInvoicenumber(ppString& t) const 	{ t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetArtikel_name(ppString& t) const 	{ t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetArtikel_langname(ppString& t) const 	{ t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }
		const poschangeS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
		void 		SetMengebestaetigt(long t) { s.MENGEBESTAETIGT = t; }
		void 		SetMenge_alt(long t) { s.MENGE_ALT = t; }
		void 		SetSwchecked(char t) { s.SWCHECKED[0] = t; s.SWCHECKED[1] = '\0';}
		void 		SetNameapo(const ppString& t) { ppGStrCopy(s.NAMEAPO,t.c_str() ,L_POSCHANGE_NAMEAPO); }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_POSCHANGE_INVOICENUMBER); }
		void 		SetArtikel_name(const ppString& t) { ppGStrCopy(s.ARTIKEL_NAME,t.c_str() ,L_POSCHANGE_ARTIKEL_NAME); }
		void 		SetArtikel_langname(const ppString& t) { ppGStrCopy(s.ARTIKEL_LANGNAME,t.c_str() ,L_POSCHANGE_ARTIKEL_LANGNAME); }
		void 		SetStruct(const poschangeS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1541,FetchRel,pos); return rc;}
		int 		Update(int pos=0)	{ int rc = UniqueServerCall(1543,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPOSCHANGE()  //constructor
		{
			::buf_default((void *)&s, POSCHANGE_BES, POSCHANGE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPOSCHANGE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, POSCHANGE_BES, POSCHANGE_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,POSCHANGE_BES,POSCHANGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1541 ) 	return CursorServerCall(1541,s.FETCH_REL,pos);
			if( fkt_nr == 1543 ) 	return UniqueServerCall(1543,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_POSCHANGE& d)
		{
#ifdef WIN32
			ppGStripLast(d.NAMEAPO);
			ppGStripLast(d.INVOICENUMBER);
			ppGStripLast(d.ARTIKEL_NAME);
			ppGStripLast(d.ARTIKEL_LANGNAME);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, POSCHANGE_BES, POSCHANGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else 
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CPOSCHANGE c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<poschangeS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, POSCHANGE_BES, POSCHANGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

class CPOSCHANGEHIST : public ppDadeVirtual
{
	//data members
	public:
		poschangehistS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<poschangehistS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<poschangehistS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<poschangehistS>; Strip(s); poschangehistS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<poschangehistS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<poschangehistS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<poschangehistS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetDatum() const	{ return s.DATUM; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		long		GetMengebestellt() const	{ return s.MENGEBESTELLT; }
		long		GetMengebestaetigt() const	{ return s.MENGEBESTAETIGT; }
		long		GetMenge_alt() const	{ return s.MENGE_ALT; }
		char		GetSwchecked() const	{ return s.SWCHECKED[0]; }
		const char*	GetNameapo(ppString& t) const 	{ t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		const char*	GetInvoicenumber(ppString& t) const 	{ t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetArtikel_name(ppString& t) const 	{ t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetArtikel_langname(ppString& t) const 	{ t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }
		const poschangehistS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
		void 		SetMengebestaetigt(long t) { s.MENGEBESTAETIGT = t; }
		void 		SetMenge_alt(long t) { s.MENGE_ALT = t; }
		void 		SetSwchecked(char t) { s.SWCHECKED[0] = t; s.SWCHECKED[1] = '\0';}
		void 		SetNameapo(const ppString& t) { ppGStrCopy(s.NAMEAPO,t.c_str() ,L_POSCHANGEHIST_NAMEAPO); }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_POSCHANGEHIST_INVOICENUMBER); }
		void 		SetArtikel_name(const ppString& t) { ppGStrCopy(s.ARTIKEL_NAME,t.c_str() ,L_POSCHANGEHIST_ARTIKEL_NAME); }
		void 		SetArtikel_langname(const ppString& t) { ppGStrCopy(s.ARTIKEL_LANGNAME,t.c_str() ,L_POSCHANGEHIST_ARTIKEL_LANGNAME); }
		void 		SetStruct(const poschangehistS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1542,FetchRel,pos); return rc;}
		int 		Update(int pos=0)	{ int rc = UniqueServerCall(1544,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPOSCHANGEHIST()  //constructor
		{
			::buf_default((void *)&s, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPOSCHANGEHIST()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,POSCHANGEHIST_BES,POSCHANGEHIST_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1542 ) 	return CursorServerCall(1542,s.FETCH_REL,pos);
			if( fkt_nr == 1544 ) 	return UniqueServerCall(1544,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_POSCHANGEHIST& d)
		{
#ifdef WIN32
			ppGStripLast(d.NAMEAPO);
			ppGStripLast(d.INVOICENUMBER);
			ppGStripLast(d.ARTIKEL_NAME);
			ppGStripLast(d.ARTIKEL_LANGNAME);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else 
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CPOSCHANGEHIST c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<poschangehistS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

class CPROLINK : public ppDadeVirtual
{
	//data members
	public:
		prolinkS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<prolinkS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<prolinkS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<prolinkS>; Strip(s); prolinkS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<prolinkS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<prolinkS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<prolinkS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetDatum() const	{ return s.DATUM; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const char*	GetInvoicenumberpro(ppString& t) const 	{ t = s.INVOICENUMBERPRO; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetInvoicenumber(ppString& t) const 	{ t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDateproforma() const	{ return s.DATEPROFORMA; }
		long		GetKdauftragnrpro() const	{ return s.KDAUFTRAGNRPRO; }
		const prolinkS& GetStruct() const { return s; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetInvoicenumberpro(const ppString& t) { ppGStrCopy(s.INVOICENUMBERPRO,t.c_str() ,L_PROLINK_INVOICENUMBERPRO); }
		void 		SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_PROLINK_INVOICENUMBER); }
		void 		SetDateproforma(long t) { s.DATEPROFORMA = t; }
		void 		SetKdauftragnrpro(long t) { s.KDAUFTRAGNRPRO = t; }
		void 		SetStruct(const prolinkS& t) { s = t; }
		int 		Insert(int pos=0)	{ int rc = UniqueServerCall(1571,pos); Strip(s); return rc;}
		int 		SelProLink(int pos=0)	{ int rc = UniqueServerCall(1570,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPROLINK()  //constructor
		{
			::buf_default((void *)&s, PROLINK_BES, PROLINK_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPROLINK()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, PROLINK_BES, PROLINK_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1571 ) 	return UniqueServerCall(1571,pos);
			if( fkt_nr == 1570 ) 	return UniqueServerCall(1570,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_PROLINK& d)
		{
#ifdef WIN32
			ppGStripLast(d.INVOICENUMBERPRO);
			ppGStripLast(d.INVOICENUMBER);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, PROLINK_BES, PROLINK_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

class CPROLINKACT : public ppDadeVirtual
{
	//data members
	public:
		prolinkactS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<prolinkactS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<prolinkactS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<prolinkactS>; Strip(s); prolinkactS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<prolinkactS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<prolinkactS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<prolinkactS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const char*	GetInvoicenumberpro(ppString& t) const 	{ t = s.INVOICENUMBERPRO; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetInvoicenumber(ppString& t) const 	{ t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDateproforma() const	{ return s.DATEPROFORMA; }
		long		GetKdauftragnrpro() const	{ return s.KDAUFTRAGNRPRO; }
		const prolinkactS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetInvoicenumberpro(const ppString& t) { ppGStrCopy(s.INVOICENUMBERPRO,t.c_str() ,L_PROLINKACT_INVOICENUMBERPRO); }
		void 		SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_PROLINKACT_INVOICENUMBER); }
		void 		SetDateproforma(long t) { s.DATEPROFORMA = t; }
		void 		SetKdauftragnrpro(long t) { s.KDAUFTRAGNRPRO = t; }
		void 		SetStruct(const prolinkactS& t) { s = t; }
		int 		Insert(int pos=0)	{ int rc = UniqueServerCall(1573,pos); Strip(s); return rc;}
		int 		SelProLink(int pos=0)	{ int rc = UniqueServerCall(1572,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPROLINKACT()  //constructor
		{
			::buf_default((void *)&s, PROLINKACT_BES, PROLINKACT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPROLINKACT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, PROLINKACT_BES, PROLINKACT_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1573 ) 	return UniqueServerCall(1573,pos);
			if( fkt_nr == 1572 ) 	return UniqueServerCall(1572,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_PROLINKACT& d)
		{
#ifdef WIN32
			ppGStripLast(d.INVOICENUMBERPRO);
			ppGStripLast(d.INVOICENUMBER);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, PROLINKACT_BES, PROLINKACT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

#endif
