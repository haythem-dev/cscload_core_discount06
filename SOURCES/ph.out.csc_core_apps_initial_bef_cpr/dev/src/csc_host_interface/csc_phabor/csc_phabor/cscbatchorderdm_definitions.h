//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDM_DEFINITIONS
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDM_DEFINITIONS

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
    namespace batchOrder
    {
        namespace processing
		{
			namespace cscBatchOrderDM
			{
				//const basar::Int32  VSE_RUBBISH = 40404;
				const basar::Int32  VSE_CENTURY_DEF = 20000000;
				const basar::Int32  VSE_DATE_FILLER = 1000000;
				const basar::Int32  VSE_DATE_ZERO = 0;
				//const basar::Int32  VSE_DATE_RUBBISH = VSE_CENTURY_DEF + 4040404;
				const basar::Int32  BRANCH_FOR_SAP_DELNO = 48;

				const basar::VarString	DEFAULT_ORDERNO = "0";

				basar::ConstString ORDER_TEXT_DEFAULT = "-AUFTRAG";
				basar::ConstString ORDER_TEXT_SET_UP = "EINRICHTER";
				basar::ConstString ORDER_TEXT_WAREHOSUE = "LAGER";
				basar::ConstString ORDER_TEXT_WAREHOUSE_DISTRIBUTION = "LAGER VERTEILER";
				basar::ConstString ORDER_TEXT_INDUSTRY_RETURN = "INDUSTRIE RETOUR";
				basar::ConstString ORDER_TEXT_PICKING_ERROR = "KOMMIFEHLER-AUFTRAG";
				basar::ConstString ORDER_TEXT_WRONG_CUSTOMER = "Auftrag fuer Kunde : ";
				basar::ConstString ORDER_TEXT_IBT = "VERBUND-AUFTRAG";
				basar::ConstString ORDER_FLAG_PICKING_ERROR = "C";
				basar::ConstString ORDER_FLAG_MAIN_WAREHOUSE = "S";
				basar::ConstString PHARMOS_YES = "J";

				const basar::VarString PARAMETER_APPLICATION = "CSC_PHABOR";
				const basar::VarString PARAMETER_REASON = "BATCHORDERSPLIT";
				const basar::VarString PARAMETER_NAME = "BATCHORDERTYPE";
			}
        }
    }
}

#endif
