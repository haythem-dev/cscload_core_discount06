<?php
require_once("../default_header.php");
@ini_set( "error_log", date("Ymd")."index.log" );
require_once( '../inc.cscprocesses.php' );

$objCSCProcesses = new CSCProcesses( 'CSCProcesses.xml' );
$objCSCProcesses->loadXML();



?>
<html>
	<head>
		<title>CSC Batches Version Overview</title>
		<link rel="stylesheet" type="text/css" href="style.css"/>
		<script language="JavaScript" src="ajaxtools.js"></script>	
		<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
		<META HTTP-EQUIV="Expires" CONTENT="-1">
		<?php
		?>
	</head>
	<body>						
		<table width="100%">			
			<tr><td><a name="at" /><h2>Austria</h2> <span id="ATResult" >Requesting information for AT!</span></td></tr>						
			<tr><td><a name="bg" /><h2>Bulgaria</h2> <span id="BGResult" >Requesting information for BG!</span></td></tr>			
			<tr><td><a name="ch" /><h2>Switzerland</h2> <span id="CHResult" >Requesting information for CH!</span></td></tr>			
			<tr><td><a name="de" /><h2>Germany</h2> <span id="DEResult" >Requesting information for DE!</span></td></tr>			
			<tr><td><a name="fr" /><h2>France</h2> <span id="FRResult" >Requesting information for FR!</span></td></tr>					
			<tr><td><a name="hr" /><h2>Croatia</h2> <span id="HRResult" >Requesting information for HR!</span></td></tr>			
			<tr><td><a name="rs" /><h2>Serbia</h2> <span id="RSResult" >Requesting information for RS!</span></td></tr>									
		</table>		
		
		<script language="JavaScript">
			<?php
			$currentcountry = null;			
			while( false != ($currentcountry = $objCSCProcesses->getCountryFromList()) )
			{
				?> 				
				getInformation( '<?php print $currentcountry->getName(); ?>' ); 				
				<?php
			}			
			?>
		</script>
		
	</body>
</html>

			