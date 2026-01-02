set isolation dirty read;
update kdauftrag set bemerkungen='STORNO CSC-PLATFORM-CONS.', kdauftragstat='0000000001000000', etauftragschalter1=512 where kdauftragnr in (
select distinct a.kdauftragnr
from kdauftragpos p
join kdauftrag a on a.kdauftragnr=p.kdauftragnr
left join kdauftragpostour ta on ta.kdauftragnr=a.kdauftragnr and ta.posnr=0
left join kunde k on k.idfnr=a.idfnr and k.filialnr=a.filialnr
where a.filialnr in (54,81,82) and a.kdauftragnrfiliale=0 and p.mengebestellt>0
and ( a.kdauftragstat like '00010000000__%'	-- ZU
   or a.kdauftragstat like '0000100000%') 	-- ER   
);

delete from cststockreserved 
where kdauftragnr in (
select a.kdauftragnr from kdauftrag a where a.bemerkungen='STORNO CSC-PLATFORM-CONS.'
);