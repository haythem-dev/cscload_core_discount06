/*----------------------------------------------------------------------------*/
/*  define values for the INFORMIX stub , to get unique function numbers      */
/*----------------------------------------------------------------------------*/
enum F_tablenames
{
 F_ALLGEMEIN          ,
 F_ARTIKELALTERN      ,
 F_ARTIKELPREIS       ,
 F_ARTIKEL            , /* obsolete */
 F_ARTIKELLAGERORT    ,
 F_ARTIKELMGPREIS     , /* obsolete */
 F_ARTIKELNATRA       , /* obsolete */
 F_ARTIKELSEKBEZ      , /* obsolete */
 F_KDAUFTRAGART       ,
 F_AUFTRAGARTKD       ,
 F_KDAUFTRAGEREIGNIS  ,
 F_AUFTRAGARTKOMB     ,
 F_KDAUFTRAGSCHALTER  ,
 F_BEARBEITER         , /* obsolete */
 F_BUCHUNGSART        ,
 F_FILIALE            ,
 F_KOMMIARTEN         ,
 F_KDBETRIEBSENDE     ,
 F_KUNDE              ,
 F_KUNDEKONDI         ,
 F_KUNDESCHALTER      ,
 F_NACHLIEFERPOS      ,
 F_NUMMER             ,
 F_PARAAUFTRAGBEARB   ,
 F_KDAUFTRAGPOS       ,
 F_TOURROUTE          ,
 F_TAGESTYP           ,
 F_TOUR               ,
 F_TOURPLANGEN        ,
 F_TOURPLANTAG        ,
 F_KDKONDITIONGRUPPE  , /* obsolete */
 F_KONDITIONGRUPPE    ,
 F_KDAUFTRAG          ,
 F_KUNDENGRUPPE       ,
 F_DISPOARTIKEL       ,
 F_LOCKMANAGER        ,
 F_FKWARTESCHLANGE    , /* obsolete */
 F_GERAETEANRUFPLAN   , /* obsolete */
 F_KDAUFTRAGBEM       ,
 F_ALTERNATIVFILIALE  , /* obsolete */
 F_ZEITARTEN          ,
 F_KDAUFTRAGENDEZEIT  ,
 F_BLIEFER            ,
 F_ARTFIL             ,
 F_NACHLIEFPROT       ,
 F_ARTIKELKONTO       ,
 F_KUNDEMONUMS        ,
 F_FILIALPARTNER      ,	/* obsolete */
 F_MODEMTAB           ,	/* obsolete */
 F_KDVERBUNDPOS       , /* obsolete */
 F_KDVERBUND          , /* obsolete */
 F_RECHNER            ,
 F_PARAAUFTRAGER      ,	/* obsolete */
 F_ARTIKELREIMPORT    ,
 F_VERBUNDSPERRE      , /* obsolete */
 F_ARTIKELZENTRAL     ,
 F_ARTIKELLOKAL       ,
 F_MODEMANRUFPLAN     , /* obsolete */
 F_VSEDATEIEN         , /* obsolete */
 F_AKTIVEPROZESSE     , /* obsolete */
 F_REGIONARTEN        ,
 F_TOURFOLGETAG       , /* obsolete */
 F_KDVERBUNDFILIALE   , /* obsolete */
 F_LAGERREVISION      ,
 F_ARTIKELF           ,
 F_TASKCONTROL        ,
 F_ARTIKELNUMMERN     ,
 F_CUSTOMERORDERNO    ,
 F_KDAUFTRAGINFO      ,
 F_ARTICLEPREDELIVERY , /* obsolete */
 F_CUSTOMERRECODE     ,
 F_CUSTOMERROUTING    ,
 F_CUSTOMERPHARMACYGR ,
 F_VALIDDISCOUNTINFO  , /* obsolete */
 F_STOCKENTRY         ,
 F_DEBTLIMIT          ,
 F_ARTICLEQUOTA       ,
 F_PARAMETER          ,
 F_ARTICLETEXT        ,
 F_DELAYEDDELIVERYART , /* obsolete */
 F_DELAYEDDELIVERYCST ,
 F_FEIERTAG           ,
 F_DISCOUNT           ,
 F_ARTICLERESERVATION ,
 F_KDAUFTRAGPOSRAB    ,
 F_DISCOUNTGRP        ,
 F_DISCOUNTGRPMEM     ,
 F_DISCOUNTORDERTYP   ,
 F_DISCOUNTPHARMAGRP  ,
 F_NARCTRANSACTIONTRANSFER,
 F_POSITIONPARKING    ,
 F_ARTICLEPACKUNIT    ,
 F_TOURPLANTAGWOCHE   ,
 F_TOURCONSTIME       ,
 F_TOURPLANCONSTIME   ,
 F_TOURPLANWOCHE      ,
 F_KOBEHAELTERTYP     ,
 F_CSTSTOCKRESERVED   ,
 F_ACSTSTOCKRESERVED  ,
 F_DISCOUNTLIST       ,
 F_CSTDISCOUNTCONT    ,
 F_TAXRATES           ,
 F_SEPORDERART        , /* obsolete */
 F_SEPORDERARTGRP     ,
 F_ARTICLEOLDPRICE    ,
 F_COUNTRYCODES       ,
 F_ARTICLELPPR        ,
 F_AKDVERBUND         , /* obsolete */
 F_ORDERCRITERIA      ,
 F_SHIPAUXNO          , /* obsolete */
 F_KNDAUSKU           ,
 F_CLEARWAFO          ,
 F_ARTICLEAUXBRANCH   , /* obsolete */
 F_CSTSEPORDERARTGRP  ,
 F_ARTICLEGROUP       ,
 F_ARTCOMPACK         ,
 F_CSTDISCACC         ,
 F_DEALERVOLUME       ,
 F_CPVALIDITYPERIOD   ,
 F_TENDERHEAD         ,
 F_TENDERPOS          ,
 F_TENDERPROGRESS     ,
 F_ARTIKELZENTRALFR   ,
 F_KDAUFTRAGDISCACC   ,
 F_ARTSPECIALCOND     ,
 F_PROMOTIONS         ,
 F_SERVICES           , /*nicht mehr obsolete SR-16056431*/
 F_SERVICETYPES       , /* obsolete */
 F_CSTPAYMENTTERMS    ,
 F_KDAUFTRAGWERTE     ,
 F_KDAUFTRAGPOSCHARGE ,
 F_ARTICLECHARGE      ,
 F_KDAUFTRAGRECHART   ,
 F_KDAUFTRPOSRECHART  ,
 F_GENERALCALCAVP     ,
 F_CSTCALCAVP         ,
 F_CSTPRINT           ,
 F_TAXTAB             ,
 F_KDAUFTRAGPOSREFUND ,
 F_KDAUFTRAGPOSPROMO  ,
 F_KDAUFTRAGPOSCHANGE ,
 F_ARTICLECODES       ,
 F_KDAUFTRAGPROLINK   ,
 F_KDVERBUNDPOSRAB    , /* obsolete */
 F_TENDERCUSTOMER     ,
 F_ENCLOSERSCALE      ,
 F_PROMOTIONQUOTA     ,
 F_PROMOTIONQUOTACST  ,
 F_CUSTOMERSURCHARGE  ,
 F_KDAUFTRAGPOSXML    , /* obsolete */
 F_VARTIKELLOKAL      ,
 F_VARTICLEQUOTA      , /* obsolete */
 F_MANUFACTURERGROUP  ,
 F_SMTPUSERGROUPS     ,
 F_KDAUFTRAGDEBTREL   ,
 F_VKDVERBUNDPOS      , /* obsolete */
 F_PROMOTIONSCALE     ,
 F_CSTTOUREXCLUSIONS  , /* obsolete */
 F_ORDERREMARKTYPES   ,
 F_ORDERREMARKS       ,
 F_CUSTOMERGROUP      ,
 F_CUSTOMERGRPFLAGS   ,
 F_CUSTGRPFLAGTYPES   ,
 F_CUSTOMERTOUR       ,
 F_OEORIGINTYPES      ,
 F_OERESTRICTIONTYPES ,
 F_ORDERENTRYRESTRICTIONS,
 F_EVENTREASONS,
 F_KDAUFTRAGPOSEREIGNIS,
 F_TOTEINFO,
 F_KDAUFTRAGPOSTOUR,
 F_IBTBRANCHES,
 F_CUSTOMERBUSINESSHOURS,
 F_CSCCUSTOMER,
 F_CUSTOMERSPECIALS,
 F_ORDERRELATIONNOTYPES,
 F_ORDERRELATIONNO,
 F_IBTTYPE,
 F_SALESMAN,
 F_SUPPLDELIVERYINFO,
 F_ORDERPERIOD,
 F_IBTASSORTMENTTYPE
 };

enum F_DBfunctions
{
 F_StartBrowse,
 F_GetNext    ,
 F_EndBrowse  ,
 F_Read       ,
 F_ReadLock   ,
 F_Insert     ,
 F_Update     ,
 F_Delete
};

#define F_FunctionNr -2
#define F_XFRMessage -1
#define F_Connect 0
#define F_Disconnect 1
#define F_SQLCode 2
#define F_SQLMessage 3
#define F_Begin 4
#define F_Commit 5
#define F_Rollback 6

#define F_Lock                    0
#define F_IsLocked                1
#define F_UnLock                  2
#define F_ReleaseLock             3
#define F_ReleaseAllLocks         4
#define F_LockManagerStartBrowse  5
#define F_LockManagerGetNext      6
#define F_GetServerTime           7
