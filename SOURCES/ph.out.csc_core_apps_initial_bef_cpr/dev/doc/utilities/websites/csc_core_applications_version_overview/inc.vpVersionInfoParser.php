<pre>
<?php
/*
$svncontent = file_get_contents( "example_svn.txt" );
$gitcontent = file_get_contents( "example_git.txt" );
print "<h2>SVN</h2>";
var_dump(parseVersionInfos($svncontent));
print "<hr>";
print "<h2>GIT</h2>";
var_dump(parseVersionInfos($gitcontent));
*/

function parseVersionInfos($vpinfo)
{
		$retval = array();		
		$lines = explode( "\n", $vpinfo );

		if( strstr($vpinfo, "Origin:") && strstr($vpinfo, "Branch:") )
		{					
			foreach( $lines as $line )
			{
				$line = trim($line);
				
				if( substr($line, 0, 4) == '@(#)' ) $retval['git_version'] = trim(substr($line,4));
				if( substr($line, 0, 7) == 'Origin:') $retval['git_origin'] = trim(substr($line,7));
				if( substr($line, 0, 7) == 'Branch:') $retval['git_branch'] = trim(substr($line,7));
				if( substr($line, 0, 7) == 'Commit:') $retval['git_commit'] = trim(substr($line,7));
				if( substr($line, 0, 7) == 'Status:') $retval['git_status'] = trim(substr($line,7));
				if( substr($line, 0, 4) == 'Tag:') $retval['git_tag'] = trim(substr($line,4));
				if( substr($line, 0, 5) == 'Date:') $retval['git_date'] = trim(substr($line,5));
				if( substr($line, 0, 7) == 'Author:') $retval['git_author'] = trim(substr($line,7));
			}
			
			$retval['version'] = $retval['git_version'];
			$retval['revision'] = $retval['git_commit'] . " | " . $retval['git_status'];
			$retval['date'] = substr($retval['git_date'], 0, 10);
			$retval['time'] = substr($retval['git_date'], 11, 8);
			$retval['url'] = $retval['git_origin'] . " | " . $retval['git_branch'] . " | " . $retval['git_tag'];
			
		}		
		
		if( strstr($vpinfo, "svn://") )
		{				
			$version  = ""; $versiontemplate  = "Version: @(#)"; 
			$revision = "";	$revisiontemplate = "Revision: ";
			$date     = ""; $datetemplate     = "Date: ";
			$time     = ""; $timetemplate     = "Time: ";
			$svnurl   = ""; $svnurltemplate   = "URL: ";
			
			foreach( $lines as $line )
			{												
				if( substr( $line, 0, strlen( $versiontemplate ) ) == $versiontemplate )
				{														
					$version = substr( $line, strlen( $versiontemplate ), strlen( $line ) - strlen( $versiontemplate ) );
					$xtemplate = " v ";
					$version = substr( $version, strpos( $version, $xtemplate ) + strlen( $xtemplate ), strlen( $version ) - (2 * strlen( $xtemplate )) );
					
				}
				if( substr( $line, 0, strlen( $revisiontemplate ) ) == $revisiontemplate )
				{														
					$revision = substr( $line, strlen( $revisiontemplate ), strlen( $line ) - strlen( $revisiontemplate ) );
				}		
				if( substr( $line, 0, strlen( $datetemplate ) ) == $datetemplate )
				{														
					$date = substr( $line, strlen( $datetemplate ), strlen( $line ) - strlen( $datetemplate ) );
				}		
				if( substr( $line, 0, strlen( $timetemplate ) ) == $timetemplate )
				{														
					$time = substr( $line, strlen( $timetemplate ), strlen( $line ) - strlen( $timetemplate ) );
				}					
				if( substr( $line, 0, strlen( $svnurltemplate ) ) == $svnurltemplate )
				{														
					$svnurl = trim(substr( $line, strlen( $svnurltemplate ), strlen( $line ) - strlen( $svnurltemplate ) ));									
					$svntemplate = "svn://denu00ms0023/marathon/orderentry/csc_core_applications";
					$svnurl = trim(substr( $svnurl, strlen( $svntemplate ), strlen( $svnurl ) - strlen( $svntemplate ) ));									
					
					$lines = explode( "/dev", $svnurl );
					$svnurl = str_replace( "/dev", "<br />/dev", $svnurl );	
					$svnurl = $lines[0];																	
				}					
			}				
			
			$retval['version'] = $version;
			$retval['revision'] = $revision;
			$retval['date'] = $date;
			$retval['time'] = $time;
			$retval['url'] = $svnurl;
		}
		
		return $retval;
}

?>
</pre>