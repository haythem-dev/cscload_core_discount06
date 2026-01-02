 
/* ERSTELLUNGSDATUM: 5.Aug.1993              */
/* DEFINE FUER -- PASSWD --                  */
 
  #define L_PASSWD_FILIAL_NR              4
  #define L_PASSWD_USERNAME               8
  #define L_PASSWD_PASSWORD               8
  #define L_PASSWD_UID                    11
  #define L_PASSWD_LAGER                  50
 
/* LAENGE DER INDIZES                        */
 
  #define I_PASSWD_FILIAL_NR              4
  #define I_PASSWD_USERNAME               8
  #define L_PASSWD_PKEY                   12
 
/* BESCHREIBUNG FUER -- PASSWD --            */
 
  static struct buf_desc PASSWD_BES [] =       
  {
  { TYP_C ,    4,    0 },
  { TYP_C ,    8,    0 },
  { TYP_C ,    8,    0 },
  { TYP_L ,   11,    0 },
  { TYP_C ,   50,    0 },
  };
 
  #define PASSWD_ANZ (int) (sizeof(PASSWD_BES) / sizeof (struct buf_desc) )
 
/* STRUCTUR FUER -- PASSWD --                */
 
  #ifdef ESQL_C                                
  EXEC SQL BEGIN DECLARE SECTION;              
  #endif                                       
 
  struct PASSWD {                              
    char   FILIAL_NR             [5];
    char   USERNAME              [9];
    char   PASSWORD              [9];
    long   UID;        
    char   LAGER                 [51];
  };
 
  #ifdef ESQL_C                                
  EXEC SQL END DECLARE SECTION;                
  #endif                                       
 
/* STRUCTUR FUER COBOLD -- PASSWD --         */
 
  #ifdef ESQL_C                                
  EXEC SQL BEGIN DECLARE SECTION;              
  #endif                                       
 
  struct COB_PASSWD {                          
    char   FILIAL_NR             [4];
    char   USERNAME              [8];
    char   PASSWORD              [8];
    long   UID;        
    char   LAGER                 [50];
  };
 
  #ifdef ESQL_C                                
  EXEC SQL END DECLARE SECTION;                
  #endif                                       
 
/* STRUCTUR (CHAR) FUER -- PASSWD --         */
 
  struct C_PASSWD {                            
    char   FILIAL_NR             [4];
    char   USERNAME              [8];
    char   PASSWORD              [8];
    char   UID                   [11];
    char   LAGER                 [50];
  };
 
/* STRUCTUR FUER INDIKATOR (INT-BS)          */
 
  struct II_PASSWD {                           
    int    FILIAL_NR;        
    int    USERNAME;        
    int    PASSWORD;        
    int    UID;        
    int    LAGER;        
  };
 
 
/* STRUCTUR FUER INDIKATOR (INT-MX)          */
 
  #ifdef ESQL_C                                
  EXEC SQL BEGIN DECLARE SECTION;              
  #endif                                       
 
  struct I_PASSWD {                            
    short  FILIAL_NR;        
    short  USERNAME;        
    short  PASSWORD;        
    short  UID;        
    short  LAGER;        
  };
 
  #ifdef ESQL_C                                
  EXEC SQL END DECLARE SECTION;                
  #endif                                       
 
/* STRUCTUR FUER INDIKATOR (CHAR)            */
 
 
  struct IC_PASSWD {                           
    char   FILIAL_NR            [1];  
    char   USERNAME             [1];  
    char   PASSWORD             [1];  
    char   UID                  [1];  
    char   LAGER                [1];  
  };
 
  #define G_PASSWD sizeof( struct PASSWD )     
