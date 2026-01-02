#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_PARAMETER_DBACTIONPARAMETER_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_PARAMETER_DBACTIONPARAMETER_H

//-----------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-----------------------------------------------------------------------------------------------//
//  class declaration section
//-----------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
	namespace infrastructure
	{
		namespace parameter
		{
			class DBActionParameter
			{
			    public:
				    ~DBActionParameter();

                    static const basar::VarString ART_WITHOUT_STOCK_SEL_ACTIVE;
                    static const basar::VarString SUBS_ART_WITH_STOCK_SEL_ACTIVE;
                    static const basar::VarString PSEUDO_ARTICLES_SEL_ACTIVE;
                    static const basar::VarString ACTIVE_ARTICLES_SEL_ACTIVE;
                    static const basar::VarString ART_WO_STCK_BOOKING_SEL_ACTIVE;
                    static const basar::VarString RESERVED_ARTICLES_SEL_ACTIVE;
                    static const basar::VarString SPECIAL_PZNS_SEL_ACTIVE;
                    static const basar::VarString ART_REIMPORT_SEL_ACTIVE;
                    //static const basar::VarString INACTIVE_ARTICLES_SEL_ACTIVE;
                    //static const basar::VarString RES_ART_WITH_TYPE_SEL_ACTIVE;

                    static const basar::VarString PERSISTENCE_STRATEGY;
				    
			private:
				////////////////////////////////
				// methods
				////////////////////////////////
                DBActionParameter();
                DBActionParameter( const DBActionParameter& r );
                DBActionParameter& operator = ( const DBActionParameter& r );
			};
		}
	}
}

#endif
