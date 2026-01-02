unload to 'C:\temp\fr\articles_to_delete.csv' delimiter ';'
select * from zartikel where hersteller_nr in (19, 11244, 11257, 11606, 11729) order by 1
select * from herstel where  hersteller_nr in (19, 11244, 11257, 11606, 11729);

update zartikel set artikel_geloescht = '1', datum_aender = 20160913 where  hersteller_nr in (19, 11244, 11257, 11606, 11729);

insert into zapflege (artikel_nr, datum)
select artikel_nr, '20160913' from zartikel where  hersteller_nr in (19, 11244, 11257, 11606, 11729) and artikel_nr not in (select artikel_nr from zapflege where datum = 20160913);

1)	set the delete flag for this article (in article page 2, see first screenshot)
2)	one day later (after the delete flag has been transferred to Pharmos) order job JSA670 for all prewholesale branches (this job deletes all articles with delete flag in Pharmos)
3)	after feedback that the job has run successfully you can delete either a single article or all articles with delete flag by using the 2 respective functionalities in the ZDP mask "charge relations"
