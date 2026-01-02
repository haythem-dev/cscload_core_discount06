<?php

class TelnetConn
{	
	static public function getAllConnTCAccess()
	{
		$retval = array();	
		
		// cscservice				
        $retval[] = new TelnetConn( "ode23", 56670, "cscservice70", "Germany ProductAvailability" );					
        $retval[] = new TelnetConn( "ode23", 56671, "cscservice71", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode23", 56672, "cscservice72", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode23", 56673, "cscservice73", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode23", 56674, "cscservice74", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode23", 56675, "cscservice75", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode23", 56676, "cscservice76", "Germany ProductAvailability" );               
        $retval[] = new TelnetConn( "ode23", 56677, "cscservice77", "Germany ProductAvailability" );
        								
        $retval[] = new TelnetConn( "ode24", 56670, "cscservice70", "Germany ProductAvailability" );					
        $retval[] = new TelnetConn( "ode24", 56671, "cscservice71", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode24", 56672, "cscservice72", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode24", 56673, "cscservice73", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode24", 56674, "cscservice74", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode24", 56675, "cscservice75", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode24", 56676, "cscservice76", "Germany ProductAvailability" );               
        $retval[] = new TelnetConn( "ode24", 56677, "cscservice77", "Germany ProductAvailability" );        
        					
        $retval[] = new TelnetConn( "ode25", 56670, "cscservice70", "Germany ProductAvailability" );					
        $retval[] = new TelnetConn( "ode25", 56671, "cscservice71", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode25", 56672, "cscservice72", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode25", 56673, "cscservice73", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode25", 56674, "cscservice74", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode25", 56675, "cscservice75", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode25", 56676, "cscservice76", "Germany ProductAvailability" );               
        $retval[] = new TelnetConn( "ode25", 56677, "cscservice77", "Germany ProductAvailability" );        

        $retval[] = new TelnetConn( "ode26", 56670, "cscservice70", "Germany ProductAvailability" );					
        $retval[] = new TelnetConn( "ode26", 56671, "cscservice71", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode26", 56672, "cscservice72", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode26", 56673, "cscservice73", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode26", 56674, "cscservice74", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode26", 56675, "cscservice75", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode26", 56676, "cscservice76", "Germany ProductAvailability" );               
        $retval[] = new TelnetConn( "ode26", 56677, "cscservice77", "Germany ProductAvailability" );

        $retval[] = new TelnetConn( "ode27", 56670, "cscservice70", "Germany ProductAvailability" );					
        $retval[] = new TelnetConn( "ode27", 56671, "cscservice71", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode27", 56672, "cscservice72", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode27", 56673, "cscservice73", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode27", 56674, "cscservice74", "Germany ProductAvailability" );        
        $retval[] = new TelnetConn( "ode27", 56675, "cscservice75", "Germany ProductAvailability" );
        $retval[] = new TelnetConn( "ode27", 56676, "cscservice76", "Germany ProductAvailability" );               
        $retval[] = new TelnetConn( "ode27", 56677, "cscservice77", "Germany ProductAvailability" );

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
