<?php
class CSCCommands
{
	private $m_XMLPath = '';
	private $m_XMLDoc = null;
	private $m_Commands = array();
		
	function __construct( $xmlpath )
	{
		$this->m_XMLPath = $xmlpath;		
		$this->m_XMLDoc = new DOMDocument();
	}
	
	function getCommand( $identifier )
	{
		return $this->m_Commands[$identifier];
	}
	
	function loadXML()
	{
		$this->m_XMLDoc->loadXML( file_get_contents( $this->m_XMLPath ) );		
		foreach( $this->m_XMLDoc->getElementsByTagName( "Command" ) as $cmd )
		{		
			$identifier = '';
			$cmdpath = '';
			$command = '';						
			foreach( $cmd->attributes as $a )
			{			
				switch( $a->nodeName )
				{
					case 'Identifier': $identifier = $a->nodeValue; break;
					case 'CommandPath': $cmdpath = $a->nodeValue; break;
					case 'Command': $command = $a->nodeValue; break;					
					default: break;
				}				
			}
			
			$csccommand = new CSCCommand( $identifier, $cmdpath, $command );
			$this->m_Commands[$identifier] = $csccommand;			
		}
	}
}

class CSCCommand
{
	private $m_Identifier = '';
	private $m_CommandPath = '';
	private $m_Command = '';
	
	function replaceCountryAndBranch( $country, $branch, $val )
	{
		return str_replace( '[?F]', $branch, str_replace( '[?C]', $country, $val ) );
	}
	
	function __construct( $identifier, $cmdpath, $cmd )
	{
		$this->m_Identifier = $identifier;
		$this->m_CommandPath = $cmdpath;
		$this->m_Command = $cmd;			
	}	
	
	function getIdentifier()
	{
		return $this->m_Identifier;
	}
	
	function getCommandPath()
	{
		return $this->m_CommandPath;
	}
	
	function getCommand()
	{
		return $this->m_Command;
	}
	
}
?>