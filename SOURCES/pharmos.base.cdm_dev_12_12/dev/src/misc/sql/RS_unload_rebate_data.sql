unload to 'D:\temp\rs\RS_current_rebategroup_data.txt'
select g.discountgrpno, description, discountgrptype, articleno  from cdiscgrp g, cdiscgrpmem m
where g.discountgrpno = m.discountgrpno 
order by 1, 4

unload to 'D:\temp\rs\RS_current_rebate_data.txt'
select articleno, discountgrpno, manufacturerno, artcategoryno, paymenttargetno, baseqty, datefrom,
dateto,  discountvaluepct, discountqty, pharmacygroupid, customerno, fixedprice
from cdiscount where dateto >= 20120531

