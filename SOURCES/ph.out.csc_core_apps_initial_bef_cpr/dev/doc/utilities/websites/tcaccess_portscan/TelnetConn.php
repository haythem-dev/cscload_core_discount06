<?php

class TelnetConn
{	
	static public function getAllConnTCAccess()
	{
		$retval = array();	
		
		// Austria
		$retval[] = new TelnetConn( "129.210.15.61", 3161, "tcAccess Austria", "61 Wien" );	
		$retval[] = new TelnetConn( "129.210.15.61", 3162, "tcAccess Austria", "62 Graz" );	
		$retval[] = new TelnetConn( "129.210.15.61", 3163, "tcAccess Austria", "63 Linz" );	
		$retval[] = new TelnetConn( "129.210.15.61", 3169, "tcAccess Austria", "64 Tirol / Jenbach" );	
		$retval[] = new TelnetConn( "129.210.15.61", 3183, "tcAccess Austria", "83 Prewholesale" );	
		
		// Bulgaria
		$retval[] = new TelnetConn( "129.210.15.22", 3122, "tcAccess Bulgaria", "22 Sofia" );	
		$retval[] = new TelnetConn( "129.210.15.22", 3123, "tcAccess Bulgaria", "23 Burgas" );			
		$retval[] = new TelnetConn( "129.210.15.22", 3125, "tcAccess Bulgaria", "25 Plovdiv" );	
		$retval[] = new TelnetConn( "129.210.15.22", 3126, "tcAccess Bulgaria", "26 Veliko Tarnovo" );	
		$retval[] = new TelnetConn( "129.210.15.22", 3128, "tcAccess Bulgaria", "28 Sofia Zentrallager" );	
		
		// Croatia
		$retval[] = new TelnetConn( "129.210.15.71", 3171, "tcAccess Croatia", "71 Zagreb" );	
		$retval[] = new TelnetConn( "129.210.15.71", 3172, "tcAccess Croatia", "72 Osijek" );	
		$retval[] = new TelnetConn( "129.210.15.71", 3173, "tcAccess Croatia", "73 Split / Solin" );	
		$retval[] = new TelnetConn( "129.210.15.71", 3174, "tcAccess Croatia", "74 Rijeka" );	
		$retval[] = new TelnetConn( "129.210.15.71", 3177, "tcAccess Croatia", "77 Velica Gorica" );	
		
		// France
		$retval[] = new TelnetConn( "10.242.5.45", 3117, "tcAccess France", "17 Troyes Veto" );	
		$retval[] = new TelnetConn( "10.242.5.45", 3118, "tcAccess France", "18 Blois" );	
		$retval[] = new TelnetConn( "129.210.15.30", 3130, "tcAccess France", "30 Creteil" );	
		$retval[] = new TelnetConn( "129.210.15.30", 3132, "tcAccess France", "32 Les Mureaux" );	
		$retval[] = new TelnetConn( "129.210.15.30", 3134, "tcAccess France", "34 St. Aignan" );			
		$retval[] = new TelnetConn( "129.210.15.36", 3136, "tcAccess France", "36 Toulon / Ollioules" );	
		$retval[] = new TelnetConn( "129.210.15.36", 3137, "tcAccess France", "37 Puget" );	
		$retval[] = new TelnetConn( "129.210.15.30", 3138, "tcAccess France", "38 Lille" );	
		$retval[] = new TelnetConn( "129.210.15.36", 3139, "tcAccess France", "39 Lyon" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3141, "tcAccess France", "41 St. Etienne" );	
		$retval[] = new TelnetConn( "10.242.5.45", 3142, "tcAccess France", "42 Niort" );	
		$retval[] = new TelnetConn( "129.210.15.36", 3143, "tcAccess France", "43 Prewholesale Ivry Lab" );	
		$retval[] = new TelnetConn( "10.242.5.45", 3145, "tcAccess France", "45 Chatellerault" );	
		$retval[] = new TelnetConn( "129.210.15.36", 3147, "tcAccess France", "47 Creteil Depot Centrale" );	
		$retval[] = new TelnetConn( "129.210.15.36", 3148, "tcAccess France", "48 Prewholesale Ris Orangis" );	
		$retval[] = new TelnetConn( "10.242.5.80", 3150, "tcAccess France", "50 Nancy" );	
		$retval[] = new TelnetConn( "10.242.5.80", 3153, "tcAccess France", "53 Metz" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3155, "tcAccess France", "55 Bayonne" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3160, "tcAccess France", "60 Pau" );	
		$retval[] = new TelnetConn( "10.242.5.80", 3166, "tcAccess France", "66 Reims" );	
		$retval[] = new TelnetConn( "10.242.5.45", 3168, "tcAccess France", "68 Troyes" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3175, "tcAccess France", "75 Moulins" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3176, "tcAccess France", "76 Clermt. Ferrand" );	
		$retval[] = new TelnetConn( "10.242.5.80", 3180, "tcAccess France", "80 Auxerre" );	
		$retval[] = new TelnetConn( "129.210.15.30", 3186, "tcAccess France", "86 Combs La Ville" );	
		$retval[] = new TelnetConn( "10.242.5.60", 3187, "tcAccess France", "87 Toulouse" );	
		
		// Germany
		$retval[] = new TelnetConn( "129.210.15.5", 3105, "tcAccess Germany", "05 F&uuml;rth" );	
		$retval[] = new TelnetConn( "129.210.15.6", 3106, "tcAccess Germany", "06 Berlin" );	
		$retval[] = new TelnetConn( "129.210.15.9", 3108, "tcAccess Germany", "08 M&uuml;nster" );	
		$retval[] = new TelnetConn( "129.210.15.9", 3109, "tcAccess Germany", "09 Herne" );	
		$retval[] = new TelnetConn( "129.210.15.21", 3121, "tcAccess Germany", "21 Hageda-Stumpf M&uuml;nchen" );	
		$retval[] = new TelnetConn( "129.210.15.31", 3131, "tcAccess Germany", "31 Hamburg" );	
		$retval[] = new TelnetConn( "129.210.15.33", 3133, "tcAccess Germany", "33 Oldenburg" );	
		$retval[] = new TelnetConn( "129.210.15.40", 3140, "tcAccess Germany", "40 Bielefeld" );	
		$retval[] = new TelnetConn( "129.210.15.44", 3144, "tcAccess Germany", "44 Augsburg" );	
		$retval[] = new TelnetConn( "129.210.15.46", 3146, "tcAccess Germany", "46 K&ouml;ln" );	
		$retval[] = new TelnetConn( "129.210.15.51", 3151, "tcAccess Germany", "51 Mannheim" );	
		$retval[] = new TelnetConn( "129.210.15.52", 3152, "tcAccess Germany", "52 Neuhausen" );	
		$retval[] = new TelnetConn( "129.210.15.54", 3154, "tcAccess Germany", "54 Bad Kreuznach" );	
		$retval[] = new TelnetConn( "129.210.15.56", 3156, "tcAccess Germany", "56 Hanau" );	
		$retval[] = new TelnetConn( "129.210.15.57", 3157, "tcAccess Germany", "57 M&uuml;nchen" );	
		$retval[] = new TelnetConn( "129.210.15.58", 3158, "tcAccess Germany", "58 Freiburg" );	
		$retval[] = new TelnetConn( "129.210.15.59", 3159, "tcAccess Germany", "59 Cottbus" );	
		$retval[] = new TelnetConn( "129.210.15.70", 3170, "tcAccess Germany", "70 G&ouml;ttingen" );	
		$retval[] = new TelnetConn( "129.210.15.78", 3178, "tcAccess Germany", "78 Hannover" );	
		$retval[] = new TelnetConn( "129.210.15.81", 3181, "tcAccess Germany", "81 Leipzig" );	
		$retval[] = new TelnetConn( "129.210.15.81", 3182, "tcAccess Germany", "82 Gotha" );	
		
		// Serbia
		$retval[] = new TelnetConn( "129.210.15.84", 3103, "tcAccess Serbia", "03 Leskovac" );	
		$retval[] = new TelnetConn( "129.210.15.84", 3184, "tcAccess Serbia", "84 Belgrad" );	
		$retval[] = new TelnetConn( "129.210.15.84", 3185, "tcAccess Serbia", "85 Novi Sad" );	
		
		// Switzerland
		$retval[] = new TelnetConn( "129.210.15.12", 3112, "tcAccess Switzerland", "12 Unterentfelden" );	
		$retval[] = new TelnetConn( "129.210.15.12", 3113, "tcAccess Switzerland", "13 Puidoux" );	
		$retval[] = new TelnetConn( "129.210.15.12", 3116, "tcAccess Switzerland", "16 Prewholesale" );	
		
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
