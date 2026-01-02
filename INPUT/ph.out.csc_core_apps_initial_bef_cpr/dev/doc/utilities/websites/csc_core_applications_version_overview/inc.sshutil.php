<?php
set_include_path(__DIR__ . '/phpseclib1.0.15' );
require_once( 'Net/SSH2.php' );

class SSHUtil
{
	private $m_Connection = null;
	private $m_Connected = false;
	private $m_Server = '';
	private $m_Username = '';	
	private $m_Password = '';
    private $m_Port = 22;

	function __construct()
	{
	}
		
	function execute( $command )
	{
		return $this->m_Connection->exec( $command );		
	}
	
	function connect( $server, $username, $password )
	{
		$this->m_Server = trim($server);
		$this->m_Username = $username;
		$this->m_Password = $password;
		
		$this->m_Connected = false;
		$this->m_Connection = new Net_SSH2( $this->m_Server, $this->m_Port );		
		if( !@$this->m_Connection->login( $this->m_Username, $this->m_Password ) )
		{
			$this->m_Connected = false;			
			return false;
		}
		else
		{
			$this->m_Connected = true;			
			return true;
		}			
	}
}
?>