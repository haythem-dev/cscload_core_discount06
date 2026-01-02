
-- zgrppflege
select * from zgrppflege order by datum, dezap_sa, key_gruppe

insert into zgrppflege
select distinct key_gruppe, cast(to_char(current, '%Y%m%d') as integer), dezap_sa from zgrppflege where datum > 20100418
and key_gruppe||'_'||dezap_sa not in (select key_gruppe||'_'||dezap_sa from zgrppflege where datum = cast(to_char(current, '%Y%m%d') as integer))


-- zpznpflege
select * from zpznpflege order by datum, dezap_sa, artikel_nr

insert into zpznpflege
select distinct artikel_nr, cast(to_char(current, '%Y%m%d') as integer), dezap_sa from zpznpflege where datum > 20100418
and dezap_sa != '28' 
and artikel_nr||'_'||dezap_sa not in (select artikel_nr||'_'||dezap_sa from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer))


-- zapflege
select * from zapflege order by datum, artikel_nr

insert into zapflege
select distinct artikel_nr, cast(to_char(current, '%Y%m%d') as integer) from zapflege where datum > 20100728
and artikel_nr not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))

-- insert into zapflege
-- select artikel_nr, cast(to_char(current, '%Y%m%d') as integer) from zartikel where ((datum_aender > 20100131 and datum_aender < 20100203) or (datum_anlage > 20100131 and datum_anlage < 20100203 and 
-- datum_aender = 0)) and artikel_nr not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))


-- zgrppflege für zzahlbed --> muss auf zpps1:zpps1de laufen
insert into zgrppflege 
select zahlungsbedingung,  cast(to_char(current, '%Y%m%d') as integer), '27' from zzahlbed where datum_aender > 20100418
and zahlungsbedingung not in (select key_gruppe from zgrppflege where datum = cast(to_char(current, '%Y%m%d') as integer))

