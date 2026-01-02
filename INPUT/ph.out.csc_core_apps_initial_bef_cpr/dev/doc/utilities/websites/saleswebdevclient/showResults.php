<?php

function showResults( $array, $link, $starttime, $endtime )
{
    ?><table align="center" width="100%" style="font-size: 10pt">
            <tr>
                <td><h2>Results</h2></td>
            </tr>
            <tr>
                <td>
                    <fieldset>
                        <pre>
                        <?
                        $i = 1;
                        foreach( $array as $x )
                        {
                            $duration = $x['duration'];
                            $httpcode = $x['httpcode'];
                            print "\r\nNo. $i \t\t Duration: $duration sec.\t\t http Code: $httpcode";
                            $i++;
                        }
                        ?>
                        </pre>
                    </fieldset>
               </td>
            </tr>
            <tr>
                <td><h2>Details</h2></td>
            </tr>
            <tr>
                <td>
                    <fieldset>
                        <b>Used Link: &nbsp;</b><font color='black'><?= $link ?></font><br/>
                        <b><?= $starttime ?> - <?= $endtime ?></b>
                        <br/>
                        <?
                        $i = 1;
                        foreach( $array as $x )
                        {
                            ?>
                            <hr>
                            <h2>No. <?= $i ?>, Duration: <?= $x['duration'] ?> sec., http Code: <?= $x['httpcode'] ?></h2>
							<pre>
                            <?    
                            //file_put_contents( "lastresponse.xml", $x['content'] );
                            $content = str_replace( ">", ">\r\n", str_replace( "\r\n", "", $x['content'] ) );
							print htmlspecialchars( $content );							
                            $i++;
							?>
							</pre>
							<?
                        }
                        ?>
                    </fieldset>
               </td>
            </tr>
        </table><?
}

?>

