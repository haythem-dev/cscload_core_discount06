<?php

@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

$Country = "";
$Swimp = false;
$SalesWeb = false;

$file = "checkaccount.log";
$username = $_REQUEST['username'];
$userpassword = $_REQUEST['userpassword'];

if( isset( $_REQUEST['Swimp'] ) )
{
    file_put_contents($file, "Username:[".$_REQUEST['username']."] Password:[".$_REQUEST['userpassword']."] Swimp:[".$_REQUEST['Swimp']."]\r\n", FILE_APPEND);    
	$Swimp = true;
	$Country = $_REQUEST['Swimp'];
    if( $Country == 'BG' ) exit("SalesWeb not for Bulgaria!");
    if( $Country == 'FR' ) exit("SalesWeb not for France!");
    if( $Country == 'HR' ) exit("SalesWeb not for Croatia!");    
    if( $Country == 'RS' ) exit("SalesWeb not for Serbia!");        
}

if( isset( $_REQUEST['SalesWeb']  ) )
{
    file_put_contents($file, "Username:[".$_REQUEST['username']."] Password:[".$_REQUEST['userpassword']."] SalesWeb:[".$_REQUEST['SalesWeb']."]\r\n", FILE_APPEND);    
	$SalesWeb = true;
	$Country = $_REQUEST['SalesWeb'];
    if( $Country == 'AT' ) exit("SalesWeb not for Austria!");
    if( $Country == 'DE' ) exit("SalesWeb not for Germany!");
    if( $Country == 'CH' ) exit("SalesWeb not for Switzerland!");            
}



$SalesWebURLs = array();
$SalesWebURLs['BG'] = "/wsxmlbulgaria/routes.php";
$SalesWebURLs['HR'] = "/wsxmlcroatia/invoice.php";
$SalesWebURLs['FR'] = "/wsxmlfrance/articlecatalogue.php";
$SalesWebURLs['RS'] = "/wsxmlserbia/orderinfo.php";

$SwimpURLs = array();
$SwimpURLs['DE']    = "/wsxmlgermany/articlecatalogue.php";
$SwimpURLs['AT']    = "/epharmgh/argeiteminforequest";
$SwimpURLs['CH']    = "/amedis/productavailability12";

$URL2Check = "";

if( $SalesWeb == true )
{	
    $URL2Check = $SalesWebURLs[$Country];	    
    $SalesWebServer = array();
    for( $i = 1; $i < 9; ++$i )
    {
        $SalesWebServer[$i]['name'] = "SW$i";
        $SalesWebServer[$i]['url']  = "http://10.100.121.20$i:81";
    }
	foreach( $SalesWebServer as $it )
	{
		print $it['name']. ": ";
		$rc = check( $it['url'].$URL2Check, $username, $userpassword );
		if( (int)$rc == 200 )
		{
			print "<img src=\"available.png\" />";
		}
		else 
		{
			print "<img src=\"not-available.png\" />";
		}
		
		print "<br />";
		flush();
	}
}

if( $Swimp == true )
{
    $URL2Check = $SwimpURLs[$Country];
	$it = "https://salesweb.phoenixgroup.eu";
	$rc = check( $it.$URL2Check, $username, $userpassword );
	if( (int)$rc == 200 )
	{
		print "<img src=\"available.png\" />";
	}
	else 
	{
		print "<img src=\"not-available.png\" />";
	}
	print "<br />";
}

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