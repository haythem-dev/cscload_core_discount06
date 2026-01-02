. /software/etc/profile_prz

dbaccess ode21 -<<%
begin work;

--delete from kdverbund where filialnr = 27;			-- obsolete
--delete from kdverbundpos where filialnr = 27;			-- obsolete
delete from cststockreserved where branchno = 27;		-- wichtig
--update artikellokal set bestandreserviert = 0 where filialnr = 27 and bestandreserviert > 0; --obsolete
--delete from ibtrequest where ibtbranchno = 27;		-- tödlich, also weg damit

commit work;
%

