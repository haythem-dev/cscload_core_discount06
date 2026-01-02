//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeRemark
 *  \author		Steffen Heinlein
 *  \date		28.05.2014
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	struct RemarkValues
	{
		basar::VarString		RecordType;
		basar::Long64			OrderNo;
		basar::Long64			PositionNo;
		basar::Int32			TextType;
		basar::Int32			SequentialNo;
		basar::VarString		Text;

		RemarkValues()
		{
			init();
		}

		void init()
		{
			RecordType = "TX";
			OrderNo = 0;
			PositionNo = 0;
			TextType = 0;
			SequentialNo = 0;
			Text = "";
		}
	};

	namespace RemarkFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_ORDERNO = 7;
		static const size_t LENGTH_POSITIONNO = 7;
		static const size_t LENGTH_TEXTTYPE = 4;
		static const size_t LENGTH_SEQUENTIALNO = 4;
		static const size_t LENGTH_TEXT = 250;		
	}
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_DEFINITIONS_H
