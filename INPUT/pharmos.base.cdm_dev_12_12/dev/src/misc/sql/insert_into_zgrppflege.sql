select "0000"||to_char(hersteller_nr) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '20' as z from herstel where hersteller_nr < 10 and 0000||to_char(hersteller_nr) not in (select key_gruppe from zgrppflege where dezap_sa = '20' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "000"||to_char(hersteller_nr) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '20' as z from herstel where hersteller_nr >= 10 and hersteller_nr < 100 and 000||to_char(hersteller_nr) not in (select key_gruppe from zgrppflege where dezap_sa = '20' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "00"||to_char(hersteller_nr) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '20' as z from herstel where hersteller_nr >= 100 and hersteller_nr < 1000 and 00||to_char(hersteller_nr) not in (select key_gruppe from zgrppflege where dezap_sa = '20' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "0"||to_char(hersteller_nr) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '20' as z from herstel where hersteller_nr >= 1000 and hersteller_nr < 10000 and 0||to_char(hersteller_nr) not in (select key_gruppe from zgrppflege where dezap_sa = '20' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select to_char(hersteller_nr) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '20' as z from herstel where hersteller_nr >= 10000 and to_char(hersteller_nr) not in (select key_gruppe from zgrppflege where dezap_sa = '20' and datum = cast(to_char(current, '%Y%m%d') as integer))
into temp raab1

select "00"||to_char(service_no) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '30' as z from cservices where service_no < 10 and "00"||to_char(service_no)  not in (select key_gruppe from zgrppflege where dezap_sa = '30' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "0"||to_char(service_no) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '30' as z from cservices where service_no >= 10 and service_no < 100 and "0"||to_char(service_no)  not in (select key_gruppe from zgrppflege where dezap_sa = '30' and datum = cast(to_char(current, '%Y%m%d') as integer))
into temp raab1

drop table raab1

insert into zgrppflege
select * from raab1

select * from zgrppflege where dezap_sa = '30' and datum = 20091117


