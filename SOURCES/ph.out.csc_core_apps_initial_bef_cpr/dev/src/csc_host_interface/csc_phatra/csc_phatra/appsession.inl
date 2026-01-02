//--------------------------------------------------------------------------------------------------//
/*! \brief      
 *  \author     Bischof Bjoern
 *  \date       29.12.2010
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

inline std::ostream& operator<< ( std::ostream& strm, const csc_phatra::AppSession& appSession )
{
	appSession.toStream( strm );
	return strm;
}
