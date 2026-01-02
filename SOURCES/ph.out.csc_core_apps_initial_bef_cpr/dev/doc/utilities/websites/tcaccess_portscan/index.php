<html>

<head>
	<title>tcAccess Portscan</title>
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
	
	$doTelnetChecksTCAccess = true; $checkTelnetChecksTCAccess=" checked "; 
	?>
</head>

<body>
	<h1>tcAccess Portscan</h1>
	<form action="<?php print $_SERVER['PHP_SELF']; ?>" method="POST">
		<table>
			<tr>
				<td>
					<select name="country" size="1">
						<?php
						foreach($aCountry as $aLand)
						{
							$selected="";
                            if( isset($_REQUEST['country']) )
                            {
                                if($_REQUEST['country'] == $aLand) $selected = ' selected ';
                            }
							?>
							<option value="<?=$aLand; ?>" <?=$selected; ?>>
								<?=$aLand; ?>
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
		<h2>TCAccess</h2>	
		<table>
			<thead>
				<tr>				
					<th>Description</th>
					<th>Host:Port</th>				
					<th>Status</th>		
					<th>Branch</th>
				</tr>
			</thead>
			<tbody>
				<?php
				if( !isset( $_REQUEST['country'] ) )
				{
					$_REQUEST['country'] = 'All';
				}
				$country=$_REQUEST['country'];
				$aConn = Telnetconn::getAllConnTCAccess();				
				foreach( $aConn as $Conn )
				{
					if((preg_match("/$country/", $Conn->m_Description)) || $country=="All")
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
									?><img alt="OK" src="available.png"/><?php							
								}
								?>
							</td>
							<td><?php print " ".$Conn->m_Remark; ?> &nbsp;</td>						
						</tr>
						<?php
						flush();
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
