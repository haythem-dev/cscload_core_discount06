select * from carticlecodes where articleno not in (select artikel_nr from zartikel) 
and date_changed < 20171001
order by articleno

--> ifr21 für Pharmos
insert into zpznpflege (artikel_nr, datum, dezap_sa)
select articleno, '20171004', '34' from carticlecodes where articleno 
--in (3134, 3176)
 not in (select artikel_nr from zartikel) 
and articleno not in (select artikel_nr from zpznpflege where datum = 20171004 and dezap_sa = '34')
and date_changed < 20171001

--> ifr21 für ZDP  
delete from carticlecodes where articleno 
--in (3134, 3176)
 not in (select artikel_nr from zartikel)
and date_changed < 20171001

--> ofr21 für KSC
--select * from articlecodes where articleno not in (select artikel_nr from artikelzentral)
--delete from articlecodes where articleno
--in (3134, 3176)
 not in (select artikel_nr from artikelzentral)



