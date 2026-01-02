<?

function showSubmit( $fieldname, $description )
{
    ?><input type="submit" name="<?= $fieldname ?>" value="<?= $description ?>" style="font-size: 8pt"/><?
}

function showTextArea( $request, $fieldname, $cols = 150, $rows = 20, $wrap = 'soft' )
{
    ?><textarea cols="<?= $cols ?>" rows="<?= $rows ?>" wrap="<?= $wrap ?>" name="<?= $fieldname ?>"><?= $request[$fieldname] ?></textarea><?
}

function showInputText( $request, $fieldname, $password = false, $size = 10, $maxlength = 20 )
{
    if( false == $password )
    {
        ?><input type="text" name="<?= $fieldname ?>" value="<?=$request[$fieldname]?>" maxlength="<?= $maxlength ?>" size="<?= $size ?>" style="font-size: 8pt"/><?
    }
    else
    {
        ?><input type="password" name="<?= $fieldname ?>" value="<?=$request[$fieldname]?>" maxlength="<?= $maxlength ?>" size="<?= $size ?>" style="font-size: 8pt"/><?
    }
}


function showSelect( $request, $fieldname, $arrData, $keyname, $valuename )
{
    ?><select name="<?= $fieldname ?>" size="1" style="font-size: 8pt"><?
        foreach( $arrData as $a )
        {
            if( !isset( $request[$fieldname] ) )
            {
                ?><option value="<?= $a[$valuename] ?>"><?= $a[$keyname] ?></option><?
            }
            else
            {            
                if( $request[$fieldname] == $a[$valuename] )
                {
                    ?><option selected value="<?= $a[$valuename] ?>"><?= $a[$keyname] ?></option><?
                }
                else
                {
                    ?><option value="<?= $a[$valuename] ?>"><?= $a[$keyname] ?></option><?
                }
            }
        }
    ?></select><?
}

?>