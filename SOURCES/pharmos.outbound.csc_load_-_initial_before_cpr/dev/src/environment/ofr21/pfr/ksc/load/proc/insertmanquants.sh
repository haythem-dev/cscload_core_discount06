dbaccess ofr21pre -<<%
begin work;
load from /transfer/ksc/data/49/manquants.txt
insert into manquants;
commit work;
%

