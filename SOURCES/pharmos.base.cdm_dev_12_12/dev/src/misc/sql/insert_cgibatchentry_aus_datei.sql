create temp table raab1 (
pzn integer
);

create unique index i_raab1 on raab1 (pzn);

load from 'D:\fuer_unix\cgibatchentry_wyeth_260210.txt'
delimiter ';'
insert into raab1

select * from raab1

-- ACHTUNG !! in jedem SQL-Statement den company_code entsprechend anpassen

-- aktuellen Stand sichern
unload to 'D:\DB-Staende\cgibatchentry_vor_update_wyeth_260210.txt'
select * from cgibatchentry where company_code = 4

-- zu löschende Artikel in zapflege schreiben (Verteilung Pharmos)
insert into zapflege
select articleno, cast(to_char(current, '%Y%m%d') as integer) from cgibatchentry
where company_code = 4
and articleno not in (select pzn from raab1)
and articleno not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))

-- nicht mehr benötigte Artikel löschen
delete from cgibatchentry where company_code = 4 and articleno not in (select pzn from raab1)

-- neue Artikel in zapflege schreiben (Verteilung Pharmos)
insert into zapflege
select pzn, cast(to_char(current, '%Y%m%d') as integer) from raab1
where pzn not in (select articleno from cgibatchentry where company_code = 4)
and pzn not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))

-- neue Artikel einfügen
insert into cgibatchentry 
select pzn, '4' from raab1 where pzn not in (select articleno from cgibatchentry where company_code = 4)

-- Kontrolle cgibatchentry
select * from cgibatchentry where company_code = 4