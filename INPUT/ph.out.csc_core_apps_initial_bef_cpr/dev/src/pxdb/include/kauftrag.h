#define Ktasbc0
#define Ktasbc1  where IDFNR          =   :recordp->IDFNR
#define Ktasbc18 where IDFNR          =   :recordp->IDFNR\
                 and   TOURID         =   :recordp->TOURID
#define Ktasbc19 where IDFNR          =   :recordp->IDFNR\
                 and   TOURID         =   :recordp->TOURID\
                 and   FILIALNR       =   :recordp->FILIALNR
#define Ktasbc22 where IDFNR          =   :recordp->IDFNR\
                 and   TOURID         =   :recordp->TOURID\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc25 where IDFNR          =   :recordp->IDFNR\
                 and   TOURID         =   :recordp->TOURID\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc26 where IDFNR          =   :recordp->IDFNR\
                 and   FILIALNR       =   :recordp->FILIALNR
#define Ktasbc27 where IDFNR          =   :recordp->IDFNR\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   PERSONALNR     =   :recordp->PERSONALNR
#define Ktasbc28 where IDFNR          =   :recordp->IDFNR\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   PERSONALNR     =   :recordp->PERSONALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc29 where IDFNR          =   :recordp->IDFNR\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc30 where IDFNR          =   :recordp->IDFNR\
                 and   PERSONALNR     =   :recordp->PERSONALNR
#define Ktasbc31 where IDFNR          =   :recordp->IDFNR\
                 and   PERSONALNR     =   :recordp->PERSONALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc32 where IDFNR          =   :recordp->IDFNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc33 where GERAETNAME     =   :recordp->GERAETNAME
#define Ktasbc42 where GERAETNAME     =   :recordp->GERAETNAME\
                 and   FILIALNR       =   :recordp->FILIALNR
#define Ktasbc45 where GERAETNAME     =   :recordp->GERAETNAME\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc48 where GERAETNAME     =   :recordp->GERAETNAME\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc49 where TOURID         =   :recordp->TOURID
#define Ktasbc50 where TOURID         =   :recordp->TOURID\
                 and   FILIALNR       =   :recordp->FILIALNR
#define Ktasbc53 where TOURID         =   :recordp->TOURID\
                 and   FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc56 where TOURID         =   :recordp->TOURID\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc57 where FILIALNR       =   :recordp->FILIALNR
#define Ktasbc60 where FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT\
                 and   SENDESTATUS    =   :recordp->SENDESTATUS
#define Ktasbc61 where PERSONALNR     =   :recordp->PERSONALNR
#define Ktasbc62 where PERSONALNR     =   :recordp->PERSONALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc63 where KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT
#define Ktasbc64 where VERTRIEBSZENTRUMNR =  :recordp->VERTRIEBSZENTRUMNR
#define Ktasbc65 where KUNDENNR           =  :recordp->KUNDENNR
#define Ktasbc66 where VERTRIEBSZENTRUMNR =  :recordp->VERTRIEBSZENTRUMNR\
                 and   KUNDENNR           =  :recordp->KUNDENNR
#define Ktasbc67 where VERTRIEBSZENTRUMNR =  :recordp->VERTRIEBSZENTRUMNR\
                 and   KUNDENNR           =  :recordp->KUNDENNR\
                 and   KDAUFTRAGSTAT    like :recordp->KDAUFTRAGSTAT
#define Ktasbc68 where FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT\
                 and   SENDESTATUS    =   :recordp->SENDESTATUS\
                 and   MOD(KDAUFTRAGNR,2)=1\
				 order by KOART desc, TOURID asc
#define Ktasbc69 where FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT\
                 and   SENDESTATUS    =   :recordp->SENDESTATUS\
                 and   MOD(KDAUFTRAGNR,2)=0\
				 order by KOART desc, TOURID asc
#define Ktasbc70 where FILIALNR       =   :recordp->FILIALNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT\
                 and   (ZUGRUND like       :recordp->ZUGRUND\
                 or    (ZUGRUND like       '1000%'\
                 and   KDAUFTRAGDEBTREL.ISRELEASED =1))\
                 and   SENDESTATUS    =   :recordp->SENDESTATUS
#define Ktasbc71 where VERTRIEBSZENTRUMNR =  :recordp->VERTRIEBSZENTRUMNR\
                 and   KUNDENNR           =  :recordp->KUNDENNR\
                 and   KDAUFTRAGSTAT like :recordp->KDAUFTRAGSTAT\
                 and   ZUGRUND like       :recordp->ZUGRUND\
                 and   BatchAuftragNr =   :recordp->BATCHAUFTRAGNR
				

