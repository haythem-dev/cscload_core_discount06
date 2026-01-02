<?

//getDataFromLogDB( "swlog_hr_order_20110429_.db", "SELECT id FROM tblSalesWebLog;", "http://10.100.121.201:81/SalesWebLogService/SalesWebLogService.php", "SALESWEB1" );

function getDataFromLogDB( $database, $query, $location, $server )
{

	$database           = $database;
	$strQuery           = $query;
	$LOC                = $location;
	$server             = $server;
	
	$USER               = 'salesweblog';
	$PASSWORT           = 'ST49fiUt';
	$URI                = 'urn:SalesWebLogServer';
	
	$SOAPCLIENTSETTINGS = array( "location" =>  "$LOC",
	                             "uri"      =>  "$URI",
	                             "style"    =>  SOAP_RPC,
	                             "use"      =>  SOAP_ENCODED,
	                             "login"    =>  "$USER",
	                             "password" =>  "$PASSWORT" );    
	                                                      
	$parDatabase        = new SoapParam( $database, 'strDB' );
	$parQuery           = new SoapParam( $strQuery, 'strQuery' );
	$parServer          = new SoapParam( $server, 'strServer' );
	
	$SoapParameters     = array( $parServer,
	                             $parQuery,
	                             $parDatabase );
	
	$SoapSettings       = array( "uri"          =>  "$URI",
	                             "soapaction"   =>  "$URI#getQueryResultDB",
	                             "login"        =>  "$USER",
	                             "password"     =>  "$PASSWORT" );
	
	$objSoapClient      = new SoapClient( NULL, $SOAPCLIENTSETTINGS );
	
	
	$arrResult = array();
	try
	{
	    $arrResult = $objSoapClient->__call( 'getQueryResultDB',
	                                         $SoapParameters,
	                                         $SoapSettings );
	    if( is_soap_fault( $arrResult ) )
	    {
	        print "SOAP FAULT! <br/>";
	        print "faultcode: ".$arrResult->faultcode."<br/>";
	        print "faultstring: ".$arrResult->faultstring."<br/>";
	        return false;
	    }	    
	}
	catch( SoapFault $fault )
	{
	    print "SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})";    
	}

	return $arrResult;
}
?>

