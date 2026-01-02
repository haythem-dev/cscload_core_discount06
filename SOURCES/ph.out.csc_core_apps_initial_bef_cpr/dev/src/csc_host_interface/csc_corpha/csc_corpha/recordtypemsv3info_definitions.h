//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeMSV3Info
 *  \author		Steffen Heinlein
 *  \date		08.08.2013
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	enum MSV3InfoTextType{ ORDERLABEL = 0, PACKAGELABEL = 1 }; // ORDERLABEL == "MSV3-Auftragskennung", PACKAGELABEL == "MSV3-GebindeID"

	struct MSV3InfoValues
	{
		basar::VarString 			RecordType; 
		basar::Long64				KSCOrderNo;
		basar::VarString            TextType;
		basar::Long64				SeqNo;
		basar::VarString			Text;		

		MSV3InfoValues()
		{
			init();
		}

		void init()
		{
			RecordType = "M3";
			KSCOrderNo = 0;
			TextType = " ";
			SeqNo = 0;						
			Text = " ";
		}
	};

	namespace MSV3InfoFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;						
		static const size_t LENGTH_KSCODERNO = 7;
		static const size_t LENGTH_TEXTTYPE = 1;
		static const size_t LENGTH_SEQNO = 9;
		static const size_t LENGTH_TEXT = 20;		
	}
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_DEFINITIONS_H
