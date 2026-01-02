<?php

class TelnetConn
{	
	static public function getAllConnTCAccess()
	{
		$retval = array();	
		
		// cscservice
		$retval[] = new TelnetConn( "zqas21", 56111, "cscservice", "Austria" );	
		$retval[] = new TelnetConn( "zqas21", 56191, "cscservice", "Austria PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56161, "cscservice", "Bulgaria" );	
		$retval[] = new TelnetConn( "zqas21", 56101, "cscservice", "Switzerland" );	
		$retval[] = new TelnetConn( "zqas21", 56141, "cscservice", "Switzerland PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56001, "cscservice", "Germany" );			
		$retval[] = new TelnetConn( "zqas21", 56121, "cscservice", "France" );	
		$retval[] = new TelnetConn( "zqas21", 56131, "cscservice", "France PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56201, "cscservice", "Croatia" );	
		$retval[] = new TelnetConn( "zqas21", 56171, "cscservice", "Serbia" );	
		
		// kscserver
		$retval[] = new TelnetConn( "zqas21", 56630, "kscserver", "Austria" );	
		$retval[] = new TelnetConn( "zqas21", 56655, "kscserver", "Austria PWS" );			
		$retval[] = new TelnetConn( "zqas21", 56640, "kscserver", "Bulgaria" );	
		$retval[] = new TelnetConn( "zqas21", 56615, "kscserver", "Switzerland" );	
		$retval[] = new TelnetConn( "zqas21", 56620, "kscserver", "Switzerland PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56600, "kscserver", "Germany" );			
		$retval[] = new TelnetConn( "zqas21", 56605, "kscserver", "France" );	
		$retval[] = new TelnetConn( "zqas21", 56610, "kscserver", "France PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56625, "kscserver", "Croatia" );	
		$retval[] = new TelnetConn( "zqas21", 56645, "kscserver", "Serbia" );			
		
		// zaapunix
		$retval[] = new TelnetConn( "zqas21", 56113, "zaapunix", "Austria" );					
		$retval[] = new TelnetConn( "zqas21", 56193, "zaapunix", "Austria PWS" );	
		$retval[] = new TelnetConn( "zqas21", 56163, "zaapunix", "Bulgaria" );		
		$retval[] = new TelnetConn( "zqas21", 56103, "zaapunix", "Switzerland" );		
		$retval[] = new TelnetConn( "zqas21", 56143, "zaapunix", "Switzerland PWS" );		
		$retval[] = new TelnetConn( "zqas21", 56003, "zaapunix", "Germany" );				
		$retval[] = new TelnetConn( "zqas21", 56123, "zaapunix", "France" );		
		$retval[] = new TelnetConn( "zqas21", 56133, "zaapunix", "France PWS" );		
		$retval[] = new TelnetConn( "zqas21", 56203, "zaapunix", "Croatia" );		
		$retval[] = new TelnetConn( "zqas21", 56173, "zaapunix", "Serbia" );		

		return $retval;
	}
	
	public $m_Host = "";
	public $m_Port = "";	
	public $m_Description = "";
	public $m_Remark = "";
	public $m_ErrorNo = 0;
	public $m_ErrorMessage = "";
	
	public function __construct( $Host, $Port, $Description, $Remark=""  )
	{
		$this->m_Description = $Description;
		$this->m_Host = $Host;
		$this->m_Port = $Port;
		$this->m_Remark = $Remark;
	}
	
	public function checkStatus()
	{
		$conn = @fsockopen( $this->m_Host, $this->m_Port, $this->m_ErrorNo, $this->m_ErrorMessage, 5 );
		if( !$conn )
		{
			return false;
		}
		else 
		{
			@fclose( $conn );
			return true;
		}
	}
}

?>
