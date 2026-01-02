--delete from zartpreis where artikel_nr = 3025383 and datumgueltigab = 20111115;
select * from zapflege where artikel_nr = 3025383;


create temp table TH (pzn integer);
create unique index i_TH on TH (pzn);

load from 'D:\temp\ch\mwst_verm.csv'
insert into TH

select * from TH where pzn not in (select artikel_nr from zartikel);
select * from TH where pzn not in (select artikel_nr from zartpreis);
select * from zartpreis where artikel_nr in (select pzn from TH) and datumgueltigab >= 20111115
select * from zartpreis p where artikel_nr in (select pzn from TH) and ke_mwst = '1' and datumgueltigab = (select max (datumgueltigab) from zartpreis where artikel_nr = p.artikel_nr)


delete from TH where pzn not in (select artikel_nr from zartikel);
delete from TH where pzn not in (select artikel_nr from zartpreis);
delete from TH where pzn in (select artikel_nr from zartpreis p where ke_mwst = '1' and datumgueltigab = (select max (datumgueltigab) from zartpreis where artikel_nr = p.artikel_nr))


select * from zartpreis p where artikel_nr in (select pzn from TH) and datumgueltigab = (select max (datumgueltigab) from zartpreis where artikel_nr = p.artikel_nr)


insert into zartpreis (artikel_nr, datumgueltigab, grosso, aep, avp, ke_mwst, herst_prozent, eavp, maxavp, preis_typ, lieferbasispreis)
select artikel_nr, '20111115', grosso, aep, avp, '1', herst_prozent, eavp, maxavp, preis_typ, lieferbasispreis from zartpreis p where artikel_nr in (select pzn from TH) and datumgueltigab = (select max (datumgueltigab) from zartpreis where artikel_nr = p.artikel_nr)


insert into zapflege (artikel_nr, datum) 
select pzn, '20111115' from TH where pzn not in (select artikel_nr from zapflege where datum = 20111115)

