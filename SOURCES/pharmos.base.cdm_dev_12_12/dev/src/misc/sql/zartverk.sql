// --> doppelte Prioritäten:
select artikel_nr_bas, prioritaet, count(prioritaet) from zartverk group by 1, 2 order by 3 desc

--update zartverk set prioritaet = 2 where artikel_nr_bas = 1181392 and ARTIKEL_NR_VERK = 8818740

// --> Prioritäten nicht fortlaufend:
select * from zartverk v where prioritaet - 1 not in (select prioritaet from zartverk z where v.artikel_nr_bas = z.artikel_nr_bas ) and prioritaet > 1


