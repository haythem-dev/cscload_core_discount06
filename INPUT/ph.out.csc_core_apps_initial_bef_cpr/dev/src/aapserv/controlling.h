#ifndef __PP_CONTROLLING_H_
#define __PP_CONTROLLING_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Controlling **/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CHECKDISTRESS *********************************************/

#define L_CHECKDISTRESS_FILIALNR 6

/* Length-Define of CSTSEPORDER ***********************************************/

#define L_CSTSEPORDER_BRANCHNO 6
#define L_CSTSEPORDER_CUSTOMERNO 11
#define L_CSTSEPORDER_ARTGRP 6
#define L_CSTSEPORDER_KDAUFTRAGART 2
#define L_CSTSEPORDER_KOART 1
#define L_CSTSEPORDER_BUCHART 1
#define L_CSTSEPORDER_DEFERORDER 1

/* Length-Define of DEALERUMSATZ **********************************************/

#define L_DEALERUMSATZ_BRANCHNO 6
#define L_DEALERUMSATZ_UID 11
#define L_DEALERUMSATZ_INVOICENO 11
#define L_DEALERUMSATZ_ORDERNOVSE 11
#define L_DEALERUMSATZ_ORDERNOKSC 11
#define L_DEALERUMSATZ_DATEINVOICE 11
#define L_DEALERUMSATZ_TIMEINVOICE 11
#define L_DEALERUMSATZ_INVOICEVOLUME 11
#define N_DEALERUMSATZ_INVOICEVOLUME 2
#define L_DEALERUMSATZ_VOLUME1 11
#define N_DEALERUMSATZ_VOLUME1 2
#define L_DEALERUMSATZ_VOLUME2 11
#define N_DEALERUMSATZ_VOLUME2 2
#define L_DEALERUMSATZ_VOLUME3 11
#define N_DEALERUMSATZ_VOLUME3 2
#define L_DEALERUMSATZ_VOLUME4 11
#define N_DEALERUMSATZ_VOLUME4 2

/* Length-Define of FORBIDDENWORDS ********************************************/

#define L_FORBIDDENWORDS_BRANCHNO 6
#define L_FORBIDDENWORDS_FORBIDDENWORD 240
#define L_FORBIDDENWORDS_DATEFROM 11
#define L_FORBIDDENWORDS_DATETO 11

/* Length-Define of INVOICENUMBER *********************************************/

#define L_INVOICENUMBER_KDAUFTRAGNR 11
#define L_INVOICENUMBER_INVOICENUMBER 15

/* Length-Define of INVOICENUMBEROLD ******************************************/

#define L_INVOICENUMBEROLD_DATUM 11
#define L_INVOICENUMBEROLD_KDAUFTRAGNR 11
#define L_INVOICENUMBEROLD_INVOICENUMBER 15

/* Length-Define of PARAMETER *************************************************/

#define L_PARAMETER_FILIALNR 6
#define L_PARAMETER_PROGRAMMNAME 15
#define L_PARAMETER_ZWECK 20
#define L_PARAMETER_PARAMETERNAME 20
#define L_PARAMETER_AUSPRAEGUNG 254
#define L_PARAMETER_WERT 11

/* Length-Define of SEPORDER **************************************************/

#define L_SEPORDER_BRANCHNO 6
#define L_SEPORDER_NARCOTIC 1
#define L_SEPORDER_COLDCHAIN 1
#define L_SEPORDER_COOL08 1
#define L_SEPORDER_COOL20 1
#define L_SEPORDER_RESERVEHOSPITAL 1
#define L_SEPORDER_DEFERORDER 1

/* Length-Define of SEPORDERGRP ***********************************************/

#define L_SEPORDERGRP_BRANCHNO 6
#define L_SEPORDERGRP_ARTGRP 6
#define L_SEPORDERGRP_KDAUFTRAGART 2
#define L_SEPORDERGRP_KOART 1
#define L_SEPORDERGRP_BUCHART 1
#define L_SEPORDERGRP_DEFERORDER 1
#define L_SEPORDERGRP_MANUFACTURERNO 11

/* Length-Define of TASKCONTROL ***********************************************/

#define L_TASKCONTROL_VERTRIEBSZENTRUMNR 6
#define L_TASKCONTROL_ZEITUNIX 11
#define L_TASKCONTROL_PROGRAMMNAME 15

/* Length-Define of TAXES *****************************************************/

#define L_TAXES_TAXLEVEL 6
#define L_TAXES_SALESTAXRATE 5
#define N_TAXES_SALESTAXRATE 2
#define L_TAXES_DEFAULTTAX 1

/* Length-Define of CUSTOMERORDERCHECK ****************************************/

#define L_CUSTOMERORDERCHECK_BRANCHNO 6
#define L_CUSTOMERORDERCHECK_CUSTOMERNO 11
#define L_CUSTOMERORDERCHECK_CHECKORDERTIME 11
#define L_CUSTOMERORDERCHECK_ORDERSTATUS 6
#define L_CUSTOMERORDERCHECK_NAMEAPO 40
#define L_CUSTOMERORDERCHECK_ORT 30
#define L_CUSTOMERORDERCHECK_POSTLEITZAHL 10
#define L_CUSTOMERORDERCHECK_VERTRIEBSZENTRUMNR 6
#define L_CUSTOMERORDERCHECK_KUNDENNR 11

/* Length-Define of LGTEXT ****************************************************/

#define L_LGTEXT_LGID 2
#define L_LGTEXT_APPID 15
#define L_LGTEXT_GRPID 40
#define L_LGTEXT_TEXTID 40
#define L_LGTEXT_TEXT 240

/* SqlDefine of CHECKDISTRESS *************************************************/


#define CHECKDISTRESS_PLISTE \
        "PARAMETER.FILIALNR"

/* SqlDefine of CSTSEPORDER ***************************************************/


#define CSTSEPORDER_PLISTE \
        "CSTSEPORDERARTGRP.BRANCHNO,"\
        "CSTSEPORDERARTGRP.CUSTOMERNO,"\
        "CSTSEPORDERARTGRP.ARTGRP,"\
        "CSTSEPORDERARTGRP.KDAUFTRAGART,"\
        "CSTSEPORDERARTGRP.KOART,"\
        "CSTSEPORDERARTGRP.BUCHART,"\
        "CSTSEPORDERARTGRP.DEFERORDER"

/* SqlDefine of DEALERUMSATZ **************************************************/


#define DEALERUMSATZ_PLISTE \
        "DEALERVOLUME.BRANCHNO,"\
        "DEALERVOLUME.UID,"\
        "DEALERVOLUME.INVOICENO,"\
        "DEALERVOLUME.ORDERNOVSE,"\
        "DEALERVOLUME.ORDERNOKSC,"\
        "DEALERVOLUME.DATEINVOICE,"\
        "DEALERVOLUME.TIMEINVOICE,"\
        "DEALERVOLUME.INVOICEVOLUME,"\
        "DEALERVOLUME.VOLUME1,"\
        "DEALERVOLUME.VOLUME2,"\
        "DEALERVOLUME.VOLUME3,"\
        "DEALERVOLUME.VOLUME4"

/* SqlDefine of FORBIDDENWORDS ************************************************/


#define FORBIDDENWORDS_PLISTE \
        "FORBIDDENWORDS.BRANCHNO,"\
        "FORBIDDENWORDS.FORBIDDENWORD,"\
        "FORBIDDENWORDS.DATEFROM,"\
        "FORBIDDENWORDS.DATETO"

/* SqlDefine of INVOICENUMBER *************************************************/


#define INVOICENUMBER_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "KDAUFTRAG.INVOICENUMBER"

/* SqlDefine of INVOICENUMBEROLD **********************************************/


#define INVOICENUMBEROLD_PLISTE \
        "AKDAUFTRAG.DATUM,"\
        "AKDAUFTRAG.KDAUFTRAGNR,"\
        "AKDAUFTRAG.INVOICENUMBER"

/* SqlDefine of PARAMETER *****************************************************/


#define PARAMETER_PLISTE \
        "PARAMETER.FILIALNR,"\
        "PARAMETER.PROGRAMMNAME,"\
        "PARAMETER.ZWECK,"\
        "PARAMETER.PARAMETERNAME,"\
        "PARAMETER.AUSPRAEGUNG,"\
        "PARAMETER.WERT"

/* SqlDefine of SEPORDER ******************************************************/


#define SEPORDER_PLISTE \
        "SEPORDERART.BRANCHNO,"\
        "SEPORDERART.NARCOTIC,"\
        "SEPORDERART.COLDCHAIN,"\
        "SEPORDERART.COOL08,"\
        "SEPORDERART.COOL20,"\
        "SEPORDERART.RESERVEHOSPITAL,"\
        "SEPORDERART.DEFERORDER"

/* SqlDefine of SEPORDERGRP ***************************************************/


#define SEPORDERGRP_PLISTE \
        "SEPORDERARTGRP.BRANCHNO,"\
        "SEPORDERARTGRP.ARTGRP,"\
        "SEPORDERARTGRP.KDAUFTRAGART,"\
        "SEPORDERARTGRP.KOART,"\
        "SEPORDERARTGRP.BUCHART,"\
        "SEPORDERARTGRP.DEFERORDER,"\
        "SEPORDERARTGRP.MANUFACTURERNO"

/* SqlDefine of TASKCONTROL ***************************************************/


#define TASKCONTROL_PLISTE \
        "TASKCONTROL.VERTRIEBSZENTRUMNR,"\
        "TASKCONTROL.ZEITUNIX,"\
        "TASKCONTROL.PROGRAMMNAME"

/* SqlDefine of TAXES *********************************************************/


#define TAXES_PLISTE \
        "TAXRATES.TAXLEVEL,"\
        "TAXRATES.SALESTAXRATE,"\
        "TAXRATES.DEFAULTTAX"

/* SqlDefine of CUSTOMERORDERCHECK ********************************************/


#define CUSTOMERORDERCHECK_PLISTE \
        "CUSTOMERORDERCHECK.BRANCHNO,"\
        "CUSTOMERORDERCHECK.CUSTOMERNO,"\
        "CUSTOMERORDERCHECK.CHECKORDERTIME,"\
        "CUSTOMERORDERCHECK.ORDERSTATUS,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.ORT,"\
        "KUNDE.POSTLEITZAHL,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR"

/* SqlDefine of LGTEXT ********************************************************/


#define LGTEXT_PLISTE \
        "LGTEXTAE.LGID,"\
        "LGTEXTAE.APPID,"\
        "LGTEXTAE.GRPID,"\
        "LGTEXTAE.TEXTID,"\
        "LGTEXTAE.TEXT"

/* SqlDefine of CHECKDISTRESS *************************************************/


#define CHECKDISTRESS_UPDLISTE \
        "FILIALNR=?"
/* SqlDefine of CSTSEPORDER ***************************************************/


#define CSTSEPORDER_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ARTGRP=?,"\
        "KDAUFTRAGART=?,"\
        "KOART=?,"\
        "BUCHART=?,"\
        "DEFERORDER=?"
/* SqlDefine of DEALERUMSATZ **************************************************/


#define DEALERUMSATZ_UPDLISTE \
        "BRANCHNO=?,"\
        "UID=?,"\
        "INVOICENO=?,"\
        "ORDERNOVSE=?,"\
        "ORDERNOKSC=?,"\
        "DATEINVOICE=?,"\
        "TIMEINVOICE=?,"\
        "INVOICEVOLUME=?,"\
        "VOLUME1=?,"\
        "VOLUME2=?,"\
        "VOLUME3=?,"\
        "VOLUME4=?"
/* SqlDefine of FORBIDDENWORDS ************************************************/


#define FORBIDDENWORDS_UPDLISTE \
        "BRANCHNO=?,"\
        "FORBIDDENWORD=?,"\
        "DATEFROM=?,"\
        "DATETO=?"
/* SqlDefine of INVOICENUMBER *************************************************/


#define INVOICENUMBER_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "INVOICENUMBER=?"
/* SqlDefine of INVOICENUMBEROLD **********************************************/


#define INVOICENUMBEROLD_UPDLISTE \
        "DATUM=?,"\
        "KDAUFTRAGNR=?,"\
        "INVOICENUMBER=?"
/* SqlDefine of PARAMETER *****************************************************/


#define PARAMETER_UPDLISTE \
        "FILIALNR=?,"\
        "PROGRAMMNAME=?,"\
        "ZWECK=?,"\
        "PARAMETERNAME=?,"\
        "AUSPRAEGUNG=?,"\
        "WERT=?"
/* SqlDefine of SEPORDER ******************************************************/


#define SEPORDER_UPDLISTE \
        "BRANCHNO=?,"\
        "NARCOTIC=?,"\
        "COLDCHAIN=?,"\
        "COOL08=?,"\
        "COOL20=?,"\
        "RESERVEHOSPITAL=?,"\
        "DEFERORDER=?"
/* SqlDefine of SEPORDERGRP ***************************************************/


#define SEPORDERGRP_UPDLISTE \
        "BRANCHNO=?,"\
        "ARTGRP=?,"\
        "KDAUFTRAGART=?,"\
        "KOART=?,"\
        "BUCHART=?,"\
        "DEFERORDER=?,"\
        "MANUFACTURERNO=?"
/* SqlDefine of TASKCONTROL ***************************************************/


#define TASKCONTROL_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "ZEITUNIX=?,"\
        "PROGRAMMNAME=?"
/* SqlDefine of TAXES *********************************************************/


#define TAXES_UPDLISTE \
        "TAXLEVEL=?,"\
        "SALESTAXRATE=?,"\
        "DEFAULTTAX=?"
/* SqlDefine of CUSTOMERORDERCHECK ********************************************/


#define CUSTOMERORDERCHECK_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "CHECKORDERTIME=?,"\
        "ORDERSTATUS=?,"\
        "NAMEAPO=?,"\
        "ORT=?,"\
        "POSTLEITZAHL=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlDefine of LGTEXT ********************************************************/


#define LGTEXT_UPDLISTE \
        "LGID=?,"\
        "APPID=?,"\
        "GRPID=?,"\
        "TEXTID=?,"\
        "TEXT=?"
/* SqlMacros-Define of CHECKDISTRESS ******************************************/

#define CHECKDISTRESS_ZEIGER(x) \
        :x->FILIALNR
#define CHECKDISTRESS_ZEIGERSEL(x) \
        :x->FILIALNR

/* SqlMacros-Define of CSTSEPORDER ********************************************/

#define CSTSEPORDER_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER
#define CSTSEPORDER_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER

/* SqlMacros-Define of DEALERUMSATZ *******************************************/

#define DEALERUMSATZ_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->UID,\
        :x->INVOICENO,\
        :x->ORDERNOVSE,\
        :x->ORDERNOKSC,\
        :x->DATEINVOICE,\
        :x->TIMEINVOICE,\
        :x->INVOICEVOLUME,\
        :x->VOLUME1,\
        :x->VOLUME2,\
        :x->VOLUME3,\
        :x->VOLUME4
#define DEALERUMSATZ_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->UID,\
        :x->INVOICENO,\
        :x->ORDERNOVSE,\
        :x->ORDERNOKSC,\
        :x->DATEINVOICE,\
        :x->TIMEINVOICE,\
        :x->INVOICEVOLUME,\
        :x->VOLUME1,\
        :x->VOLUME2,\
        :x->VOLUME3,\
        :x->VOLUME4

/* SqlMacros-Define of FORBIDDENWORDS *****************************************/

#define FORBIDDENWORDS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->FORBIDDENWORD,\
        :x->DATEFROM,\
        :x->DATETO
#define FORBIDDENWORDS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->FORBIDDENWORD,\
        :x->DATEFROM,\
        :x->DATETO

/* SqlMacros-Define of INVOICENUMBER ******************************************/

#define INVOICENUMBER_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->INVOICENUMBER
#define INVOICENUMBER_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->INVOICENUMBER

/* SqlMacros-Define of INVOICENUMBEROLD ***************************************/

#define INVOICENUMBEROLD_ZEIGER(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->INVOICENUMBER
#define INVOICENUMBEROLD_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->INVOICENUMBER

/* SqlMacros-Define of PARAMETER **********************************************/

#define PARAMETER_ZEIGER(x) \
        :x->FILIALNR,\
        :x->PROGRAMMNAME,\
        :x->ZWECK,\
        :x->PARAMETERNAME,\
        :x->AUSPRAEGUNG,\
        :x->WERT
#define PARAMETER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->PROGRAMMNAME,\
        :x->ZWECK,\
        :x->PARAMETERNAME,\
        :x->AUSPRAEGUNG,\
        :x->WERT

/* SqlMacros-Define of SEPORDER ***********************************************/

#define SEPORDER_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->RESERVEHOSPITAL,\
        :x->DEFERORDER
#define SEPORDER_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->RESERVEHOSPITAL,\
        :x->DEFERORDER

/* SqlMacros-Define of SEPORDERGRP ********************************************/

#define SEPORDERGRP_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER,\
        :x->MANUFACTURERNO
#define SEPORDERGRP_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER,\
        :x->MANUFACTURERNO

/* SqlMacros-Define of TASKCONTROL ********************************************/

#define TASKCONTROL_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->ZEITUNIX,\
        :x->PROGRAMMNAME
#define TASKCONTROL_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->ZEITUNIX,\
        :x->PROGRAMMNAME

/* SqlMacros-Define of TAXES **************************************************/

#define TAXES_ZEIGER(x) \
        :x->TAXLEVEL,\
        :x->SALESTAXRATE,\
        :x->DEFAULTTAX
#define TAXES_ZEIGERSEL(x) \
        :x->TAXLEVEL,\
        :x->SALESTAXRATE,\
        :x->DEFAULTTAX

/* SqlMacros-Define of CUSTOMERORDERCHECK *************************************/

#define CUSTOMERORDERCHECK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->CHECKORDERTIME,\
        :x->ORDERSTATUS,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->POSTLEITZAHL,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define CUSTOMERORDERCHECK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->CHECKORDERTIME,\
        :x->ORDERSTATUS,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->POSTLEITZAHL,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of LGTEXT *************************************************/

#define LGTEXT_ZEIGER(x) \
        :x->LGID,\
        :x->APPID,\
        :x->GRPID,\
        :x->TEXTID,\
        :x->TEXT
#define LGTEXT_ZEIGERSEL(x) \
        :x->LGID,\
        :x->APPID,\
        :x->GRPID,\
        :x->TEXTID,\
        :x->TEXT

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CHECKDISTRESS_H
#define CHECKDISTRESS_ANZ ( sizeof(CHECKDISTRESS_BES) / sizeof(struct buf_desc) )
#define CSTSEPORDER_H
#define CSTSEPORDER_ANZ ( sizeof(CSTSEPORDER_BES) / sizeof(struct buf_desc) )
#define DEALERUMSATZ_H
#define DEALERUMSATZ_ANZ ( sizeof(DEALERUMSATZ_BES) / sizeof(struct buf_desc) )
#define FORBIDDENWORDS_H
#define FORBIDDENWORDS_ANZ ( sizeof(FORBIDDENWORDS_BES) / sizeof(struct buf_desc) )
#define INVOICENUMBER_H
#define INVOICENUMBER_ANZ ( sizeof(INVOICENUMBER_BES) / sizeof(struct buf_desc) )
#define INVOICENUMBEROLD_H
#define INVOICENUMBEROLD_ANZ ( sizeof(INVOICENUMBEROLD_BES) / sizeof(struct buf_desc) )
#define PARAMETER_H
#define PARAMETER_ANZ ( sizeof(PARAMETER_BES) / sizeof(struct buf_desc) )
#define SEPORDER_H
#define SEPORDER_ANZ ( sizeof(SEPORDER_BES) / sizeof(struct buf_desc) )
#define SEPORDERGRP_H
#define SEPORDERGRP_ANZ ( sizeof(SEPORDERGRP_BES) / sizeof(struct buf_desc) )
#define TASKCONTROL_H
#define TASKCONTROL_ANZ ( sizeof(TASKCONTROL_BES) / sizeof(struct buf_desc) )
#define TAXES_H
#define TAXES_ANZ ( sizeof(TAXES_BES) / sizeof(struct buf_desc) )
#define CUSTOMERORDERCHECK_H
#define CUSTOMERORDERCHECK_ANZ ( sizeof(CUSTOMERORDERCHECK_BES) / sizeof(struct buf_desc) )
#define LGTEXT_H
#define LGTEXT_ANZ ( sizeof(LGTEXT_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CHECKDISTRESS *******************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKDISTRESS {
    short FILIALNR;
} checkdistressS;
#else /* TRANSCLASS */
typedef struct N_CHECKDISTRESS {
    short FILIALNR;

    bool operator == (const N_CHECKDISTRESS& right) const {
        return (
            FILIALNR == right.FILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
#endif
    }
} checkdistressS;
#endif /* TRANSCLASS */

/* original struct of CSTSEPORDER *********************************************/

#ifndef TRANSCLASS
typedef struct N_CSTSEPORDER {
    short BRANCHNO;
    long CUSTOMERNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long FETCH_REL;
} cstseporderS;
#else /* TRANSCLASS */
typedef struct N_CSTSEPORDER {
    short BRANCHNO;
    long CUSTOMERNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long FETCH_REL;
    bool operator == (const N_CSTSEPORDER& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ARTGRP == right.ARTGRP &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            !strcmp(DEFERORDER, right.DEFERORDER)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        ARTGRP = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(KOART, " " );
        strcpy(BUCHART, " " );
        strcpy(DEFERORDER, " " );
#endif
    }
} cstseporderS;
#endif /* TRANSCLASS */

/* original struct of DEALERUMSATZ ********************************************/

#ifndef TRANSCLASS
typedef struct N_DEALERUMSATZ {
    short BRANCHNO;
    long UID;
    long INVOICENO;
    long ORDERNOVSE;
    long ORDERNOKSC;
    long DATEINVOICE;
    long TIMEINVOICE;
    double INVOICEVOLUME;
    double VOLUME1;
    double VOLUME2;
    double VOLUME3;
    double VOLUME4;
    long FETCH_REL;
} dealerumsatzS;
#else /* TRANSCLASS */
typedef struct N_DEALERUMSATZ {
    short BRANCHNO;
    long UID;
    long INVOICENO;
    long ORDERNOVSE;
    long ORDERNOKSC;
    long DATEINVOICE;
    long TIMEINVOICE;
    double INVOICEVOLUME;
    double VOLUME1;
    double VOLUME2;
    double VOLUME3;
    double VOLUME4;
    long FETCH_REL;
    bool operator == (const N_DEALERUMSATZ& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            UID == right.UID &&
            INVOICENO == right.INVOICENO &&
            ORDERNOVSE == right.ORDERNOVSE &&
            ORDERNOKSC == right.ORDERNOKSC &&
            DATEINVOICE == right.DATEINVOICE &&
            TIMEINVOICE == right.TIMEINVOICE &&
            INVOICEVOLUME == right.INVOICEVOLUME &&
            VOLUME1 == right.VOLUME1 &&
            VOLUME2 == right.VOLUME2 &&
            VOLUME3 == right.VOLUME3 &&
            VOLUME4 == right.VOLUME4
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        UID = 0;
        INVOICENO = 0;
        ORDERNOVSE = 0;
        ORDERNOKSC = 0;
        DATEINVOICE = 0;
        TIMEINVOICE = 0;
        INVOICEVOLUME = 0;
        VOLUME1 = 0;
        VOLUME2 = 0;
        VOLUME3 = 0;
        VOLUME4 = 0;
#endif
    }
} dealerumsatzS;
#endif /* TRANSCLASS */

/* original struct of FORBIDDENWORDS ******************************************/

#ifndef TRANSCLASS
typedef struct N_FORBIDDENWORDS {
    short BRANCHNO;
    char FORBIDDENWORD[241];
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
} forbiddenwordsS;
#else /* TRANSCLASS */
typedef struct N_FORBIDDENWORDS {
    short BRANCHNO;
    char FORBIDDENWORD[241];
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
    bool operator == (const N_FORBIDDENWORDS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(FORBIDDENWORD, right.FORBIDDENWORD) &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(FORBIDDENWORD, " " );
        DATEFROM = 0;
        DATETO = 0;
#endif
    }
} forbiddenwordsS;
#endif /* TRANSCLASS */

/* original struct of INVOICENUMBER *******************************************/

#ifndef TRANSCLASS
typedef struct N_INVOICENUMBER {
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
} invoicenumberS;
#else /* TRANSCLASS */
typedef struct N_INVOICENUMBER {
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];

    bool operator == (const N_INVOICENUMBER& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(INVOICENUMBER, right.INVOICENUMBER)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(INVOICENUMBER, " " );
#endif
    }
} invoicenumberS;
#endif /* TRANSCLASS */

/* original struct of INVOICENUMBEROLD ****************************************/

#ifndef TRANSCLASS
typedef struct N_INVOICENUMBEROLD {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
} invoicenumberoldS;
#else /* TRANSCLASS */
typedef struct N_INVOICENUMBEROLD {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];

    bool operator == (const N_INVOICENUMBEROLD& right) const {
        return (
            DATUM == right.DATUM &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(INVOICENUMBER, right.INVOICENUMBER)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        KDAUFTRAGNR = 0;
        strcpy(INVOICENUMBER, " " );
#endif
    }
} invoicenumberoldS;
#endif /* TRANSCLASS */

/* original struct of PARAMETER ***********************************************/

#ifndef TRANSCLASS
typedef struct N_PARAMETER {
    short FILIALNR;
    char PROGRAMMNAME[16];
    char ZWECK[21];
    char PARAMETERNAME[21];
    char AUSPRAEGUNG[255];
    long WERT;
    long FETCH_REL;
} parameterS;
#else /* TRANSCLASS */
typedef struct N_PARAMETER {
    short FILIALNR;
    char PROGRAMMNAME[16];
    char ZWECK[21];
    char PARAMETERNAME[21];
    char AUSPRAEGUNG[255];
    long WERT;
    long FETCH_REL;
    bool operator == (const N_PARAMETER& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(PROGRAMMNAME, right.PROGRAMMNAME) &&
            !strcmp(ZWECK, right.ZWECK) &&
            !strcmp(PARAMETERNAME, right.PARAMETERNAME) &&
            !strcmp(AUSPRAEGUNG, right.AUSPRAEGUNG) &&
            WERT == right.WERT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(PROGRAMMNAME, " " );
        strcpy(ZWECK, " " );
        strcpy(PARAMETERNAME, " " );
        strcpy(AUSPRAEGUNG, " " );
        WERT = 0;
#endif
    }
} parameterS;
#endif /* TRANSCLASS */

/* original struct of SEPORDER ************************************************/

#ifndef TRANSCLASS
typedef struct N_SEPORDER {
    short BRANCHNO;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    char RESERVEHOSPITAL[2];
    char DEFERORDER[2];
} seporderS;
#else /* TRANSCLASS */
typedef struct N_SEPORDER {
    short BRANCHNO;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    char RESERVEHOSPITAL[2];
    char DEFERORDER[2];

    bool operator == (const N_SEPORDER& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(NARCOTIC, right.NARCOTIC) &&
            !strcmp(COLDCHAIN, right.COLDCHAIN) &&
            !strcmp(COOL08, right.COOL08) &&
            !strcmp(COOL20, right.COOL20) &&
            !strcmp(RESERVEHOSPITAL, right.RESERVEHOSPITAL) &&
            !strcmp(DEFERORDER, right.DEFERORDER)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(NARCOTIC, " " );
        strcpy(COLDCHAIN, " " );
        strcpy(COOL08, " " );
        strcpy(COOL20, " " );
        strcpy(RESERVEHOSPITAL, " " );
        strcpy(DEFERORDER, " " );
#endif
    }
} seporderS;
#endif /* TRANSCLASS */

/* original struct of SEPORDERGRP *********************************************/

#ifndef TRANSCLASS
typedef struct N_SEPORDERGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long MANUFACTURERNO;
    long FETCH_REL;
} sepordergrpS;
#else /* TRANSCLASS */
typedef struct N_SEPORDERGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long MANUFACTURERNO;
    long FETCH_REL;
    bool operator == (const N_SEPORDERGRP& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            ARTGRP == right.ARTGRP &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            !strcmp(DEFERORDER, right.DEFERORDER) &&
            MANUFACTURERNO == right.MANUFACTURERNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        ARTGRP = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(KOART, " " );
        strcpy(BUCHART, " " );
        strcpy(DEFERORDER, " " );
        MANUFACTURERNO = 0;
#endif
    }
} sepordergrpS;
#endif /* TRANSCLASS */

/* original struct of TASKCONTROL *********************************************/

#ifndef TRANSCLASS
typedef struct N_TASKCONTROL {
    short VERTRIEBSZENTRUMNR;
    long ZEITUNIX;
    char PROGRAMMNAME[16];
    long FETCH_REL;
} taskcontrolS;
#else /* TRANSCLASS */
typedef struct N_TASKCONTROL {
    short VERTRIEBSZENTRUMNR;
    long ZEITUNIX;
    char PROGRAMMNAME[16];
    long FETCH_REL;
    bool operator == (const N_TASKCONTROL& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            ZEITUNIX == right.ZEITUNIX &&
            !strcmp(PROGRAMMNAME, right.PROGRAMMNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        ZEITUNIX = 0;
        strcpy(PROGRAMMNAME, " " );
#endif
    }
} taskcontrolS;
#endif /* TRANSCLASS */

/* original struct of TAXES ***************************************************/

#ifndef TRANSCLASS
typedef struct N_TAXES {
    short TAXLEVEL;
    double SALESTAXRATE;
    char DEFAULTTAX[2];
    long FETCH_REL;
} taxesS;
#else /* TRANSCLASS */
typedef struct N_TAXES {
    short TAXLEVEL;
    double SALESTAXRATE;
    char DEFAULTTAX[2];
    long FETCH_REL;
    bool operator == (const N_TAXES& right) const {
        return (
            TAXLEVEL == right.TAXLEVEL &&
            SALESTAXRATE == right.SALESTAXRATE &&
            !strcmp(DEFAULTTAX, right.DEFAULTTAX)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TAXLEVEL = 0;
        SALESTAXRATE = 0;
        strcpy(DEFAULTTAX, " " );
#endif
    }
} taxesS;
#endif /* TRANSCLASS */

/* original struct of CUSTOMERORDERCHECK **************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERORDERCHECK {
    short BRANCHNO;
    long CUSTOMERNO;
    long CHECKORDERTIME;
    short ORDERSTATUS;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
} customerordercheckS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERORDERCHECK {
    short BRANCHNO;
    long CUSTOMERNO;
    long CHECKORDERTIME;
    short ORDERSTATUS;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
    bool operator == (const N_CUSTOMERORDERCHECK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            CHECKORDERTIME == right.CHECKORDERTIME &&
            ORDERSTATUS == right.ORDERSTATUS &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(POSTLEITZAHL, right.POSTLEITZAHL) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        CHECKORDERTIME = 0;
        ORDERSTATUS = 0;
        strcpy(NAMEAPO, " " );
        strcpy(ORT, " " );
        strcpy(POSTLEITZAHL, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} customerordercheckS;
#endif /* TRANSCLASS */

/* original struct of LGTEXT **************************************************/

#ifndef TRANSCLASS
typedef struct N_LGTEXT {
    char LGID[3];
    char APPID[16];
    char GRPID[41];
    char TEXTID[41];
    char TEXT[241];
    long FETCH_REL;
} lgtextS;
#else /* TRANSCLASS */
typedef struct N_LGTEXT {
    char LGID[3];
    char APPID[16];
    char GRPID[41];
    char TEXTID[41];
    char TEXT[241];
    long FETCH_REL;
    bool operator == (const N_LGTEXT& right) const {
        return (
            !strcmp(LGID, right.LGID) &&
            !strcmp(APPID, right.APPID) &&
            !strcmp(GRPID, right.GRPID) &&
            !strcmp(TEXTID, right.TEXTID) &&
            !strcmp(TEXT, right.TEXT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(LGID, " " );
        strcpy(APPID, " " );
        strcpy(GRPID, " " );
        strcpy(TEXTID, " " );
        strcpy(TEXT, " " );
#endif
    }
} lgtextS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CHECKDISTRESS *******************************/

struct C_CHECKDISTRESS {
    short FILIALNR;
};
/* Structur with real chartype of CSTSEPORDER *********************************/

struct C_CSTSEPORDER {
    short BRANCHNO;
    long CUSTOMERNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART;
    char BUCHART;
    char DEFERORDER;
    long FETCH_REL;
};
/* Structur with real chartype of DEALERUMSATZ ********************************/

struct C_DEALERUMSATZ {
    short BRANCHNO;
    long UID;
    long INVOICENO;
    long ORDERNOVSE;
    long ORDERNOKSC;
    long DATEINVOICE;
    long TIMEINVOICE;
    double INVOICEVOLUME;
    double VOLUME1;
    double VOLUME2;
    double VOLUME3;
    double VOLUME4;
    long FETCH_REL;
};
/* Structur with real chartype of FORBIDDENWORDS ******************************/

struct C_FORBIDDENWORDS {
    short BRANCHNO;
    char FORBIDDENWORD[241];
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
};
/* Structur with real chartype of INVOICENUMBER *******************************/

struct C_INVOICENUMBER {
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
};
/* Structur with real chartype of INVOICENUMBEROLD ****************************/

struct C_INVOICENUMBEROLD {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
};
/* Structur with real chartype of PARAMETER ***********************************/

struct C_PARAMETER {
    short FILIALNR;
    char PROGRAMMNAME[16];
    char ZWECK[21];
    char PARAMETERNAME[21];
    char AUSPRAEGUNG[255];
    long WERT;
    long FETCH_REL;
};
/* Structur with real chartype of SEPORDER ************************************/

struct C_SEPORDER {
    short BRANCHNO;
    char NARCOTIC;
    char COLDCHAIN;
    char COOL08;
    char COOL20;
    char RESERVEHOSPITAL;
    char DEFERORDER;
};
/* Structur with real chartype of SEPORDERGRP *********************************/

struct C_SEPORDERGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART;
    char BUCHART;
    char DEFERORDER;
    long MANUFACTURERNO;
    long FETCH_REL;
};
/* Structur with real chartype of TASKCONTROL *********************************/

struct C_TASKCONTROL {
    short VERTRIEBSZENTRUMNR;
    long ZEITUNIX;
    char PROGRAMMNAME[16];
    long FETCH_REL;
};
/* Structur with real chartype of TAXES ***************************************/

struct C_TAXES {
    short TAXLEVEL;
    double SALESTAXRATE;
    char DEFAULTTAX;
    long FETCH_REL;
};
/* Structur with real chartype of CUSTOMERORDERCHECK **************************/

struct C_CUSTOMERORDERCHECK {
    short BRANCHNO;
    long CUSTOMERNO;
    long CHECKORDERTIME;
    short ORDERSTATUS;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
};
/* Structur with real chartype of LGTEXT **************************************/

struct C_LGTEXT {
    char LGID[3];
    char APPID[16];
    char GRPID[41];
    char TEXTID[41];
    char TEXT[241];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CHECKDISTRESS *****************************/

struct I_CHECKDISTRESS {
    short FILIALNR;
};
/* Sizetype  Structur (buf_desc) of CSTSEPORDER *******************************/

struct I_CSTSEPORDER {
    short BRANCHNO;
    short CUSTOMERNO;
    short ARTGRP;
    short KDAUFTRAGART;
    short KOART;
    short BUCHART;
    short DEFERORDER;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of DEALERUMSATZ ******************************/

struct I_DEALERUMSATZ {
    short BRANCHNO;
    short UID;
    short INVOICENO;
    short ORDERNOVSE;
    short ORDERNOKSC;
    short DATEINVOICE;
    short TIMEINVOICE;
    short INVOICEVOLUME;
    short VOLUME1;
    short VOLUME2;
    short VOLUME3;
    short VOLUME4;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of FORBIDDENWORDS ****************************/

struct I_FORBIDDENWORDS {
    short BRANCHNO;
    short FORBIDDENWORD;
    short DATEFROM;
    short DATETO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of INVOICENUMBER *****************************/

struct I_INVOICENUMBER {
    short KDAUFTRAGNR;
    short INVOICENUMBER;
};
/* Sizetype  Structur (buf_desc) of INVOICENUMBEROLD **************************/

struct I_INVOICENUMBEROLD {
    short DATUM;
    short KDAUFTRAGNR;
    short INVOICENUMBER;
};
/* Sizetype  Structur (buf_desc) of PARAMETER *********************************/

struct I_PARAMETER {
    short FILIALNR;
    short PROGRAMMNAME;
    short ZWECK;
    short PARAMETERNAME;
    short AUSPRAEGUNG;
    short WERT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of SEPORDER **********************************/

struct I_SEPORDER {
    short BRANCHNO;
    short NARCOTIC;
    short COLDCHAIN;
    short COOL08;
    short COOL20;
    short RESERVEHOSPITAL;
    short DEFERORDER;
};
/* Sizetype  Structur (buf_desc) of SEPORDERGRP *******************************/

struct I_SEPORDERGRP {
    short BRANCHNO;
    short ARTGRP;
    short KDAUFTRAGART;
    short KOART;
    short BUCHART;
    short DEFERORDER;
    short MANUFACTURERNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TASKCONTROL *******************************/

struct I_TASKCONTROL {
    short VERTRIEBSZENTRUMNR;
    short ZEITUNIX;
    short PROGRAMMNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TAXES *************************************/

struct I_TAXES {
    short TAXLEVEL;
    short SALESTAXRATE;
    short DEFAULTTAX;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CUSTOMERORDERCHECK ************************/

struct I_CUSTOMERORDERCHECK {
    short BRANCHNO;
    short CUSTOMERNO;
    short CHECKORDERTIME;
    short ORDERSTATUS;
    short NAMEAPO;
    short ORT;
    short POSTLEITZAHL;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of LGTEXT ************************************/

struct I_LGTEXT {
    short LGID;
    short APPID;
    short GRPID;
    short TEXTID;
    short TEXT;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CHECKDISTRESS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKDISTRESS_BES [] = {
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKDISTRESS_BES [] = {
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of CSTSEPORDER *****************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTSEPORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTSEPORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of DEALERUMSATZ ****************************************/

#if defined (BUF_DESC)
static struct buf_desc DEALERUMSATZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DEALERUMSATZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of FORBIDDENWORDS **************************************/

#if defined (BUF_DESC)
static struct buf_desc FORBIDDENWORDS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc FORBIDDENWORDS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of INVOICENUMBER ***************************************/

#if defined (BUF_DESC)
static struct buf_desc INVOICENUMBER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc INVOICENUMBER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
};
#endif

/* Structur (buf_desc) of INVOICENUMBEROLD ************************************/

#if defined (BUF_DESC)
static struct buf_desc INVOICENUMBEROLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc INVOICENUMBEROLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
};
#endif

/* Structur (buf_desc) of PARAMETER *******************************************/

#if defined (BUF_DESC)
static struct buf_desc PARAMETER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PARAMETER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of SEPORDER ********************************************/

#if defined (BUF_DESC)
static struct buf_desc SEPORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SEPORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* Structur (buf_desc) of SEPORDERGRP *****************************************/

#if defined (BUF_DESC)
static struct buf_desc SEPORDERGRP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SEPORDERGRP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TASKCONTROL *****************************************/

#if defined (BUF_DESC)
static struct buf_desc TASKCONTROL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TASKCONTROL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TAXES ***********************************************/

#if defined (BUF_DESC)
static struct buf_desc TAXES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TAXES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CUSTOMERORDERCHECK **********************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERORDERCHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERORDERCHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of LGTEXT **********************************************/

#if defined (BUF_DESC)
static struct buf_desc LGTEXT_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc LGTEXT_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CheckDistress *************************************/

#define CHECKDISTRESS_ISINWORK 1643

/* FunctionNumber-Define of CstSepOrder ***************************************/

#define CSTSEPORDER_DELETE 1461
#define CSTSEPORDER_INSERT 1460
#define CSTSEPORDER_SELLIST 1458
#define CSTSEPORDER_UPDATE 1459

/* FunctionNumber-Define of DealerUmsatz **************************************/

#define DEALERUMSATZ_SELLIST 1484

/* FunctionNumber-Define of ForbiddenWords ************************************/

#define FORBIDDENWORDS_DELETEWORD 1391
#define FORBIDDENWORDS_INSERT 1392
#define FORBIDDENWORDS_SELWORDLIST 1394
#define FORBIDDENWORDS_SELWORDS 1389
#define FORBIDDENWORDS_UPDATEWORD 1390

/* FunctionNumber-Define of InvoiceNumber *************************************/

#define INVOICENUMBER_GETNUMBER 1548

/* FunctionNumber-Define of InvoiceNumberOld **********************************/

#define INVOICENUMBEROLD_GETNUMBER 1549

/* FunctionNumber-Define of Parameter *****************************************/

#define PARAMETER_SELPARAMETER 1770
#define PARAMETER_SELZWECK 1403

/* FunctionNumber-Define of SepOrder ******************************************/

#define SEPORDER_DELETE 1414
#define SEPORDER_INSERT 1413
#define SEPORDER_SEL 1411
#define SEPORDER_UPDATE 1412

/* FunctionNumber-Define of SepOrderGrp ***************************************/

#define SEPORDERGRP_DELETE 1423
#define SEPORDERGRP_INSERT 1424
#define SEPORDERGRP_SEL 1421
#define SEPORDERGRP_UPDATE 1422

/* FunctionNumber-Define of TaskControl ***************************************/

#define TASKCONTROL_CHECKTIMES 1314

/* FunctionNumber-Define of Taxes *********************************************/

#define TAXES_SELLIST 1440

/* FunctionNumber-Define of customerordercheck ********************************/

#define CUSTOMERORDERCHECK_SELLIST 1418

/* FunctionNumber-Define of lgtext ********************************************/

#define LGTEXT_SEL 1333
#define LGTEXT_SETLANGUAGE 1338

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CheckDistress *********************************/

#define IsInWork 1643

/* Old-FunctionNumber-Define of CstSepOrder ***********************************/

#define Delete 1461
#define Insert 1460
#define SelList 1458
#define Update 1459

/* Old-FunctionNumber-Define of DealerUmsatz **********************************/

#define SelList 1484

/* Old-FunctionNumber-Define of ForbiddenWords ********************************/

#define DeleteWord 1391
#define Insert 1392
#define SelWordList 1394
#define SelWords 1389
#define UpdateWord 1390

/* Old-FunctionNumber-Define of InvoiceNumber *********************************/

#define GetNumber 1548

/* Old-FunctionNumber-Define of InvoiceNumberOld ******************************/

#define GetNumber 1549

/* Old-FunctionNumber-Define of Parameter *************************************/

#define SelParameter 1770
#define SelZweck 1403

/* Old-FunctionNumber-Define of SepOrder **************************************/

#define Delete 1414
#define Insert 1413
#define Sel 1411
#define Update 1412

/* Old-FunctionNumber-Define of SepOrderGrp ***********************************/

#define Delete 1423
#define Insert 1424
#define Sel 1421
#define Update 1422

/* Old-FunctionNumber-Define of TaskControl ***********************************/

#define CheckTimes 1314

/* Old-FunctionNumber-Define of Taxes *****************************************/

#define SelList 1440

/* Old-FunctionNumber-Define of customerordercheck ****************************/

#define SelList 1418

/* Old-FunctionNumber-Define of lgtext ****************************************/

#define Sel 1333
#define SetLanguage 1338

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

class CCHECKDISTRESS : public ppDadeVirtual {
public:
    checkdistressS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkdistressS> lst; // class list

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
                     vector< checkdistressS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkdistressS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkdistressS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkdistressS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkdistressS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }

    const checkdistressS &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }

    void         SetStruct(const checkdistressS & t) { s = t; }

    int          IsInWork(int pos = 0) { int ret = UniqueServerCall(1643, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKDISTRESS() {
        ::buf_default((void *)&s, CHECKDISTRESS_BES, CHECKDISTRESS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKDISTRESS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKDISTRESS_BES, CHECKDISTRESS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1643 ) return UniqueServerCall(1643, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKDISTRESS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKDISTRESS_BES, (int)CHECKDISTRESS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCSTSEPORDER : public ppDadeVirtual {
public:
    cstseporderS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstseporderS> lst; // class list

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
                     vector< cstseporderS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstseporderS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstseporderS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstseporderS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstseporderS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetArtgrp() const { return s.ARTGRP; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetBuchart() const { return s.BUCHART[0]; }
    char         GetDeferorder() const { return s.DEFERORDER[0]; }

    const cstseporderS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetArtgrp(short t) { s.ARTGRP = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_CSTSEPORDER_KDAUFTRAGART); }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetDeferorder(char t) { s.DEFERORDER[0] = t; s.DEFERORDER[1] = '\0';}

    void         SetStruct(const cstseporderS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1461, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1460, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1458, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1459, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTSEPORDER() {
        ::buf_default((void *)&s, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTSEPORDER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTSEPORDER_BES, (int)CSTSEPORDER_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1461 ) return UniqueServerCall(1461, pos);
        if ( fkt_nr == 1460 ) return UniqueServerCall(1460, pos);
        if ( fkt_nr == 1458 ) return CursorServerCall(1458, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1459 ) return UniqueServerCall(1459, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTSEPORDER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTSEPORDER_BES, (int)CSTSEPORDER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTSEPORDER c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTSEPORDER_BES, (int)CSTSEPORDER_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CDEALERUMSATZ : public ppDadeVirtual {
public:
    dealerumsatzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<dealerumsatzS> lst; // class list

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
                     vector< dealerumsatzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     dealerumsatzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< dealerumsatzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<dealerumsatzS>::iterator
                 beginList() { return lst.begin(); }
    vector<dealerumsatzS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetUid() const { return s.UID; }
    long         GetInvoiceno() const { return s.INVOICENO; }
    long         GetOrdernovse() const { return s.ORDERNOVSE; }
    long         GetOrdernoksc() const { return s.ORDERNOKSC; }
    long         GetDateinvoice() const { return s.DATEINVOICE; }
    long         GetTimeinvoice() const { return s.TIMEINVOICE; }
    double       GetInvoicevolume() const { return s.INVOICEVOLUME; }
    double       GetVolume1() const { return s.VOLUME1; }
    double       GetVolume2() const { return s.VOLUME2; }
    double       GetVolume3() const { return s.VOLUME3; }
    double       GetVolume4() const { return s.VOLUME4; }

    const dealerumsatzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetInvoiceno(long t) { s.INVOICENO = t; }
    void         SetOrdernovse(long t) { s.ORDERNOVSE = t; }
    void         SetOrdernoksc(long t) { s.ORDERNOKSC = t; }
    void         SetDateinvoice(long t) { s.DATEINVOICE = t; }
    void         SetTimeinvoice(long t) { s.TIMEINVOICE = t; }
    void         SetInvoicevolume(double t) { s.INVOICEVOLUME = t; }
    void         SetVolume1(double t) { s.VOLUME1 = t; }
    void         SetVolume2(double t) { s.VOLUME2 = t; }
    void         SetVolume3(double t) { s.VOLUME3 = t; }
    void         SetVolume4(double t) { s.VOLUME4 = t; }

    void         SetStruct(const dealerumsatzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1484, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDEALERUMSATZ() {
        ::buf_default((void *)&s, DEALERUMSATZ_BES, DEALERUMSATZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDEALERUMSATZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DEALERUMSATZ_BES, DEALERUMSATZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DEALERUMSATZ_BES, (int)DEALERUMSATZ_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1484 ) return CursorServerCall(1484, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DEALERUMSATZ & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DEALERUMSATZ_BES, (int)DEALERUMSATZ_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CDEALERUMSATZ c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DEALERUMSATZ_BES, (int)DEALERUMSATZ_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CFORBIDDENWORDS : public ppDadeVirtual {
public:
    forbiddenwordsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<forbiddenwordsS> lst; // class list

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
                     vector< forbiddenwordsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     forbiddenwordsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< forbiddenwordsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<forbiddenwordsS>::iterator
                 beginList() { return lst.begin(); }
    vector<forbiddenwordsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetForbiddenword(ppString & t) const { t = s.FORBIDDENWORD; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }

    const forbiddenwordsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetForbiddenword(const ppString & t) { ppGStrCopy(s.FORBIDDENWORD, t.c_str(), L_FORBIDDENWORDS_FORBIDDENWORD); }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }

    void         SetStruct(const forbiddenwordsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteWord(int pos = 0) { return UniqueServerCall(1391, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1392, pos); Strip(s); return ret; }
    int          SelWordList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1394, FetchRel, pos); return ret; }
    int          SelWords(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1389, FetchRel, pos); return ret; }
    int          UpdateWord(int pos = 0) { int ret = UniqueServerCall(1390, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CFORBIDDENWORDS() {
        ::buf_default((void *)&s, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CFORBIDDENWORDS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FORBIDDENWORDS_BES, (int)FORBIDDENWORDS_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1391 ) return UniqueServerCall(1391, pos);
        if ( fkt_nr == 1392 ) return UniqueServerCall(1392, pos);
        if ( fkt_nr == 1394 ) return CursorServerCall(1394, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1389 ) return CursorServerCall(1389, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1390 ) return UniqueServerCall(1390, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_FORBIDDENWORDS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.FORBIDDENWORD);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, FORBIDDENWORDS_BES, (int)FORBIDDENWORDS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CFORBIDDENWORDS c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FORBIDDENWORDS_BES, (int)FORBIDDENWORDS_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CINVOICENUMBER : public ppDadeVirtual {
public:
    invoicenumberS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<invoicenumberS> lst; // class list

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
                     vector< invoicenumberS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     invoicenumberS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< invoicenumberS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<invoicenumberS>::iterator
                 beginList() { return lst.begin(); }
    vector<invoicenumberS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetInvoicenumber(ppString & t) const { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }

    const invoicenumberS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetInvoicenumber(const ppString & t) { ppGStrCopy(s.INVOICENUMBER, t.c_str(), L_INVOICENUMBER_INVOICENUMBER); }

    void         SetStruct(const invoicenumberS & t) { s = t; }

    int          GetNumber(int pos = 0) { int ret = UniqueServerCall(1548, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CINVOICENUMBER() {
        ::buf_default((void *)&s, INVOICENUMBER_BES, INVOICENUMBER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CINVOICENUMBER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, INVOICENUMBER_BES, INVOICENUMBER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1548 ) return UniqueServerCall(1548, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_INVOICENUMBER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INVOICENUMBER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, INVOICENUMBER_BES, (int)INVOICENUMBER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CINVOICENUMBEROLD : public ppDadeVirtual {
public:
    invoicenumberoldS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<invoicenumberoldS> lst; // class list

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
                     vector< invoicenumberoldS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     invoicenumberoldS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< invoicenumberoldS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<invoicenumberoldS>::iterator
                 beginList() { return lst.begin(); }
    vector<invoicenumberoldS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetInvoicenumber(ppString & t) const { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }

    const invoicenumberoldS &
                 GetStruct() const { return s; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetInvoicenumber(const ppString & t) { ppGStrCopy(s.INVOICENUMBER, t.c_str(), L_INVOICENUMBEROLD_INVOICENUMBER); }

    void         SetStruct(const invoicenumberoldS & t) { s = t; }

    int          GetNumber(int pos = 0) { int ret = UniqueServerCall(1549, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CINVOICENUMBEROLD() {
        ::buf_default((void *)&s, INVOICENUMBEROLD_BES, INVOICENUMBEROLD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CINVOICENUMBEROLD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, INVOICENUMBEROLD_BES, INVOICENUMBEROLD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1549 ) return UniqueServerCall(1549, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_INVOICENUMBEROLD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INVOICENUMBER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, INVOICENUMBEROLD_BES, (int)INVOICENUMBEROLD_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CPARAMETER : public ppDadeVirtual {
public:
    parameterS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<parameterS> lst; // class list

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
                     vector< parameterS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     parameterS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< parameterS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<parameterS>::iterator
                 beginList() { return lst.begin(); }
    vector<parameterS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetProgrammname(ppString & t) const { t = s.PROGRAMMNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetZweck(ppString & t) const { t = s.ZWECK; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetParametername(ppString & t) const { t = s.PARAMETERNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetAuspraegung(ppString & t) const { t = s.AUSPRAEGUNG; t.erasespace(ppString::END); return t.c_str(); }
    long         GetWert() const { return s.WERT; }

    const parameterS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetProgrammname(const ppString & t) { ppGStrCopy(s.PROGRAMMNAME, t.c_str(), L_PARAMETER_PROGRAMMNAME); }
    void         SetZweck(const ppString & t) { ppGStrCopy(s.ZWECK, t.c_str(), L_PARAMETER_ZWECK); }
    void         SetParametername(const ppString & t) { ppGStrCopy(s.PARAMETERNAME, t.c_str(), L_PARAMETER_PARAMETERNAME); }
    void         SetAuspraegung(const ppString & t) { ppGStrCopy(s.AUSPRAEGUNG, t.c_str(), L_PARAMETER_AUSPRAEGUNG); }
    void         SetWert(long t) { s.WERT = t; }

    void         SetStruct(const parameterS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelParameter(int pos = 0) { int ret = UniqueServerCall(1770, pos); Strip(s); return ret; }
    int          SelZweck(int pos = 0) { int ret = UniqueServerCall(1403, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPARAMETER() {
        ::buf_default((void *)&s, PARAMETER_BES, PARAMETER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPARAMETER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PARAMETER_BES, PARAMETER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_BES, (int)PARAMETER_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1770 ) return UniqueServerCall(1770, pos);
        if ( fkt_nr == 1403 ) return UniqueServerCall(1403, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PARAMETER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PROGRAMMNAME);
        ppGStripLast(d.ZWECK);
        ppGStripLast(d.PARAMETERNAME);
        ppGStripLast(d.AUSPRAEGUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PARAMETER_BES, (int)PARAMETER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPARAMETER c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_BES, (int)PARAMETER_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CSEPORDER : public ppDadeVirtual {
public:
    seporderS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<seporderS> lst; // class list

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
                     vector< seporderS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     seporderS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< seporderS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<seporderS>::iterator
                 beginList() { return lst.begin(); }
    vector<seporderS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    char         GetNarcotic() const { return s.NARCOTIC[0]; }
    char         GetColdchain() const { return s.COLDCHAIN[0]; }
    char         GetCool08() const { return s.COOL08[0]; }
    char         GetCool20() const { return s.COOL20[0]; }
    char         GetReservehospital() const { return s.RESERVEHOSPITAL[0]; }
    char         GetDeferorder() const { return s.DEFERORDER[0]; }

    const seporderS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetNarcotic(char t) { s.NARCOTIC[0] = t; s.NARCOTIC[1] = '\0';}
    void         SetColdchain(char t) { s.COLDCHAIN[0] = t; s.COLDCHAIN[1] = '\0';}
    void         SetCool08(char t) { s.COOL08[0] = t; s.COOL08[1] = '\0';}
    void         SetCool20(char t) { s.COOL20[0] = t; s.COOL20[1] = '\0';}
    void         SetReservehospital(char t) { s.RESERVEHOSPITAL[0] = t; s.RESERVEHOSPITAL[1] = '\0';}
    void         SetDeferorder(char t) { s.DEFERORDER[0] = t; s.DEFERORDER[1] = '\0';}

    void         SetStruct(const seporderS & t) { s = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1414, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1413, pos); Strip(s); return ret; }
    int          Sel(int pos = 0) { int ret = UniqueServerCall(1411, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1412, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSEPORDER() {
        ::buf_default((void *)&s, SEPORDER_BES, SEPORDER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSEPORDER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SEPORDER_BES, SEPORDER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1414 ) return UniqueServerCall(1414, pos);
        if ( fkt_nr == 1413 ) return UniqueServerCall(1413, pos);
        if ( fkt_nr == 1411 ) return UniqueServerCall(1411, pos);
        if ( fkt_nr == 1412 ) return UniqueServerCall(1412, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SEPORDER & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SEPORDER_BES, (int)SEPORDER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CSEPORDERGRP : public ppDadeVirtual {
public:
    sepordergrpS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<sepordergrpS> lst; // class list

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
                     vector< sepordergrpS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     sepordergrpS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< sepordergrpS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<sepordergrpS>::iterator
                 beginList() { return lst.begin(); }
    vector<sepordergrpS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetArtgrp() const { return s.ARTGRP; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetBuchart() const { return s.BUCHART[0]; }
    char         GetDeferorder() const { return s.DEFERORDER[0]; }
    long         GetManufacturerno() const { return s.MANUFACTURERNO; }

    const sepordergrpS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetArtgrp(short t) { s.ARTGRP = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_SEPORDERGRP_KDAUFTRAGART); }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetDeferorder(char t) { s.DEFERORDER[0] = t; s.DEFERORDER[1] = '\0';}
    void         SetManufacturerno(long t) { s.MANUFACTURERNO = t; }

    void         SetStruct(const sepordergrpS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1423, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1424, pos); Strip(s); return ret; }
    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1421, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1422, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSEPORDERGRP() {
        ::buf_default((void *)&s, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSEPORDERGRP() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SEPORDERGRP_BES, (int)SEPORDERGRP_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1423 ) return UniqueServerCall(1423, pos);
        if ( fkt_nr == 1424 ) return UniqueServerCall(1424, pos);
        if ( fkt_nr == 1421 ) return CursorServerCall(1421, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1422 ) return UniqueServerCall(1422, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SEPORDERGRP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SEPORDERGRP_BES, (int)SEPORDERGRP_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CSEPORDERGRP c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SEPORDERGRP_BES, (int)SEPORDERGRP_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CTASKCONTROL : public ppDadeVirtual {
public:
    taskcontrolS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<taskcontrolS> lst; // class list

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
                     vector< taskcontrolS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     taskcontrolS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< taskcontrolS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<taskcontrolS>::iterator
                 beginList() { return lst.begin(); }
    vector<taskcontrolS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetZeitunix() const { return s.ZEITUNIX; }
    const char*  GetProgrammname(ppString & t) const { t = s.PROGRAMMNAME; t.erasespace(ppString::END); return t.c_str(); }

    const taskcontrolS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetZeitunix(long t) { s.ZEITUNIX = t; }
    void         SetProgrammname(const ppString & t) { ppGStrCopy(s.PROGRAMMNAME, t.c_str(), L_TASKCONTROL_PROGRAMMNAME); }

    void         SetStruct(const taskcontrolS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CheckTimes(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1314, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTASKCONTROL() {
        ::buf_default((void *)&s, TASKCONTROL_BES, TASKCONTROL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTASKCONTROL() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TASKCONTROL_BES, TASKCONTROL_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TASKCONTROL_BES, (int)TASKCONTROL_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1314 ) return CursorServerCall(1314, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TASKCONTROL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PROGRAMMNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TASKCONTROL_BES, (int)TASKCONTROL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CTASKCONTROL c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TASKCONTROL_BES, (int)TASKCONTROL_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CTAXES : public ppDadeVirtual {
public:
    taxesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<taxesS> lst; // class list

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
                     vector< taxesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     taxesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< taxesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<taxesS>::iterator
                 beginList() { return lst.begin(); }
    vector<taxesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetTaxlevel() const { return s.TAXLEVEL; }
    double       GetSalestaxrate() const { return s.SALESTAXRATE; }
    char         GetDefaulttax() const { return s.DEFAULTTAX[0]; }

    const taxesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetSalestaxrate(double t) { s.SALESTAXRATE = t; }
    void         SetDefaulttax(char t) { s.DEFAULTTAX[0] = t; s.DEFAULTTAX[1] = '\0';}

    void         SetStruct(const taxesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1440, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTAXES() {
        ::buf_default((void *)&s, TAXES_BES, TAXES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTAXES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TAXES_BES, TAXES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TAXES_BES, (int)TAXES_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1440 ) return CursorServerCall(1440, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TAXES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TAXES_BES, (int)TAXES_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CTAXES c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TAXES_BES, (int)TAXES_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCUSTOMERORDERCHECK : public ppDadeVirtual {
public:
    customerordercheckS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customerordercheckS> lst; // class list

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
                     vector< customerordercheckS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customerordercheckS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customerordercheckS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customerordercheckS>::iterator
                 beginList() { return lst.begin(); }
    vector<customerordercheckS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetCheckordertime() const { return s.CHECKORDERTIME; }
    short        GetOrderstatus() const { return s.ORDERSTATUS; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostleitzahl(ppString & t) const { t = s.POSTLEITZAHL; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const customerordercheckS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetCheckordertime(long t) { s.CHECKORDERTIME = t; }
    void         SetOrderstatus(short t) { s.ORDERSTATUS = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_CUSTOMERORDERCHECK_NAMEAPO); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_CUSTOMERORDERCHECK_ORT); }
    void         SetPostleitzahl(const ppString & t) { ppGStrCopy(s.POSTLEITZAHL, t.c_str(), L_CUSTOMERORDERCHECK_POSTLEITZAHL); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const customerordercheckS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1418, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERORDERCHECK() {
        ::buf_default((void *)&s, CUSTOMERORDERCHECK_BES, CUSTOMERORDERCHECK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERORDERCHECK() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERORDERCHECK_BES, CUSTOMERORDERCHECK_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTOMERORDERCHECK_BES, (int)CUSTOMERORDERCHECK_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1418 ) return CursorServerCall(1418, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CUSTOMERORDERCHECK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.ORT);
        ppGStripLast(d.POSTLEITZAHL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERORDERCHECK_BES, (int)CUSTOMERORDERCHECK_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCUSTOMERORDERCHECK c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTOMERORDERCHECK_BES, (int)CUSTOMERORDERCHECK_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CLGTEXT : public ppDadeVirtual {
public:
    lgtextS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<lgtextS> lst; // class list

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
                     vector< lgtextS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     lgtextS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< lgtextS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<lgtextS>::iterator
                 beginList() { return lst.begin(); }
    vector<lgtextS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetLgid(ppString & t) const { t = s.LGID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetAppid(ppString & t) const { t = s.APPID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetGrpid(ppString & t) const { t = s.GRPID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTextid(ppString & t) const { t = s.TEXTID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetText(ppString & t) const { t = s.TEXT; t.erasespace(ppString::END); return t.c_str(); }

    const lgtextS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetLgid(const ppString & t) { ppGStrCopy(s.LGID, t.c_str(), L_LGTEXT_LGID); }
    void         SetAppid(const ppString & t) { ppGStrCopy(s.APPID, t.c_str(), L_LGTEXT_APPID); }
    void         SetGrpid(const ppString & t) { ppGStrCopy(s.GRPID, t.c_str(), L_LGTEXT_GRPID); }
    void         SetTextid(const ppString & t) { ppGStrCopy(s.TEXTID, t.c_str(), L_LGTEXT_TEXTID); }
    void         SetText(const ppString & t) { ppGStrCopy(s.TEXT, t.c_str(), L_LGTEXT_TEXT); }

    void         SetStruct(const lgtextS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1333, FetchRel, pos); return ret; }
    int          SetLanguage(int pos = 0) { int ret = UniqueServerCall(1338, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CLGTEXT() {
        ::buf_default((void *)&s, LGTEXT_BES, LGTEXT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CLGTEXT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, LGTEXT_BES, LGTEXT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LGTEXT_BES, (int)LGTEXT_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1333 ) return CursorServerCall(1333, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1338 ) return UniqueServerCall(1338, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_LGTEXT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.LGID);
        ppGStripLast(d.APPID);
        ppGStripLast(d.GRPID);
        ppGStripLast(d.TEXTID);
        ppGStripLast(d.TEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, LGTEXT_BES, (int)LGTEXT_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CLGTEXT c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LGTEXT_BES, (int)LGTEXT_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
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
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS

#endif   // GUARD
