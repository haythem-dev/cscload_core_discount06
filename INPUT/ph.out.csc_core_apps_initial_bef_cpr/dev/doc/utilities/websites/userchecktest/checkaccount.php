<?php

@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

$username = $_REQUEST['username'];
$userpassword = $_REQUEST['userpassword'];

$URLs = array();
if( "de" == strtolower(substr( $username, 0, 2 )) || "msv3produploader" == $username || "msv3testuploader" == $username )
{
	if( 12 == strlen( $username ) || "msv3produploader" == $username || "msv3testuploader" == $username )
	{
		$URLs['DEPA']['DESC'] = "MSV3 VerfuegbarkeitsAnfrage";
		$URLs['DEPA']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/verfuegbarkeitAnfragen";		
		$URLs['DECT']['DESC'] = "MSV3 VerbindungsTest";
		$URLs['DECT']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/verbindungTesten";		
		$URLs['DERA']['DESC'] = "MSV3 RuecknahmeAngebot";
		$URLs['DERA']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/ruecknahmeangebotAnfordern";		
		$URLs['DEPB']['DESC'] = "MSV3 VerfuegbartkeitsAnfrage Bulk";
		$URLs['DEPB']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/verfuegbarkeitAnfragenBulk";
		$URLs['DEOR']['DESC'] = "MSV3 Bestellung";
		$URLs['DEOR']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/bestellen";		
		$URLs['DEOS']['DESC'] = "MSV3 Statusabfrage Bestellung";
		$URLs['DEOS']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/bestellstatusAbfragen";		
		$URLs['DECD']['DESC'] = "MSV3 Abfrage Vertragsdaten";		
		$URLs['DECD']['URL'] = "https://msv3test.phoenixgroup.eu/msv3test/v1.0/vertragsdatenabfragen";
	}
	else
	{
		$URLs['DEPA']['DESC'] = "XML ProductAvailability";
		$URLs['DEPA']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlgermany/articlecatalogue.php";
		$URLs['DEOR']['DESC'] = "XML Order";
		$URLs['DEOR']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlgermany/order.php";
		$URLs['DEDN']['DESC'] = "XML DeliveryNote";
		$URLs['DEDN']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlgermany/invoice.php";
		$URLs['DESL']['DESC'] = "XML StockLevel";
		$URLs['DESL']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlgermany/stocklevel.php";	
	}
}
else if( "ch" == strtolower( substr( $username, 0, 2 ) ) )
{	
	$URLs['CHPA']['DESC'] = "XML ProductAvailability";
	$URLs['CHPA']['URL']  = "https://salestest.phoenixgroup.eu/amedis/productavailability12";		
	$URLs['CHOR']['DESC'] = "XML Order";
	$URLs['CHOR']['URL']  = "https://salestest.phoenixgroup.eu/amedis/orders12";			
	$URLs['CHDN']['DESC'] = "XML DeliveryNote";
	$URLs['CHDN']['URL']  = "https://salestest.phoenixgroup.eu/amedis/deliverynotes12";			
	$URLs['CHCC']['DESC'] = "XML Customer Conditions";
	$URLs['CHCC']['URL']  = "https://salestest.phoenixgroup.eu/amedis/customerconditions12";
}
else if( "at" == strtolower( substr( $username, 0, 2 ) ) )
{
	$URLs['ATPA']['DESC'] = "XML ProductAvailability";
	$URLs['ATPA']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlaustria/argeinfo.php";
	$URLs['ATOR']['DESC'] = "XML Order";
	$URLs['ATOR']['URL']  = "https://salestest.phoenixgroup.eu/wsxmlaustria/argeorder.php";
}


print "<hr/>".date("d.m.Y H:i:s")."<hr/>";
print "<table>";
foreach( $URLs as $URL )
{
	$url = $URL['URL'];
	$desc = $URL['DESC'];
	$rc = check( $url, $username, $userpassword );
	print "<tr>";
	if( (int)$rc == 200 )
	{
		print "<td><img src='available.png'/></td><td>$desc</td><td>$url</td>";
	}
	else
	{
		print "<td><img src='not-available.png'/></td><td>$desc</td><td>$url</td>";
	}
	print "</tr>";
}
print "</table>";

?>

<?php
function check( $link, $user, $password )
{			
	$objCurl = curl_init();
	curl_setopt( $objCurl, CURLOPT_USERPWD, "$user:$password" );
	curl_setopt( $objCurl, CURLOPT_URL, $link );
	curl_setopt( $objCurl, CURLOPT_SSL_VERIFYPEER, 0 );
	curl_setopt( $objCurl, CURLOPT_RETURNTRANSFER, 1 );
	curl_setopt( $objCurl, CURLOPT_HEADER, 0 );	
	//curl_setopt( $objCurl, CURLOPT_POST, 1 );
	curl_setopt( $objCurl, CURLOPT_TIMEOUT, 200 );	
	
	curl_exec( $objCurl );
	
	$httpcode = curl_getinfo( $objCurl, CURLINFO_HTTP_CODE );
		
	curl_close( $objCurl );
	
	return $httpcode;
}
?>