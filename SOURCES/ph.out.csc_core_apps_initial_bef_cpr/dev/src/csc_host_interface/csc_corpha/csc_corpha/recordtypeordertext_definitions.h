//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeOrderText
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	enum TextType{ HEADTEXT = 1, TAILTEXT = 2 };

	struct OrderTextValues
	{
		basar::VarString		RecordType;
		basar::VarString		Text;

		OrderTextValues()
		{
			init();
		}

		void init()
		{
		}
	};

	namespace OrderTextFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_TEXT = 240;
	}
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_DEFINITIONS_H
