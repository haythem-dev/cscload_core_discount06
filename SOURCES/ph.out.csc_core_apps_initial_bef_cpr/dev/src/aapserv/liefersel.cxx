/* Lieferantendaten Selektionsdatei */
#include"bufkon.h"
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<memory.h>
#include "ppgeneric.h"
#include "passwd.h"	 /* nase iftsel spaeter entfernen */
#include "lieferinfo.h"
EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define VERSION "1.0"

/* PROTOTYPES */
extern void write_log(int status, char *FehlerMeldung);
extern long UID; /* User - ID (wie in passwd) */


int LieferselSel_info(struct LIEFERINFO *liefer, char *error_msg)
{
 
EXEC SQL BEGIN DECLARE SECTION;
struct LIEFERINFO  *l;
EXEC SQL END DECLARE SECTION;

l = liefer;

EXEC SQL select
          bliefer.besla_name,
          bliefer.plz_strasse,
          bliefer.ort,
          bliefer.e_mail,
          bliefer.einkaufsverbot,
          liefer.arzneimittelbezug
    into
          :l->BESLA_NAME,
          :l->PLZ_STRASSE,
          :l->ORT,
          :l->E_MAIL,
          :l->EINKAUFSVERBOT,
          :l->ARZNEIMITTELBEZUG
    from  bliefer, liefer
    where bliefer.besla_nr = :l->BESLA_NR
	  and liefer.lant_nr = bliefer.lant_nr;
 
 if (sqlca.sqlcode < 0)
  {
   sprintf(error_msg, "LieferselSel_info: select %ld", sqlca.sqlcode);
   return -1;
  }

if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;  
  }

return 0; 
}

