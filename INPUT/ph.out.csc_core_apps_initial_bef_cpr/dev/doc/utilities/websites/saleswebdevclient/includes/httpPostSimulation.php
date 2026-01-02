<?

class httpPostSimulation
{
	//----------------------------------------------------------------------------------------------------------------
	//
	// static function post
	//
	//----------------------------------------------------------------------------------------------------------------
	static function post( $strLink, $strUser, $strPasswort, $iTimeout = 700 ) //, $Proxy = 'proxy:8080' )
	{
		$objCurl = curl_init();
		/*if( strlen(trim($Proxy)) > 0 )
		{
			curl_setopt( $objCurl, CURLOPT_PROXY, $Proxy); 
		}*/
		curl_setopt( $objCurl, CURLOPT_USERPWD, "$strUser:$strPasswort" );
		curl_setopt( $objCurl, CURLOPT_URL, $strLink );
		curl_setopt( $objCurl, CURLOPT_SSL_VERIFYPEER, 0 );
		curl_setopt( $objCurl, CURLOPT_RETURNTRANSFER, 1 );
		curl_setopt( $objCurl, CURLOPT_HEADER, 0 );
		curl_setopt( $objCurl, CURLOPT_POST, 1 );
		curl_setopt( $objCurl, CURLOPT_TIMEOUT, (int)$iTimeout );
		$strResponse = curl_exec( $objCurl );
		curl_close ( $objCurl );
		return $strResponse;
	}

	//----------------------------------------------------------------------------------------------------------------
	//
	// static function postData
	//
	//----------------------------------------------------------------------------------------------------------------
	static function postData( $strLink, $strUser, $strPasswort, $strXML, $iTimeout = 200 ) //, $Proxy = 'proxy:8080' )
	{
		$objCurl = curl_init();
		/*if( strlen(trim($Proxy)) > 0 )
		{
			curl_setopt( $objCurl, CURLOPT_PROXY, $Proxy); 
		}*/
		curl_setopt( $objCurl, CURLOPT_USERPWD, "$strUser:$strPasswort" );
		curl_setopt( $objCurl, CURLOPT_URL, $strLink );
		curl_setopt( $objCurl, CURLOPT_SSL_VERIFYPEER, 0 );
		curl_setopt( $objCurl, CURLOPT_RETURNTRANSFER, 1 );
		curl_setopt( $objCurl, CURLOPT_HEADER, 0 );
		curl_setopt( $objCurl, CURLOPT_POST, 1 );
		curl_setopt( $objCurl, CURLOPT_POSTFIELDS, $strXML );
		curl_setopt( $objCurl, CURLOPT_TIMEOUT, (int)$iTimeout );		

		$strResponse = curl_exec( $objCurl );

    	curl_close( $objCurl );

		return $strResponse;
	}
	
	//----------------------------------------------------------------------------------------------------------------
	//
	// static function multiplePostDataREF
	//
	//----------------------------------------------------------------------------------------------------------------
	static function multiplePostDataREF( $count, $link, $user, $password, $data, $referenz, $timeout = 200, $usepost = true ) //, $Proxy = 'proxy:8080' )
	{
		if( 0 == (int)$count ) return false;				

		// create and init $count curl objects
		$arrCurl = array();
		for( $i = 0; $i < $count; ++$i )
		{
			//$xdata = str_replace( $referenz, $referenz.uniqid(), $data );							
			$xdata = str_replace( "UNIQUEID", substr( uniqid(md5(rand()), true), 0, 9), $data );
					
			$arrCurl[$i] = curl_init();
			if( strlen( $user ) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_USERPWD, "$user:$password" );
			}
			
			/*
			if( strlen(trim($Proxy)) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_PROXY, $Proxy); 
			}			
			*/
			
			curl_setopt( $arrCurl[$i], CURLOPT_URL, $link );
			curl_setopt( $arrCurl[$i], CURLOPT_SSL_VERIFYPEER, 0 );
			curl_setopt( $arrCurl[$i], CURLOPT_RETURNTRANSFER, 1 );
			curl_setopt( $arrCurl[$i], CURLOPT_HEADER, 0 );
			if( $usepost === true )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_POST, 1 );
			}
			curl_setopt( $arrCurl[$i], CURLOPT_TIMEOUT, (int)$timeout );
			curl_setopt( $arrCurl[$i], CURLOPT_POSTFIELDS, $xdata );
		}

		// create multi curl object
		$objMultiCurl = curl_multi_init();

		// add curl objects from array to curl multi object
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_add_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// execute curl objects
		$running = 0;
		do
		{
			curl_multi_exec( $objMultiCurl, $running );
		} while( $running > 0 );

		// get content
		$arrResponses = array();
		for( $i = 0; $i < $count; ++$i )
		{
			$arrResponses[$i]['content']  = curl_multi_getcontent( $arrCurl[$i] );
			$arrResponses[$i]['duration'] = curl_getinfo( $arrCurl[$i], CURLINFO_TOTAL_TIME );
			$arrResponses[$i]['httpcode'] = curl_getinfo( $arrCurl[$i], CURLINFO_HTTP_CODE );
		}

		//close all handles
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_remove_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// close multi curl
		curl_multi_close( $objMultiCurl );

		return $arrResponses;
	}	

	//----------------------------------------------------------------------------------------------------------------
	//
	// static function multiplePostData
	//
	//----------------------------------------------------------------------------------------------------------------
	static function multiplePostData( $count, $link, $user, $password, $data, $timeout = 200, $usepost = true ) //, $Proxy = 'proxy:8080' )
	{
		if( 0 == (int)$count ) return false;

		// create and init $count curl objects
		$arrCurl = array();
		for( $i = 0; $i < $count; ++$i )
		{
			$arrCurl[$i] = curl_init();
			if( strlen( $user ) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_USERPWD, "$user:$password" );
			}
			curl_setopt( $arrCurl[$i], CURLOPT_URL, $link );			
			
			curl_setopt( $arrCurl[$i], CURLOPT_SSL_VERIFYPEER, 0 );
			
			
			curl_setopt( $arrCurl[$i], CURLOPT_SSL_VERIFYHOST, 0 ); 
			
			
			curl_setopt( $arrCurl[$i], CURLOPT_RETURNTRANSFER, 1 );
			curl_setopt( $arrCurl[$i], CURLOPT_HEADER, 0 );			
			if( $usepost === true )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_POST, 1 );
			}
			/*
			if( strlen(trim($Proxy)) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_PROXY, $Proxy); 
			}
			*/						
			curl_setopt( $arrCurl[$i], CURLOPT_TIMEOUT, (int)$timeout );
			curl_setopt( $arrCurl[$i], CURLOPT_POSTFIELDS, $data );
			curl_setopt( $arrCurl[$i], CURLOPT_HTTPHEADER, array("Content-Type: text/xml", "Content-length: ".strlen($data)));
		}

		// create multi curl object
		$objMultiCurl = curl_multi_init();

		// add curl objects from array to curl multi object
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_add_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// execute curl objects
		$running = 0;
		do
		{
			curl_multi_exec( $objMultiCurl, $running );
		} while( $running > 0 );

		// get content
		$arrResponses = array();
		for( $i = 0; $i < $count; ++$i )
		{
			$arrResponses[$i]['content']  = curl_multi_getcontent( $arrCurl[$i] );
			$arrResponses[$i]['duration'] = curl_getinfo( $arrCurl[$i], CURLINFO_TOTAL_TIME );
			$arrResponses[$i]['httpcode'] = curl_getinfo( $arrCurl[$i], CURLINFO_HTTP_CODE );
		}

		//close all handles
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_remove_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// close multi curl
		curl_multi_close( $objMultiCurl );

		return $arrResponses;
	}

	//----------------------------------------------------------------------------------------------------------------
	//
	// static function multiplePost
	//
	//----------------------------------------------------------------------------------------------------------------
	static function multiplePost( $count, $link, $user, $password, $timeout = 200, $usepost = true ) //, $Proxy = 'proxy:8080' )
	{
		if( 0 == (int)$count ) return false;

		// create and init $count curl objects
		$arrCurl = array();
		for( $i = 0; $i < $count; ++$i )
		{
			$arrCurl[$i] = curl_init();
			if( strlen( $user ) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_USERPWD, "$user:$password" );
			}
			curl_setopt( $arrCurl[$i], CURLOPT_URL, $link );
			curl_setopt( $arrCurl[$i], CURLOPT_SSL_VERIFYPEER, 0 );
			curl_setopt( $arrCurl[$i], CURLOPT_RETURNTRANSFER, 1 );
			curl_setopt( $arrCurl[$i], CURLOPT_HEADER, 0 );
			if( $usepost === true )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_POST, 1 );
			}
			/*
			if( strlen(trim($Proxy)) > 0 )
			{
				curl_setopt( $arrCurl[$i], CURLOPT_PROXY, $Proxy); 
			}
			*/									
			curl_setopt( $arrCurl[$i], CURLOPT_TIMEOUT, (int)$timeout );
		}

		// create multi curl object
		$objMultiCurl = curl_multi_init();

		// add curl objects from array to curl multi object
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_add_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// execute curl objects
		$running = 0;
		do
		{
			curl_multi_exec( $objMultiCurl, $running );
		} while( $running > 0 );

		// get content
		$arrResponses = array();
		for( $i = 0; $i < $count; ++$i )
		{
			$arrResponses[$i]['content']  = curl_multi_getcontent( $arrCurl[$i] );
			$arrResponses[$i]['duration'] = curl_getinfo( $arrCurl[$i], CURLINFO_TOTAL_TIME );
			$arrResponses[$i]['httpcode'] = curl_getinfo( $arrCurl[$i], CURLINFO_HTTP_CODE );
		}

		//close all handles
		for( $i = 0; $i < $count; ++$i )
		{
			curl_multi_remove_handle( $objMultiCurl, $arrCurl[$i] );
		}

		// close multi curl
		curl_multi_close( $objMultiCurl );

		return $arrResponses;
	}
}

?>
