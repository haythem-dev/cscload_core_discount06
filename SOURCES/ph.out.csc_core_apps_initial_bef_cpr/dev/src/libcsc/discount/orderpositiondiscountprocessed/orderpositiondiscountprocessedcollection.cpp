#include "orderpositiondiscountprocessedcollection.h"

namespace libcsc
{
namespace discount
{
void OrderPositionDiscountProcessedCollection::insert( 
	const basar::Int32 positionNo, 
	const libcsc::discount::OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed
		)
{
	std::map<basar::Int32, libcsc::discount::OrderPositionDiscountProcessedPtr>::insert( 
		std::pair<basar::Int32, libcsc::discount::OrderPositionDiscountProcessedPtr>( positionNo, orderPositionDiscountProcessed ) 
			);
}

bool OrderPositionDiscountProcessedCollection::contains( const basar::Int32 positionNo ) const
{
	return ( find( positionNo ) != end() );
}

} // end namespace discount
} // end namespace libcsc

