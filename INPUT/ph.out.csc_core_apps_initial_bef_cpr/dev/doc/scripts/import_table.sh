#!/bin/bash
set -x
#Hintergrund: Bestände auf der DB waren alle mit '3' überschrieben. Bestände wurden vom Mainframe abgezogen , mittels Unix-Share überspielt und mit dem Skript 
#in die Informix KSC-artikellokal eingespielt.
#only input we need file abe40.csv with pzn and bestand from mainframe team
dbaccess ode21 << end
-- step 1: Sicherheitsbackup der zu modifizierenden Daten
-- unload to artikellokal.csv delimiter ';' select * from artikellokal where filialnr = 40;

-- step 2: crate temp table und laden der Daten in die temp table
  create temp table tmp_article (pzn integer, bestand integer);
  create index tmp_idx on tmp_article(pzn); 
  load from abe40.csv delimiter ';' insert into tmp_article;
  
-- step 3a) Update der Zieltabelle mit den Daten aus der temp table (ACHTUNG: unperformant!!!)
-- update artikellokal l set bestand = (select bestand from tmp_article t where l.artikel_nr=t.pzn ) where filialnr = 40 and
-- l.artikel_nr= (select pzn from tmp_article t where l.artikel_nr=t.pzn );
  
-- step 3b) Update der Zieltabelle mit den Daten aus der temp table (viel besser als 3a!)
  MERGE INTO artikellokal AS l USING tmp_article AS t ON l.filialnr = 40 AND l.artikel_nr = t.pzn
  WHEN MATCHED THEN
  UPDATE SET l.bestand = t.bestand;
end
