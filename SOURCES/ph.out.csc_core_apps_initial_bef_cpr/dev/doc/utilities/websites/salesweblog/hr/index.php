<?php

@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

require_once( 'utilities.php' );
require_once( 'LogSettings.php' );
LogSettings::loadSettings( "settings.xml" );

$LogPeriod = getDates4LastDays( 7 );

?>
<html>

<head>
	<title>SalesWeb Log</title>
	<link rel="stylesheet" type="text/css" href="style.css"/>
	<script language="JavaScript" src="ajaxtools.js"></script>	
</head>

<body onload="changeDatabase();">	
	<h1>SalesWeb Log</h1>	
	<table>
		<tr>
			<td>
				<label for="logdbName">Database:</label>
				<select name="logdbName" id="logdbName" onchange="changeDatabase();">
					<?php
					foreach( LogSettings::$LogDatabases as $it )
					{							
						$selected = '';
						if( $_REQUEST['logdbName'] == $it['name'] ) $selected = ' selected ';						
						?><option <?= $selected ?> value="<?= $it['name'] ?>"><?= $it['name'] ?></option><?					
					}
					?>					
				</select>
			</td>
			<td>
				<label for="logdbType">Type:</label>
				<select name="logdbType" id="logdbType">
					<?php
					$selected = "";
					if( isset($_REQUEST['logdbType']) && $_REQUEST['logdbType'] == 'normal' )
					{
						$selected = " selected ";
					}					
					?>
					<option <?= $selected ?> value="normal">normal</option>
					<?php
					$selected = "";
					if( isset($_REQUEST['logdbType']) && $_REQUEST['logdbType'] == 'errors' )
					{
						$selected = " selected ";
					}					
					?>
					<option <?= $selected ?> value="errors">only fatal errors</option>					
				</select>				
			</td>
			<td>
				<label for="logDate">Date:</label>
				<select name="logDate" id="logDate">
					<?php
					foreach( $LogPeriod as $it )
					{
						$selected = '';
						if( $_REQUEST['logDate'] == $it ) $selected = ' selected ';
						?><option <?= $selected ?> value="<?= $it ?>"><?= formatDate($it) ?></option><?php
					}
					?>
				</select>
			</td>
			<td>
				<label for="TimeFrom">Time (HHMM):</label>
				<?php if( !isset( $_REQUEST['TimeFrom'] ) ) $_REQUEST['TimeFrom']	= '0000'; ?>
				<input type="text" maxlength="4" name="TimeFrom" id="TimeFrom" size="3" value="<?= $_REQUEST['TimeFrom'] ?>"/>
				<label for="TimeTo"> - </label>
				<?php if( !isset( $_REQUEST['TimeTo'] ) ) $_REQUEST['TimeTo']	= '2359'; ?>
				<input type="text" maxlength="4" name="TimeTo" id="TimeTo" size="3" value="<?= $_REQUEST['TimeTo'] ?>"/>				
			</td>							
			<td>
				<label for="serverName">Server:</label>
				<select name="serverName" id="serverName">
					<?php
					foreach( LogSettings::$Servers as $it )
					{							
						$selected = '';
						if( $_REQUEST['serverName'] == $it['name'] ) $selected = ' selected ';						
						?><option <?= $selected ?> value="<?= $it['name'] ?>"><?= $it['name'] ?></option><?					
					}
					?>					
				</select>				
			</td>
		</tr>
		<tr>
			<td>
				<label for="branchNo">Branches:</label>
				<select name="branchNo" id="branchNo">
					<?php
					foreach( LogSettings::$Branches as $it )
					{												
						$selected = '';
						if( $_REQUEST['branchNo'] == $it['no'] ) $selected = ' selected ';						
						?><option <?= $selected ?> value="<?= $it['no'] ?>"><?= $it['no'] . " " . $it['name'] ?></option><?					
					}
					?>									
				</select>
			</td>
			<td>
				<label for="customerNo">Customer No.:</label>
				<?php if( !isset( $_REQUEST['customerNo'] ) ) $_REQUEST['customerNo']	= ''; ?>
				<input type="text" maxlength="7" name="customerNo" id="customerNo" size="5" value="<?= $_REQUEST['customerNo'] ?>"/>
			</td>
		</tr>	
	</table>
		
	<span id="orderOptions" style="display: block;">		
		<table>
			<tr>
				<td>
					<?php if( !isset( $_REQUEST['orderNo'] ) ) $_REQUEST['orderNo']	= ''; ?>
					<label for="orderNo">Order No.:</label> 
					<input type="text" maxlength="7" name="orderNo" id="orderNo" size="5" value="<?= $_REQUEST['orderNo'] ?>" />						
				</td>
				<td>
					<?php if( !isset( $_REQUEST['reference'] ) ) $_REQUEST['reference']	= ''; ?>
					<label for="reference">Reference:</label> 
					<input type="text" maxlength="20" name="reference" id="reference" size="5" value="<?= $_REQUEST['reference'] ?>" />												
				</td>
			</tr>
		</table>		
	</span>		

	<span id="textOptions" style="display: block;">
		<table>
			<tr>			
				<td>
					<?php if( !isset( $_REQUEST['txtInRequest'] ) ) $_REQUEST['txtInRequest']	= ''; ?>
					<label for="txtInRequest">Text in Request:</label> 
					<input type="text" maxlength="20" name="txtInRequest" id="txtInRequest" size="5" value="<?= $_REQUEST['txtInRequest'] ?>" />																
				</td>			
				<td>
					<?php if( !isset( $_REQUEST['txtInResponse'] ) ) $_REQUEST['txtInResponse']	= ''; ?>
					<label for="txtInResponse">Text in Response:</label> 
					<input type="text" maxlength="20" name="txtInResponse" id="txtInResponse" size="5" value="<?= $_REQUEST['txtInResponse'] ?>" />																
				</td>
			</tr>
		</table>	
	</span>	
	
	<p>
		<input type="button" name="startSearch" id="startSearch" value="Search Log Entries" onclick="Search4LogEntries();"/>
	</p>	
	
	<table>
		<tr><td>Total number of entries found: <span id="numberOfResults">0</span></td></tr>
		<tr><td><span id="resultArea1"></span></td></tr>
		<tr><td><span id="resultArea2"></span></td></tr>
		<tr><td><span id="resultArea3"></span></td></tr>
		<tr><td><span id="resultArea4"></span></td></tr>
		<tr><td><span id="resultArea5"></span></td></tr>
		<tr><td><span id="resultArea6"></span></td></tr>
		<tr><td><span id="resultArea7"></span></td></tr>
		<tr><td><span id="resultArea8"></span></td></tr>
		<tr><td><span id="resultArea9"></span></td></tr>
	</table>	

</body>

</html>

					