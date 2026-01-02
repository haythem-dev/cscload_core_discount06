select  count(*) from cdiscount where discountspec = 1 and pharmacygroupid not in ('020', '030') and dateto > 20110607


update cdiscount set discountspec = 0 where discountspec = 1 and pharmacygroupid not in ('020', '030') and dateto > 20110607

select  
ARTICLENO, 
       DISCOUNTGRPNO, 
       PHARMACYGROUPID, 
       CUSTOMERNO, 
       BASEQTY, 
       DATEFROM, 
       DATETO, 
       GRPDISCOUNTTYP, 
       DISCOUNTTYPE, 
       DISCOUNTSPEC, 
BASE_VALUE, 
       BASE_MULT_STD_QTY, 
MANUFACTURERNO, 
       ARTCATEGORYNO, 
       PAYMENTTARGETNO
from cdiscount where discountspec = 1 and pharmacygroupid not in ('020', '030') and dateto > 20110607
into temp TH


select count (*) from TH

create unique index i_TH on TH (ARTICLENO, 
       DISCOUNTGRPNO, 
       PHARMACYGROUPID, 
       CUSTOMERNO, 
       BASEQTY, 
       DATEFROM, 
       DATETO, 
       GRPDISCOUNTTYP, 
       DISCOUNTTYPE, 
       DISCOUNTSPEC, 
BASE_VALUE, 
       BASE_MULT_STD_QTY, 
MANUFACTURERNO, 
       ARTCATEGORYNO, 
       PAYMENTTARGETNO);

select * from TH where articleno in (select articleno from cdiscount where 
TH.DISCOUNTGRPNO = DISCOUNTGRPNO and 
TH.PHARMACYGROUPID = PHARMACYGROUPID and 
TH.CUSTOMERNO = CUSTOMERNO and 
TH.BASEQTY = BASEQTY and 
--TH.DATEFROM = DATEFROM and 
--TH.DATETO = DATETO and 
dateto > 20110607 and 
TH.GRPDISCOUNTTYP = GRPDISCOUNTTYP and 
TH.DISCOUNTTYPE = DISCOUNTTYPE and 
TH.BASE_VALUE = BASE_VALUE and 
TH.BASE_MULT_STD_QTY = BASE_MULT_STD_QTY and 
TH.MANUFACTURERNO = MANUFACTURERNO and 
TH.ARTCATEGORYNO = ARTCATEGORYNO and 
TH.PAYMENTTARGETNO = PAYMENTTARGETNO and 
discountspec = '0' )


select * from cdiscount where articleno = 6787633


       



DISCOUNTQTY, 
       DISCOUNTVALUEPCT, 
       DISCOUNTQTYPCT, 
       SURCHARGEPCT, 
       PHARMGRPEXCLUDED, 
       FIXEDPRICE, 
       REFUNDPCT, 
       INTERNALDISCOUNT, 
       DISCOUNTARTICLE, 
       MONTHLYDISCOUNT, 
       PHARMGRPEXCL_2, 
       PHARMGRPEXCL_3,        
NO_MULTIPLE_QTY, 
       FIXEDDISCOUNTVALUE,        
GROSSPROFITPCT, 
       ADDONDISCOUNTOK, 
       PAYMENTTERMTYPE, 
       TARGETQTY, 
       EXCEEDANCEPCT, 
       REFUNDTYPE, 
       ARTICLE_NO_PACK, 
       REFUNDVALUE, 
       PROMOTION_NO, 
       TURNOVERCALCIMPACT, 
       MAXQTY, 
       ADDONDISCOUNT
