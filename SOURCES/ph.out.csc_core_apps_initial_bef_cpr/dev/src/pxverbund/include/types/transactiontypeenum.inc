#ifndef GUARD_TRANSCTIONTYPE_ENUM_H
#define GUARD_TRANSCTIONTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum TransactionTypeEnum
{
	TRANSACTIONTYPE_DEBIT					=  97, // 'a',	
	TRANSACTIONTYPE_GOODSIN 				=  98, // 'b',  
	TRANSACTIONTYPE_CUSTOMERRETURNS 		=  99, // 'c',  
	TRANSACTIONTYPE_STOCKRECONCILIATION 	= 100, // 'd',  
	TRANSACTIONTYPE_PERMANENTINVENTORY		= 101, // 'e',  
	TRANSACTIONTYPE_AUXDELIVERY 			= 102, // 'g',  
	TRANSACTIONTYPE_SHORTAGE				= 103, // 'k',  
	TRANSACTIONTYPE_AUXBOOKED				= 104, // 'm',  
	TRANSACTIONTYPE_BATCHINCONSISTENCY		= 105, // 'o',  
	TRANSACTIONTYPE_VSEAMOUNT				= 106, // 'q',  
	TRANSACTIONTYPE_SUPPLY  				= 107, // 'r',  
	TRANSACTIONTYPE_QUOTA_EXCEEDED			= 108, // 'v',  
	TRANSACTIONTYPE_CODEBLOCAGE 			= 109, // 'y',  
	TRANSACTIONTYPE_RESERVATION 			= 110, // 'x',  
	TRANSACTIONTYPE_TRANSFERQUARANTINE		= 111, // 'z',  
	TRANSACTIONTYPE_PICKING_CORRECTION		= 65  // 'A'   
} 


// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_TRANSCTIONTYPE_ENUM_H
