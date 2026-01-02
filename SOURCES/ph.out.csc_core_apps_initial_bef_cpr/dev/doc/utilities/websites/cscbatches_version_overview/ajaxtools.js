var vAT  = null; var vATFinished  = false; vATResult  = null;
var vBG  = null; var vBGFinished  = false; vBGResult  = null;
var vCH  = null; var vCHFinished  = false; vCHResult  = null;
var vDE  = null; var vDEFinished  = false; vDEResult  = null;
var vFR  = null; var vFRFinished  = false; vFRResult  = null;
var vHR  = null; var vHRFinished  = false; vHRResult  = null;
var vRS  = null; var vRSFinished  = false; vRSResult  = null;


function initAjaxObjects( country )
{    	
	if( country == "at"  ) { vAT  = null; vATFinished  = false; }
	if( country == "bg"  ) { vBG  = null; vBGFinished  = false; }
	if( country == "ch"  ) { vCH  = null; vCHFinished  = false; }
	if( country == "de"  ) { vDE  = null; vDEFinished  = false; }	
	if( country == "fr"  ) { vFR  = null; vFRFinished  = false; }
	if( country == "hr"  ) { vHR  = null; vHRFinished  = false; }
	if( country == "rs"  ) { vRS  = null; vRSFinished  = false; }
}

function sendAjaxRequests(urlorg, country)
{	
	var url = urlorg + "?ReqCountry=" + country; 	
	if( country == "at"  ) { vAT.open( "GET",  url, true ); vAT.onreadystatechange  = updateSeite; vAT.send( null );  }	
	if( country == "bg"  ) { vBG.open( "GET",  url, true ); vBG.onreadystatechange  = updateSeite; vBG.send( null );  }
	if( country == "ch"  ) { vCH.open( "GET",  url, true ); vCH.onreadystatechange  = updateSeite; vCH.send( null );  }
	if( country == "de"  ) { vDE.open( "GET",  url, true ); vDE.onreadystatechange  = updateSeite; vDE.send( null );  }	
	if( country == "fr"  ) { vFR.open( "GET",  url, true ); vFR.onreadystatechange  = updateSeite; vFR.send( null );  }
	if( country == "hr"  ) { vHR.open( "GET",  url, true ); vHR.onreadystatechange  = updateSeite; vHR.send( null );  }
	if( country == "rs"  ) { vRS.open( "GET",  url, true ); vRS.onreadystatechange  = updateSeite; vRS.send( null );  }	
}

function createAjaxRequestObjects( country )
{		
	if( country == "at"  ) { try { vAT  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vAT  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vAT  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vAT  = null; } } } } 	
	if( country == "bg"  ) { try { vBG  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vBG  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vBG  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vBG  = null; } } } }	
	if( country == "ch"  ) { try { vCH  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vCH  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vCH  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vCH  = null; } } } }	
	if( country == "de"  ) { try { vDE  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vDE  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vDE  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vDE  = null; } } } }		
	if( country == "fr"  ) { try { vFR  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vFR  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vFR  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vFR  = null; } } } }	
	if( country == "hr"  ) { try { vHR  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vHR  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vHR  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vHR  = null; } } } }	
	if( country == "rs"  ) { try { vRS  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vRS  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vRS  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vRS  = null; } } } }			
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

function getInformation(country)
{		
	if( country == "at"  ) { vATResult  = document.getElementById( "ATResult"  ); /*replaceText( vATResult, "getting information for "  + country + " ..." );*/ }
	if( country == "bg"  ) { vBGResult  = document.getElementById( "BGResult"  ); /*replaceText( vBGResult, "getting information for "  + country + " ..." );*/ }
	if( country == "ch"  ) { vCHResult  = document.getElementById( "CHResult"  ); /*replaceText( vCHResult, "getting information for "  + country + " ..." );*/ }
	if( country == "de"  ) { vDEResult  = document.getElementById( "DEResult"  ); /*replaceText( vDEResult, "getting information for "  + country + " ..." );*/ }	
	if( country == "fr"  ) { vFRResult  = document.getElementById( "FRResult"  ); /*replaceText( vFRResult, "getting information for "  + country + " ..." );*/ }
	if( country == "hr"  ) { vHRResult  = document.getElementById( "HRResult"  ); /*replaceText( vHRResult, "getting information for "  + country + " ..." );*/ }
	if( country == "rs"  ) { vRSResult  = document.getElementById( "RSResult"  ); /*replaceText( vRSResult, "getting information for "  + country + " ..." );*/ }
	
	initAjaxObjects( country );		
	createAjaxRequestObjects( country ); 				
	sendAjaxRequests( "ajaxworker.php", country );			
}

function updateSeite()
{	
	if( 4 == vAT.readyState  && vATFinished  == false ){ vATFinished  = true; replaceText( vATResult , vAT.responseText  ); }	
	if( 4 == vBG.readyState  && vBGFinished  == false ){ vBGFinished  = true; replaceText( vBGResult , vBG.responseText  ); }	
	if( 4 == vCH.readyState  && vCHFinished  == false ){ vCHFinished  = true; replaceText( vCHResult , vCH.responseText  ); }	
	if( 4 == vDE.readyState  && vDEFinished  == false ){ vDEFinished  = true; replaceText( vDEResult , vDE.responseText  ); }		
	if( 4 == vFR.readyState  && vFRFinished  == false ){ vFRFinished  = true; replaceText( vFRResult , vFR.responseText  ); }	
	if( 4 == vHR.readyState  && vHRFinished  == false ){ vHRFinished  = true; replaceText( vHRResult , vHR.responseText  ); }	
	if( 4 == vRS.readyState  && vRSFinished  == false ){ vRSFinished  = true; replaceText( vRSResult , vRS.responseText  ); }	
}

