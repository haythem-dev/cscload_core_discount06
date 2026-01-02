#!/usr/bin/ksh

function checkUser
{
	local readonly _BRANCHNO=${1};
	CURRENTUSER=$(id -u -n);		
	getBranchUser ${_BRANCHNO};
	
	print "Current User : ${CURRENTUSER}";
	print "Branch User  : ${BRANCHUSER}";
		
	if [ "${BRANCHUSER}" != "${CURRENTUSER}" ] ; then 
		echo "Bitte für Filiale ${_BRANCHNO} nur mit dem User ${BRANCHUSER} starten.";
		exit;
	fi;
}

function getBranchUser
{
	local readonly _BRANCHNO=${1};	
	BRANCHUSER="devuser";
	if [ "22" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;
	if [ "23" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;	
	if [ "24" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;
	if [ "25" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;
	if [ "26" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;
	if [ "28" == "${_BRANCHNO}" ] ; then BRANCHUSER="devuserbg"; fi;		
}

function getBranchDirectory
{
	local readonly _BRANCHNO=${1};	
	
	checkUser ${_BRANCHNO};
	
	# AT
	if [ "61" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/at/ksc/"; fi;
	if [ "62" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/at/ksc/"; fi;
	if [ "63" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/at/ksc/"; fi;
	if [ "64" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/at/ksc/"; fi;	
	if [ "83" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/pat/ksc/"; fi;
	
	# BG
	if [ "22" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	if [ "23" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	if [ "24" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	if [ "25" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	if [ "26" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	if [ "28" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/bg/ksc/"; fi;
	
	# CH
	if [ "12" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/ch/ksc/"; fi;
	if [ "13" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/ch/ksc/"; fi;
	if [ "16" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/pch/ksc/"; fi;
	
	# DE Süd	
	if [ "5" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "05" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "21" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "44" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "51" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "52" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "54" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "57" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "58" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "81" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	if [ "82" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de4/ksc/"; fi;
	
	# DE Nord
	if [ "6" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "8" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "9" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "06" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "08" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "09" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "33" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "40" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "31" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "46" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "56" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "59" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "70" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	if [ "78" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/de/ksc/"; fi;
	
	# FR
	if [ "17" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "18" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "30" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "32" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "34" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "35" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "36" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "37" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "38" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "39" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "41" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "43" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/pfr/ksc/"; fi;
	if [ "45" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "48" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/pfr/ksc/"; fi;
	if [ "50" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "53" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "55" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "60" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "66" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "68" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;
	if [ "75" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;	
	if [ "76" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;	
	if [ "80" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;	
	if [ "86" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;	
	if [ "87" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/fr/ksc/"; fi;	
	
	# HR
	if [ "71" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/hr/ksc/"; fi;
	if [ "72" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/hr/ksc/"; fi;
	if [ "73" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/hr/ksc/"; fi;
	if [ "74" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/hr/ksc/"; fi;
	if [ "77" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/hr/ksc/"; fi;
	
	# RS		
	if [ "3" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/rs/ksc/"; fi;
	if [ "03" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/rs/ksc/"; fi;
	if [ "84" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/rs/ksc/"; fi;
	if [ "85" == "${_BRANCHNO}" ] ; then KSCPATH="$WSS/rs/ksc/"; fi;
	
	return "";		
}