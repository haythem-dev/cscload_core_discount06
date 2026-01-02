DELETE FROM ich21@zdev21_tcp:zartikel WHERE artikel_nr BETWEEN 30000 AND 30015;
INSERT INTO ich21@zdev21_tcp:zartikel(artikel_nr,artikel_nr_herst,hersteller_nr,bearbeiter,datum_anlage,artikel_mc,artikel_name) 
SELECT * 
FROM TABLE(LIST{
  ROW(30000, 30000, 2726, 'massupda'::char(8), 20220810, 'NTTEST_ALPHA'::char(12), 'NTTest: NATRA Rabatte         '::char(30)),
  ROW(30001, 30001, 2726, 'massupda'::char(8), 20220810, 'NTTEST_BETA'::char(12),  'NTTest: %-Cash schlägt NATRA  '::char(30)),
  ROW(30002, 30002, 2726, 'massupda'::char(8), 20220810, 'NTTEST_GAMMA'::char(12), 'NTTest: NATRA statt 0%-Cash   '::char(30)),
  ROW(30003, 30003, 2726, 'massupda'::char(8), 20220810, 'NTTEST_DELTA'::char(12), 'NTTest: Verschiedene %-Cash   '::char(30)),
  ROW(30004, 30004, 2726, 'massupda'::char(8), 20220810, 'NTTEST_EPSIL'::char(12), 'NTTest: 2 von 4 Cash gültig   '::char(30)),
  ROW(30005, 30005, 2726, 'massupda'::char(8), 20220810, 'NTTEST_ZETA'::char(12),  'NTTest: Kein %-Cash Rabatt    '::char(30)),
  ROW(30006, 30006, 2726, 'massupda'::char(8), 20220810, 'NTTEST_ETA'::char(12),   'NTTest: Discounttyp 13 - TENA '::char(30)),
  ROW(30007, 30007, 2726, 'massupda'::char(8), 20220810, 'NTTEST_THETA'::char(12), 'NTTest: Discounttyp 14 - Auf. '::char(30)),
  ROW(30008, 30008, 2726, 'massupda'::char(8), 20220810, 'NTTEST_IOTA'::char(12),  'NTTest: Ungültige Flags       '::char(30)),
  ROW(30009, 30009, 2726, 'massupda'::char(8), 20220810, 'NTTEST_KAPPA'::char(12), 'NTTest: Kappa                 '::char(30)),
  ROW(30010, 30010, 2726, 'massupda'::char(8), 20220810, 'NTTEST_LAMBD'::char(12), 'NTTest: Lambda                '::char(30)),
  ROW(30011, 30011, 2726, 'massupda'::char(8), 20220810, 'NTTEST_MY'::char(12),    'NTTest: My                    '::char(30)),
  ROW(30012, 30012, 2726, 'massupda'::char(8), 20220810, 'NTTEST_NY'::char(12),    'NTTest: Ny                    '::char(30)),
  ROW(30013, 30013, 2726, 'massupda'::char(8), 20220810, 'NTTEST_XI'::char(12),    'NTTest: Xi                    '::char(30)),
  ROW(30014, 30014, 2726, 'massupda'::char(8), 20220810, 'NTTEST_OMIKR'::char(12), 'NTTest: Omikron               '::char(30)),
  ROW(30015, 30015, 2726, 'massupda'::char(8), 20220810, 'NTTEST_PI'::char(12),    'NTTest: Pi                    '::char(30))
}) T(artikel_nr,artikel_nr_herst,hersteller_nr,bearbeiter,datum_anlage,artikel_mc,artikel_name);

-- Meldung im Rabatt-View: Artikel-Code unbekannt!
-- ==> Prüfung in pharmos.base.eklibs\dev\src\phxlib\lsarticlecodes.cpp:
-- long CLsArticleCodes::getArticleNoByCode( CString& articleCode, CString& cErrmld )
-- e.g.: SELECT article_code FROM carticlecodes WHERE articleno = 30000
--              AND preferred_flag = 1
--              AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)

DELETE FROM ich21@zdev21_tcp:carticlecodes WHERE articleno BETWEEN 30000 AND 30015;
INSERT INTO ich21@zdev21_tcp:carticlecodes(articleno,code_type,article_code,serial_number,preferred_flag,date_changed) 
SELECT * 
FROM TABLE(LIST{
  ROW(30000, 11, '30000'::char(25), 0, 0, 20220810),
  ROW(30001, 11, '30001'::char(25), 0, 0, 20220810),
  ROW(30002, 11, '30002'::char(25), 0, 0, 20220810),
  ROW(30003, 11, '30003'::char(25), 0, 0, 20220810),
  ROW(30004, 11, '30004'::char(25), 0, 0, 20220810),
  ROW(30005, 22, '30005'::char(25), 0, 0, 20220810),
  ROW(30006, 11, '30006'::char(25), 0, 0, 20220810),
  ROW(30007, 22, '30007'::char(25), 0, 0, 20220810),
  ROW(30008, 22, '30008'::char(25), 0, 0, 20220810),
  ROW(30009, 11, '30009'::char(25), 0, 0, 20220810),
  ROW(30010, 11, '30010'::char(25), 0, 0, 20220810),
  ROW(30011, 22, '30011'::char(25), 0, 0, 20220810),
  ROW(30012, 22, '30012'::char(25), 0, 0, 20220810),
  ROW(30013, 11, '30013'::char(25), 0, 0, 20220810),
  ROW(30014, 11, '30014'::char(25), 0, 0, 20220810),
  ROW(30015, 22, '30015'::char(25), 0, 0, 20220810)
}) T(articleno,code_type,article_code,serial_number,preferred_flag,date_changed);
