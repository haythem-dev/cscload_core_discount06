<html>

<head>
	<title>KSC Services Portscan</title>
	<link rel="stylesheet" type="text/css" href="style.css"/>
	<?php	
	require_once( "TelnetConn.php" );	
		
	$doTelnetChecksTCAccess = false;	
	$checkTelnetChecksTCAccess = "";
	
	$aCountry = array();
	$aCountry[] = "All";
	$aCountry[] = "Austria";
	$aCountry[] = "Bulgaria";
	$aCountry[] = "Croatia";
	$aCountry[] = "France";
	$aCountry[] = "Germany";
	$aCountry[] = "Serbia";
	$aCountry[] = "Switzerland";	

	$aServices = array();
	$aServices[] = "All";
	$aServices[] = "cscservice";
	$aServices[] = "kscserver";
	$aServices[] = "zaapunix";
    
    $selected="";
    $aLand = "";
    $aService = "";
	
	$doTelnetChecksTCAccess = true; $checkTelnetChecksTCAccess=" checked "; 
	?>
</head>

<body>
	<h1>KSC Services Portscan</h1>	
	<form action="<?php print $_SERVER['PHP_SELF']; ?>" method="POST">
		<table>
			<tr>
				<td>
					Country:
					<select name="country" size="1">
						<?php
						foreach($aCountry as $aLand)
						{	
                            if( isset($_REQUEST['country']) )
                            {
                                if($_REQUEST['country'] == $aLand) 
                                {
                                    $selected = ' selected ';
                                }
                            }
							?>
							<option value="<?php echo( $aLand ); ?>" <?php echo( $selected ); ?>>
								<?php echo( $aLand ); ?>
							</option>
							<?php
						}
						?>
					</select>
				</td>

				<td>
					Services:
					<select name="service" size="1">
						<?php
						foreach($aServices as $aService)
						{							
                            if( isset($_REQUEST['service']) )
                            {
                                if($_REQUEST['service'] == $aService) $selected = ' selected ';
                            }
							?>
							<option value="<?=$aService; ?>" <?=$selected; ?>>
								<?=$aService; ?>
							</option>
							<?php
						}
						?>
					</select>
				</td>				
				
				<td> &nbsp;&nbsp;&nbsp; <input type="submit" value="start checks" /></td>
			</tr>
		</table>		
	</form>	
	
	<?php
	if( $doTelnetChecksTCAccess === true )
	{
		?>
		<hr />		
		<table>
			<thead>
				<tr>				
					<th>Description</th>
					<th>Server:Port</th>				
					<th>Status</th>		
					<th>Domain</th>
				</tr>
			</thead>
			<tbody>
				<?php
				if( !isset( $_REQUEST['country'] ) ) $_REQUEST['country'] = 'All';				
				if( !isset( $_REQUEST['service'] ) ) $_REQUEST['service'] = 'All';
				
				$country = $_REQUEST['country'];
				$service = $_REQUEST['service'];
				$aConn = Telnetconn::getAllConnTCAccess();				
				foreach( $aConn as $Conn )
				{
					if((preg_match("/$service/", $Conn->m_Description)) || $service=="All")
					{
						if((preg_match("/$country/", $Conn->m_Remark)) || $country=="All")
						{
							$rc = $Conn->checkStatus();
							?>
							<tr>
								<td><?php print $Conn->m_Description; ?></td>
								<td><?php print $Conn->m_Host; ?>:<?php print $Conn->m_Port; ?></td>
								<td align="center">
									<?php
									if( $rc === false )
									{
										?>
										<img alt="<?php print "(".$Conn->m_ErrorNo.") ".$Conn->m_ErrorMessage; ?>" src="not-available.png"/>								
										<?php															
									}
									else 
									{
										?><img alt="Up and Running" src="available.png"/><?php							
									}
									?>
								</td>
								<td><?php print " ".$Conn->m_Remark; ?> &nbsp;</td>						
							</tr>
							<?php
							flush();
						}
					}
				}			
				?>
			</tbody>
		</table>	
		<?php
	}	
	?>		
	
</body>
</html>
