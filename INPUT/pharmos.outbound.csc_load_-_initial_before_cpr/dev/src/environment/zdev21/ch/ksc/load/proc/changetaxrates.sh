. /software/etc/profile_prz

dbaccess och21 -<<%
begin work;

update taxrates set salestaxrate = 7.7 where taxlevel = 0;

commit work;
%

dbaccess och21pre -<<%
begin work;

update taxrates set salestaxrate = 7.7 where taxlevel = 0;

commit work;
%

