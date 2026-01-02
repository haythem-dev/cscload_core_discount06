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

$LogPeriod = getDates4LastDays( 7 );

$resultEntries = getDataFromLogDB( "swlog_bg_productavailability_20120716_.db", "SELECT * FROM tblSalesWebLog", "http://10.100.121.201:81/SalesWebLogService/SalesWebLogService.php", strtoupper("SalesWeb2") );
				
				echo sizeof($resultEntries);
				
					foreach( $resultEntries as $itEntries )
					{
					
						if( sizeof($resultEntries) > 0 )
						{
							echo formatTime($itEntries['logtime']).";".";".$itEntries['orderno'].";"."ExecTime"."; \r\n";
							$countWriteRows++;
						}
					}

?>