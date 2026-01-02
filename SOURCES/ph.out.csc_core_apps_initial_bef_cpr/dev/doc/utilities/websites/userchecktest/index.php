<?php

@header( "Expires: Mon, 26 Jul 1997 05:00:00 GMT" );
@header( "Last-Modified: " . gmdate( "D, d M Y H:i:s" ). " GMT" );
@header( "Cache-Control: no-store, no-cache, must-revalidate" );
@header( "Cache-Control: post-check=0, pre-check=0", false );
@header( "Pragma: no-cache" );
@ini_set( "max_execution_time", 700 );
@ini_set( "default_socket_timeout", 700 );	

?>
<html>

<head>
    <title>UserCheck XML</title>
    <link rel="stylesheet" type="text/css" href="prz.css"/>    
    <script language="JavaScript" src="ajaxtools.js"></script>	
</head>

<body>

    <h1>UserCheck XML / MSV3 (Testenvironment)</h1>

    <!--<h2>Parameters</h2>-->
    <form method="GET" name="input">
        <table><tr><td><fieldset>
        <table>                       
            <tr>
                <th>Username</th>
                <th>Password</th>
            </tr>
            <tr>
                <td>
                    <input type="text" id="username" value="" />
                </td>
                <td>
                    <input type="text" id="password" value="" />
                </td>
            </tr>
            <tr>
                <td colspan="2" align="center">
                    <input type="button" id="usercheck" name="usercheck" value="Check Account" onclick="checkAccount();" />
                </td>
            </tr>
        </table>
        </fieldset></td></tr></table>

    </form>

    <h2>Results</h2>
    <table>
    	<tbody>
	    	<tr>
	    		<td> <span id="SalesWebResult"></span> &nbsp; </td>
	    	</tr>
    	</tbody>    	    	
    </table>
        
</body>

</html>