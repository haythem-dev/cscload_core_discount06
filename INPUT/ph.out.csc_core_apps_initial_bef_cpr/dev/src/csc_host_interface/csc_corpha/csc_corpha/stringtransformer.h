#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDERDM_STRINGTRANSFORMER_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDERDM_STRINGTRANSFORMER_H

#include <libbasar_definitions.h>

namespace domMod
{
	namespace corpha
	{
		namespace ProcessOrderDM
		{
			class StringTransformer
			{
				private:
					StringTransformer();
					virtual ~StringTransformer();

					static basar::VarString m_Country;

				public:
					// Function to replace unprintable characters (for specific locale) with '_'
					static basar::VarString& transform(basar::VarString& str);

					// Transformation should be performed based on corresponding locale
					static void setCountry( const basar::VarString & country );
			};
		}
	}
}
#endif //GUARD_DOMMOD_CORPHA_PROCESSORDERDM_STRINGTRANSFORMER_H