<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
       "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Sales Web Austria Arge Order</title>
<link rel="stylesheet" type="text/css" href="salesweb.css">
<?php

if( !isset( $_REQUEST['Benutzername']  ) ) { $_REQUEST['Benutzername'] = ''; }
if( !isset( $_REQUEST['Passwort']  ) ) { $_REQUEST['Passwort'] = ''; }
if( !isset( $_REQUEST['Customernumber']  ) ) { $_REQUEST['Customernumber'] = ''; }
if( !isset( $_REQUEST['RequestID']  ) ) { $_REQUEST['RequestID'] = ''; }
if( !isset( $_REQUEST['SoftwareID']  ) ) { $_REQUEST['SoftwareID'] = 'A5'; }
if( !isset( $_REQUEST['SupplierID']  ) ) { $_REQUEST['SupplierID'] = 'PHO'; }
if( !isset( $_REQUEST['OrderNumber']  ) ) { $_REQUEST['OrderNumber'] = ''; }
if( !isset( $_REQUEST['OrderDate']  ) ) { $_REQUEST['OrderDate'] = 'JHJJ-MM-DD'; }
if( !isset( $_REQUEST['ArgeOrderVersion'] ) ) { $_REQUEST['ArgeOrderVersion'] = '4.00'; }

$aFilialen = array();
$aFilialen[0]['name']  = 'bitte w&auml;hlen'; 	$aFilialen[0]['value'] = '0'; 
$aFilialen[61]['name'] = '61 Wien'; 			$aFilialen[61]['value'] = '61'; 
$aFilialen[62]['name'] = '62 Graz';     		$aFilialen[62]['value'] = '62';
$aFilialen[63]['name'] = '63 Linz'; 			$aFilialen[63]['value'] = '63'; 
$aFilialen[64]['name'] = '64 Tirol/Jenbach';    $aFilialen[64]['value'] = '64'; 

$aServer = array();
//$aServer[0]['name']= 'Production'; $aServer[0]['value']='https://salesweb.phoenixgroup.eu/wsxmlaustria/argeorder.php';
//$aServer[0]['name']= 'FAKE-Production'; $aServer[0]['value']="https://salestest.phoenixgroup.eu/wsxmlaustria/argeorder.php";
$aServer[1]['name']= 'Test'; $aServer[1]['value']='https://salestest.phoenixgroup.eu/wsxmlaustria/argeorder.php';

$aVersions = array();
$aVersions[0]['name'] = "3.00"; $aVersions[0]['value'] = "3.00";
$aVersions[1]['name'] = "3.01"; $aVersions[1]['value'] = "3.01";
$aVersions[2]['name'] = "3.02"; $aVersions[2]['value'] = "3.02";
$aVersions[3]['name'] = "4.00"; $aVersions[3]['value'] = "4.00";

for($a=0; $a<5; $a++)
{
	if( !isset( $_REQUEST['pzn'.$a]  ) ) { $_REQUEST['pzn'.$a] = ''; }
	if( !isset( $_REQUEST['qty'.$a]  ) ) { $_REQUEST['qty'.$a] = ''; }
	if( !isset( $_REQUEST['CustomerNoteText'.$a]  ) ) { $_REQUEST['CustomerNoteText'.$a] = ''; }
	if( !isset( $_REQUEST['CustomerNoteType'.$a]  ) ) { $_REQUEST['CustomerNoteType'.$a] = ''; }
}

?>
</head>
<body>
<h1>Sales Web Austria Arge Order</h1>
<table border="0">
<form action="<?php print $_SERVER['PHP_SELF']; ?>" method="post">
	<tr>
		<td  align="left">User: </td>
		<td style='padding-right:1em;' >
			<input name="Benutzername" type="text" size="11" value="<?php print $_REQUEST['Benutzername']; ?>">
		</td>
			<td  align="left">Password: </td>
		<td>
			<input name="Passwort" type="password" value="<?php print $_REQUEST['Passwort']; ?>">
		</td>
		<td>
			<select name="Server">
				<?php
				foreach( $aServer as $aS )
				{
					$selected = '';
                    
                    if( isset( $_REQUEST['Server']) )
                    {
                        if( $_REQUEST['Server'] == $aS['value'] ) $selected = ' selected ';
                    }
					?>
					<option value="<?php print $aS['value']; ?>" <?php print $selected; ?> >
						<?php print $aS['name']; ?>
					</option>
					<?php
				}
				?>			
			</select>
		</td>
	</tr>
	<tr>
		<td  align="left"><b>Customernumber:</b></td>
		<td>
			<input name="Customernumber" type="text" size="7" maxlength="7" value="<?php print $_REQUEST['Customernumber']; ?>">
		</td>
		
		<td  align="left"><b>Branch: </b></td>
		<td>
			<select name="Filiale">
				<?php
				foreach( $aFilialen as $aFiliale )
				{
					$selected = '';
                    if( isset( $_REQUEST['Filiale']) )
                    {
                        if( $_REQUEST['Filiale'] == $aFiliale['value'] ) $selected = ' selected ';
                    }
					?>
					<option value="<?php print $aFiliale['value']; ?>" <?php print $selected; ?> >
						<?php print $aFiliale['name']; ?>
					</option>
					<?php
				}
				?>			
			</select>
		</td>	
	</tr>
				<tr>
					<td align="left"><b>Version: </b></td>
					<td>
						<select name="ArgeOrderVersion">
							<?php
							foreach( $aVersions as $aVersion )
							{
								$selected = '';
								if( $_REQUEST['ArgeOrderVersion'] == $aVersion['value'] ) $selected = ' selected ';
								?><option value="<?php print $aVersion['value']; ?>" <?php print $selected; ?> ><?php print $aVersion['name']; ?></option><?php
							}
							?>			
						</select>
					</td>								
				</tr>	
	<tr height=10px;>
	</tr>
	<tr>
		<td><b>RequestID</b></td>
		<td><input name="RequestID" type="text" size=10px value=<?php print $_REQUEST['RequestID']; ?>></td>
		<td><b>SoftwareID</b></td>
		<td><input name="SoftwareID" type="text" size=10px value=<?php print $_REQUEST['SoftwareID']; ?>></td>
		<td><b>SupplierID</b></td>
		<td><input name="SupplierID" type="text" size=10px value=<?php print $_REQUEST['SupplierID']; ?>></td>	
	</tr>
	<tr>
		<td><b>OrderNumber</b></td>
		<td><input name="OrderNumber" type="text" size=10px value=<?php print $_REQUEST['OrderNumber']; ?>></td>
	</tr>
	<tr ><td height=100%><br/></td></tr>
	<!--<tr><td colspan="2"></td><td colspan="2"><u>CustomerNote</u></td></tr>-->
	<tr>
		<td >
			PZN: 
		</td>
		<td>
			Quantity:
		</td>
		<!--
		<td align='left' >
			Type
		</td>
		<td>
			Text
		</td>-->
	</tr>
	<?php
	for($a=0; $a<5; $a++)
	{
		print "<tr>";
		print "<td><input type='text' size=8 maxlength=7 name=pzn".$a." value='".$_REQUEST['pzn'.$a]."'></td>";
		print "<td><input type='text' size=8 maxlength=7 name=qty".$a." value='".$_REQUEST['qty'.$a]."'></td>";
		//print "<td><input type='text' size=15 name=CustomerNoteType".$a." value='".$_REQUEST['CustomerNoteType'.$a]."'></td>";
		//print "<td><input type='text' name=CustomerNoteText".$a." value='".$_REQUEST['CustomerNoteText'.$a]."'></td>";
		print "</tr>";
	}	
	?>
	<tr><td></td><td><input type="Submit" name="Submit"></td></tr>
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
function checkDatum($inDate)
{
	$CountCheckChangeDate=0;
	$timestamp=time();
	$Jahr=date("Y", $timestamp);
	
	$nlCheckChangeDate = preg_split("/-/", $inDate);
	if($nlCheckChangeDate[0]>=($Jahr-10) && $nlCheckChangeDate[0]<=$Jahr)
	{
		$CountCheckChangeDate++;
	}

	if($nlCheckChangeDate[1]>=01 && $nlCheckChangeDate[1]<=12)
	{
		$CountCheckChangeDate++;
	}

	if($nlCheckChangeDate[2]>=01 && $nlCheckChangeDate[2]<=31)
	{
		$CountCheckChangeDate++;
	}

	if(strlen($inDate)==10)
	{
		$CountCheckChangeDate++;
	}

	if($CountCheckChangeDate==4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

function checkPZN()
{
	$artikelcheck=true;
	$x=0;
	for( $a = 0; $a < 5; $a++ )
	{
		$pzn=trim($_REQUEST['pzn'.$a]);
		$qty=trim($_REQUEST['qty'.$a]);
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

function checkBool($inBool)
{
	if($inBool=="true")
	{
		return "bgcolor=green";
	}
	else
	{
		return "bgcolor=red";
	}

}

//XML-Bearbeiten ---------------------------------------------------------------------
if(isset($_REQUEST['Submit']))
{
	require_once( 'post.php' );
	$Benutzername=trim($_REQUEST['Benutzername']);
	$Passwort=trim($_REQUEST['Passwort']);
	$Customernumber=trim($_REQUEST['Customernumber']);
	$Filiale = $_REQUEST['Filiale'];
	$Server = $_REQUEST['Server'];
	$RequestID = $_REQUEST['RequestID'];
	$SoftwareID = $_REQUEST['SoftwareID'];
	$SupplierID = $_REQUEST['SupplierID'];
	$OrderNumber = $_REQUEST['OrderNumber'];
	$Version = $_REQUEST['ArgeOrderVersion'];
	$errorsend=false;
	$timestamp=time();
	$timestampDate=date("Y-m-d", $timestamp);
	$timestampClock=date("H:i:s", $timestamp);
	$RequestTimeStamp=$timestampDate."T".$timestampClock;
	$RequestOrderItem="";
	$XMLNote="";
	$headersend=true;

	
	//DEBUG
	//print $Filiale."|".$Customernumber."|".checkPZN()."|".$OrderNumber."|".$SupplierID."|".$SoftwareID."|".$RequestID."";
	if($Filiale>0 && $Customernumber>0 && checkPZN() && $OrderNumber>0 && $SupplierID!="" && $SoftwareID!="" && $RequestID!="")
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
					/*
					$Benutzername = 'austriaorder';
					$Passwort = 'stepRU7e';*/
					
					$Benutzername = 'xmluploader';
					$Passwort = 'stepRU7e';
					
				}	
		}



		$XMLRequest = file_get_contents( 'requesttemplate.xml' );
		$XMLRequest = str_replace( '#REQUESTID#', $RequestID, $XMLRequest );
		$XMLRequest = str_replace( '#TIMESTAMP#', $RequestTimeStamp, $XMLRequest );
		$XMLRequest = str_replace( '#CUSTOMERID#', $Customernumber, $XMLRequest );
		$XMLRequest = str_replace( '#SOFTWAREID#', $SoftwareID, $XMLRequest );
		$XMLRequest = str_replace( '#SUPPLIERID#', $SupplierID, $XMLRequest );
		$XMLRequest = str_replace( '#BRANCH#', $Filiale, $XMLRequest );
		$XMLRequest = str_replace( '#ORDERNUMBER#', $OrderNumber, $XMLRequest );
		$XMLRequest = str_replace( '#ORDERDATE#', $timestampDate, $XMLRequest );
		$XMLRequest = str_replace( '#ARGEORDERVERSION#', $Version, $XMLRequest );
		
		for($a=0; $a<5; $a++)
		{
			if($_REQUEST['pzn'.$a]!=0 && $_REQUEST['pzn'.$a]!="")
			{
				$XMLNote="";
				$XMLorderItemTemplate = file_get_contents( 'oitemplate.xml' );
				$XMLorderItemTemplate = str_replace( '#POSID#', $a+1, $XMLorderItemTemplate );
				$XMLorderItemTemplate = str_replace( '#QTY#', $_REQUEST['qty'.$a], $XMLorderItemTemplate );
				$XMLorderItemTemplate = str_replace( '#ITEMID_PZN#', "PZN", $XMLorderItemTemplate );
				$XMLorderItemTemplate = str_replace( '#ITEMID_ID#', $_REQUEST['pzn'.$a], $XMLorderItemTemplate );
				//$XMLorderItemTemplate = str_replace( '#SUBSEQUENTDELIVERY#', $SUBSEQUENTDELIVERY, $XMLorderItemTemplate );
				/*if(isset($_REQUEST['CustomerNoteType'.$a]) && $_REQUEST['CustomerNoteType'.$a]!="")
				{	$XMLNote = $XMLNote.' Type="'.$_REQUEST['CustomerNoteType'.$a].'" ';		}
				
				if(isset($_REQUEST['CustomerNoteText'.$a]) && $_REQUEST['CustomerNoteText'.$a]!="")
				{	$XMLNote = $XMLNote.' Text="'.$_REQUEST['CustomerNoteText'.$a].'" ';		}
				
				if(isset($XMLNote) && $XMLNote!=""){	$XMLNote="<ItemNoteCustomer ".$XMLNote."/>";}
				
				$XMLorderItemTemplate = str_replace( '#ItemNoteCustomer#', $XMLNote, $XMLorderItemTemplate );*/
				$RequestOrderItem=$RequestOrderItem."".$XMLorderItemTemplate;
			}
		}
		
		$XMLRequest = str_replace( '#ORDERITEM#', $RequestOrderItem, $XMLRequest );
		//-------------------------------------------------------------------------------------------------------
		//DEBUG AUSGABE
		//file_put_contents("Request.xml", $XMLRequest );
		$XMLResponse = httpPostSimulation::postData( $Server, $Benutzername, $Passwort, $XMLRequest );
		//file_put_contents("Response.xml", $XMLResponse );
		
		$dom = new DOMDocument();
		if( $dom->loadXML( $XMLResponse ) )
		{
			$style="style='padding-right:1em; padding-left:1em;'";
			$root = $dom->documentElement;
			print "<hr/><h2><u>Order</u></h2><br/>";
			print "<table border=1>";
		
			$nlExceptionalCaseInfo = $root->getElementsByTagName( 'ExceptionalCaseInfo' );
			foreach( $nlExceptionalCaseInfo as $ExceptionalCaseInfo )
			{
				$code = $ExceptionalCaseInfo->getAttribute('ExceptionCode');
				$message = $ExceptionalCaseInfo->getAttribute('ExceptionText');

				print "Error: <br/>\r\n";
				print "<table><tr><th>Code</th><th>Message</th></tr>";
				print "<td>".$code."</td><td>".$message."</td>";
				$errorsend=true;
			}

			if($errorsend==true){exit;} //Wenn ERROR ausgegeben wurde, wird abgebrochen -> keine Überschriften etc
	

			$style="align='center' style='padding-right:1em; padding-left:1em;'";
			
			//ORDER
			$nlOrder = $root->getElementsByTagName( 'Order' );
			foreach( $nlOrder as $Order )
			{
				$OrderNumber = $Order->getAttribute('OrderNumber');
				$OrderDate = $Order->getAttribute('OrderDate');
				
				
				
				//OrderConfirmation
				$nlOrderConfirmation= $root->getElementsByTagName( 'OrderConfirmation' );
				foreach( $nlOrderConfirmation as $OrderConfirmation )
				{
					$OrderConfirmation_NumberOfItemsReceived = $OrderConfirmation->getAttribute('NumberOfItemsReceived');
					$OrderConfirmation_DeliveryValue = $OrderConfirmation->getAttribute('DeliveryValue');
				}
				
				//SupplierSpecials
				$SupplierSpecials_NumberOfOrderEntrySystem = 0;
				$nlSupplierSpecials= $root->getElementsByTagName( 'SupplierSpecials' );
				foreach( $nlSupplierSpecials as $SupplierSpecials )
				{
					$SupplierSpecials_NumberOfOrderEntrySystem = $SupplierSpecials->getAttribute('NumberOfOrderEntrySystem');
				}
				print "<table><tr><th ".$style.">Number of Items Received</th><th ".$style.">Delivery Value</th><th ".$style.">Number of Order Entry System</th></tr>";
				print "<tr><td>".$OrderConfirmation_NumberOfItemsReceived."</td><td>".$OrderConfirmation_DeliveryValue."</td><td>".$SupplierSpecials_NumberOfOrderEntrySystem."</td></tr>";
				print "</table>";
				//OrderItem
				$nlOrderItem = $Order->getElementsByTagName( 'OrderItem' );
				foreach( $nlOrderItem as $OrderItem )
				{
					unset($PosId);
					unset($Quantity);
					unset($ItemId_Type);
					unset($ItemId_Id);
					unset($ItemResponse_Quantity);
					unset($ItemResponse_DeliveryPromise);
					unset($ItemResponse_InfoCode);
					unset($ItemResponse_InfoText);
					unset($DeliveryTerms_SubsequentDelivery);
					unset($DeliveryTerms_DeliverySortGroup);
					unset($ItemResponse_InfoCode);
					unset($ItemResponse_InfoText);
					unset($ItemNoteSupplier_Type);
					unset($ItemNoteSupplier_Text);
					
					$PosId = $OrderItem->getAttribute('PosId');
					$Quantity = $OrderItem->getAttribute('Quantity');
					
					
					//ItemId
					$nlItemId = $OrderItem->getElementsByTagName( 'ItemId' );
					foreach( $nlItemId as $ItemId )
					{
						$ItemId_Type = $ItemId->getAttribute('Type');
						$ItemId_Id = $ItemId->getAttribute('Id');
					}
					
					//ItemResponse
					$nlItemResponse = $OrderItem->getElementsByTagName( 'ItemResponse' );
					foreach( $nlItemResponse as $ItemResponse )
					{
						$ItemResponse_Quantity = $ItemResponse->getAttribute('Quantity');
						$ItemResponse_DeliveryPromise = $ItemResponse->getAttribute('DeliveryPromise');
						$ItemResponse_InfoCode = $ItemResponse->getAttribute('InfoCode');
						$ItemResponse_InfoText = $ItemResponse->getAttribute('InfoText');
					}
					
					//DeliveryTerms
					$nlDeliveryTerms = $OrderItem->getElementsByTagName( 'DeliveryTerms' );
					foreach( $nlDeliveryTerms as $DeliveryTerms )
					{
						$DeliveryTerms_SubsequentDelivery = $DeliveryTerms->getAttribute('SubsequentDelivery');
						$DeliveryTerms_DeliverySortGroup = $DeliveryTerms->getAttribute('DeliverySortGroup');
						$ItemResponse_InfoCode = $DeliveryTerms->getAttribute('InfoCode');
						$ItemResponse_InfoText = $DeliveryTerms->getAttribute('InfoText');
					}
					
					//ItemNoteSupplier
					$nlItemNoteSupplier = $OrderItem->getElementsByTagName( 'ItemNoteSupplier' );
					foreach( $nlItemNoteSupplier as $ItemNoteSupplier )
					{
						$ItemNoteSupplier_Type = $ItemNoteSupplier->getAttribute('Type');
						$ItemNoteSupplier_Text = $ItemNoteSupplier->getAttribute('Text');
					}
					
					print "<tr>";
					if($headersend==true)
					{
						print "<br/><h2><u>OrderItem</u></h2><br/>";
						print "<table>";
						if(isset($ItemId_Type))
						{	print "<th  ".$style.">PosId</th><th  ".$style.">Quantity</th>";	}
						
						if(isset($ItemId_Type))
						{	print "<th  ".$style.">Type</th><th  ".$style.">ID</th>";	}
						
						if(isset($ItemResponse_Quantity))
						{	print "<th  ".$style.">Quantity</th><th  ".$style.">DeliveryPromise</th><th  ".$style.">InfoCode</th>";
							print "<th  ".$style.">InfoText</th>";	}
						
						if(isset($DeliveryTerms_SubsequentDelivery))
						{	print "<th  ".$style.">SubsequentDelivery</th><th ".$style.">DeliverySortGroup</th>";
							print "<th ".$style.">InfoCode</th><th ".$style.">InfoText</th>";	}
						
						if(isset($ItemNoteSupplier_Type))
						{	print "<th>Type</th><th>Text</th>";	}
						
						$headersend=false;
					}
					print "</tr>";
				
					print "<tr>";
					print "<td ".$style.">".$PosId."</td><td ".$style.">".$Quantity."</td>";
					if(isset($ItemId_Type) && $ItemId_Type!="")
					{
						print "<td ".$style.">".$ItemId_Type."</td><td ".$style.">".$ItemId_Id."</td>";
					}
					if(isset($ItemResponse_Quantity) && $ItemResponse_Quantity!="")
					{
						print "<td ".$style.">".$ItemResponse_Quantity."</td><td ".$style." ".checkBool($ItemResponse_DeliveryPromise)."></td>";
						print "<td  ".$style.">".$ItemResponse_InfoCode."</td><td align='left'>".$ItemResponse_InfoText."</td>";
					}
					if(isset($DeliveryTerms_SubsequentDelivery) && $DeliveryTerms_SubsequentDelivery!="")
					{
						print "<td ".$style.">".$DeliveryTerms_SubsequentDelivery."</td><td ".$style.">".$DeliveryTerms_DeliverySortGroup."</td>";
						print "<td ".$style.">".$ItemResponse_InfoCode."</td><td ".$style.">".$ItemResponse_InfoText."</td>";
					}
					if(isset($ItemNoteSupplier_Type) && $ItemNoteSupplier_Type!="")
					{
						print "<td ".$style.">".$ItemNoteSupplier_Type."</td><td align='left' >".$ItemNoteSupplier_Text."</td>";
					}

				}//OrderItem->Ende
				
			}//ORDER->Ende
			

			print "</table>";
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
		print "<h1>Please fill all fields with a bold name out!</h1>";
	}
	
	print "<pre>";		
	print "<hr />";
	print "<h3>Debug</h3>";
	print_r( $_REQUEST );
	print "<hr />";	
	print "</pre>";
	
}
?>


</body>
</html>
