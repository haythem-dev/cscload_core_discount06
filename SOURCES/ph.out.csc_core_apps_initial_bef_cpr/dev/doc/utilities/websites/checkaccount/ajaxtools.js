var SaleswebBG = null; var SaleswebBGFinished = false; var SalesWebBGResult = null;
var SaleswebHR = null; var SaleswebHRFinished = false; var SalesWebHRResult = null;
var SaleswebFR = null; var SaleswebFRFinished = false; var SalesWebFRResult = null;
var SaleswebRS = null; var SaleswebRSFinished = false; var SalesWebRSResult = null;

var SwimpDE    = null; var SwimpDEFinished    = false; var SwimpDEResult    = null;
var SwimpAT    = null; var SwimpATFinished    = false; var SwimpATResult    = null;
var SwimpCH    = null; var SwimpCHFinished    = false; var SwimpCHResult    = null;

function initAjaxObjects() // init ajax objects
{    		
	SalesWebBG = null; SalesWebBGFinished = false;
	SalesWebHR = null; SalesWebHRFinished = false;
	SalesWebFR = null; SalesWebFRFinished = false;	
	SalesWebRS = null; SalesWebRSFinished = false;
	
	SwimpDE    = null; SwimpDEFinished    = false;	
    SwimpAT    = null; SwimpATFinished    = false;	
    SwimpCH    = null; SwimpCHFinished    = false;	
}

function sendAjaxRequests(url) // open ajax objects
{
	var urlorg = url;		
	url = urlorg + "&SalesWeb=BG"; SalesWebBG.open( "GET", url, true );
	url = urlorg + "&SalesWeb=HR"; SalesWebHR.open( "GET", url, true );
	url = urlorg + "&SalesWeb=FR"; SalesWebFR.open( "GET", url, true );	
	url = urlorg + "&SalesWeb=RS"; SalesWebRS.open( "GET", url, true );	
    
	url = urlorg + "&Swimp=DE";    SwimpDE.open( "GET", url, true );
    url = urlorg + "&Swimp=AT";    SwimpAT.open( "GET", url, true );
    url = urlorg + "&Swimp=CH";    SwimpCH.open( "GET", url, true );
    
    SwimpAT.onreadystatechange    = updateSeite; SwimpAT.send( null );			
    SwimpCH.onreadystatechange    = updateSeite; SwimpCH.send( null );			            
	SwimpDE.onreadystatechange    = updateSeite; SwimpDE.send( null );			    
		
	SalesWebBG.onreadystatechange = updateSeite; SalesWebBG.send( null );	
	SalesWebHR.onreadystatechange = updateSeite; SalesWebHR.send( null );	
	SalesWebFR.onreadystatechange = updateSeite; SalesWebFR.send( null );		
	SalesWebRS.onreadystatechange = updateSeite; SalesWebRS.send( null );					
}

function createAjaxRequestObjects() // instantiate ajax objects
{		
	try
	{ 		
        SalesWebBG = new XMLHttpRequest(); 
        SalesWebHR = new XMLHttpRequest(); 
		SalesWebFR = new XMLHttpRequest();         
        SalesWebRS = new XMLHttpRequest(); 		
        
        SwimpDE    = new XMLHttpRequest(); 		
        SwimpAT    = new XMLHttpRequest(); 		
        SwimpCH    = new XMLHttpRequest(); 		
	}
	catch( tryMicrosoft ) 
	{
		try
		{ 			
            SalesWebBG = new ActiveXObject( "Msxml2.XMLHTTP" ); 
            SalesWebHR = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			SalesWebFR = new ActiveXObject( "Msxml2.XMLHTTP" );             
            SalesWebRS = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			
            SwimpDE    = new ActiveXObject( "Msxml2.XMLHTTP" ); 			
            SwimpAT    = new ActiveXObject( "Msxml2.XMLHTTP" ); 			
            SwimpCH    = new ActiveXObject( "Msxml2.XMLHTTP" ); 			
		}
		catch( tryMicrosoft2 )
		{			
			try
			{ 				
                SalesWebBG = new ActiveXObject( "Microsoft.XMLHTTP" ); 
                SalesWebHR = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				SalesWebFR = new ActiveXObject( "Microsoft.XMLHTTP" );                 
                SalesWebRS = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				
                SwimpDE    = new ActiveXObject( "Microsoft.XMLHTTP" ); 				
                SwimpAT    = new ActiveXObject( "Microsoft.XMLHTTP" ); 				
                SwimpCH    = new ActiveXObject( "Microsoft.XMLHTTP" ); 				
			}
			catch( error )
			{ 				
                SalesWebBG = null; 
                SalesWebHR = null; 
                SalesWebFR = null;                 
                SalesWebRS = null; 
                
				SwimpDE    = null; 				
                SwimpAT    = null; 				
                SwimpCH    = null;
			}
		}		
	}		
}

function replaceText( el, text )
{	
	if( el != null )
	{
		el.innerHTML = text;		
	}
}

function clearText( el )
{
	if( el != null )
	{
		if( el.childNodes )
		{
			for( var i = 0; i < el.childNodes.length; i++ )
			{
				var childNode = el.childNodes[i];
				el.removeChild(childNode);
			}
		}
	}
}

function checkAccount()
{			
	document.getElementById("usercheck").disabled = true;
	
	SalesWebBGResult = document.getElementById( "SalesWebResultBG" ); replaceText( SalesWebBGResult, "" );		
	SalesWebHRResult = document.getElementById( "SalesWebResultHR" ); replaceText( SalesWebHRResult, "" );		
	SalesWebFRResult = document.getElementById( "SalesWebResultFR" ); replaceText( SalesWebFRResult, "" );			
	SalesWebRSResult = document.getElementById( "SalesWebResultRS" ); replaceText( SalesWebRSResult, "" );		
	
	SwimpDEResult    = document.getElementById( "SWIMPResultDE" );    replaceText( SwimpDEResult, "" );								
    SwimpATResult    = document.getElementById( "SWIMPResultAT" );    replaceText( SwimpATResult, "" );								
    SwimpCHResult    = document.getElementById( "SWIMPResultCH" );    replaceText( SwimpCHResult, "" );								
    
	var username     = document.getElementById("username").value;			
	var userpassword = document.getElementById("password").value;								
	initAjaxObjects();		
	createAjaxRequestObjects(); 		
	var url = "checkaccount.php?username=" + username + "&userpassword=" + userpassword;				
	sendAjaxRequests( url );		
}

function updateSeite()
{	
	if( 4 == SalesWebBG.readyState && SaleswebBGFinished == false )
	{
		SaleswebBGFinished = true;				
		replaceText( SalesWebBGResult, SalesWebBG.responseText );		    
	}		
	if( 4 == SalesWebHR.readyState && SaleswebHRFinished == false )
	{
		SaleswebHRFinished = true;				
		replaceText( SalesWebHRResult, SalesWebHR.responseText );		    
	}			
	if( 4 == SalesWebFR.readyState && SaleswebFRFinished == false )
	{
		SaleswebFRFinished = true;				
		replaceText( SalesWebFRResult, SalesWebFR.responseText );		    
	}				
	if( 4 == SalesWebRS.readyState && SaleswebRSFinished == false )
	{
		SaleswebRSFinished = true;				
		replaceText( SalesWebRSResult, SalesWebRS.responseText );		    
	}	
	
	if( 4 == SwimpDE.readyState && SwimpDEFinished == false )
	{
		SwimpDEFinished = true;				
		replaceText( SwimpDEResult, SwimpDE.responseText );		    
	}			
	if( 4 == SwimpAT.readyState && SwimpATFinished == false )
	{
		SwimpATFinished = true;				
		replaceText( SwimpATResult, SwimpAT.responseText );		    
	}			    
	if( 4 == SwimpCH.readyState && SwimpCHFinished == false )
	{
		SwimpCHFinished = true;				
		replaceText( SwimpCHResult, SwimpCH.responseText );		    
	}			        
}

function outline(id)
{	
	if( document.getElementById(id).style.display == 'none' )
	{
		document.getElementById(id).style.display = 'block';
	}
	else
	{
		document.getElementById(id).style.display = 'none';
	}
}