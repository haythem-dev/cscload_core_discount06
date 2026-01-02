DELETE FROM och21@zdev21_tcp:articlecodes WHERE articleno BETWEEN 30000 AND 30015;

INSERT INTO och21@zdev21_tcp:articlecodes(articleno,code_type,article_code,preferred_flag)
SELECT * 
FROM TABLE(LIST{
  ROW(30000,11,'30000',1),
  ROW(30001,11,'30001',1),
  ROW(30002,11,'30002',1),
  ROW(30003,11,'30003',1),
  ROW(30004,11,'30004',1),
  ROW(30005,11,'30005',1),
  ROW(30006,11,'30006',1),
  ROW(30007,11,'30007',1),
  ROW(30008,11,'30008',1),
  ROW(30009,11,'30009',1),
  ROW(30010,11,'30010',1),
  ROW(30011,11,'30011',1),
  ROW(30012,11,'30012',1),
  ROW(30013,11,'30013',1),
  ROW(30014,11,'30014',1),
  ROW(30015,11,'30015',1)
}) T(articleno,code_type,article_code,preferred_flag);

DELETE FROM och21@zdev21_tcp:artikelzentral WHERE artikel_nr BETWEEN 30000 AND 30015;

INSERT INTO och21@zdev21_tcp:artikelzentral(artikel_nr,artikel_mc,hersteller_nr,importarticle,etartklasse1,darreichform,einheit,packgroesse,etartschalter1,etartschalter2,warengruppe,artikel_nr_herst,artikel_name,artikel_langname)
SELECT *
FROM TABLE(LIST{
  ROW(30000,'NTTEST_ALPHA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30000'::char(15),  'NTTest Alpha'::char(30),  'NTTest Alpha lang'::char(50)),
  ROW(30001, 'NTTEST_BETA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30001'::char(15),   'NTTest Beta'::char(30),   'NTTest Beta lang'::char(50)),
  ROW(30002,'NTTEST_GAMMA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30002'::char(15),  'NTTest Gamma'::char(30),  'NTTest Gamma lang'::char(50)),
  ROW(30003,'NTTEST_DELTA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30003'::char(15),  'NTTest Delta'::char(30),  'NTTest Delta lang'::char(50)),
  ROW(30004,'NTTEST_EPSIL'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30004'::char(15),'NTTest Epsilon'::char(30),'NTTest Epsilon lang'::char(50)),
  ROW(30005, 'NTTEST_ZETA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30005'::char(15),   'NTTest Zeta'::char(30),   'NTTest Zeta lang'::char(50)),
  ROW(30006,  'NTTEST_ETA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30006'::char(15),    'NTTest Eta'::char(30),    'NTTest Eta lang'::char(50)),
  ROW(30007,'NTTEST_THETA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30007'::char(15),  'NTTest Theta'::char(30),  'NTTest Theta lang'::char(50)),
  ROW(30008, 'NTTEST_IOTA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30008'::char(15),   'NTTest Iota'::char(30),   'NTTest Iota lang'::char(50)),
  ROW(30009,'NTTEST_KAPPA'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30009'::char(15),  'NTTest Kappa'::char(30),  'NTTest Kappa lang'::char(50)),
  ROW(30010,'NTTEST_LAMBD'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30010'::char(15), 'NTTest Lambda'::char(30), 'NTTest Lambda lang'::char(50)),
  ROW(30011,   'NTTEST_MY'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30011'::char(15),     'NTTest My'::char(30),     'NTTest My lang'::char(50)),
  ROW(30012,   'NTTEST_NY'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30012'::char(15),     'NTTest Ny'::char(30),     'NTTest Ny lang'::char(50)),
  ROW(30013,   'NTTEST_XI'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30013'::char(15),     'NTTest Xi'::char(30),     'NTTest Xi lang'::char(50)),
  ROW(30014,'NTTEST_OMIKR'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30014'::char(15),'NTTest Omikron'::char(30),'NTTest Omikron lang'::char(50)),
  ROW(30015,   'NTTEST_PI'::char(12),2726,0,4096,'SUB'::char(3),'1 ST'::char(9),1,0,10240,'11111'::char(5),'30015'::char(15),     'NTTest Pi'::char(30),     'NTTest Pi lang'::char(50))
}) T(artikel_nr,artikel_mc,hersteller_nr,importarticle,etartklasse1,darreichform,einheit,packgroesse,etartschalter1,etartschalter2,warengruppe,artikel_nr_herst,artikel_name,artikel_langname);

DELETE FROM och21@zdev21_tcp:artselect WHERE artikel_nr BETWEEN 30000 AND 30015;

INSERT INTO och21@zdev21_tcp:artselect(artikel_nr,artikel_mc,packgroesse,darreichform,einheit,artikel_name,etartschalter1,etartschalter2)
SELECT *
FROM TABLE(LIST{
  ROW(30000,'NTTEST_ALPHA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Alpha'::char(30),4096,10240),
  ROW(30001, 'NTTEST_BETA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),   'NTTest Beta'::char(30),4096,10240),
  ROW(30002,'NTTEST_GAMMA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Gamma'::char(30),4096,10240),
  ROW(30003,'NTTEST_DELTA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Delta'::char(30),4096,10240),
  ROW(30004,'NTTEST_EPSIL'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Epsil'::char(30),4096,10240),
  ROW(30005, 'NTTEST_ZETA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),   'NTTest Zeta'::char(30),4096,10240),
  ROW(30006,  'NTTEST_ETA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),    'NTTest Eta'::char(30),4096,10240),
  ROW(30007,'NTTEST_THETA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Theta'::char(30),4096,10240),
  ROW(30008, 'NTTEST_TOTA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),   'NTTest Tota'::char(30),4096,10240),
  ROW(30009,'NTTEST_KAPPA'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Kappa'::char(30),4096,10240),
  ROW(30010,'NTTEST_LAMBD'::char(12),1,'SUB'::char(3),'1 ST'::char(9),  'NTTest Lambd'::char(30),4096,10240),
  ROW(30011,   'NTTEST_MY'::char(12),1,'SUB'::char(3),'1 ST'::char(9),     'NTTest My'::char(30),4096,10240),
  ROW(30012,   'NTTEST_NY'::char(12),1,'SUB'::char(3),'1 ST'::char(9),     'NTTest Ny'::char(30),4096,10240),
  ROW(30013,   'NTTEST_XI'::char(12),1,'SUB'::char(3),'1 ST'::char(9),     'NTTest Xi'::char(30),4096,10240),
  ROW(30014,'NTTEST_OMIKR'::char(12),1,'SUB'::char(3),'1 ST'::char(9),'NTTest Omikron'::char(30),4096,10240),
  ROW(30015,   'NTTEST_PI'::char(12),1,'SUB'::char(3),'1 ST'::char(9),     'NTTest Pi'::char(30),4096,10240)
}) T(artikel_nr,artikel_mc,packgroesse,darreichform,einheit,artikel_name,etartschalter1,etartschalter2);

DELETE FROM och21@zdev21_tcp:artikelpreis WHERE artikel_nr BETWEEN 30000 AND 30015;

INSERT INTO och21@zdev21_tcp:artikelpreis(artikel_nr,datumgueltigab,datumgueltigbis,preisekapo,preisekgrosso,preisekgrossona,preisvkapo,rabattfest,rabattfestdm,preisfest,preisprozent,preisagp,preis_typ,maxavp)
SELECT *
FROM TABLE(LIST{
  ROW(30000,20220801,20221231,0.00,30.29,0.00,0.00,0.00,10.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30001,20220801,20221231,0.00,30.29,0.00,0.00,0.00,10.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30002,20220801,20221231,0.00,30.29,0.00,0.00,0.00,10.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30003,20220801,20221231,0.00,30.29,0.00,0.00,0.00,20.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30004,20220801,20221231,0.00,30.29,0.00,0.00,0.00,20.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30005,20220801,20221231,0.00,30.29,0.00,0.00,0.00,20.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30006,20220801,20221231,0.00,30.29,0.00,0.00,0.00,20.95::decimal(9,2),0.00,0.00,32.30,0,0.00),
  ROW(30007,20220801,20221231,0.00,57.29,0.00,0.00,0.00,32.95::decimal(9,2),0.00,0.00,48.30,0,0.00),
  ROW(30008,20220801,20221231,0.00,58.29,0.00,0.00,0.00,33.95::decimal(9,2),0.00,0.00,49.30,0,0.00),
  ROW(30009,20220801,20221231,0.00,49.29,0.00,0.00,0.00,34.95::decimal(9,2),0.00,0.00,50.30,0,0.00),
  ROW(30010,20220801,20221231,0.00,60.29,0.00,0.00,0.00,35.95::decimal(9,2),0.00,0.00,51.30,0,0.00),
  ROW(30011,20220801,20221231,0.00,61.29,0.00,0.00,0.00,36.95::decimal(9,2),0.00,0.00,52.30,0,0.00),
  ROW(30012,20220801,20221231,0.00,62.29,0.00,0.00,0.00,37.95::decimal(9,2),0.00,0.00,53.30,0,0.00),
  ROW(30013,20220801,20221231,0.00,21.29,0.00,0.00,0.00,26.95::decimal(9,2),0.00,0.00,42.30,0,0.00),
  ROW(30014,20220801,20221231,0.00,22.29,0.00,0.00,0.00,27.95::decimal(9,2),0.00,0.00,43.30,0,0.00),
  ROW(30015,20220801,20221231,0.00,23.29,0.00,0.00,0.00,28.95::decimal(9,2),0.00,0.00,44.30,0,0.00)
}) T(artikel_nr,datumgueltigab,datumgueltigbis,preisekapo,preisekgrosso,preisekgrossona,preisvkapo,rabattfest,rabattfestdm,preisfest,preisprozent,preisagp,preis_typ,maxavp);

DELETE FROM och21@zdev21_tcp:artikellagerort WHERE filialnr=12 AND artikel_nr BETWEEN 30000 AND 30015;

INSERT INTO och21@zdev21_tcp:artikellagerort(filialnr,artikel_nr,lagerbereichnr,stationnr,lagerfachnr,datumverfall,bestand,verbundartikel)
SELECT *
FROM TABLE(LIST{
  ROW(12,30000,1,'XA'::char(2),'ABCDEF'::char(10),3012,100,1),
  ROW(12,30001,1,'XB'::char(2),'ABCDEF'::char(10),3012,101,1),
  ROW(12,30002,1,'XC'::char(2),'ABCDEF'::char(10),3012,102,1),
  ROW(12,30003,1,'XD'::char(2),'ABCDEF'::char(10),3012,103,1),
  ROW(12,30004,1,'XE'::char(2),'ABCDEF'::char(10),3012,104,1),
  ROW(12,30005,1,'XF'::char(2),'ABCDEF'::char(10),3012,105,1),
  ROW(12,30006,1,'XG'::char(2),'ABCDEF'::char(10),3012,106,1),
  ROW(12,30007,1,'XH'::char(2),'ABCDEF'::char(10),3012,107,1),
  ROW(12,30008,1,'XI'::char(2),'ABCDEF'::char(10),3012,108,1),
  ROW(12,30009,1,'XJ'::char(2),'ABCDEF'::char(10),3012,109,1),
  ROW(12,30010,1,'XK'::char(2),'ABCDEF'::char(10),3012,110,1),
  ROW(12,30011,1,'XL'::char(2),'ABCDEF'::char(10),3012,111,1),
  ROW(12,30012,1,'XM'::char(2),'ABCDEF'::char(10),3012,112,1),
  ROW(12,30013,1,'XN'::char(2),'ABCDEF'::char(10),3012,113,1),
  ROW(12,30014,1,'XO'::char(2),'ABCDEF'::char(10),3012,114,1),
  ROW(12,30015,1,'XP'::char(2),'ABCDEF'::char(10),3012,115,1)
}) T(filialnr,artikel_nr,lagerbereichnr,stationnr,lagerfachnr,datumverfall,bestand,verbundartikel);
