<?php
@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	
@ini_set( "display_errors", 0 );
@ini_set( "display_startup_errors", 0 );
@ini_set( "error_reporting", E_ALL );
@ini_set( "log_errors", 1 );
@ini_set( "track_errors", 1 );
?>