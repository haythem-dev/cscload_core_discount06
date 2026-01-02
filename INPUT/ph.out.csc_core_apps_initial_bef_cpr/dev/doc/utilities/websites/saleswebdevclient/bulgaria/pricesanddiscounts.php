<?php

ini_set( 'max_execution_time', 6000 );

require_once '../includes/httpPostSimulation.php';
require_once '../includes/getSalesWebLinks.php';
require_once '../includes/getSalesWebUser.php';
require_once '../includes/showFormElements.php';
require_once '../includes/showResults.php';

$arrLinks      = getSalesWebLinks( 'pricesanddiscounts', 'BG' );
$arrUser       = getSalesWebUser( 'BG' );

if( !isset( $_REQUEST['FRM_XMLRequest'] ) )
{
    $_REQUEST['FRM_XMLRequest'] = file_get_contents( 'xmldata/pricesanddiscounts.xml' );
}
else
{
    $_REQUEST['FRM_XMLRequest'] = stripslashes( $_POST['FRM_XMLRequest'] );
}

if( !isset( $_REQUEST['FRM_Username'] ) )
    $_REQUEST['FRM_Username'] = '';

if( !isset( $_REQUEST['FRM_NumberOfRequests'] ) )
    $_REQUEST['FRM_NumberOfRequests'] = 1;

if( !isset($_REQUEST['FRM_Passwort']) )
	$_REQUEST['FRM_Passwort'] = '';
	
?>

<html>
<head><link rel="stylesheet" type="text/css" href="../style/prz.css"/></head>
<body link="#FFFFFF" vlink="#FFFFFF" alink="#FFFFFF">
	<h1><img src="../images/bulgaria.jpg" height="5%"/> &nbsp; PricesAndDiscounts Interface Bulgaria</h1>
    <table align="center" width="100%" style="font-size: 10pt">
        <tr>
            <td>
                <fieldset>
                    <form method="POST" action="<?=$_SERVER['PHP_SELF']?>">

                        <table style="font-size: 10pt">
                          <tr>
                              <td><b>Link: </b></td>
                              <td><? showSelect( $_REQUEST, 'FRM_Link', $arrLinks, 'server', 'link' ); ?></td>
                          </tr>
                          <tr>
                              <td><b>Username: </b></td>
                              <td><? showInputText( $_REQUEST, 'FRM_Username', false, 15 ); ?></td>
                          </tr>
                          <tr>
                              <td><b>Passwort: </b></td>
                              <td><? showInputText( $_REQUEST, 'FRM_Passwort', false, 15 ); ?></td>
                          </tr>
                          <tr>
                              <td valign="top"><b>XML Request: </b></td>
                              <td><? showTextArea( $_REQUEST, 'FRM_XMLRequest' ); ?></td>
                          </tr>
                          <tr>
                              <td><b>Number of requests: </b></td>
                              <td><? showInputText( $_REQUEST, 'FRM_NumberOfRequests', false, 2 ); ?></td>
                          </tr>
                          <tr>
                            <td colspan="2"><? showSubmit( 'FRM_Submit', 'Request PricesAndDiscounts' ); ?></td>
                          </tr>
                        </table>
                    </form>
                </fieldset>
            </td>
        </tr>
    </table>
	<?
	if( isset( $_REQUEST['FRM_Submit'] ) )
	{
	    $strXMLRequest     = utf8_encode( stripslashes( $_REQUEST['FRM_XMLRequest'] ) );
	    $strUsername       = $_REQUEST['FRM_Username'];
	    $strLink           = $_REQUEST['FRM_Link'];
	    $strPassword       = $_REQUEST['FRM_Passwort'];
	    $strNumberRequests = $_REQUEST['FRM_NumberOfRequests'];

	    $start_time = date("d.m.Y H:i:s");
	    $arrResult  = httpPostSimulation::multiplePostDataREF( $strNumberRequests, $strLink, $strUsername, $strPassword, $strXMLRequest, '#REF#' );
	    $end_time   = date("d.m.Y H:i:s");

	    showResults( $arrResult, $strLink, $start_time, $end_time );
	}
	?>
</body>
</html>
