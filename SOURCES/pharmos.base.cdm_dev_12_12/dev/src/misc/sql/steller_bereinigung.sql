select count(steller), steller  from zartikel group by 2;
select count(*) from ccpvalidityperiod;
select count(*) from cartcompack;


--> Positionen ohne Köpfe
select * from cartcompack where article_no_pack not in (select article_no_pack from ccpvalidityperiod);

--> Köpfe ohne Positionen
select * from  ccpvalidityperiod where article_no_pack not in (select article_no_pack from cartcompack );

--> PZN´s unbekannt 
select * from ccpvalidityperiod where article_no_pack not in (select artikel_nr from zartikel);
select * from cartcompack where article_no_pack not in (select artikel_nr from zartikel);
select * from cartcompack where article_no_element not in (select artikel_nr from zartikel);


select * from cartcompack where article_no_pack not in (select artikel_nr from zartikel where steller = 'S');
select * from cartcompack where article_no_element not in (select artikel_nr from zartikel where steller = 'T');

select * from zartikel where steller = 'S' and artikel_nr not in (select article_no_pack from cartcompack);
select * from zartikel where steller = 'T' and artikel_nr not in (select article_no_element from cartcompack);



unload to 'C:\temp\ch\zartikel_steller.txt'
select artikel_nr, steller from zartikel;

unload to 'C:\temp\ch\ccpvalidityperiod.txt'
select * from ccpvalidityperiod ;

unload to 'C:\temp\ch\cartcompack.txt'
select * from cartcompack ;



delete from ccpvalidityperiod where article_no_pack not in (select artikel_nr from zartikel);
delete from cartcompack where article_no_pack not in (select artikel_nr from zartikel);
delete from cartcompack where article_no_element not in (select artikel_nr from zartikel);

insert into zapflege (artikel_nr, datum)
select artikel_nr, '20130812' from zartikel where artikel_nr in (select article_no_element from cartcompack) and steller != 'T' and artikel_nr not in (select artikel_nr from zapflege where datum = 20130812)

update zartikel set steller = 'T' where  artikel_nr in (select article_no_element from cartcompack) and steller != 'T';


insert into zapflege (artikel_nr, datum)
select artikel_nr, '20130812' from zartikel where artikel_nr in (select article_no_pack from cartcompack) and steller != 'S' and artikel_nr not in (select artikel_nr from zapflege where datum = 20130812)

update zartikel set steller = 'S' where  artikel_nr in (select article_no_pack from cartcompack) and steller != 'S';


insert into zapflege (artikel_nr, datum)
select artikel_nr, '20130812' from zartikel where artikel_nr not in (select article_no_pack from cartcompack) and artikel_nr not in (select article_no_element from cartcompack)  and steller != 'N' and artikel_nr not in (select artikel_nr from zapflege where datum = 20130812)

update zartikel set steller = 'N' where  artikel_nr not in (select article_no_pack from cartcompack) and artikel_nr not in (select article_no_element from cartcompack) and steller != 'N';

