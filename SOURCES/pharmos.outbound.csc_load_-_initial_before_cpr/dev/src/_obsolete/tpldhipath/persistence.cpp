///////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition: Persistence.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "define.h"
#include "macro.h"
#include "persistence.h"
#include "customerroutingtable.h"
#include <sstream>

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
Persistence::Persistence()
: m_ErrMsg( "" )
{
	__FUNCTION__( Persistence::Persistence )
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
Persistence::~Persistence()
{
	__FUNCTION__( ~Persistence() )
	DEBUG_ENTER( fun )	
	
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair< bool, S_Counter > Persistence::processAndSave( const std::list<S_SQLKUNDE>& customers, const long lDateOfRunning )
{
	__FUNCTION__( Persistence::process() )
	DEBUG_ENTER( fun )	
    
    bool processed = true;	

    SCustomRoutingTable* objSCustomRoutingTable = createCustomRoutingTable();
    std::ostringstream os;
    unsigned int uiNoTransAction = 0;
	std::list<S_SQLKUNDE>::const_iterator it;
	for( it = customers.begin(); it != customers.end(); ++it ){
		uiNoTransAction++;
        objSCustomRoutingTable->init();

		if( it->isValidCustomerPhoneNo_TelNr() == false ){
        	continue;
        }
        
        // CUSTOMER PHONE NO
        os.str("");
		os << "0" << it->CUSTOMERPHONENO_TELNR;
		strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.ORIGIN, os.str().c_str() );

        //  CALLTYPE
		if( strlen(it->PHONEPRIORITY) > 0 ){
			switch( it->PHONEPRIORITY[0] ){
				case 'V':	os.str("");
							os << "AA_VIP";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 89;
							break;
				case 'A':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 80;
							break;
				case 'B':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 60;
							break;
				case 'C':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 40;
							break;
				case 'D':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 20;
							break;
				case 'S':	os.str("");
							os << "AA_Sonder";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable->m_stSQLSTRUCT.INITIALPRIORITY = 89;
							break;

				default:	continue;
			}
		}
		//  CAPTION
		os.str("");
		os  << right << setw( 2 )   << setfill( '0' )   << it->VERTRIEBSZENTRUMNR
		    << right << setw( 7 )                       << it->KUNDENNR 
		    << right << setw( 8 )                       << lDateOfRunning
            << right                                    << " " 
            << right                                    << it->NAMEAPO 
            << right                                    << " " 
            << right                                    << it->ORT;
		strcpy( objSCustomRoutingTable->m_stSQLSTRUCT.CAPTION, os.str().c_str() );

#ifndef NDEBUG
		//objSCustomRoutingTable->toStream();
#endif
        if( false == save( *objSCustomRoutingTable ) ){
            processed = false;	
            break;
        }
	} // ENDE FOR

    delete objSCustomRoutingTable; 

    DEBUG_LEAVE( fun )	
    return std::make_pair( processed, objSCustomRoutingTable->m_stS_Counter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string& Persistence::getErrMsg() const
{
	__FUNCTION__( Persistence::getErrMsg() )
	DEBUG_ENTER( fun )	
    return m_ErrMsg;
	DEBUG_LEAVE( fun )	
}

