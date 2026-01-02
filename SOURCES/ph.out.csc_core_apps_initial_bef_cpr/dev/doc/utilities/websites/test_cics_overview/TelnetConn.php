<?php

class TelnetConn
{	
	static public function getAllConnTCAccess()
	{
		$retval = array();	
		
		// VSETAS
		$retval[] = new TelnetConn( "10.242.5.212", 3212, "tcAccess", "VSETAS CH 12 Unterentfelden" );	
		$retval[] = new TelnetConn( "10.242.5.212", 3213, "tcAccess", "VSETAS CH 13 Puidoux" );	
		$retval[] = new TelnetConn( "10.242.5.212", 3216, "tcAccess", "VSETAS CH 16 PWS Puidoux" );		
        $retval[] = new TelnetConn( "10.242.5.212", 3261, "tcAccess", "VSETAS AT 61 Wien" );		
        $retval[] = new TelnetConn( "10.242.5.212", 3262, "tcAccess", "VSETAS AT 62 Graz" );	
        $retval[] = new TelnetConn( "10.242.5.212", 3263, "tcAccess", "VSETAS AT 63 Linz" );	
        $retval[] = new TelnetConn( "10.242.5.212", 3264, "tcAccess", "VSETAS AT 64 Tirol" );	
        $retval[] = new TelnetConn( "10.242.5.212", 3283, "tcAccess", "VSETAS AT 83 PWS Wien" );	
        
        // VSETDE
        $retval[] = new TelnetConn( "10.242.5.210", 3205, "tcAccess", "VSETDE DE 05 Fürth" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3206, "tcAccess", "VSETDE DE 06 Berlin" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3208, "tcAccess", "VSETDE DE 08 Münster" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3209, "tcAccess", "VSETDE DE 09 Herne" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3221, "tcAccess", "VSETDE DE 21 Hageda-Stumpf München" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3231, "tcAccess", "VSETDE DE 31 Hamburg" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3233, "tcAccess", "VSETDE DE 33 Oldenburg" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3240, "tcAccess", "VSETDE DE 40 Bielefeld" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3244, "tcAccess", "VSETDE DE 44 Augsburg" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3246, "tcAccess", "VSETDE DE 46 Köln" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3251, "tcAccess", "VSETDE DE 51 Mannheim" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3252, "tcAccess", "VSETDE DE 52 Neuhausen" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3254, "tcAccess", "VSETDE DE 54 Bad Kreuznach" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3256, "tcAccess", "VSETDE DE 56 Hanau" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3257, "tcAccess", "VSETDE DE 57 München" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3258, "tcAccess", "VSETDE DE 58 Freiburg" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3259, "tcAccess", "VSETDE DE 59 Cottbus" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3270, "tcAccess", "VSETDE DE 70 Göttingen" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3278, "tcAccess", "VSETDE DE 78 Hannover" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3281, "tcAccess", "VSETDE DE 81 Leipzig" );	
        $retval[] = new TelnetConn( "10.242.5.210", 3282, "tcAccess", "VSETDE DE 82 Gotha" );	
        
        // VSETOE
        $retval[] = new TelnetConn( "10.242.5.211", 3222, "tcAccess", "VSETOE BG 22 Sofia" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3223, "tcAccess", "VSETOE BG 23 Burgas" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3225, "tcAccess", "VSETOE BG 25 Plovdiv" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3226, "tcAccess", "VSETOE BG 26 Veliko Tarnovo" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3228, "tcAccess", "VSETOE BG 28 ZL Sofia" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3271, "tcAccess", "VSETOE HR 71 Zagreb" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3272, "tcAccess", "VSETOE HR 72 Osijek" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3273, "tcAccess", "VSETOE HR 73 Split" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3274, "tcAccess", "VSETOE HR 74 Rijeka" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3277, "tcAccess", "VSETOE HR 77 Velica Gorica" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3203, "tcAccess", "VSETOE RS 03 Leskovac" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3284, "tcAccess", "VSETOE RS 84 Belgrad" );	        
        $retval[] = new TelnetConn( "10.242.5.211", 3285, "tcAccess", "VSETOE RS 85 Novi Sad" );	    

        // VSETFR
        $retval[] = new TelnetConn( "10.242.5.209", 3217, "tcAccess", "VSETFR FR 17 Veto" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3218, "tcAccess", "VSETFR FR 18 Blois" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3230, "tcAccess", "VSETFR FR 30 Creteil" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3232, "tcAccess", "VSETFR FR 32 Les Mureaux" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3234, "tcAccess", "VSETFR FR 34 St. Aignan" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3236, "tcAccess", "VSETFR FR 36 Toulon" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3237, "tcAccess", "VSETFR FR 37 Puget" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3238, "tcAccess", "VSETFR FR 38 Lille" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3239, "tcAccess", "VSETFR FR 39 Lyon" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3241, "tcAccess", "VSETFR FR 41 St. Etienne" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3242, "tcAccess", "VSETFR FR 42 Niort" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3243, "tcAccess", "VSETFR FR 43 PWS Ivrylab" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3245, "tcAccess", "VSETFR FR 45 Chatellerault" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3247, "tcAccess", "VSETFR FR 47 Creteil Central" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3248, "tcAccess", "VSETFR FR 48 PWS Ris Orangis" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3250, "tcAccess", "VSETFR FR 50 Nancy" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3253, "tcAccess", "VSETFR FR 53 Metz" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3255, "tcAccess", "VSETFR FR 55 Bayonne" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3260, "tcAccess", "VSETFR FR 60 Pau" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3266, "tcAccess", "VSETFR FR 66 Reims" );	        
        $retval[] = new TelnetConn( "10.242.5.209", 3268, "tcAccess", "VSETFR FR 68 Troyes" );	
        $retval[] = new TelnetConn( "10.242.5.209", 3275, "tcAccess", "VSETFR FR 75 Moulins" );	
        $retval[] = new TelnetConn( "10.242.5.209", 3276, "tcAccess", "VSETFR FR 76 Clermont Ferrand" );	
        $retval[] = new TelnetConn( "10.242.5.209", 3280, "tcAccess", "VSETFR FR 80 Auxerre" );	
        $retval[] = new TelnetConn( "10.242.5.209", 3286, "tcAccess", "VSETFR FR 86 Combs-La-Ville" );	
        $retval[] = new TelnetConn( "10.242.5.209", 3287, "tcAccess", "VSETFR FR 87 Toulouse" );	
		
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
