DELETE FROM ich21@zdev21_tcp:artikellokal WHERE filialnr=12 AND artikel_nr BETWEEN 30000 AND 30015;
INSERT INTO ich21@zdev21_tcp:artikellokal(filialnr,artikel_nr,bestand,artikelaktiv,bestandtagesanfang,lagerbereichnr,lagerfachnr,verbundartikel,stationnr,etartschalter1,etartschalter2) 
SELECT * 
FROM TABLE(LIST{
  ROW(12,30000,100,1,110,1,14030306,1,'07',4096,10240),
  ROW(12,30001,101,1,111,1,14030306,1,'07',4096,10240),
  ROW(12,30002,102,1,112,1,14030306,1,'07',4096,10240),
  ROW(12,30003,103,1,113,1,14030306,1,'07',4096,10240),
  ROW(12,30004,104,1,114,1,14030306,1,'07',4096,10240),
  ROW(12,30005,105,1,115,1,14030306,1,'07',4096,10240),
  ROW(12,30006,106,1,116,1,14030306,1,'07',4096,10240),
  ROW(12,30007,107,1,117,1,14030306,1,'07',4096,10240),
  ROW(12,30008,108,1,114,1,14030306,1,'07',4096,10240),
  ROW(12,30009,109,1,115,1,14030306,1,'07',4096,10240),
  ROW(12,30010,110,1,116,1,14030306,1,'07',4096,10240),
  ROW(12,30011,111,1,117,1,14030306,1,'07',4096,10240),
  ROW(12,30012,112,1,118,1,14030306,1,'07',4096,10240),
  ROW(12,30013,113,1,119,1,14030306,1,'07',4096,10240),
  ROW(12,30014,114,1,120,1,14030306,1,'07',4096,10240),
  ROW(12,30015,115,1,121,1,14030306,1,'07',4096,10240)
}) T(filialnr,artikel_nr,bestand,artikelaktiv,bestandtagesanfang,lagerbereichnr,lagerfachnr,verbundartikel,stationnr,etartschalter1,etartschalter2);


-- filialnr  artikel_nr  bestand  nachfrage  zuzahlung  rabattfaehig  natrastaffelnr  prisoart  artikelaktiv  lagerbereichnr  stationnr  lagerfachnr  verbundartikel
-- --------  ----------  -------  ---------  ---------  ------------  --------------  --------  ------------  --------------  ---------  -----------  --------------
--       12     7772904      196          0             00                         0  0         1                          1  07         14030306     1             
-- 
--  etartschalter1  etartschalter2  etartschalter3  etartschalter4  etartschalter5  verkaufeinheit  containergroesse  kontigentmenge  chargenartikel  textkey
--  --------------  --------------  --------------  --------------  --------------  --------------  ----------------  --------------  --------------  -------
--               0            1025               4               0               0               0                 0               0  0                     0
-- 			   
--  bestandreserviert  wafotyp  kzrange  moreconditions  bestandtagesanfang  codeblocage  blockedforreturns
--  -----------------  -------  -------  --------------  ------------------  -----------  -----------------
--                  0  1        0        0                              196                               0
