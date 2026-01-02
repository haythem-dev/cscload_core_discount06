<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
       "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Sales Web Austria Arge Item Info</title>
<link rel="stylesheet" type="text/css" href="salesweb.css">
<?php

if( !isset( $_REQUEST['Benutzername']  ) ) { $_REQUEST['Benutzername'] = ''; }
if( !isset( $_REQUEST['Passwort']  ) ) { $_REQUEST['Passwort'] = ''; }
if( !isset( $_REQUEST['Customernumber']  ) ) { $_REQUEST['Customernumber'] = ''; }
if( !isset( $_REQUEST['RequestID']  ) ) { $_REQUEST['RequestID'] = 'A01'; }
if( !isset( $_REQUEST['SoftwareID']  ) ) { $_REQUEST['SoftwareID'] = 'A5'; }
if( !isset( $_REQUEST['SupplierID']  ) ) { $_REQUEST['SupplierID'] = 'PHO'; }
if( !isset( $_REQUEST['ArgeItemVersion']  ) ) { $_REQUEST['ArgeItemVersion'] = '4.00'; }	
if( !isset( $_REQUEST['Server'] ) ) { $_REQUEST['Server'] = 'https://salestest.phoenixgroup.eu/wsxmlaustria/argeinfo.php'; }

if( isset( $_REQUEST['RequestItemDetails']  ) ) {$RIDcheck="checked=true";}else{ $RIDcheck="";}

for( $a = 1; $a < 6; ++$a)
{	
	if( !isset( $_REQUEST['ID'.$a]  ) ) { $_REQUEST['ID'.$a] = ''; }
	if( !isset( $_REQUEST['Menge'.$a]  ) ) { $_REQUEST['Menge'.$a] = ''; }	
}

$aFilialen = array();
$aFilialen[0]['name']  = 'bitte w&auml;hlen'; 	$aFilialen[0]['value'] = '0'; 
$aFilialen[61]['name'] = '61 Wien'; 			$aFilialen[61]['value'] = '61'; 
$aFilialen[62]['name'] = '62 Graz';     		$aFilialen[62]['value'] = '62';
$aFilialen[63]['name'] = '63 Linz'; 			$aFilialen[63]['value'] = '63'; 
$aFilialen[64]['name'] = '64 Tirol/Jenbach';    $aFilialen[64]['value'] = '64'; 

$aServer = array();
$aServer[0]['name']= 'Production'; $aServer[0]['value']='https://salesweb.phoenixgroup.eu/wsxmlaustria/argeinfo.php';
$aServer[1]['name']= 'Test'; $aServer[1]['value']='https://salestest.phoenixgroup.eu/wsxmlaustria/argeinfo.php';
$aServer[2]['name']= 'Acceptance'; $aServer[2]['value']='http://denu1vc0029.phoenix.loc/WebServiceAustriaFrontend/pa.aspx';

$aVersions = array();
$aVersions[0]['name'] = "3.00"; $aVersions[0]['value'] = "3.00";
$aVersions[1]['name'] = "3.01"; $aVersions[1]['value'] = "3.01";
$aVersions[2]['name'] = "3.02"; $aVersions[2]['value'] = "3.02";
$aVersions[3]['name'] = "4.00"; $aVersions[3]['value'] = "4.00";


?>
</head>
<body>
<h1>Sales Web Austria Arge Item Info</h1>
<table border="0">
<form action="<?php print $_SERVER['PHP_SELF']; ?>" method="post">
	<tr>
		<td valign="top">
			<table border="1px" height="200px">
				<tr>
					<td align="left">User: </td>
					<td style='padding-right:1em;' ><input name="Benutzername" type="text" size="11" value="<?php print $_REQUEST['Benutzername']; ?>"></td>
				</tr>
				<tr>
					<td align="left">Password: </td>
					<td><input name="Passwort" type="password" size="11" value="<?php print $_REQUEST['Passwort']; ?>"></td>
				</tr>
				<tr>
					<td align="left">Server:</td>
					<td>
						<select name="Server">
							<?php
							foreach( $aServer as $aS )
							{
								$selected = '';
								if( $_REQUEST['Server'] == $aS['value'] ) $selected = ' selected ';
								?><option value="<?php print $aS['value']; ?>" <?php print $selected; ?> ><?php print $aS['name']; ?></option><?php
							}
							?>			
						</select>
					</td>				
				</tr>
				<tr>
					<td align="left"><b>Branch: </b></td>
					<td>
						<select name="Filiale">
							<?php
							foreach( $aFilialen as $aFiliale )
							{
								$selected = '';
                                if( isset($_REQUEST['Filiale']) )
                                {
                                    if( $_REQUEST['Filiale'] == $aFiliale['value'] ) $selected = ' selected ';
                                }
								?><option value="<?php print $aFiliale['value']; ?>" <?php print $selected; ?> ><?php print $aFiliale['name']; ?></option><?php
							}
							?>			
						</select>
					</td>				
				</tr>
				<tr>
					<td align="left"><b>CustomerNo:</b></td>
					<td><input name="Customernumber" type="text" size="7" maxlength="7" value="<?php print $_REQUEST['Customernumber']; ?>"></td>
				</tr>
				<tr><td>&nbsp;</td></tr>
			</table>
		</td>				
		<td valign="top">
			<table border="1px" height="200px">
				<tr>
					<td align="left"><b>Version: </b></td>
					<td>
						<select name="ArgeItemVersion">
							<?php
							foreach( $aVersions as $aVersion )
							{
								$selected = '';
								if( $_REQUEST['ArgeItemVersion'] == $aVersion['value'] ) $selected = ' selected ';
								?><option value="<?php print $aVersion['value']; ?>" <?php print $selected; ?> ><?php print $aVersion['name']; ?></option><?php
							}
							?>			
						</select>
					</td>								
				</tr>
				<tr>
					<td>RequestID:</td>
					<td><input type="text" size=10px value=<?php print $_REQUEST['RequestID'] ?>></td>
				</tr>
				<tr>
					<td>SoftwareID:</td>
					<td><input type="text" size=10px value=<?php print $_REQUEST['SoftwareID'] ?>></td>					
				</tr>
				<tr>
					<td>SupplierID:</td>
					<td><input type="text" size=10px value=<?php print $_REQUEST['SupplierID'] ?>></td>				
				</tr>
				<tr>
					<td>ItemDetails:</td>
					<td><input type="checkbox" name="RequestItemDetails" <?php print $RIDcheck ?>></td>						
				</tr>
			</table>
		</td>		
		<td valign="top">
			<table border="1px" height="200px">
				<tr>
					<td align='center' valign="center"> Barcode </td>
					<td align='center' valign="center"> PZN </td>
					<td align='center' valign="center"> ID </td>
					<td align='center' valign="center"> Menge </td>
					<td></td>
				</tr>
				<?php
				for($a=1; $a<6; $a++)
				{
					$Pchecked="";
					$Bchecked="";

					if(isset($_REQUEST["type".$a]) && $_REQUEST["type".$a] == 'Barcode')
						{$Bchecked="checked";}
					else
					{
						if((isset($_REQUEST["type".$a]) && $_REQUEST["type".$a] == 'PZN') || !isset($_REQUEST["type".$a]))
							{$Pchecked="checked";}
					}

					print "<tr>";
					print '<td align="center"><input type="radio" name="type'.$a.'" value="Barcode" '.$Bchecked.'></td>';
					print '<td align="left"><input type="radio" name="type'.$a.'" value="PZN" '.$Pchecked.'></td>';
					//print "<td  align='left'>ID: </td>";
					print "<td><input name='ID".$a."' type='text' size='13' maxlength='13' value='".$_REQUEST['ID'.$a]."'></td>";
					//print "<td  align='left'>Menge: </td>";
					print "	<td><input name='Menge".$a."' type='text' size='5' maxlength='5' value='".$_REQUEST['Menge'.$a]."'></td>";
					print "</tr>";

				}

				?>
				</tr>			
			</table>
		</td>
	</tr>		
</table>
<table>
	<tr>
		<td align="center" colspan="2">
			<br><input type="submit" value="SEND" name="Submit" size="center">
		</td>
	</tr>
</form>
</table>

<?php

/*print "<pre>";		
//print $Server.$Filiale;
print "<hr />";
print "<h3>Debug</h3>";
print_r( $_REQUEST );
print "<hr />";	
print "</pre>";*/

//FUNKTIONEN
function checkPZN()
{
	$artikelcheck=true;
	$x=0;
	for( $a = 1; $a < 6; $a++ )
	{
		$pzn=trim($_REQUEST['ID'.$a]);
		$qty=trim($_REQUEST['Menge'.$a]);
		if($pzn!='' && $qty=='')
		{
			$artikelcheck=false;
		}
		
		if($pzn=='' && $qty!='')
		{
			$artikelcheck=false;
		}
		
		if($pzn=='')
		{
			$x+=1;
		}
				
		/*if(!is_numeric($_REQUEST['Menge'.$a]) || !is_numeric($_REQUEST['PZN'.$a]) || !is_numeric($_REQUEST['Kundennummer']))
		{
			$artikelcheck=false;
		}*/
		

	}
	
	if($artikelcheck==true && $x!=5)
	{
		return $artikelcheck;
	}
	{
		return false;
	}	
}

function checkZero($inZahl)
{
	if($inZahl!=0 && $inZahl!="")
	{
		return $inZahl;
	}
	else
	{
		return "";
	}
}

function checkEuro($inZahl)
{
	if($inZahl!=0 && $inZahl!="")
	{
		return $inZahl." &euro;";
	}
	else
	{
		return "";
	}
}


//XML-Bearbeiten ---------------------------------------------------------------------
if(isset($_REQUEST['Submit']))
{
	require_once( 'post.php' );
	$Benutzername=trim($_REQUEST['Benutzername']);
	$Passwort=trim($_REQUEST['Passwort']);
	$Customernumber=trim($_REQUEST['Customernumber']);
	$RequestID=trim($_REQUEST['RequestID']);
	$SoftwareID=trim($_REQUEST['SoftwareID']);
	$SupplierID=trim($_REQUEST['SupplierID']);
	$Filiale = $_REQUEST['Filiale'];
	$Server = $_REQUEST['Server'];
	$errorsend=false;
	$Version = $_REQUEST['ArgeItemVersion'];
	if($RIDcheck==""){$RID="false";}else{$RID="true";}
	
	//TIMESTAMP
	$timestamp2=time();
	$Date=date("Y-m-d", $timestamp2);
	$Time=date("H:i:s", $timestamp2);
	$Timestamp=$Date."T".$Time;

	if($Filiale>0 && $Customernumber>0 && checkPZN())
	{
		if( strstr($Server, 'salestest') )
		{
				if( strlen($Benutzername) == '' )
				{
					$Benutzername = 'xmluploader';
					$Passwort = 'stepRU7e';
				}
		}
		else
		{
				if( strlen($Benutzername) == '' )
				{
					$Benutzername = 'xmluploader';
					$Passwort = 'stepRU7e';
				}	
		}


		$XMLRequest = file_get_contents( 'requesttemplate.xml' );
		$XMLRequest = str_replace( '#BRANCH#', $Filiale, $XMLRequest );
		$XMLRequest = str_replace( '#CUSTOMERNUMBER#', $Customernumber, $XMLRequest );
		$XMLRequest = str_replace( '#REQUESTID#', $RequestID, $XMLRequest );
		$XMLRequest = str_replace( '#TIMESTAMP#', $Timestamp, $XMLRequest );
		$XMLRequest = str_replace( '#RID#', $RID, $XMLRequest );
		$XMLRequest = str_replace( '#SWID#', $SoftwareID, $XMLRequest );
		$XMLRequest = str_replace( '#SUPPLIERID#', $SupplierID, $XMLRequest );
		$XMLRequest = str_replace( '#ARGEITEMVERSION#', $Version, $XMLRequest );
		
		$InfoItem="";
		for($a=1; $a<=5; $a++)
		{
			
			if(isset($_REQUEST['ID'.$a]) && $_REQUEST['ID'.$a]!="")
			{
				$InfoItemRequest=file_get_contents( 'requestInfoItemtemplate.xml' );
				$InfoItemRequest = str_replace( '#POSID#', $a, $InfoItemRequest );
				$InfoItemRequest = str_replace( '#QTY#', $_REQUEST['Menge'.$a], $InfoItemRequest );
				$InfoItemRequest = str_replace( '#ID#', $_REQUEST['ID'.$a], $InfoItemRequest );
				$InfoItemRequest = str_replace( '#TYPE#', $_REQUEST['type'.$a], $InfoItemRequest );
				$InfoItem=$InfoItem.$InfoItemRequest;
				
			}
		}
		
		$XMLRequest = str_replace( '#INFOITEM#', $InfoItem, $XMLRequest );
		//-------------------------------------------------------------------------------------------------------
		//DEBUG AUSGABE
		//file_put_contents("Request.xml", $XMLRequest );
		$XMLResponse = httpPostSimulation::postData( $Server, $Benutzername, $Passwort, $XMLRequest );
		//file_put_contents("Response.xml", $XMLResponse );
		
		$dom = new DOMDocument();
		if( $dom->loadXML( $XMLResponse ) )
		{
		
			$style="style='padding-right:0.5em; padding-left:0.5em;'";
			$root = $dom->documentElement;
			print "<hr/><h1>Result</h1><br/>";
			print "<table border=1>";
			print "<tr>";
			/*
			$nlError = $root->getElementsByTagName( 'Error' );
			foreach( $nlError as $error )
			{
				$code = $error->getAttribute('Code');
				$message = $error->getAttribute('Message');

				print "Error: <br/>\r\n";
				print "<table><tr><th>Code</th><th>Message</th></tr>";
				print "<td>".$code."</td><td>".$message."</td>";
				$errorsend=true;
			}*/



			$style="align='center' style='padding-right:1em; padding-left:1em;'";
			$InfoItemheaderSend=false;
			$nlInfoItem = $root->getElementsByTagName( 'InfoItem' );
			foreach( $nlInfoItem as $InfoItem )
			{
				if($InfoItemheaderSend==false)
				{
					print "<th ".$style.">PosId</th><th ".$style.">Quantity</th><th ".$style.">Availability</th>";
					print "<th ".$style.">InfoCode</th><th ".$style.">InfoText</th><th ".$style.">Productname</th><th ".$style.">PurchasePrice</th><th ".$style.">RetailPrice</th>";
					print "<th ".$style.">PZN</th><th ".$style.">Type</th><th ".$style.">Text</th><th ".$style.">ChangeReason</th>";

					$InfoItemheaderSend=true;
					print "</tr>";
				}
				$PosId = $InfoItem->getAttribute('PosId');
				$Quantity = $InfoItem->getAttribute('Quantity');
				$Productname = "";
				$PurchasePrice = "";
				$RetailPrice = "";
				$PZN = "";
				$Availability = "";
				$InfoCode = "";
				$InfoText = "";
				$Type = "";
				$Text = "";
				$ChangeReason = "";
				
				$nlItemAvailability = $InfoItem->getElementsByTagName( 'ItemAvailability' );
				foreach($nlItemAvailability as $ItemAvailability)
				{
					$Availability = $ItemAvailability->getAttribute('Availability');
					$InfoCode = $ItemAvailability->getAttribute('InfoCode');
					$InfoText = $ItemAvailability->getAttribute('InfoText');
				}
				
				$nlItemDetails = $InfoItem->getElementsByTagName( 'ItemDetails' );
				foreach($nlItemDetails as $ItemDetails)
				{
					$Productname = $ItemDetails->getAttribute('Productname');
					$PurchasePrice = $ItemDetails->getAttribute('PurchasePrice');
					$RetailPrice = $ItemDetails->getAttribute('RetailPrice');
					$PZN = $ItemDetails->getAttribute('PZN');
				}
				
				$nlItemChangedTo = $InfoItem->getElementsByTagName( 'ItemChangedTo' );
				foreach($nlItemChangedTo as $ItemChangedTo)
				{
					$Productname = $ItemChangedTo->getAttribute('Productname');
					$PurchasePrice = $ItemChangedTo->getAttribute('PurchasePrice');
					$RetailPrice = $ItemChangedTo->getAttribute('RetailPrice');
					$PZN = $ItemChangedTo->getAttribute('PZN');
					$ChangeReason = $ItemChangedTo->getAttribute('ChangeReason');
				}
				
				$nlItemNoteSupplier = $InfoItem->getElementsByTagName( 'ItemNoteSupplier' );
				foreach($nlItemNoteSupplier as $ItemNoteSupplier)
				{
					$Type = $ItemNoteSupplier->getAttribute('Type');
					$Text = $ItemNoteSupplier->getAttribute('Text');
				}
				


				print "<tr>";
				print "<td align='center'>".$PosId."</td><td align='center'>".$Quantity."</td><td bgcolor=".$Availability."></td>";
				print "<td align='center'>".$InfoCode."</td><td align='center'>".$InfoText."</td><td  align='left' >".$Productname."</td><td align='right' ".$style.">".checkEuro(checkZero($PurchasePrice))."</td>";	
				print "<td align='right' ".$style.">".checkEuro(checkZero($RetailPrice))."</td><td >".$PZN."</td><td ".$style." >".$Type."</td>";	
				print "<td align='left'>".$Text."</td><td >".$ChangeReason."</td>";
				
			}
			print "</table>";
			
			$IINSheaderSend=false;
			$nlItemInfoNotesSupplier = $root->getElementsByTagName( 'ItemInfoNotesSupplier' );
			foreach( $nlItemInfoNotesSupplier as $ItemInfoNotesSupplier )
			{
				$Type = $ItemInfoNotesSupplier->getAttribute('Type');
				$Text = $ItemInfoNotesSupplier->getAttribute('Text');
				
				if($IINSheaderSend==false)
				{
					print "<table><tr><th>Type</th><th>Text</th></tr>";
					$IINSheaderSend=true;
				}
				
				print "<tr>";
				print "<td align='right' ".$style." >".$Type."</td>";
				print "<td align='right' ".$style." >".$Text."</td>";
				print "</tr>";
			}
			if($IINSheaderSend==true){print "</table>";}
			
			$SuppSpecHeadSend=false;
			$nlSupplierSpecials = $root->getElementsByTagName( 'SupplierSpecials' );
			foreach( $nlSupplierSpecials as $SupplierSpecials )
			{
				if($SuppSpecHeadSend==false)
				{
					print "<table><tr><th>SupplierSpecial</th></tr>";
					$SuppSpecHeadSend=true;
				}
				
				
				print var_dump($SupplierSpecials );
			}
			if($SuppSpecHeadSend==true){print "</table>";}
			
			
			$ECIheadSend=false;
			$nlExceptionalCaseInfo = $root->getElementsByTagName( 'ExceptionalCaseInfo' );
			foreach( $nlExceptionalCaseInfo as $ExceptionalCaseInfo )
			{
				if($ECIheadSend==false)
				{
					print "<table><tr><th>Code</th><th>Text</th></tr>";
					$ECIheadSend=true;
				}
				
				
				$Code = $ExceptionalCaseInfo->getAttribute('ExceptionCode');
				$Text = $ExceptionalCaseInfo->getAttribute('ExceptionText');
	
				print "<tr><td>".$Code."</td><td>".$Text."</td></tr>";
			}
			if($ECIheadSend==true){print "</table>";}
		}
		else
		{
			print "Failed to load XML";
		}
		
		
		$dom = new DOMDocument;
		
		print "<br/><br/><hr />";
		print "<br/><h2>XML-Request</h2><pre>";		
		$dom->preserveWhiteSpace = false;
		$dom->loadXML($XMLRequest);
		$dom->formatOutput = true;
		print htmlspecialchars( $dom->saveXml() );		
		print"</pre><hr />";		
				
		print "<br/><h2>XML-Respone</h2><pre>";				
		//print htmlspecialchars($XMLResponse); 								
		$dom->preserveWhiteSpace = false;
		$dom->loadXML($XMLResponse);
		$dom->formatOutput = true;
		print htmlspecialchars( $dom->saveXml() );		
		print "</pre><hr />";	
		
		

		
	}
	else
	{
		print "<h1>Please enter data for all fields written in bold!</h1>";
	}
	/*
	print "<pre>";		
	//print $Server.$Filiale;
	print "<hr />";
	print "<h3>Debug</h3>";
	print_r( $_REQUEST );
	print "<hr />";	
	print "</pre>";
	*/
}
?>


</body>
</html>
