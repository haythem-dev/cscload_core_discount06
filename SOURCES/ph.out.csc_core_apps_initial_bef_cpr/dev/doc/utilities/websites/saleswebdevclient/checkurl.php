<?php
require_once( "httpPostSimulation.php" );
require_once( "showFormElements.php" );
?>
<html>
<head>
	<title>URL Check</title>
</head>
<body>
	<h1>URL Check</h1>
	<form method="POST" action="<?=$_SERVER['PHP_SELF']?>">
	<table>
		<tr>
			<td><b>Link:</b></td>
			<td><? showInputText( $_REQUEST, 'url', false, 15 ); ?></td>
		</tr>
		<tr>
			<td><b>Username:</b></td>
			<td><? showInputText( $_REQUEST, 'user', false, 15 ); ?></td>
		</tr>
		<tr>
			<td><b>Passwort:</b></td>
			<td><? showInputText( $_REQUEST, 'password', true, 15 ); ?></td>
		</tr>
		<tr>
			<td><b>Anzahl Requests:</b></td>
			<td><? showInputText( $_REQUEST, 'requests', false, 15 ); ?></td>
		</tr>
		<tr>
			<td colspan="2"><? showSubmit( 'submit', 'Request Link' ); ?></td>
		</tr>
	</table>
	</form>
	<?php
	if( isset( $_REQUEST['submit'] ) )
	{	    
	    $strUsername       = $_REQUEST['FRM_Username'];
	    $strLink           = $_REQUEST['FRM_Link'];
	    $strPassword       = $_REQUEST['FRM_Passwort'];
	    $strNumberRequests = $_REQUEST['FRM_NumberOfRequests'];

	    $start_time = date("d.m.Y H:i:s");
	    $arrResult  = httpPostSimulation::multiplePostData( $_REQUEST['requests'], $_REQUEST['url'], $_REQUEST['user'], $_REQUEST['password'], "" );
	    $end_time   = date("d.m.Y H:i:s");

	    showResults( $arrResult, $_REQUEST['url'], $start_time, $end_time );
	}
	?>
</body>
</html>
<?php


?>