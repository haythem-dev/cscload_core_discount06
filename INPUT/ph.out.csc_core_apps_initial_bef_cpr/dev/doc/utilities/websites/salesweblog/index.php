<?php

@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

?>
<html>

<head>
	<title>SalesWeb Log</title>
	<link rel="stylesheet" type="text/css" href="style.css"/>
	<script language="JavaScript" src="ajaxtools.js"></script>	
</head>

<body>	
	<h1>SalesWeb Log</h1>	
	
	<ul>		
		<li><a href="./bg/index.php">Bulgaria</a></li>
		<li><a href="./hr/index.php">Croatia</a></li>
		<li><a href="./fr/index.php">France</a></li>		
		<li><a href="./rs/index.php">Serbia</a></li>				
	</ul>
	
	
</body>

</html>

					