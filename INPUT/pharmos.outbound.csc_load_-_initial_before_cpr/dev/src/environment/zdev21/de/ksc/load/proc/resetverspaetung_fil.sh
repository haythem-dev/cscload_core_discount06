dbaccess ode21 -<<%
update paraauftragbearb
set tourverspaetung = 0
where filialnr = ${1};
%
