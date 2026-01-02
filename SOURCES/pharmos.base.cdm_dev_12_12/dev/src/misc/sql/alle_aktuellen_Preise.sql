select * from zartpreis as a where artikel_nr in
(select artikel_nr from zartikel as b) and
datumgueltigab = (select max(datumgueltigab) from zartpreis as c
where a.artikel_nr = c.artikel_nr) 
into temp r1
