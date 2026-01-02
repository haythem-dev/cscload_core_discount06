/* Artikelauskunft Auftragsbearbeitung Selektionsdatei */
#include"bufkon.h"
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<memory.h>
#include "ppgeneric.h"
#include "passwd.h"	 /* nase iftsel spaeter entfernen */
#include "telview.h"
#include "koplist.h"
EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define VERSION "1.0"

/* PROTOTYPES */
extern void write_log(int status, char *FehlerMeldung);
extern long UID; /* User - ID (wie in passwd) */


int IftselSel_suchbez(struct VTELARTAK *d, char *error_msg)
{
   static int fst = 1;

   EXEC SQL BEGIN DECLARE SECTION;
      struct VTELARTAK   *a;
   EXEC SQL END DECLARE SECTION;

   a = d;

   if (fst) /* beim ersten mal oder bei neu deklarieren */
     {
      fst = 0;
      ppGStripLast(a->ARTIKEL_NAME);
      EXEC SQL declare Sel_suchbez scroll cursor with hold for
      select 
         VTELARTAK_LISTE 
      from 
         TELARTAK
      where   
         artikel_name like :a->ARTIKEL_NAME;

      EXEC SQL open Sel_suchbez;
      if (sqlca.sqlcode < 0 )
        {
         fst = 1;
         sprintf(error_msg, "IftselSel_suchbez: open Sel_suchbez %ld %ld", 
                             sqlca.sqlcode, sqlca.sqlerrd[1]);
         return -1;
        }
     } /* ENDE if (fst) */
   if (a->FETCH_REL == 0)   /* close cursor */
     {
      fst = 1;
      EXEC SQL close Sel_suchbez;
      if (sqlca.sqlcode < 0 )
        {
         sprintf(error_msg, "IftselSel_suchbez: close Sel_suchbez %ld %ld",
                             sqlca.sqlcode, sqlca.sqlerrd[1]);
         return -1;
        }
      return 1;
     }
   EXEC SQL fetch relative :a->FETCH_REL Sel_suchbez into VTELARTAK_ZEIGER(a);
   if (sqlca.sqlcode < 0 )
     {
      fst = 1;
      sprintf(error_msg, "IftselSel_suchbez: fetch Sel_suchbez %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      EXEC SQL close Sel_suchbez;
      return -1;
     }
   if (sqlca.sqlcode == SQLNOTFOUND)
     {
      return 1;
     }
   return 0;
}

int IftselVers_kontr(struct PASSWD *pw, char *error_msg) 
{
int rc;

UID = pw->UID;
while (pw->USERNAME[strlen(pw->USERNAME)-1] == ' ') 
       pw->USERNAME[strlen(pw->USERNAME)-1]  = '\0';
rc = strcmp(VERSION, pw->USERNAME);
if (rc != 0)
  {
   sprintf(error_msg,
   "Versionskonflikt Server:%s Client:%s", VERSION, pw->USERNAME);
   return -1;
  }
return 0;
}

int IftselSel_tellistt(struct KOPLIST *art, char *error_msg)
{
static int fst = 1;
 
EXEC SQL BEGIN DECLARE SECTION;
struct KOPLIST  *a;
struct I_KOPLIST i;
EXEC SQL END DECLARE SECTION;

a = art;

if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
    ppGStripLast(a->BEZEICHNUNG);
    EXEC SQL declare cu_seltel scroll cursor with hold for
    select
          tellist.satznr,
          tellist.pzn,
          tellist.bezeichnung,
          tellist.alternativ_name,
          tellist.dispo_hinweis,
          tellist.bemerkung
    from  tellist
    where tellist.bezeichnung like :a->BEZEICHNUNG /*oracle matches nase*/
	and	  tellist.pzn >= 0
    order by BEZEICHNUNG;
 
   EXEC SQL open cu_seltel;
   if (sqlca.sqlcode < 0)
      {
       fst = 1;
       sprintf(error_msg, "IftselSel_tellistt: open cu_seltel %ld", sqlca.sqlcode);
       return -1;
      }
   }
     
if(a->FETCH_REL == 0)  /* close cursor */
  {     
   fst = 1;
      EXEC SQL close cu_seltel;
      if (sqlca.sqlcode < 0)
     {
      sprintf(error_msg, "IftselSel_tellistt: close cu_seltel %ld", sqlca.sqlcode);
      EXEC SQL close cu_seltel;
      return -1;
     } 
    return 1; 
  }
  
EXEC SQL fetch relative :a->FETCH_REL cu_seltel
    into
          :a->SATZNR          indicator :i.SATZNR,
          :a->PZN             indicator :i.PZN,
          :a->BEZEICHNUNG     indicator :i.BEZEICHNUNG,
          :a->ALTERNATIV_NAME indicator :i.ALTERNATIV_NAME,
          :a->DISPO_HINWEIS   indicator :i.DISPO_HINWEIS,
          :a->BEMERKUNG       indicator :i.BEMERKUNG;
 if (sqlca.sqlcode < 0)
  {
   fst = 1;
   sprintf(error_msg, "IftselSel_tellistt: fetch cu_telsel %ld", sqlca.sqlcode);
   EXEC SQL close cu_seltel;
   return -1;
  }

if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;  
  }
if (i.BEZEICHNUNG   < 0)
   {
    strcpy(error_msg,"IftselSel_tellistt: BEZEICHNUING NULL");
    EXEC SQL close cu_seltel;
    return -1;
   }
if (i.PZN   < 0)
   {
    strcpy(error_msg,"IftselSel_tellistt: PZN NULL");
    EXEC SQL close cu_seltel;
    return -1;
   }
if (i.ALTERNATIV_NAME < 0)
   {
    strcpy(error_msg,"IftselSel_tellistt: ALTERNATIV_NAME NULL");
    EXEC SQL close cu_seltel;
    return -1;
   }
if (i.DISPO_HINWEIS  < 0)
   {
    strcpy(error_msg,"IftselSel_tellistt: DISPO_HINWEIS NULL");
    EXEC SQL close cu_seltel;
    return -1;
   }
if (i.BEMERKUNG < 0)
   {
    strcpy(error_msg,"IftselSel_tellistt: BEMERKUNG NULL");
    EXEC SQL close cu_seltel;
    return -1;
   }

return 0; 
}

int IftselSel_info(struct KOPLIST *art, char *error_msg)
{
 
EXEC SQL BEGIN DECLARE SECTION;
struct KOPLIST  *a;
EXEC SQL END DECLARE SECTION;

a = art;

EXEC SQL select
          tellist.satznr,
          tellist.pzn,
          tellist.bezeichnung,
          tellist.alternativ_name,
          tellist.dispo_hinweis,
          tellist.bemerkung
    into
          :a->SATZNR,
          :a->PZN,
          :a->BEZEICHNUNG,
          :a->ALTERNATIV_NAME,
          :a->DISPO_HINWEIS,
          :a->BEMERKUNG
    from  tellist
    where tellist.PZN = :a->PZN;
 
 if (sqlca.sqlcode < 0)
  {
   sprintf(error_msg, "IftselSel_info: select %ld", sqlca.sqlcode);
   return -1;
  }

if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;  
  }

return 0; 
}

int IftselIns_tellistt(struct KOPLIST *art, char *error_msg)
{

EXEC SQL BEGIN DECLARE SECTION;
struct KOPLIST  *a;
EXEC SQL END DECLARE SECTION;

a=art;

EXEC SQL insert into tellist
      (satznr,
      pzn,
      bezeichnung,
      alternativ_name,
      dispo_hinweis,
      bemerkung)  
   values  
      (:a->SATZNR,
      :a->PZN,
      :a->BEZEICHNUNG,
      :a->ALTERNATIV_NAME,
      :a->DISPO_HINWEIS,
      :a->BEMERKUNG);   
if (sqlca.sqlcode < 0)
  {
   sprintf(error_msg, "IftselIns_tellistt: insert %ld", sqlca.sqlcode);
   EXEC SQL close cu_seltel;
   return -1;
  }
return 0;
}

int IftselUpd_tellistt(struct KOPLIST *art, char *error_msg)
{

EXEC SQL BEGIN DECLARE SECTION;
struct KOPLIST  *a;
EXEC SQL END DECLARE SECTION;

a=art;

EXEC SQL update tellist
   set   bezeichnung     = :a->BEZEICHNUNG,
         pzn             = :a->PZN,
         alternativ_name = :a->ALTERNATIV_NAME,
         dispo_hinweis   = :a->DISPO_HINWEIS,
         bemerkung       = :a->BEMERKUNG  
   where satznr = :a->SATZNR;
     
if (sqlca.sqlcode < 0)
  {
   sprintf(error_msg, "IftselUpd_tellistt: update %ld", sqlca.sqlcode);
   EXEC SQL close cu_seltel;
   return -1;
  }
return 0;
}

int IftselDel_tellistt(struct KOPLIST *art, char *error_msg)
{

EXEC SQL BEGIN DECLARE SECTION;
struct KOPLIST  *a;
EXEC SQL END DECLARE SECTION;
a=art;

EXEC SQL delete from tellist
   where satznr = :a->SATZNR;
     
if (sqlca.sqlcode < 0)
  {
   sprintf(error_msg, "IftselDel_tellistt: delete %ld", sqlca.sqlcode);
   EXEC SQL close cu_seltel;
   return -1;
  }
return 0;
}
