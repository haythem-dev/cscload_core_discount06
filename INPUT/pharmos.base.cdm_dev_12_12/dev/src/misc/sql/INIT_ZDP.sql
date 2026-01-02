select count(artikel_nr),
--niedrspanne_elac
--niedrspanne_sonst
--amg_ausnahmereg
--zulass_gener
--abschlag_130
--sidablatt
--rundung_std_mge
--nicht_ueber_dafue
--bestell_nur_ozek 
homoeopathikum 
from zartikel group by 2 order by 1 desc


update zartikel set niedrspanne_elac = '0' where niedrspanne_elac = ' ' ;
update zartikel set niedrspanne_sonst = '0' where niedrspanne_sonst = ' ' ;
update zartikel set amg_ausnahmereg = '0' where amg_ausnahmereg = ' ' ;
update zartikel set zulass_gener = '0' where zulass_gener = ' ' ;
update zartikel set abschlag_130 = '0' where abschlag_130 = ' ' ;
update zartikel set sidablatt = '0' where sidablatt = ' ' ;
update zartikel set rundung_std_mge = '0' where rundung_std_mge = ' ' ;
update zartikel set nicht_ueber_dafue = '0' where nicht_ueber_dafue = ' ' ;
update zartikel set nicht_ueber_xml = '0' where nicht_ueber_xml = ' ' ;
update zartikel set bestell_nur_ozek = '0' where bestell_nur_ozek = ' ' ;

update zartikel set homoeopathikum = '0' where homoeopathikum = ' ' ;
update zartikel set anthroposophikum = '0' where anthroposophikum = ' ' ;
update zartikel set phytopharmakon = '0' where phytopharmakon = ' ' ;
update zartikel set trezeptarznei = '0' where trezeptarznei = ' ' ;
update zartikel set amg_47 = '0' where amg_47 = ' ' ;
update zartikel set batteriegesetz = '0' where batteriegesetz = ' ' ;

update zartikel set nem_phagropruefung = '0' where nem_phagropruefung = ' ' 
update zartikel set nem_zertifikat = '0' where nem_zertifikat = ' ' 
update zartikel set bestell_nicht_ausl = '0' where bestell_nicht_ausl = ' ' 
update zartikel set ean_nichtvorhanden = '0' where ean_nichtvorhanden = ' ' 

update zartikel set faelsch_gefahr = '0' where faelsch_gefahr = ' ' 
--and artikel_nr >= 0 and artikel_nr < 1000000;
--and artikel_nr >= 1000000 and artikel_nr < 2000000;
--and artikel_nr >= 2000000 and artikel_nr < 3000000;
--and artikel_nr >= 3000000 and artikel_nr < 4000000;
--and artikel_nr >= 4000000 and artikel_nr < 5000000;
--and artikel_nr >= 5000000 and artikel_nr < 6000000;
--and artikel_nr >= 6000000 and artikel_nr < 7000000;
--and artikel_nr >= 7000000 and artikel_nr < 8000000;
--and artikel_nr >= 8000000 and artikel_nr < 9000000;
and artikel_nr >= 9000000





