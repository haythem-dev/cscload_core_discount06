#! /usr/bin/sh
# set -x

typeset -i BRANCHNO=$1

FROM_SERVER="zdev21"
TO_SERVER="zdev21"
KDDISPO_SERVER="zdev21"
UADM_SERVER="zdev21"

#FROM_SERVER="ode22"
#TO_SERVER="ode21"
#KDDISPO_SERVER="ide21"
#UADM_SERVER="ode21"

FROM_DB_INST="ode22"
TO_DB_INST="ode21"
KDDISPO_DB_INST="ide21"
UADM_DB_INST="zpcua1"

FROM_DBSERVER="${FROM_SERVER}_tcp"
TO_DBSERVER="${TO_SERVER}_tcp"
TO_DBSERVER_SHM="${TO_SERVER}_shm"


FROMDB="${FROM_DB_INST}@${FROM_DBSERVER}"
TODB="${TO_DB_INST}@${TO_DBSERVER}"
TODB_SHM="${TO_DB_INST}@${TO_DBSERVER_SHM}"
KDDISPO_DB="${KDDISPO_DB_INST}@${KDDISPO_SERVER}_tcp"
UADM_DB="${UADM_DB_INST}@${UADM_SERVER}_tcp"

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
function doSQL
{
	SQL="$1";

	echo $(date -u +"%T") "${SQL}" 2>&1;
	echo "${SQL}" | dbaccess ${FROMDB} 2>&1;
}

#---------------------------------------------------------------------------------------------
# main script starts here
#---------------------------------------------------------------------------------------------

doSQL "
delete from ${TODB}:anrufparameter                                                where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:anrufparameter                   				  where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:anrufparameter     select * from ${FROMDB}:anrufparameter     where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:anrufparameter                   				      where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:articlequota                                                  where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:articlequota                                       where branchno=${BRANCHNO};
insert into ${TODB}:articlequota       select * from ${FROMDB}:articlequota       where branchno=${BRANCHNO};
select count(*) from ${TODB}:articlequota                                         where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:articlereservation                                            where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:articlereservation                                 where branchno=${BRANCHNO};
insert into ${TODB}:articlereservation select * from ${FROMDB}:articlereservation where branchno=${BRANCHNO};
select count(*) from ${TODB}:articlereservation                                   where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:auftragartkomb                                                where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:auftragartkomb                                     where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:auftragartkomb     select * from ${FROMDB}:auftragartkomb     where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:auftragartkomb                                       where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:backrouting                                                   where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:backrouting                                        where branchno=${BRANCHNO};
insert into ${TODB}:backrouting        select * from ${FROMDB}:backrouting        where branchno=${BRANCHNO};
select count(*) from ${TODB}:backrouting                                          where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:buchungsart                                                   where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:buchungsart                                        where branchno=${BRANCHNO};
insert into ${TODB}:buchungsart        select * from ${FROMDB}:buchungsart        where branchno=${BRANCHNO};
select count(*) from ${TODB}:buchungsart                                          where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:branchinfo                                                    where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:branchinfo         								  where branchno=${BRANCHNO};
insert into ${TODB}:branchinfo         select * from ${FROMDB}:branchinfo         where branchno=${BRANCHNO};
select count(*) from ${TODB}:branchinfo         								  where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackattach                                                where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:callbackattach                                     where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:callbackattach     select * from ${FROMDB}:callbackattach     where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:callbackattach                                       where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackdivision                                              where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:callbackdivision                                   where branchno=${BRANCHNO};
insert into ${TODB}:callbackdivision   select * from ${FROMDB}:callbackdivision   where branchno=${BRANCHNO};
select count(*) from ${TODB}:callbackdivision                                     where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackitems                                                 where kritiknr in (select kritiknr from ${TODB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${FROMDB}:callbackitems                                      where kritiknr in (select kritiknr from ${FROMDB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
insert into ${TODB}:callbackitems      select * from ${FROMDB}:callbackitems      where kritiknr in (select kritiknr from ${FROMDB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${TODB}:callbackitems                                        where kritiknr in (select kritiknr from ${FROMDB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
"

doSQL "
delete from ${TODB}:callbackofftime                                               where callbackpartno in (select callbackpartno from ${TODB}:callbackpartner where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${FROMDB}:callbackofftime                                    where callbackpartno in (select callbackpartno from ${FROMDB}:callbackpartner where vertriebszentrumnr=${BRANCHNO});
insert into ${TODB}:callbackofftime    select * from ${FROMDB}:callbackofftime    where callbackpartno in (select callbackpartno from ${FROMDB}:callbackpartner where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${TODB}:callbackofftime                                      where callbackpartno in (select callbackpartno from ${TODB}:callbackpartner where vertriebszentrumnr=${BRANCHNO});
"

doSQL "
delete from ${TODB}:callbackpartner                                               where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:callbackpartner                                    where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:callbackpartner    select * from ${FROMDB}:callbackpartner    where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:callbackpartner                                      where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackreasons                                               where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:callbackreasons      							  where branchno=${BRANCHNO};
insert into ${TODB}:callbackreasons    select * from ${FROMDB}:callbackreasons    where branchno=${BRANCHNO};
select count(*) from ${TODB}:callbackreasons      							      where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:collordergrp                                                  where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:collordergrp       								  where branchno=${BRANCHNO};
insert into ${TODB}:collordergrp       select * from ${FROMDB}:collordergrp       where branchno=${BRANCHNO};
select count(*) from ${TODB}:collordergrp       								  where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:collordergrpmem                                               where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:collordergrpmem                                    where branchno=${BRANCHNO};
insert into ${TODB}:collordergrpmem    select * from ${FROMDB}:collordergrpmem    where branchno=${BRANCHNO};
select count(*) from ${TODB}:collordergrpmem                                      where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cremawebusersuggestion                                        where branchno=${BRANCHNO};
select count(*)	from ${FROMDB}:cremawebusersuggestion                             where branchno=${BRANCHNO};
insert into ${TODB}:cremawebusersuggestion (editorname, customerno, branchno, choice, choicereason, choicecomment, lastchanged)
	select editorname, customerno, branchno, choice, choicereason, choicecomment, lastchanged
	from ${FROMDB}:cremawebusersuggestion                                         where branchno=${BRANCHNO};
select count(*)	from ${TODB}:cremawebusersuggestion                               where branchno=${BRANCHNO};	
"

doSQL "
delete from ${TODB}:cscini                                                        where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:cscini                                             where branchno=${BRANCHNO};
insert into ${TODB}:cscini             select * from ${FROMDB}:cscini             where branchno=${BRANCHNO};
select count(*) from ${TODB}:cscini                                               where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cstseporderartgrp                                             where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:cstseporderartgrp                                  where branchno=${BRANCHNO};
insert into ${TODB}:cstseporderartgrp  select * from ${FROMDB}:cstseporderartgrp  where branchno=${BRANCHNO};
select count(*) from ${TODB}:cstseporderartgrp                                    where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cststockreserved                                              where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:cststockreserved                                   where branchno=${BRANCHNO} and reservtype=7;
insert into ${TODB}:cststockreserved   select * from ${FROMDB}:cststockreserved   where branchno=${BRANCHNO} and reservtype=7;
select count(*) from ${TODB}:cststockreserved                                     where branchno=${BRANCHNO} and reservtype=7;
"

doSQL "
delete from ${TODB}:customernomapping                                             where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:customernomapping                                  where branchno=${BRANCHNO};
insert into ${TODB}:customernomapping  select * from ${FROMDB}:customernomapping  where branchno=${BRANCHNO};
select count(*) from ${TODB}:customernomapping                                    where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:customerphoneno                                               where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:customerphoneno                                    where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:customerphoneno    select * from ${FROMDB}:customerphoneno    where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:customerphoneno                                      where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:delayeddeliverycst                                            where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:delayeddeliverycst                                 where branchno=${BRANCHNO};
insert into ${TODB}:delayeddeliverycst select * from ${FROMDB}:delayeddeliverycst where branchno=${BRANCHNO};
select count(*) from ${TODB}:delayeddeliverycst                                   where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynoteheader                                            where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:deliverynoteheader 								  where branchno=${BRANCHNO};
insert into ${TODB}:deliverynoteheader select * from ${FROMDB}:deliverynoteheader where branchno=${BRANCHNO};
select count(*) from ${TODB}:deliverynoteheader 								  where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynotefooter                                            where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:deliverynotefooter                                 where branchno=${BRANCHNO};
insert into ${TODB}:deliverynotefooter select * from ${FROMDB}:deliverynotefooter where branchno=${BRANCHNO};
select count(*) from ${TODB}:deliverynotefooter                                   where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynotepos                                               where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:deliverynotepos                                    where branchno=${BRANCHNO};
insert into ${TODB}:deliverynotepos    select * from ${FROMDB}:deliverynotepos    where branchno=${BRANCHNO};
select count(*) from ${TODB}:deliverynotepos                                      where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:distressrouting                                               where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:distressrouting                                    where branchno=${BRANCHNO};
insert into ${TODB}:distressrouting    select * from ${FROMDB}:distressrouting    where branchno=${BRANCHNO};
select count(*) from ${TODB}:distressrouting                                      where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:feiertag                                                      where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:feiertag                                           where filialnr=${BRANCHNO};
insert into ${TODB}:feiertag           select * from ${FROMDB}:feiertag           where filialnr=${BRANCHNO};
select count(*) from ${TODB}:feiertag                                             where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:filiale                                                       where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:filiale                                            where filialnr=${BRANCHNO};
insert into ${TODB}:filiale            select * from ${FROMDB}:filiale            where filialnr=${BRANCHNO};
select count(*) from ${TODB}:filiale                                              where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:ibtbranches                                                   where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:ibtbranches                                        where branchno=${BRANCHNO};
insert into ${TODB}:ibtbranches        select * from ${FROMDB}:ibtbranches        where branchno=${BRANCHNO};
select count(*) from ${TODB}:ibtbranches                                          where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdauftragart                                                  where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:kdauftragart                                       where branchno=${BRANCHNO};
insert into ${TODB}:kdauftragart       select * from ${FROMDB}:kdauftragart       where branchno=${BRANCHNO};
select count(*) from ${TODB}:kdauftragart                                         where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdauftragendezeit                                             where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:kdauftragendezeit                                  where filialnr=${BRANCHNO};
insert into ${TODB}:kdauftragendezeit  select * from ${FROMDB}:kdauftragendezeit  where filialnr=${BRANCHNO};
select count(*) from ${TODB}:kdauftragendezeit                                    where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdkritik                                                      where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:kdkritik                                           where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:kdkritik           select * from ${FROMDB}:kdkritik           where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:kdkritik                                             where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdkritikpos                                                   where kritiknr in (select kritiknr from ${TODB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${FROMDB}:kdkritikpos                                        where kritiknr in (select kritiknr from ${FROMDB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
insert into ${TODB}:kdkritikpos        select * from ${FROMDB}:kdkritikpos        where kritiknr in (select kritiknr from ${FROMDB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
select count(*) from ${TODB}:kdkritikpos                                          where kritiknr in (select kritiknr from ${TODB}:kdkritik where vertriebszentrumnr=${BRANCHNO});
"

doSQL "
delete from ${TODB}:kommiarten                                                    where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:kommiarten                                         where branchno=${BRANCHNO};
insert into ${TODB}:kommiarten         select * from ${FROMDB}:kommiarten         where branchno=${BRANCHNO};
select count(*) from ${TODB}:kommiarten                                           where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundemasterplan                                               where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:kundemasterplan                                    where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:kundemasterplan    select * from ${FROMDB}:kundemasterplan    where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:kundemasterplan                                      where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundemonums                                                   where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:kundemonums                                        where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:kundemonums    select * from ${FROMDB}:kundemonums            where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:kundemonums                                          where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundenotdienstplan                                            where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:kundenotdienstplan                                 where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:kundenotdienstplan select * from ${FROMDB}:kundenotdienstplan where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:kundenotdienstplan                                   where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
select count(*) from ${FROMDB}:kundeurlaub                                        where vertriebszentrumnr=${BRANCHNO};
delete from ${TODB}:kundeurlaub                                                   where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:kundeurlaub        select * from ${FROMDB}:kundeurlaub        where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:kundeurlaub                                          where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
select count(*) from ${FROMDB}:ladeanrufplan                                      where vertriebszentrumnr=${BRANCHNO};
delete from ${TODB}:ladeanrufplan                                                 where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:ladeanrufplan      select * from ${FROMDB}:ladeanrufplan      where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:ladeanrufplan                                        where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:mailusers                                                     where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:mailusers                                          where filialnr=${BRANCHNO};
insert into ${TODB}:mailusers          select * from ${FROMDB}:mailusers          where filialnr=${BRANCHNO};
select count(*) from ${TODB}:mailusers                                            where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:nachlieferpos                                                 where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:nachlieferpos                                      where vertriebszentrumnr=${BRANCHNO} and postyp in (2, 3, 5);
insert into ${TODB}:nachlieferpos (kdauftragnr,posnr,datum,postyp,idfnr,artikel_nr,menge,filialnr1,filialnr2,filialnr3,status,ursprungauftragnr,ursprungposnr,kundennr,vertriebszentrumnr,erfasst,kdauftragart,posart,preisekaponetto,batchauftragnr,batchposnr,mengenatra,bemerkungen,preisekapo,preisvkapo,preisagp,datumvaluta,koart,buchart,code_type,article_code,discountvaluepct,mengebestellt,preis_typ)
    select                 1000000+kdauftragnr,posnr,datum,postyp,idfnr,artikel_nr,menge,filialnr1,filialnr2,filialnr3,status,ursprungauftragnr,ursprungposnr,kundennr,vertriebszentrumnr,erfasst,kdauftragart,posart,preisekaponetto,batchauftragnr,batchposnr,mengenatra,bemerkungen,preisekapo,preisvkapo,preisagp,datumvaluta,koart,buchart,code_type,article_code,discountvaluepct,mengebestellt,preis_typ
	from ${FROMDB}:nachlieferpos                                                  where vertriebszentrumnr=${BRANCHNO} and postyp in (2, 3, 5);
select count(*) from ${TODB}:nachlieferpos                                        where vertriebszentrumnr=${BRANCHNO} and postyp in (2, 3, 5);
"


doSQL "
delete from ${TODB}:orderperiodtime where order_period_id in (select id from ${TODB}:orderperiod where branchno=${BRANCHNO});
delete from ${TODB}:orderperiod where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:orderperiod where branchno=${BRANCHNO};
insert into ${TODB}:orderperiod (customerno, tourid, branchno, weekday)
	select customerno, tourid, branchno, weekday from ${FROMDB}:orderperiod where branchno=${BRANCHNO};
select count(*) from ${TODB}:orderperiod where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:orderperiodtime opt join ${FROMDB}:orderperiod op on op.id=opt.order_period_id where op.branchno=${BRANCHNO};
insert into ${TODB}:orderperiodtime (fromtime, totime, maintime, order_period_id)
	select told.fromtime, told.totime, told.maintime, pnew.id
	from ${FROMDB}:orderperiodtime told 
		inner join ${FROMDB}:orderperiod pold on told.order_period_id=pold.id
		inner join ${TODB}:orderperiod pnew on pold.customerno=pnew.customerno and pold.tourid=pnew.tourid and pold.branchno=pnew.branchno and pold.weekday=pnew.weekday
	where pold.branchno=${BRANCHNO};
select count(*) from ${TODB}:orderperiodtime opt join ${TODB}:orderperiod op on op.id=opt.order_period_id where op.branchno=${BRANCHNO};
"


doSQL "
delete from ${TODB}:paraauftragbearb                                              where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:paraauftragbearb                                   where filialnr=${BRANCHNO};
insert into ${TODB}:paraauftragbearb   select * from ${FROMDB}:paraauftragbearb   where filialnr=${BRANCHNO};
select count(*) from ${TODB}:paraauftragbearb                                     where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:parameter                                                     where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:parameter                                          where filialnr=${BRANCHNO}; 
insert into ${TODB}:parameter          select * from ${FROMDB}:parameter          where filialnr=${BRANCHNO}; 
select count(*) from ${TODB}:parameter                                            where filialnr=${BRANCHNO}; 
"

doSQL "
delete from ${TODB}:passwd                                                        where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:passwd                                             where filialnr=${BRANCHNO};
insert into ${TODB}:passwd             select * from ${FROMDB}:passwd             where filialnr=${BRANCHNO};
select count(*) from ${TODB}:passwd                                               where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:pseudolagerorte                                               where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:pseudolagerorte                                    where filialnr=${BRANCHNO};
insert into ${TODB}:pseudolagerorte    select * from ${FROMDB}:pseudolagerorte    where filialnr=${BRANCHNO};
select count(*) from ${TODB}:pseudolagerorte                                      where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:regionarten                                                   where regionnr=${BRANCHNO} and regionteilnr=${BRANCHNO};
select count(*) from ${FROMDB}:regionarten                                        where regionnr=${BRANCHNO} and regionteilnr=${BRANCHNO};
insert into ${TODB}:regionarten        select * from ${FROMDB}:regionarten        where regionnr=${BRANCHNO} and regionteilnr=${BRANCHNO};
select count(*) from ${TODB}:regionarten                                          where regionnr=${BRANCHNO} and regionteilnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:salesman                                                      where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:salesman                                           where branchno=${BRANCHNO};
insert into ${TODB}:salesman           select * from ${FROMDB}:salesman           where branchno=${BRANCHNO};
select count(*) from ${TODB}:salesman                                             where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:shipauxno                                                     where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:shipauxno                                          where branchno=${BRANCHNO};
insert into ${TODB}:shipauxno          select * from ${FROMDB}:shipauxno          where branchno=${BRANCHNO};
select count(*) from ${TODB}:shipauxno                                            where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:seporderartgrp                                                where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:seporderartgrp                                     where branchno=${BRANCHNO};
insert into ${TODB}:seporderartgrp     select * from ${FROMDB}:seporderartgrp     where branchno=${BRANCHNO};
select count(*) from ${TODB}:seporderartgrp                                       where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:sondertouren                                                  where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:sondertouren                                       where filialnr=${BRANCHNO};
insert into ${TODB}:sondertouren       select * from ${FROMDB}:sondertouren       where filialnr=${BRANCHNO};
select count(*) from ${TODB}:sondertouren                                         where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:stockentry                                                    where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:stockentry                                         where branchno=${BRANCHNO};
insert into ${TODB}:stockentry         select * from ${FROMDB}:stockentry         where branchno=${BRANCHNO};
select count(*) from ${TODB}:stockentry                                           where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:werte                                                         where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${FROMDB}:werte                                              where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:werte              select * from ${FROMDB}:werte              where vertriebszentrumnr=${BRANCHNO};
select count(*) from ${TODB}:werte                                                where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:zeitarten                                                     where vertriebszentrumnr=${BRANCHNO};
select count(*)	from ${FROMDB}:zeitarten	                                      where vertriebszentrumnr=${BRANCHNO};
insert into ${TODB}:zeitarten (zeitart, zeitschluessel, tagestyp, zeitbegin, zeitende, zeitzusatz, kzupd, vertriebszentrumnr, weekday)  
	select zeitart, zeitschluessel, tagestyp, zeitbegin, zeitende, zeitzusatz, kzupd, vertriebszentrumnr, weekday
	from ${FROMDB}:zeitarten
	where vertriebszentrumnr=${BRANCHNO};
select count(*)	from ${TODB}:zeitarten	                                          where vertriebszentrumnr=${BRANCHNO};	
"

#-- narcotics
doSQL "
delete from ${TODB}:narcopenorders                                                where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:narcopenorders                                     where branchno=${BRANCHNO};
insert into ${TODB}:narcopenorders     select * from ${FROMDB}:narcopenorders     where branchno=${BRANCHNO};
select count(*) from ${TODB}:narcopenorders                                       where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:narcnumber                                                    where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:narcnumber                                         where filialnr=${BRANCHNO};
insert into ${TODB}:narcnumber         select * from ${FROMDB}:narcnumber         where filialnr=${BRANCHNO};
select count(*) from ${TODB}:narcnumber                                           where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:narctransactionoriginal                                       where branchno=${BRANCHNO};
select count(*)	from ${FROMDB}:narctransactionoriginal 	                          where branchno=${BRANCHNO};
insert into ${TODB}:narctransactionoriginal (branchno,articleno,transactiondate,transactiontime,customersupplierno,transactiontype,purchaseorderno,qtytransaction,qtyinstock,tourid)
	select branchno,articleno,transactiondate,transactiontime,customersupplierno,transactiontype,purchaseorderno,qtytransaction,qtyinstock,tourid
	from ${FROMDB}:narctransactionoriginal
	where branchno=${BRANCHNO};
select count(*)	from ${TODB}:narctransactionoriginal 	                          where branchno=${BRANCHNO};	
"

#--> Serial (id) ist wg debtmailsend schon DB-übergreifend eindeutig!
doSQL "
delete from ${TODB}:smtpusergroups                                                where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:smtpusergroups                                     where branchno=${BRANCHNO};
insert into ${TODB}:smtpusergroups (id, smtpid, debtlevelid, sentfromaddress, senttoaddress, url, branchno, crematypeid)
	select id, smtpid, debtlevelid, sentfromaddress, senttoaddress, url, branchno, crematypeid
	from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO};
select count(*) from ${TODB}:smtpusergroups                                       where branchno=${BRANCHNO};	
"

#--> Serial (id) auf ode21 wurde vorab um 100 erhöht, so dass die Übernahme von ode22 mit ID´s < 100 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO});
select count(*)	from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO});
insert into ${TODB}:smtpemailtype (id, emailtype, smtpusergroupid)
	select id, emailtype, smtpusergroupid
	from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO});
select count(*)	from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO});	
"

#--> Serial (id) auf ode21 wurde vorab um 100 erhöht, so dass die Übernahme von ode22 mit ID´s < 100 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpgvlmail where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));
select count(*)	from ${FROMDB}:smtpgvlmail where smtpemailtypeid in (select id from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO}));
insert into ${TODB}:smtpgvlmail (id, smtpemailtypeid, sendgvlmail)
	select id, smtpemailtypeid, sendgvlmail
	from ${FROMDB}:smtpgvlmail where smtpemailtypeid in (select id from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO}));
select count(*)	from ${TODB}:smtpgvlmail where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));	
"

#--> Serial (id) auf ode21 wurde vorab um 1000 erhöht, so dass die Übernahme von ode22 mit ID´s < 1000 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpsendtoemailaddresses where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));
select count(*) from ${FROMDB}:smtpsendtoemailaddresses where smtpemailtypeid in (select id from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO}));
insert into ${TODB}:smtpsendtoemailaddresses (id, senttoaddress, smtpemailtypeid)
	select id,  senttoaddress, smtpemailtypeid
	from ${FROMDB}:smtpsendtoemailaddresses where smtpemailtypeid in (select id from ${FROMDB}:smtpemailtype where smtpusergroupid in (select id from ${FROMDB}:smtpusergroups where branchno=${BRANCHNO}));
select count(*) from ${TODB}:smtpsendtoemailaddresses where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));	
"

# ABBA UW orderproposal ohne orderhead mit orderno = 0 umziehen.
doSQL "
delete from ${TODB}:orderproposal                                         where branchno = ${BRANCHNO} and ordernobatch not in (select orderno from ${TODB}:orderhead);
select count(*) from ${FROMDB}:orderproposal where branchno = ${BRANCHNO} and ordernobatch not in (select orderno from ${FROMDB}:orderhead);
insert into ${TODB}:orderproposal    select * from ${FROMDB}:orderproposal where branchno = ${BRANCHNO} and ordernobatch not in (select orderno from ${FROMDB}:orderhead);
select count(*) from ${TODB}:orderproposal where branchno = ${BRANCHNO} and ordernobatch not in (select orderno from ${TODB}:orderhead);
"

#infozbw auf Süd deaktivieren
doSQL "
delete from ${FROMDB}:zeitarten where zeitart=3 and vertriebszentrumnr=${BRANCHNO};
delete from ${FROMDB}:taskcontrol where vertriebszentrumnr=${BRANCHNO};
delete from ${FROMDB}:parameter where zweck='TASKCONTROL' and filialnr=${BRANCHNO};
"

#--rechner
doSQL "
update ${FROMDB}:rechner set rechner_name='${TO_SERVER}', datenbank_name='${TODB}' where filialnr=${BRANCHNO};
update ${TODB}:rechner set rechner_name='${TO_SERVER}', datenbank_name='${TODB_SHM}' where filialnr=${BRANCHNO};
"

# kundendispo
doSQL "
update ${KDDISPO_DB}:parameterkd set auspraeg='${TODB}'        where filialnr=${BRANCHNO} and programmname='KD2CLIENT' and zweck='STRINGS'      and parametername='LOGINTABLE';
update ${KDDISPO_DB}:parameterkd set auspraeg='${TO_SERVER}'   where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='AESERVER';
update ${KDDISPO_DB}:parameterkd set auspraeg='${TO_DB_INST}'  where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='DBAE';
update ${KDDISPO_DB}:parameterkd set auspraeg='${TO_DBSERVER}' where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='DBSERVER';
"

# UADM
# CSC (48) - csc_batches/abbauw
# IBTSPLITTING (91)
# IRM (43)
# NARCOTICS (28)
# ORDER_ENTRY (80) - ibtorderimport
doSQL "
update ${UADM_DB}:pplogpara set paravalue='DE1'                where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'CSC')          and para1='${BRANCHNO}' and parabez='GROUP';

update ${UADM_DB}:pplogpara set paravalue='${TO_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IBTSPLITTING') and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${TO_DBSERVER}'     where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IBTSPLITTING') and para1='${BRANCHNO}' and parabez='DBSRV';

update ${UADM_DB}:pplogpara set paravalue='${TO_SERVER}'       where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IRM')          and para1='${BRANCHNO}' and parabez='CSC_SRVNAME';

update ${UADM_DB}:pplogpara set paravalue='${TO_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'NARCOTICS')    and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${TO_DBSERVER}'     where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'NARCOTICS')    and para1='${BRANCHNO}' and parabez='HOST';

update ${UADM_DB}:pplogpara set paravalue='${TO_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'ORDER_ENTRY')  and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${TO_DBSERVER_SHM}' where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'ORDER_ENTRY')  and para1='${BRANCHNO}' and parabez='DBSRV';
"
