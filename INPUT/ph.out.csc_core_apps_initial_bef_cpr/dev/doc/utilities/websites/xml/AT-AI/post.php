<?

class httpPostSimulation
{

	static function postData( $strLink, $strUser, $strPasswort, $strXML, $iTimeout = 200 )
	{
		$objCurl = curl_init();
		curl_setopt( $objCurl, CURLOPT_USERPWD, "$strUser:$strPasswort" );
		curl_setopt( $objCurl, CURLOPT_URL, $strLink );
		curl_setopt( $objCurl, CURLOPT_SSL_VERIFYPEER, 0 );
		curl_setopt( $objCurl, CURLOPT_RETURNTRANSFER, 1 );
		curl_setopt( $objCurl, CURLOPT_HEADER, 0 );
		curl_setopt( $objCurl, CURLOPT_POST, 1 );
		curl_setopt( $objCurl, CURLOPT_POSTFIELDS, $strXML );
		curl_setopt( $objCurl, CURLOPT_TIMEOUT, (int)$iTimeout );
		
		curl_setopt( $objCurl, CURLOPT_HTTPHEADER, array('Content-Type: text/xml'));
		
		$strResponse = curl_exec( $objCurl );
    	curl_close( $objCurl );
		return $strResponse;
	}
}

?>
