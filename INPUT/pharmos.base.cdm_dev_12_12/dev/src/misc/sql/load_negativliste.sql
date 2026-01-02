create temp table TH (pzn integer, neglist char (1));
create unique index i_TH on TH (pzn);

load from 'D:\temp\fr\rev30.csv' delimiter ';'
insert into TH


select * from TH where pzn not in (select artikel_nr from zartikel)

unload to 'D:\temp\fr\article_not_in_zdp.txt'
select pzn from TH where pzn not in (select artikel_nr from zartikel)

delete from TH where pzn not in (select artikel_nr from zartikel)

unload to 'D:\temp\fr\negativliste_vor_update.txt'
select artikel_nr, negativliste from zartikel where artikel_nr in (select pzn from TH)


update zartikel set negativliste = (select neglist from TH where pzn = zartikel.artikel_nr) where artikel_nr in (select pzn from TH)


insert into zapflege
select pzn, '20111123' from TH where pzn not in (select artikel_nr from zapflege where datum = 20111123)

