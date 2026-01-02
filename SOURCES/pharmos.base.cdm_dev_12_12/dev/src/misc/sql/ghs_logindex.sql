create temp table th33 (pzn integer, val char(10));

load from 'C:\logindex\logINDEX_GHS_33.csv' delimiter ';'
insert into th33;

select * from th33

-- update clioart
select * from th33 where pzn not in (select phar from clioart);

update clioart set pictogram01_flag = 1 where phar in (
select pzn from th33 where val = 'GHS01');
update clioart set pictogram02_flag = 1 where phar in (
select pzn from th33 where val = 'GHS02');
update clioart set pictogram03_flag = 1 where phar in (
select pzn from th33 where val = 'GHS03');
update clioart set pictogram04_flag = 1 where phar in (
select pzn from th33 where val = 'GHS04');
update clioart set pictogram05_flag = 1 where phar in (
select pzn from th33 where val = 'GHS05');
update clioart set pictogram06_flag = 1 where phar in (
select pzn from th33 where val = 'GHS06');
update clioart set pictogram07_flag = 1 where phar in (
select pzn from th33 where val = 'GHS07');
update clioart set pictogram08_flag = 1 where phar in (
select pzn from th33 where val = 'GHS08');
update clioart set pictogram09_flag = 1 where phar in (
select pzn from th33 where val = 'GHS09');


-- löschen von Artikeln, die wir nicht im Stamm haben
delete from th33 where pzn not in (select artikel_nr from zartikel);

unload to 'C:\temp\ch\csafetydatasheet_20160812.txt' select * from csafetydatasheet;

-- neue csafetydatasheet- einträge
insert into csafetydatasheet ( articleno, date_changed, pictogram01_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS01' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram02_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS02' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram03_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS03' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram04_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS04' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram05_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS05' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram06_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS06' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram07_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS07' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram08_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS08' and pzn not in (select articleno from csafetydatasheet);
insert into csafetydatasheet ( articleno, date_changed, pictogram09_flag)
select pzn, '20160812', 1 from th33 where val = 'GHS09' and pzn not in (select articleno from csafetydatasheet);


-- update csafetydatasheet
update csafetydatasheet set pictogram01_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS01');
update csafetydatasheet set pictogram02_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS02');
update csafetydatasheet set pictogram03_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS03');
update csafetydatasheet set pictogram04_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS04');
update csafetydatasheet set pictogram05_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS05');
update csafetydatasheet set pictogram06_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS06');
update csafetydatasheet set pictogram07_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS07');
update csafetydatasheet set pictogram08_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS08');
update csafetydatasheet set pictogram09_flag = 1, date_changed = 20160812 where articleno in (
select pzn from th33 where val = 'GHS09');



-- zapflege
insert into zapflege (artikel_nr, datum)
select distinct pzn, '20160812' from th33 where pzn not in (select artikel_nr from zapflege where datum = 20160812)


------------------------------------------------------------------------------------------------------------------


create temp table th16 (pzn integer, val char(10));

load from 'C:\logindex\logINDEX_GHS_16.csv' delimiter ';'
insert into th16;

select * from th16


------------------------------------------------------------------------------------------------------------------


create temp table th24 (pzn integer, val char(10));

load from 'C:\logindex\logINDEX_GHS_24.csv' delimiter ';'
insert into th24;

insert into cliohsatz 
select pzn, val from th24 where val not in (select hazardnoteid from cliohsatz where phar = th24.pzn)

delete from th24 where val[1] != 'H';

-- führendes H entfernen
update th24 set val = val[2,4]

delete from th24 where val not in (select hazardnoteid from chazardnote)
delete from th24 where pzn not in (select artikel_nr from zartikel);


unload to 'C:\temp\ch\chazardnote2article_20160812.txt' select * from chazardnote2article;

insert into chazardnote2article
select pzn, val from th24 where val not in (select hazardnoteid from chazardnote2article where articleno = th24.pzn)

-- zapflege
insert into zapflege (artikel_nr, datum)
select distinct pzn, '20160812' from th24 where pzn not in (select artikel_nr from zapflege where datum = 20160812)

