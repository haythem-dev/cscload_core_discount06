<?

class LogSettings
{	
	public static $User = '';
	public static $Password = '';
	public static $URI = '';
	
	public static $Servers = array();
	public static $LogDatabases = array();
	public static $Branches = array();
	
	public static function loadSettings( $Path2SettingsXML )
	{
		LogSettings::$User = '';
		LogSettings::$Password = '';
		LogSettings::$URI = '';
		LogSettings::$Servers = array();
		LogSettings::$LogDatabases = array();
		LogSettings::$Branches = array();
		
		$DomDocument = new DOMDocument();
		$DomDocument->loadXML( file_get_contents( $Path2SettingsXML ) );
		$Root = $DomDocument->documentElement;
		
		// get logservice attributes
			$Items = $Root->getElementsByTagName('logservice');
			foreach( $Items as $logservice )	
			{
				foreach( $logservice->attributes as $attribute )
				{
					switch( $attribute->nodeName )
					{
						case "user":
							LogSettings::$User = $attribute->nodeValue;
							break;
						case "password":
							LogSettings::$Password = $attribute->nodeValue;
							break;
						case "uri":
							LogSettings::$URI = $attribute->nodeValue;
							break;
						default:
							break;
					}
				}
			}
			unset($Items);
		
		// get server
			$ServerLists = $Root->getElementsByTagName('serverlist');
			foreach( $ServerLists as $ServerList )
			{
				$Items = $ServerList->getElementsByTagName('server');
				foreach( $Items as $server )
				{				
					$a = array();
					foreach( $server->attributes as $attribute ) $a[$attribute->nodeName] = $attribute->nodeValue;
					LogSettings::$Servers[] = $a;
					
				}
			}			
			
		// get log databases
			$LogDBs = $Root->getElementsByTagName('logdatabases');
			foreach( $LogDBs as $LogDB )
			{
				$Items = $LogDB->getElementsByTagName('logdb');
				foreach( $Items as $logdb )
				{
					$a = array();
					foreach( $logdb->attributes as $attribute ) $a[$attribute->nodeName] = $attribute->nodeValue;
					LogSettings::$LogDatabases[] = $a;
					unset( $a );				
				}
			}	

		// get branches 
			$BranchLists = $Root->getElementsByTagName('branchlist');
			foreach( $BranchLists as $BranchList )
			{
				$branches = $BranchList->getElementsByTagName('branch');
				foreach( $branches as $branch )
				{
					$a = array();
					foreach( $branch->attributes as $attribute ) $a[$attribute->nodeName] = $attribute->nodeValue;
					LogSettings::$Branches[] = $a;
					unset( $a );
				}
			}
	}
}

?>