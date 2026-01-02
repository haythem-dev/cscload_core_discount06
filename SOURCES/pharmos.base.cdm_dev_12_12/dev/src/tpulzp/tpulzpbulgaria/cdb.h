 
/*****************************************************************************/
/*                                                                           */
/*   header     : cdb.h                                                      */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 07.04.97                                                   */
/*   language   : C/Esql                                                     */
/*                                                                           */
/*   declaration: standard-functions for database calls                      */
/*                                                                           */
/*****************************************************************************/

/*** INCLUDE *****************************************************************/

 #include "cprztype.h"
 typedef enum { DIRTY_READ = 0, COMMITTED_READ, CURSOR_STABILITY, 
                REPEATABLE_READ } sqlread;                        
 
/*** DECLARATION *************************************************************/

 #ifdef __CPLUS__
 extern "C" { 
  #ifndef __S390IBM__
  bool OpenDb( char *spDatabase );
  bool CloseDb( void );
  bool ConnectDb( char *spDatabase );
  #else  
  bool OpenDb( char *spDatabase, char *spSsid );
  bool CloseDb( char *spDatabase, char *spSsid );
  bool ConnectDb( char *spDatabase, char *spSsid );
  #endif
  bool SetIsolation( sqlread iSqlRead );
  bool SetLockMode( int iSec );
  bool SetExplainOn( void );
  bool SetExplainOff( void );
  bool Commit( void );
  bool Begin( void );
  bool Rollback( void );
  bool GetNumberOfBranch( void *vBranchNo, dataTyp d );
 }
 #else
  #ifndef __S390IBM__
  extern bool OpenDb( char *spDatabase );
  extern bool CloseDb( void );
  extern bool ConnectDb( char *spDatabase );
  #else
  extern bool OpenDb( char *spDatabase, char *spSsid );
  extern bool CloseDb( char *spDatabase, char *spSsid );
  extern bool ConnectDb( char *spDatabase, char *spSsid );
  #endif
  extern bool SetIsolation( sqlread iSqlRead );
  extern bool SetExplainOn( void );
  extern bool SetExplainOff( void );
  extern bool Commit( void );
  extern bool Begin( void );
  extern bool Rollback( void );
  extern bool GetNumberOfBranch( void *vBranchNo, dataTyp d );
 #endif

/*** END - DECLARATION *******************************************************/
