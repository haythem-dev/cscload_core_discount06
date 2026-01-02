#ifndef __PP_KDAUFTRAGART_H_
#define __PP_KDAUFTRAGART_H_

/******************************************************************************/
/* w:\kdauftragart ************************************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGART **********************************************/

#define L_KDAUFTRAGART_KDAUFTRAGART 2
#define L_KDAUFTRAGART_AUFTRAGARTTYP 11
#define L_KDAUFTRAGART_BEZEICHNUNG 30
#define L_KDAUFTRAGART_VALUTAMONATE 11
#define L_KDAUFTRAGART_SKDAUFTRAGARTNATRA 1
#define L_KDAUFTRAGART_SKDAUFTRAGARTNETTO 1
#define L_KDAUFTRAGART_SKDAUFTRAGARTBANR 1
#define L_KDAUFTRAGART_SKDAUFTRAGARTMONAT 1
#define L_KDAUFTRAGART_SKDAUFTRAGVERBUND 1
#define L_KDAUFTRAGART_SKDAUFTRAGARTVALS 1
#define L_KDAUFTRAGART_SGLOBAL 1
#define L_KDAUFTRAGART_SBILDSCHIRM 1
#define L_KDAUFTRAGART_SDAFUE 1
#define L_KDAUFTRAGART_SSTANDARD 1
#define L_KDAUFTRAGART_BRANCHNO 6
#define L_KDAUFTRAGART_DISINKINDENTERABLE 1
#define L_KDAUFTRAGART_SDISCOUNTABLE 1
#define L_KDAUFTRAGART_SMUSTSUBORDER 1
#define L_KDAUFTRAGART_SFREEPRICE 1
#define L_KDAUFTRAGART_SORDERCONS 1
#define L_KDAUFTRAGART_SRESTDEL 1
#define L_KDAUFTRAGART_SNOQUOTA 1
#define L_KDAUFTRAGART_SNOPARTQTY 1
#define L_KDAUFTRAGART_SDEFERORDER 1
#define L_KDAUFTRAGART_SSERVICEORDER 1
#define L_KDAUFTRAGART_SNODD 1
#define L_KDAUFTRAGART_SONLYEH 1
#define L_KDAUFTRAGART_SNOPROMOTIONS 6
#define L_KDAUFTRAGART_SDEFAULTKENNUNG 6
#define L_KDAUFTRAGART_SALWAYSRESTDEL 6
#define L_KDAUFTRAGART_STOCKRESERVATION 1

/* Length/Count-Define of KDAUFTRAGART ****************************************/

#define LS_KDAUFTRAGART_KDAUFTRAGART 2 + 1
#define LS_KDAUFTRAGART_AUFTRAGARTTYP 10 + 1
#define LS_KDAUFTRAGART_BEZEICHNUNG 30 + 1
#define LS_KDAUFTRAGART_VALUTAMONATE 10 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGARTNATRA 1 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGARTNETTO 1 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGARTBANR 1 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGARTMONAT 1 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGVERBUND 1 + 1
#define LS_KDAUFTRAGART_SKDAUFTRAGARTVALS 1 + 1
#define LS_KDAUFTRAGART_SGLOBAL 1 + 1
#define LS_KDAUFTRAGART_SBILDSCHIRM 1 + 1
#define LS_KDAUFTRAGART_SDAFUE 1 + 1
#define LS_KDAUFTRAGART_SSTANDARD 1 + 1
#define LS_KDAUFTRAGART_BRANCHNO 5 + 1
#define LS_KDAUFTRAGART_DISINKINDENTERABLE 1 + 1
#define LS_KDAUFTRAGART_SDISCOUNTABLE 1 + 1
#define LS_KDAUFTRAGART_SMUSTSUBORDER 1 + 1
#define LS_KDAUFTRAGART_SFREEPRICE 1 + 1
#define LS_KDAUFTRAGART_SORDERCONS 1 + 1
#define LS_KDAUFTRAGART_SRESTDEL 1 + 1
#define LS_KDAUFTRAGART_SNOQUOTA 1 + 1
#define LS_KDAUFTRAGART_SNOPARTQTY 1 + 1
#define LS_KDAUFTRAGART_SDEFERORDER 1 + 1
#define LS_KDAUFTRAGART_SSERVICEORDER 1 + 1
#define LS_KDAUFTRAGART_SNODD 1 + 1
#define LS_KDAUFTRAGART_SONLYEH 1 + 1
#define LS_KDAUFTRAGART_SNOPROMOTIONS 5 + 1
#define LS_KDAUFTRAGART_SDEFAULTKENNUNG 5 + 1
#define LS_KDAUFTRAGART_SALWAYSRESTDEL 5 + 1
#define LS_KDAUFTRAGART_STOCKRESERVATION 1 + 1

#define KDAUFTRAGARTKDAUFTRAGART 0
#define KDAUFTRAGARTAUFTRAGARTTYP 1
#define KDAUFTRAGARTBEZEICHNUNG 2
#define KDAUFTRAGARTVALUTAMONATE 3
#define KDAUFTRAGARTSKDAUFTRAGARTNATRA 4
#define KDAUFTRAGARTSKDAUFTRAGARTNETTO 5
#define KDAUFTRAGARTSKDAUFTRAGARTBANR 6
#define KDAUFTRAGARTSKDAUFTRAGARTMONAT 7
#define KDAUFTRAGARTSKDAUFTRAGVERBUND 8
#define KDAUFTRAGARTSKDAUFTRAGARTVALS 9
#define KDAUFTRAGARTSGLOBAL 10
#define KDAUFTRAGARTSBILDSCHIRM 11
#define KDAUFTRAGARTSDAFUE 12
#define KDAUFTRAGARTSSTANDARD 13
#define KDAUFTRAGARTBRANCHNO 14
#define KDAUFTRAGARTDISINKINDENTERABLE 15
#define KDAUFTRAGARTSDISCOUNTABLE 16
#define KDAUFTRAGARTSMUSTSUBORDER 17
#define KDAUFTRAGARTSFREEPRICE 18
#define KDAUFTRAGARTSORDERCONS 19
#define KDAUFTRAGARTSRESTDEL 20
#define KDAUFTRAGARTSNOQUOTA 21
#define KDAUFTRAGARTSNOPARTQTY 22
#define KDAUFTRAGARTSDEFERORDER 23
#define KDAUFTRAGARTSSERVICEORDER 24
#define KDAUFTRAGARTSNODD 25
#define KDAUFTRAGARTSONLYEH 26
#define KDAUFTRAGARTSNOPROMOTIONS 27
#define KDAUFTRAGARTSDEFAULTKENNUNG 28
#define KDAUFTRAGARTSALWAYSRESTDEL 29
#define KDAUFTRAGARTSTOCKRESERVATION 30

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGART_H
#define KDAUFTRAGART_ANZ ( sizeof(KDAUFTRAGART_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGART **************************************************/

#define KDAUFTRAGART_LISTE \
        KDAUFTRAGART.KDAUFTRAGART,\
        KDAUFTRAGART.AUFTRAGARTTYP,\
        KDAUFTRAGART.BEZEICHNUNG,\
        KDAUFTRAGART.VALUTAMONATE,\
        KDAUFTRAGART.SKDAUFTRAGARTNATRA,\
        KDAUFTRAGART.SKDAUFTRAGARTNETTO,\
        KDAUFTRAGART.SKDAUFTRAGARTBANR,\
        KDAUFTRAGART.SKDAUFTRAGARTMONAT,\
        KDAUFTRAGART.SKDAUFTRAGVERBUND,\
        KDAUFTRAGART.SKDAUFTRAGARTVALS,\
        KDAUFTRAGART.SGLOBAL,\
        KDAUFTRAGART.SBILDSCHIRM,\
        KDAUFTRAGART.SDAFUE,\
        KDAUFTRAGART.SSTANDARD,\
        KDAUFTRAGART.BRANCHNO,\
        KDAUFTRAGART.DISINKINDENTERABLE,\
        KDAUFTRAGART.SDISCOUNTABLE,\
        KDAUFTRAGART.SMUSTSUBORDER,\
        KDAUFTRAGART.SFREEPRICE,\
        KDAUFTRAGART.SORDERCONS,\
        KDAUFTRAGART.SRESTDEL,\
        KDAUFTRAGART.SNOQUOTA,\
        KDAUFTRAGART.SNOPARTQTY,\
        KDAUFTRAGART.SDEFERORDER,\
        KDAUFTRAGART.SSERVICEORDER,\
        KDAUFTRAGART.SNODD,\
        KDAUFTRAGART.SONLYEH,\
        KDAUFTRAGART.SNOPROMOTIONS,\
        KDAUFTRAGART.SDEFAULTKENNUNG,\
        KDAUFTRAGART.SALWAYSRESTDEL,\
		KDAUFTRAGART.STOCKRESERVATION
#define KDAUFTRAGART_LISTE_390 \
        KDAUFTRAGART,\
        AUFTRAGARTTYP,\
        BEZEICHNUNG,\
        VALUTAMONATE,\
        SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO,\
        SKDAUFTRAGARTBANR,\
        SKDAUFTRAGARTMONAT,\
        SKDAUFTRAGVERBUND,\
        SKDAUFTRAGARTVALS,\
        SGLOBAL,\
        SBILDSCHIRM,\
        SDAFUE,\
        SSTANDARD,\
        BRANCHNO,\
        DISINKINDENTERABLE,\
        SDISCOUNTABLE,\
        SMUSTSUBORDER,\
        SFREEPRICE,\
        SORDERCONS,\
        SRESTDEL,\
        SNOQUOTA,\
        SNOPARTQTY,\
        SDEFERORDER,\
        SSERVICEORDER,\
        SNODD,\
        SONLYEH,\
        SNOPROMOTIONS,\
        SDEFAULTKENNUNG,\
        SALWAYSRESTDEL,\
		STOCKRESERVATION
#define KDAUFTRAGART_PLISTE \
        "KDAUFTRAGART.KDAUFTRAGART,"\
        "KDAUFTRAGART.AUFTRAGARTTYP,"\
        "KDAUFTRAGART.BEZEICHNUNG,"\
        "KDAUFTRAGART.VALUTAMONATE,"\
        "KDAUFTRAGART.SKDAUFTRAGARTNATRA,"\
        "KDAUFTRAGART.SKDAUFTRAGARTNETTO,"\
        "KDAUFTRAGART.SKDAUFTRAGARTBANR,"\
        "KDAUFTRAGART.SKDAUFTRAGARTMONAT,"\
        "KDAUFTRAGART.SKDAUFTRAGVERBUND,"\
        "KDAUFTRAGART.SKDAUFTRAGARTVALS,"\
        "KDAUFTRAGART.SGLOBAL,"\
        "KDAUFTRAGART.SBILDSCHIRM,"\
        "KDAUFTRAGART.SDAFUE,"\
        "KDAUFTRAGART.SSTANDARD,"\
        "KDAUFTRAGART.BRANCHNO,"\
        "KDAUFTRAGART.DISINKINDENTERABLE,"\
        "KDAUFTRAGART.SDISCOUNTABLE,"\
        "KDAUFTRAGART.SMUSTSUBORDER,"\
        "KDAUFTRAGART.SFREEPRICE,"\
        "KDAUFTRAGART.SORDERCONS,"\
        "KDAUFTRAGART.SRESTDEL,"\
        "KDAUFTRAGART.SNOQUOTA,"\
        "KDAUFTRAGART.SNOPARTQTY,"\
        "KDAUFTRAGART.SDEFERORDER,"\
        "KDAUFTRAGART.SSERVICEORDER,"\
        "KDAUFTRAGART.SNODD,"\
        "KDAUFTRAGART.SONLYEH,"\
        "KDAUFTRAGART.SNOPROMOTIONS,"\
        "KDAUFTRAGART.SDEFAULTKENNUNG,"\
        "KDAUFTRAGART.SALWAYSRESTDEL,"\
		"KDAUFTRAGART.STOCKRESERVATION"
#define KDAUFTRAGART_PELISTE \
        "KDAUFTRAGART,"\
        "AUFTRAGARTTYP,"\
        "BEZEICHNUNG,"\
        "VALUTAMONATE,"\
        "SKDAUFTRAGARTNATRA,"\
        "SKDAUFTRAGARTNETTO,"\
        "SKDAUFTRAGARTBANR,"\
        "SKDAUFTRAGARTMONAT,"\
        "SKDAUFTRAGVERBUND,"\
        "SKDAUFTRAGARTVALS,"\
        "SGLOBAL,"\
        "SBILDSCHIRM,"\
        "SDAFUE,"\
        "SSTANDARD,"\
        "BRANCHNO,"\
        "DISINKINDENTERABLE,"\
        "SDISCOUNTABLE,"\
        "SMUSTSUBORDER,"\
        "SFREEPRICE,"\
        "SORDERCONS,"\
        "SRESTDEL,"\
        "SNOQUOTA,"\
        "SNOPARTQTY,"\
        "SDEFERORDER,"\
        "SSERVICEORDER,"\
        "SNODD,"\
        "SONLYEH,"\
        "SNOPROMOTIONS,"\
        "SDEFAULTKENNUNG,"\
        "SALWAYSRESTDEL,"\
		"STOCKRESERVATION"
#define KDAUFTRAGART_UPDLISTE \
        "KDAUFTRAGART=?,"\
        "AUFTRAGARTTYP=?,"\
        "BEZEICHNUNG=?,"\
        "VALUTAMONATE=?,"\
        "SKDAUFTRAGARTNATRA=?,"\
        "SKDAUFTRAGARTNETTO=?,"\
        "SKDAUFTRAGARTBANR=?,"\
        "SKDAUFTRAGARTMONAT=?,"\
        "SKDAUFTRAGVERBUND=?,"\
        "SKDAUFTRAGARTVALS=?,"\
        "SGLOBAL=?,"\
        "SBILDSCHIRM=?,"\
        "SDAFUE=?,"\
        "SSTANDARD=?,"\
        "BRANCHNO=?,"\
        "DISINKINDENTERABLE=?,"\
        "SDISCOUNTABLE=?,"\
        "SMUSTSUBORDER=?,"\
        "SFREEPRICE=?,"\
        "SORDERCONS=?,"\
        "SRESTDEL=?,"\
        "SNOQUOTA=?,"\
        "SNOPARTQTY=?,"\
        "SDEFERORDER=?,"\
        "SSERVICEORDER=?,"\
        "SNODD=?,"\
        "SONLYEH=?,"\
        "SNOPROMOTIONS=?,"\
        "SDEFAULTKENNUNG=?,"\
        "SALWAYSRESTDEL=?,"\
		"STOCKRESERVATION=?"
/* SqlMacros-Define of KDAUFTRAGART *******************************************/

#define KDAUFTRAGART_ZEIGER(x) \
        :x->KDAUFTRAGART,\
        :x->AUFTRAGARTTYP,\
        :x->BEZEICHNUNG,\
        :x->VALUTAMONATE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
        :x->SKDAUFTRAGARTBANR,\
        :x->SKDAUFTRAGARTMONAT,\
        :x->SKDAUFTRAGVERBUND,\
        :x->SKDAUFTRAGARTVALS,\
        :x->SGLOBAL,\
        :x->SBILDSCHIRM,\
        :x->SDAFUE,\
        :x->SSTANDARD,\
        :x->BRANCHNO,\
        :x->DISINKINDENTERABLE,\
        :x->SDISCOUNTABLE,\
        :x->SMUSTSUBORDER,\
        :x->SFREEPRICE,\
        :x->SORDERCONS,\
        :x->SRESTDEL,\
        :x->SNOQUOTA,\
        :x->SNOPARTQTY,\
        :x->SDEFERORDER,\
        :x->SSERVICEORDER,\
        :x->SNODD,\
        :x->SONLYEH,\
        :x->SNOPROMOTIONS,\
        :x->SDEFAULTKENNUNG,\
        :x->SALWAYSRESTDEL,\
		:x->STOCKRESERVATION
#define KDAUFTRAGART_ZEIGERSEL(x) \
        :x->KDAUFTRAGART,\
        :x->AUFTRAGARTTYP,\
        :x->BEZEICHNUNG,\
        :x->VALUTAMONATE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
        :x->SKDAUFTRAGARTBANR,\
        :x->SKDAUFTRAGARTMONAT,\
        :x->SKDAUFTRAGVERBUND,\
        :x->SKDAUFTRAGARTVALS,\
        :x->SGLOBAL,\
        :x->SBILDSCHIRM,\
        :x->SDAFUE,\
        :x->SSTANDARD,\
        :x->BRANCHNO,\
        :x->DISINKINDENTERABLE,\
        :x->SDISCOUNTABLE,\
        :x->SMUSTSUBORDER,\
        :x->SFREEPRICE,\
        :x->SORDERCONS,\
        :x->SRESTDEL,\
        :x->SNOQUOTA,\
        :x->SNOPARTQTY,\
        :x->SDEFERORDER,\
        :x->SSERVICEORDER,\
        :x->SNODD,\
        :x->SONLYEH,\
        :x->SNOPROMOTIONS,\
        :x->SDEFAULTKENNUNG,\
        :x->SALWAYSRESTDEL,\
		:x->STOCKRESERVATION
#define KDAUFTRAGART_UPDATE(x) \
        KDAUFTRAGART.KDAUFTRAGART=:x->KDAUFTRAGART,\
        KDAUFTRAGART.AUFTRAGARTTYP=:x->AUFTRAGARTTYP,\
        KDAUFTRAGART.BEZEICHNUNG=:x->BEZEICHNUNG,\
        KDAUFTRAGART.VALUTAMONATE=:x->VALUTAMONATE,\
        KDAUFTRAGART.SKDAUFTRAGARTNATRA=:x->SKDAUFTRAGARTNATRA,\
        KDAUFTRAGART.SKDAUFTRAGARTNETTO=:x->SKDAUFTRAGARTNETTO,\
        KDAUFTRAGART.SKDAUFTRAGARTBANR=:x->SKDAUFTRAGARTBANR,\
        KDAUFTRAGART.SKDAUFTRAGARTMONAT=:x->SKDAUFTRAGARTMONAT,\
        KDAUFTRAGART.SKDAUFTRAGVERBUND=:x->SKDAUFTRAGVERBUND,\
        KDAUFTRAGART.SKDAUFTRAGARTVALS=:x->SKDAUFTRAGARTVALS,\
        KDAUFTRAGART.SGLOBAL=:x->SGLOBAL,\
        KDAUFTRAGART.SBILDSCHIRM=:x->SBILDSCHIRM,\
        KDAUFTRAGART.SDAFUE=:x->SDAFUE,\
        KDAUFTRAGART.SSTANDARD=:x->SSTANDARD,\
        KDAUFTRAGART.BRANCHNO=:x->BRANCHNO,\
        KDAUFTRAGART.DISINKINDENTERABLE=:x->DISINKINDENTERABLE,\
        KDAUFTRAGART.SDISCOUNTABLE=:x->SDISCOUNTABLE,\
        KDAUFTRAGART.SMUSTSUBORDER=:x->SMUSTSUBORDER,\
        KDAUFTRAGART.SFREEPRICE=:x->SFREEPRICE,\
        KDAUFTRAGART.SORDERCONS=:x->SORDERCONS,\
        KDAUFTRAGART.SRESTDEL=:x->SRESTDEL,\
        KDAUFTRAGART.SNOQUOTA=:x->SNOQUOTA,\
        KDAUFTRAGART.SNOPARTQTY=:x->SNOPARTQTY,\
        KDAUFTRAGART.SDEFERORDER=:x->SDEFERORDER,\
        KDAUFTRAGART.SSERVICEORDER=:x->SSERVICEORDER,\
        KDAUFTRAGART.SNODD=:x->SNODD,\
        KDAUFTRAGART.SONLYEH=:x->SONLYEH,\
        KDAUFTRAGART.SNOPROMOTIONS=:x->SNOPROMOTIONS,\
        KDAUFTRAGART.SDEFAULTKENNUNG=:x->SDEFAULTKENNUNG,\
        KDAUFTRAGART.SALWAYSRESTDEL=:x->SALWAYSRESTDEL,\
		KDAUFTRAGART.STOCKRESERVATION=:x->STOCKRESERVATION
/* SqlMacros390-Define of KDAUFTRAGART ****************************************/

#define KDAUFTRAGART_ZEIGER_390 \
        :KDAUFTRAGART,\
        :AUFTRAGARTTYP,\
        :BEZEICHNUNG,\
        :VALUTAMONATE,\
        :SKDAUFTRAGARTNATRA,\
        :SKDAUFTRAGARTNETTO,\
        :SKDAUFTRAGARTBANR,\
        :SKDAUFTRAGARTMONAT,\
        :SKDAUFTRAGVERBUND,\
        :SKDAUFTRAGARTVALS,\
        :SGLOBAL,\
        :SBILDSCHIRM,\
        :SDAFUE,\
        :SSTANDARD,\
        :BRANCHNO,\
        :DISINKINDENTERABLE,\
        :SDISCOUNTABLE,\
        :SMUSTSUBORDER,\
        :SFREEPRICE,\
        :SORDERCONS,\
        :SRESTDEL,\
        :SNOQUOTA,\
        :SNOPARTQTY,\
        :SDEFERORDER,\
        :SSERVICEORDER,\
        :SNODD,\
        :SONLYEH,\
        :SNOPROMOTIONS,\
        :SDEFAULTKENNUNG,\
        :SALWAYSRESTDEL,\
		:STOCKRESERVATION 
#define KDAUFTRAGART_UPDATE_390 \
        KDAUFTRAGART=:KDAUFTRAGART,\
        AUFTRAGARTTYP=:AUFTRAGARTTYP,\
        BEZEICHNUNG=:BEZEICHNUNG,\
        VALUTAMONATE=:VALUTAMONATE,\
        SKDAUFTRAGARTNATRA=:SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO=:SKDAUFTRAGARTNETTO,\
        SKDAUFTRAGARTBANR=:SKDAUFTRAGARTBANR,\
        SKDAUFTRAGARTMONAT=:SKDAUFTRAGARTMONAT,\
        SKDAUFTRAGVERBUND=:SKDAUFTRAGVERBUND,\
        SKDAUFTRAGARTVALS=:SKDAUFTRAGARTVALS,\
        SGLOBAL=:SGLOBAL,\
        SBILDSCHIRM=:SBILDSCHIRM,\
        SDAFUE=:SDAFUE,\
        SSTANDARD=:SSTANDARD,\
        BRANCHNO=:BRANCHNO,\
        DISINKINDENTERABLE=:DISINKINDENTERABLE,\
        SDISCOUNTABLE=:SDISCOUNTABLE,\
        SMUSTSUBORDER=:SMUSTSUBORDER,\
        SFREEPRICE=:SFREEPRICE,\
        SORDERCONS=:SORDERCONS,\
        SRESTDEL=:SRESTDEL,\
        SNOQUOTA=:SNOQUOTA,\
        SNOPARTQTY=:SNOPARTQTY,\
        SDEFERORDER=:SDEFERORDER,\
        SSERVICEORDER=:SSERVICEORDER,\
        SNODD=:SNODD,\
        SONLYEH=:SONLYEH,\
        SNOPROMOTIONS=:SNOPROMOTIONS,\
        SDEFAULTKENNUNG=:SDEFAULTKENNUNG,\
        SALWAYSRESTDEL=:SALWAYSRESTDEL,\
		STOCKRESERVATION=:STOCKRESERVATION
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGART ********************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGART {
    char KDAUFTRAGART[3];
    long AUFTRAGARTTYP;
    char BEZEICHNUNG[31];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
    char SKDAUFTRAGARTBANR[2];
    char SKDAUFTRAGARTMONAT[2];
    char SKDAUFTRAGVERBUND[2];
    char SKDAUFTRAGARTVALS[2];
    char SGLOBAL[2];
    char SBILDSCHIRM[2];
    char SDAFUE[2];
    char SSTANDARD[2];
    short BRANCHNO;
    char DISINKINDENTERABLE[2];
    char SDISCOUNTABLE[2];
    char SMUSTSUBORDER[2];
    char SFREEPRICE[2];
    char SORDERCONS[2];
    char SRESTDEL[2];
    char SNOQUOTA[2];
    char SNOPARTQTY[2];
    char SDEFERORDER[2];
    char SSERVICEORDER[2];
    char SNODD[2];
    char SONLYEH[2];
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SALWAYSRESTDEL;
    short STOCKRESERVATION;
} kdauftragartS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGART {
    char KDAUFTRAGART[3];
    long AUFTRAGARTTYP;
    char BEZEICHNUNG[31];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
    char SKDAUFTRAGARTBANR[2];
    char SKDAUFTRAGARTMONAT[2];
    char SKDAUFTRAGVERBUND[2];
    char SKDAUFTRAGARTVALS[2];
    char SGLOBAL[2];
    char SBILDSCHIRM[2];
    char SDAFUE[2];
    char SSTANDARD[2];
    short BRANCHNO;
    char DISINKINDENTERABLE[2];
    char SDISCOUNTABLE[2];
    char SMUSTSUBORDER[2];
    char SFREEPRICE[2];
    char SORDERCONS[2];
    char SRESTDEL[2];
    char SNOQUOTA[2];
    char SNOPARTQTY[2];
    char SDEFERORDER[2];
    char SSERVICEORDER[2];
    char SNODD[2];
    char SONLYEH[2];
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SALWAYSRESTDEL;
    short STOCKRESERVATION;

    bool operator == (const N_KDAUFTRAGART& right) const {
        return (
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            AUFTRAGARTTYP == right.AUFTRAGARTTYP &&
            !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
            VALUTAMONATE == right.VALUTAMONATE &&
            !strcmp(SKDAUFTRAGARTNATRA, right.SKDAUFTRAGARTNATRA) &&
            !strcmp(SKDAUFTRAGARTNETTO, right.SKDAUFTRAGARTNETTO) &&
            !strcmp(SKDAUFTRAGARTBANR, right.SKDAUFTRAGARTBANR) &&
            !strcmp(SKDAUFTRAGARTMONAT, right.SKDAUFTRAGARTMONAT) &&
            !strcmp(SKDAUFTRAGVERBUND, right.SKDAUFTRAGVERBUND) &&
            !strcmp(SKDAUFTRAGARTVALS, right.SKDAUFTRAGARTVALS) &&
            !strcmp(SGLOBAL, right.SGLOBAL) &&
            !strcmp(SBILDSCHIRM, right.SBILDSCHIRM) &&
            !strcmp(SDAFUE, right.SDAFUE) &&
            !strcmp(SSTANDARD, right.SSTANDARD) &&
            BRANCHNO == right.BRANCHNO &&
            !strcmp(DISINKINDENTERABLE, right.DISINKINDENTERABLE) &&
            !strcmp(SDISCOUNTABLE, right.SDISCOUNTABLE) &&
            !strcmp(SMUSTSUBORDER, right.SMUSTSUBORDER) &&
            !strcmp(SFREEPRICE, right.SFREEPRICE) &&
            !strcmp(SORDERCONS, right.SORDERCONS) &&
            !strcmp(SRESTDEL, right.SRESTDEL) &&
            !strcmp(SNOQUOTA, right.SNOQUOTA) &&
            !strcmp(SNOPARTQTY, right.SNOPARTQTY) &&
            !strcmp(SDEFERORDER, right.SDEFERORDER) &&
            !strcmp(SSERVICEORDER, right.SSERVICEORDER) &&
            !strcmp(SNODD, right.SNODD) &&
            !strcmp(SONLYEH, right.SONLYEH) &&
            SNOPROMOTIONS == right.SNOPROMOTIONS &&
            SDEFAULTKENNUNG == right.SDEFAULTKENNUNG &&
            SALWAYSRESTDEL == right.SALWAYSRESTDEL &&
            STOCKRESERVATION == right.STOCKRESERVATION
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(KDAUFTRAGART, " " );
        AUFTRAGARTTYP = 0;
        strcpy(BEZEICHNUNG, " " );
        VALUTAMONATE = 0;
        strcpy(SKDAUFTRAGARTNATRA, " " );
        strcpy(SKDAUFTRAGARTNETTO, " " );
        strcpy(SKDAUFTRAGARTBANR, " " );
        strcpy(SKDAUFTRAGARTMONAT, " " );
        strcpy(SKDAUFTRAGVERBUND, " " );
        strcpy(SKDAUFTRAGARTVALS, " " );
        strcpy(SGLOBAL, " " );
        strcpy(SBILDSCHIRM, " " );
        strcpy(SDAFUE, " " );
        strcpy(SSTANDARD, " " );
        BRANCHNO = 0;
        strcpy(DISINKINDENTERABLE, " " );
        strcpy(SDISCOUNTABLE, " " );
        strcpy(SMUSTSUBORDER, " " );
        strcpy(SFREEPRICE, " " );
        strcpy(SORDERCONS, " " );
        strcpy(SRESTDEL, " " );
        strcpy(SNOQUOTA, " " );
        strcpy(SNOPARTQTY, " " );
        strcpy(SDEFERORDER, " " );
        strcpy(SSERVICEORDER, " " );
        strcpy(SNODD, " " );
        strcpy(SONLYEH, " " );
        SNOPROMOTIONS = 0;
        SDEFAULTKENNUNG = 0;
        SALWAYSRESTDEL = 0;
        STOCKRESERVATION = 0;
#endif
    }
} kdauftragartS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGART **************************************/

struct S_KDAUFTRAGART {
    char KDAUFTRAGART[2 + 1];
    char AUFTRAGARTTYP[11];
    char BEZEICHNUNG[30 + 1];
    char VALUTAMONATE[11];
    char SKDAUFTRAGARTNATRA[1 + 1];
    char SKDAUFTRAGARTNETTO[1 + 1];
    char SKDAUFTRAGARTBANR[1 + 1];
    char SKDAUFTRAGARTMONAT[1 + 1];
    char SKDAUFTRAGVERBUND[1 + 1];
    char SKDAUFTRAGARTVALS[1 + 1];
    char SGLOBAL[1 + 1];
    char SBILDSCHIRM[1 + 1];
    char SDAFUE[1 + 1];
    char SSTANDARD[1 + 1];
    char BRANCHNO[7];
    char DISINKINDENTERABLE[1 + 1];
    char SDISCOUNTABLE[1 + 1];
    char SMUSTSUBORDER[1 + 1];
    char SFREEPRICE[1 + 1];
    char SORDERCONS[1 + 1];
    char SRESTDEL[1 + 1];
    char SNOQUOTA[1 + 1];
    char SNOPARTQTY[1 + 1];
    char SDEFERORDER[1 + 1];
    char SSERVICEORDER[1 + 1];
    char SNODD[1 + 1];
    char SONLYEH[1 + 1];
    char SNOPROMOTIONS[7];
    char SDEFAULTKENNUNG[7];
    char SALWAYSRESTDEL[7];
    char STOCKRESERVATION[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGART *********************/

struct O_KDAUFTRAGART {
    char KDAUFTRAGART[2];
    char AUFTRAGARTTYP[11];
    char BEZEICHNUNG[30];
    char VALUTAMONATE[11];
    char SKDAUFTRAGARTNATRA[1];
    char SKDAUFTRAGARTNETTO[1];
    char SKDAUFTRAGARTBANR[1];
    char SKDAUFTRAGARTMONAT[1];
    char SKDAUFTRAGVERBUND[1];
    char SKDAUFTRAGARTVALS[1];
    char SGLOBAL[1];
    char SBILDSCHIRM[1];
    char SDAFUE[1];
    char SSTANDARD[1];
    char BRANCHNO[7];
    char DISINKINDENTERABLE[1];
    char SDISCOUNTABLE[1];
    char SMUSTSUBORDER[1];
    char SFREEPRICE[1];
    char SORDERCONS[1];
    char SRESTDEL[1];
    char SNOQUOTA[1];
    char SNOPARTQTY[1];
    char SDEFERORDER[1];
    char SSERVICEORDER[1];
    char SNODD[1];
    char SONLYEH[1];
    char SNOPROMOTIONS[7];
    char SDEFAULTKENNUNG[7];
    char SALWAYSRESTDEL[7];
    char STOCKRESERVATION[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGART ********************************/

struct C_KDAUFTRAGART {
    char KDAUFTRAGART[3];
    long AUFTRAGARTTYP;
    char BEZEICHNUNG[31];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA;
    char SKDAUFTRAGARTNETTO;
    char SKDAUFTRAGARTBANR;
    char SKDAUFTRAGARTMONAT;
    char SKDAUFTRAGVERBUND;
    char SKDAUFTRAGARTVALS;
    char SGLOBAL;
    char SBILDSCHIRM;
    char SDAFUE;
    char SSTANDARD;
    short BRANCHNO;
    char DISINKINDENTERABLE;
    char SDISCOUNTABLE;
    char SMUSTSUBORDER;
    char SFREEPRICE;
    char SORDERCONS;
    char SRESTDEL;
    char SNOQUOTA;
    char SNOPARTQTY;
    char SDEFERORDER;
    char SSERVICEORDER;
    char SNODD;
    char SONLYEH;
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SALWAYSRESTDEL;
    short STOCKRESERVATION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGART ******************************/

struct I_KDAUFTRAGART {
    short KDAUFTRAGART;
    short AUFTRAGARTTYP;
    short BEZEICHNUNG;
    short VALUTAMONATE;
    short SKDAUFTRAGARTNATRA;
    short SKDAUFTRAGARTNETTO;
    short SKDAUFTRAGARTBANR;
    short SKDAUFTRAGARTMONAT;
    short SKDAUFTRAGVERBUND;
    short SKDAUFTRAGARTVALS;
    short SGLOBAL;
    short SBILDSCHIRM;
    short SDAFUE;
    short SSTANDARD;
    short BRANCHNO;
    short DISINKINDENTERABLE;
    short SDISCOUNTABLE;
    short SMUSTSUBORDER;
    short SFREEPRICE;
    short SORDERCONS;
    short SRESTDEL;
    short SNOQUOTA;
    short SNOPARTQTY;
    short SDEFERORDER;
    short SSERVICEORDER;
    short SNODD;
    short SONLYEH;
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SALWAYSRESTDEL;
    short STOCKRESERVATION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGART ****************************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGART_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGART_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  1, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGART **********************************/

 #define KDAUFTRAGART_S390 \
         char KDAUFTRAGART[3]; \
         long AUFTRAGARTTYP; \
         char BEZEICHNUNG[31]; \
         long VALUTAMONATE; \
         char SKDAUFTRAGARTNATRA; \
         char SKDAUFTRAGARTNETTO; \
         char SKDAUFTRAGARTBANR; \
         char SKDAUFTRAGARTMONAT; \
         char SKDAUFTRAGVERBUND; \
         char SKDAUFTRAGARTVALS; \
         char SGLOBAL; \
         char SBILDSCHIRM; \
         char SDAFUE; \
         char SSTANDARD; \
         short BRANCHNO; \
         char DISINKINDENTERABLE; \
         char SDISCOUNTABLE; \
         char SMUSTSUBORDER; \
         char SFREEPRICE; \
         char SORDERCONS; \
         char SRESTDEL; \
         char SNOQUOTA; \
         char SNOPARTQTY; \
         char SDEFERORDER; \
         char SSERVICEORDER; \
         char SNODD; \
         char SONLYEH; \
         short SNOPROMOTIONS; \
         short SDEFAULTKENNUNG; \
         short SALWAYSRESTDEL; \
		 short STOCKRESERVATION; \



/* Copy-Function Struct to single Data KDAUFTRAGART ***************************/

 #define KDAUFTRAGART_S390_COPY_TO_SINGLE(_x_) \
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         AUFTRAGARTTYP=_x_->AUFTRAGARTTYP;\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         VALUTAMONATE=_x_->VALUTAMONATE;\
         SKDAUFTRAGARTNATRA=_x_->SKDAUFTRAGARTNATRA;\
         SKDAUFTRAGARTNETTO=_x_->SKDAUFTRAGARTNETTO;\
         SKDAUFTRAGARTBANR=_x_->SKDAUFTRAGARTBANR;\
         SKDAUFTRAGARTMONAT=_x_->SKDAUFTRAGARTMONAT;\
         SKDAUFTRAGVERBUND=_x_->SKDAUFTRAGVERBUND;\
         SKDAUFTRAGARTVALS=_x_->SKDAUFTRAGARTVALS;\
         SGLOBAL=_x_->SGLOBAL;\
         SBILDSCHIRM=_x_->SBILDSCHIRM;\
         SDAFUE=_x_->SDAFUE;\
         SSTANDARD=_x_->SSTANDARD;\
         BRANCHNO=_x_->BRANCHNO;\
         DISINKINDENTERABLE=_x_->DISINKINDENTERABLE;\
         SDISCOUNTABLE=_x_->SDISCOUNTABLE;\
         SMUSTSUBORDER=_x_->SMUSTSUBORDER;\
         SFREEPRICE=_x_->SFREEPRICE;\
         SORDERCONS=_x_->SORDERCONS;\
         SRESTDEL=_x_->SRESTDEL;\
         SNOQUOTA=_x_->SNOQUOTA;\
         SNOPARTQTY=_x_->SNOPARTQTY;\
         SDEFERORDER=_x_->SDEFERORDER;\
         SSERVICEORDER=_x_->SSERVICEORDER;\
         SNODD=_x_->SNODD;\
         SONLYEH=_x_->SONLYEH;\
         SNOPROMOTIONS=_x_->SNOPROMOTIONS;\
         SDEFAULTKENNUNG=_x_->SDEFAULTKENNUNG;\
         SALWAYSRESTDEL=_x_->SALWAYSRESTDEL;\
		 STOCKRESERVATION=_x_->STOCKRESERVATION;\

 #define KDAUFTRAGART_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->AUFTRAGARTTYP=AUFTRAGARTTYP;\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->VALUTAMONATE=VALUTAMONATE;\
          _x_->SKDAUFTRAGARTNATRA=SKDAUFTRAGARTNATRA;\
          _x_->SKDAUFTRAGARTNETTO=SKDAUFTRAGARTNETTO;\
          _x_->SKDAUFTRAGARTBANR=SKDAUFTRAGARTBANR;\
          _x_->SKDAUFTRAGARTMONAT=SKDAUFTRAGARTMONAT;\
          _x_->SKDAUFTRAGVERBUND=SKDAUFTRAGVERBUND;\
          _x_->SKDAUFTRAGARTVALS=SKDAUFTRAGARTVALS;\
          _x_->SGLOBAL=SGLOBAL;\
          _x_->SBILDSCHIRM=SBILDSCHIRM;\
          _x_->SDAFUE=SDAFUE;\
          _x_->SSTANDARD=SSTANDARD;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DISINKINDENTERABLE=DISINKINDENTERABLE;\
          _x_->SDISCOUNTABLE=SDISCOUNTABLE;\
          _x_->SMUSTSUBORDER=SMUSTSUBORDER;\
          _x_->SFREEPRICE=SFREEPRICE;\
          _x_->SORDERCONS=SORDERCONS;\
          _x_->SRESTDEL=SRESTDEL;\
          _x_->SNOQUOTA=SNOQUOTA;\
          _x_->SNOPARTQTY=SNOPARTQTY;\
          _x_->SDEFERORDER=SDEFERORDER;\
          _x_->SSERVICEORDER=SSERVICEORDER;\
          _x_->SNODD=SNODD;\
          _x_->SONLYEH=SONLYEH;\
          _x_->SNOPROMOTIONS=SNOPROMOTIONS;\
          _x_->SDEFAULTKENNUNG=SDEFAULTKENNUNG;\
          _x_->SALWAYSRESTDEL=SALWAYSRESTDEL;\
		  _x_->STOCKRESERVATION=STOCKRESERVATION;\



/* FunctionNumber-Define of kdauftragart **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragart **********************************/


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
void FehlerBehandlung(int rc, const char * const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual {
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

class CKDAUFTRAGART : public ppDadeVirtual {
public:
    kdauftragartS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragartS> lst; // class list

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
                     vector< kdauftragartS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragartS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragartS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragartS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragartS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    long         GetAuftragarttyp() const { return s.AUFTRAGARTTYP; }
    const char*  GetBezeichnung(ppString & t) const { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
    long         GetValutamonate() const { return s.VALUTAMONATE; }
    char         GetSkdauftragartnatra() const { return s.SKDAUFTRAGARTNATRA[0]; }
    char         GetSkdauftragartnetto() const { return s.SKDAUFTRAGARTNETTO[0]; }
    char         GetSkdauftragartbanr() const { return s.SKDAUFTRAGARTBANR[0]; }
    char         GetSkdauftragartmonat() const { return s.SKDAUFTRAGARTMONAT[0]; }
    char         GetSkdauftragverbund() const { return s.SKDAUFTRAGVERBUND[0]; }
    char         GetSkdauftragartvals() const { return s.SKDAUFTRAGARTVALS[0]; }
    char         GetSglobal() const { return s.SGLOBAL[0]; }
    char         GetSbildschirm() const { return s.SBILDSCHIRM[0]; }
    char         GetSdafue() const { return s.SDAFUE[0]; }
    char         GetSstandard() const { return s.SSTANDARD[0]; }
    short        GetBranchno() const { return s.BRANCHNO; }
    char         GetDisinkindenterable() const { return s.DISINKINDENTERABLE[0]; }
    char         GetSdiscountable() const { return s.SDISCOUNTABLE[0]; }
    char         GetSmustsuborder() const { return s.SMUSTSUBORDER[0]; }
    char         GetSfreeprice() const { return s.SFREEPRICE[0]; }
    char         GetSordercons() const { return s.SORDERCONS[0]; }
    char         GetSrestdel() const { return s.SRESTDEL[0]; }
    char         GetSnoquota() const { return s.SNOQUOTA[0]; }
    char         GetSnopartqty() const { return s.SNOPARTQTY[0]; }
    char         GetSdeferorder() const { return s.SDEFERORDER[0]; }
    char         GetSserviceorder() const { return s.SSERVICEORDER[0]; }
    char         GetSnodd() const { return s.SNODD[0]; }
    char         GetSonlyeh() const { return s.SONLYEH[0]; }
    short        GetSnopromotions() const { return s.SNOPROMOTIONS; }
    short        GetSdefaultkennung() const { return s.SDEFAULTKENNUNG; }
    short        GetSalwaysrestdel() const { return s.SALWAYSRESTDEL; }
    short        GetStockreservation() const { return s.STOCKRESERVATION; }

    const kdauftragartS &
                 GetStruct() const { return s; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_KDAUFTRAGART_KDAUFTRAGART); }
    void         SetAuftragarttyp(long t) { s.AUFTRAGARTTYP = t; }
    void         SetBezeichnung(const ppString & t) { ppGStrCopy(s.BEZEICHNUNG, t.c_str(), L_KDAUFTRAGART_BEZEICHNUNG); }
    void         SetValutamonate(long t) { s.VALUTAMONATE = t; }
    void         SetSkdauftragartnatra(char t) { s.SKDAUFTRAGARTNATRA[0] = t; s.SKDAUFTRAGARTNATRA[1] = '\0';}
    void         SetSkdauftragartnetto(char t) { s.SKDAUFTRAGARTNETTO[0] = t; s.SKDAUFTRAGARTNETTO[1] = '\0';}
    void         SetSkdauftragartbanr(char t) { s.SKDAUFTRAGARTBANR[0] = t; s.SKDAUFTRAGARTBANR[1] = '\0';}
    void         SetSkdauftragartmonat(char t) { s.SKDAUFTRAGARTMONAT[0] = t; s.SKDAUFTRAGARTMONAT[1] = '\0';}
    void         SetSkdauftragverbund(char t) { s.SKDAUFTRAGVERBUND[0] = t; s.SKDAUFTRAGVERBUND[1] = '\0';}
    void         SetSkdauftragartvals(char t) { s.SKDAUFTRAGARTVALS[0] = t; s.SKDAUFTRAGARTVALS[1] = '\0';}
    void         SetSglobal(char t) { s.SGLOBAL[0] = t; s.SGLOBAL[1] = '\0';}
    void         SetSbildschirm(char t) { s.SBILDSCHIRM[0] = t; s.SBILDSCHIRM[1] = '\0';}
    void         SetSdafue(char t) { s.SDAFUE[0] = t; s.SDAFUE[1] = '\0';}
    void         SetSstandard(char t) { s.SSTANDARD[0] = t; s.SSTANDARD[1] = '\0';}
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDisinkindenterable(char t) { s.DISINKINDENTERABLE[0] = t; s.DISINKINDENTERABLE[1] = '\0';}
    void         SetSdiscountable(char t) { s.SDISCOUNTABLE[0] = t; s.SDISCOUNTABLE[1] = '\0';}
    void         SetSmustsuborder(char t) { s.SMUSTSUBORDER[0] = t; s.SMUSTSUBORDER[1] = '\0';}
    void         SetSfreeprice(char t) { s.SFREEPRICE[0] = t; s.SFREEPRICE[1] = '\0';}
    void         SetSordercons(char t) { s.SORDERCONS[0] = t; s.SORDERCONS[1] = '\0';}
    void         SetSrestdel(char t) { s.SRESTDEL[0] = t; s.SRESTDEL[1] = '\0';}
    void         SetSnoquota(char t) { s.SNOQUOTA[0] = t; s.SNOQUOTA[1] = '\0';}
    void         SetSnopartqty(char t) { s.SNOPARTQTY[0] = t; s.SNOPARTQTY[1] = '\0';}
    void         SetSdeferorder(char t) { s.SDEFERORDER[0] = t; s.SDEFERORDER[1] = '\0';}
    void         SetSserviceorder(char t) { s.SSERVICEORDER[0] = t; s.SSERVICEORDER[1] = '\0';}
    void         SetSnodd(char t) { s.SNODD[0] = t; s.SNODD[1] = '\0';}
    void         SetSonlyeh(char t) { s.SONLYEH[0] = t; s.SONLYEH[1] = '\0';}
    void         SetSnopromotions(short t) { s.SNOPROMOTIONS = t; }
    void         SetSdefaultkennung(short t) { s.SDEFAULTKENNUNG = t; }
    void         SetSalwaysrestdel(short t) { s.SALWAYSRESTDEL = t; }
    void         SetStockreservation(short t) { s.STOCKRESERVATION = t; }

    void         SetStruct(const kdauftragartS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGART() {
        ::buf_default((void *)&s, KDAUFTRAGART_BES, KDAUFTRAGART_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGART() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGART_BES, KDAUFTRAGART_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGART_BES, (int)KDAUFTRAGART_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGART_BES, (int)KDAUFTRAGART_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGART & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.BEZEICHNUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGART_BES, (int)KDAUFTRAGART_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of KDAUFTRAGART *****************************************/

 #define KDAUFTRAGART_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGART char(2) default " " not null,\
         AUFTRAGARTTYP integer default 0 not null,\
         BEZEICHNUNG char(30) default " " not null,\
         VALUTAMONATE integer default 0 not null,\
         SKDAUFTRAGARTNATRA char(1) default " " not null,\
         SKDAUFTRAGARTNETTO char(1) default " " not null,\
         SKDAUFTRAGARTBANR char(1) default " " not null,\
         SKDAUFTRAGARTMONAT char(1) default " " not null,\
         SKDAUFTRAGVERBUND char(1) default " " not null,\
         SKDAUFTRAGARTVALS char(1) default " " not null,\
         SGLOBAL char(1) default " " not null,\
         SBILDSCHIRM char(1) default " " not null,\
         SDAFUE char(1) default " " not null,\
         SSTANDARD char(1) default " " not null,\
         BRANCHNO smallint default 0 not null,\
         DISINKINDENTERABLE char(1) default " " not null,\
         SDISCOUNTABLE char(1) default " " not null,\
         SMUSTSUBORDER char(1) default " " not null,\
         SFREEPRICE char(1) default " " not null,\
         SORDERCONS char(1) default " " not null,\
         SRESTDEL char(1) default " " not null,\
         SNOQUOTA char(1) default " " not null,\
         SNOPARTQTY char(1) default " " not null,\
         SDEFERORDER char(1) default " " not null,\
         SSERVICEORDER char(1) default " " not null,\
         SNODD char(1) default " " not null,\
         SONLYEH char(1) default " " not null,\
         SNOPROMOTIONS smallint default 0 not null,\
         SDEFAULTKENNUNG smallint default 0 not null,\
         SALWAYSRESTDEL smallint default 0 not null,\
         STOCKRESERVATION smallint default 0 not null) in ksc extent size 12 next size 12 lock mode row;



/* CreateIndexStatement of KDAUFTRAGART ***************************************/

 #define KDAUFTRAGART_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index kdauftragartx on _X_(\
              BranchNo,\
              kdauftragart ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGART ***************************************/

 #define KDAUFTRAGART_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index kdauftragartx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
