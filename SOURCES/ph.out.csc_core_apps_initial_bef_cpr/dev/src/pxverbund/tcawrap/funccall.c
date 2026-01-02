#include "tcawrap.h"

#include <assert.h>
#include <string.h>
#include <tcaapi.h>

#include "error.h"


//------------------------------------------------------------------------------
int	callCics (const struct CicsConnParam * const pConnParam,
		      const char * const                 call      ,
		      char * const                       result    ,
			  unsigned long                      resultlen ,
		      ErrorMsg                           errmsg    )
{
#ifdef WIN32
	TCAHANDLE handle = 0;
#else
	ULONG handle = 0;
#endif
    int   ret    = 1;

	strcpy(errmsg, "");
	
	// send call to host
    if (FALSE == tcACCESS_HostSqlQueryAsync_Start( 
        TCADBT_SQL_ENGINE,	// DB type
        call,				// SQL statement
        0,					// MaxCharFieldLength
        NULL, NULL, NULL,	// host parameter
        0,					// max records
        &handle,				// query handle
        pConnParam->slot,	// slot
        0,					// options
        NULL,				// parent window
        NULL,				// progress callback
        0, 0				// error display
        ) )
    {
        errorhandler(errmsg);
        return 0;
    }

    assert(0 != handle);

	// get description, number of rows & colums from host 
	{
		PTCACCESS_SQL_DATA_DESCRIPTION pSQLDesc      = 0;
		BOOL                           fEndOfData    = FALSE;
		ULONG                          numberOfCols;
		ULONG                          numberOfRows;

		if (FALSE == tcACCESS_HostSqlQueryAsync_FetchData ( (void **) &pSQLDesc, 	// result description
															&numberOfCols, 
															&numberOfRows, 
															handle,					// query handle 
															&fEndOfData
														  ) )
		{
			errorhandler(errmsg);
			ret = 0;
		}
        else
        {
            assert(1    == numberOfCols);
            assert(1    == numberOfRows);
            assert(TRUE == fEndOfData  );

            // get values
            {
                USHORT len;
                BOOL   fNull;
                
                if (FALSE == tcACCESS_HostSqlQueryAsync_GetOutputFieldValue(1,			// column 
                                                                            1,			// row
                                                                            result, 	// result buffer
                                                                            resultlen,  // result buffer length
                                                                            &len,		// value length 
                                                                            &fNull,		// null flag
                                                                            handle		// query handle
                                                                           ) )
                {
                    errorhandler(errmsg);
                    ret = 0;
                }

                assert(len   <= resultlen);
                assert(FALSE == fNull);

            }
        }
    }

	// close call
    if (FALSE == tcACCESS_HostSqlQueryAsync_Stop(handle))
    {
        errorhandler(errmsg);
        return 0;
	}

	return ret;
}

