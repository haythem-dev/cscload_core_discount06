<style type="text/css">
  body
  {
    background-color: #7B7D7D;
  }
</style>

# csc_load | how to's 

<br>
<br>

## How to...

<br>
<br>

**...add a new field to an existing table**

>Make sure you download and configure DADE as described here:   
>https://coin-collaboration.phoenix.loc/communities/pgit_developerzone/AEWiki/DADE.aspx
  
>ATTENTION: some objects are referencing tables that are NOT in the same project!  
>Example: artikelzentral table is defined in project phosix, but the object is in project Nordat   
>(don't ask why, we don't have an answer either ¯\\_(ツ)_/¯)  
>Use the search function in the menue bar to find your table or object: Help... -> Find...


>1. Add the new field(s) in the desired table  
>2. Select the object, right click on attribues "Update Object Attributes"
>3. Select the table on the right side
>4. Double click on the field to add it to the object
>5. Close the window 
>6. Right click on the object itself and select "Generate Headerfile" 
>7. Copy and replace the existing headerfile with the new one
>8. Adjust code if necessary

<br>


**...test tpldzentral**

>ATTENTION: 
>Check /software/wss/de/ksc/load/vars/tpldzentral.vars  
You can configure it to load the data from the zdev21 or ide21!  
>You are very likely to change the date of some articles in table zaplfege:ide21 to load some datasets.


>1. To avoid unnecessary commits, copy the files to your repository on UNIX via FileZilla for example  
>2. Create the bin by calling the make command, for example like this:  
>make debug, make relase or make -j30  
>3. Duplicate the already existing tpldzentral.bin, in case the new compiled version fails:  
>/software/wss/{country}/ksc/load/bin cp tpldzentral.bin tpldzentral.bin.old  
>4. Copy the new compiled bin to /software/wss/{country}/ksc/load/bin  
>5. Start tpldzentral:  
>/software/wss/de/ksc/load/proc tpldzentral.sh -start  
>/software/wss/de/ksc/load/proc tpldzentral.sh -start -ld 20220123


<br>