// ajax objects
var sw1anfrage = null; 
var sw2anfrage = null; 
var sw3anfrage = null; 
var sw4anfrage = null; 
var sw5anfrage = null; 
var sw6anfrage = null; 
var sw7anfrage = null; 
var sw8anfrage = null; 
var sw9anfrage = null;
var sw1finished = false;
var sw2finished = false;
var sw3finished = false;
var sw4finished = false;
var sw5finished = false;
var sw6finished = false;
var sw7finished = false;
var sw8finished = false;	
var sw9finished = false;
var result1 = null;
var result2 = null;
var result3 = null;
var result4 = null;
var result5 = null;
var result6 = null;
var result7 = null;
var result8 = null;
var result9 = null;

// init ajax objects    
function initAjaxObjects()
{    	
	sw1anfrage = null; 
	sw1finished = false;
	sw2anfrage = null; 
	sw2finished = false;
	sw3anfrage = null; 
	sw3finished = false;
	sw4anfrage = null; 
	sw4finished = false;
	sw5anfrage = null; 
	sw5finished = false;
	sw6anfrage = null; 
	sw6finished = false;
	sw7anfrage = null; 
	sw7finished = false;
	sw8anfrage = null; 
	sw8finished = false;
	sw9anfrage = null; 
	sw9finished = false;	
}

// open ajax objects
function sendAjaxRequests(url)
{
	var urlorg = url;
	
	url = urlorg + "&No=1";
	sw1anfrage.open( "GET", url, true );
	url = urlorg + "&No=2";
	sw2anfrage.open( "GET", url, true );
	url = urlorg + "&No=3";
	sw3anfrage.open( "GET", url, true );
	url = urlorg + "&No=4";
	sw4anfrage.open( "GET", url, true );
	url = urlorg + "&No=5";
	sw5anfrage.open( "GET", url, true );
	url = urlorg + "&No=6";
	sw6anfrage.open( "GET", url, true );
	url = urlorg + "&No=7";
	sw7anfrage.open( "GET", url, true );
	url = urlorg + "&No=8";
	sw8anfrage.open( "GET", url, true );
	url = urlorg + "&No=9";		
	sw9anfrage.open( "GET", url, true );
			
	sw1anfrage.onreadystatechange = updateSeite;
	sw2anfrage.onreadystatechange = updateSeite;
	sw3anfrage.onreadystatechange = updateSeite;
	sw4anfrage.onreadystatechange = updateSeite;
	sw5anfrage.onreadystatechange = updateSeite;
	sw6anfrage.onreadystatechange = updateSeite;
	sw7anfrage.onreadystatechange = updateSeite;
	sw8anfrage.onreadystatechange = updateSeite;
	sw9anfrage.onreadystatechange = updateSeite;
		
	sw1anfrage.send( null );
	sw2anfrage.send( null );
	sw3anfrage.send( null );
	sw4anfrage.send( null );
	sw5anfrage.send( null );
	sw6anfrage.send( null );
	sw7anfrage.send( null );
	sw8anfrage.send( null );	
	sw9anfrage.send( null );
}

// instantiate ajax objects
function createAjaxRequestObjects()
{		
	try
	{ 
		sw1anfrage = new XMLHttpRequest(); 
		sw2anfrage = new XMLHttpRequest(); 
		sw3anfrage = new XMLHttpRequest(); 
		sw4anfrage = new XMLHttpRequest(); 
		sw5anfrage = new XMLHttpRequest(); 
		sw6anfrage = new XMLHttpRequest(); 
		sw7anfrage = new XMLHttpRequest(); 
		sw8anfrage = new XMLHttpRequest(); 
		sw9anfrage = new XMLHttpRequest(); 
	}
	catch( tryMicrosoft ) 
	{
		try
		{ 
			sw1anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw2anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw3anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw4anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw5anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw6anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw7anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw8anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
			sw9anfrage = new ActiveXObject( "Msxml2.XMLHTTP" ); 
		}
		catch( tryMicrosoft2 )
		{			
			try
			{ 
				sw1anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw2anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw3anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw4anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw5anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw6anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw7anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw8anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
				sw9anfrage = new ActiveXObject( "Microsoft.XMLHTTP" ); 
			}
			catch( error )
			{ 
				sw1anfrage = null; 
				sw2anfrage = null; 
				sw3anfrage = null; 
				sw4anfrage = null; 
				sw5anfrage = null; 
				sw6anfrage = null; 
				sw7anfrage = null; 
				sw8anfrage = null; 
				sw9anfrage = null; 
			}
		}		
	}		
}

function replaceText( el, text )
{	
	if( el != null )
	{
		el.innerHTML = text;
		//clearText( el );
		//var newNode = document.createTextNode( text );
		//el.appendChild( newNode );
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

function Search4LogEntries()
{			
	
	result1 = document.getElementById( "resultArea1" );
	result2 = document.getElementById( "resultArea2" );
	result3 = document.getElementById( "resultArea3" );
	result4 = document.getElementById( "resultArea4" );
	result5 = document.getElementById( "resultArea5" );
	result6 = document.getElementById( "resultArea6" );
	result7 = document.getElementById( "resultArea7" );
	result8 = document.getElementById( "resultArea8" );			
	result9 = document.getElementById( "resultArea9" );			
	
	replaceText( result1, "" );		
	replaceText( result2, "" );		
	replaceText( result3, "" );		
	replaceText( result4, "" );		
	replaceText( result5, "" );		
	replaceText( result6, "" );		
	replaceText( result7, "" );		
	replaceText( result8, "" );		
	replaceText( result9, "" );		
					
	// get values from form
	var idx = 0;				
	
	idx = document.getElementById("logdbName").selectedIndex;
	var logdbName = document.getElementById("logdbName").options[idx].value;				
	
	idx = document.getElementById("logdbType").selectedIndex;
	var logdbType = document.getElementById("logdbType").options[idx].value;				
	
	idx = document.getElementById("logDate").selectedIndex;
	var logDate = document.getElementById("logDate").options[idx].value;
	
	idx = document.getElementById("serverName").selectedIndex;		
	var serverName = document.getElementById("serverName").options[idx].value;				
	
	idx = document.getElementById("branchNo").selectedIndex;		
	var branchNo = document.getElementById("branchNo").options[idx].value;							
	
	var customerNo = document.getElementById("customerNo").value;			
	
	var orderNo = document.getElementById("orderNo").value;
	
	var reference = document.getElementById("reference").value;
	
	var txtInRequest = document.getElementById("txtInRequest").value;	
	var txtInResponse = document.getElementById("txtInResponse").value;	
	
	initAjaxObjects();		
	createAjaxRequestObjects(); 		
	var url = "logsearcher.php" + "?logdbName=" + logdbName + "&logdbType=" + logdbType + "&logDate=" + logDate + "&serverName=" + serverName + "&branchNo=" + branchNo + "&customerNo=" + customerNo + "&orderNo=" + orderNo + "&reference=" + reference + "&xmlreq=" + txtInRequest + "&xmlres=" + txtInResponse;				
	
	sendAjaxRequests( url );				
}

function updateSeite()
{
	if( 4 == sw1anfrage.readyState && sw1finished == false )
	{
		sw1finished = true;				
		replaceText( result1, sw1anfrage.responseText );		    
	}		
	if( 4 == sw2anfrage.readyState && sw2finished == false )
	{
		sw2finished = true;
		replaceText( result2, sw2anfrage.responseText );		    
	}		
	if( 4 == sw3anfrage.readyState && sw3finished == false )
	{
		sw3finished = true;
		replaceText( result3, sw3anfrage.responseText );		    
	}				
	if( 4 == sw4anfrage.readyState && sw4finished == false )
	{
		sw4finished = true;
		replaceText( result4, sw4anfrage.responseText );		    
	}		
	if( 4 == sw5anfrage.readyState && sw5finished == false )
	{
		sw5finished = true;
		replaceText( result5, sw5anfrage.responseText );		    
	}							
	if( 4 == sw6anfrage.readyState && sw6finished == false )
	{
		sw6finished = true;
		replaceText( result6, sw6anfrage.responseText );		    
	}				
	if( 4 == sw7anfrage.readyState && sw7finished == false )
	{
		sw7finished = true;
		replaceText( result7, sw7anfrage.responseText );		    
	}						
	if( 4 == sw8anfrage.readyState && sw8finished == false )
	{
		sw8finished = true;
		replaceText( result8, sw8anfrage.responseText );		    
	}			
	if( 4 == sw9anfrage.readyState && sw9finished == false )
	{
		sw9finished = true;
		replaceText( result9, sw9anfrage.responseText );		    
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

function changeDatabase()
{
	var idx = 0;					
	idx = document.getElementById("logdbName").selectedIndex;
	var logdbName = document.getElementById("logdbName").options[idx].value;				
	
	document.getElementById('orderOptions').style.display = 'none';						
	document.getElementById('textOptions').style.display = 'block';						
	
	if( logdbName == 'Order' )
	{
		document.getElementById('orderOptions').style.display = 'block';								
	}		
}