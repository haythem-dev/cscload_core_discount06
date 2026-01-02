-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadvicehead, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadvicehead AS dst
USING(
	select a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno 
	, a.kdauftragnr as cscorderno, '1' as completed, ' ' as specialdocumenttype, ta.tourid as tourid, a.datumvaluta as duedate
	, a.kdauftragart as ordertype, a.koart as pickingtype, a.buchart as bookingtype
	, 0 as requested, 0 as confirmed, a.orderlabel as orderlabel
	from kdauftrag a 
	join kdauftragpostour ta on ta.kdauftragnr=a.kdauftragnr and ta.posnr=0
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum>20171100
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)	
) AS src
ON dst.branchno=src.branchno AND dst.customerno=src.customerno AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.pharmosorderno, dst.deliveryadviceno, dst.cscorderno, dst.completed, dst.tourid, dst.duedate, dst.ordertype, dst.pickingtype, dst.bookingtype, dst.orderlabel)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.pharmosorderno, src.deliveryadviceno, src.cscorderno, src.completed, src.tourid, src.duedate, src.ordertype, src.pickingtype, src.bookingtype, src.orderlabel)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.cscorderno=src.cscorderno, dst.completed=src.completed, dst.tourid=src.tourid, dst.duedate=src.duedate, dst.ordertype=src.ordertype,
		dst.pickingtype=src.pickingtype, dst.bookingtype=src.bookingtype, dst.orderlabel=src.orderlabel
;


-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadvicevattotals, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadvicevattotals AS dst
USING(
	select 
	  a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno
	, cast(tr.taxlevel as varchar(1)) as vat, tr.salestaxrate as vatpercentage
	, sum(p.preisekapo) as netvalue, (sum(p.preisekapo) * tr.salestaxrate / 100) as vatvalue
	from kdauftragpos p
	join kdauftrag a on a.kdauftragnr=p.kdauftragnr
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum>20171100
	join artikelzentral z on z.artikel_nr=p.artikel_nr
	join taxrates tr on tr.taxlevel=z.taxlevel	
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
	group by a.filialnr, a.idfnr, a.kdauftragnr, a.kdauftragnrfiliale, tr.taxlevel, tr.salestaxrate, e.datum
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno AND dst.vat=src.vat
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.deliveryadviceno, dst.vat, dst.vatpercentage, dst.netvalue, dst.vatvalue)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.deliveryadviceno, src.vat, src.vatpercentage, src.netvalue, src.vatvalue)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.vatpercentage=src.vatpercentage, dst.netvalue=src.netvalue, dst.vatvalue=src.vatvalue		
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadvicetotals, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadvicetotals AS dst
USING(
	select 
	  a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno
	, (sum(a.wertauftrag) * 0.025) as depositvalue, (sum(a.wertauftrag) * 0.015) as logisticservicecost
	from kdauftrag a 
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum>20171100
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
	group by a.filialnr, a.idfnr, a.kdauftragnr, a.kdauftragnrfiliale, e.datum
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno	
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.deliveryadviceno, dst.depositvalue, dst.logisticservicecost)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.deliveryadviceno, src.depositvalue, src.logisticservicecost)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.depositvalue=src.depositvalue, dst.logisticservicecost=src.logisticservicecost		
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadviceline, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadviceline AS dst
USING(
	select 
	  a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, p.posnr as pharmosorderposno
	, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno, p.posnr as deliveryadviceposno, p.posnr as cscorderposno
	, p.artikel_nr as articleno, p.article_code as article_code, p.code_type as code_type
	, p.mengebestellt as qty_ordered, p.mengebestaetigt as qty_confirmed, p.mengenatra as qty_rebateinkind, p.mengegeliefert as qty_invoiced
	, nvl(r.remarktext,'') as linereference, nvl(z.taxlevel,0) as vat
	, p.preisekapo as invoicedprice, p.preisekapo * 0.015 as logisticservicecost, 0.01 as minlogisticservicecostvalue
	, case nvl(ir.ibtrequestid,0)when 0 then 0 else 1 end as linetype
	, tr.salestaxrate as vatpercentage
	from kdauftragpos p
	join kdauftrag a on a.kdauftragnr=p.kdauftragnr
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum > 20171100
	join kdauftragereignis e110 on e110.kdauftragnr=a.kdauftragnr and e110.ereignisart=110
	left join artikelzentral z on z.artikel_nr=p.artikel_nr
	join taxrates tr on tr.taxlevel=z.taxlevel	
	left join orderremarks r on r.cscorderno=p.kdauftragnr and r.positionno=p.posnr and r.remarktype=2
	left join ibtrequest ir on ir.branchno=a.filialnr and ir.cscorderno=a.kdauftragnr and ir.cscorderposno=p.posnr and ir.customerno=a.idfnr and ir.processingstate=1
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno AND dst.deliveryadviceposno=src.deliveryadviceposno 
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.pharmosorderno, dst.pharmosorderposno, dst.deliveryadviceno, dst.deliveryadviceposno, dst.cscorderposno, dst.articleno, dst.article_code, dst.code_type, dst.qty_ordered, dst.qty_confirmed, dst.qty_rebateinkind, dst.qty_invoiced, dst.linereference, dst.vat, dst.invoicedprice, dst.logisticservicecost, dst.minlogisticservicecostvalue, dst.linetype, dst.vatpercentage)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.pharmosorderno, src.pharmosorderposno, src.deliveryadviceno, src.deliveryadviceposno, src.cscorderposno, src.articleno, src.article_code, src.code_type, src.qty_ordered, src.qty_confirmed, src.qty_rebateinkind, src.qty_invoiced, src.linereference, src.vat, src.invoicedprice, src.logisticservicecost, src.minlogisticservicecostvalue, src.linetype, src.vatpercentage)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.cscorderposno=src.cscorderposno, dst.articleno=src.articleno, dst.article_code=src.article_code, dst.code_type=src.code_type, 
		dst.qty_ordered=src.qty_ordered, dst.qty_confirmed=src.qty_confirmed, dst.qty_rebateinkind=src.qty_rebateinkind, dst.qty_invoiced=src.qty_invoiced, 
		dst.linereference=src.linereference, dst.vat=src.vat, dst.invoicedprice=src.invoicedprice, dst.logisticservicecost=src.logisticservicecost, 
		dst.minlogisticservicecostvalue=src.minlogisticservicecostvalue, dst.linetype=src.linetype, dst.vatpercentage=src.vatpercentage
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadviceremarks (invoiceline), changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadviceremarks AS dst
USING(
	select a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, p.posnr as pharmosorderposno
	, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno, p.posnr as deliveryadviceposno
	, r.remarktype as remarktype, r.textnumber as serialno, nvl(r.remarktext,'') as remarktext
	from kdauftragpos p
	join kdauftrag a on a.kdauftragnr=p.kdauftragnr
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum>20171100					
	join orderremarks r on r.cscorderno=p.kdauftragnr and r.positionno=p.posnr 	
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno AND dst.deliveryadviceposno=src.deliveryadviceposno 
	AND dst.remarktype=src.remarktype AND dst.serialno=src.serialno
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.deliveryadviceno, dst.deliveryadviceposno, dst.remarktype, dst.serialno, dst.remarktext)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.deliveryadviceno, src.deliveryadviceposno, src.remarktype, src.serialno, src.remarktext)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.remarktext=src.remarktext 		
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadviceremarks (invoice), changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadviceremarks AS dst
USING(
	select 
	  a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, 0 as pharmosorderposno
	, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno, 0 as deliveryadviceposno
	, r.remarktype as remarktype, r.textnumber as serialno, nvl(r.remarktext,'') as remarktext
	from kdauftrag a 
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum>20171100
	join orderremarks r on r.cscorderno=a.kdauftragnr and r.positionno=0 
	where a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno AND dst.deliveryadviceposno=src.deliveryadviceposno 
	AND dst.remarktype=src.remarktype AND dst.serialno=src.serialno
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.deliveryadviceno, dst.deliveryadviceposno, dst.remarktype, dst.serialno, dst.remarktext)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.deliveryadviceno, src.deliveryadviceposno, src.remarktype, src.serialno, src.remarktext)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.remarktext=src.remarktext 		
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadvicelinedetails, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadvicelinedetails AS dst
USING(
	select a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, a.kdauftragnr as pharmosorderno, p.posnr as pharmosorderposno, p.posnr as deliveryposno
	, (p.mengebestaetigt + p.mengenatra) as qty_delivery	
	, ('CHARGE:' || nvl(r.remarktext,'')) as batch, 20200107 as expirydate
	, 4711 as packageid, 'TRACKID:' || cast(a.kdauftragnr as varchar(10)) as trackingid
	, (p.mengebestellt - p.mengebestaetigt) as qty_lack
	from kdauftragpos p
	join kdauftrag a on a.kdauftragnr=p.kdauftragnr
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum > 20171100
	join orderremarks r on r.cscorderno=p.kdauftragnr and r.positionno=p.posnr
	where r.remarktype=2 	
	and a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate	AND dst.pharmosorderno=src.pharmosorderno AND dst.pharmosorderposno=src.pharmosorderposno 
	AND dst.deliveryposno=src.deliveryposno	
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.pharmosorderno, dst.pharmosorderposno, dst.deliveryposno, dst.qty_delivery, dst.batch, dst.expirydate, dst.packageid, dst.trackingid, dst.qty_lack)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.pharmosorderno, src.pharmosorderposno, src.deliveryposno, src.qty_delivery, src.batch, src.expirydate, src.packageid, src.trackingid, src.qty_lack)
WHEN MATCHED THEN 
	UPDATE SET 		
		dst.qty_delivery=src.qty_delivery, dst.batch=src.batch, dst.expirydate=src.expirydate, 
		dst.packageid=src.packageid, dst.trackingid=src.trackingid, dst.qty_lack=src.qty_lack
;

-- --------------------------------------------------------------------------------------------------------------------------------
-- fill deliveryadvicelinediscounts, changed 2017-11-20
-- --------------------------------------------------------------------------------------------------------------------------------
MERGE INTO wde21@zdev21_tcp:deliveryadvicelinediscounts AS dst
USING(
	select 
	  a.filialnr as branchno, a.idfnr as customerno, e.datum as deliveryadvicedate
	, RIGHT(('000000000' || cast(a.kdauftragnr as varchar(10))),10) as deliveryadviceno, p.posnr as deliveryadviceposno
	, 0 as discountmode, 0 as discount, 'X' as origin, 0 as deletereason, 0 as discountvalue, 0 as discounttype, 0 as hierarchy, 0 as calculationbasis	
	from kdauftragpos p
	join kdauftrag a on a.kdauftragnr=p.kdauftragnr
	join kdauftragereignis e on e.kdauftragnr=a.kdauftragnr and e.ereignisart=4 and e.datum > 20171100			
	join kdauftragereignis e110 on e110.kdauftragnr=a.kdauftragnr and e110.ereignisart=110			
	and a.filialnr in (5,6,8,9,21,31,33,40,44,46,51,52,54,56,57,58,59,78,81,82)
) AS src
ON 	dst.branchno=src.branchno AND dst.customerno=src.customerno
	AND dst.deliveryadvicedate=src.deliveryadvicedate AND dst.deliveryadviceno=src.deliveryadviceno AND dst.deliveryadviceposno=src.deliveryadviceposno 
	AND dst.discountmode=src.discountmode
WHEN NOT MATCHED THEN 
	INSERT (dst.branchno, dst.customerno, dst.deliveryadvicedate, dst.deliveryadviceno, dst.deliveryadviceposno, dst.discountmode, dst.discount, dst.origin, dst.deletereason, dst.discountvalue, dst.discounttype, dst.hierarchy, dst.calculationbasis)
     VALUES (src.branchno, src.customerno, src.deliveryadvicedate, src.deliveryadviceno, src.deliveryadviceposno, src.discountmode, src.discount, src.origin, src.deletereason, src.discountvalue, src.discounttype, src.hierarchy, src.calculationbasis)
WHEN MATCHED THEN 
	UPDATE SET 
		dst.discount=src.discount, dst.origin=src.origin, dst.deletereason=src.deletereason, dst.discountvalue=src.discountvalue, dst.discounttype=src.discounttype, dst.hierarchy=src.hierarchy, dst.calculationbasis=src.calculationbasis		
;