#ifndef TCAWRAP_H
#define TCAWRAP_H

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif

//------------------------------------------------------------------------------
// types
//------------------------------------------------------------------------------

//! error message buffer
typedef char ErrorMsg[512];

//! parameters for CICS connection
struct CicsConnParam
{
	char config    [128];	//!< configuration (e.g. "VSEGO_70"); 
	char ipaddr    [ 64];	//!< CICS host ip address
	char port      [ 16];	//!< CICS host port
	char starttrans[ 64];	//!< CICS host start transaction (e.g. "TCAS")
	char user      [ 64];	//!< user name       (optional)
	char passwd    [ 64];	//!< user's password (optional)
	
	char cicsname  [128];	//!< out: hold CICS name for opened session
							//!< after connect (e.g. "A02CICS2")
	long slot           ;	//!< out: slot with connected session
	int  open           ;	//!< out: 0/1 connection closed/open
};

//------------------------------------------------------------------------------
// init 
//------------------------------------------------------------------------------

//! init necessary shared libraries: necessary for forked children processes!
void				initTcaChild	();

//------------------------------------------------------------------------------
// CICS 
//------------------------------------------------------------------------------

//! is CICS available? should be called before openConn()
//! \retval     1          CICS is up
//! \retval     0          CICS is down
//! \param[in]  pConnParam connection parameters
//! \param[in]  timeout    timeout (in seconds) for trying to connect
//! \param[out] errmsg     buffer for error message
int 				isCicsAvail		(const struct CicsConnParam * const pConnParam,
									 int                                timeout   ,									 
									 ErrorMsg                           errmsg	  );

//------------------------------------------------------------------------------
// connection
//------------------------------------------------------------------------------

//! reset connection parameters
//! \param[out] pConnParam is filled with default parameters
void 				resetConnParam	(struct CicsConnParam * const pConnParam);

//! set connection parameter to struct CicsConnParam (reset implicity)
//! \param[in]  config      configuration (e.g. "PhoenixGeneric_west")
//! \param[in]  ipaddr		CICS host ip address
//! \param[in]  port        CICS host port
//! \param[in]  starttrans  CICS start transaction
//! \param[in]  user        CICS user 
//! \param[in]  passwd      CICS user's password 
//! \param[out] pConnParam  filled with connection parameters
void				setConnParam	(const char * const           config,
									 const char * const           ipaddr,
									 const char * const           port,			
									 const char * const           starttrans,	
									 const char * const           user,			
									 const char * const           passwd,		
									 struct CicsConnParam * const pConnParam	
									);

//! get connection's CICS name after session is opened
//! \param[in] pConnParam connection parameters
const char *        getConnCicsName	(const struct CicsConnParam * const pConnParam);

//! get connections's slot after session is opened
//! \param[in] pConnParam connection parameters
long 				getConnSlot		(const struct CicsConnParam * const pConnParam);

//! is connection open?
//! \retval    1          for success
//! \retval    0          failure
//! \param[in] pConnParam connection parameters
int					isConnOpen		(const struct CicsConnParam * const pConnParam);

//! \brief  open CICS connection
//! \retval         1          success
//! \retval         0          failure
//! \param[in, out] pConnParam connection parameters: after connect out field are set
//! \param[out]     errmsg     buffer for error message
int					openConn		(struct CicsConnParam * const pConnParam,
									 ErrorMsg                     errmsg    );

//! \brief  close CICS connection
//! \retval         1          success
//! \retval         0          failure
//! \param[in, out] pConnParam connection parameters: after connect out field are set
//! \param[out]     errmsg     buffer for error message
int					closeConn		(struct CicsConnParam * const pConnParam,
								     ErrorMsg                     errmsg    );

//------------------------------------------------------------------------------
// function call
//------------------------------------------------------------------------------

//! call CICS link module
//! \retval     1          success
//! \retval     0          failure
//! \param[in]  pConnParam connection parameters
//! \param[in]  call       e.g: "call stp.tcastp ('xyz', '1234')"
//! \param[out] result     result buffer, must be allocated
//! \param[in]  resultlen  length of result buffer
//! \param[out] errmsg     buffer for error message
int					callCics		(const struct CicsConnParam * const pConnParam,
									 const char * const                 call      ,
									 char * const                       result    ,	
									 unsigned long                      resultlen ,
									 ErrorMsg                           errmsg    );

//------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------
#endif

