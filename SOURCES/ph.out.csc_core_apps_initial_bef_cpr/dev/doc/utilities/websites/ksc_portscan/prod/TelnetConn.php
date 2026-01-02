<?php

class TelnetConn
{	
	static public function getAllConnTCAccess()
	{
		$retval = array();	
		
		// cscservice
		$retval[] = new TelnetConn( "oat21", 56111, "cscservice", "Austria" );	
		$retval[] = new TelnetConn( "oat21", 56191, "cscservice", "Austria PWS" );	
		$retval[] = new TelnetConn( "obg21", 56161, "cscservice", "Bulgaria" );	
		$retval[] = new TelnetConn( "och21", 56101, "cscservice", "Switzerland" );	
		$retval[] = new TelnetConn( "och21", 56141, "cscservice", "Switzerland PWS" );	
		$retval[] = new TelnetConn( "ode21", 56001, "cscservice", "Germany" );			
		$retval[] = new TelnetConn( "ode23", 56001, "cscservice", "Germany ProductAvailability" );					
		$retval[] = new TelnetConn( "ode24", 56001, "cscservice", "Germany ProductAvailability" );					
		$retval[] = new TelnetConn( "ofr21", 56121, "cscservice", "France" );	
		$retval[] = new TelnetConn( "ofr21", 56131, "cscservice", "France PWS" );	
		$retval[] = new TelnetConn( "ohr21", 56201, "cscservice", "Croatia" );	
		$retval[] = new TelnetConn( "ors21", 56171, "cscservice", "Serbia" );	

		// kscserver
		$retval[] = new TelnetConn( "oat21", 56630, "kscserver", "Austria" );	
		$retval[] = new TelnetConn( "oat21", 56655, "kscserver", "Austria PWS" );			
		$retval[] = new TelnetConn( "obg21", 56640, "kscserver", "Bulgaria" );	
		$retval[] = new TelnetConn( "och21", 56615, "kscserver", "Switzerland" );	
		$retval[] = new TelnetConn( "och21", 56620, "kscserver", "Switzerland PWS" );	
		$retval[] = new TelnetConn( "ode21", 56600, "kscserver", "Germany" );			
		$retval[] = new TelnetConn( "ode23", 56600, "kscserverLN", "Germany ProductAvailability" );	
		$retval[] = new TelnetConn( "ode23", 56660, "kscserverXmlNord", "Germany Bulk-ProductAvailability" );					
		$retval[] = new TelnetConn( "ode24", 56600, "kscserverLN", "Germany ProductAvailability" );	
		$retval[] = new TelnetConn( "ode24", 56660, "kscserverXmlNord", "Germany Bulk-ProductAvailability" );	

		$retval[] = new TelnetConn( "ofr21", 56605, "kscserver", "France" );	
		$retval[] = new TelnetConn( "ofr21", 56610, "kscserver", "France PWS" );	
		$retval[] = new TelnetConn( "ohr21", 56625, "kscserver", "Croatia" );	
		$retval[] = new TelnetConn( "ors21", 56645, "kscserver", "Serbia" );	
		
		// zaapunix
		$retval[] = new TelnetConn( "oat21", 56113, "zaapunix", "Austria" );					
		$retval[] = new TelnetConn( "oat21", 56193, "zaapunix", "Austria PWS" );	
		$retval[] = new TelnetConn( "obg21", 56163, "zaapunix", "Bulgaria" );		
		$retval[] = new TelnetConn( "och21", 56103, "zaapunix", "Switzerland" );		
		$retval[] = new TelnetConn( "och21", 56143, "zaapunix", "Switzerland PWS" );		
		$retval[] = new TelnetConn( "ode21", 56003, "zaapunix", "Germany" );		
		$retval[] = new TelnetConn( "ofr21", 56123, "zaapunix", "France" );		
		$retval[] = new TelnetConn( "ofr21", 56133, "zaapunix", "France PWS" );		
		$retval[] = new TelnetConn( "ohr21", 56203, "zaapunix", "Croatia" );		
		$retval[] = new TelnetConn( "ors21", 56173, "zaapunix", "Serbia" );		

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
