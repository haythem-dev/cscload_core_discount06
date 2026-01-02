//--------------------------------------------------------------------------------------------//
/*! \file        
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       09.08.2013
 *  \version    00.00.00.01 first version 
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PACKAGELABELCOLLECTION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PACKAGELABELCOLLECTION_H

#include <libbasarcmnutil_bstring.h>
#include <icsc_loggerptr.h>
#include <vector>

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{
	class PackageLabelCollection
	{
		public:

			struct sPackageLabelItem
			{
				basar::Int32 PackageLabelID;
				basar::VarString PackageLabel;
			};

											PackageLabelCollection();
											~PackageLabelCollection();								

			basar::Int32					addPackageLabel( const basar::VarString& );
			void							injectLogger( libcsc_utils::ICSC_LoggerPtr );
			
			bool							hasItems() const;
			const sPackageLabelItem&		getFirst();
			const sPackageLabelItem&		getNext();
			bool							isEnd();

		private:

											PackageLabelCollection( const PackageLabelCollection& );
											PackageLabelCollection& operator= ( const PackageLabelCollection& );		

			std::vector<sPackageLabelItem>	m_PackageLabelVector;
			libcsc_utils::ICSC_LoggerPtr	m_Logger;
			basar::Int32					m_CurrentID;

			std::vector<PackageLabelCollection::sPackageLabelItem>::const_iterator m_Iterator;
			sPackageLabelItem				m_CurrentLabel;
	};
}
}
}

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PACKAGELABELCOLLECTION_H
