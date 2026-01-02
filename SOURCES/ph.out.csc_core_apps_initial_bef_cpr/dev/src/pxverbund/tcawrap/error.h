#ifndef ERROR_H
#define ERROR_H

//! retrieve error message in case of failure
void 	errorhandler	(ErrorMsg errmsg	//!< buffer for error message
						);

//! append log message to file /tmp/tcawrap.log
void	logMsg			(const char * const msg,		//!< log message
						 int                enable		//!< is logging enabled?
						);

#endif

