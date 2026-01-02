unload to 'd:\temp\discount_501.txt'
select articleno,discountgrpno,pharmacygroupid,baseqty,datefrom,dateto,discountvaluepct,manufacturerno,paymenttargetno, fixedprice
from cdiscount where pharmacygroupid = '501' and dateto > 20111123