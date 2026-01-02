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
	if( $logDBName_name == "Orders" ) $query = $query . ", referenceNumber AS reference ";	
	if( $logDBName_name == "Orders" ) $query = $query . ", orderEntryNumber AS orderno  ";
	$query = $query . ", logtime AS logtime ";
	$query = $query . "FROM tblSalesWebLog ";
	$query = $query . "WHERE 1=1 ";
	if( strlen(trim($branchNo)) > 0 ) 	$query = $query . " AND branch='$branchNo' ";
	if( strlen(trim($customerNo)) > 0 ) $query = $query . " AND ( customer='$customerNo' OR user LIKE '%$customerNo%') ";
	if( strlen(trim($orderNo)) > 0 ) 	$query = $query . " AND orderno='$orderNo' ";
	if( strlen(trim($reference)) > 0 ) 	$query = $query . " AND referenceNumber LIKE '%$reference%' ";
	if( strlen(trim($xmlreq)) > 0 ) 	$query = $query . " AND request LIKE '%$xmlreq%' ";
	if( strlen(trim($xmlres)) > 0 ) 	$query = $query . " AND ( responseFromWebService LIKE '%$xmlres%' OR responseToCustomer LIKE '%$xmlres%' ) ";
	$query = $query . "ORDER BY logtime, customer ";
	$query = $query . ";";		
	
// query data	
	$result = getDataFromLogDB( $logDBName_dbname, $query, $serverLocation, strtoupper($serverName) );
	print "<hr /><b>Results for Log Server $serverName (".sizeof($result)." entries found)</b>";		
	
	$shown = false;	
	if( $logDBName_name == "CheckOrderBuffer" ) { showOrderResults( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation );	 $shown = true; }	
	if( $logDBName_name == "Orders" ) { showOrderResults( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation ); $shown = true; }
	if( $logDBName_name == "Order" ) { showOrderResults( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation ); $shown = true; }
	if( $shown == false ) { showArticleCatalogueResults( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation ); $shown = true; }
	
	function showArticleCatalogueResults( $result, $LogDate, $serverName, $logDBName_dbname, $serverLocation)
	{
		if( sizeof($result) > 0 )
		{
			?>
			<table>
				<thead>
					<th>Date</th>
					<th>Time</th>
					<th>BranchNo</th>
					<th>CustomerNo</th>					
					<th>Details</th>	
				</thead>
				<tbody>
					<?php
					foreach( $result as $it )
					{
						?>
						<tr>
							<td width="100px"><?= formatDate($LogDate) ?></td>
							<td width="100px"><?= formatTime($it['logtime']) ?></td>
							<td width="100px"><?= $it['branchno'] ?></td>
							<td width="150px"><?= $it['customerno'] ?></td>		
							<td align="center">	
								<a href="detail.php?serverName=<?=$serverName?>&serverLocation=<?=$serverLocation?>&logDBName=<?=$logDBName_dbname?>&logID=<?=$it['id']?>" target="about:blank">																											
									<img src="info.png" alt="show details"/>
								</a>
							</td>
						</tr>
						<?php
					}
					?>
				</tbody>
			</table>			
			<?php	
		}		
	}
	
	function showOrderResults($result, $LogDate, $serverName, $logDBName_dbname, $serverLocation)
	{	
		//$logDBName_dbname = str_replace( "_.db", "", $logDBName_dbname );
		if( sizeof($result) > 0 )
		{
			?>
			<table>
				<thead>
					<th>Date</th>
					<th>Time</th>
					<th>BranchNo</th>
					<th>CustomerNo</th>
					<th>OrderNo</th>
					<th>Reference</th>		
					<th>Details</th>	
				</thead>
				<tbody>
					<?php
					foreach( $result as $it )
					{
						?>
						<tr>
							<td width="100px"><?= formatDate($LogDate) ?></td>
							<td width="100px"><?= formatTime($it['logtime']) ?></td>
							<td width="100px"><?= $it['branchno'] ?></td>
							<td width="150px"><?= $it['customerno'] ?></td>
							<td width="100px"><?= $it['orderno'] ?></td>
							<td width="200px"><?= $it['reference'] ?></td>
							<td align="center">																
								<a href="detail.php?serverName=<?=$serverName?>&serverLocation=<?=$serverLocation?>&logDBName=<?=$logDBName_dbname?>&logID=<?=$it['id']?>" target="about:blank">				
									<img src="info.png" alt="show details"/>
								</a>
							</td>
						</tr>
						<?php
					}
					?>
				</tbody>
			</table>
			<?php	
		}
	}
?>