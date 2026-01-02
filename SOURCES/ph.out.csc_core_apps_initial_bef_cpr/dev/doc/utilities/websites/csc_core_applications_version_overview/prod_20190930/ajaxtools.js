var vAT     = null; var vATFinished     = false; vATResult     = null;
var vBG     = null; var vBGFinished     = false; vBGResult     = null;
var vCH     = null; var vCHFinished     = false; vCHResult     = null;
var vDE     = null; var vDEFinished     = false; vDEResult     = null;
var vDEXML  = null; var vDEXMLFinished  = false; vDEXMLResult  = null;
var vDEXML2 = null; var vDEXML2Finished = false; vDEXML2Result = null;
var vFR     = null; var vFRFinished     = false; vFRResult     = null;
var vHR     = null; var vHRFinished     = false; vHRResult     = null;
var vRS     = null; var vRSFinished     = false; vRSResult     = null;
var vPAT    = null; var vPATFinished    = false; vPATResult    = null;
var vPCH    = null; var vPCHFinished    = false; vPCHResult    = null;
var vPFR    = null; var vPFRFinished    = false; vPFRResult    = null;

function initAjaxObjects( country )
{    	
	if( country == "at"     ) { vAT     = null; vATFinished     = false; }
	if( country == "bg"     ) { vBG     = null; vBGFinished     = false; }
	if( country == "ch"     ) { vCH     = null; vCHFinished     = false; }
	if( country == "de"     ) { vDE     = null; vDEFinished     = false; }	
	if( country == "deXML"  ) { vDEXML  = null; vDEXMLFinished  = false; }	
	if( country == "fr"     ) { vFR     = null; vFRFinished     = false; }
	if( country == "hr"     ) { vHR     = null; vHRFinished     = false; }
	if( country == "rs"     ) { vRS     = null; vRSFinished     = false; }
	if( country == "pat"    ) { vPAT    = null; vPATFinished    = false; }
	if( country == "pch"    ) { vPCH    = null; vPCHFinished    = false; }
	if( country == "pfr"    ) { vPFR    = null; vPFRFinished    = false; }
	if( country == "deXML2" ) { vDEXML2 = null; vDEXML2Finished = false; }	
}

function sendAjaxRequests(urlorg, country)
{	
	var url = urlorg + "?ReqCountry=" + country; 	
	if( country == "at"     ) { vAT.open( "GET",  url, true   ); vAT.onreadystatechange     = updateSeite; vAT.send( null );     }	
	if( country == "bg"     ) { vBG.open( "GET",  url, true   ); vBG.onreadystatechange     = updateSeite; vBG.send( null );     }
	if( country == "ch"     ) { vCH.open( "GET",  url, true   ); vCH.onreadystatechange     = updateSeite; vCH.send( null );     }
	if( country == "de"     ) { vDE.open( "GET",  url, true   ); vDE.onreadystatechange     = updateSeite; vDE.send( null );     }	
	if( country == "deXML"  ) { vDEXML.open( "GET", url, true ); vDEXML.onreadystatechange  = updateSeite; vDEXML.send( null );  }		
	if( country == "fr"     ) { vFR.open( "GET",  url, true   ); vFR.onreadystatechange     = updateSeite; vFR.send( null );     }
	if( country == "hr"     ) { vHR.open( "GET",  url, true   ); vHR.onreadystatechange     = updateSeite; vHR.send( null );     }
	if( country == "rs"     ) { vRS.open( "GET",  url, true   ); vRS.onreadystatechange     = updateSeite; vRS.send( null );     }
	if( country == "pat"    ) { vPAT.open( "GET", url, true   ); vPAT.onreadystatechange    = updateSeite; vPAT.send( null );    }
	if( country == "pch"    ) { vPCH.open( "GET", url, true   ); vPCH.onreadystatechange    = updateSeite; vPCH.send( null );    }
	if( country == "pfr"    ) { vPFR.open( "GET", url, true   ); vPFR.onreadystatechange    = updateSeite; vPFR.send( null );    }	
	if( country == "deXML2" ) { vDEXML2.open( "GET", url, true ); vDEXML2.onreadystatechange = updateSeite; vDEXML2.send( null ); }		
}

function createAjaxRequestObjects( country )
{		
	if( country == "at"     ) { try { vAT  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vAT  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vAT  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vAT  = null; } } } } 	
	if( country == "bg"     ) { try { vBG  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vBG  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vBG  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vBG  = null; } } } }	
	if( country == "ch"     ) { try { vCH  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vCH  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vCH  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vCH  = null; } } } }	
	if( country == "de"     ) { try { vDE  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vDE  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vDE  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vDE  = null; } } } }		
	if( country == "deXML"  ) { try { vDEXML = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vDEXML = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vDEXML = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vDEXML = null; } } } }	
	if( country == "fr"     ) { try { vFR  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vFR  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vFR  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vFR  = null; } } } }	
	if( country == "hr"     ) { try { vHR  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vHR  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vHR  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vHR  = null; } } } }	
	if( country == "rs"     ) { try { vRS  = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vRS  = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vRS  = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vRS  = null; } } } }		
	if( country == "pat"    ) { try { vPAT = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vPAT = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vPAT = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vPAT = null; } } } }
	if( country == "pch"    ) { try { vPCH = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vPCH = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vPCH = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vPCH = null; } } } }
	if( country == "pfr"    ) { try { vPFR = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vPFR = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vPFR = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vPFR = null; } } } }
	if( country == "deXML2" ) { try { vDEXML2 = new XMLHttpRequest(); } catch( tryMicrosoft ) { try { vDEXML2 = new ActiveXObject( "Msxml2.XMLHTTP" ); } catch( tryMicrosoft2 ) { try { vDEXML2 = new ActiveXObject( "Microsoft.XMLHTTP" ); } catch( error ) { vDEXML2 = null; } } } }		
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
	if( country == "at"  ) { vATResult  = document.getElementById( "ATResult"  ); }
	if( country == "bg"  ) { vBGResult  = document.getElementById( "BGResult"  ); }
	if( country == "ch"  ) { vCHResult  = document.getElementById( "CHResult"  ); }
	if( country == "de"  ) { vDEResult  = document.getElementById( "DEResult"  ); }	
	if( country == "deXML" ) { vDEXMLResult = document.getElementById( "DEXMLResult" ); }	
	if( country == "fr"  ) { vFRResult  = document.getElementById( "FRResult"  ); }
	if( country == "hr"  ) { vHRResult  = document.getElementById( "HRResult"  ); }
	if( country == "rs"  ) { vRSResult  = document.getElementById( "RSResult"  ); }
	if( country == "pat" ) { vPATResult = document.getElementById( "PATResult" ); }
	if( country == "pch" ) { vPCHResult = document.getElementById( "PCHResult" ); }
	if( country == "pfr" ) { vPFRResult = document.getElementById( "PFRResult" ); }		
	if( country == "deXML2" ) { vDEXML2Result = document.getElementById( "DEXML2Result" ); }	
	
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
	if( 4 == vDEXML.readyState && vDEXMLFinished == false ){ vDEXMLFinished = true; replaceText( vDEXMLResult, vDEXML.responseText ); }		
	if( 4 == vFR.readyState  && vFRFinished  == false ){ vFRFinished  = true; replaceText( vFRResult , vFR.responseText  ); }	
	if( 4 == vHR.readyState  && vHRFinished  == false ){ vHRFinished  = true; replaceText( vHRResult , vHR.responseText  ); }	
	if( 4 == vRS.readyState  && vRSFinished  == false ){ vRSFinished  = true; replaceText( vRSResult , vRS.responseText  ); }	
	if( 4 == vPAT.readyState && vPATFinished == false ){ vPATFinished = true; replaceText( vPATResult, vPAT.responseText ); }	
	if( 4 == vPCH.readyState && vPCHFinished == false ){ vPCHFinished = true; replaceText( vPCHResult, vPCH.responseText ); }	
	if( 4 == vPFR.readyState && vPFRFinished == false ){ vPFRFinished = true; replaceText( vPFRResult, vPFR.responseText ); }	
	if( 4 == vDEXML2.readyState && vDEXML2Finished == false ){ vDEXML2Finished = true; replaceText( vDEXML2Result, vDEXML2.responseText ); }	
}

