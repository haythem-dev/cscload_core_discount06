<?php

function formatDate( $d )
{
	return substr($d, 0, 4)."-".substr($d, 4, 2)."-".substr($d, 6, 2);
}

function formatTime( $t )
{
	return substr($t, 0, 2).":".substr($t, 2, 2).":".substr($t, 4, 2);	
}

function getDates4LastDays($days)
{
	$retval = array();
	for( $i = 0; $i < $days; ++$i )
	{
		$retval[$i] = getDateTodayMinusXDays( $i );
	}
	return $retval;
}

function getDateTodayMinusXDays( $x )
{
	$dat = mktime(0, 0, 0, date("m"), date ("d")-$x, date("Y") );
	$dat = strftime("%Y%m%d" , $dat);
	return $dat;		
}

function print_rpre($obj)
{
	print "<pre>";
	print_r( $obj );
	print "</pre>";
}

?>