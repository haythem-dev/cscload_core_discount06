var Salesweb = null; var SaleswebFinished = false; var SalesWebResult = null;

function initAjaxObjects() // init ajax objects
{    	
	SalesWeb = null; SalesWebFinished = false;
}

function sendAjaxRequests(url) // open ajax objects
{	
	SalesWeb.open( "GET", url, true );	
	SalesWeb.onreadystatechange = updateSeite; SalesWeb.send( null );	
	SaleswebFinished = false;				
}

function createAjaxRequestObjects() // instantiate ajax objects
{		
	try
	{ 
		SalesWeb = new XMLHttpRequest(); 
	}
	catch( tryMicrosoft ) 
	{
		try
		{ 
			SalesWeb = new ActiveXObject( "Msxml2.XMLHTTP" ); 
		}
		catch( tryMicrosoft2 )
		{			
			try
			{ 
				SalesWeb = new ActiveXObject( "Microsoft.XMLHTTP" ); 
			}
			catch( error )
			{ 
				SalesWeb = null; 
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
	//document.getElementById("usercheck").disabled = true;
	
	SalesWebResult = document.getElementById( "SalesWebResult" ); replaceText( SalesWebResult, "" );			
	var username     = document.getElementById("username").value;				
	var userpassword = document.getElementById("password").value;			
	initAjaxObjects();			
	createAjaxRequestObjects(); 			
	var url = "checkaccount.php?username=" + username + "&userpassword=" + userpassword;						
	sendAjaxRequests( url );			
}

function updateSeite()
{
	if( 4 == SalesWeb.readyState && SaleswebFinished == false )
	{
		SaleswebFinished = true;				
		replaceText( SalesWebResult, SalesWeb.responseText );		    
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
