#!/bin/bash


_tourassig=$1;
_branchno=$2;


function checkParameter()
{
	 
	 if [ -z "$_tourassig" ]; 
	 then 
		echo "USAGE: To Activate = 1 , DeActivate = 0 "
		echo "EG: fixebindung.sh 0 5"
		exit 99
	 fi
	 
	 if [ -z "$_branchno" ]; 
	 then 
		echo "USAGE: Enter Filialnr"
		exit 99
	 fi
}

function updateFixeBindung()
{
dbaccess ode21 -<<%
begin work;
update paraauftragbearb set orderperiodtourassignment = ${_tourassig} where filialnr = ${_branchno};
commit work;
%
}

checkParameter
updateFixeBindung