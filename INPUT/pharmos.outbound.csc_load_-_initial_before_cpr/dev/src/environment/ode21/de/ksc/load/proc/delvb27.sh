. /software/etc/profile_prz


CURR_DATE=`date +"%y.%m.%d"`;
TIME_STAMP=`date +"%d.%m.%y-%H:%M:%S"`;
LOG_FILE=$WSS/de/ksc/load/log/delvb27.$CURR_DATE.log

echo $TIME_STAMP Start >>$LOG_FILE

dbaccess ode21 -<<%
begin work;

delete from kdverbund where filialnr = 27;
delete from kdverbundpos where filialnr = 27;
delete from cststockreserved where branchno = 27;
update artikellokal set bestandreserviert = 0 where filialnr = 27 and bestandreserviert > 0;
delete from ibtrequest where ibtbranchno = 27;

commit work;
%

echo $TIME_STAMP Stop >>$LOG_FILE

