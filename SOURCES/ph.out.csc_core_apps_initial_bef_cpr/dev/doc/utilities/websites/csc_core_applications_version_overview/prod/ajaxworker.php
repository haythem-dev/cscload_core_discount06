<?php
require_once("../default_header.php");
@ini_set( "error_log", date("Ymd")."ajaxworker.log" );

require_once( '../inc.sshutil.php' );
require_once( '../inc.cscprocesses.php' );
require_once( '../inc.csccommands.php' );
require_once( '../inc.vpVersionInfoParser.php' );

$objCSCProcesses = new CSCProcesses( 'CSCProcesses.xml' );
$objCSCProcesses->loadXML();

$objCommands = new CSCCommands( 'CSCCommands.xml' );
$objCommands->loadXML();

$COUNTRY = $_REQUEST['ReqCountry'];
		
$currentcountry = null;			
while( false != ($currentcountry = $objCSCProcesses->getCountryFromList()) )
{
	if( $COUNTRY != $currentcountry->getName() )
	{
		continue;
	}
	else
	{		
		if( $COUNTRY == "deXML" ){ $COUNTRY = "de"; }
		if( $COUNTRY == "deXML2" ){ $COUNTRY = "de"; }
        if( $COUNTRY == "deXML3" ){ $COUNTRY = "de"; }
        if( $COUNTRY == "deXML4" ){ $COUNTRY = "de"; }
        if( $COUNTRY == "deXML5" ){ $COUNTRY = "de"; }
		$objSSHUtil = new SSHUtil();						
		$connected = $objSSHUtil->connect( $currentcountry->getServerName(), $currentcountry->getUserName(), $currentcountry->getPassword() );
		if( true != $connected )
		{
			print "connection failed";			
		}
		else
		{
					$proc = null;
					$headerprinted = false;
					while( false != ($proc = $currentcountry->getProcessFromList() ) )
					{
						if( !$headerprinted )
						{
							$headerprinted = true;
							?>		
							<table width="100%">
								<thead>		
									<tr>
										<th width="40px" >Ctry</th>
										<th width="50px" >Server</th>
										<th width="150px">Program</th>													
										<th>Version</th>														
										<th>Date</th>
										<th>Revision</th>										
										<th>URL</th>
									</tr>
								</thead>
								<tbody>		
							<?php						
						}
					
						$csccommand = $objCommands->getCommand( $proc->getCommandIdentifier() );
						$branches = array( '' );
						if( $proc->isBranchSpecific() )
						{
							$branches = $proc->getBranches();
						}
						
						$version  = ""; $versiontemplate  = "Version: @(#)"; 
						$revision = "";	$revisiontemplate = "Revision: ";
						$date     = ""; $datetemplate     = "Date: ";
						$time     = ""; $timetemplate     = "Time: ";
						$svnurl   = ""; $svnurltemplate   = "URL: ";
						$content = "";
						foreach( $branches as $b )
						{
							$execcommand = $csccommand->replaceCountryAndBranch( $COUNTRY, $b, $csccommand->getCommandPath().$csccommand->getCommand() );							
							$result = $objSSHUtil->execute( $execcommand );							
							$ainfo = parseVersionInfos($result);
							if( isset( $ainfo['version']  ) ) $version  = $ainfo['version'];
							if( isset( $ainfo['revision'] ) ) $revision = $ainfo['revision'];
							if( isset( $ainfo['date']     ) ) $date     = $ainfo['date'];
							if( isset( $ainfo['time']     ) ) $time     = $ainfo['time'];
							if( isset( $ainfo['url']      ) ) $svnurl   = $ainfo['url'];																																
						}						
						if( strlen(trim($svnurl)) == 0 )
						{
							$svnurl = $content;
						}
						?>						
						<tr>
							<td valign="top"><?php print $COUNTRY; ?></td>
							<td valign="top"><?php print $currentcountry->getServerName(); ?></td> 								
							<td valign="top"><?php print $proc->getCommandIdentifier(); ?></td>
							<td valign="top" align="right"><?php print trim($version); ?>&nbsp; &nbsp;</td>							
							<td valign="top" align="center"><?php print trim($date." ".$time); ?></td>
							<td valign="top" align="center"><?php print trim($revision); ?></td>
							<td valign="top"><?php print trim($svnurl); ?></td>
						</tr>						
						<?php							
					}
					?>
					</tbody></table>
					<?php											
		}
	}
}
?>
