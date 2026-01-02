<?php
@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

require_once( 'getDataFromLog.php' );
require_once( 'utilities.php' );
require_once( 'LogSettings.php' );
LogSettings::loadSettings( "settings.xml" );

// date
	$LogDate = date("Ymd");
	$LogDate = $_REQUEST['logDate'];
	
// time
	if( !isset( $_REQUEST['timefrom'] ) ) $_REQUEST['timefrom'] = '0000';
	$TimeFrom = $_REQUEST['timefrom'] * 100;
	if( !isset( $_REQUEST['timeto'] ) ) $_REQUEST['timeto'] = '2359';
	$TimeTo = $_REQUEST['timeto'] * 100;	

// get log db names
	$logDBName_dbname = "";
	$logDBName_dbnameerrors = "";
	foreach( LogSettings::$LogDatabases as $it )
	{
		if( $it['name'] == $_REQUEST['logdbName'] )
		{
			$logDBName_name   = $it['name'];
			$logDBName_dbname = $it['dbname'];
			$logDBName_dbnameerrors = $it['dbnameerrors'];			
		}
	}	
	if( $_REQUEST['logdbType'] == 'normal' )
	{
		$logDBName_dbname = str_replace( "#DATE#", $LogDate, $logDBName_dbname );
	}
	else 
	{
		$logDBName_dbname = str_replace( "#DATE#", $LogDate, $logDBName_dbnameerrors );
	}	

// get server 
	$serverName = "";
	$serverLocation = "";
	foreach( LogSettings::$Servers as $it )
	{
		if( ( substr( $_REQUEST['serverName'], 8, 1 ) == $_REQUEST['No'] ) || ( substr( $_REQUEST['serverName'], 0, 3 ) == 'All' ) )
		{
			if( substr( $it['name'], 8, 1) == $_REQUEST['No'] )	
			{
				$serverName = $it['name'];
				$serverLocation = $it['location'];		
			}		
		}
		if( $it['name'] == 'SalesTest' && $_REQUEST['No'] == 9 )
		{
			if( substr( $_REQUEST['serverName'], 0, 3 ) != 'All' )
			{
				$serverName = $it['name'];
				$serverLocation = $it['location'];					
			}
		}		
	}		
	if( strlen($serverName) == 0 ) exit();
	
//getTimestamp
	$timestamp = $_REQUEST['Timestamp'];
	
// get branchno 
	$branchNo = $_REQUEST['branchNo'];
	
// get customerno
	$customerNo = $_REQUEST['customerNo'];
	
// get orderNo 
	if( !isset($_REQUEST['orderNo']) ) $_REQUEST['orderNo'] = "";
	$orderNo = $_REQUEST['orderNo'];	
	
// get reference
	if( !isset( $_REQUEST['reference'] ) ) $_REQUEST['reference'] = "";
	$reference = $_REQUEST['reference'];
	
// get text in request
	if( !isset( $_REQUEST['xmlreq'] ) ) $_REQUEST['xmlreq'] = "";
	$xmlreq = $_REQUEST['xmlreq'];
	
// get text in response
	if( !isset( $_REQUEST['xmlres'] ) ) $_REQUEST['xmlres'] = "";
	$xmlres = $_REQUEST['xmlres'];		

// build query
	$query = "SELECT id AS id ";
	$query = $query . ", branch AS branchno ";
	$query = $query . ", customer AS customerno ";
	if( $logDBName_name == "Order" ) $query = $query . ", referenceNumber AS reference ";	
	if( $logDBName_name == "Order" ) $query = $query . ", orderEntryNumber AS orderno  ";
	$query = $query . ", logtime AS logtime ";
	$query = $query . "FROM tblSalesWebLog ";
	$query = $query . "WHERE 1=1 ";
	if( strlen(trim($branchNo)) > 0 ) 	$query = $query . " AND branch='$branchNo' ";
	if( strlen(trim($customerNo)) > 0 ) $query = $query . " AND ( customer='$customerNo' OR user LIKE '%$customerNo%') ";
	if( strlen(trim($orderNo)) > 0 ) 	$query = $query . " AND orderno='$orderNo' ";
	if( strlen(trim($reference)) > 0 ) 	$query = $query . " AND referenceNumber LIKE '%$reference%' ";
	if( strlen(trim($xmlreq)) > 0 ) 	$query = $query . " AND request LIKE '%$xmlreq%' ";
	if( strlen(trim($xmlres)) > 0 ) 	$query = $query . " AND ( responseFromWebService LIKE '%$xmlres%' OR responseToCustomer LIKE '%$xmlres%' ) ";
	$query = $query . "AND (logtime>=$TimeFrom AND logtime<=$TimeTo) ";	
	$query = $query . "ORDER BY logtime, customer ";
	$query = $query . ";";
	
// query data	
	$result = getDataFromLogDB( $logDBName_dbname, $query, $serverLocation, strtoupper($serverName) );
	
	$countWriteRows = 0;
	if($logDBName_name == "Order") 					{ $countWriteRows = putFileOrder( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation, $logDBName_name, $timestamp); }
	if($logDBName_name == "ProductAvailability") { $countWriteRows = putFileProductAvailability( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation, $logDBName_name, $timestamp); }
	
	print "<hr /><b>Write ".$countWriteRows." entries </b>";
	
	function putFileOrder( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation, $logDBName_name, $timestamp)
	{	
		$countWriteRows = 0;
		$CSVdatei=fopen($logDBName_name."-".$LogDate.".csv","a");
		
		if( sizeof($result) > 0 && $CSVdatei )
		{		
			foreach( $result as $it )
			{
				$query = " SELECT orderEntryNumber AS orderno
				, logtime AS logtime
				, request AS request
				FROM tblSalesWebLog
				WHERE id=".$it['id'].";";

				$resultEntries = getDataFromLogDB( $logDBName_dbname, $query, $serverLocation, strtoupper($serverName) );
				if( sizeof($result) > 0 && $CSVdatei )
				{		
					foreach( $resultEntries as $itEntries )
					{
						if( sizeof($resultEntries) > 0 && $CSVdatei )
						{
							$row = formatTime($itEntries['logtime']).";".substr_count($itEntries['request'], '</OrderItem>').";".$itEntries['orderno'].";"."ExecTime"."; \r\n";
							$countWriteRows++;
						}
					}
				}
				
				fputs($CSVdatei,$row);
			}
		}	
		else
		{
			print "Error can´t open the file or no entries from mysql server";
		}
		fclose($CSVdatei);
		return $countWriteRows;
	}

	function putFileProductAvailability( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation, $logDBName_name, $timestamp)
	{	
		$countWriteRows = 0;
		$CSVdatei=fopen($logDBName_name."-".$LogDate.".csv","a");
		$text="";
		
		if( sizeof($result) > 0 && $CSVdatei )
		{		
			foreach( $result as $it )
			{
				$query = " SELECT orderEntryNumber AS orderno
				, logtime AS logtime
				, request AS request
				FROM tblSalesWebLog
				WHERE id=".$it['id'].";";

				$resultEntries = getDataFromLogDB( $logDBName_dbname, $query, $serverLocation, strtoupper($serverName) );
			/*	if( sizeof($resultEntries) > 0 && $CSVdatei )
				{		
					foreach( $resultEntries as $itEntries )
					{
						$row = formatTime($itEntries['logtime']).";".substr_count($itEntries['request'], '<article articleNumber=').";".$itEntries['orderno'].";"."ExecTime"."; \r\n";
						
						$text=$text.$row;
					}
				}
				else
				{
					alert("1");
				}*/
				$countWriteRows++;
				
			}
		}	
		else
		{
			print "Error can´t open the file or no entries from mysql server";
		}
		fputs($CSVdatei,$text);
		fclose($CSVdatei);
		return $countWriteRows;
	}


	
?>