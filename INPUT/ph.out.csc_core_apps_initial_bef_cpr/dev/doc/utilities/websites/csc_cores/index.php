<?php
require_once( "../default_header.php" );
@ini_set( "error_log", date("Ymd")."ajaxworker.log" );
require_once( '../inc.sshutil.php' );

function listCoreFiles( $server )
{
	?>
	<h2>Cores on <?php print $server; ?></h2>	
	<?php
	$objSSHUtil = new SSHUtil();
	$connected = $objSSHUtil->connect( $server, "produser", "redR8-Wo3" );
	if( true != $connected ) die( "Connection to $server failed!" );
	$result = $objSSHUtil->execute( "ls -ltr /software/wss/usercore" );
	$lines = explode( "\n", $result );															
	if( count($lines) > 2 )
	{
		?><table width="100%" style="color: red; font-weight: bold;"><?php		
		foreach( $lines as $line )
		{		
			if( substr($line, 0, 5) != "total" )
			{
				?><tr><td><?php print $line; ?></td></tr><?php
			}
		}		
		?></table><?php
	}
}

?>

<html>
	<head>
		<title>Outbound COREs Overview</title>
		<link rel="stylesheet" type="text/css" href="style.css"/>		
		<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
		<META HTTP-EQUIV="Expires" CONTENT="-1">		
	</head>
	<body>		
		<h1>Outbound COREs Overview</h1>
		<?php
		listCoreFiles("oat21");
		listCoreFiles("obg21");
		listCoreFiles("och21");
		listCoreFiles("ode21");		
		listCoreFiles("ode23");
		listCoreFiles("ode24");
        listCoreFiles("ode25");
        listCoreFiles("ode26");
        listCoreFiles("ode27");
		listCoreFiles("ofr21");
		listCoreFiles("ohr21");
		listCoreFiles("ors21");
		?>
	</body>
</html>
