#ifndef __PP_AUFTRAGSART_H_
#define __PP_AUFTRAGSART_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of AUFTRAGSART ***********************************************/

#define L_AUFTRAGSART_KDAUFTRAGART 2
#define L_AUFTRAGSART_ALLOWDESIREDBATCH 6
#define L_AUFTRAGSART_ALLOWFIXEDBATCH 6
#define L_AUFTRAGSART_BEZEICHNUNG 30
#define L_AUFTRAGSART_FORBIDUSERCHANGE 6
#define L_AUFTRAGSART_SKDAUFTRAGARTNATRA 1
#define L_AUFTRAGSART_SKDAUFTRAGARTNETTO 1
#define L_AUFTRAGSART_SGLOBAL 1
#define L_AUFTRAGSART_SBILDSCHIRM 1
#define L_AUFTRAGSART_SDAFUE 1
#define L_AUFTRAGSART_SSTANDARD 1
#define L_AUFTRAGSART_BRANCHNO 6
#define L_AUFTRAGSART_DISINKINDENTERABLE 1
#define L_AUFTRAGSART_SDISCOUNTABLE 1
#define L_AUFTRAGSART_SMUSTSUBORDER 1
#define L_AUFTRAGSART_SFREEPRICE 1
#define L_AUFTRAGSART_SORDERCONS 1
#define L_AUFTRAGSART_SRESTDEL 1
#define L_AUFTRAGSART_SNOQUOTA 1
#define L_AUFTRAGSART_SNOPARTQTY 1
#define L_AUFTRAGSART_SDEFERORDER 1
#define L_AUFTRAGSART_SNODD 1
#define L_AUFTRAGSART_SONLYEH 1
#define L_AUFTRAGSART_SNOPROMOTIONS 6
#define L_AUFTRAGSART_SDEFAULTKENNUNG 6
#define L_AUFTRAGSART_SIVCVOUCHERNO 6
#define L_AUFTRAGSART_SORIGINALINVOICENO 6
#define L_AUFTRAGSART_SCONSULTATIONNEEDED 6
#define L_AUFTRAGSART_SNOLINEFEE 6
#define L_AUFTRAGSART_SNOPACKAGEFEE 6
#define L_AUFTRAGSART_SMUSTHEADLINE 6
#define L_AUFTRAGSART_STOCKRESERVATION 1

/* Length/Count-Define of AUFTRAGSART *****************************************/

#define LS_AUFTRAGSART_KDAUFTRAGART 2 + 1
#define LS_AUFTRAGSART_ALLOWDESIREDBATCH 5 + 1
#define LS_AUFTRAGSART_ALLOWFIXEDBATCH 5 + 1
#define LS_AUFTRAGSART_BEZEICHNUNG 30 + 1
#define LS_AUFTRAGSART_FORBIDUSERCHANGE 5 + 1
#define LS_AUFTRAGSART_SKDAUFTRAGARTNATRA 1 + 1
#define LS_AUFTRAGSART_SKDAUFTRAGARTNETTO 1 + 1
#define LS_AUFTRAGSART_SGLOBAL 1 + 1
#define LS_AUFTRAGSART_SBILDSCHIRM 1 + 1
#define LS_AUFTRAGSART_SDAFUE 1 + 1
#define LS_AUFTRAGSART_SSTANDARD 1 + 1
#define LS_AUFTRAGSART_BRANCHNO 5 + 1
#define LS_AUFTRAGSART_DISINKINDENTERABLE 1 + 1
#define LS_AUFTRAGSART_SDISCOUNTABLE 1 + 1
#define LS_AUFTRAGSART_SMUSTSUBORDER 1 + 1
#define LS_AUFTRAGSART_SFREEPRICE 1 + 1
#define LS_AUFTRAGSART_SORDERCONS 1 + 1
#define LS_AUFTRAGSART_SRESTDEL 1 + 1
#define LS_AUFTRAGSART_SNOQUOTA 1 + 1
#define LS_AUFTRAGSART_SNOPARTQTY 1 + 1
#define LS_AUFTRAGSART_SDEFERORDER 1 + 1
#define LS_AUFTRAGSART_SNODD 1 + 1
#define LS_AUFTRAGSART_SONLYEH 1 + 1
#define LS_AUFTRAGSART_SNOPROMOTIONS 5 + 1
#define LS_AUFTRAGSART_SDEFAULTKENNUNG 5 + 1
#define LS_AUFTRAGSART_SIVCVOUCHERNO 5 + 1
#define LS_AUFTRAGSART_SORIGINALINVOICENO 5 + 1
#define LS_AUFTRAGSART_SCONSULTATIONNEEDED 5 + 1
#define LS_AUFTRAGSART_SNOLINEFEE 5 + 1
#define LS_AUFTRAGSART_SNOPACKAGEFEE 5 + 1
#define LS_AUFTRAGSART_SMUSTHEADLINE 5 + 1
#define LS_AUFTRAGSART_STOCKRESERVATION 1 + 1

#define AUFTRAGSARTKDAUFTRAGART 0
#define AUFTRAGSARTALLOWDESIREDBATCH 1
#define AUFTRAGSARTALLOWFIXEDBATCH 2
#define AUFTRAGSARTBEZEICHNUNG 3
#define AUFTRAGSARTFORBIDUSERCHANGE 4
#define AUFTRAGSARTSKDAUFTRAGARTNATRA 5
#define AUFTRAGSARTSKDAUFTRAGARTNETTO 6
#define AUFTRAGSARTSGLOBAL 7
#define AUFTRAGSARTSBILDSCHIRM 8
#define AUFTRAGSARTSDAFUE 9
#define AUFTRAGSARTSSTANDARD 10
#define AUFTRAGSARTBRANCHNO 11
#define AUFTRAGSARTDISINKINDENTERABLE 12
#define AUFTRAGSARTSDISCOUNTABLE 13
#define AUFTRAGSARTSMUSTSUBORDER 14
#define AUFTRAGSARTSFREEPRICE 15
#define AUFTRAGSARTSORDERCONS 16
#define AUFTRAGSARTSRESTDEL 17
#define AUFTRAGSARTSNOQUOTA 18
#define AUFTRAGSARTSNOPARTQTY 19
#define AUFTRAGSARTSDEFERORDER 20
#define AUFTRAGSARTSNODD 21
#define AUFTRAGSARTSONLYEH 22
#define AUFTRAGSARTSNOPROMOTIONS 23
#define AUFTRAGSARTSDEFAULTKENNUNG 24
#define AUFTRAGSARTSIVCVOUCHERNO 25
#define AUFTRAGSARTSORIGINALINVOICENO 26
#define AUFTRAGSARTSCONSULTATIONNEEDED 27
#define AUFTRAGSARTSNOLINEFEE 28
#define AUFTRAGSARTSNOPACKAGEFEE 29
#define AUFTRAGSARTSMUSTHEADLINE 30
#define AUFTRAGSARTSTOCKRESERVATION 31

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define AUFTRAGSART_H
#define AUFTRAGSART_ANZ ( sizeof(AUFTRAGSART_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of AUFTRAGSART ***************************************************/

#define AUFTRAGSART_LISTE \
        KDAUFTRAGART.KDAUFTRAGART,\
        ORDERTYPEBATCHCONFIG.ALLOWDESIREDBATCH,\
        ORDERTYPEBATCHCONFIG.ALLOWFIXEDBATCH,\
        KDAUFTRAGART.BEZEICHNUNG,\
        ORDERTYPEBATCHCONFIG.FORBIDUSERCHANGE,\
        KDAUFTRAGART.SKDAUFTRAGARTNATRA,\
        KDAUFTRAGART.SKDAUFTRAGARTNETTO,\
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
        KDAUFTRAGART.SNODD,\
        KDAUFTRAGART.SONLYEH,\
        KDAUFTRAGART.SNOPROMOTIONS,\
        KDAUFTRAGART.SDEFAULTKENNUNG,\
        KDAUFTRAGART.SIVCVOUCHERNO,\
        KDAUFTRAGART.SORIGINALINVOICENO,\
        KDAUFTRAGART.STOCKRESERVATION,\
        AADUMMY.SCONSULTATIONNEEDED,\
        AADUMMY.SNOLINEFEE,\
        AADUMMY.SNOPACKAGEFEE,\
        AADUMMY.SMUSTHEADLINE
#define AUFTRAGSART_LISTE_390 \
        KDAUFTRAGART,\
        ALLOWDESIREDBATCH,\
        ALLOWFIXEDBATCH,\
        BEZEICHNUNG,\
        FORBIDUSERCHANGE,\
        SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO,\
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
        SNODD,\
        SONLYEH,\
        SNOPROMOTIONS,\
        SDEFAULTKENNUNG,\
        SIVCVOUCHERNO,\
        SORIGINALINVOICENO,\
        SCONSULTATIONNEEDED,\
        SNOLINEFEE,\
        SNOPACKAGEFEE,\
        SMUSTHEADLINE,\
		STOCKRESERVATION
#define AUFTRAGSART_PLISTE \
        "KDAUFTRAGART.KDAUFTRAGART,"\
        "ORDERTYPEBATCHCONFIG.ALLOWDESIREDBATCH,"\
        "ORDERTYPEBATCHCONFIG.ALLOWFIXEDBATCH,"\
        "KDAUFTRAGART.BEZEICHNUNG,"\
        "ORDERTYPEBATCHCONFIG.FORBIDUSERCHANGE,"\
        "KDAUFTRAGART.SKDAUFTRAGARTNATRA,"\
        "KDAUFTRAGART.SKDAUFTRAGARTNETTO,"\
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
        "KDAUFTRAGART.SNODD,"\
        "KDAUFTRAGART.SONLYEH,"\
        "KDAUFTRAGART.SNOPROMOTIONS,"\
        "KDAUFTRAGART.SDEFAULTKENNUNG,"\
        "KDAUFTRAGART.SIVCVOUCHERNO,"\
        "KDAUFTRAGART.SORIGINALINVOICENO,"\
        "KDAUFTRAGART.STOCKRESERVATION,"\
        "AADUMMY.SCONSULTATIONNEEDED,"\
        "AADUMMY.SNOLINEFEE,"\
        "AADUMMY.SNOPACKAGEFEE,"\
        "AADUMMY.SMUSTHEADLINE"
#define AUFTRAGSART_PELISTE \
        "KDAUFTRAGART,"\
        "ALLOWDESIREDBATCH,"\
        "ALLOWFIXEDBATCH,"\
        "BEZEICHNUNG,"\
        "FORBIDUSERCHANGE,"\
        "SKDAUFTRAGARTNATRA,"\
        "SKDAUFTRAGARTNETTO,"\
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
        "SNODD,"\
        "SONLYEH,"\
        "SNOPROMOTIONS,"\
        "SDEFAULTKENNUNG,"\
        "SIVCVOUCHERNO,"\
        "SORIGINALINVOICENO,"\
        "SCONSULTATIONNEEDED,"\
        "SNOLINEFEE,"\
        "SNOPACKAGEFEE,"\
        "SMUSTHEADLINE,"\
		"STOCKRESERVATION"
#define AUFTRAGSART_UPDLISTE \
        "KDAUFTRAGART=?,"\
        "ALLOWDESIREDBATCH=?,"\
        "ALLOWFIXEDBATCH=?,"\
        "BEZEICHNUNG=?,"\
        "FORBIDUSERCHANGE=?,"\
        "SKDAUFTRAGARTNATRA=?,"\
        "SKDAUFTRAGARTNETTO=?,"\
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
        "SNODD=?,"\
        "SONLYEH=?,"\
        "SNOPROMOTIONS=?,"\
        "SDEFAULTKENNUNG=?,"\
        "SIVCVOUCHERNO=?,"\
        "SORIGINALINVOICENO=?,"\
        "SCONSULTATIONNEEDED=?,"\
        "SNOLINEFEE=?,"\
        "SNOPACKAGEFEE=?,"\
        "SMUSTHEADLINE=?,"\
		"STOCKRESERVATION=?"
/* SqlMacros-Define of AUFTRAGSART ********************************************/

#define AUFTRAGSART_ZEIGER(x) \
        :x->KDAUFTRAGART,\
        :x->ALLOWDESIREDBATCH,\
        :x->ALLOWFIXEDBATCH,\
        :x->BEZEICHNUNG,\
        :x->FORBIDUSERCHANGE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
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
        :x->SNODD,\
        :x->SONLYEH,\
        :x->SNOPROMOTIONS,\
        :x->SDEFAULTKENNUNG,\
        :x->SIVCVOUCHERNO,\
        :x->SORIGINALINVOICENO,\
        :x->SCONSULTATIONNEEDED,\
        :x->SNOLINEFEE,\
        :x->SNOPACKAGEFEE,\
        :x->SMUSTHEADLINE,\
		:x->STOCKRESERVATION
#define AUFTRAGSART_ZEIGERSEL(x) \
        :x->KDAUFTRAGART,\
        :x->ALLOWDESIREDBATCH,\
        :x->ALLOWFIXEDBATCH,\
        :x->BEZEICHNUNG,\
        :x->FORBIDUSERCHANGE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
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
        :x->SNODD,\
        :x->SONLYEH,\
        :x->SNOPROMOTIONS,\
        :x->SDEFAULTKENNUNG,\
        :x->SIVCVOUCHERNO,\
        :x->SORIGINALINVOICENO,\
        :x->SCONSULTATIONNEEDED,\
        :x->SNOLINEFEE,\
        :x->SNOPACKAGEFEE,\
        :x->SMUSTHEADLINE,\
		:x->STOCKRESERVATION
#define AUFTRAGSART_UPDATE(x) \
        KDAUFTRAGART.KDAUFTRAGART=:x->KDAUFTRAGART,\
        ORDERTYPEBATCHCONFIG.ALLOWDESIREDBATCH=:x->ALLOWDESIREDBATCH,\
        ORDERTYPEBATCHCONFIG.ALLOWFIXEDBATCH=:x->ALLOWFIXEDBATCH,\
        KDAUFTRAGART.BEZEICHNUNG=:x->BEZEICHNUNG,\
        ORDERTYPEBATCHCONFIG.FORBIDUSERCHANGE=:x->FORBIDUSERCHANGE,\
        KDAUFTRAGART.SKDAUFTRAGARTNATRA=:x->SKDAUFTRAGARTNATRA,\
        KDAUFTRAGART.SKDAUFTRAGARTNETTO=:x->SKDAUFTRAGARTNETTO,\
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
        KDAUFTRAGART.SNODD=:x->SNODD,\
        KDAUFTRAGART.SONLYEH=:x->SONLYEH,\
        KDAUFTRAGART.SNOPROMOTIONS=:x->SNOPROMOTIONS,\
        KDAUFTRAGART.SDEFAULTKENNUNG=:x->SDEFAULTKENNUNG,\
        KDAUFTRAGART.SIVCVOUCHERNO=:x->SIVCVOUCHERNO,\
        KDAUFTRAGART.SORIGINALINVOICENO=:x->SORIGINALINVOICENO,\
		KDAUFTRAGART.STOCKRESERVATION=:x->STOCKRESERVATION,\
        AADUMMY.SCONSULTATIONNEEDED=:x->SCONSULTATIONNEEDED,\
        AADUMMY.SNOLINEFEE=:x->SNOLINEFEE,\
        AADUMMY.SNOPACKAGEFEE=:x->SNOPACKAGEFEE,\
        AADUMMY.SMUSTHEADLINE=:x->SMUSTHEADLINE
/* SqlMacros390-Define of AUFTRAGSART *****************************************/

#define AUFTRAGSART_ZEIGER_390 \
        :KDAUFTRAGART,\
        :ALLOWDESIREDBATCH,\
        :ALLOWFIXEDBATCH,\
        :BEZEICHNUNG,\
        :FORBIDUSERCHANGE,\
        :SKDAUFTRAGARTNATRA,\
        :SKDAUFTRAGARTNETTO,\
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
        :SNODD,\
        :SONLYEH,\
        :SNOPROMOTIONS,\
        :SDEFAULTKENNUNG,\
        :SIVCVOUCHERNO,\
        :SORIGINALINVOICENO,\
        :SCONSULTATIONNEEDED,\
        :SNOLINEFEE,\
        :SNOPACKAGEFEE,\
        :SMUSTHEADLINE,\
		:STOCKRESERVATION
#define AUFTRAGSART_UPDATE_390 \
        KDAUFTRAGART=:KDAUFTRAGART,\
        ALLOWDESIREDBATCH=:ALLOWDESIREDBATCH,\
        ALLOWFIXEDBATCH=:ALLOWFIXEDBATCH,\
        BEZEICHNUNG=:BEZEICHNUNG,\
        FORBIDUSERCHANGE=:FORBIDUSERCHANGE,\
        SKDAUFTRAGARTNATRA=:SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO=:SKDAUFTRAGARTNETTO,\
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
        SNODD=:SNODD,\
        SONLYEH=:SONLYEH,\
        SNOPROMOTIONS=:SNOPROMOTIONS,\
        SDEFAULTKENNUNG=:SDEFAULTKENNUNG,\
        SIVCVOUCHERNO=:SIVCVOUCHERNO,\
        SORIGINALINVOICENO=:SORIGINALINVOICENO,\
        SCONSULTATIONNEEDED=:SCONSULTATIONNEEDED,\
        SNOLINEFEE=:SNOLINEFEE,\
        SNOPACKAGEFEE=:SNOPACKAGEFEE,\
        SMUSTHEADLINE=:SMUSTHEADLINE,\
		STOCKRESERVATION=:STOCKRESERVATION
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of AUFTRAGSART *********************************************/

#ifndef TRANSCLASS
typedef struct N_AUFTRAGSART {
    char KDAUFTRAGART[3];
    short ALLOWDESIREDBATCH;
    short ALLOWFIXEDBATCH;
    char BEZEICHNUNG[31];
    short FORBIDUSERCHANGE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
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
    char SNODD[2];
    char SONLYEH[2];
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SIVCVOUCHERNO;
    short SORIGINALINVOICENO;
    short SCONSULTATIONNEEDED;
    short SNOLINEFEE;
    short SNOPACKAGEFEE;
    short SMUSTHEADLINE;
    short STOCKRESERVATION;
} auftragsartS;
#else /* TRANSCLASS */
typedef struct N_AUFTRAGSART {
    char KDAUFTRAGART[3];
    short ALLOWDESIREDBATCH;
    short ALLOWFIXEDBATCH;
    char BEZEICHNUNG[31];
    short FORBIDUSERCHANGE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
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
    char SNODD[2];
    char SONLYEH[2];
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SIVCVOUCHERNO;
    short SORIGINALINVOICENO;
    short SCONSULTATIONNEEDED;
    short SNOLINEFEE;
    short SNOPACKAGEFEE;
    short SMUSTHEADLINE;
    short STOCKRESERVATION;

    bool operator == (const N_AUFTRAGSART& right) const {
        return (
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            ALLOWDESIREDBATCH == right.ALLOWDESIREDBATCH &&
            ALLOWFIXEDBATCH == right.ALLOWFIXEDBATCH &&
            !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
            FORBIDUSERCHANGE == right.FORBIDUSERCHANGE &&
            !strcmp(SKDAUFTRAGARTNATRA, right.SKDAUFTRAGARTNATRA) &&
            !strcmp(SKDAUFTRAGARTNETTO, right.SKDAUFTRAGARTNETTO) &&
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
            !strcmp(SNODD, right.SNODD) &&
            !strcmp(SONLYEH, right.SONLYEH) &&
            SNOPROMOTIONS == right.SNOPROMOTIONS &&
            SDEFAULTKENNUNG == right.SDEFAULTKENNUNG &&
            SIVCVOUCHERNO == right.SIVCVOUCHERNO &&
            SORIGINALINVOICENO == right.SORIGINALINVOICENO &&
            SCONSULTATIONNEEDED == right.SCONSULTATIONNEEDED &&
            SNOLINEFEE == right.SNOLINEFEE &&
            SNOPACKAGEFEE == right.SNOPACKAGEFEE &&
            SMUSTHEADLINE == right.SMUSTHEADLINE &&
            STOCKRESERVATION == right.STOCKRESERVATION
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(KDAUFTRAGART, " " );
        ALLOWDESIREDBATCH = 0;
        ALLOWFIXEDBATCH = 0;
        strcpy(BEZEICHNUNG, " " );
        FORBIDUSERCHANGE = 0;
        strcpy(SKDAUFTRAGARTNATRA, " " );
        strcpy(SKDAUFTRAGARTNETTO, " " );
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
        strcpy(SNODD, " " );
        strcpy(SONLYEH, " " );
        SNOPROMOTIONS = 0;
        SDEFAULTKENNUNG = 0;
        SIVCVOUCHERNO = 0;
        SORIGINALINVOICENO = 0;
        SCONSULTATIONNEEDED = 0;
        SNOLINEFEE = 0;
        SNOPACKAGEFEE = 0;
        SMUSTHEADLINE = 0;
        STOCKRESERVATION = 0;
#endif
    }
} auftragsartS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of AUFTRAGSART ***************************************/

struct S_AUFTRAGSART {
    char KDAUFTRAGART[2 + 1];
    char ALLOWDESIREDBATCH[7];
    char ALLOWFIXEDBATCH[7];
    char BEZEICHNUNG[30 + 1];
    char FORBIDUSERCHANGE[7];
    char SKDAUFTRAGARTNATRA[1 + 1];
    char SKDAUFTRAGARTNETTO[1 + 1];
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
    char SNODD[1 + 1];
    char SONLYEH[1 + 1];
    char SNOPROMOTIONS[7];
    char SDEFAULTKENNUNG[7];
    char SIVCVOUCHERNO[7];
    char SORIGINALINVOICENO[7];
    char SCONSULTATIONNEEDED[7];
    char SNOLINEFEE[7];
    char SNOPACKAGEFEE[7];
    char SMUSTHEADLINE[7];
    char STOCKRESERVATION[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of AUFTRAGSART **********************/

struct O_AUFTRAGSART {
    char KDAUFTRAGART[2];
    char ALLOWDESIREDBATCH[7];
    char ALLOWFIXEDBATCH[7];
    char BEZEICHNUNG[30];
    char FORBIDUSERCHANGE[7];
    char SKDAUFTRAGARTNATRA[1];
    char SKDAUFTRAGARTNETTO[1];
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
    char SNODD[1];
    char SONLYEH[1];
    char SNOPROMOTIONS[7];
    char SDEFAULTKENNUNG[7];
    char SIVCVOUCHERNO[7];
    char SORIGINALINVOICENO[7];
    char SCONSULTATIONNEEDED[7];
    char SNOLINEFEE[7];
    char SNOPACKAGEFEE[7];
    char SMUSTHEADLINE[7];
    char STOCKRESERVATION[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of AUFTRAGSART *********************************/

struct C_AUFTRAGSART {
    char KDAUFTRAGART[3];
    short ALLOWDESIREDBATCH;
    short ALLOWFIXEDBATCH;
    char BEZEICHNUNG[31];
    short FORBIDUSERCHANGE;
    char SKDAUFTRAGARTNATRA;
    char SKDAUFTRAGARTNETTO;
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
    char SNODD;
    char SONLYEH;
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SIVCVOUCHERNO;
    short SORIGINALINVOICENO;
    short SCONSULTATIONNEEDED;
    short SNOLINEFEE;
    short SNOPACKAGEFEE;
    short SMUSTHEADLINE;
    short STOCKRESERVATION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of AUFTRAGSART *******************************/

struct I_AUFTRAGSART {
    short KDAUFTRAGART;
    short ALLOWDESIREDBATCH;
    short ALLOWFIXEDBATCH;
    short BEZEICHNUNG;
    short FORBIDUSERCHANGE;
    short SKDAUFTRAGARTNATRA;
    short SKDAUFTRAGARTNETTO;
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
    short SNODD;
    short SONLYEH;
    short SNOPROMOTIONS;
    short SDEFAULTKENNUNG;
    short SIVCVOUCHERNO;
    short SORIGINALINVOICENO;
    short SCONSULTATIONNEEDED;
    short SNOLINEFEE;
    short SNOPACKAGEFEE;
    short SMUSTHEADLINE;
    short STOCKRESERVATION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of AUFTRAGSART *****************************************/

#if defined (BUF_DESC)
static struct buf_desc AUFTRAGSART_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
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
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc AUFTRAGSART_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
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
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  1, 0 },
};
#endif

/* description for datatypes of AUFTRAGSART ***********************************/

 #define AUFTRAGSART_S390 \
         char KDAUFTRAGART[3]; \
         short ALLOWDESIREDBATCH; \
         short ALLOWFIXEDBATCH; \
         char BEZEICHNUNG[31]; \
         short FORBIDUSERCHANGE; \
         char SKDAUFTRAGARTNATRA; \
         char SKDAUFTRAGARTNETTO; \
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
         char SNODD; \
         char SONLYEH; \
         short SNOPROMOTIONS; \
         short SDEFAULTKENNUNG; \
         short SIVCVOUCHERNO; \
         short SORIGINALINVOICENO; \
         short SCONSULTATIONNEEDED; \
         short SNOLINEFEE; \
         short SNOPACKAGEFEE; \
         short SMUSTHEADLINE; \
		 short STOCKRESERVATION; \



/* Copy-Function Struct to single Data AUFTRAGSART ****************************/

 #define AUFTRAGSART_S390_COPY_TO_SINGLE(_x_) \
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         ALLOWDESIREDBATCH=_x_->ALLOWDESIREDBATCH;\
         ALLOWFIXEDBATCH=_x_->ALLOWFIXEDBATCH;\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         FORBIDUSERCHANGE=_x_->FORBIDUSERCHANGE;\
         SKDAUFTRAGARTNATRA=_x_->SKDAUFTRAGARTNATRA;\
         SKDAUFTRAGARTNETTO=_x_->SKDAUFTRAGARTNETTO;\
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
         SNODD=_x_->SNODD;\
         SONLYEH=_x_->SONLYEH;\
         SNOPROMOTIONS=_x_->SNOPROMOTIONS;\
         SDEFAULTKENNUNG=_x_->SDEFAULTKENNUNG;\
         SIVCVOUCHERNO=_x_->SIVCVOUCHERNO;\
         SORIGINALINVOICENO=_x_->SORIGINALINVOICENO;\
         SCONSULTATIONNEEDED=_x_->SCONSULTATIONNEEDED;\
         SNOLINEFEE=_x_->SNOLINEFEE;\
         SNOPACKAGEFEE=_x_->SNOPACKAGEFEE;\
         SMUSTHEADLINE=_x_->SMUSTHEADLINE;\
		 STOCKRESERVATION=_x_->STOCKRESERVATION;\

 #define AUFTRAGSART_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->ALLOWDESIREDBATCH=ALLOWDESIREDBATCH;\
          _x_->ALLOWFIXEDBATCH=ALLOWFIXEDBATCH;\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->FORBIDUSERCHANGE=FORBIDUSERCHANGE;\
          _x_->SKDAUFTRAGARTNATRA=SKDAUFTRAGARTNATRA;\
          _x_->SKDAUFTRAGARTNETTO=SKDAUFTRAGARTNETTO;\
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
          _x_->SNODD=SNODD;\
          _x_->SONLYEH=SONLYEH;\
          _x_->SNOPROMOTIONS=SNOPROMOTIONS;\
          _x_->SDEFAULTKENNUNG=SDEFAULTKENNUNG;\
          _x_->SIVCVOUCHERNO=SIVCVOUCHERNO;\
          _x_->SORIGINALINVOICENO=SORIGINALINVOICENO;\
          _x_->SCONSULTATIONNEEDED=SCONSULTATIONNEEDED;\
          _x_->SNOLINEFEE=SNOLINEFEE;\
          _x_->SNOPACKAGEFEE=SNOPACKAGEFEE;\
          _x_->SMUSTHEADLINE=SMUSTHEADLINE;\
		  _x_->STOCKRESERVATION=STOCKRESERVATION;\



/* FunctionNumber-Define of Auftragsart ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Auftragsart ***********************************/


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

class CAUFTRAGSART : public ppDadeVirtual {
public:
    auftragsartS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<auftragsartS> lst; // class list

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
                     vector< auftragsartS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     auftragsartS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< auftragsartS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<auftragsartS>::iterator
                 beginList() { return lst.begin(); }
    vector<auftragsartS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetAllowdesiredbatch() const { return s.ALLOWDESIREDBATCH; }
    short        GetAllowfixedbatch() const { return s.ALLOWFIXEDBATCH; }
    const char*  GetBezeichnung(ppString & t) const { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
    short        GetForbiduserchange() const { return s.FORBIDUSERCHANGE; }
    char         GetSkdauftragartnatra() const { return s.SKDAUFTRAGARTNATRA[0]; }
    char         GetSkdauftragartnetto() const { return s.SKDAUFTRAGARTNETTO[0]; }
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
    char         GetSnodd() const { return s.SNODD[0]; }
    char         GetSonlyeh() const { return s.SONLYEH[0]; }
    short        GetSnopromotions() const { return s.SNOPROMOTIONS; }
    short        GetSdefaultkennung() const { return s.SDEFAULTKENNUNG; }
    short        GetSivcvoucherno() const { return s.SIVCVOUCHERNO; }
    short        GetSoriginalinvoiceno() const { return s.SORIGINALINVOICENO; }
    short        GetSconsultationneeded() const { return s.SCONSULTATIONNEEDED; }
    short        GetSnolinefee() const { return s.SNOLINEFEE; }
    short        GetSnopackagefee() const { return s.SNOPACKAGEFEE; }
    short        GetSmustheadline() const { return s.SMUSTHEADLINE; }
    short        GetStockreservation() const { return s.STOCKRESERVATION; }

    const auftragsartS &
                 GetStruct() const { return s; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_AUFTRAGSART_KDAUFTRAGART); }
    void         SetAllowdesiredbatch(short t) { s.ALLOWDESIREDBATCH = t; }
    void         SetAllowfixedbatch(short t) { s.ALLOWFIXEDBATCH = t; }
    void         SetBezeichnung(const ppString & t) { ppGStrCopy(s.BEZEICHNUNG, t.c_str(), L_AUFTRAGSART_BEZEICHNUNG); }
    void         SetForbiduserchange(short t) { s.FORBIDUSERCHANGE = t; }
    void         SetSkdauftragartnatra(char t) { s.SKDAUFTRAGARTNATRA[0] = t; s.SKDAUFTRAGARTNATRA[1] = '\0';}
    void         SetSkdauftragartnetto(char t) { s.SKDAUFTRAGARTNETTO[0] = t; s.SKDAUFTRAGARTNETTO[1] = '\0';}
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
    void         SetSnodd(char t) { s.SNODD[0] = t; s.SNODD[1] = '\0';}
    void         SetSonlyeh(char t) { s.SONLYEH[0] = t; s.SONLYEH[1] = '\0';}
    void         SetSnopromotions(short t) { s.SNOPROMOTIONS = t; }
    void         SetSdefaultkennung(short t) { s.SDEFAULTKENNUNG = t; }
    void         SetSivcvoucherno(short t) { s.SIVCVOUCHERNO = t; }
    void         SetSoriginalinvoiceno(short t) { s.SORIGINALINVOICENO = t; }
    void         SetSconsultationneeded(short t) { s.SCONSULTATIONNEEDED = t; }
    void         SetSnolinefee(short t) { s.SNOLINEFEE = t; }
    void         SetSnopackagefee(short t) { s.SNOPACKAGEFEE = t; }
    void         SetSmustheadline(short t) { s.SMUSTHEADLINE = t; }
    void         SetStockreservation(short t) { s.STOCKRESERVATION = t; }

    void         SetStruct(const auftragsartS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CAUFTRAGSART() {
        ::buf_default((void *)&s, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CAUFTRAGSART() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, AUFTRAGSART_BES, (int)AUFTRAGSART_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, AUFTRAGSART_BES, (int)AUFTRAGSART_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_AUFTRAGSART & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.BEZEICHNUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, AUFTRAGSART_BES, (int)AUFTRAGSART_ANZ, error_msg);
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
/* CreateSqlStatement of AUFTRAGSART ******************************************/

 #define AUFTRAGSART_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGART char(2) default " " not null,\
         ALLOWDESIREDBATCH smallint default 0 not null,\
         ALLOWFIXEDBATCH smallint default 0 not null,\
         BEZEICHNUNG char(30) default " " not null,\
         FORBIDUSERCHANGE smallint default 0 not null,\
         SKDAUFTRAGARTNATRA char(1) default " " not null,\
         SKDAUFTRAGARTNETTO char(1) default " " not null,\
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
         SNODD char(1) default " " not null,\
         SONLYEH char(1) default " " not null,\
         SNOPROMOTIONS smallint default 0 not null,\
         SDEFAULTKENNUNG smallint default 0 not null,\
         SIVCVOUCHERNO smallint default 0 not null,\
         SORIGINALINVOICENO smallint default 0 not null,\
         SCONSULTATIONNEEDED smallint default 0 not null,\
         SNOLINEFEE smallint default 0 not null,\
         SNOPACKAGEFEE smallint default 0 not null,\
         SMUSTHEADLINE smallint default 0 not null,\
		 STOCKRESERVATION char(1) default " " not null) extent size 10 next size 10 lock mode row;



/* CreateIndexStatement of AUFTRAGSART ****************************************/

 #define AUFTRAGSART_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index kdauftragartx on _X_(\
              BranchNo,\
              kdauftragart );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of AUFTRAGSART ****************************************/

 #define AUFTRAGSART_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index kdauftragartx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
