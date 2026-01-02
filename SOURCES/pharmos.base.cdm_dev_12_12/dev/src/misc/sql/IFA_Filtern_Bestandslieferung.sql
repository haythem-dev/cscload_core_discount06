delete from zifaoart;

load from 'C:\IFA\IFAOART_20121129\zifaoart.txt'
insert into zifaoart;

delete from zifaart where ifanr in (20121210, 20121211, 20121214);

-----------------

create temp table th_zifaoart(
ii char(10),
satz char(1),
A00PZN integer,
a00gdat integer,
A00PBEZ char (26),
A00PGMENG char (7),
A00PGEINH char(2),
A00DARFO char(3), 
A00ANBNR integer, 
A00ATYP char(2),
a00lkz char(1),
A00EAN char(13),
A00ARTNR char(18),
A00HMNR char(11),
A00PNAM char(50),
A00WGA char(2),
A00PPN char(12),
a05gdat integer,
A05VFDAT char(2),
A05LZEIT integer,
A05KKETTE char(2),
A05TMAX char(4),
A05TMIN  char(4),
A05LICHT char(2),
A05FEUCHT char(2),
A05LAGE char(2),
A05ZERBR char(2),
A05EICH char(2),
A05LZEICH char(2),
a04gdat integer,
A04LAENGE char(6),
A04HOEHE char(6),
A04BREITE char(6),
A04GWCHT char(6),
A04VPART char(2),
A04MBEST char(6),
a01gdat integer,
s1 char(1),
s2 char(1),
s3 char(1),
s4 char(1),
s5 char(1),
s6 char(1),
s7 char(1),
s8 char(1),
A01KAEPDM decimal(10,2),
A01GEPDM decimal(10,2),
A01AMPVSGB char(2),
A01AMPVAMG char(2),
A01AEPDM  decimal(10,2),
A01AVPDM decimal(10,2),
A01UVP decimal(10,2),
A01ZBV decimal(10,2),
A01MWST char(2),
A01ERSTATT decimal(10,2),
A01AB130A2 decimal(10,2),
A01RESERV1 decimal(10,2),
A01RESERV2 decimal(10,2),
A01RESERV3 decimal(10,2),
a02gdat integer,
A02AM char(2),
A02MP char(2),
A02APPFL char(2),
A02VSPFL char(2),
A02BTM char(2),
A02TFG char(2),
A02DROCH char(2),
A02TIERAM char(2),
A02NEGLIS char(2),
A02HMZV char(2),
A02LIFSTYL char(2),
A02HOMOEO char(2),
A02ANTHRO char(2),
A02PHYTO char(2),
A02AUSNREI char(2),
A02GENER char(2),
A02SDB char(2),
A02ZULREG char(30), 
A02LEBENSM char(2), 
A02NEM char(2),
A02DIAET char(2),
A02BIOZID char(2),
A02PSM char(2),
A02TREZEP char(2),
A0247AMG char(2),
A02130A18 char(2),
A02130A1A8 char(2),
A02VERIFIZ char(2),
A0252B char(2),
A02BIOSIEG char(2),
A02KOSMET char(2),
A02STERIL char(2),
A02RESERV1 char(2),
A02RESERV2 char(2),
A02RESERV3 char(2),
a03gdat integer,
A03VTSTAT char(2),
A03VWGGH char(2),
A03VWGAPO char(2),
A03VWGKAP char(2),
A03VWGSEH char(2),
A03VKSTAT char(2),
a06gdat integer,
A06PZNNF integer,
A06PZNORIG integer,
a09gdat integer,
A09THGP char(2)
);

create unique index i_TH on th_zifaoart (a00pzn);

--drop table th_zifaoart
1. + letzte 2 Zeilen aus File entfernen.
letztes ";" pro Zeile entfernen (letzte Zeile!)
Umlaute ersetzen     http://www.torsten-horn.de/techdocs/ascii.htm
    { 129,  252 },    /* ¸  -  Å */
    { 132,  228 },    /* ‰  -  Ñ */
    { 142,  196 },    /* ƒ  -  é */
    { 148,  246 },    /* ˆ - î */
    { 153,  214 },    /* ÷ -  ô */
    { 154,  220 },    /* ‹  -  ö */
    { 225,  223 },    /* ﬂ  -  · */

select count(*) from th_zifaoart;
delete from th_zifaoart;

load from 'C:\ifa\liefd002.ild' delimiter ';'
insert into th_zifaoart;


// Lˆschungen sichern
select a00pzn from zifaoart where a00pzn not in (select a00pzn from th_zifaoart)
into temp th_zifaoart_loesch

select * from th_zifaoart_loesch


// kein G¸ltigkeitsdatum ab 2013
delete from th_zifaoart where a00gdat < 20130101 and a05gdat < 20130101 and a04gdat < 20130101 and a01gdat < 20130101 and a02gdat < 20130101 and a03gdat < 20130101 and a06gdat < 20130101 and a09gdat < 20130101 ;

// Lˆsch-KZ
delete from th_zifaoart where a00lkz = 'X' or satz = '2';

// Preise : 100
update th_zifaoart set 
A01KAEPDM = A01KAEPDM / 100,
A01GEPDM = A01GEPDM / 100,
A01AEPDM = A01AEPDM / 100,
A01AVPDM = A01AVPDM / 100,
A01ZBV = A01ZBV / 100,
A01UVP = A01UVP / 100,
A01ERSTATT = A01ERSTATT / 100,
A01AB130A2 = A01AB130A2  / 100,
A01RESERV1 = A01RESERV1 / 100,
A01RESERV2 = A01RESERV2 / 100,
A01RESERV3 = A01RESERV3 / 100;



// PZN¥s komplett identischer Datens‰tze in temp table und anschlieﬂend aus th_zifaoart lˆschen
select th.a00pzn from th_zifaoart th, zifaoart z where th.a00pzn = z.a00pzn
and th.A00PBEZ = z.A00PBEZ 
and th.A00PGMENG = z.A00PGMENG
and th.A00PGEINH  = z.A00PGEINH
and th.A00DARFO  = z.A00DARFO
and th.A00ANBNR  = z.A00ANBNR
and th.A00ATYP  = z.A00ATYP
and th.A00EAN  = z.A00EAN
and th.A00ARTNR  = z.A00ARTNR
and th.A00HMNR  = z.A00HMNR
and th.A00PNAM  = z.A00PNAM 
and th.A00WGA  = z.A00WGA
and th.A00PPN  = z.A00PPN
and th.A05VFDAT  = z.A05VFDAT
and th.A05LZEIT  = z.A05LZEIT
and th.A05KKETTE  = z.A05KKETTE
and th.A05TMAX  = z.A05TMAX
and th.A05TMIN   = z.A05TMIN
and th.A05LICHT  = z.A05LICHT
and th.A05FEUCHT  = z.A05FEUCHT
and th.A05LAGE  = z.A05LAGE
and th.A05ZERBR  = z.A05ZERBR
and th.A05EICH  = z.A05EICH
and th.A05LZEICH  = z.A05LZEICH
and th.A04LAENGE  = z.A04LAENGE
and th.A04HOEHE  = z.A04HOEHE
and th.A04BREITE  = z.A04BREITE
and th.A04GWCHT  = z.A04GWCHT
and th.A04VPART  = z.A04VPART
and th.A04MBEST  = z.A04MBEST
and th.A01KAEPDM  = z.A01KAEPDM
and th.A01GEPDM  = z.A01GEPDM
and th.A01AMPVSGB  = z.A01AMPVSGB
and th.A01AMPVAMG  = z.A01AMPVAMG
and th.A01AEPDM   = z.A01AEPDM
and th.A01AVPDM  = z.A01AVPDM
and th.A01ZBV  = z.A01ZBV
and th.A01UVP  = z.A01UVP
and th.A01MWST  = z.A01MWST
and th.A01ERSTATT  = z.A01ERSTATT
and th.A01AB130A2  = z.A01AB130A2
and th.A01RESERV1  = z.A01RESERV1
and th.A01RESERV2  = z.A01RESERV2
and th.A01RESERV3  = z.A01RESERV3
and th.A02AM  = z.A02AM
and th.A02MP  = z.A02MP
and th.A02APPFL  = z.A02APPFL
and th.A02VSPFL  = z.A02VSPFL
and th.A02BTM  = z.A02BTM
and th.A02TFG  = z.A02TFG
and th.A02DROCH  = z.A02DROCH
and th.A02TIERAM  = z.A02TIERAM
and th.A02NEGLIS  = z.A02NEGLIS
and th.A02HMZV  = z.A02HMZV
and th.A02LIFSTYL  = z.A02LIFSTYL
and th.A02HOMOEO  = z.A02HOMOEO
and th.A02ANTHRO  = z.A02ANTHRO
and th.A02PHYTO  = z.A02PHYTO
and th.A02AUSNREI  = z.A02AUSNREI
and th.A02GENER  = z.A02GENER
and th.A02SDB  = z.A02SDB
and th.A02ZULREG  = z.A02ZULREG
and th.A02LEBENSM  = z.A02LEBENSM
and th.A02NEM  = z.A02NEM
and th.A02DIAET  = z.A02DIAET
and th.A02BIOZID  = z.A02BIOZID
and th.A02BIOSIEG   = z.A02BIOSIEG
and th.A02KOSMET   = z.A02KOSMET
and th.A02STERIL   = z.A02STERIL
and th.A02PSM  = z.A02PSM
and th.A02TREZEP  = z.A02TREZEP
and th.A0247AMG  = z.A0247AMG
and th.A02130A18  = z.A02130A18
and th.A02130A1A8  = z.A02130A1A8
and th.A02VERIFIZ  = z.A02VERIFIZ
and th.A0252B  = z.A0252B
and th.A02RESERV1  = z.A02RESERV1
and th.A02RESERV2  = z.A02RESERV2
and th.A02RESERV3  = z.A02RESERV3
and th.A03VTSTAT  = z.A03VTSTAT
and th.A03VWGGH  = z.A03VWGGH
and th.A03VWGAPO  = z.A03VWGAPO
and th.A03VWGKAP  = z.A03VWGKAP
and th.A03VWGSEH  = z.A03VWGSEH
and th.A03VKSTAT  = z.A03VKSTAT
and th.A06PZNNF  = z.A06PZNNF
and th.A06PZNORIG  = z.A06PZNORIG
and th.A09THGP  = z.A09THGP
into temp th

select * from th

drop table th

create unique index i_th2 on th (a00pzn);
delete from th_zifaoart where a00pzn in (select a00pzn from th);


// Identische Felder in th_zifaoart leeren
select ii, 
CASE WHEN th.A00PZN IN (SELECT A00PZN from zifaoart) THEN '3' ELSE '1' END as satz11,
lpad (th.A00PZN, 8, '0') as A00PZN,
CASE WHEN th.a00gdat < 20130101 THEN '' ELSE cast(th.a00gdat as char(8)) END as a00gdat,
CASE WHEN th.A00PBEZ = z.A00PBEZ THEN '' ELSE trim(th.A00PBEZ) END as A00PBEZ,
CASE WHEN th.A00PGMENG = z.A00PGMENG THEN '' ELSE trim(th.A00PGMENG) END as A00PGMENG,
CASE WHEN th.A00PGEINH  = z.A00PGEINH THEN '' ELSE trim(th.A00PGEINH) END as A00PGEINH,
CASE WHEN th.A00DARFO  = z.A00DARFO THEN '' ELSE trim(th.A00DARFO) END as A00DARFO,
CASE WHEN th.A00ANBNR  = z.A00ANBNR THEN '' ELSE trim(cast(th.A00ANBNR as char(5))) END as A00ANBNR,
CASE WHEN th.A00ATYP  = z.A00ATYP THEN '' ELSE th.A00ATYP END as A00ATYP,
th.a00lkz,
CASE WHEN th.A00EAN  = z.A00EAN THEN '' ELSE trim(th.A00EAN) END as A00EAN,
CASE WHEN th.A00ARTNR  = z.A00ARTNR THEN '' WHEN length(trim(th.A00ARTNR)) = 0 THEN ' ' ELSE trim(th.A00ARTNR) END as A00ARTNR,
CASE WHEN th.A00HMNR  = z.A00HMNR THEN '' ELSE trim(cast(th.A00HMNR as char(10))) END as A00HMNR,
CASE WHEN th.A00PNAM  = z.A00PNAM  THEN '' WHEN length(trim(th.A00PNAM)) = 0 THEN ' ' ELSE trim(th.A00PNAM) END as A00PNAM,
CASE WHEN th.A00WGA  = z.A00WGA THEN '' ELSE th.A00WGA END as A00WGA,
CASE WHEN th.A00PPN  = z.A00PPN THEN '' ELSE trim(th.A00PPN) END as A00PPN,
CASE WHEN th.a05gdat < 20130101 THEN '' ELSE cast(th.a05gdat as char(8)) END as a05gdat,
CASE WHEN th.A05VFDAT  = z.A05VFDAT THEN '' ELSE th.A05VFDAT END as A05VFDAT,
CASE WHEN th.A05LZEIT  = z.A05LZEIT THEN '' ELSE trim(cast(th.A05LZEIT as char(3))) END as A05LZEIT,
CASE WHEN th.A05KKETTE  = z.A05KKETTE THEN '' ELSE th.A05KKETTE END as A05KKETTE,
CASE WHEN th.A05TMAX  = z.A05TMAX THEN '' WHEN length(trim(th.A05TMAX)) = 0 THEN ' ' ELSE trim(th.A05TMAX) END as A05TMAX,
CASE WHEN th.A05TMIN   = z.A05TMIN THEN '' WHEN length(trim(th.A05TMIN)) = 0 THEN ' ' ELSE trim(th.A05TMIN) END as A05TMIN,
CASE WHEN th.A05LICHT  = z.A05LICHT THEN '' ELSE th.A05LICHT END as A05LICHT,
CASE WHEN th.A05FEUCHT  = z.A05FEUCHT THEN '' ELSE th.A05FEUCHT END as A05FEUCHT,
CASE WHEN th.A05LAGE  = z.A05LAGE THEN '' ELSE th.A05LAGE END as A05LAGE,
CASE WHEN th.A05ZERBR  = z.A05ZERBR THEN '' ELSE th.A05ZERBR END as A05ZERBR,
CASE WHEN th.A05EICH  = z.A05EICH THEN '' ELSE th.A05EICH END as A05EICH,
CASE WHEN th.A05LZEICH  = z.A05LZEICH THEN '' ELSE trim(cast(th.A05LZEICH as char(3))) END as A05LZEICH,
CASE WHEN th.a04gdat < 20130101 THEN '' ELSE cast(th.a04gdat as char(8)) END as a04gdat,
CASE WHEN th.A04LAENGE  = z.A04LAENGE THEN '' WHEN length(trim(th.A04LAENGE)) = 0 THEN ' ' ELSE trim(th.A04LAENGE) END as A04LAENGE,
CASE WHEN th.A04HOEHE  = z.A04HOEHE THEN '' WHEN length(trim(th.A04HOEHE)) = 0 THEN ' ' ELSE trim(th.A04HOEHE) END as A04HOEHE,
CASE WHEN th.A04BREITE  = z.A04BREITE THEN '' WHEN length(trim(th.A04BREITE)) = 0 THEN ' ' ELSE trim(th.A04BREITE) END as A04BREITE,
CASE WHEN th.A04GWCHT  = z.A04GWCHT THEN '' WHEN length(trim(th.A04GWCHT)) = 0 THEN ' ' ELSE trim(th.A04GWCHT) END as A04GWCHT,
CASE WHEN th.A04VPART  = z.A04VPART THEN '' ELSE th.A04VPART END as A04VPART,
CASE WHEN th.A04MBEST  = z.A04MBEST THEN '' WHEN length(trim(th.A04MBEST)) = 0 THEN ' ' ELSE trim(th.A04MBEST) END as A04MBEST,
CASE WHEN th.a01gdat < 20130101 THEN '' ELSE cast(th.a01gdat as char(8)) END as a01gdat,
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01KAEPDM > z.A01KAEPDM THEN '4' WHEN   th.A01KAEPDM < z.A01KAEPDM THEN '5' ELSE '' END as s1, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01GEPDM > z.A01GEPDM THEN '4' WHEN   th.A01GEPDM < z.A01GEPDM THEN '5' ELSE '' END as s2, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01AEPDM > z.A01AEPDM THEN '4' WHEN   th.A01AEPDM < z.A01AEPDM THEN '5' ELSE '' END as s3, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01AVPDM > z.A01AVPDM THEN '4' WHEN   th.A01AVPDM < z.A01AVPDM THEN '5' ELSE '' END as s4, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01UVP > z.A01UVP THEN '4' WHEN   th.A01UVP < z.A01UVP THEN '5' ELSE '' END as s5, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01ZBV > z.A01ZBV THEN '4' WHEN   th.A01ZBV < z.A01ZBV THEN '5' ELSE '' END as s6, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01ERSTATT > z.A01ERSTATT THEN '4' WHEN   th.A01ERSTATT < z.A01ERSTATT THEN '5' ELSE '' END as s7, 
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '1' WHEN  th.A01AB130A2 > z.A01AB130A2 THEN '4' WHEN   th.A01AB130A2 < z.A01AB130A2 THEN '5' ELSE '' END as s8, 
CASE WHEN th.A01KAEPDM  = z.A01KAEPDM THEN '' ELSE trim(cast(cast(th.A01KAEPDM * 100 as integer) as char(10))) END as A01KAEPDM,
CASE WHEN th.A01GEPDM  = z.A01GEPDM THEN '' ELSE trim(cast(cast(th.A01GEPDM * 100 as integer) as char(10))) END as A01GEPDM,
CASE WHEN th.A01AMPVSGB  = z.A01AMPVSGB THEN '' ELSE th.A01AMPVSGB END as A01AMPVSGB,
CASE WHEN th.A01AMPVAMG  = z.A01AMPVAMG THEN '' ELSE th.A01AMPVAMG END as A01AMPVAMG,
CASE WHEN th.A01AEPDM   = z.A01AEPDM THEN '' ELSE trim(cast(cast(th.A01AEPDM * 100 as integer) as char(10))) END as A01AEPDM,
CASE WHEN th.A01AVPDM  = z.A01AVPDM THEN '' ELSE trim(cast(cast(th.A01AVPDM * 100 as integer) as char(10))) END as A01AVPDM,
CASE WHEN th.A01UVP  = z.A01UVP THEN '' ELSE trim(cast(cast(th.A01UVP * 100 as integer) as char(10))) END as A01UVP,
CASE WHEN th.A01ZBV  = z.A01ZBV THEN '' ELSE trim(cast(cast(th.A01ZBV * 100 as integer) as char(10))) END as A01ZBV,
CASE WHEN th.A01MWST  = z.A01MWST THEN '' ELSE th.A01MWST END as A01MWST,
CASE WHEN th.A01ERSTATT  = z.A01ERSTATT THEN '' ELSE trim(cast(cast(th.A01ERSTATT * 100 as integer) as char(10))) END as A01ERSTATT,
CASE WHEN th.A01AB130A2  = z.A01AB130A2 THEN '' ELSE trim(cast(cast(th.A01AB130A2 * 100 as integer) as char(10))) END as A01AB130A2,
CASE WHEN th.A01RESERV1  = z.A01RESERV1 THEN '' ELSE trim(cast(cast(th.A01RESERV1 * 100 as integer) as char(10))) END as A01RESERV1,
CASE WHEN th.A01RESERV2  = z.A01RESERV2 THEN '' ELSE trim(cast(cast(th.A01RESERV2 * 100 as integer) as char(10))) END as A01RESERV2,
CASE WHEN th.A01RESERV3  = z.A01RESERV3 THEN '' ELSE trim(cast(cast(th.A01RESERV3 * 100 as integer) as char(10))) END as A01RESERV3,
CASE WHEN th.a02gdat < 20130101 THEN '' ELSE cast(th.a02gdat as char(8)) END as a02gdat,
CASE WHEN th.A02AM  = z.A02AM THEN '' ELSE th.A02AM END as A02AM,
CASE WHEN th.A02MP  = z.A02MP THEN '' ELSE th.A02MP END as A02MP,
CASE WHEN th.A02APPFL  = z.A02APPFL THEN '' ELSE th.A02APPFL END as A02APPFL,
CASE WHEN th.A02VSPFL  = z.A02VSPFL THEN '' ELSE th.A02VSPFL END as A02VSPFL,
CASE WHEN th.A02BTM  = z.A02BTM THEN '' ELSE th.A02BTM END as A02BTM,
CASE WHEN th.A02TFG  = z.A02TFG THEN '' ELSE th.A02TFG END as A02TFG,
CASE WHEN th.A02DROCH  = z.A02DROCH THEN '' ELSE th.A02DROCH END as A02DROCH,
CASE WHEN th.A02TIERAM  = z.A02TIERAM THEN '' ELSE th.A02TIERAM END as A02TIERAM,
CASE WHEN th.A02NEGLIS  = z.A02NEGLIS THEN '' ELSE th.A02NEGLIS END as A02NEGLIS,
CASE WHEN th.A02HMZV  = z.A02HMZV THEN '' ELSE th.A02HMZV END as A02HMZV,
CASE WHEN th.A02LIFSTYL  = z.A02LIFSTYL THEN '' ELSE th.A02LIFSTYL END as A02LIFSTYL,
CASE WHEN th.A02HOMOEO  = z.A02HOMOEO THEN '' ELSE th.A02HOMOEO END as A02HOMOEO,
CASE WHEN th.A02ANTHRO  = z.A02ANTHRO THEN '' ELSE th.A02ANTHRO END as A02ANTHRO,
CASE WHEN th.A02PHYTO  = z.A02PHYTO THEN '' ELSE th.A02PHYTO END as A02PHYTO,
CASE WHEN th.A02AUSNREI  = z.A02AUSNREI THEN '' ELSE th.A02AUSNREI END as A02AUSNREI,
CASE WHEN th.A02GENER  = z.A02GENER THEN '' ELSE th.A02GENER END as A02GENER,
CASE WHEN th.A02SDB  = z.A02SDB THEN '' ELSE th.A02SDB END as A02SDB,
CASE WHEN th.A02ZULREG  = z.A02ZULREG THEN '' WHEN length(trim(th.A02ZULREG)) = 0 THEN ' ' ELSE trim(th.A02ZULREG) END as A02ZULREG,
CASE WHEN th.A02LEBENSM  = z.A02LEBENSM THEN '' ELSE th.A02LEBENSM END as A02LEBENSM,
CASE WHEN th.A02NEM  = z.A02NEM THEN '' ELSE th.A02NEM END as A02NEM,
CASE WHEN th.A02DIAET  = z.A02DIAET THEN '' ELSE th.A02DIAET END as A02DIAET,
CASE WHEN th.A02BIOZID  = z.A02BIOZID THEN '' ELSE th.A02BIOZID END as A02BIOZID,
CASE WHEN th.A02BIOSIEG  = z.A02BIOSIEG THEN '' ELSE th.A02BIOSIEG END as A02BIOSIEG,
CASE WHEN th.A02KOSMET  = z.A02KOSMET THEN '' ELSE th.A02KOSMET END as A02KOSMET,
CASE WHEN th.A02STERIL  = z.A02STERIL THEN '' ELSE th.A02STERIL END as A02STERIL,
CASE WHEN th.A02PSM  = z.A02PSM THEN '' ELSE th.A02PSM END as A02PSM,
CASE WHEN th.A02TREZEP  = z.A02TREZEP THEN '' ELSE th.A02TREZEP END as A02TREZEP,
CASE WHEN th.A0247AMG  = z.A0247AMG THEN '' ELSE th.A0247AMG END as A0247AMG,
CASE WHEN th.A02130A18  = z.A02130A18 THEN '' ELSE th.A02130A18 END as A02130A18,
CASE WHEN th.A02130A1A8  = z.A02130A1A8 THEN '' ELSE th.A02130A1A8 END as A02130A1A8,
CASE WHEN th.A02VERIFIZ  = z.A02VERIFIZ THEN '' ELSE th.A02VERIFIZ END as A02VERIFIZ,
CASE WHEN th.A0252B  = z.A0252B THEN '' ELSE th.A0252B END as A0252B,
CASE WHEN th.A02RESERV1  = z.A02RESERV1 THEN '' WHEN length(trim(th.A02RESERV1)) = 0 THEN '  ' ELSE trim(th.A02RESERV1) END as A02RESERV1,
CASE WHEN th.A02RESERV2  = z.A02RESERV2 THEN '' WHEN length(trim(th.A02RESERV2)) = 0 THEN '  ' ELSE trim(th.A02RESERV2) END as A02RESERV2,
CASE WHEN th.A02RESERV3  = z.A02RESERV3 THEN '' WHEN length(trim(th.A02RESERV3)) = 0 THEN '  ' ELSE trim(th.A02RESERV3) END as A02RESERV3,
CASE WHEN th.a03gdat < 20130101 THEN '' ELSE cast(th.a03gdat as char(8)) END as a03gdat,
CASE WHEN th.A03VTSTAT  = z.A03VTSTAT THEN '' ELSE th.A03VTSTAT END as A03VTSTAT,
CASE WHEN th.A03VWGGH  = z.A03VWGGH THEN '' ELSE th.A03VWGGH END as A03VWGGH,
CASE WHEN th.A03VWGAPO  = z.A03VWGAPO THEN '' ELSE th.A03VWGAPO END as A03VWGAPO,
CASE WHEN th.A03VWGKAP  = z.A03VWGKAP THEN '' ELSE th.A03VWGKAP END as A03VWGKAP,
CASE WHEN th.A03VWGSEH  = z.A03VWGSEH THEN '' ELSE th.A03VWGSEH END as A03VWGSEH,
CASE WHEN th.A03VKSTAT  = z.A03VKSTAT THEN '' ELSE th.A03VKSTAT END as A03VKSTAT,
CASE WHEN  th.A00PZN NOT IN (SELECT A00PZN from zifaoart) THEN '00000000' WHEN th.a06gdat < 20130101 THEN '' ELSE cast(th.a06gdat as char(8)) END as a06gdat,
CASE WHEN th.A06PZNNF  = z.A06PZNNF THEN '' ELSE cast(lpad (th.A06PZNNF, 8, '0') as char(8)) END as A06PZNNF,
CASE WHEN th.A06PZNORIG  = z.A06PZNORIG THEN '' ELSE cast(lpad (th.A06PZNORIG, 8, '0') as char(8)) END as A06PZNORIG,
CASE WHEN th.a09gdat < 20130101 THEN '' ELSE cast(th.a09gdat as char(8)) END as a09gdat,
CASE WHEN th.A09THGP  = z.A09THGP THEN '' ELSE th.A09THGP END as A09THGP
from th_zifaoart th, outer zifaoart z
where th.A00PZN = z.A00PZN
into temp th_zifaoart2;

create unique index i_th3 on th_zifaoart2 (a00pzn);

insert into th_zifaoart2 (ii, satz11, a00pzn, a00gdat, a00lkz) 
select 'IA45', '2', a00pzn, '20130101', 'X' from th_zifaoart_loesch;

select * from th_zifaoart2


--drop table th_zifaoart2


unload to 'C:\temp\ifa\xxx.txt' delimiter ';'
select * from th_zifaoart2 

---------------------------
1. + letzte 2 Zeilen in File manuell erzeugen !





















insert into th_zifaoart (a00pzn, a02biosieg, a02steril, a02kosmet) values (292, '', '', '')





select count(*) from th_zifaoart where a02biosieg != '' or a02kosmet != '' or a02steril != ''

update zifaoart set a02biosieg = (select a02biosieg  from th_zifaoart where a00pzn = zifaoart.a00pzn  ) 
update zifaoart set a02kosmet = (select a02kosmet from th_zifaoart where a00pzn = zifaoart.a00pzn ) 
update zifaoart set a02steril = (select a02steril from th_zifaoart where a00pzn = zifaoart.a00pzn ) 
where
 a00pzn >= 0 and a00pzn < 1000000;
 a00pzn >= 1000000 and a00pzn < 2000000;
 a00pzn >= 2000000 and a00pzn < 3000000;
 a00pzn >= 3000000 and a00pzn < 4000000;
 a00pzn >= 4000000 and a00pzn < 5000000;
 a00pzn >= 5000000 and a00pzn < 6000000;
 a00pzn >= 6000000 and a00pzn < 7000000;
 a00pzn >= 7000000 and a00pzn < 8000000;
 a00pzn >= 8000000 and a00pzn < 9000000;
 a00pzn >= 9000000

update zartikel set biosiegel = 1 where artikel_nr in (select a00pzn from th_zifaoart where a02biosieg = '01')
update zartikel set kosmetikum = 1 where artikel_nr in (select a00pzn from th_zifaoart where a02kosmet = '01')
update zartikel set steril = 1 where artikel_nr in (select a00pzn from th_zifaoart where a02steril = '01')


