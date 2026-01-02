set isolation dirty read;
select a.filialnr as filiale, a.idfnr as IDF, k.nameapo as NameApotheke, k.ort as ort, a.kdauftragnr as KSCAuftragsNr, a.kdauftragart as auftragsart, a.koart as kommiart, a.buchart as buchungsart
, nvl(ta.departuredate,0) as datum, nvl(ta.tourid,'') as tourid, p.posnr, p.article_code as artikelcode, p.mengebestellt as mengebestellt, p.mengebestaetigt as mengebestaetigt
, a.orderlabel	
, case 
	when a.kdauftragstat like '00010000000__%' then 'ZU'
	when a.kdauftragstat like '00010000000_1%' then 'ZU'
	when a.kdauftragstat like '00010000000_0%' then 'ZU'
	when a.kdauftragstat like '0000100000%'    then 'ER'
	when a.kdauftragstat like '_________1%'    then 'ST'	
	when a.kdauftragstat like '00001___10%'    then 'FA'	
	when a.kdauftragstat like '00001__100%'    then 'BF'
	when a.kdauftragstat like '01%'            then 'IE'	
	else 'unknown' end as auftragsstatus
from kdauftragpos p
join kdauftrag a on a.kdauftragnr=p.kdauftragnr
left join kdauftragpostour ta on ta.kdauftragnr=a.kdauftragnr and ta.posnr=0
left join kunde k on k.idfnr=a.idfnr and k.filialnr=a.filialnr
where a.filialnr in (5,56) and a.kdauftragnrfiliale=0 and p.mengebestellt>0
and ( a.kdauftragstat like '00010000000__%'	-- ZU
   or a.kdauftragstat like '0000100000%') 	-- ER   
order by a.kdauftragnr, p.posnr

