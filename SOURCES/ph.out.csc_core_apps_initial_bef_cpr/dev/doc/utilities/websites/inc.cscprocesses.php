<?php
class CSCProcesses
{
	private $m_XMLPath = '';
	private $m_XMLDoc = null;
	private $m_Countries = array();
		
	function __construct( $xmlpath )
	{
		$this->m_XMLPath = $xmlpath;		
		$this->m_XMLDoc = new DOMDocument();
	}
	
	function getCountryFromList()
	{
		$retval = false;
		foreach( $this->m_Countries as $key => $value )
		{
			$retval = $value;
			unset( $this->m_Countries[$key] );
			break;
		}
		return $retval;
	}
	
	function loadXML()
	{
		$this->m_XMLDoc->loadXML( file_get_contents( $this->m_XMLPath ) );		
		foreach( $this->m_XMLDoc->getElementsByTagName( "Country" ) as $ctry )
		{
			$shortname = '';
			$servername = '';
			$username = '';			
			$password = '';
			foreach( $ctry->attributes as $a )
			{			
				switch( $a->nodeName )
				{
					case 'ShortName': $shortname = $a->nodeValue; break;
					case 'ServerName': $servername = $a->nodeValue; break;
					case 'UserName': $username = $a->nodeValue; break;
					case 'Password': $password = $a->nodeValue; break;
					default: break;
				}				
			}
		
			$country = new CSCCountry( $shortname, $servername, $username, $password );			
			
			foreach( $ctry->getElementsByTagName( "Process" ) as $proc )
			{
				$cmdid = '';				
				$branchlist = '';
				foreach( $proc->attributes as $a )
				{
					switch( $a->nodeName )
					{
						case 'CommandIdentifier': $cmdid = $a->nodeValue; break;						
						case 'BranchList': $branchlist = $a->nodeValue; break;
						default: break;
					}
				}
				$country->addProcess( new CSCProcess( $cmdid, $branchlist ) );
			}					
			
			$this->m_Countries[] = $country;
		}
	}
}

class CSCCountry
{
	private $m_ShortName = '';
	private $m_ServerName = '';
	private $m_UserName = '';
	private $m_Password = '';
	private $m_Processes = null;	
	
	function __construct( $shortname, $servername, $username, $password )
	{
		$this->m_ShortName = $shortname;
		$this->m_ServerName = $servername;
		$this->m_UserName = $username;
		$this->m_Password = $password;
		$this->m_Processes = array();
	}
	
	function addProcess( $cscprocess )
	{
		$this->m_Processes[] = $cscprocess;
	}
	
	function getName()
	{
		return $this->m_ShortName;
	}
	
	function getServerName()
	{
		return $this->m_ServerName;
	}
	
	function getUserName()
	{
		return $this->m_UserName;
	}
	
	function getPassword()
	{
		return $this->m_Password;
	}
	
	function getProcessFromList()
	{
		$retval = false;
		foreach( $this->m_Processes as $key => $value )
		{
			$retval = $value;
			unset( $this->m_Processes[$key] );
			break;
		}
		return $retval;
	}
}

class CSCProcess
{
	private $m_CommandIdentifier = '';	
	private $m_BranchList = array();
	
	function __construct( $cmdid, $branches )
	{
		$this->m_CommandIdentifier = $cmdid;		
		if( strlen( trim( $branches ) ) > 0 )
		{
			$this->m_BranchList = explode( ';', $branches );
		}
	}
	
	function getCommandIdentifier()
	{
		return $this->m_CommandIdentifier;
	}
	
	function isBranchSpecific()
	{
		if( is_array( $this->m_BranchList ) )
		{
			if( sizeof( $this->m_BranchList ) > 0 )
			{
				return true;
			}
		}
		return false;
	}
	
	function getBranches()
	{
		return $this->m_BranchList;
	}
}

?>