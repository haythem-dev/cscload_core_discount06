<?php

function getServerDE()
{
	$arrServer = array(); $y = 0;			
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest';	
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb';					
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenix-ag.de/';  $arrServer[$y]['srv'] = 'SalesWeb';					
	if( strtolower($_SERVER["AUTH_USER"]) == "phoenix\\steffen.heinlein" )
	{
		$y++; $arrServer[$y]['url'] = 'http://denu1vc0029.phoenix.loc/'; $arrServer[$y]['srv'] = 'VM Heinlein';		
	}
	return $arrServer;
}

function getServerBG()
{
	$arrServer = array(); $y = 0;			
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest';	
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb';					
	if( strtolower($_SERVER["AUTH_USER"]) == "phoenix\\steffen.heinlein" )
	{
		//$y++; $arrServer[$y]['url'] = 'http://denu1vc0029.phoenix.loc/'; $arrServer[$y]['srv'] = 'VM Heinlein';		
	}
	return $arrServer;
}

function getServerAT()
{
	$arrServer = array(); $y = 0;			
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest';	
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb';					
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenix-ag.de/';  $arrServer[$y]['srv'] = 'SalesWeb';	
	if( strtolower($_SERVER["AUTH_USER"]) == "phoenix\\steffen.heinlein" )
	{
	//	$y++; $arrServer[$y]['url'] = 'http://denu1vc0029.phoenix.loc/'; $arrServer[$y]['srv'] = 'VM Heinlein';		
	}
	return $arrServer;
}

function getServerCH()
{
	$arrServer = array(); $y = 0;			
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest';	
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	//$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb';					
	if( strtolower($_SERVER["AUTH_USER"]) == "phoenix\\steffen.heinlein" )
	{
		$y++; $arrServer[$y]['url'] = 'http://denu1vc0029.phoenix.loc/'; $arrServer[$y]['srv'] = 'VM Heinlein';		
	}
	return $arrServer;
}

function getSalesWebLinks( $interface, $country )
{	
	$arrServer = array(); $y = 0;			
	$y++; $arrServer[$y]['url'] = 'https://salestest.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest';	
	$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenixgroup.eu/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salestesttemp.phoenix-ag.de/'; $arrServer[$y]['srv'] = 'SalesTest ITRE';	
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb';		
	$y++; $arrServer[$y]['url'] = 'http://salesweb.phoenixgroup.eu/';  $arrServer[$y]['srv'] = 'SalesWeb HTTP';		
	$y++; $arrServer[$y]['url'] = 'https://salesweb.phoenix-ag.de/';  $arrServer[$y]['srv'] = 'SalesWeb';		
	$y++; $arrServer[$y]['url'] = 'http://10.100.121.201:81/'; $arrServer[$y]['srv'] = 'SalesWeb1';			
    $arrResult = array();
        
    /////////////////////////////////////////////////////////
    // Bulgaria
    /////////////////////////////////////////////////////////    
    if( 'BG' == $country )
    {   
		$arrServer = getServerBG();
		
    	$arrInterfaces = array(); $y = 0;    	
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/articlelist.php';   	   $arrInterfaces[$y]['srv'] = 'articlelist';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/changedquantities.php';   $arrInterfaces[$y]['srv'] = 'changedquantities';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/creditlimit.php';         $arrInterfaces[$y]['srv'] = 'creditlimit';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/discountaccount.php';     $arrInterfaces[$y]['srv'] = 'discountaccount';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/expirydates.php';         $arrInterfaces[$y]['srv'] = 'expirydates';    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/invoices.php';            $arrInterfaces[$y]['srv'] = 'invoices';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/order.php';               $arrInterfaces[$y]['srv'] = 'order';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/ordertransformer.php';    $arrInterfaces[$y]['srv'] = 'order';		
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/orderstatus.php';         $arrInterfaces[$y]['srv'] = 'orderstatus';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/paymentconditions.php';   $arrInterfaces[$y]['srv'] = 'paymentconditions';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/payments.php';   		   $arrInterfaces[$y]['srv'] = 'payments';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/pricesanddiscounts.php';  $arrInterfaces[$y]['srv'] = 'pricesanddiscounts';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/pricesanddiscounts2.php';  $arrInterfaces[$y]['srv'] = 'pricesanddiscounts2';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/productavailability.php'; $arrInterfaces[$y]['srv'] = 'productavailability';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/promotions.php';          $arrInterfaces[$y]['srv'] = 'promotions';
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceBulgariaFrontend/pr.aspx';  	   $arrInterfaces[$y]['srv'] = 'promotions';    	    					    	    	    							
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/routes.php';              $arrInterfaces[$y]['srv'] = 'routes';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/substitutes.php';         $arrInterfaces[$y]['srv'] = 'substitutes';
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlbulgaria/turnover.php';            $arrInterfaces[$y]['srv'] = 'turnover';
    	
    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;       		    	 	    	  	    	   	      	   
    }

    /////////////////////////////////////////////////////////
    // Schweiz
    /////////////////////////////////////////////////////////
    if( 'CH' == $country )
    {
		$arrServer = getServerCH();
		
    	$arrInterfaces = array(); $y = 0;    	
		
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/cucos.php?branch=12';               $arrInterfaces[$y]['srv'] = 'cucos';    			
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/cucos.php?branch=13';               $arrInterfaces[$y]['srv'] = 'cucos';    	
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/cucos2.php?branch=12';              $arrInterfaces[$y]['srv'] = 'cucos';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/cucos2.php?branch=13';              $arrInterfaces[$y]['srv'] = 'cucos';    	    	    	    	
		$y++; $arrInterfaces[$y]['url'] = 'amedis/customerconditions12'; 		           $arrInterfaces[$y]['srv'] = 'cucos';    	    	    	    			
		$y++; $arrInterfaces[$y]['url'] = 'amedis/customerconditions13'; 		           $arrInterfaces[$y]['srv'] = 'cucos';    	    	    	    					
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/cc.aspx?branch=12';  	   $arrInterfaces[$y]['srv'] = 'cucos';    	    					    	    	    							
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/cc.aspx?branch=13';  	   $arrInterfaces[$y]['srv'] = 'cucos';    	    					    	    	    							
		
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/deliverynote.php?branch=12';        $arrInterfaces[$y]['srv'] = 'deliverynote';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/deliverynote.php?branch=13';        $arrInterfaces[$y]['srv'] = 'deliverynote';    	
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/deliverynote2.php?branch=12';       $arrInterfaces[$y]['srv'] = 'deliverynote';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/deliverynote2.php?branch=13';       $arrInterfaces[$y]['srv'] = 'deliverynote';    	    	    	
		$y++; $arrInterfaces[$y]['url'] = 'amedis/deliverynotes12';        				   $arrInterfaces[$y]['srv'] = 'deliverynote';    			
		$y++; $arrInterfaces[$y]['url'] = 'amedis/deliverynotes13';        				   $arrInterfaces[$y]['srv'] = 'deliverynote';    					
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/dn.aspx?branch=12'; $arrInterfaces[$y]['srv'] = 'deliverynote';    	    					    	    	    							
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/dn.aspx?branch=13'; $arrInterfaces[$y]['srv'] = 'deliverynote';    	    					    	    	    							
		
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order_prod.php?branch=12';          $arrInterfaces[$y]['srv'] = 'order';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order_prod.php?branch=13';          $arrInterfaces[$y]['srv'] = 'order';    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order_prod2.php?branch=12';         $arrInterfaces[$y]['srv'] = 'order';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order_prod2.php?branch=13';         $arrInterfaces[$y]['srv'] = 'order';    	    			
    	$y++; $arrInterfaces[$y]['url'] = 'amedis/orders12'; 					           $arrInterfaces[$y]['srv'] = 'order';    			
		$y++; $arrInterfaces[$y]['url'] = 'amedis/orders13'; 					           $arrInterfaces[$y]['srv'] = 'order';    					
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/or.aspx?branch=12'; $arrInterfaces[$y]['srv'] = 'order';    	    					    	    	    							
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceSwitzerlandFrontend/or.aspx?branch=13'; $arrInterfaces[$y]['srv'] = 'order';    	    					    	    	    							
    	
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order.php?branch=12';               $arrInterfaces[$y]['srv'] = 'order';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order.php?branch=13';               $arrInterfaces[$y]['srv'] = 'order';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order2.php?branch=12';              $arrInterfaces[$y]['srv'] = 'order';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/order2.php?branch=13';              $arrInterfaces[$y]['srv'] = 'order';    	    					
		
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/productavailability.php?branch=12'; $arrInterfaces[$y]['srv'] = 'productavailability';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/productavailability.php?branch=13'; $arrInterfaces[$y]['srv'] = 'productavailability';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/productavailability2.php?branch=12'; $arrInterfaces[$y]['srv'] = 'productavailability';    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlamedis/productavailability2.php?branch=13'; $arrInterfaces[$y]['srv'] = 'productavailability';    			
		$y++; $arrInterfaces[$y]['url'] = 'amedis/productavailability12';                  $arrInterfaces[$y]['srv'] = 'productavailability';    			
		$y++; $arrInterfaces[$y]['url'] = 'amedis/productavailability13';                  $arrInterfaces[$y]['srv'] = 'productavailability';    			
    	
    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;      	                        
    }


    /////////////////////////////////////////////////////////
    // Österreich
    /////////////////////////////////////////////////////////
    if( 'AT' == $country )
    {   
		$arrServer = getServerAT();			
    	$arrInterfaces = array(); $y = 0;    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlaustria/argeinfo.php';  $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlaustria/argeinfo2.php';  $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceAustriaFrontend/pa.aspx';  $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					    	    	    					
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlaustria/argeorder.php'; $arrInterfaces[$y]['srv'] = 'order';    	    		    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlaustria/argeorder2.php'; $arrInterfaces[$y]['srv'] = 'order';    	    		    			
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceAustriaFrontend/or.aspx';  $arrInterfaces[$y]['srv'] = 'order';    	    					    	    	    							
		$y++; $arrInterfaces[$y]['url'] = 'epharmgh/argeiteminforequest'; $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					
		$y++; $arrInterfaces[$y]['url'] = 'epharmgh/argeorderrequest';  $arrInterfaces[$y]['srv'] = 'order';    	    					

    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;     	 	
    }       

    /////////////////////////////////////////////////////////
    // Kroatien
    /////////////////////////////////////////////////////////
    if( 'HR' == $country )
    {
    	$arrInterfaces = array(); $y = 0;    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlcroatia/articlecatalogue.php'; $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlcroatia/invoice.php';          $arrInterfaces[$y]['srv'] = 'invoice';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlcroatia/invoice2.php';          $arrInterfaces[$y]['srv'] = 'invoice';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlcroatia/order_prod.php';       $arrInterfaces[$y]['srv'] = 'order';    	    			
    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;     	 	    	                                    
    }

    /////////////////////////////////////////////////////////
    // Frankreich
    /////////////////////////////////////////////////////////
    if( 'FR' == $country )
    {
    	$arrInterfaces = array(); $y = 0;    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlfrance/articlecatalogue.php';                           $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    			    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlfrance/deliverynotes.php';                              $arrInterfaces[$y]['srv'] = 'deliverynotes';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlfrance/order.php';                                      $arrInterfaces[$y]['srv'] = 'order';    	    					
    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;     	    	               
    }

    /////////////////////////////////////////////////////////
    // Deutschland
    /////////////////////////////////////////////////////////
    if( 'DE' == $country )
    {
		$arrServer = getServerDE();		
    	$arrInterfaces = array(); $y = 0;    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlgermany/articlecatalogue.php';                            $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					    	
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceGermanyFrontend/pa.aspx';                            $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					    	    	    			
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlgermany/invoice.php';                                     $arrInterfaces[$y]['srv'] = 'invoice';    	    					
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceGermanyFrontend/dn.aspx';                            $arrInterfaces[$y]['srv'] = 'invoice';    	    					    	    	    			
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlgermany/order.php';                                       $arrInterfaces[$y]['srv'] = 'order';    
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceGermanyFrontend/or.aspx';                            $arrInterfaces[$y]['srv'] = 'order';    	    					    	    	    					
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlgermany/stocklevel.php';                                  $arrInterfaces[$y]['srv'] = 'stocklevel';    	    											
		$y++; $arrInterfaces[$y]['url'] = 'WebServiceGermanyFrontend/sl.aspx';                            $arrInterfaces[$y]['srv'] = 'stocklevel';    	    					    	    	    							

    	$i = 0; 
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        		
		   	    			     	
    	return $arrResult;      	            
    }
    
    /////////////////////////////////////////////////////////
    // Serbien
    /////////////////////////////////////////////////////////
    if( 'RS' == $country )
    {
    	$arrInterfaces = array(); $y = 0;    	    	
    	$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/articlecatalogue.php';  $arrInterfaces[$y]['srv'] = 'articlecatalogue';    	    					
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/creditlimit.php'; 	   $arrInterfaces[$y]['srv'] = 'creditlimit';    	    			    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/deliverylist.php'; 	   $arrInterfaces[$y]['srv'] = 'deliverylist';    	    			    	
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/order.php';             $arrInterfaces[$y]['srv'] = 'order';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/orderinfo.php';         $arrInterfaces[$y]['srv'] = 'orderinfo';    	    			
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/pharmacies.php';		   $arrInterfaces[$y]['srv'] = 'pharmacies';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/prices.php';		       $arrInterfaces[$y]['srv'] = 'prices';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/products.php';		   $arrInterfaces[$y]['srv'] = 'products';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/stocklevel.php';		   $arrInterfaces[$y]['srv'] = 'stocklevel';
		$y++; $arrInterfaces[$y]['url'] = 'wsxmlserbia/tender.php';            $arrInterfaces[$y]['srv'] = 'tenderinfo'; 
    	$i = 0;
    	foreach( $arrInterfaces as $b )
    	{
    		if( $b['srv'] == $interface )
    		{   	    		
	    		foreach( $arrServer as $a )
	    		{
		        	$i++;
		        	$arrResult[$i]['link']   = $a['url'].$b['url'];
		        	$arrResult[$i]['server'] = $a['srv'].' ('.$arrResult[$i]['link'].')';
		        	$arrResult[$i]['user']   = 'xmluploader';    	    			
	    		}    		 	    			        		        
    		}
    	}     	        	    	    		       	
    	return $arrResult;     	 	    	                                    
    }    
}

?>
