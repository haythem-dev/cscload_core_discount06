/* define the keys for browse DW...         and the Primary Keys PK.. */
/*                         and matchcode MC where applicable          */
/*                         and second Key SK where applicable         */
#define DWtdispart   where KDAUFTRAGNR = :recordp->KDAUFTRAGNR
#define PKtdispart   KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and POSNR = :recordp->POSNR
#define DWtartalt    where ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and FILIALNR = :recordp->FILIALNR
#define PKtartalt    ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and ARTIKEL_NR_ALTERN = :recordp->ARTIKEL_NR_ALTERN\
                     and FILIALNR = :recordp->FILIALNR
#define DWtartbpr    where ARTIKEL_NR = :recordp->ARTIKEL_NR
#define PKtartbpr    ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and DATUMGUELTIGAB =  :recordp->DATUMGUELTIGAB
#define DWtartmpr    where ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
#define PKtartmpr    ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and DATUMGUELTIGAB =  :recordp->DATUMGUELTIGAB\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR

#define DWtartlag    where ARTIKEL_NR = :recordp->ARTIKEL_NR

#define PKtartlag    FILIALNR       = :recordp->FILIALNR\
                     and   ARTIKEL_NR      = :recordp->ARTIKEL_NR\
                     and   LAGERBEREICHNR = :recordp->LAGERBEREICHNR\
                     and   LAGERFACHNR    = :recordp->LAGERFACHNR
#define DWtartsek    where ARTIKEL_MC like :matchcode
#define MCtartsek    ARTIKEL_MC
#define PKtartsek    ARTIKEL_NR = :recordp->ARTIKEL_NR
#define DWtartikel   where ARTIKEL_MC like :matchcode
#define MCtartikel   ARTIKEL_MC
#define PKtartikel   ARTIKEL_NR = :recordp->ARTIKEL_NR
#define DWtartvza    where ARTIKEL_NR = :recordp->ARTIKEL_NR
#define PKtartvza    ARTIKEL_NR = :recordp->ARTIKEL_NR\
                     and FILIALNR = :recordp->FILIALNR
#define DWtmartikel  where ARTIKEL_MC like :matchcode
#define MCtmartikel  ARTIKEL_MC
#define PKtmartikel  ARTIKEL_NR = :recordp->ARTIKEL_NR
#define DWtaufart    where BRANCHNO = :recordp->BRANCHNO
#define PKtaufart    BRANCHNO = :recordp->BRANCHNO\
                     and KDAUFTRAGART = :recordp->KDAUFTRAGART
#define MCtaufart    KDAUFTRAGART
#define DWtaufartk   where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR
#define PKtaufartk   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR\
                     and KDAUFTRAGART = :recordp->KDAUFTRAGART
#define DWtauferg    where KDAUFTRAGNR = :recordp->KDAUFTRAGNR
#define PKtauferg    KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and DATUM = :recordp->DATUM\
                     and ZEIT = :recordp->ZEIT
#define DWtaufkom    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
#define MCtaufkom    KDAUFTRAGART
#define PKtaufkom    KDAUFTRAGART = :recordp->KDAUFTRAGART\
                     and BUCHART = :recordp->BUCHART\
                     and KOART = :recordp->KOART\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR

#define DWtbearb     where BENUTZERID like :matchcode
#define MCtbearb     BENUTZERID
#define PKtbearb     PERSONALNR = :recordp->PERSONALNR
#define SKtbearb     BENUTZERID = :recordp->BENUTZERID
#define PKtbucart    BUCHART = :recordp->BUCHART\
                     and BRANCHNO = :recordp->BRANCHNO

#define DWtbucart    where BRANCHNO = :recordp->BRANCHNO
#define PKtfiliale   FILIALNR = :recordp->FILIALNR
#define DWtfiliale
#define PKtkomart    KOART = :recordp->KOART\
                     and BRANCHNO = :recordp->BRANCHNO
#define DWtkomart    where BRANCHNO = :recordp->BRANCHNO
#define DWtkundbet   where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR
#define PKtkundbet   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR\
                     and WEEKDAY  = :recordp->WEEKDAY
#define DWtkunde     where MATCHCODE like :matchcode
#define MCtkunde     MATCHCODE
#define PKtkunde     IDFNR = :recordp->IDFNR\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
#define PKtkundkon   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR
#define DWtkundkon
#define PKtkundkz    VERTRIEBSZENTRUMNR = :rp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :rp->KUNDENNR
#define DWtkundkz    where VERTRIEBSZENTRUMNR = :rp->VERTRIEBSZENTRUMNR\
                     and SKDWARENACHLIEFERN = :rp->SKDWARENACHLIEFERN
#define PKtkundgrp   KDGRUPPE = :recordp->KDGRUPPE
#define DWtkundgrp
#define DWtliefpo    where KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and  POSNR = :recordp->POSNR\
                     and  DATUM >= :recordp->DATUM
#define PKtliefpo    KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and POSNR = :recordp->POSNR\
                     and DATUM = :recordp->DATUM\
                     and POSTYP = :recordp->POSTYP
#define DWtparauf
#define DWtposit     where KDAUFTRAGNR = :rp->KDAUFTRAGNR
#define PKtposit     KDAUFTRAGNR = :rp->KDAUFTRAGNR\
                     and POSNR = :rp->POSNR
#define PKttagtyp    TAGESTYP = :recordp->TAGESTYP
#define DWttagtyp
#define DWttour      where DATUMKOMMI = :recordp->DATUMKOMMI\
                     and FILIALNR = :recordp->FILIALNR
#define PKttour      DATUMKOMMI = :recordp->DATUMKOMMI\
                     and TOURID = :recordp->TOURID\
                     and FILIALNR = :recordp->FILIALNR
#define DWttourpg    where IDFNR = :recordp->IDFNR\
                     and TAGESTYP = :recordp->TAGESTYP
#define PKttourpg    IDFNR = :recordp->IDFNR\
                     and TAGESTYP = :recordp->TAGESTYP\
                     and TOURID = :recordp->TOURID
#define DWttourpt    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR\
                     and DATUMKOMMI = :recordp->DATUMKOMMI
#define PKttourpt    VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR\
                     and DATUMKOMMI = :recordp->DATUMKOMMI\
                     and TOURID = :recordp->TOURID
#define PKtauftrag   KDAUFTRAGNR  = :rp->KDAUFTRAGNR
#define DWtkdkondg   where IDFNR = :recordp->IDFNR\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
#define PKtkdkondg   IDFNR = :recordp->IDFNR\
                     and KONDGRUPPENNR = :recordp->KONDGRUPPENNR
#define DWtkondgrp
#define PKtkondgrp   KONDGRUPPENNR = :recordp->KONDGRUPPENNR

#define DWtfkwarte
#define PKtfkwarte   KDAUFTRAGNR = :recordp->KDAUFTRAGNR

#define DWtgeranrp
#define PKtgeranrp   GERAETEID = :recordp->GERAETEID

#define DWtmodanrp
#define PKtmodanrp   GERAETEID = :recordp->GERAETEID

#define DWtaufbem    where KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and BEMERKUNGSART = :recordp->BEMERKUNGSART
#define PKtaufbem    KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and BEMERKUNGSART = :recordp->BEMERKUNGSART\
                     and BEMERKUNGSNR = :recordp->BEMERKUNGSNR
/* !!! DWtaufbem wird gleichzeitig fuer pxAuftragBemDelete benutzt !!! */

#define DWtaltfil    where FILIALNR = :recordp->FILIALNR
#define PKtaltfil    FILIALNR = :recordp->FILIALNR

#define DWtzeitart   where ZEITART = :recordp->ZEITART\
                     and ZEITSCHLUESSEL = :recordp->ZEITSCHLUESSEL\
                     and WEEKDAY        = :recordp->WEEKDAY\
                     and VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR

#define PKtzeitart   LFDNR =  :recordp->LFDNR

#define DWtaufende   where FILIALNR = :recordp->FILIALNR
#define PKtaufende   FILIALNR = :recordp->FILIALNR\
                     and BATCHSCHREIBEN = :recordp->BATCHSCHREIBEN\
                     and HERKUNFTSFILIALNR = :recordp->HERKUNFTSFILIALNR\
                     and ABSCHLUSSMODUS = :recordp->ABSCHLUSSMODUS\
                     and ABSCHLUSSZEIT = :recordp->ABSCHLUSSZEIT

#define DWtartfil
#define PKtartfil    ARTIKEL_NR = :recordp->ARTIKEL_NR

#define DWtnlprot    where ARTIKEL_NR = :recordp->ARTIKEL_NR\
	                 and KDAUFTRAGNR = :recordp->KDAUFTRAGNR
#define PKtnlprot    ARTIKEL_NR = :recordp->ARTIKEL_NR

#define DWtartacct    BELEGNR = :recordp->BELEGNR\
                     and   IDFNR   = :recordp->IDFNR
#define PKtartacct   LFDNR      = :recordp->LFDNR

#define DWtkdmums
#define PKtkdmums    VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and KUNDENNR = :recordp->KUNDENNR\
                     and JAHR   = :recordp->JAHR\
                     and MONAT  = :recordp->MONAT

#define DWtpartner
#define PKtpartner   FILIALNR = :recordp->FILIALNR

#define DWtmodtab
#define PKtmodtab    FILIALNR = :recordp->FILIALNR

#define DWtverbund
#define PKtverbund   HERKUNFTFILIALE = :recordp->HERKUNFTFILIALE\
                     and KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and FILIALNR    = :recordp->FILIALNR

#define DWtverbpos   where HERKUNFTFILIALE = :recordp->HERKUNFTFILIALE\
                     and KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and FILIALNR    = :recordp->FILIALNR
#define PKtverbpos   HERKUNFTFILIALE = :recordp->HERKUNFTFILIALE\
                     and KDAUFTRAGNR = :recordp->KDAUFTRAGNR\
                     and POSNR       = :recordp->POSNR\
                     and FILIALNR    = :recordp->FILIALNR

#define DWtrechner
#define PKtrechner   FILIALNR = :recordp->FILIALNR


#define DWtreimprt   where ARTIKEL_NR = :recordp->ARTIKEL_NR
#define PKtreimprt   FILIALNR = :recordp->FILIALNR\
                     and ARTIKEL_NR = :recordp->ARTIKEL_NR \
                     and ARTIKEL_NR_ALTERN = :recordp->ARTIKEL_NR_ALTERN

#define DWtverblck
#define PKtverblck   FILIALNR = :recordp->FILIALNR
#define PKtvsedat    FILIALNR = :recordp->FILIALNR\
                     and DATEINR = :recordp->DATEINR
#define DWtaktproz
#define PKtaktproz   PROGRAMMNAME = :recordp->PROGRAMMNAME\
                     and PROGRAMMPARTNER = :recordp->PROGRAMMPARTNER

#define PKtregart    REGIONENTYP = :recordp->REGIONENTYP\
                     and REGIONTEILNR = :recordp->REGIONTEILNR

#define PKtlagrev    FILIALNR = :recordp->FILIALNR\
                     and ARTIKEL_NR = :recordp->ARTIKEL_NR
#define DWtlagrev    where FILIALNR = :recordp->FILIALNR\
                     and ARTIKEL_NR = :recordp->ARTIKEL_NR
#define PKttaskctl   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                     and PROGRAMMNAME = :recordp->PROGRAMMNAME
#define DWttaskctl
#define PKtartnum    EAN = :recordp->EAN

#define DWtartnum    where EAN = :recordp->EAN

#define PKtkdordnr   BRANCHNO = :recordp->BRANCHNO\
                     and CUSTOMERNO = :recordp->CUSTOMERNO\
                     and CUSTOMERORDERNO = :recordp->CUSTOMERORDERNO
#define DWtkdordnr   where BRANCHNO = :recordp->BRANCHNO\
                     and CUSTOMERNO = :recordp->CUSTOMERNO\
                     and ORDERVALUE = :recordp->ORDERVALUE

#define PKtkdaufin   KDAUFTRAGNR  = :recordp->KDAUFTRAGNR

#define DWtkdaufin


#define PKtcustrou   CUSTOMERNO = :recordp->CUSTOMERNO\
                     and BRANCHNO = :recordp->BRANCHNO\
                     and TIMEFROM   = :recordp->TIMEFROM\
                     and WEEKDAY    = :recordp->WEEKDAY
#define DWtcustrou   where CUSTOMERNO = :recordp->CUSTOMERNO\
                     and BRANCHNO = :recordp->BRANCHNO\
                     and WEEKDAY    = :recordp->WEEKDAY

#define PKtcustphg   CUSTOMERNO = :recordp->CUSTOMERNO\
                     and BRANCHNO = :recordp->BRANCHNO\
                     and PHARMACYGROUPID   = :recordp->PHARMACYGROUPID
#define DWtcustphg   where CUSTOMERNO = :recordp->CUSTOMERNO\
                     and BRANCHNO = :recordp->BRANCHNO

#define PKtvaldisc   BRANCHNO = :recordp->BRANCHNO\
                     and ARTICLENO = :recordp->ARTICLENO\
                     and TYPEOFDISCOUNT = :recordp->TYPEOFDISCOUNT\
                     and PHARMACYGROUPID   = :recordp->PHARMACYGROUPID\
                     and DATEFROM = :recordp->DATEFROM
#define DWtvaldisc   where BRANCHNO = :recordp->BRANCHNO\
                     and ARTICLENO = :recordp->ARTICLENO\
                     and TYPEOFDISCOUNT = :recordp->TYPEOFDISCOUNT

#define PKtstkent    DATE = :recordp->DATE\
                     and BRANCHNO = :recordp->BRANCHNO\
                     and ARTICLENO = :recordp->ARTICLENO
#define DWtstkent
#define PKtdebtlim   PARTNERNO = :recordp->PARTNERNO\
                     and LIMITTYPE = :recordp->LIMITTYPE
#define DWtdebtlim

#define PKtartquot   BRANCHNO = :recordp->BRANCHNO\
                     and CUSTOMERNO = :recordp->CUSTOMERNO\
                     and ARTICLENO = :recordp->ARTICLENO\
                     and PHARMACYGROUPID = :recordp->PHARMACYGROUPID

#define DWtartquot   where BRANCHNO = :recordp->BRANCHNO\
                     and CUSTOMERNO = :recordp->CUSTOMERNO\
                     and ARTICLENO = :recordp->ARTICLENO

#define PKtparamet   FILIALNR = :recordp->FILIALNR\
                     and PROGRAMMNAME = :recordp->PROGRAMMNAME\
                     and ZWECK         = :recordp->ZWECK\
                     and PARAMETERNAME = :recordp->PARAMETERNAME

#define DWtparamet   where FILIALNR    = :recordp->FILIALNR\
                     and PROGRAMMNAME  = :recordp->PROGRAMMNAME\
                     and ZWECK         = :recordp->ZWECK\
                     and PARAMETERNAME = :recordp->PARAMETERNAME\
                     and WERT          = :recordp->WERT
#define PKtarttext   TEXTKEY       = :recordp->TEXTKEY

#define DWtarttext

#define PKtddelcst   BRANCHNO          = :recordp->BRANCHNO\
                     and CUSTOMERNO    = :recordp->CUSTOMERNO\
                     and WEEKDAY       = :recordp->WEEKDAY\
                     and ACTIV         = '1'

#define DWtddelcst   where BRANCHNO    = :recordp->BRANCHNO\
                     and CUSTOMERNO    = :recordp->CUSTOMERNO\
                     and WEEKDAY       = :recordp->WEEKDAY\
                     and ACTIV         = '1'

#define PKtholiday   FILIALNR          = :recordp->FILIALNR

#define DWtholiday   where FILIALNR    = :recordp->FILIALNR

#define PKtdiscount  BRANCHNO          = :recordp->BRANCHNO\
                     and ARTICLENO     = :recordp->ARTICLENO\
                     and DISCOUNTGRPNO = :recordp->DISCOUNTGRPNO\
                     and PHARMACYGROUPID = :recordp->PHARMACYGROUPID\
                     and CUSTOMERNO    = :recordp->CUSTOMERNO

#define DWtdiscount            where BRANCHNO    = :recordp->BRANCHNO\
                               and ARTICLENO     = :recordp->ARTICLENO

#define PKtartreservation      BRANCHNO       = :recordp->BRANCHNO\
                               and ARTICLENO  = :recordp->ARTICLENO\
                               and RESERVTYPE = :recordp->RESERVTYPE

#define DWtartreservation      where BRANCHNO      = :recordp->BRANCHNO\
                               and PHARMACYGROUPID = :recordp->PHARMACYGROUPID\
                               and ARTICLENO       = :recordp->ARTICLENO

#define PKtkdauftragposrab     KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                               and POSNR          = :recordp->POSNR\
                               and DISCOUNTTYPE   = :recordp->DISCOUNTTYPE\
                               and PAYMENTTARGETNO = :recordp->PAYMENTTARGETNO

#define DWtkdauftragposrab     where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR\
                               and POSNR          = :recordp->POSNR

#define PKtdiscountgrp         BRANCHNO            = :recordp->BRANCHNO\
                               and DISCOUNTGRPNO   = :recordp->DISCOUNTGRPNO

#define DWtdiscountgrp         where BRANCHNO     = :recordp->BRANCHNO\
                               and DISCOUNTGRPNO  = :recordp->DISCOUNTGRPNO

#define PKtdiscountgrpmem      BRANCHNO           = :recordp->BRANCHNO\
                               and DISCOUNTGRPNO  = :recordp->DISCOUNTGRPNO\
                               and ARTICLENO      = :recordp->ARTICLENO

#define DWtdiscountgrpmem      where BRANCHNO     = :recordp->BRANCHNO\
                               and ARTICLENO      = :recordp->ARTICLENO

#define PKtdiscountordertyp    KDAUFTRAGART = :recordp->KDAUFTRAGART

#define DWtdiscountordertyp    where KDAUFTRAGART = :recordp->KDAUFTRAGART

#define PKtnarctracttrfer      TRANSFERID          = :recordp->TRANSFERID

#define DWtnarctracttrfer      where BRANCHNO     = :recordp->BRANCHNO\
                               and ARTICLENO      = :recordp->ARTICLENO\
                               and ORDERNO        = :recordp->ORDERNO
#define PKtpositionparking     BRANCHNO            = :recordp->BRANCHNO\
                               and CUSTOMERNO      = :recordp->CUSTOMERNO\
                               and ARTICLENO       = :recordp->ARTICLENO

#define DWtpositionparking     where BRANCHNO     = :recordp->BRANCHNO\
                               and CUSTOMERNO     = :recordp->CUSTOMERNO\
                               and ARTICLENO      = :recordp->ARTICLENO

#define PKtarticlepackunit     ARTICLENO          = :recordp->ARTICLENO\
                               and PACKINGUNIT    = :recordp->PACKINGUNIT\
                               and ROUNDPCT       = :recordp->ROUNDPCT

#define DWtarticlepackunit     where ARTICLENO      = :recordp->ARTICLENO

#define PKttourpltwoche        VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                               and   KUNDENNR     = :recordp->KUNDENNR\
                               and   TOURID       = :recordp->TOURID\
                               and   TAGESTYP     = :recordp->TAGESTYP

#define DWttourpltwoche        where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                               and   KUNDENNR           = :recordp->KUNDENNR
#define PKttourconstime        FILIALNR           = :recordp->FILIALNR\
                               and   TOURID       = :recordp->TOURID\
                               and   DATUMKOMMI   = :recordp->DATUMKOMMI\
                               and   CONSTIME     = :recordp->CONSTIME

#define DWttourconstime        where FILIALNR     = :recordp->FILIALNR\
                               and   TOURID       = :recordp->TOURID\
                               and   DATUMKOMMI   = :recordp->DATUMKOMMI                             

#define PKttourplconstime      VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                               and   KUNDENNR     = :recordp->KUNDENNR\
                               and   TOURID       = :recordp->TOURID\
                               and   DATUMKOMMI   = :recordp->DATUMKOMMI\
                               and   CONSTIME     = :recordp->CONSTIME

#define DWttourplconstime      where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR\
                               and   KUNDENNR           = :recordp->KUNDENNR\
                               and   TOURID             = :recordp->TOURID\
                               and   DATUMKOMMI         = :recordp->DATUMKOMMI
                               
#define PKttourplanwoche       FILIALNR           = :recordp->FILIALNR\
                               and   TOURID       = :recordp->TOURID\
                               and   TAGESTYP     = :recordp->TAGESTYP

#define DWttourplanwoche       where FILIALNR     = :recordp->FILIALNR\
                               and   TOURID       = :recordp->TOURID

#define PKtdiscountlist       ORDER_TYPE          = :recordp->ORDER_TYPE\
                              and SUB_ORDER_TYPE  = :recordp->SUB_ORDER_TYPE


#define DWtdiscountlist      where ORDER_TYPE    = :recordp->ORDER_TYPE\
                             and SUB_ORDER_TYPE  = :recordp->SUB_ORDER_TYPE

#define PKtcstdiscountcont   BRANCHNO           = :recordp->BRANCHNO\
                             and CUSTOMERNO     = :recordp->CUSTOMERNO\
                             and ORDER_TYPE     = :recordp->ORDER_TYPE\
                             and SUB_ORDER_TYPE  = :recordp->SUB_ORDER_TYPE


#define DWtcstdiscountcont   where BRANCHNO      = :recordp->BRANCHNO\
                             and CUSTOMERNO      = :recordp->CUSTOMERNO\
                             and ORDER_TYPE      = :recordp->ORDER_TYPE

#define PKttaxrates          TAXLEVEL            = :recordp->TAXLEVEL

#define DWttaxrates

#define PKtseporderartgrp    BRANCHNO            = :recordp->BRANCHNO\
                             and ARTGRP          = :recordp->ARTGRP

#define DWtseporderartgrp    where BRANCHNO      = :recordp->BRANCHNO

#define PKtarticleoldprice   BRANCHNO            = :recordp->BRANCHNO\
                             and ARTICLENO       = :recordp->ARTICLENO

#define DWtarticleoldprice   where BRANCHNO      = :recordp->BRANCHNO\
                             and ARTICLENO       = :recordp->ARTICLENO

#define PKtcountrycodes      BRANCHNO            = :recordp->BRANCHNO\
                             and INFOCODE        = :recordp->INFOCODE

#define DWtcountrycodes      where BRANCHNO      = :recordp->BRANCHNO\
                             and INFOCODE        = :recordp->INFOCODE

#define PKtarticlelppr       ARTICLENO           = :recordp->ARTICLENO\
                             and  REIMBURSEMENT_TYPE = :recordp->REIMBURSEMENT_TYPE

#define DWtarticlelppr       where ARTICLENO     = :recordp->ARTICLENO\
                             and  REIMBURSEMENT_TYPE = :recordp->REIMBURSEMENT_TYPE

#define PKtordercriteria    BRANCHNO            = :recordp->BRANCHNO\
                            and ARTICLENO           = :recordp->ARTICLENO
#define DWtordercriteria    where BRANCHNO    = :recordp->BRANCHNO\
                            and ARTICLENO     = :recordp->ARTICLENO

#define PKtkundeausku       VERTRIEBSZENTRUMNR  = :recordp->VERTRIEBSZENTRUMNR\
                            and KUNDENNR        = :recordp->KUNDENNR

#define DWtkundeausku       where VERTRIEBSZENTRUMNR    = :recordp->VERTRIEBSZENTRUMNR\
                            and KUNDENNR                = :recordp->KUNDENNR

#define PKtclearwafo        ORDERDATE           = :recordp->ORDERDATE\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                            and ARTICLENO           = :recordp->ARTICLENO\
                            and POSNR               = :recordp->POSNR\
                            and VERTRIEBSZENTRUMNR  = :recordp->VERTRIEBSZENTRUMNR

#define DWtclearwafo        where  ORDERDATE        = :recordp->ORDERDATE\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                            and ARTICLENO           = :recordp->ARTICLENO\
                            and POSNR               = :recordp->POSNR\
                            and VERTRIEBSZENTRUMNR  = :recordp->VERTRIEBSZENTRUMNR

#define PKtcstsepordartgrp  BRANCHNO                = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO\
                            and ARTGRP              = :recordp->ARTGRP

#define DWtcstsepordartgrp  where  BRANCHNO         = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO

#define PKtarticlegrp       ARTICLENO               = :recordp->ARTICLENO

#define DWtarticlegrp       where ARTICLENO         = :recordp->ARTICLENO

#define PKtartcompack       ARTICLE_NO_PACK         = :recordp->ARTICLE_NO_PACK\
                            and ARTICLE_NO_ELEMENT  = :recordp->ARTICLE_NO_ELEMENT

#define DWtartcompack       where ARTICLE_NO_PACK   = :recordp->ARTICLE_NO_PACK

#define PKtcstdiscacc       BRANCHNO                = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO\
                            and DATE                = :recordp->DATE\
                            and INVOICENUMBER       = :recordp->INVOICENUMBER\
                            and VOUCHERTYP          = :recordp->VOUCHERTYP

#define DWtcstdiscacc       where  BRANCHNO         = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO\
                            and DATE                = :recordp->DATE

#define PKtdealervolume     BRANCHNO                = :recordp->BRANCHNO\
                            and UID                 = :recordp->UID\
                            and DATEINVOICE         = :recordp->DATEINVOICE\
                            and INVOICENO           = :recordp->INVOICENO

#define DWtdealervolume     where  BRANCHNO         = :recordp->BRANCHNO\
                            and    UID              = :recordp->UID

#define PKtcpvalidperiod    ARTICLE_NO_PACK         = :recordp->ARTICLE_NO_PACK

#define DWtcpvalidperiod    where ARTICLE_NO_PACK   = :recordp->ARTICLE_NO_PACK

#define PKttenderpos        TENDERNO                = :recordp->TENDERNO\
                            and ARTICLENO           = :recordp->ARTICLENO

#define DWttenderpos        where TENDERNO          = :recordp->TENDERNO\
                            and   ARTICLENO         = :recordp->ARTICLENO

#define PKttenderprogress   TENDERNO                = :recordp->TENDERNO\
                            and ARTICLENO           = :recordp->ARTICLENO\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                            and ORDERDATE           = :recordp->ORDERDATE\
                            and POSNR               = :recordp->POSNR

#define DWttenderprogress   where TENDERNO          = :recordp->TENDERNO\
                            and   ARTICLENO         = :recordp->ARTICLENO\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                            and ORDERDATE           = :recordp->ORDERDATE
#define DWtartmasfr         where ARTIKEL_MC like :matchcode
#define MCtartmasfr         ARTIKEL_MC
#define PKtartmasfr         ARTIKEL_NR = :recordp->ARTIKEL_NR

#define PKtkdaufdiscacc     BRANCHNO                = :recordp->BRANCHNO\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR

#define DWtkdaufdiscacc     where BRANCHNO          = :recordp->BRANCHNO\
                            and KDAUFTRAGNR         = :recordp->KDAUFTRAGNR
#define PKtartspecialcond   ARTICLENO               = :recordp->ARTICLENO

#define DWtartspecialcond   where ARTICLENO         = :recordp->ARTICLENO

#define PKtpromotions       PROMOTION_NO            = :recordp->PROMOTION_NO

#define DWtpromotions       where PROMOTION_NO      = :recordp->PROMOTION_NO

#define PKtservices         SERVICE_NO              = :recordp->SERVICE_NO

#define DWtservices         where SERVICE_NO        = :recordp->SERVICE_NO

#define PKtservicetypes     SERVICETYPENO           = :recordp->SERVICETYPENO

#define DWtservicetypes     where SERVICETYPENO     = :recordp->SERVICETYPENO

#define PKtcstpaymentterms  BRANCHNO                = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO\
                            and PREIS_TYP           = :recordp->PREIS_TYP
#define DWtcstpaymentterms  where BRANCHNO          = :recordp->BRANCHNO\
                            and CUSTOMERNO          = :recordp->CUSTOMERNO

#define PKtkdauftragwerte   KDAUFTRAGNR             = :recordp->KDAUFTRAGNR
#define DWtkdauftragwerte   where KDAUFTRAGNR       = :recordp->KDAUFTRAGNR

#define PKtkdauftragposcharge   KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                                and POSNR           = :recordp->POSNR
#define DWtkdauftragposcharge   where KDAUFTRAGNR   = :recordp->KDAUFTRAGNR\
                                and POSNR           = :recordp->POSNR
#define PKtarticlecharge    BRANCHNO                = :recordp->BRANCHNO\
                            and ARTICLENO           = :recordp->ARTICLENO\
                            and CHARGENNR           = :recordp->CHARGENNR
#define DWtarticlecharge    where BRANCHNO          = :recordp->BRANCHNO\
                            and ARTICLENO           = :recordp->ARTICLENO

#define PKtkdauftragrechart KDAUFTRAGNR             = :recordp->KDAUFTRAGNR
#define DWtkdauftragrechart where KDAUFTRAGNR       = :recordp->KDAUFTRAGNR

#define PKtkdauftrposrechart KDAUFTRAGNR         = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR
#define DWtkdauftrposrechart where KDAUFTRAGNR   = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR

#define PKtgeneralcalcavp    PRICE_GROUP         = :recordp->PRICE_GROUP\
                             and PREIS_TYP       = :recordp->PREIS_TYP
#define DWtgeneralcalcavp

#define PKtcstcalcavp        BRANCHNO            = :recordp->BRANCHNO\
                             and CUSTOMERNO      = :recordp->CUSTOMERNO\
                             and PRICE_GROUP     = :recordp->PRICE_GROUP\
                             and PREIS_TYP       = :recordp->PREIS_TYP\
                             and ABDACODE        = :recordp->ABDACODE
#define DWtcstcalcavp        where BRANCHNO      = :recordp->BRANCHNO\
                             and CUSTOMERNO      = :recordp->CUSTOMERNO\
                             and PRICE_GROUP     = :recordp->PRICE_GROUP\
                             and PREIS_TYP       = :recordp->PREIS_TYP\
                             and ABDACODE        = :recordp->ABDACODE

#define PKtcstprint       BRANCHNO                = :recordp->BRANCHNO\
                          and CUSTOMERNO          = :recordp->CUSTOMERNO\
                          and PREIS_TYP           = :recordp->PREIS_TYP
#define DWtcstprint       where BRANCHNO          = :recordp->BRANCHNO\
                          and CUSTOMERNO          = :recordp->CUSTOMERNO

#define PKttaxtab   TAX_ART                                             = :recordp->TAX_ART\
                     and TAX_VON_DM                             = :recordp->TAX_VON_DM
#define DWttaxtab  where TAX_ART                                = :recordp->TAX_ART\
                     and TAX_VON_DM                             = :recordp->TAX_VON_DM

#define PKtkdauftragposrefund KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR
#define DWtkdauftragposrefund where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR

#define PKtkdauftragpospromo KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR\
                             and PROMOTION_NO    = :recordp->PROMOTION_NO
#define DWtkdauftragpospromo where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR\
                             and POSNR           = :recordp->POSNR

#define PKtkdauftragposchange  KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                               and POSNR           = :recordp->POSNR
#define DWtkdauftragposchange where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR\
                              and POSNR           = :recordp->POSNR
#define PKtarticlecodes       ARTICLE_CODE         = :recordp->ARTICLE_CODE
#define DWtarticlecodes       where ARTICLE_CODE   = :recordp->ARTICLE_CODE

#define PKtkdauftragprolink   KDAUFTRAGNR        = :recordp->KDAUFTRAGNR
#define DWtkdauftragprolink   where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR


#define PKttendercustomer     TENDERNO             = :recordp->TENDERNO\
                               and BRANCHNO        = :recordp->BRANCHNO\
                               and CUSTOMERNO      = :recordp->CUSTOMERNO

#define DWttendercustomer    where TENDERNO        = :recordp->TENDERNO\
                               and BRANCHNO        = :recordp->BRANCHNO\
                               and CUSTOMERNO      = :recordp->CUSTOMERNO

#define PKtencloserscale      BRANCHNO             = :recordp->BRANCHNO\
                               and CUSTOMERNO      = :recordp->CUSTOMERNO

#define DWtencloserscale    where BRANCHNO         = :recordp->BRANCHNO\
                               and CUSTOMERNO      = :recordp->CUSTOMERNO

#define PKtpromotionquota      BRANCHNO             = :recordp->BRANCHNO\
                               and PROMOTION_NO      = :recordp->PROMOTION_NO\
                               and ARTICLENO           = :recordp->ARTICLENO

#define DWtpromotionquota    where BRANCHNO         = :recordp->BRANCHNO\
                               and PROMOTION_NO      = :recordp->PROMOTION_NO

#define PKtpromotionquotacst   BRANCHNO             = :recordp->BRANCHNO\
                               and PROMOTION_NO     = :recordp->PROMOTION_NO\
                               and CUSTOMERNO       = :recordp->CUSTOMERNO\
                               and ARTICLENO          = :recordp->ARTICLENO

#define DWtpromotionquotacst   where BRANCHNO       = :recordp->BRANCHNO\
                               and PROMOTION_NO     = :recordp->PROMOTION_NO\
                               and CUSTOMERNO       = :recordp->CUSTOMERNO

#define PKtcustomersurcharge   BRANCHNO                 = :recordp->BRANCHNO\
                               and CUSTOMERNO       = :recordp->CUSTOMERNO\
                               and MANUFACTURERNO   = :recordp->MANUFACTURERNO

#define DWtcustomersurcharge   where BRANCHNO       = :recordp->BRANCHNO\
                               and CUSTOMERNO       = :recordp->CUSTOMERNO\
                               and MANUFACTURERNO   = :recordp->MANUFACTURERNO

#define PKtvartikellokal      ARTIKEL_NR            = :recordp->ARTIKEL_NR\
                              and FILIALNR          = :recordp->FILIALNR

#define DWtvartikellokal

#define PKtmanufacturergroup    KONSIG_PARTNER_NR   = :recordp->KONSIG_PARTNER_NR

#define DWtmanufacturergroup    where KONSIG_PARTNER_NR   = :recordp->KONSIG_PARTNER_NR

#define PKtkdauftragdebtrel    KDAUFTRAGNR   = :recordp->KDAUFTRAGNR and RELCOUNTER = :recordp->RELCOUNTER

#define DWtkdauftragdebtrel    where KDAUFTRAGNR   = :recordp->KDAUFTRAGNR


#define PKtpromotionscale     BASEPROMOTION         = :recordp->BASEPROMOTION\
                              and PROMOTION_NO      = :recordp->PROMOTION_NO

#define DWtpromotionscale     where PROMOTION_NO      = :recordp->PROMOTION_NO


#define PKtcustomergroup      BRANCHNO                 = :recordp->BRANCHNO\
                              and CUSTOMERGROUPNO      = :recordp->CUSTOMERGROUPNO

#define DWtcustomergroup      where BRANCHNO           = :recordp->BRANCHNO\
                              and CUSTOMERGROUPNO      = :recordp->CUSTOMERGROUPNO


#define PKtcustomergrpflags   BRANCHNO                 = :recordp->BRANCHNO\
                              and CUSTOMERGROUPNO      = :recordp->CUSTOMERGROUPNO

#define DWtcustomergrpflags   where (BRANCHNO           = :recordp->BRANCHNO\
                              or BRANCHNO = 0)\
                              and CUSTOMERGROUPNO      = :recordp->CUSTOMERGROUPNO

#define PKtcustgrpflagtypes   BRANCHNO                 = :recordp->BRANCHNO

#define DWtcustgrpflagtypes   where BRANCHNO           = :recordp->BRANCHNO

#define PKtoeorigintypes      ORIGINTYPE               = :recordp->ORIGINTYPE

#define DWtoeorigintypes      where ORIGINDEVICE       = :recordp->ORIGINDEVICE

#define PKtoerestrictiontypes  RESTRICTIONTYPE         = :recordp->RESTRICTIONTYPE

#define DWtoerestrictiontypes  where RESTRICTIONTYPE   = :recordp->RESTRICTIONTYPE

#define PKtorderentryrestrictions  BRANCHNO            = :recordp->BRANCHNO

#define DWtorderentryrestrictions  where BRANCHNO      = :recordp->BRANCHNO

#define PKteventreason         EVENTCODE               = :recordp->EVENTCODE

#define DWteventreason  where  EVENTCODE               = :recordp->EVENTCODE

#define PKtkdauftragposereignis DATUM                  = :recordp->DATUM\
                                and KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                                and POSEREIGNISART     = :recordp->POSEREIGNISART\
                                and POSNR              = :recordp->POSNR\
                                and UHRZEIT            = :recordp->UHRZEIT

#define DWtkdauftragposereignis   where DATUM          = :recordp->DATUM\
                                and KDAUFTRAGNR        = :recordp->KDAUFTRAGNR\
                                and POSEREIGNISART     = :recordp->POSEREIGNISART\
                                and POSNR              = :recordp->POSNR\
                                and UHRZEIT            = :recordp->UHRZEIT

#define PKtcustomerspecials     BRANCHNO               = :recordp->BRANCHNO\
                                and CUSTOMERNO         = :recordp->CUSTOMERNO\
                                and WEEKDAY            = :recordp->WEEKDAY

#define DWtcustomerspecials     where BRANCHNO           = :recordp->BRANCHNO\
                                and CUSTOMERNO           = :recordp->CUSTOMERNO

#define PKtSALESMAN    BRANCHNO   = :recordp->BRANCHNO and SALESMANNO = :recordp->SALESMANNO


#define PKtservices             SERVICE_NO             = :recordp->SERVICE_NO

#define DWtservices             where SERVICE_NO       = :recordp->SERVICE_NO

#define  DWtibtassortmenttype

