select grenze_a from filiale where filialnr = 0

update filiale set grenze_a = 3000 where filialnr = 0;
select grenze_a from filiale where filialnr = 0


select artikel_nr, aep
 from zartpreis as a 
where 
datumgueltigab = (select max(datumgueltigab) from zartpreis as c
where a.artikel_nr = c.artikel_nr) 
and aep > (select grenze_a from filiale where filialnr = 0) 	--> über Preisgrenze ==> skontofähig = 0, Warengruppe am Ende mit "9"
-- and aep <= (select grenze_a from filiale where filialnr = 0) 	--> unter Preisgrenze ==> skontofähig = 1, Warengruppe am Ende mit "0"
into temp th1;

create unique index i_th1 on th1 (artikel_nr);

select * from th1, outer zartwg w where art = '2' and w.artikel_nr = th1.artikel_nr

-- wenn aktuell keine Warengruppe gesetzt ist, dann kann diese auch nicht geändert und keine Skontofähigkeit übernommen werden:
delete from th1 where artikel_nr not in (select artikel_nr from zartwg where art = '2' and artikel_nr = th1.artikel_nr and warengruppe != '')


select artikel_nr as pzn, warengruppe, 
warengruppe[1,4] || '9' as wgr_neu 			--> über Preisgrenze ==> skontofähig = 0, Warengruppe am Ende mit "9"
-- warengruppe[1,4] || '0' as wgr_neu 			--> unter Preisgrenze ==> skontofähig = 1, Warengruppe am Ende mit "0"
from zartwg where art = '2' 
and artikel_nr in (select artikel_nr from th1)
into temp th2;

create unique index i_th2 on th2 (pzn);

select * from th2

delete from th2 where warengruppe = wgr_neu; -- keine Änderung
delete from th2 where wgr_neu not in (select wgr_gruppe from zdkwgr); -- neue Warengruppe nicht bekannt

update zartwg set warengruppe = (select wgr_neu from th2 where zartwg.artikel_nr = th2.pzn) where art = '2' and artikel_nr in (select pzn from th2);
update zartikel set skontofaehig = CASE WHEN (select wgr_sktof from zdkwgr where wgr_gruppe = (select wgr_neu from th2 where pzn = zartikel.artikel_nr))  = 'J' THEN '1' ELSE '0' END where artikel_nr in (select pzn from th2)
insert into zapflege select pzn, cast(to_char(current, '%Y%m%d') as integer) from th2 where pzn not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer));

--------------------------------------


select artikel_nr, skontofaehig from zartikel where artikel_nr in (select pzn from th2)
select * from zdkwgr where wgr_gruppe in (select wgr_neu from th2)

