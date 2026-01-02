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

$serverName = $_REQUEST['serverName'];
$logDBName = $_REQUEST['logDBName'];
$logID = $_REQUEST['logID'];
$serverLocation = $_REQUEST['serverLocation'];

$query = "
SELECT id AS id
, branch AS branchno
, user AS user
, customer AS customerno
, referenceNumber AS reference
, orderEntryNumber AS orderno
, logdate AS logdate
, logtime AS logtime
, request AS request
, responseFromWebService AS internalresponse
, responseToCustomer AS response
, statusConfirm AS confirmation
, errorMessage AS errortext
FROM tblSalesWebLog
WHERE id=$logID;
";

// query data	
$result = getDataFromLogDB( $logDBName, $query, $serverLocation, strtoupper($serverName) );

?>
<html>

<head>
	<title>SalesWeb Log</title>
	<link rel="stylesheet" type="text/css" href="style.css"/>
	<script language="JavaScript" src="ajaxtools.js"></script>	
</head>

<body>	
	<h1>SalesWeb Log Details</h1>		
	<?php
	foreach( $result as $it )
	{
		?>
		<table>
			<tr>
				<th>Log ID:</th>
				<th>Branch No.:</th>
				<th>User:</th>
				<th>Customer No.:</th>
			</tr>						
			<tr>
				<td align="center"><?= $it['id'] ?></td>				
				<td align="center"><?= $it['branchno'] ?></td>				
				<td align="center"><?= $it['user'] ?></td>				
				<td align="center"><?= $it['customerno'] ?></td>
			</tr>
		</table>
		<table>
			<tr>
				<th>Timestamp:</th>
				<th>Order No.:</th>				
				<th>Reference:</th>				
				<th>Messages:</th>
				<th>Confirmation:</th>
			</tr>
			<tr>
				<td><?= formatDate( $it['logdate'] ) . '&nbsp; &nbsp;' . formatTime( $it['logtime'] ) ?></td>
				<td><?= $it['orderno'] ?></td>
				<td><?= $it['reference'] ?></td>				
				<td><?= $it['errortext'] ?></td>
				<td><?= $it['confirmation'] ?></td>
			</tr>
		</table>					
		<table width="100%">
			<tr>
				<th valign="top" align="left" width="100%"><a href="#" onclick="outline('show_request')">Request:</a></th>
			</tr>			
			<tr>
				<td>
					<span id="show_request" style="display: none">				
						<pre><?= (htmlspecialchars( str_replace( ">", ">\r\n", $it['request'] ) )) ?></pre>
					</span>
				</td>
			</tr>			
			<tr>
				<th valign="top" align="left" width="100%"><a href="#" onclick="outline('show_response1')">Response to customer:</a></th>
			</tr>
			<tr>
				<td>
					<span id="show_response1" style="display: none">			
						<pre><?= (htmlspecialchars( str_replace( ">", ">\r\n", $it['response'] ) )) ?></pre>
					</span>
				</td>
			</tr>	
			<tr>
				<th valign="top" align="left" width="100%"><a href="#" onclick="outline('show_response2')">Internal response:</a></th>
			</tr>
			<tr>
				<td>
					<span id="show_response2" style="display: none">		
						<pre><?= htmlspecialchars( str_replace( ">", ">\r\n", $it['internalresponse'] ) ) ?></pre>
					</span>
				</td>
					
			</tr>					
		</table>
		<?		
	}
	?>
	
</body>

</html>