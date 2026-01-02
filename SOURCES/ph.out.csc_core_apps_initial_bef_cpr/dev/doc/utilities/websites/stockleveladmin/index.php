<?php
require_once("../inc.sshutil.php");
?>
<html>
	<head>
		<title>Stocklevel Germany Administration</title>
		<link rel="stylesheet" type="text/css" href="style.css"/>
		<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
		<META HTTP-EQUIV="Expires" CONTENT="-1">
		<?php
		$BranchNo = '';		
		if( isset( $_REQUEST['fBranchNo'] ) ) $BranchNo = $_REQUEST['fBranchNo'];
		$CustomerNo = '';
		if( isset( $_REQUEST['fCustomerNo'] ) ) $CustomerNo = $_REQUEST['fCustomerNo'];
		$obj = new StocklevelAdmin();
		
		$User = strtolower($_SERVER['AUTH_USER']);				
		?>
	</head>
	<body>		
		<h1>Stocklevel Germany Administration</h1>
		<?php
		if(    $User != 'phoenix\steffen.heinlein' 
			&& $User != 'phoenix\thomas.hoerath'
			&& $User != 'phoenix\andre.egerer'			
			&& $User != 'phoenix\harald.schilling'			
			&& $User != 'phoenix\herbert.knoechel'			
			&& $User != 'phoenix\hubert.luebke'			
			&& $User != 'phoenix\juergen.bogendoerfer'			
			&& $User != 'phoenix\matthias.backmeroff'			
			&& $User != 'phoenix\rudi.griesshammer'			
			&& $User != 'phoenix\sascha.weiss'			
			&& $User != 'phoenix\stefan.brief'						
			&& $User != 'phoenix\michael.poesdorf'			
			&& $User != 'phoenix\sebastian.truebe'		
			&& $User != 'phoenix\charly.tchaptchet'
			&& $User != 'phoenix\christian.woehrle'
		  )
		{
			?>
			<h2>You are not authorised to use this function.</h2>			
			<?php
			die();
		}
		?>
		<table>
			<thead>
				<tr>
					<th colspan='5'>Install Stocklevel Interface for customer</th>
				</tr>
			</thead>
			<tbody>
				<form name="stockleveladmin" action="<?php print $_SERVER['PHP_SELF'] ?>" method="POST">	    
				<tr>
					<td>BranchNo:</td>
					<td><input type="text" name="fBranchNo" size="1" value="<?php print $BranchNo; ?>" /></td>
					<td>CustomerNo:</td>
					<td><input type="text" name="fCustomerNo" size="5" value="<?php print $CustomerNo; ?>" /></td>
					<td><input type="submit" name="fSubmit" value="OK" /></td>
				</tr>
				</form>
			</tbody>
			<tfoot>
				<tr>
					<td colspan='5'>
						<pre>
						<?php						
						if( isset( $_REQUEST['fSubmit'] ) )
						{							
							$obj->installStocklevel( $BranchNo, $CustomerNo );							
						}
						?>
						</pre>
					</td>
				</tr>
			</tfoot>
		</table>				        
		<table>
			<thead>
				<tr>
					<th colspan='2'>Already Installed</th>
				</tr>
				<tr>
					<th>BranchNo</th>
					<th>CustomerNo</th>
				</tr>
			</thead>
			<tbody>
				<?php
				$obj->getInstalledCustomers(6);
				$lines = explode( "\n", $obj->m_Message );
				foreach( $lines as $line )
				{
					while( strstr( $line, "  " ) )
					{
						$line = str_replace( "  ", " ", $line );
					}
					$cols = explode( " ", $line );
					if( isset( $cols[8] ) )
					{
						$it = trim($cols[8]);
						$it = str_replace( "/software/wss/de/ksc/load/data/input/stocklevel-", "", $it );
						$it = str_replace( ".info", "", $it );												
						$details = explode( "-", $it );
						?>
						<tr>
							<td><?php print $details[0]; ?></td>
							<td><?php print $details[1]; ?></td>
						</tr>
						<?php
					}
				}
				?>				
			</tbody>			
		</table>
	</body>
</html>


<?php

class StocklevelAdmin
{
	public  $m_Message     = '';
	public	$m_LastCommand = '';
	public  $m_Server      = 'ode21';
	private $m_Username    = 'salesweb';
	private $m_Password    = 'xmlxml!';
	private $m_SSH         = null;    
	
    private function connectSSH()
    {
        
        $this->m_SSH = new SSHUtil();
        $connected = $this->m_SSH->connect( $this->m_Server, $this->m_Username, $this->m_Password );
        if( true != $connected )            
		{		
			$this->m_Message = "Login failed.";
			return false;
		}        
        return true;
    }
    
	public function getInstalledCustomers($branchno)
	{				
        if( false == $this->connectSSH() )
        {
            return false;
        }					        			
		$this->m_LastCommand = "ls -l /software/wss/de/ksc/load/data/input/stocklevel-*-*.info";              
		$this->m_Message = $this->m_SSH->execute($this->m_LastCommand);		
        return true;
	}
	
	public function installStocklevel( $branchno, $customerno )	
	{	
		$branchno = $branchno;	
		$customerno = $customerno;
		if( $customerno < 0 || $customerno > 9999999 )
		{
			$this->m_Message = "Invalid customer no.!";
			return;		
		}
        
        if( false == $this->connectSSH() )
        {
            return false;
        }					         							
		$this->m_LastCommand = "touch /software/wss/de/ksc/load/data/input/stocklevel-".$branchno."-".$customerno.".info";
		$this->m_Message = $this->m_SSH->execute( $this->m_LastCommand );					
        return true;		
	}

	private function checkCustomer( $branchno, $customerno )
	{
            $strDBServer = $this->getServer($branchno)."_tcp";
            $strDBHost   = $this->getServer($branchno);
            $strDB       = $this->getServer($branchno);
            $strDBUser   = "salesweb";
            $strDBPass   = "xmlxml!";
						
            $ifx = ifx_connect( "$strDB@$strDBServer", $strDBUser, $strDBPass );			
			if( !$ifx )
			{
				$this->m_Message = "Connection to Informix DB failed.";
				return false;
			}
			
			$query = "SELECT idfnr FROM kunde WHERE filialnr=$branchno and idfnr=$customerno;";
			$result = ifx_query( $query, $ifx );
			$retval = false;
			while( $row = ifx_fetch_row( $result, "NEXT" ) )
			{
				$retval = true;
				break;
			}						
			ifx_close( $ifx );			
			return $retval;
	}
};

?>